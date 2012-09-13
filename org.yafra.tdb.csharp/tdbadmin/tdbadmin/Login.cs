using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using org.swyn.foundation.db;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Login : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label log_l_dbn;
		private System.Windows.Forms.Label log_l_user;
		private System.Windows.Forms.TextBox log_e_dbn;
		private System.Windows.Forms.TextBox log_e_user;
		private System.Windows.Forms.Button log_b_ok;
		private System.Windows.Forms.Button log_b_cancel;
		private System.Windows.Forms.TextBox log_e_pwd;
		private System.Windows.Forms.Label log_l_pwd;
		private System.Windows.Forms.Label log_l_host;
		private System.Windows.Forms.Label log_l_dbtype;
		private System.Windows.Forms.TextBox log_e_host;
		private System.Windows.Forms.ComboBox log_c_dbtype;
		private System.Windows.Forms.ToolTip toolTip1;
		private System.ComponentModel.IContainer components;

		public Login()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}


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


		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.log_l_dbn = new System.Windows.Forms.Label();
			this.log_l_user = new System.Windows.Forms.Label();
			this.log_e_dbn = new System.Windows.Forms.TextBox();
			this.log_e_user = new System.Windows.Forms.TextBox();
			this.log_b_ok = new System.Windows.Forms.Button();
			this.log_b_cancel = new System.Windows.Forms.Button();
			this.log_e_pwd = new System.Windows.Forms.TextBox();
			this.log_l_pwd = new System.Windows.Forms.Label();
			this.log_l_host = new System.Windows.Forms.Label();
			this.log_l_dbtype = new System.Windows.Forms.Label();
			this.log_e_host = new System.Windows.Forms.TextBox();
			this.log_c_dbtype = new System.Windows.Forms.ComboBox();
			this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
			this.SuspendLayout();
			// 
			// log_l_dbn
			// 
			this.log_l_dbn.Location = new System.Drawing.Point(0, 0);
			this.log_l_dbn.Name = "log_l_dbn";
			this.log_l_dbn.TabIndex = 0;
			this.log_l_dbn.Text = "Database";
			this.toolTip1.SetToolTip(this.log_l_dbn, "Enter the database name, if you use Sql use your catalog name, if you use ODBC/Ol" +
				"eDB use your DSN name, if you use Oracle use your SID");
			// 
			// log_l_user
			// 
			this.log_l_user.Location = new System.Drawing.Point(0, 24);
			this.log_l_user.Name = "log_l_user";
			this.log_l_user.TabIndex = 1;
			this.log_l_user.Text = "User";
			this.toolTip1.SetToolTip(this.log_l_user, "Enter the database user");
			// 
			// log_e_dbn
			// 
			this.log_e_dbn.Location = new System.Drawing.Point(104, 0);
			this.log_e_dbn.Name = "log_e_dbn";
			this.log_e_dbn.Size = new System.Drawing.Size(184, 20);
			this.log_e_dbn.TabIndex = 1;
			this.log_e_dbn.Text = "traveldb";
			this.toolTip1.SetToolTip(this.log_e_dbn, "Default database called traveldb");
			// 
			// log_e_user
			// 
			this.log_e_user.Location = new System.Drawing.Point(104, 24);
			this.log_e_user.Name = "log_e_user";
			this.log_e_user.Size = new System.Drawing.Size(184, 20);
			this.log_e_user.TabIndex = 2;
			this.log_e_user.Text = "";
			// 
			// log_b_ok
			// 
			this.log_b_ok.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.log_b_ok.Location = new System.Drawing.Point(40, 144);
			this.log_b_ok.Name = "log_b_ok";
			this.log_b_ok.Size = new System.Drawing.Size(64, 24);
			this.log_b_ok.TabIndex = 6;
			this.log_b_ok.Text = "OK";
			this.log_b_ok.Click += new System.EventHandler(this.log_b_ok_Click);
			// 
			// log_b_cancel
			// 
			this.log_b_cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.log_b_cancel.Location = new System.Drawing.Point(184, 144);
			this.log_b_cancel.Name = "log_b_cancel";
			this.log_b_cancel.Size = new System.Drawing.Size(64, 24);
			this.log_b_cancel.TabIndex = 7;
			this.log_b_cancel.Text = "Cancel";
			this.log_b_cancel.Click += new System.EventHandler(this.log_b_cancel_Click);
			// 
			// log_e_pwd
			// 
			this.log_e_pwd.Location = new System.Drawing.Point(104, 48);
			this.log_e_pwd.Name = "log_e_pwd";
			this.log_e_pwd.PasswordChar = '*';
			this.log_e_pwd.Size = new System.Drawing.Size(184, 20);
			this.log_e_pwd.TabIndex = 3;
			this.log_e_pwd.Text = "";
			// 
			// log_l_pwd
			// 
			this.log_l_pwd.Location = new System.Drawing.Point(0, 48);
			this.log_l_pwd.Name = "log_l_pwd";
			this.log_l_pwd.TabIndex = 7;
			this.log_l_pwd.Text = "Password";
			// 
			// log_l_host
			// 
			this.log_l_host.Location = new System.Drawing.Point(0, 72);
			this.log_l_host.Name = "log_l_host";
			this.log_l_host.TabIndex = 8;
			this.log_l_host.Text = "Hostname";
			this.toolTip1.SetToolTip(this.log_l_host, "Enter the hostname of the database server");
			// 
			// log_l_dbtype
			// 
			this.log_l_dbtype.Location = new System.Drawing.Point(0, 96);
			this.log_l_dbtype.Name = "log_l_dbtype";
			this.log_l_dbtype.TabIndex = 9;
			this.log_l_dbtype.Text = "DB Type";
			this.toolTip1.SetToolTip(this.log_l_dbtype, "Choose your server database type");
			// 
			// log_e_host
			// 
			this.log_e_host.Location = new System.Drawing.Point(104, 72);
			this.log_e_host.Name = "log_e_host";
			this.log_e_host.Size = new System.Drawing.Size(184, 20);
			this.log_e_host.TabIndex = 4;
			this.log_e_host.Text = "";
			// 
			// log_c_dbtype
			// 
			this.log_c_dbtype.Items.AddRange(new object[] {
																			 "SqlServer",
																			 "Oracle",
																			 "MySQL",
																			 "Odbc",
																			 "OleDb"});
			this.log_c_dbtype.Location = new System.Drawing.Point(104, 96);
			this.log_c_dbtype.Name = "log_c_dbtype";
			this.log_c_dbtype.Size = new System.Drawing.Size(184, 21);
			this.log_c_dbtype.TabIndex = 5;
			this.log_c_dbtype.Text = "SqlServer";
			// 
			// Login
			// 
			this.AcceptButton = this.log_b_ok;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.log_b_cancel;
			this.ClientSize = new System.Drawing.Size(288, 197);
			this.Controls.Add(this.log_c_dbtype);
			this.Controls.Add(this.log_e_host);
			this.Controls.Add(this.log_e_pwd);
			this.Controls.Add(this.log_e_user);
			this.Controls.Add(this.log_e_dbn);
			this.Controls.Add(this.log_l_dbtype);
			this.Controls.Add(this.log_l_host);
			this.Controls.Add(this.log_l_pwd);
			this.Controls.Add(this.log_b_cancel);
			this.Controls.Add(this.log_b_ok);
			this.Controls.Add(this.log_l_user);
			this.Controls.Add(this.log_l_dbn);
			this.Name = "Login";
			this.Text = "TravelDB Login";
			this.ResumeLayout(false);

		}
		#endregion


		private void log_b_cancel_Click(object sender, System.EventArgs e)
		{
			// exit
			this.DialogResult = DialogResult.Cancel;
			Close();
		}

		private void log_b_ok_Click(object sender, System.EventArgs e)
		{
			// load and set profile and open database
			try
			{
				tdb.User prof = new tdb.User();
				prof.SetLogin(this.log_e_user.Text, this.log_e_pwd.Text, this.log_e_dbn.Text, this.log_c_dbtype.Text, this.log_e_host.Text);
				prof.LoadProfile(this.log_e_user.Text);
				this.DialogResult = DialogResult.OK;
			}
			catch (System.Data.SqlClient.SqlException)
			{
				this.DialogResult = DialogResult.Cancel;
				MessageBox.Show("travelDB error: Could not open the database");
			}
			Close();
		}
	}
}
