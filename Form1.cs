using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using Newtonsoft.Json;

namespace BIMManager
{

    public partial class MainForm : Form
    {
        private string creoPath = @"C:\\Program Files\\PTC\\Creo 10.0\\Parametric\\bin\\creo.exe";
        private IntPtr wrapperPtr = IntPtr.Zero;

        [DllImport("CreoWrapper.dll")]
        private static extern IntPtr Wrapper_New();

        [DllImport("CreoWrapper.dll")]
        private static extern void Wrapper_Delete(IntPtr w);

        [DllImport("CreoWrapper.dll")]
        private static extern bool InitCreo(IntPtr w, [MarshalAs(UnmanagedType.LPWStr)] string path);

        [DllImport("CreoWrapper.dll")]
        private static extern void CloseCreo(IntPtr w);

        [DllImport("CreoWrapper.dll")]
        private static extern bool CreatePart(IntPtr w, ref PartParams p);

        [DllImport("CreoWrapper.dll")]
        private static extern bool CreatePartFromJson(IntPtr w, [MarshalAs(UnmanagedType.LPWStr)] string json);

        public MainForm()
        {
            InitializeComponent();
            wrapperPtr = Wrapper_New();
        }

        private void TestAddPart()
        {
            // TODO: 从实际的UI控件获取值，这里使用示例值
            var p = new PartParams
            {
                Length = 100.0,
                Width = 50.0,
                Height = 30.0,
                DraftAngle = 5.0,
                FilletRadius = 2.0
            };

            // 方法1: 直接使用结构体
            bool partResult = CreatePart(wrapperPtr, ref p);

            // 方法2: 使用JSON
            var partData = new CreoData
            {
                Length = p.Length,
                Width = p.Width,
                Height = p.Height,
                DraftAngle = p.DraftAngle,
                FilletRadius = p.FilletRadius
            };
            string json = JsonConvert.SerializeObject(partData);
            bool jsonResult = CreatePartFromJson(wrapperPtr, json);

            MessageBox.Show(partResult && jsonResult ? "模型生成成功" : "生成失败");
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            bool ret = InitCreo(wrapperPtr, creoPath);
            if (!ret)
                MessageBox.Show("Creo 启动失败！");
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            CloseCreo(wrapperPtr);
            if (wrapperPtr != IntPtr.Zero)
            {
                Wrapper_Delete(wrapperPtr);
                wrapperPtr = IntPtr.Zero;
            }
        }
    }
}
