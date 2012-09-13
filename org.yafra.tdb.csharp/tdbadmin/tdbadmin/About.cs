using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for About.
	/// </summary>
	public class About : System.Windows.Forms.Form
	{
		private System.Windows.Forms.LinkLabel linkLabel1;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Label Abt_l_title;
		private System.Windows.Forms.Label Abt_l_descr;
		private System.Windows.Forms.Button Abt_b_close;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public About()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			this.label3.Text = versioninfo.PSIDENT;
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.Abt_l_title = new System.Windows.Forms.Label();
			this.Abt_l_descr = new System.Windows.Forms.Label();
			this.linkLabel1 = new System.Windows.Forms.LinkLabel();
			this.label3 = new System.Windows.Forms.Label();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.Abt_b_close = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// Abt_l_title
			// 
			this.Abt_l_title.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.Abt_l_title.Location = new System.Drawing.Point(128, 16);
			this.Abt_l_title.Name = "Abt_l_title";
			this.Abt_l_title.Size = new System.Drawing.Size(120, 32);
			this.Abt_l_title.TabIndex = 0;
			this.Abt_l_title.Text = "travelDB";
			// 
			// Abt_l_descr
			// 
			this.Abt_l_descr.Location = new System.Drawing.Point(16, 96);
			this.Abt_l_descr.Name = "Abt_l_descr";
			this.Abt_l_descr.Size = new System.Drawing.Size(240, 72);
			this.Abt_l_descr.TabIndex = 1;
			this.Abt_l_descr.Text = "travelDB is an information and booking system for the touristic industry.\nCopyrig" +
				"ht by yafra.org, 2004, Switzerland.";
			// 
			// linkLabel1
			// 
			this.linkLabel1.Location = new System.Drawing.Point(16, 176);
			this.linkLabel1.Name = "linkLabel1";
			this.linkLabel1.Size = new System.Drawing.Size(240, 32);
			this.linkLabel1.TabIndex = 2;
			this.linkLabel1.TabStop = true;
			this.linkLabel1.Text = "Visit http://www.yafra.org/ for more information\'s";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(16, 232);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(240, 64);
			this.label3.TabIndex = 3;
			this.label3.Text = "Version: v01r00";
			// 
			// pictureBox1
			// 
			this.pictureBox1.Location = new System.Drawing.Point(16, 16);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size(80, 64);
			this.pictureBox1.TabIndex = 4;
			this.pictureBox1.TabStop = false;
			// 
			// Abt_b_close
			// 
			this.Abt_b_close.Location = new System.Drawing.Point(104, 312);
			this.Abt_b_close.Name = "Abt_b_close";
			this.Abt_b_close.TabIndex = 5;
			this.Abt_b_close.Text = "Close";
			this.Abt_b_close.Click += new System.EventHandler(this.Abt_b_close_Click);
			// 
			// About
			// 
			this.AcceptButton = this.Abt_b_close;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(292, 349);
			this.ControlBox = false;
			this.Controls.Add(this.Abt_b_close);
			this.Controls.Add(this.pictureBox1);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.linkLabel1);
			this.Controls.Add(this.Abt_l_descr);
			this.Controls.Add(this.Abt_l_title);
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "About";
			this.ShowInTaskbar = false;
			this.Text = "About";
			this.TopMost = true;
			this.ResumeLayout(false);

		}
		#endregion

		private void Abt_b_close_Click(object sender, System.EventArgs e)
		{
			this.Close();
		}

	}
}
