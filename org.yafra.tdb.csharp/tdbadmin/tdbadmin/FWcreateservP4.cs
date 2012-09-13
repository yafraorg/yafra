using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using org.swyn.foundation.gui;

namespace tdbadmin
{
    public class FourthPage : ExteriorWizardPage
    {
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Label label3;
        private System.ComponentModel.IContainer components = null;

        public FourthPage()
        {
            // This call is required by the Windows Form Designer.
            InitializeComponent();

            // TODO: Add any initialization after the InitializeComponent call
        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (components != null)
                {
                    components.Dispose();
                }
            }
            base.Dispose(disposing);
        }

        #region Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // m_titleLabel
            // 
            this.m_titleLabel.Text = "Almost Finished with the Sample Setup Wizard";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(170, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(292, 26);
            this.label1.TabIndex = 2;
            this.label1.Text = "Back to Wizard 97 style.  The final page also extends ExteriorWizardPage but with" +
                "out a watermark image.";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(170, 104);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(292, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Click the checkbox below to enable the Finish button.";
            // 
            // checkBox1
            // 
            this.checkBox1.Location = new System.Drawing.Point(199, 126);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.TabIndex = 4;
            this.checkBox1.Text = "&Enable Finish";
            this.checkBox1.Click += new System.EventHandler(this.checkBox1_Click);
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(170, 274);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(292, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "Click Finish to close this wizard.";
            // 
            // FourthPage
            // 
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.label3,
                                                                          this.checkBox1,
                                                                          this.label2,
                                                                          this.m_watermarkPicture,
                                                                          this.m_titleLabel,
                                                                          this.label1});
            this.Name = "FourthPage";
            this.ResumeLayout(false);

        }
        #endregion

        protected override bool OnSetActive()
        {
            if (!base.OnSetActive())
                return false;

            // Enable both the Back and Finish (enabled/disabled) buttons on this page    
            Wizard.SetWizardButtons(WizardButton.Back |
                (checkBox1.Checked ? WizardButton.Finish : WizardButton.DisabledFinish));
            return true;
        }

        private void checkBox1_Click(object sender, System.EventArgs e)
        {
            // Enable both the Back and Finish (enabled/disabled) buttons on this page    
            Wizard.SetWizardButtons(WizardButton.Back |
                (checkBox1.Checked ? WizardButton.Finish : WizardButton.DisabledFinish));
        }
    }
}
