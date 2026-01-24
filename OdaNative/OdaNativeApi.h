#pragma once

#ifdef ODANATIVE_EXPORTS
#define ODA_API __declspec(dllexport)
#else
#define ODA_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    // 不透明句柄（代表一个 OdaEngine 实例）
    typedef void* ODA_HANDLE;

    // ----------------- 参数结构 -----------------

    struct OdaBoxParam
    {
        double length;
        double width;
        double height;
    };

    struct OdaCylinderParam
    {
        double radius;
        double height;
    };

    // ----------------- 初始化 -----------------

    ODA_API bool Oda_Initialize(HWND hwnd);

    // ----------------- 建模接口 -----------------

    ODA_API bool Oda_CreateOrUpdateBox(const OdaBoxParam* param);

    ODA_API bool Oda_CreateOrUpdateCylinder(const OdaCylinderParam* param);

    // ----------------- 查询 -----------------

    ODA_API double Oda_GetHeight();

    // ----------------- 反初始化（可选） -----------------
    // 在进程退出前显式清理 ODA，避免 Debug 版本中的断言。
    ODA_API void Oda_Cleanup();

#ifdef __cplusplus
}
#endif
