namespace BIMManager
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
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textLength = new DevExpress.XtraEditors.TextEdit();
            this.textWidth = new DevExpress.XtraEditors.TextEdit();
            this.textHeight = new DevExpress.XtraEditors.TextEdit();
            this.textDraftAngle = new DevExpress.XtraEditors.TextEdit();
            this.textFilletRadius = new DevExpress.XtraEditors.TextEdit();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.textLength.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textWidth.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textHeight.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textDraftAngle.Properties)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.textFilletRadius.Properties)).BeginInit();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.textFilletRadius, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.textDraftAngle, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.textHeight, 1, 2);
            this.tableLayoutPanel1.Controls.Add(this.textWidth, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.label2, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.label3, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.label4, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.label5, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.button1, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.button2, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.textLength, 1, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(45, 49);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 6;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.Size = new System.Drawing.Size(452, 193);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Location = new System.Drawing.Point(3, 3);
            this.label1.Margin = new System.Windows.Forms.Padding(3);
            this.label1.Name = "label1";
            this.label1.Padding = new System.Windows.Forms.Padding(3);
            this.label1.Size = new System.Drawing.Size(220, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "长度";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Location = new System.Drawing.Point(3, 33);
            this.label2.Margin = new System.Windows.Forms.Padding(3);
            this.label2.Name = "label2";
            this.label2.Padding = new System.Windows.Forms.Padding(3);
            this.label2.Size = new System.Drawing.Size(220, 24);
            this.label2.TabIndex = 1;
            this.label2.Text = "宽度";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Location = new System.Drawing.Point(3, 63);
            this.label3.Margin = new System.Windows.Forms.Padding(3);
            this.label3.Name = "label3";
            this.label3.Padding = new System.Windows.Forms.Padding(3);
            this.label3.Size = new System.Drawing.Size(220, 24);
            this.label3.TabIndex = 2;
            this.label3.Text = "高度";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Location = new System.Drawing.Point(3, 93);
            this.label4.Margin = new System.Windows.Forms.Padding(3);
            this.label4.Name = "label4";
            this.label4.Padding = new System.Windows.Forms.Padding(3);
            this.label4.Size = new System.Drawing.Size(220, 24);
            this.label4.TabIndex = 3;
            this.label4.Text = "角度";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Location = new System.Drawing.Point(3, 123);
            this.label5.Margin = new System.Windows.Forms.Padding(3);
            this.label5.Name = "label5";
            this.label5.Padding = new System.Windows.Forms.Padding(3);
            this.label5.Size = new System.Drawing.Size(220, 24);
            this.label5.TabIndex = 4;
            this.label5.Text = "半径";
            // 
            // button1
            // 
            this.button1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button1.Location = new System.Drawing.Point(3, 153);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(220, 37);
            this.button1.TabIndex = 5;
            this.button1.Text = "测试参数";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.button2.Location = new System.Drawing.Point(229, 153);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(220, 37);
            this.button2.TabIndex = 6;
            this.button2.Text = "测试json";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textLength
            // 
            this.textLength.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textLength.EditValue = "100";
            this.textLength.Location = new System.Drawing.Point(229, 3);
            this.textLength.Name = "textLength";
            this.textLength.Size = new System.Drawing.Size(220, 20);
            this.textLength.TabIndex = 7;
            // 
            // textWidth
            // 
            this.textWidth.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textWidth.EditValue = "25";
            this.textWidth.Location = new System.Drawing.Point(229, 33);
            this.textWidth.Name = "textWidth";
            this.textWidth.Size = new System.Drawing.Size(220, 20);
            this.textWidth.TabIndex = 8;
            this.textWidth.Tag = "";
            // 
            // textHeight
            // 
            this.textHeight.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textHeight.EditValue = "30";
            this.textHeight.Location = new System.Drawing.Point(229, 63);
            this.textHeight.Name = "textHeight";
            this.textHeight.Size = new System.Drawing.Size(220, 20);
            this.textHeight.TabIndex = 9;
            // 
            // textDraftAngle
            // 
            this.textDraftAngle.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textDraftAngle.EditValue = "30";
            this.textDraftAngle.Location = new System.Drawing.Point(229, 93);
            this.textDraftAngle.Name = "textDraftAngle";
            this.textDraftAngle.Size = new System.Drawing.Size(220, 20);
            this.textDraftAngle.TabIndex = 10;
            // 
            // textFilletRadius
            // 
            this.textFilletRadius.Dock = System.Windows.Forms.DockStyle.Fill;
            this.textFilletRadius.EditValue = "50";
            this.textFilletRadius.Location = new System.Drawing.Point(229, 123);
            this.textFilletRadius.Name = "textFilletRadius";
            this.textFilletRadius.Size = new System.Drawing.Size(220, 20);
            this.textFilletRadius.TabIndex = 11;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(648, 404);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "MainForm";
            this.Text = "参数建模Demo";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.textLength.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textWidth.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textHeight.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textDraftAngle.Properties)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.textFilletRadius.Properties)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private DevExpress.XtraEditors.TextEdit textLength;
        private DevExpress.XtraEditors.TextEdit textFilletRadius;
        private DevExpress.XtraEditors.TextEdit textDraftAngle;
        private DevExpress.XtraEditors.TextEdit textHeight;
        private DevExpress.XtraEditors.TextEdit textWidth;
    }
}

