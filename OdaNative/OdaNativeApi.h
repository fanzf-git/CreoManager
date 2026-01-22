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

    struct OdaInitParam
    {
        const wchar_t* runtimePath;  // ODA Runtime / License 路径
        void* hostHwnd;              // WinForms.Handle / WPF HwndSource.Handle
    };

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

    ODA_API bool Oda_Initialize(const OdaInitParam* param);

    // ----------------- 建模接口 -----------------

    ODA_API bool Oda_CreateOrUpdateBox(const OdaBoxParam* param);

    ODA_API bool Oda_CreateOrUpdateCylinder(const OdaCylinderParam* param);

    // ----------------- 查询 -----------------

    ODA_API double Oda_GetHeight();

#ifdef __cplusplus
}
#endif
