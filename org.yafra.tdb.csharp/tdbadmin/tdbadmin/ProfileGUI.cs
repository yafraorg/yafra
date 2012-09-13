using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using tdb.DS;
using org.swyn.foundation.utils;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for DataForm1.
	/// </summary>
	public class GUIuser : System.Windows.Forms.Form
	{
		private ProfileDS objProfileDS;
		private System.Windows.Forms.Button btnLoad;
		private System.Windows.Forms.Button btnUpdate;
		private System.Windows.Forms.Button btnCancelAll;
		public System.Windows.Forms.DataGrid grdmp_profil;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public GUIuser()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
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
			this.objProfileDS = new tdb.DS.ProfileDS();
			this.btnLoad = new System.Windows.Forms.Button();
			this.btnUpdate = new System.Windows.Forms.Button();
			this.btnCancelAll = new System.Windows.Forms.Button();
			this.grdmp_profil = new System.Windows.Forms.DataGrid();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			((System.ComponentModel.ISupportInitialize)(this.objProfileDS)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.grdmp_profil)).BeginInit();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// objProfileDS
			// 
			this.objProfileDS.DataSetName = "ProfileDS";
			this.objProfileDS.Locale = new System.Globalization.CultureInfo("en-US");
			// 
			// btnLoad
			// 
			this.btnLoad.Location = new System.Drawing.Point(8, 16);
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.TabIndex = 0;
			this.btnLoad.Text = "&Load";
			this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
			// 
			// btnUpdate
			// 
			this.btnUpdate.Location = new System.Drawing.Point(112, 16);
			this.btnUpdate.Name = "btnUpdate";
			this.btnUpdate.TabIndex = 1;
			this.btnUpdate.Text = "&Update";
			this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
			// 
			// btnCancelAll
			// 
			this.btnCancelAll.Location = new System.Drawing.Point(224, 16);
			this.btnCancelAll.Name = "btnCancelAll";
			this.btnCancelAll.TabIndex = 2;
			this.btnCancelAll.Text = "Ca&ncel All";
			this.btnCancelAll.Click += new System.EventHandler(this.btnCancelAll_Click);
			// 
			// grdmp_profil
			// 
			this.grdmp_profil.AlternatingBackColor = System.Drawing.Color.LightGray;
			this.grdmp_profil.BackColor = System.Drawing.Color.Gainsboro;
			this.grdmp_profil.BackgroundColor = System.Drawing.Color.Silver;
			this.grdmp_profil.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.grdmp_profil.CaptionBackColor = System.Drawing.Color.LightSteelBlue;
			this.grdmp_profil.CaptionFont = new System.Drawing.Font("Microsoft Sans Serif", 8F);
			this.grdmp_profil.CaptionForeColor = System.Drawing.Color.MidnightBlue;
			this.grdmp_profil.DataMember = "mp_profil";
			this.grdmp_profil.DataSource = this.objProfileDS;
			this.grdmp_profil.Dock = System.Windows.Forms.DockStyle.Fill;
			this.grdmp_profil.FlatMode = true;
			this.grdmp_profil.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F);
			this.grdmp_profil.ForeColor = System.Drawing.Color.Black;
			this.grdmp_profil.GridLineColor = System.Drawing.Color.DimGray;
			this.grdmp_profil.GridLineStyle = System.Windows.Forms.DataGridLineStyle.None;
			this.grdmp_profil.HeaderBackColor = System.Drawing.Color.MidnightBlue;
			this.grdmp_profil.HeaderFont = new System.Drawing.Font("Microsoft Sans Serif", 8F);
			this.grdmp_profil.HeaderForeColor = System.Drawing.Color.White;
			this.grdmp_profil.LinkColor = System.Drawing.Color.MidnightBlue;
			this.grdmp_profil.Location = new System.Drawing.Point(3, 16);
			this.grdmp_profil.Name = "grdmp_profil";
			this.grdmp_profil.ParentRowsBackColor = System.Drawing.Color.DarkGray;
			this.grdmp_profil.ParentRowsForeColor = System.Drawing.Color.Black;
			this.grdmp_profil.SelectionBackColor = System.Drawing.Color.CadetBlue;
			this.grdmp_profil.SelectionForeColor = System.Drawing.Color.White;
			this.grdmp_profil.Size = new System.Drawing.Size(402, 162);
			this.grdmp_profil.TabIndex = 3;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.btnLoad);
			this.groupBox1.Controls.Add(this.btnUpdate);
			this.groupBox1.Controls.Add(this.btnCancelAll);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBox1.Location = new System.Drawing.Point(0, 181);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(408, 48);
			this.groupBox1.TabIndex = 4;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Actions";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.grdmp_profil);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox2.Location = new System.Drawing.Point(0, 0);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(408, 181);
			this.groupBox2.TabIndex = 5;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "User profiles";
			// 
			// GUIuser
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.AutoScroll = true;
			this.ClientSize = new System.Drawing.Size(408, 229);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Name = "GUIuser";
			this.Text = "User Profile";
			((System.ComponentModel.ISupportInitialize)(this.objProfileDS)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.grdmp_profil)).EndInit();
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private void btnCancelAll_Click(object sender, System.EventArgs e)
		{
			this.objProfileDS.RejectChanges();
		}

		private void btnLoad_Click(object sender, System.EventArgs e)
		{
			string sql;
			org.swyn.foundation.utils.DBtools db = new DBtools(tdb.User.Uhelper, tdb.User.Udbcon);
			this.objProfileDS.Clear();
			sql = String.Format("Select * from tdbadmin.mp_profil");
			db.FillDS(this.objProfileDS, sql, new string[] { "mp_profil" });
		}

		private void btnUpdate_Click(object sender, System.EventArgs e)
		{
			org.swyn.foundation.utils.DBtools db = new DBtools(tdb.User.Uhelper, tdb.User.Udbcon);
			db.UpdDS(this.objProfileDS, "tdbadmin.tdb_insprof",
				new string[] { "MPID", "MPUSER", "BCHST", "SECLEVEL", "S_ID", "LAND_ID", "DLTT_ID", "DLT_ID", "KAT_ID", "DLAT_ID", "DLNT_ID", "SAI_ID", "PRG_ID", "A_ZEIT", "E_ZEIT", "P_RANGE" },
				"tdbadmin.tdb_updprof",
				new string[] { "MPID", "MPUSER", "BCHST", "SECLEVEL", "S_ID", "LAND_ID", "DLTT_ID", "DLT_ID", "KAT_ID", "DLAT_ID", "DLNT_ID", "SAI_ID", "PRG_ID", "A_ZEIT", "E_ZEIT", "P_RANGE" },
				"tdbadmin.tdb_delprof",
				new string[] {"MPID"}, "mp_profil");
//			IDbCommand inscmd = tdb.User.Uhelper.CreateCommand(dbc, "tdbadmin.tdb_insprof",
//				"MPID", "MPUSER", "BCHST", "SECLEVEL", "S_ID", "LAND_ID", "DLTT_ID", "DLT_ID", "KAT_ID", "DLAT_ID", "DLNT_ID", "SAI_ID", "PRG_ID", "A_ZEIT", "E_ZEIT", "P_RANGE");
//			IDbCommand updcmd = tdb.User.Uhelper.CreateCommand(dbc, "tdbadmin.tdb_updprof", 
//				"MPID", "MPUSER", "BCHST", "SECLEVEL", "S_ID", "LAND_ID", "DLTT_ID", "DLT_ID", "KAT_ID", "DLAT_ID", "DLNT_ID", "SAI_ID", "PRG_ID", "A_ZEIT", "E_ZEIT", "P_RANGE");
//			IDbCommand delcmd = tdb.User.Uhelper.CreateCommand(dbc, "tdbadmin.tdb_delprof", "MPID");
//			tdb.User.Uhelper.UpdateDataset(inscmd, delcmd, updcmd, this.objProfileDS, "mp_profil");
		}

	}
}
