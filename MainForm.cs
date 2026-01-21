using System;
using System.Windows.Forms;
using OdaCliWrapper;

namespace BIMManager
{
    public partial class MainForm : Form
    {
        private OdaViewer _viewer = new OdaViewer();

        public MainForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 创建盒子
        /// </summary>
        private void CreateBox()
        {
            try
            {
                double length = double.Parse(textLength.Text);
                double width = double.Parse(textWidth.Text);
                double height = double.Parse(textHeight.Text);

                if (length <= 0 || width <= 0 || height <= 0)
                {
                    MessageBox.Show("长度、宽度和高度必须大于0", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                var param = new BoxParamCli
                {
                    Length = length,
                    Width = width,
                    Height = height
                };

                _viewer.DrawBox(param);
                MessageBox.Show("盒子创建成功", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (FormatException)
            {
                MessageBox.Show("请输入有效的数值", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"创建失败: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// 创建圆柱体
        /// </summary>
        private void CreateCylinder()
        {
            try
            {
                double radius = double.Parse(textCylinderRadius.Text);
                double height = double.Parse(textCylinderHeight.Text);

                if (radius <= 0 || height <= 0)
                {
                    MessageBox.Show("圆柱体半径和高度必须大于0", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                var param = new CylinderParamCli
                {
                    Radius = radius,
                    Height = height
                };

                _viewer.DrawCylinder(param);
                MessageBox.Show("圆柱体创建成功", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (FormatException)
            {
                MessageBox.Show("请输入有效的数值", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"创建失败: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            _viewer.Init(viewPanel.Handle);
        }

        private void btnCreateBox_Click(object sender, EventArgs e)
        {
            CreateBox();
        }

        private void btnCreateCylinder_Click(object sender, EventArgs e)
        {
            CreateCylinder();
        }
    }
}
