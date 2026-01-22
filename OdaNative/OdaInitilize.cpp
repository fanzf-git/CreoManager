#include "OdaCommon.h"

#include "pch.h"
#include "OdaInitilize.h"

// ODA SDK 头文件
#include "RxInit.h"
#include "RxSystemServices.h"
#include "RxDynamicModule.h"
#include "OdPlatformSettings.h"
#include "RxObject.h"
#include "DbDatabase.h"

// 声明 ODA SDK 的全局变量（在 TD_DbRoot.lib 中定义）
extern OdRxClass** g_odDbRegistredDwgClasses;

// 自定义 SystemServices 类，用于 ODA 激活和初始化
// 只需要实现激活逻辑，其他方法由 TD_RxServices.lib 和 TD_WinApp.lib 提供实现
class OdaSystemServices : public RxSystemServicesImpl
{
public:
    OdaSystemServices();
    virtual ~OdaSystemServices() override;

    // 禁止拷贝和赋值
    OdaSystemServices(const OdaSystemServices&) = delete;
    OdaSystemServices& operator=(const OdaSystemServices&) = delete;
};

// ODA 初始化管理类（定义在 cpp 文件中，避免头文件中的 OdStaticRxObject 识别问题）
class OdaInitializerImpl
{
public:
    // 初始化 ODA（单例模式，确保只初始化一次）
    static bool Initialize();

    // 清理 ODA（在程序退出时调用）
    static void Cleanup();

    // 检查是否已初始化
    static bool IsInitialized();

private:
    OdaInitializerImpl() = default;
    ~OdaInitializerImpl() = default;

    static bool s_initialized;
    static OdStaticRxObject<OdaSystemServices> s_systemServices;
};

// 静态成员变量定义
bool OdaInitializerImpl::s_initialized = false;
OdStaticRxObject<OdaSystemServices> OdaInitializerImpl::s_systemServices;

// ============================================================================
// OdaSystemServices 实现
// ============================================================================

OdaSystemServices::OdaSystemServices()
{
    // 包含 ODA SDK 提供的激活信息文件
    static const char* ActInfo[] = {
  #include "OdActivationInfo"
    };
    
    // 执行 ODA 激活
    // ActInfo[0] 是 userInfo，ActInfo[1] 是 userSignature
    odActivate(ActInfo[0], ActInfo[1]);
}

OdaSystemServices::~OdaSystemServices()
{
    // 清理 ODA 静态数据
    odCleanUpStaticData();
}

// ============================================================================
// OdaInitializerImpl 实现
// ============================================================================

bool OdaInitializerImpl::Initialize()
{
    // 如果已经初始化，直接返回成功
    if (s_initialized)
    {
        return true;
    }
    
    try
    {
        // 初始化 ODA（传入自定义的 SystemServices）
        // 这会初始化基础 ODA 系统并注册 DWG 类
        odInitialize(&s_systemServices);
        
        s_initialized = true;
        return true;
    }
    catch (...)
    {
        // 初始化失败
        s_initialized = false;
        return false;
    }
}

void OdaInitializerImpl::Cleanup()
{
    if (s_initialized)
    {
        // 清理 ODA
        odUninitialize();
        
        s_initialized = false;
    }
}

bool OdaInitializerImpl::IsInitialized()
{
    return s_initialized;
}

// ============================================================================
// 全局函数实现（供头文件中的 OdaInitializer 类调用）
// ============================================================================

bool OdaInitializer_Initialize()
{
    return OdaInitializerImpl::Initialize();
}

void OdaInitializer_Cleanup()
{
    OdaInitializerImpl::Cleanup();
}

bool OdaInitializer_IsInitialized()
{
    return OdaInitializerImpl::IsInitialized();
}

// ============================================================================
// OdaInitializer 类方法实现
// ============================================================================

bool OdaInitializer::Initialize()
{
    return OdaInitializer_Initialize();
}

void OdaInitializer::Cleanup()
{
    OdaInitializer_Cleanup();
}

bool OdaInitializer::IsInitialized()
{
    return OdaInitializer_IsInitialized();
}
