using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BIMViewDemo
{
    public partial class BimViewEditor : UserControl
    {
        public BimViewEditor()
        {
            InitializeComponent();

      // 由 ODA 直接在 HWND 上绘制，这里关闭背景重绘，减少闪烁
      this.SetStyle(ControlStyles.AllPaintingInWmPaint |
                    ControlStyles.UserPaint |
                    ControlStyles.Opaque, true);
        }

    protected override void OnPaint(PaintEventArgs e)
    {
      base.OnPaint(e);

      // 让 ODA 负责实际绘制
      try
      {
        OdaCliWrapper.SimpleDraw.Redraw();
      }
      catch
      {
        // 忽略绘制异常，避免影响 WinForms 消息循环
      }
    }

    protected override void OnResize(EventArgs e)
    {
      base.OnResize(e);

      // 尺寸变化时也请求一次重绘，保证视口跟随大小
      try
      {
        OdaCliWrapper.SimpleDraw.Redraw();
      }
      catch
      {
      }
    }

    protected override void OnPaintBackground(PaintEventArgs pevent)
    {
      // 不绘制背景，避免在 ODA 绘制前被擦成白色
      // base.OnPaintBackground(pevent);
    }
    }
}
