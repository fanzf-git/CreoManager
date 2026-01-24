#pragma once
#include <windows.h>

// ODA SDK 头文件 - 需要按正确顺序包含
#include "OdaCommon.h"
#include "RxObject.h" 
#include "SmartPtr.h"
#include "DbDatabase.h"
#include "Db3dSolid.h"

// 图形系统相关
#include "GiContextForDbDatabase.h"
#include "DbGsManager.h"
#include "DynamicLinker.h"
// 通过项目配置的 $(UserOdaLib) 附加目录来找到此头文件
#include "OdModuleNames.h"

// ODA 前向声明 - 在 cpp 文件中包含完整定义
class OdDbDatabase;
class OdDb3dSolid;
class OdGiContextForDbDatabase;
class OdGsDevice;

typedef OdSmartPtr<OdDbDatabase>            OdDbDatabasePtr;
typedef OdSmartPtr<OdDb3dSolid>             OdDb3dSolidPtr;
typedef OdSmartPtr<OdGiContextForDbDatabase> OdGiContextForDbDatabasePtr;
typedef OdSmartPtr<OdGsDevice>              OdGsDevicePtr;

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

// ============================================================================
// 模块1：绘制图形功能 + 简单显示（单视图）
// ============================================================================
// OdaEngine 负责：
// 1. 管理 OdDbDatabase（建模）
// 2. 管理 GsDevice + GiContext，将数据库绘制到指定 HWND
// ============================================================================

class OdaEngine
{
public:
    static OdaEngine& Instance();

    // 初始化引擎（需要先调用 OdaInitializer::Initialize()）
    // hwnd: WinForms/BIMViewEditor 的窗口句柄
    bool Initialize(HWND hwnd = nullptr);
    
    // 创建或更新 Box
    bool CreateOrUpdateBox(const BoxParam& param);
    
    // 创建或更新 Cylinder
    bool CreateOrUpdateCylinder(const CylinderParam& param);
    
    // 触发重绘
    void Redraw();
    // 缩放到当前模型范围
    void ZoomToExtents();
    
    // 获取当前圆柱体的高度
    double GetHeight();
    
    // 获取当前数据库（用于高级操作）
    const OdDbDatabasePtr GetDatabase() const { return m_db; }

private:
    OdaEngine() = default;
    ~OdaEngine() = default;
    
    // 禁止拷贝和赋值
    OdaEngine(const OdaEngine&) = delete;
    OdaEngine& operator=(const OdaEngine&) = delete;

    bool initGraphics(HWND hwnd);

private:
    HWND  m_hwnd        = nullptr;
    bool  m_initialized = false;

    // 数据库与实体
    OdDbDatabasePtr m_db;
    OdDb3dSolidPtr  m_box;
    OdDb3dSolidPtr  m_cylinder;

    // 图形系统
    OdGiContextForDbDatabasePtr m_giCtx;
    OdGsDevicePtr               m_device;
};
