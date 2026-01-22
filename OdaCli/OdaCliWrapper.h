#pragma once

// C++/CLI 支持
#using <mscorlib.dll>
#using <System.dll>

using namespace System;

namespace OdaCliWrapper
{
    /// <summary>
    /// 初始化参数（托管侧）
    /// </summary>
    public value struct OdaInitParam
    {
        String^ RuntimePath;   // ODA Runtime / License 路径
        IntPtr HostWindow;    // WinForms.Handle / WPF HwndSource.Handle
    };

    /// <summary>
    /// Box 参数
    /// </summary>
    public value struct OdaBoxParam
    {
        double Length;
        double Width;
        double Height;
    };

    /// <summary>
    /// Cylinder 参数
    /// </summary>
    public value struct OdaCylinderParam
    {
        double Radius;
        double Height;
    };

    /// <summary>
    /// ODA Native API 转调类（专门用于调用 OdaNative 的 C API）
    /// </summary>
    public ref class OdaNativeApiWrapper sealed
    {
    public:
        /// <summary>
        /// 初始化 ODA（转调 Oda_Initialize）
        /// </summary>
        static bool Initialize(IntPtr hwnd);

        /// <summary>
        /// 创建 / 更新 Box（转调 Oda_CreateOrUpdateBox）
        /// </summary>
        static bool CreateOrUpdateBox(OdaBoxParam param);

        /// <summary>
        /// 创建 / 更新 Cylinder（转调 Oda_CreateOrUpdateCylinder）
        /// </summary>
        static bool CreateOrUpdateCylinder(OdaCylinderParam param);

        /// <summary>
        /// 获取当前圆柱高度（转调 Oda_GetHeight）
        /// </summary>
        static double GetHeight();
    };

    /// <summary>
    /// ODA CLI 封装类（纯静态，使用 OdaNativeApiWrapper 进行转调）
    /// </summary>
    public ref class OdaEditor sealed
    {
    public:
        /// 初始化 ODA
        static bool Initialize(IntPtr hwnd);

        /// 创建 / 更新 Box
        static bool CreateOrUpdateBox(OdaBoxParam param);

        /// 创建 / 更新 Cylinder
        static bool CreateOrUpdateCylinder(OdaCylinderParam param);

        /// 获取当前圆柱高度
        static double GetHeight();
    };
}
