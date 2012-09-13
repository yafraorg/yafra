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
    public partial class FWcreateserv : WizardForm
    {
        private GUIoffer offer;

        public FWcreateserv()
        {
            InitializeComponent();
        }

        public void doPages()
        {
            FirstPage P1 = new FirstPage();
            P1.ObjOffer = offer;

            Controls.AddRange(new Control[] {
		        P1,
		        new SecondPage(),
		        new ThirdPage(),
		        new FourthPage()
		        });

        }

        public virtual GUIoffer ObjOffer { get { return offer; } set { offer = value; } }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SuspendLayout();
            // 
            // MyWizardForm
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(499, 362);
            this.Name = "MyWizardForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Create service offering";
            this.ResumeLayout(false);

        }
        #endregion

    }
}
