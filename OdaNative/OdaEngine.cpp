#include "OdaCommon.h"

#include "pch.h"
#include "OdaEngine.h"
#include "OdaInitilize.h"
#include "AbstractViewPE.h"
#include "Ge/GeBoundBlock3d.h"
#include "OdaDbHostServices.h"

// ===== ODA =====
// 先包含基础头文件（这些头文件会定义 OdSmartPtr）
#include "OdPlatformSettings.h"
#include "RxInit.h"
#include "RxObject.h"      // OdSmartPtr 定义在这里
#include "OdAnsiString.h"  // OdAnsiString 定义在这里

// DbDatabase 等头文件在 ODAToolkit\Drawing\Include 目录下，直接包含文件名
#include "DbDatabase.h"
#include "Db3dSolid.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
// GeExtents3d.h 在 Kernel\Include\Ge 子目录下，使用模块前缀
#include "Ge/GeExtents3d.h"

// Gs / Gi
#include "GiContextForDbDatabase.h"
#include "DbGsManager.h"
#include "DynamicLinker.h"
#include "RxDictionary.h"
#include "RxVariantValue.h"
#include "OdModuleNames.h"

// 全局 DbHostServices 实例（生命周期覆盖整个进程，使用 OdStaticRxObject 提供 addRef/release 实现）
static OdStaticRxObject<OdaDbHostServices> g_dbHostServices;

OdaEngine& OdaEngine::Instance()
{
	static OdaEngine inst;
	return inst;
}

bool OdaEngine::Initialize(HWND hwnd)
{
	// 确保 ODA 已经初始化
	if (!OdaInitializer::IsInitialized())
	{
		if (!OdaInitializer::Initialize())
		{
			return false;  // ODA 初始化失败
		}
	}

	m_hwnd = hwnd;

	// 创建新的数据库（使用 DbHostServices，自动创建默认布局/模型空间）
	m_db = g_dbHostServices.createDatabase(true, OdDb::kMetric);

	// 如果提供了窗口句柄，则初始化图形系统（将数据库绑定到给定 HWND 上）
	// 对于控制台 / 单元测试场景（hwnd == nullptr），只做建模，不初始化图形系统。
	if (hwnd)
	{
		if (!initGraphics(hwnd))
		{
			m_db.release();
			m_initialized = false;
			return false;
		}
	}

	m_initialized = true;
	return true;
}

bool OdaEngine::CreateOrUpdateBox(const BoxParam& p)
{
	if (!m_initialized || m_db.isNull())
	{
		return false;
	}

	try
	{
		// 删除旧的 Box
		if (!m_box.isNull())
		{
			m_box->erase();
		}

		// 创建新的 Box
		m_box = OdDb3dSolid::createObject();
		m_box->createBox(p.length, p.width, p.height);

		// 获取模型空间（注意：名称为 *Model_Space）
		OdDbBlockTablePtr bt =
			m_db->getBlockTableId().safeOpenObject(OdDb::kForRead);

		OdDbBlockTableRecordPtr ms =
			bt->getAt(OD_T("*Model_Space")).safeOpenObject(OdDb::kForWrite);

		// 添加到模型空间
		ms->appendOdDbEntity(m_box);

		// 模型更新后先缩放视图到几何范围，再统一刷新
		ZoomToExtents();
		Redraw();

		return true;
	}
	catch (const OdError& e)
	{
		OdString msg = OD_T("CreateOrUpdateBox failed: ");
		msg += e.description();
		msg += OD_T("\r\n");
		OutputDebugStringW(reinterpret_cast<LPCWSTR>(msg.c_str()));
		return false;
	}
	catch (...)
	{
		OutputDebugStringW(L"CreateOrUpdateBox failed: unknown exception\r\n");
		return false;
	}
}

bool OdaEngine::CreateOrUpdateCylinder(const CylinderParam& p)
{
	if (!m_initialized || m_db.isNull())
	{
		return false;
	}

	try
	{
		// 删除旧的圆柱体
		if (!m_cylinder.isNull())
		{
			m_cylinder->erase();
		}

		// 创建新的圆柱体
		// 或者使用扩展的 3D Solid 类（如 OcDb3dSolid）
		m_cylinder = OdDb3dSolid::createObject();

		// 这里创建一个正方形截面的柱体来近似圆柱体
		double diameter = p.radius * 2.0;
		m_cylinder->createBox(diameter, diameter, p.height);

		// 获取模型空间
		OdDbBlockTablePtr bt =
			m_db->getBlockTableId().safeOpenObject(OdDb::kForRead);

		OdDbBlockTableRecordPtr ms =
			bt->getAt(OD_T("*Model_Space")).safeOpenObject(OdDb::kForWrite);

		// 添加到模型空间
		ms->appendOdDbEntity(m_cylinder);

		// 模型更新后先缩放视图到几何范围，再统一刷新
		ZoomToExtents();
		Redraw();

		return true;
	}
	catch (const OdError& e)
	{
		OdString msg = OD_T("CreateOrUpdateCylinder failed: ");
		msg += e.description();
		msg += OD_T("\r\n");
		OutputDebugStringW(reinterpret_cast<LPCWSTR>(msg.c_str()));
		return false;
	}
	catch (...)
	{
		OutputDebugStringW(L"CreateOrUpdateCylinder failed: unknown exception\r\n");
		return false;
	}
}

