// ODA SDK 要求：每个 cpp 文件必须首先包含 OdaCommon.h
#include "OdaCommon.h"

#include "pch.h"
#include "OdaEngine.h"

// ===== ODA =====
// 先包含基础头文件（这些头文件会定义 OdSmartPtr）
#include "OdPlatformSettings.h"
#include "RxInit.h"
#include "RxObject.h"  // OdSmartPtr 定义在这里
#include "OdAnsiString.h"  // OdAnsiString 定义在这里

// ODA 授权信息
#include "OdaActivationInfo.h"

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

void OdaEngine::Initialize(HWND hwnd)
{
    m_hwnd = hwnd;

    // 从文件读取 ODA SDK 授权信息
    std::string activationFilePath = OdaActivation::GetDefaultActivationFilePath();
    auto activationInfo = OdaActivation::ReadActivationInfo(activationFilePath);
    
    if (!activationInfo.first.empty() && !activationInfo.second.empty())
    {
        // ODA SDK 授权激活（必须在 odInitialize 之前调用）
        odActivate(OdAnsiString(activationInfo.first.c_str()), 
                   OdAnsiString(activationInfo.second.c_str()));
    }

    // 初始化 ODA Runtime
    odInitialize(nullptr);

    m_db = OdDbDatabase::createObject();
}

void OdaEngine::CreateOrUpdateBox(const BoxParam& p)
{
    if (!m_box.isNull())
        m_box->erase();

    m_box = OdDb3dSolid::createObject();
    m_box->createBox(p.length, p.width, p.height);

    OdDbBlockTablePtr bt =
        m_db->getBlockTableId().safeOpenObject(OdDb::kForWrite);

    OdDbBlockTableRecordPtr ms =
        bt->getAt(OD_T("MODEL_SPACE")).safeOpenObject(OdDb::kForWrite);

    ms->appendOdDbEntity(m_box);
}

void OdaEngine::CreateOrUpdateCylinder(const CylinderParam& p)
{
    // 删除旧的圆柱体
    if (!m_cylinder.isNull())
        m_cylinder->erase();

    // 创建新的圆柱体
    // 注意：ODA SDK 的 OdDb3dSolid 可能不直接支持 createCylinder
    // 这里使用 createBox 作为临时方案，实际项目中需要使用 BRep 或其他方法创建圆柱体
    // 或者使用扩展的 3D Solid 类（如 OcDb3dSolid）
    m_cylinder = OdDb3dSolid::createObject();
    
    // 临时方案：使用 box 近似圆柱体（实际应该使用 BRep 创建真正的圆柱体）
    // 这里创建一个正方形截面的柱体来近似圆柱体
    double diameter = p.radius * 2.0;
    m_cylinder->createBox(diameter, diameter, p.height);

    OdDbBlockTablePtr bt =
        m_db->getBlockTableId().safeOpenObject(OdDb::kForWrite);

    OdDbBlockTableRecordPtr ms =
        bt->getAt(OD_T("MODEL_SPACE")).safeOpenObject(OdDb::kForWrite);

    ms->appendOdDbEntity(m_cylinder);
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
