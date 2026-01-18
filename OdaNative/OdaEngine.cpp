#include "pch.h"
#include "OdaEngine.h"

// ===== ODA =====
// 先包含基础头文件
#include "OdPlatformSettings.h"
#include "RxInit.h"
// DbDatabase 等头文件在 ODAToolkit\Drawing\Include 目录下，直接包含文件名
#include "DbDatabase.h"
#include "Db3dSolid.h"
#include "DbBlockTable.h"
#include "DbBlockTableRecord.h"
// GeExtents3d.h 在 Kernel\Include\Ge 子目录下，使用模块前缀
#include "Ge/GeExtents3d.h"

OdaEngine& OdaEngine::Instance()
{
    static OdaEngine inst;
    return inst;
}

void OdaEngine::Initialize(HWND hwnd)
{
    m_hwnd = hwnd;

    // 初始化 ODA Runtime
    odInitialize(nullptr);

    m_db = OdDbDatabase::createObject();

    OdDbBlockTablePtr bt =
        m_db->getBlockTableId().safeOpenObject(OdDb::kForWrite);

    OdDbBlockTableRecordPtr ms =
        bt->getAt(OD_T("MODEL_SPACE")).safeOpenObject(OdDb::kForWrite);

    m_box = OdDb3dSolid::createObject();
    m_box->createBox(100, 100, 100);

    ms->appendOdDbEntity(m_box);
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

double OdaEngine::GetHeight()
{
    if (m_box.isNull())
        return 0.0;

    OdGeExtents3d ext;
    m_box->getGeomExtents(ext);

    return ext.maxPoint().z - ext.minPoint().z;
}
