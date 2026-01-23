using System;
using System.Windows.Forms;

namespace BIMViewDemo
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            this.AutoScaleMode = AutoScaleMode.None;
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
                var result = OdaCliWrapper.SimpleDraw.CreateOrUpdateBox(length, width, height);
                if (result)
                {
                    MessageBox.Show("盒子创建成功", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
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

                var result = OdaCliWrapper.SimpleDraw.CreateOrUpdateCylinder(radius, height);
                if (result)
                {
                    MessageBox.Show("圆柱体创建成功", "成功", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
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
            try
            {
                bool ok = OdaCliWrapper.SimpleDraw.Initialize(this.viewPanel.Handle);
                if (!ok)
                {
                    MessageBox.Show("ODA 初始化失败", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"初始化失败: {ex.Message}", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
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
