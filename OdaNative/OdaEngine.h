#pragma once
#include <windows.h>

// ODA 基础定义
#include "SmartPtr.h"

// ODA 前向声明 - 在 cpp 文件中包含完整定义
class OdDbDatabase;
class OdDb3dSolid;

// 定义智能指针类型
typedef OdSmartPtr<OdDbDatabase> OdDbDatabasePtr;
typedef OdSmartPtr<OdDb3dSolid> OdDb3dSolidPtr;

struct BoxParam
{
    double length;
    double width;
    double height;
};

class OdaEngine
{
public:
    static OdaEngine& Instance();

    void Initialize(HWND hwnd);
    void CreateOrUpdateBox(const BoxParam& param);
    double GetHeight();

private:
    OdaEngine() = default;

private:
    HWND m_hwnd = nullptr;

    OdDbDatabasePtr m_db;
    OdDb3dSolidPtr  m_box;
};
