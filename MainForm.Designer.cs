namespace BIMViewDemo
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.btnOpenDwg = new System.Windows.Forms.Button();
            this.labelLength = new System.Windows.Forms.Label();
            this.labelWidth = new System.Windows.Forms.Label();
            this.labelHeight = new System.Windows.Forms.Label();
            this.textLength = new System.Windows.Forms.TextBox();
            this.textWidth = new System.Windows.Forms.TextBox();
            this.textHeight = new System.Windows.Forms.TextBox();
            this.btnCreateBox = new System.Windows.Forms.Button();
            this.labelSeparator = new System.Windows.Forms.Label();
            this.labelCylinderRadius = new System.Windows.Forms.Label();
            this.labelCylinderHeight = new System.Windows.Forms.Label();
            this.textCylinderRadius = new System.Windows.Forms.TextBox();
            this.textCylinderHeight = new System.Windows.Forms.TextBox();
            this.btnCreateCylinder = new System.Windows.Forms.Button();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.bimViewEditor = new BIMViewDemo.BimViewEditor();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 60F));
            this.tableLayoutPanel1.Controls.Add(this.btnOpenDwg, 0, 8);
            this.tableLayoutPanel1.Controls.Add(this.labelLength, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.labelWidth, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.labelHeight, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.textLength, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.textWidth, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.textHeight, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.btnCreateBox, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.labelSeparator, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.labelCylinderRadius, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.labelCylinderHeight, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.textCylinderRadius, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.textCylinderHeight, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.btnCreateCylinder, 0, 7);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(4, 4);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.Padding = new System.Windows.Forms.Padding(5);
            this.tableLayoutPanel1.RowCount = 10;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(294, 724);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // btnOpenDwg
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.btnOpenDwg, 2);
            this.btnOpenDwg.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnOpenDwg.Location = new System.Drawing.Point(8, 248);
            this.btnOpenDwg.Name = "btnOpenDwg";
            this.btnOpenDwg.Size = new System.Drawing.Size(278, 24);
            this.btnOpenDwg.TabIndex = 2;
            this.btnOpenDwg.Text = "打开 DWG";
            this.btnOpenDwg.UseVisualStyleBackColor = true;
            this.btnOpenDwg.Click += new System.EventHandler(this.btnOpenDwg_Click);
            // 
            // labelLength
            // 
            this.labelLength.AutoSize = true;
            this.labelLength.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelLength.Location = new System.Drawing.Point(8, 8);
            this.labelLength.Margin = new System.Windows.Forms.Padding(3);
            this.labelLength.Name = "labelLength";
            this.labelLength.Padding = new System.Windows.Forms.Padding(3);
            this.labelLength.Size = new System.Drawing.Size(107, 24);
            this.labelLength.TabIndex = 0;
            this.labelLength.Text = "长度";
            this.labelLength.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // labelWidth
            // 
            this.labelWidth.AutoSize = true;
            this.labelWidth.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelWidth.Location = new System.Drawing.Point(8, 38);
            this.labelWidth.Margin = new System.Windows.Forms.Padding(3);
            this.labelWidth.Name = "labelWidth";
            this.labelWidth.Padding = new System.Windows.Forms.Padding(3);
            this.labelWidth.Size = new System.Drawing.Size(107, 24);
            this.labelWidth.TabIndex = 1;
            this.labelWidth.Text = "宽度";
            this.labelWidth.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // labelHeight
            // 
            this.labelHeight.AutoSize = true;
            this.labelHeight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelHeight.Location = new System.Drawing.Point(8, 68);
            this.labelHeight.Margin = new System.Windows.Forms.Padding(3);
            this.labelHeight.Name = "labelHeight";
            this.labelHeight.Padding = new System.Windows.Forms.Padding(3);
            this.labelHeight.Size = new System.Drawing.Size(107, 24);
            this.labelHeight.TabIndex = 2;
            this.labelHeight.Text = "高度";
            this.labelHeight.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // textLength
            // 
            this.textLength.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textLength.Location = new System.Drawing.Point(121, 8);
            this.textLength.Name = "textLength";
            this.textLength.Size = new System.Drawing.Size(165, 21);
            this.textLength.TabIndex = 3;
            this.textLength.Text = "100";
            // 
            // textWidth
            // 
            this.textWidth.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textWidth.Location = new System.Drawing.Point(121, 38);
            this.textWidth.Name = "textWidth";
            this.textWidth.Size = new System.Drawing.Size(165, 21);
            this.textWidth.TabIndex = 4;
            this.textWidth.Text = "25";
            // 
            // textHeight
            // 
            this.textHeight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textHeight.Location = new System.Drawing.Point(121, 68);
            this.textHeight.Name = "textHeight";
            this.textHeight.Size = new System.Drawing.Size(165, 21);
            this.textHeight.TabIndex = 5;
            this.textHeight.Text = "30";
            // 
            // btnCreateBox
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.btnCreateBox, 2);
            this.btnCreateBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnCreateBox.Location = new System.Drawing.Point(8, 98);
            this.btnCreateBox.Name = "btnCreateBox";
            this.btnCreateBox.Size = new System.Drawing.Size(278, 29);
            this.btnCreateBox.TabIndex = 6;
            this.btnCreateBox.Text = "创建盒子";
            this.btnCreateBox.UseVisualStyleBackColor = true;
            this.btnCreateBox.Click += new System.EventHandler(this.btnCreateBox_Click);
            // 
            // labelSeparator
            // 
            this.labelSeparator.AutoSize = true;
            this.tableLayoutPanel1.SetColumnSpan(this.labelSeparator, 2);
            this.labelSeparator.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelSeparator.Location = new System.Drawing.Point(8, 133);
            this.labelSeparator.Margin = new System.Windows.Forms.Padding(3);
            this.labelSeparator.Name = "labelSeparator";
            this.labelSeparator.Size = new System.Drawing.Size(278, 14);
            this.labelSeparator.TabIndex = 7;
            this.labelSeparator.Text = "─────────────────────────";
            this.labelSeparator.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // labelCylinderRadius
            // 
            this.labelCylinderRadius.AutoSize = true;
            this.labelCylinderRadius.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelCylinderRadius.Location = new System.Drawing.Point(8, 153);
            this.labelCylinderRadius.Margin = new System.Windows.Forms.Padding(3);
            this.labelCylinderRadius.Name = "labelCylinderRadius";
            this.labelCylinderRadius.Padding = new System.Windows.Forms.Padding(3);
            this.labelCylinderRadius.Size = new System.Drawing.Size(107, 24);
            this.labelCylinderRadius.TabIndex = 8;
            this.labelCylinderRadius.Text = "圆柱体半径";
            this.labelCylinderRadius.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // labelCylinderHeight
            // 
            this.labelCylinderHeight.AutoSize = true;
            this.labelCylinderHeight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.labelCylinderHeight.Location = new System.Drawing.Point(8, 183);
            this.labelCylinderHeight.Margin = new System.Windows.Forms.Padding(3);
            this.labelCylinderHeight.Name = "labelCylinderHeight";
            this.labelCylinderHeight.Padding = new System.Windows.Forms.Padding(3);
            this.labelCylinderHeight.Size = new System.Drawing.Size(107, 24);
            this.labelCylinderHeight.TabIndex = 9;
            this.labelCylinderHeight.Text = "圆柱体高度";
            this.labelCylinderHeight.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // textCylinderRadius
            // 
            this.textCylinderRadius.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textCylinderRadius.Location = new System.Drawing.Point(121, 153);
            this.textCylinderRadius.Name = "textCylinderRadius";
            this.textCylinderRadius.Size = new System.Drawing.Size(165, 21);
            this.textCylinderRadius.TabIndex = 10;
            this.textCylinderRadius.Text = "50";
            // 
            // textCylinderHeight
            // 
            this.textCylinderHeight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textCylinderHeight.Location = new System.Drawing.Point(121, 183);
            this.textCylinderHeight.Name = "textCylinderHeight";
            this.textCylinderHeight.Size = new System.Drawing.Size(165, 21);
            this.textCylinderHeight.TabIndex = 11;
            this.textCylinderHeight.Text = "100";
            // 
            // btnCreateCylinder
            // 
            this.tableLayoutPanel1.SetColumnSpan(this.btnCreateCylinder, 2);
            this.btnCreateCylinder.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnCreateCylinder.Location = new System.Drawing.Point(8, 213);
            this.btnCreateCylinder.Name = "btnCreateCylinder";
            this.btnCreateCylinder.Size = new System.Drawing.Size(278, 29);
            this.btnCreateCylinder.TabIndex = 12;
            this.btnCreateCylinder.Text = "创建圆柱体";
            this.btnCreateCylinder.UseVisualStyleBackColor = true;
            this.btnCreateCylinder.Click += new System.EventHandler(this.btnCreateCylinder_Click);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 300F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.bimViewEditor, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(1192, 732);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // bimViewEditor
            // 
            this.bimViewEditor.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bimViewEditor.Location = new System.Drawing.Point(305, 4);
            this.bimViewEditor.Name = "bimViewEditor";
            this.bimViewEditor.Size = new System.Drawing.Size(883, 724);
            this.bimViewEditor.TabIndex = 1;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1192, 732);
            this.Controls.Add(this.tableLayoutPanel2);
            this.Name = "MainForm";
            this.Text = "参数建模示例";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label labelLength;
        private System.Windows.Forms.Label labelWidth;
        private System.Windows.Forms.Label labelHeight;
        private System.Windows.Forms.TextBox textLength;
        private System.Windows.Forms.TextBox textWidth;
        private System.Windows.Forms.TextBox textHeight;
        private System.Windows.Forms.Button btnCreateBox;
        private System.Windows.Forms.Label labelSeparator;
        private System.Windows.Forms.Label labelCylinderRadius;
        private System.Windows.Forms.Label labelCylinderHeight;
        private System.Windows.Forms.TextBox textCylinderRadius;
        private System.Windows.Forms.TextBox textCylinderHeight;
        private System.Windows.Forms.Button btnCreateCylinder;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnOpenDwg;
        private BimViewEditor bimViewEditor;
    }
}
