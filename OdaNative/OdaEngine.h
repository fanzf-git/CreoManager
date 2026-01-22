#pragma once
#include <windows.h>

// ODA SDK 头文件 - 需要按正确顺序包含
#include "OdaCommon.h"
#include "RxObject.h" 
#include "SmartPtr.h"
#include "DbDatabase.h"
#include "Db3dSolid.h"

// ODA 前向声明 - 在 cpp 文件中包含完整定义
class OdDbDatabase;
class OdDb3dSolid;

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

// ============================================================================
// 模块1：绘制图形功能
// ============================================================================
// OdaEngine 类负责提供绘制图形功能
// 包括创建和更新 3D 实体（如 Box、Cylinder 等）
// ============================================================================

class OdaEngine
{
public:
    static OdaEngine& Instance();

    // 初始化引擎（需要先调用 OdaInitializer::Initialize()）
    // hwnd: 用于重绘的窗口句柄（可以为 nullptr）
    bool Initialize(HWND hwnd = nullptr);
    
    // 创建或更新 Box
    bool CreateOrUpdateBox(const BoxParam& param);
    
    // 创建或更新 Cylinder
    bool CreateOrUpdateCylinder(const CylinderParam& param);
    
    // 触发重绘
    void Redraw();
    
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

private:
    HWND m_hwnd = nullptr;
    bool m_initialized = false;

    OdDbDatabasePtr m_db;
    OdDb3dSolidPtr  m_box;
    OdDb3dSolidPtr  m_cylinder;
};
