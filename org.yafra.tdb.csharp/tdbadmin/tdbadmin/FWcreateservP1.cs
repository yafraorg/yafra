using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using org.swyn.foundation.gui;
using tdbgui;

namespace tdbadmin
{
	public class FirstPage : ExteriorWizardPage
	{
        private GUIoffer offer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private Label label3;
        private Label SO_wp1_off;
		private System.ComponentModel.IContainer components = null;

		public FirstPage()
		{
			// This call is required by the Windows Form Designer.
			InitializeComponent();

			// TODO: Add any initialization after the InitializeComponent call
		}

        public virtual GUIoffer ObjOffer { get { return offer; } set { offer = value; } }

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
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
            this.label3 = new System.Windows.Forms.Label();
            this.SO_wp1_off = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.m_watermarkPicture)).BeginInit();
            this.SuspendLayout();
            // 
            // m_titleLabel
            // 
            this.m_titleLabel.Text = "Service creation wizard";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(170, 65);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(292, 39);
            this.label1.TabIndex = 2;
            this.label1.Text = "This wizard will guide you through the service creation based on your selected of" +
                "fer";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(170, 274);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(292, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "Click Next to continue.";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(170, 150);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(76, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Selected offer:";
            // 
            // SO_wp1_off
            // 
            this.SO_wp1_off.AutoSize = true;
            this.SO_wp1_off.Location = new System.Drawing.Point(252, 150);
            this.SO_wp1_off.Name = "SO_wp1_off";
            this.SO_wp1_off.Size = new System.Drawing.Size(0, 13);
            this.SO_wp1_off.TabIndex = 5;
            // 
            // FirstPage
            // 
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SO_wp1_off);
            this.Controls.Add(this.label3);
            this.Name = "FirstPage";
            this.Controls.SetChildIndex(this.label3, 0);
            this.Controls.SetChildIndex(this.SO_wp1_off, 0);
            this.Controls.SetChildIndex(this.label1, 0);
            this.Controls.SetChildIndex(this.label2, 0);
            this.Controls.SetChildIndex(this.m_titleLabel, 0);
            this.Controls.SetChildIndex(this.m_watermarkPicture, 0);
            ((System.ComponentModel.ISupportInitialize)(this.m_watermarkPicture)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }
		#endregion

        protected override bool OnSetActive()
        {
            this.SO_wp1_off.Text = offer.ObjBez;

            if( !base.OnSetActive() )
                return false;
            
            // Enable only the Next button on the this page    
            Wizard.SetWizardButtons( WizardButton.Next );
            return true;
        }
    }
}