void OdaEngine::Redraw()
{
	// 如果图形设备已初始化，直接刷新一次
	if (!m_device.isNull())
	{
		try
		{
			m_device->update();
		}
		catch (const OdError& e)
		{
			OdString msg = OD_T("Redraw: m_device->update() failed: ");
			msg += e.description();
			msg += OD_T("\r\n");
			OutputDebugStringW(reinterpret_cast<LPCWSTR>(msg.c_str()));
		}
		return;
	}

	// 否则退回到简单的窗口重绘
	if (m_hwnd)
		InvalidateRect(m_hwnd, nullptr, TRUE);
}

double OdaEngine::GetHeight()
{
	if (m_cylinder.isNull())
		return 0.0;

	OdGeExtents3d ext;
	m_cylinder->getGeomExtents(ext);

	return ext.maxPoint().z - ext.minPoint().z;
}

// ============================================================================
// 内部：图形系统初始化
// ============================================================================
bool OdaEngine::initGraphics(HWND hwnd)
{
  try
  {
    if (m_db.isNull())
      return false;

    // 创建 Gi 上下文
    m_giCtx = OdGiContextForDbDatabase::createObject();
    m_giCtx->setDatabase(m_db);

    // 使用模块名宏
    MODULE_NAMES_DEFINED

    // 优先尝试 OpenGL -> GDI（这是之前验证过可行的组合）
    OdGsModulePtr pGsModule = ::odrxDynamicLinker()->loadModule(OdWinOpenGLModuleName);
    if (pGsModule.isNull())
      pGsModule = ::odrxDynamicLinker()->loadModule(OdWinGDIModuleName);
    if (pGsModule.isNull())
    {
      OutputDebugStringW(L"initGraphics: failed to load Gs module (OpenGL/GDI)\r\n");
      return false;
    }

    // 创建 Device
    m_device = pGsModule->createDevice();
    if (m_device.isNull())
    {
      OutputDebugStringW(L"initGraphics: createDevice() returned null\r\n");
      return false;
    }

    // 绑定窗口句柄，并设置常用属性
    OdRxDictionaryPtr pProps = m_device->properties();
    if (!pProps.isNull())
    {
      pProps->putAt(OD_T("WindowHWND"), OdRxVariantValue((OdIntPtr)hwnd));

      if (pProps->has(OD_T("DoubleBufferEnabled")))
        pProps->putAt(OD_T("DoubleBufferEnabled"), OdRxVariantValue(true));
      if (pProps->has(OD_T("EnableSoftwareHLR")))
        pProps->putAt(OD_T("EnableSoftwareHLR"), OdRxVariantValue(true));
      if (pProps->has(OD_T("DiscardBackFaces")))
        pProps->putAt(OD_T("DiscardBackFaces"), OdRxVariantValue(true));
    }

    // 将数据库关联到当前布局，并创建视图（增加异常信息输出，便于调试）
    try
    {
      m_device = OdDbGsManager::setupActiveLayoutViews(m_device, m_giCtx);
    }
    catch (const OdError& e)
    {
      OdString msg = OD_T("setupActiveLayoutViews failed: ");
      msg += e.description();
      msg += OD_T("\r\n");
      OutputDebugStringW(reinterpret_cast<LPCWSTR>(msg.c_str()));
      throw;
    }

    // 根据窗口客户区尺寸设置 Device 大小
    if (hwnd)
    {
      RECT rc{};
      if (::GetClientRect(hwnd, &rc))
      {
        if (rc.right > rc.left && rc.bottom > rc.top)
        {
          // OdGsDCRect(左, 右, 下, 上)
          OdGsDCRect gsRect(rc.left, rc.right, rc.bottom, rc.top);
          m_device->onSize(gsRect);
        }
      }
    }

    // 初始一次更新（同样保护一下，方便看到具体异常）
    try
    {
      m_device->update();
    }
    catch (const OdError& e)
    {
      OdString msg = OD_T("initGraphics: m_device->update() failed: ");
      msg += e.description();
      msg += OD_T("\r\n");
      OutputDebugStringW(reinterpret_cast<LPCWSTR>(msg.c_str()));
      throw;
    }

    return true;
  }
  catch (...)
  {
    m_device.release();
    m_giCtx.release();
    return false;
  }
}

void OdaEngine::ZoomToExtents()
{
  // 简化版：当前只触发一次统一重绘，不做额外视图计算，避免 Debug 版 ODA 内部断言。
  Redraw();
}
