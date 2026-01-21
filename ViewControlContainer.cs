using DevExpress.Utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BIMManager
{
    public partial class ViewControlContainer : UserControl
    {
        private readonly ViewControl _drawingControl;
        private OdaCliWrapper _odaCliWrapper;
        private bool _isSelecting = false;

        public event MouseEventHandler OnDrawingControlMouseDown;

        public event EventHandler BeforeDisposed;

        private Action<List<int>> AfterSelected;

        public ViewControlContainer()
        {
            InitializeComponent();

            this.SuspendLayout();
            _drawingControl = new ViewControl();

            _drawingControl.Dock = DockStyle.Fill;

            tablePanel1.Controls.Add(_drawingControl);
            tablePanel1.SetColumn(_drawingControl, 0);
            tablePanel1.SetRow(_drawingControl, 0);
            this.ResumeLayout(false);
        }

        public void RunInUIThread(RunAction action, int id)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action(() =>
                {
                    action(id);
                }));
            }
            else
            {
                action(id);
            }
        }
    }
}
