#pragma once
#include <windows.h>

// ODA SDK 头文件 - 需要按正确顺序包含
// 注意：由于头文件中使用了 OdSmartPtr 作为成员变量，需要包含完整的定义
// OdaCommon.h 必须在最前面，定义必要的宏（如 FIRSTDLL_EXPORT）
#include "OdaCommon.h"
#include "RxObject.h"  // OdSmartPtr 定义在这里

// ODA 前向声明 - 在 cpp 文件中包含完整定义
class OdDbDatabase;
class OdDb3dSolid;

// 智能指针类型别名
// 注意：RxObject.h 已经定义了 OdSmartPtr，这里直接使用
typedef OdSmartPtr<OdDbDatabase> OdDbDatabasePtr;
typedef OdSmartPtr<OdDb3dSolid> OdDb3dSolidPtr;

struct BoxParam
{
    double length;
    double width;
    double height;
};

struct CylinderParam
{
    double radius;
    double height;
};

class OdaEngine
{
public:
    static OdaEngine& Instance();

    void Initialize(HWND hwnd);
    void CreateOrUpdateBox(const BoxParam& param);
    void CreateOrUpdateCylinder(const CylinderParam& param);
    void Redraw();
    double GetHeight();

private:
    OdaEngine() = default;

private:
    HWND m_hwnd = nullptr;

    OdDbDatabasePtr m_db;
    OdDb3dSolidPtr  m_box;
    OdDb3dSolidPtr  m_cylinder;
};
