#pragma once

using namespace System;

namespace OdaCliWrapper {
	public ref class SimpleDraw
	{
	public:
		/// <summary>
		/// 初始化 ODA
		/// </summary>
		/// <param name="hostHwnd">WinForms.Handle 或 WPF HwndSource.Handle</param>
		static bool Initialize(IntPtr hostHwnd);

		/// <summary>
		/// 创建或更新 Box
		/// </summary>
		static bool CreateOrUpdateBox(
			double length,
			double width,
			double height);

		/// <summary>
		/// 创建或更新 Cylinder
		/// </summary>
		static bool CreateOrUpdateCylinder(
			double radius,
			double height);

		/// <summary>
		/// 获取当前圆柱高度
		/// </summary>
		static double GetHeight();

        /// <summary>
        /// 打开 DWG 文件并显示到当前视图
        /// </summary>
        static bool OpenDwg(String^ filePath);
	};
}
