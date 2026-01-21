using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BIMManager
{
    internal class ViewControl : UserControl
    {
        [DllImport("user32.dll", EntryPoint = "GetDC", CharSet = CharSet.Auto)]
        private static extern IntPtr IntGetDC(IntPtr hWnd);

        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // ViewEditorControl
            // 
            this.Name = "ViewEditorControl";
            this.ResumeLayout(false);
        }

        protected override void Dispose(bool disposing)
        {
            base.Dispose(disposing);
        }

        public IntPtr CreateHDC()
        {
            if (this.IsDisposed || this.Handle == IntPtr.Zero)
            {
                throw new InvalidOperationException("控件未初始化或已经销毁.");
            }

            return IntGetDC(this.Handle);
        }
    }
}
