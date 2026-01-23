#include "OdaCommon.h"

#include "pch.h"
#include "OdaEngine.h"
#include "OdaInitilize.h"

// ===== ODA =====
// 先包含基础头文件（这些头文件会定义 OdSmartPtr）
#include "OdPlatformSettings.h"
#include "RxInit.h"
#include "RxObject.h"  // OdSmartPtr 定义在这里
#include "OdAnsiString.h"  // OdAnsiString 定义在这里

// DbDatabase 等头文件在 ODAToolkit\Drawing\Include 目录下，直接包含文件名
#include "DbDatabase.h"
#include "Db3dSolid.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
// GeExtents3d.h 在 Kernel\Include\Ge 子目录下，使用模块前缀
#include "Ge/GeExtents3d.h"
#include <windows.h>

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

	// 创建新的数据库
	m_db = OdDbDatabase::createObject();

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

		// 获取模型空间
		OdDbBlockTablePtr bt = m_db->getBlockTableId().safeOpenObject(OdDb::kForWrite);

		OdDbBlockTableRecordPtr ms = bt->getAt(OD_T("MODEL_SPACE")).safeOpenObject(OdDb::kForWrite);

		// 添加到模型空间
		ms->appendOdDbEntity(m_box);

		return true;
	}
	catch (...)
	{
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
			m_db->getBlockTableId().safeOpenObject(OdDb::kForWrite);

		OdDbBlockTableRecordPtr ms =
			bt->getAt(OD_T("MODEL_SPACE")).safeOpenObject(OdDb::kForWrite);

		// 添加到模型空间
		ms->appendOdDbEntity(m_cylinder);

		return true;
	}
	catch (...)
	{
		return false;
	}
}

void OdaEngine::Redraw()
{
	// 触发重绘（如果需要的话）
	if (m_hwnd)
	{
		InvalidateRect(m_hwnd, nullptr, TRUE);
	}
}

double OdaEngine::GetHeight()
{
	if (m_cylinder.isNull())
		return 0.0;

	OdGeExtents3d ext;
	m_cylinder->getGeomExtents(ext);

	return ext.maxPoint().z - ext.minPoint().z;
}
