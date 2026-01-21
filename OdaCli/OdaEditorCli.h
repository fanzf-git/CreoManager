#pragma once

namespace OdaCliWrapper
{
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public delegate void RunAction(System::Int32 id);

	public interface class IOdaEditorUiProvider
	{
	public:

		virtual void RunInUIThread(RunAction^ action, System::Int32 id);
	};

	public interface class IMcGEditorControl
	{
	public:
		/// <summary>
		/// 获取绘图控件的windows句柄(Handle of Window)
		/// </summary>
		virtual property IntPtr Handle{ virtual IntPtr get(); }

			/// <summary>
			/// 获取用于显示绘图的句柄(Handle to Device Context)
			/// </summary>
			/// <returns></returns>
		virtual IntPtr CreateHDC();

		/// <summary>
		/// 获取用于创建绘图的接口
		/// </summary>
		virtual property IOdaEditorUiProvider^ UIProvider{ virtual IOdaEditorUiProvider ^ get(); }

			/// <summary>
			/// 当前控件尺寸
			/// </summary>
		virtual System::Drawing::Size GetClientSize();
		/// <summary>
		/// 当前控件的矩形区域
		/// </summary>
		virtual System::Drawing::Rectangle GetClientRectangle();

		/// <summary>
		/// 当前控件的矩形区域转换为屏幕坐标
		/// </summary>
		/// <param name="r"></param>
		/// <returns></returns>
		virtual System::Drawing::Rectangle CalcRectangleToScreen(System::Drawing::Rectangle r);

		virtual void SetSnapCursor();
		/// <summary>
		/// 移动焦点到编辑器
		/// </summary>
		virtual void FocusEditor();

		/// <summary>
		/// 获取当前光标样式
		/// </summary>
		virtual Cursor^ GetCursor();

		/// <summary>
		/// 控件DoEvent
		/// </summary>
		virtual void DoEvent();

		/// <summary>
		/// 控件销毁事件
		/// </summary>
		virtual event EventHandler^ Disposed;

		/// <summary>
		/// 尺寸变化事件
		/// </summary>
		virtual event EventHandler^ SizeChanged;

		/// <summary>
		/// 控件绘制事件
		/// </summary>
		virtual event PaintEventHandler^ Paint;

		/// <summary>
		/// 控件刷新并强制重新绘制
		/// </summary>
		virtual void DoRefresh();

		virtual void Invalidate();


		//#region 绘图控件用户输入事件(鼠标& 键盘)

		/// <summary>
		/// 鼠标按下并抬起
		/// </summary>
		virtual event MouseEventHandler^ MouseClick;

		/// <summary>
		/// 鼠标双击
		/// </summary>
		virtual event MouseEventHandler^ MouseDoubleClick;

		/// <summary>
		/// 鼠标按下
		/// </summary>
		virtual event MouseEventHandler^ MouseDown;

		/// <summary>
		/// 鼠标在绘图区移动
		/// </summary>
		virtual event MouseEventHandler^ MouseMove;

		/// <summary>
		/// 鼠标按下抬起
		/// </summary>
		virtual event MouseEventHandler^ MouseUp;

		/// <summary>
		/// 鼠标滚轮
		/// </summary>
		virtual event MouseEventHandler^ MouseWheel;

		/// <summary>
		/// 鼠标从外部进入绘图区
		/// </summary>
		virtual event EventHandler^ MouseEnter;

		/// <summary>
		/// 鼠标悬停在此绘图区
		/// </summary>
		virtual event EventHandler^ MouseHover;

		/// <summary>
		/// 鼠标离开此绘图区
		/// </summary>
		virtual event EventHandler^ MouseLeave;

		/// <summary>
		/// 键盘按键按下
		/// </summary>
		virtual event KeyEventHandler^ KeyDown;

		/// <summary>
		/// 键盘按键抬起
		/// </summary>
		virtual event KeyEventHandler^ KeyUp;

		/// <summary>
		/// 键盘按键按下并抬起
		/// </summary>
		virtual event KeyPressEventHandler^ KeyPress;

		/// <summary>
		/// 开始显示进度条
		/// </summary>
		/// <param name="displayMessage">显示信息</param>
		virtual void StartProgress(System::String^ displayMessage);

		/// <summary>
		/// 更新进度
		/// </summary>
		/// <param name="progress">小于等于100，大于等于0.</param>
		virtual void ReportProgress(System::Int16 progress);

		/// <summary>
		/// 进度条完成，释放资源
		/// </summary>
		virtual void ReleaseProgress();
	};

	public ref class BoxParamCli
	{
	public:
		double Length;
		double Width;
		double Height;
	};

	public ref class CylinderParamCli
	{
	public:
		double Radius;
		double Height;
	};

	public ref class OdaViewer
	{
	public:
		void Init(IntPtr hwnd);
		void DrawBox(BoxParamCli^ param);
		void DrawCylinder(CylinderParamCli^ param);
		double GetHeight();
	};
}
