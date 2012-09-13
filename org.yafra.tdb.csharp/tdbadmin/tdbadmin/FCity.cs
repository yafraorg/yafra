using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using org.swyn.foundation.utils;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for Country.
	/// </summary>
	public class FCity : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox TDB_abgrp;
		private System.Windows.Forms.Button TDB_ab_clr;
		private System.Windows.Forms.Button TDB_ab_sel;
		private System.Windows.Forms.Button TDB_ab_exit;
		private System.Windows.Forms.Button TDB_ab_del;
		private System.Windows.Forms.Button TDB_ab_upd;
		private System.Windows.Forms.Button TDB_ab_ins;
		private System.Windows.Forms.Label tdb_e_id;
		private System.Windows.Forms.TextBox tdb_e_bez;
		private System.Windows.Forms.TextBox tdb_e_code;
		private System.Windows.Forms.TextBox tdb_e_text;
		private System.Windows.Forms.Label tdb_l_text;
		private System.Windows.Forms.Label tdb_l_code;
		private System.Windows.Forms.Label tdb_l_bez;
		private System.Windows.Forms.Label tdb_l_id;
		private System.Windows.Forms.ComboBox Ort_e_sta;
		private System.Windows.Forms.TextBox Ort_e_koord1;
		private System.Windows.Forms.TextBox Ort_e_koord2;
		private System.Windows.Forms.Label Ort_l_koord2;
		private System.Windows.Forms.Label Ort_l_sta;
		private System.Windows.Forms.Label Ort_l_koord1;
		private System.Windows.Forms.Label Ort_l_tz;
		private System.Windows.Forms.NumericUpDown Ort_e_tz;
		private System.Windows.Forms.ComboBox Ort_e_land;
		private System.Windows.Forms.Label Ort_l_land;
		private tdbgui.GUIcity Cty;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FCity()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Cty = new tdbgui.GUIcity();
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
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.Ort_e_sta = new System.Windows.Forms.ComboBox();
			this.Ort_e_koord1 = new System.Windows.Forms.TextBox();
			this.Ort_e_koord2 = new System.Windows.Forms.TextBox();
			this.Ort_l_koord2 = new System.Windows.Forms.Label();
			this.Ort_l_sta = new System.Windows.Forms.Label();
			this.Ort_l_koord1 = new System.Windows.Forms.Label();
			this.Ort_l_tz = new System.Windows.Forms.Label();
			this.Ort_e_tz = new System.Windows.Forms.NumericUpDown();
			this.Ort_e_land = new System.Windows.Forms.ComboBox();
			this.Ort_l_land = new System.Windows.Forms.Label();
			this.tdb_e_id = new System.Windows.Forms.Label();
			this.tdb_e_bez = new System.Windows.Forms.TextBox();
			this.tdb_e_code = new System.Windows.Forms.TextBox();
			this.tdb_e_text = new System.Windows.Forms.TextBox();
			this.tdb_l_text = new System.Windows.Forms.Label();
			this.tdb_l_code = new System.Windows.Forms.Label();
			this.tdb_l_bez = new System.Windows.Forms.Label();
			this.tdb_l_id = new System.Windows.Forms.Label();
			this.TDB_abgrp = new System.Windows.Forms.GroupBox();
			this.TDB_ab_clr = new System.Windows.Forms.Button();
			this.TDB_ab_sel = new System.Windows.Forms.Button();
			this.TDB_ab_exit = new System.Windows.Forms.Button();
			this.TDB_ab_del = new System.Windows.Forms.Button();
			this.TDB_ab_upd = new System.Windows.Forms.Button();
			this.TDB_ab_ins = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.Ort_e_tz)).BeginInit();
			this.TDB_abgrp.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Ort_e_sta);
			this.groupBox1.Controls.Add(this.Ort_e_koord1);
			this.groupBox1.Controls.Add(this.Ort_e_koord2);
			this.groupBox1.Controls.Add(this.Ort_l_koord2);
			this.groupBox1.Controls.Add(this.Ort_l_sta);
			this.groupBox1.Controls.Add(this.Ort_l_koord1);
			this.groupBox1.Controls.Add(this.Ort_l_tz);
			this.groupBox1.Controls.Add(this.Ort_e_tz);
			this.groupBox1.Controls.Add(this.Ort_e_land);
			this.groupBox1.Controls.Add(this.Ort_l_land);
			this.groupBox1.Controls.Add(this.tdb_e_id);
			this.groupBox1.Controls.Add(this.tdb_e_bez);
			this.groupBox1.Controls.Add(this.tdb_e_code);
			this.groupBox1.Controls.Add(this.tdb_e_text);
			this.groupBox1.Controls.Add(this.tdb_l_text);
			this.groupBox1.Controls.Add(this.tdb_l_code);
			this.groupBox1.Controls.Add(this.tdb_l_bez);
			this.groupBox1.Controls.Add(this.tdb_l_id);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(608, 365);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Ort_e_sta
			// 
			this.Ort_e_sta.Location = new System.Drawing.Point(136, 264);
			this.Ort_e_sta.Name = "Ort_e_sta";
			this.Ort_e_sta.Size = new System.Drawing.Size(256, 21);
			this.Ort_e_sta.TabIndex = 7;
			// 
			// Ort_e_koord1
			// 
			this.Ort_e_koord1.Location = new System.Drawing.Point(136, 240);
			this.Ort_e_koord1.Name = "Ort_e_koord1";
			this.Ort_e_koord1.TabIndex = 5;
			this.Ort_e_koord1.Text = "";
			// 
			// Ort_e_koord2
			// 
			this.Ort_e_koord2.Location = new System.Drawing.Point(392, 240);
			this.Ort_e_koord2.Name = "Ort_e_koord2";
			this.Ort_e_koord2.TabIndex = 6;
			this.Ort_e_koord2.Text = "";
			// 
			// Ort_l_koord2
			// 
			this.Ort_l_koord2.Location = new System.Drawing.Point(304, 240);
			this.Ort_l_koord2.Name = "Ort_l_koord2";
			this.Ort_l_koord2.Size = new System.Drawing.Size(80, 23);
			this.Ort_l_koord2.TabIndex = 16;
			this.Ort_l_koord2.Text = "Coordinates Y";
			// 
			// Ort_l_sta
			// 
			this.Ort_l_sta.Location = new System.Drawing.Point(8, 264);
			this.Ort_l_sta.Name = "Ort_l_sta";
			this.Ort_l_sta.TabIndex = 15;
			this.Ort_l_sta.Text = "Type";
			// 
			// Ort_l_koord1
			// 
			this.Ort_l_koord1.Location = new System.Drawing.Point(8, 240);
			this.Ort_l_koord1.Name = "Ort_l_koord1";
			this.Ort_l_koord1.TabIndex = 14;
			this.Ort_l_koord1.Text = "Coordinates X";
			// 
			// Ort_l_tz
			// 
			this.Ort_l_tz.Location = new System.Drawing.Point(8, 216);
			this.Ort_l_tz.Name = "Ort_l_tz";
			this.Ort_l_tz.TabIndex = 13;
			this.Ort_l_tz.Text = "Timezone UMT +/-";
			// 
			// Ort_e_tz
			// 
			this.Ort_e_tz.Location = new System.Drawing.Point(136, 216);
			this.Ort_e_tz.Maximum = new System.Decimal(new int[] {
																					  24,
																					  0,
																					  0,
																					  0});
			this.Ort_e_tz.Minimum = new System.Decimal(new int[] {
																					  24,
																					  0,
																					  0,
																					  -2147483648});
			this.Ort_e_tz.Name = "Ort_e_tz";
			this.Ort_e_tz.TabIndex = 4;
			// 
			// Ort_e_land
			// 
			this.Ort_e_land.Location = new System.Drawing.Point(136, 192);
			this.Ort_e_land.Name = "Ort_e_land";
			this.Ort_e_land.Size = new System.Drawing.Size(256, 21);
			this.Ort_e_land.TabIndex = 3;
			// 
			// Ort_l_land
			// 
			this.Ort_l_land.Location = new System.Drawing.Point(8, 192);
			this.Ort_l_land.Name = "Ort_l_land";
			this.Ort_l_land.TabIndex = 10;
			this.Ort_l_land.Text = "Country";
			// 
			// tdb_e_id
			// 
			this.tdb_e_id.Location = new System.Drawing.Point(136, 24);
			this.tdb_e_id.Name = "tdb_e_id";
			this.tdb_e_id.Size = new System.Drawing.Size(64, 16);
			this.tdb_e_id.TabIndex = 9;
			// 
			// tdb_e_bez
			// 
			this.tdb_e_bez.Location = new System.Drawing.Point(136, 40);
			this.tdb_e_bez.Name = "tdb_e_bez";
			this.tdb_e_bez.Size = new System.Drawing.Size(456, 20);
			this.tdb_e_bez.TabIndex = 0;
			this.tdb_e_bez.Text = "";
			// 
			// tdb_e_code
			// 
			this.tdb_e_code.Location = new System.Drawing.Point(136, 64);
			this.tdb_e_code.Name = "tdb_e_code";
			this.tdb_e_code.Size = new System.Drawing.Size(456, 20);
			this.tdb_e_code.TabIndex = 1;
			this.tdb_e_code.Text = "";
			// 
			// tdb_e_text
			// 
			this.tdb_e_text.Location = new System.Drawing.Point(136, 88);
			this.tdb_e_text.Multiline = true;
			this.tdb_e_text.Name = "tdb_e_text";
			this.tdb_e_text.Size = new System.Drawing.Size(456, 88);
			this.tdb_e_text.TabIndex = 2;
			this.tdb_e_text.Text = "";
			// 
			// tdb_l_text
			// 
			this.tdb_l_text.Location = new System.Drawing.Point(8, 121);
			this.tdb_l_text.Name = "tdb_l_text";
			this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.tdb_l_text.TabIndex = 4;
			this.tdb_l_text.Text = "Description";
			// 
			// tdb_l_code
			// 
			this.tdb_l_code.Location = new System.Drawing.Point(8, 63);
			this.tdb_l_code.Name = "tdb_l_code";
			this.tdb_l_code.TabIndex = 3;
			this.tdb_l_code.Text = "Code";
			// 
			// tdb_l_bez
			// 
			this.tdb_l_bez.Location = new System.Drawing.Point(8, 39);
			this.tdb_l_bez.Name = "tdb_l_bez";
			this.tdb_l_bez.TabIndex = 2;
			this.tdb_l_bez.Text = "Title";
			// 
			// tdb_l_id
			// 
			this.tdb_l_id.Location = new System.Drawing.Point(8, 21);
			this.tdb_l_id.Name = "tdb_l_id";
			this.tdb_l_id.TabIndex = 1;
			this.tdb_l_id.Text = "ID";
			// 
			// TDB_abgrp
			// 
			this.TDB_abgrp.Controls.Add(this.TDB_ab_clr);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_sel);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_exit);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_del);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_upd);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_ins);
			this.TDB_abgrp.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 312);
			this.TDB_abgrp.Name = "TDB_abgrp";
			this.TDB_abgrp.Size = new System.Drawing.Size(608, 53);
			this.TDB_abgrp.TabIndex = 15;
			this.TDB_abgrp.TabStop = false;
			this.TDB_abgrp.Text = "Actions";
			// 
			// TDB_ab_clr
			// 
			this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
			this.TDB_ab_clr.Location = new System.Drawing.Point(455, 16);
			this.TDB_ab_clr.Name = "TDB_ab_clr";
			this.TDB_ab_clr.Size = new System.Drawing.Size(75, 34);
			this.TDB_ab_clr.TabIndex = 10;
			this.TDB_ab_clr.Text = "Clear";
			this.TDB_ab_clr.Click += new System.EventHandler(this.TDB_ab_clr_Click);
			// 
			// TDB_ab_sel
			// 
			this.TDB_ab_sel.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(192)), ((System.Byte)(192)), ((System.Byte)(255)));
			this.TDB_ab_sel.Dock = System.Windows.Forms.DockStyle.Left;
			this.TDB_ab_sel.Location = new System.Drawing.Point(228, 16);
			this.TDB_ab_sel.Name = "TDB_ab_sel";
			this.TDB_ab_sel.Size = new System.Drawing.Size(80, 34);
			this.TDB_ab_sel.TabIndex = 8;
			this.TDB_ab_sel.Text = "Select";
			this.TDB_ab_sel.Click += new System.EventHandler(this.TDB_ab_sel_Click);
			// 
			// TDB_ab_exit
			// 
			this.TDB_ab_exit.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(0)), ((System.Byte)(192)), ((System.Byte)(192)));
			this.TDB_ab_exit.Dock = System.Windows.Forms.DockStyle.Right;
			this.TDB_ab_exit.Location = new System.Drawing.Point(530, 16);
			this.TDB_ab_exit.Name = "TDB_ab_exit";
			this.TDB_ab_exit.Size = new System.Drawing.Size(75, 34);
			this.TDB_ab_exit.TabIndex = 9;
			this.TDB_ab_exit.Text = "Exit";
			this.TDB_ab_exit.Click += new System.EventHandler(this.TDB_ab_exit_Click);
			// 
			// TDB_ab_del
			// 
			this.TDB_ab_del.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(255)), ((System.Byte)(192)), ((System.Byte)(192)));
			this.TDB_ab_del.Dock = System.Windows.Forms.DockStyle.Left;
			this.TDB_ab_del.Location = new System.Drawing.Point(153, 16);
			this.TDB_ab_del.Name = "TDB_ab_del";
			this.TDB_ab_del.Size = new System.Drawing.Size(75, 34);
			this.TDB_ab_del.TabIndex = 7;
			this.TDB_ab_del.Text = "Delete";
			this.TDB_ab_del.Click += new System.EventHandler(this.TDB_ab_del_Click);
			// 
			// TDB_ab_upd
			// 
			this.TDB_ab_upd.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(255)), ((System.Byte)(192)), ((System.Byte)(192)));
			this.TDB_ab_upd.Dock = System.Windows.Forms.DockStyle.Left;
			this.TDB_ab_upd.Location = new System.Drawing.Point(78, 16);
			this.TDB_ab_upd.Name = "TDB_ab_upd";
			this.TDB_ab_upd.Size = new System.Drawing.Size(75, 34);
			this.TDB_ab_upd.TabIndex = 6;
			this.TDB_ab_upd.Text = "Update";
			this.TDB_ab_upd.Click += new System.EventHandler(this.TDB_ab_upd_Click);
			// 
			// TDB_ab_ins
			// 
			this.TDB_ab_ins.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(255)), ((System.Byte)(192)), ((System.Byte)(192)));
			this.TDB_ab_ins.Dock = System.Windows.Forms.DockStyle.Left;
			this.TDB_ab_ins.Location = new System.Drawing.Point(3, 16);
			this.TDB_ab_ins.Name = "TDB_ab_ins";
			this.TDB_ab_ins.Size = new System.Drawing.Size(75, 34);
			this.TDB_ab_ins.TabIndex = 5;
			this.TDB_ab_ins.Text = "Insert";
			this.TDB_ab_ins.Click += new System.EventHandler(this.TDB_ab_ins_Click);
			// 
			// FCity
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 365);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FCity";
			this.Text = "City";
			this.Load += new System.EventHandler(this.FPrg_Load);
			this.groupBox1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.Ort_e_tz)).EndInit();
			this.TDB_abgrp.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			Cty.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			Cty.Get(id, ref rows);
			this.tdb_e_id.Text = Cty.ObjId.ToString();
			this.tdb_e_bez.Text = Cty.ObjBez;
			this.tdb_e_code.Text = Cty.ObjCode;
			this.tdb_e_text.Text = Cty.ObjText;
			this.Ort_e_land.SelectedValue = Cty.ObjLandid;
			this.Ort_e_sta.SelectedValue = Cty.ObjType;
			this.Ort_e_koord1.Text = Cty.ObjCoord1.ToString();
			this.Ort_e_koord2.Text = Cty.ObjCoord2.ToString();
			this.Ort_e_tz.Value = Cty.ObjTz;
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			Cty.InsUpd(true, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, (int)this.Ort_e_land.SelectedValue,
				(int)this.Ort_e_sta.SelectedValue, Convert.ToInt32(this.Ort_e_koord1.Text),
				Convert.ToInt32(this.Ort_e_koord2.Text), (int)this.Ort_e_tz.Value);
			tdb_e_id.Text = Cty.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			Cty.InsUpd(false, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, (int)this.Ort_e_land.SelectedValue,
				(int)this.Ort_e_sta.SelectedValue, Convert.ToInt32(this.Ort_e_koord1.Text),
				Convert.ToInt32(this.Ort_e_koord2.Text), (int)this.Ort_e_tz.Value);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			Cty.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			Cty.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_code.Text = "";
			tdb_e_text.Text = "";
			this.Ort_e_koord1.Text = "";
			this.Ort_e_koord2.Text = "";
		}
		private void FPrg_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIctry C = new tdbgui.GUIctry();
			C.SetCombo(this.Ort_e_land);

			tdbgui.GUIsta S = new tdbgui.GUIsta();
			S.ObjTyp = tdb.StatusTypes.staort;
			S.SetCombo(this.Ort_e_sta);
		}

		#endregion

	}
}
