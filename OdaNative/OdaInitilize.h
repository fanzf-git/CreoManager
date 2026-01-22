#pragma once

// ODA SDK 头文件
#include "OdaCommon.h"
#include "RxInit.h"
#include "RxSystemServicesImpl.h"

// 前向声明
class OdaSystemServices;

// ODA 初始化管理函数（类定义在 cpp 文件中）
// 初始化 ODA（单例模式，确保只初始化一次）
bool OdaInitializer_Initialize();

// 清理 ODA（在程序退出时调用）
void OdaInitializer_Cleanup();

// 检查是否已初始化
bool OdaInitializer_IsInitialized();

// 为了保持向后兼容，提供类接口封装
class OdaInitializer
{
public:
    static bool Initialize();
    static void Cleanup();
    static bool IsInitialized();
};
