#pragma once

using namespace System;

namespace OdaCliWrapper {
	public ref class SimpleDraw
	{
	public:
		/// <summary>
		/// 初始化 ODA
		/// </summary>
		/// <param name="runtimePath">ODA Runtime / License 路径</param>
		/// <param name="hostHwnd">WinForms.Handle 或 WPF HwndSource.Handle</param>
		static bool Initialize(String^ runtimePath, IntPtr hostHwnd);

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
	};
}
