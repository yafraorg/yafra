using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using org.swyn.foundation.utils;
using tdbgui;

namespace tdbadmin
{
	/// <summary>
	/// Suppliertype Form.
	/// </summary>
	public class FSup : System.Windows.Forms.Form
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
		private System.Windows.Forms.TextBox tdb_e_text;
		private System.Windows.Forms.Label tdb_l_text;
		private System.Windows.Forms.Label tdb_l_bez;
		private System.Windows.Forms.Label tdb_l_id;
		private System.Windows.Forms.TextBox tdb_e_code;
		private System.Windows.Forms.Label tdb_l_code;
		private System.Windows.Forms.ComboBox Dlt_e_sta;
		private System.Windows.Forms.Label Dlt_l_sta;
		private System.Windows.Forms.NumericUpDown Dlt_e_level;
		private System.Windows.Forms.NumericUpDown Dlt_e_anz;
		private System.Windows.Forms.Label Dlt_l_anz;
		private System.Windows.Forms.Label Dlt_l_level;
		private System.Windows.Forms.CheckBox Dlt_e_ishost;
		private System.Windows.Forms.Label Dlt_e_host;
		private System.Windows.Forms.Label Dlt_l_host;
		private System.Windows.Forms.ComboBox Dlt_e_parent;
		private System.Windows.Forms.Label Dlt_l_parent;
		private System.Windows.Forms.Label Dlt_l_dltt;
		private System.Windows.Forms.Button Dlt_e_sel;
		private System.Windows.Forms.Label Dlt_e_dltt;
		private System.Windows.Forms.Label Dlt_e_kat;
		private bool ishost;
		private tdbgui.GUIsup dlt;
		private int guikatid;
		private int guidlttid;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FSup()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			dlt = new tdbgui.GUIsup();
			ishost = false;
			guikatid = -1;
			guidlttid = -1;
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
			this.Dlt_e_kat = new System.Windows.Forms.Label();
			this.Dlt_e_dltt = new System.Windows.Forms.Label();
			this.Dlt_e_sel = new System.Windows.Forms.Button();
			this.Dlt_l_level = new System.Windows.Forms.Label();
			this.Dlt_l_anz = new System.Windows.Forms.Label();
			this.Dlt_e_anz = new System.Windows.Forms.NumericUpDown();
			this.Dlt_e_level = new System.Windows.Forms.NumericUpDown();
			this.Dlt_l_dltt = new System.Windows.Forms.Label();
			this.Dlt_l_sta = new System.Windows.Forms.Label();
			this.Dlt_e_sta = new System.Windows.Forms.ComboBox();
			this.tdb_e_code = new System.Windows.Forms.TextBox();
			this.tdb_l_code = new System.Windows.Forms.Label();
			this.Dlt_e_ishost = new System.Windows.Forms.CheckBox();
			this.Dlt_e_host = new System.Windows.Forms.Label();
			this.Dlt_l_host = new System.Windows.Forms.Label();
			this.Dlt_e_parent = new System.Windows.Forms.ComboBox();
			this.Dlt_l_parent = new System.Windows.Forms.Label();
			this.tdb_e_id = new System.Windows.Forms.Label();
			this.tdb_e_bez = new System.Windows.Forms.TextBox();
			this.tdb_e_text = new System.Windows.Forms.TextBox();
			this.tdb_l_text = new System.Windows.Forms.Label();
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
			((System.ComponentModel.ISupportInitialize)(this.Dlt_e_anz)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.Dlt_e_level)).BeginInit();
			this.TDB_abgrp.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Dlt_e_kat);
			this.groupBox1.Controls.Add(this.Dlt_e_dltt);
			this.groupBox1.Controls.Add(this.Dlt_e_sel);
			this.groupBox1.Controls.Add(this.Dlt_l_level);
			this.groupBox1.Controls.Add(this.Dlt_l_anz);
			this.groupBox1.Controls.Add(this.Dlt_e_anz);
			this.groupBox1.Controls.Add(this.Dlt_e_level);
			this.groupBox1.Controls.Add(this.Dlt_l_dltt);
			this.groupBox1.Controls.Add(this.Dlt_l_sta);
			this.groupBox1.Controls.Add(this.Dlt_e_sta);
			this.groupBox1.Controls.Add(this.tdb_e_code);
			this.groupBox1.Controls.Add(this.tdb_l_code);
			this.groupBox1.Controls.Add(this.Dlt_e_ishost);
			this.groupBox1.Controls.Add(this.Dlt_e_host);
			this.groupBox1.Controls.Add(this.Dlt_l_host);
			this.groupBox1.Controls.Add(this.Dlt_e_parent);
			this.groupBox1.Controls.Add(this.Dlt_l_parent);
			this.groupBox1.Controls.Add(this.tdb_e_id);
			this.groupBox1.Controls.Add(this.tdb_e_bez);
			this.groupBox1.Controls.Add(this.tdb_e_text);
			this.groupBox1.Controls.Add(this.tdb_l_text);
			this.groupBox1.Controls.Add(this.tdb_l_bez);
			this.groupBox1.Controls.Add(this.tdb_l_id);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(608, 397);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Dlt_e_kat
			// 
			this.Dlt_e_kat.Location = new System.Drawing.Point(224, 256);
			this.Dlt_e_kat.Name = "Dlt_e_kat";
			this.Dlt_e_kat.Size = new System.Drawing.Size(352, 16);
			this.Dlt_e_kat.TabIndex = 29;
			// 
			// Dlt_e_dltt
			// 
			this.Dlt_e_dltt.Location = new System.Drawing.Point(224, 240);
			this.Dlt_e_dltt.Name = "Dlt_e_dltt";
			this.Dlt_e_dltt.Size = new System.Drawing.Size(352, 16);
			this.Dlt_e_dltt.TabIndex = 28;
			// 
			// Dlt_e_sel
			// 
			this.Dlt_e_sel.BackColor = System.Drawing.Color.FromArgb(((System.Byte)(192)), ((System.Byte)(192)), ((System.Byte)(255)));
			this.Dlt_e_sel.Location = new System.Drawing.Point(136, 240);
			this.Dlt_e_sel.Name = "Dlt_e_sel";
			this.Dlt_e_sel.Size = new System.Drawing.Size(75, 32);
			this.Dlt_e_sel.TabIndex = 5;
			this.Dlt_e_sel.Text = "Select";
			this.Dlt_e_sel.Click += new System.EventHandler(this.Dlt_e_sel_Click);
			// 
			// Dlt_l_level
			// 
			this.Dlt_l_level.Location = new System.Drawing.Point(360, 306);
			this.Dlt_l_level.Name = "Dlt_l_level";
			this.Dlt_l_level.Size = new System.Drawing.Size(40, 17);
			this.Dlt_l_level.TabIndex = 26;
			this.Dlt_l_level.Text = "Level";
			// 
			// Dlt_l_anz
			// 
			this.Dlt_l_anz.Location = new System.Drawing.Point(8, 304);
			this.Dlt_l_anz.Name = "Dlt_l_anz";
			this.Dlt_l_anz.TabIndex = 25;
			this.Dlt_l_anz.Text = "Capacity";
			// 
			// Dlt_e_anz
			// 
			this.Dlt_e_anz.Location = new System.Drawing.Point(136, 304);
			this.Dlt_e_anz.Maximum = new System.Decimal(new int[] {
																						1000,
																						0,
																						0,
																						0});
			this.Dlt_e_anz.Name = "Dlt_e_anz";
			this.Dlt_e_anz.Size = new System.Drawing.Size(56, 20);
			this.Dlt_e_anz.TabIndex = 7;
			this.Dlt_e_anz.Value = new System.Decimal(new int[] {
																					 1,
																					 0,
																					 0,
																					 0});
			// 
			// Dlt_e_level
			// 
			this.Dlt_e_level.Location = new System.Drawing.Point(408, 304);
			this.Dlt_e_level.Maximum = new System.Decimal(new int[] {
																						  1000,
																						  0,
																						  0,
																						  0});
			this.Dlt_e_level.Name = "Dlt_e_level";
			this.Dlt_e_level.Size = new System.Drawing.Size(56, 20);
			this.Dlt_e_level.TabIndex = 8;
			this.Dlt_e_level.Value = new System.Decimal(new int[] {
																						1,
																						0,
																						0,
																						0});
			// 
			// Dlt_l_dltt
			// 
			this.Dlt_l_dltt.Location = new System.Drawing.Point(8, 240);
			this.Dlt_l_dltt.Name = "Dlt_l_dltt";
			this.Dlt_l_dltt.Size = new System.Drawing.Size(100, 32);
			this.Dlt_l_dltt.TabIndex = 22;
			this.Dlt_l_dltt.Text = "Supliertype / Category";
			// 
			// Dlt_l_sta
			// 
			this.Dlt_l_sta.Location = new System.Drawing.Point(8, 280);
			this.Dlt_l_sta.Name = "Dlt_l_sta";
			this.Dlt_l_sta.Size = new System.Drawing.Size(112, 23);
			this.Dlt_l_sta.TabIndex = 21;
			this.Dlt_l_sta.Text = "Best place attribute";
			// 
			// Dlt_e_sta
			// 
			this.Dlt_e_sta.Location = new System.Drawing.Point(136, 280);
			this.Dlt_e_sta.Name = "Dlt_e_sta";
			this.Dlt_e_sta.Size = new System.Drawing.Size(456, 21);
			this.Dlt_e_sta.TabIndex = 6;
			// 
			// tdb_e_code
			// 
			this.tdb_e_code.Location = new System.Drawing.Point(136, 64);
			this.tdb_e_code.Name = "tdb_e_code";
			this.tdb_e_code.Size = new System.Drawing.Size(456, 20);
			this.tdb_e_code.TabIndex = 1;
			this.tdb_e_code.Text = "";
			// 
			// tdb_l_code
			// 
			this.tdb_l_code.Location = new System.Drawing.Point(8, 64);
			this.tdb_l_code.Name = "tdb_l_code";
			this.tdb_l_code.TabIndex = 16;
			this.tdb_l_code.Text = "Code";
			// 
			// Dlt_e_ishost
			// 
			this.Dlt_e_ishost.Location = new System.Drawing.Point(488, 184);
			this.Dlt_e_ishost.Name = "Dlt_e_ishost";
			this.Dlt_e_ishost.TabIndex = 4;
			this.Dlt_e_ishost.Text = "Top / Root ?";
			this.Dlt_e_ishost.CheckedChanged += new System.EventHandler(this.Dlt_e_ishost_CheckedChanged);
			// 
			// Dlt_e_host
			// 
			this.Dlt_e_host.Location = new System.Drawing.Point(136, 208);
			this.Dlt_e_host.Name = "Dlt_e_host";
			this.Dlt_e_host.Size = new System.Drawing.Size(448, 23);
			this.Dlt_e_host.TabIndex = 13;
			// 
			// Dlt_l_host
			// 
			this.Dlt_l_host.Location = new System.Drawing.Point(8, 208);
			this.Dlt_l_host.Name = "Dlt_l_host";
			this.Dlt_l_host.Size = new System.Drawing.Size(104, 23);
			this.Dlt_l_host.TabIndex = 12;
			this.Dlt_l_host.Text = "Root Supplier";
			// 
			// Dlt_e_parent
			// 
			this.Dlt_e_parent.Location = new System.Drawing.Point(136, 184);
			this.Dlt_e_parent.Name = "Dlt_e_parent";
			this.Dlt_e_parent.Size = new System.Drawing.Size(344, 21);
			this.Dlt_e_parent.TabIndex = 3;
			// 
			// Dlt_l_parent
			// 
			this.Dlt_l_parent.Location = new System.Drawing.Point(8, 184);
			this.Dlt_l_parent.Name = "Dlt_l_parent";
			this.Dlt_l_parent.TabIndex = 10;
			this.Dlt_l_parent.Text = "Parent";
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
			this.tdb_l_text.Location = new System.Drawing.Point(8, 120);
			this.tdb_l_text.Name = "tdb_l_text";
			this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.tdb_l_text.TabIndex = 4;
			this.tdb_l_text.Text = "Description";
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
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 344);
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
			this.TDB_ab_clr.TabIndex = 13;
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
			this.TDB_ab_sel.TabIndex = 12;
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
			this.TDB_ab_exit.TabIndex = 14;
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
			this.TDB_ab_del.TabIndex = 11;
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
			this.TDB_ab_upd.TabIndex = 10;
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
			this.TDB_ab_ins.TabIndex = 9;
			this.TDB_ab_ins.Text = "Insert";
			this.TDB_ab_ins.Click += new System.EventHandler(this.TDB_ab_ins_Click);
			// 
			// FSup
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 397);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FSup";
			this.Text = "Supplier";
			this.Load += new System.EventHandler(this.FSup_Load);
			this.groupBox1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.Dlt_e_anz)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.Dlt_e_level)).EndInit();
			this.TDB_abgrp.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelTreeForm Fsel = new SelTreeForm();
			dlt.SelTree(Fsel.GetTV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelTreeForm Fsel = (SelTreeForm)sender;
			id = Fsel.GetID;
			dlt.Get(id, ref rows);
			this.tdb_e_code.Text = dlt.ObjCode;
			this.tdb_e_id.Text = dlt.ObjId.ToString();
			this.tdb_e_bez.Text = dlt.ObjBez;
			this.tdb_e_text.Text = dlt.ObjText;
			if (dlt.ObjParentId == -1)
			{
				this.Dlt_e_parent.SelectedValue = -1;
				this.Dlt_e_ishost.CheckState = CheckState.Checked;
				this.Dlt_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Dlt_e_parent.SelectedValue = dlt.ObjParentId;
				this.Dlt_e_ishost.CheckState = CheckState.Unchecked;
				this.Dlt_e_parent.Visible = true;
				ishost = false;
			}
			tdb.Sup dlt2 = new tdb.Sup();
			this.Dlt_e_host.Text = dlt2.GetBez(dlt.ObjHost);
			this.Dlt_e_anz.Value = dlt.ObjCapacity;
			this.Dlt_e_level.Value = dlt.ObjLevel;
			guikatid = dlt.ObjCategory;
			guidlttid = dlt.ObjSuptype;
			this.Dlt_e_dltt.Text = dlt.ObjSupT;
			this.Dlt_e_kat.Text = dlt.ObjCatT;
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			dlt.InsUpd(true, tdb_e_bez.Text, tdb_e_text.Text, tdb_e_code.Text,
				(int)this.Dlt_e_parent.SelectedValue, ishost, this.guikatid,
				this.guidlttid, (int)this.Dlt_e_sta.SelectedValue,
				(int)this.Dlt_e_level.Value, (int)this.Dlt_e_anz.Value);
			tdb_e_id.Text = dlt.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			dlt.InsUpd(false, tdb_e_bez.Text, tdb_e_text.Text, tdb_e_code.Text, 
				(int)this.Dlt_e_parent.SelectedValue, ishost, this.guikatid,
				this.guidlttid, (int)this.Dlt_e_sta.SelectedValue,
				(int)this.Dlt_e_level.Value, (int)this.Dlt_e_anz.Value);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			dlt.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			dlt.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_text.Text = "";
			Dlt_e_host.Text = "";
			Dlt_e_kat.Text = "";
			Dlt_e_dltt.Text = "";
		}

		private void FSup_Load(object sender, System.EventArgs e)
		{
			dlt.ObjOptional = true;
			dlt.SetCombo(this.Dlt_e_parent);

			tdbgui.GUIsta sta = new tdbgui.GUIsta();
			sta.ObjTyp = tdb.StatusTypes.stadlt;
			sta.SetCombo(this.Dlt_e_sta);
		}

		private void Dlt_e_ishost_CheckedChanged(object sender, System.EventArgs e)
		{
			if (this.Dlt_e_ishost.CheckState == CheckState.Checked)
			{
				this.Dlt_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Dlt_e_parent.Visible = true;
				ishost = false;
			}
		}

		private void Dlt_e_sel_Click(object sender, System.EventArgs e)
		{
			tdbgui.GUIcat cat = new tdbgui.GUIcat();
			SelForm Fsel = new SelForm();
			cat.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(Dlt_e_sel_Return);
			Fsel.ShowDialog(this);
		}

		void Dlt_e_sel_Return(object sender, EventArgs e) 
		{
			SelForm Fsel = (SelForm)sender;
			System.Windows.Forms.ListView sellv;
			sellv = Fsel.GetLV;

			ListViewItem lvitem = null;
			if(sellv.SelectedItems.Count > 0)
				lvitem = sellv.SelectedItems[0];
			ListViewItem.ListViewSubItem LVSubItem = null;
			if(lvitem != null)
			{
				LVSubItem = lvitem.SubItems[0];
				guikatid = Convert.ToInt32(LVSubItem.Text);
				LVSubItem = lvitem.SubItems[1];
				this.Dlt_e_kat.Text = LVSubItem.Text;
				LVSubItem = lvitem.SubItems[2];
				guidlttid = Convert.ToInt32(LVSubItem.Text);
				LVSubItem = lvitem.SubItems[3];
				this.Dlt_e_dltt.Text = LVSubItem.Text;
			}
		}
		#endregion



	}
}
