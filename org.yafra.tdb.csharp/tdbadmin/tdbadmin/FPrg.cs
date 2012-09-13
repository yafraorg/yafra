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
	/// Program Form.
	/// </summary>
	public class FPrg : System.Windows.Forms.Form
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
		private System.Windows.Forms.Label Prg_l_sai;
		private System.Windows.Forms.ComboBox Prg_e_sai;
		private DataTable Csai;
		private tdbgui.GUIprg P;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FPrg()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			P = new tdbgui.GUIprg();
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
			this.Prg_e_sai = new System.Windows.Forms.ComboBox();
			this.Prg_l_sai = new System.Windows.Forms.Label();
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
			this.TDB_abgrp.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Prg_e_sai);
			this.groupBox1.Controls.Add(this.Prg_l_sai);
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
			this.groupBox1.Size = new System.Drawing.Size(608, 285);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Prg_e_sai
			// 
			this.Prg_e_sai.Location = new System.Drawing.Point(136, 192);
			this.Prg_e_sai.Name = "Prg_e_sai";
			this.Prg_e_sai.Size = new System.Drawing.Size(256, 21);
			this.Prg_e_sai.TabIndex = 11;
			// 
			// Prg_l_sai
			// 
			this.Prg_l_sai.Location = new System.Drawing.Point(8, 192);
			this.Prg_l_sai.Name = "Prg_l_sai";
			this.Prg_l_sai.TabIndex = 10;
			this.Prg_l_sai.Text = "Season";
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
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 232);
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
			// FPrg
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 285);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FPrg";
			this.Text = "Program";
			this.Load += new System.EventHandler(this.FPrg_Load);
			this.groupBox1.ResumeLayout(false);
			this.TDB_abgrp.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			P.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			P.Get(id, ref rows);
			this.tdb_e_id.Text = P.ObjId.ToString();
			this.tdb_e_bez.Text = P.ObjBez;
			this.tdb_e_code.Text = P.ObjCode;
			this.tdb_e_text.Text = P.ObjText;
			this.Prg_e_sai.SelectedValue = P.ObjSaiid;

		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			P.InsUpd(true, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, (int)this.Prg_e_sai.SelectedValue);
			tdb_e_id.Text = P.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			P.InsUpd(false, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, (int)this.Prg_e_sai.SelectedValue);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			P.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			P.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_code.Text = "";
			tdb_e_text.Text = "";
		}

		private void FPrg_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIsai S = new tdbgui.GUIsai();
			S.SetCombo(this.Prg_e_sai);
		}

		#endregion
	}
}
