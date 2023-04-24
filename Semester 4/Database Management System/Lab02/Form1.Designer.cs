using System.Configuration;

namespace laboratory02
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.childTableView = new System.Windows.Forms.DataGridView();
            this.parentTableView = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.childTableView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentTableView)).BeginInit();
            this.SuspendLayout();
            // 
            // childTableView
            // 
            this.childTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childTableView.Location = new System.Drawing.Point(418, 52);
            this.childTableView.Name = "childTableView";
            this.childTableView.Size = new System.Drawing.Size(370, 315);
            this.childTableView.TabIndex = 0;
            this.childTableView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.childTableView_DataError);
            // 
            // parentTableView
            // 
            this.parentTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentTableView.Location = new System.Drawing.Point(12, 52);
            this.parentTableView.Name = "parentTableView";
            this.parentTableView.Size = new System.Drawing.Size(370, 315);
            this.parentTableView.TabIndex = 1;
            this.parentTableView.SelectionChanged += new System.EventHandler(this.parentTableView_SelectionChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(418, 399);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Update";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(160, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = ConfigurationManager.AppSettings["ParentTableName"].ToString(); 
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(588, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = ConfigurationManager.AppSettings["ChildTableName"].ToString();
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.parentTableView);
            this.Controls.Add(this.childTableView);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.childTableView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.parentTableView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView childTableView;
        private System.Windows.Forms.DataGridView parentTableView;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

