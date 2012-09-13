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
	/// category Form.
	/// </summary>
	public class FCat : System.Windows.Forms.Form
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
		private System.Windows.Forms.CheckBox Kat_e_ishost;
		private System.Windows.Forms.Label Kat_l_dltt;
		private System.Windows.Forms.ComboBox Kat_e_parent;
		private System.Windows.Forms.Label Kat_l_parent;
		private System.Windows.Forms.ComboBox Kat_e_dltt;
		private System.Windows.Forms.Label Kat_l_ga;
		private System.Windows.Forms.TextBox Kat_e_ga;
		private bool ishost;
		private tdbgui.GUIcat cat;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FCat()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			cat = new tdbgui.GUIcat();
			ishost = false;
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
			this.Kat_e_ga = new System.Windows.Forms.TextBox();
			this.Kat_l_ga = new System.Windows.Forms.Label();
			this.Kat_e_dltt = new System.Windows.Forms.ComboBox();
			this.Kat_e_ishost = new System.Windows.Forms.CheckBox();
			this.Kat_l_dltt = new System.Windows.Forms.Label();
			this.Kat_e_parent = new System.Windows.Forms.ComboBox();
			this.Kat_l_parent = new System.Windows.Forms.Label();
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
			this.TDB_abgrp.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Kat_e_ga);
			this.groupBox1.Controls.Add(this.Kat_l_ga);
			this.groupBox1.Controls.Add(this.Kat_e_dltt);
			this.groupBox1.Controls.Add(this.Kat_e_ishost);
			this.groupBox1.Controls.Add(this.Kat_l_dltt);
			this.groupBox1.Controls.Add(this.Kat_e_parent);
			this.groupBox1.Controls.Add(this.Kat_l_parent);
			this.groupBox1.Controls.Add(this.tdb_e_id);
			this.groupBox1.Controls.Add(this.tdb_e_bez);
			this.groupBox1.Controls.Add(this.tdb_e_text);
			this.groupBox1.Controls.Add(this.tdb_l_text);
			this.groupBox1.Controls.Add(this.tdb_l_bez);
			this.groupBox1.Controls.Add(this.tdb_l_id);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(608, 317);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Kat_e_ga
			// 
			this.Kat_e_ga.Location = new System.Drawing.Point(136, 208);
			this.Kat_e_ga.Name = "Kat_e_ga";
			this.Kat_e_ga.Size = new System.Drawing.Size(248, 20);
			this.Kat_e_ga.TabIndex = 17;
			this.Kat_e_ga.Text = "";
			// 
			// Kat_l_ga
			// 
			this.Kat_l_ga.Location = new System.Drawing.Point(8, 208);
			this.Kat_l_ga.Name = "Kat_l_ga";
			this.Kat_l_ga.TabIndex = 16;
			this.Kat_l_ga.Text = "Grafical attribute";
			// 
			// Kat_e_dltt
			// 
			this.Kat_e_dltt.Location = new System.Drawing.Point(136, 184);
			this.Kat_e_dltt.Name = "Kat_e_dltt";
			this.Kat_e_dltt.Size = new System.Drawing.Size(248, 21);
			this.Kat_e_dltt.TabIndex = 15;
			// 
			// Kat_e_ishost
			// 
			this.Kat_e_ishost.Location = new System.Drawing.Point(432, 160);
			this.Kat_e_ishost.Name = "Kat_e_ishost";
			this.Kat_e_ishost.TabIndex = 14;
			this.Kat_e_ishost.Text = "No Upgrade ?";
			this.Kat_e_ishost.CheckedChanged += new System.EventHandler(this.Kat_e_ishost_CheckedChanged);
			// 
			// Kat_l_dltt
			// 
			this.Kat_l_dltt.Location = new System.Drawing.Point(8, 184);
			this.Kat_l_dltt.Name = "Kat_l_dltt";
			this.Kat_l_dltt.Size = new System.Drawing.Size(104, 23);
			this.Kat_l_dltt.TabIndex = 12;
			this.Kat_l_dltt.Text = "Supplier Type";
			// 
			// Kat_e_parent
			// 
			this.Kat_e_parent.Location = new System.Drawing.Point(136, 160);
			this.Kat_e_parent.Name = "Kat_e_parent";
			this.Kat_e_parent.Size = new System.Drawing.Size(248, 21);
			this.Kat_e_parent.TabIndex = 11;
			// 
			// Kat_l_parent
			// 
			this.Kat_l_parent.Location = new System.Drawing.Point(8, 160);
			this.Kat_l_parent.Name = "Kat_l_parent";
			this.Kat_l_parent.TabIndex = 10;
			this.Kat_l_parent.Text = "Upgrade category";
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
			this.tdb_e_text.Location = new System.Drawing.Point(136, 64);
			this.tdb_e_text.Multiline = true;
			this.tdb_e_text.Name = "tdb_e_text";
			this.tdb_e_text.Size = new System.Drawing.Size(456, 88);
			this.tdb_e_text.TabIndex = 2;
			this.tdb_e_text.Text = "";
			// 
			// tdb_l_text
			// 
			this.tdb_l_text.Location = new System.Drawing.Point(8, 96);
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
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 261);
			this.TDB_abgrp.Name = "TDB_abgrp";
			this.TDB_abgrp.Size = new System.Drawing.Size(608, 56);
			this.TDB_abgrp.TabIndex = 15;
			this.TDB_abgrp.TabStop = false;
			this.TDB_abgrp.Text = "Actions";
			// 
			// TDB_ab_clr
			// 
			this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
			this.TDB_ab_clr.Location = new System.Drawing.Point(455, 16);
			this.TDB_ab_clr.Name = "TDB_ab_clr";
			this.TDB_ab_clr.Size = new System.Drawing.Size(75, 37);
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
			this.TDB_ab_sel.Size = new System.Drawing.Size(80, 37);
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
			this.TDB_ab_exit.Size = new System.Drawing.Size(75, 37);
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
			this.TDB_ab_del.Size = new System.Drawing.Size(75, 37);
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
			this.TDB_ab_upd.Size = new System.Drawing.Size(75, 37);
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
			this.TDB_ab_ins.Size = new System.Drawing.Size(75, 37);
			this.TDB_ab_ins.TabIndex = 5;
			this.TDB_ab_ins.Text = "Insert";
			this.TDB_ab_ins.Click += new System.EventHandler(this.TDB_ab_ins_Click);
			// 
			// FCat
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 317);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FCat";
			this.Text = "Category";
			this.Load += new System.EventHandler(this.FCat_Load);
			this.groupBox1.ResumeLayout(false);
			this.TDB_abgrp.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			cat.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			cat.Get(id, ref rows);
			tdb_e_id.Text = cat.ObjId.ToString();
			tdb_e_bez.Text = cat.ObjBez;
			tdb_e_text.Text = cat.ObjText;
			if (cat.ObjParentId == -1)
			{
				this.Kat_e_parent.SelectedValue = -1;
				this.Kat_e_ishost.CheckState = CheckState.Checked;
				this.Kat_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Kat_e_parent.SelectedValue = cat.ObjParentId;
				this.Kat_e_ishost.CheckState = CheckState.Unchecked;
				this.Kat_e_parent.Visible = true;
				ishost = false;
			}
			Kat_e_ga.Text = cat.ObjColor.ToString();
			this.Kat_e_dltt.SelectedValue = cat.ObjSupType;
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			cat.InsUpd(true, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Kat_e_parent.SelectedValue,
				(int)this.Kat_e_dltt.SelectedValue, Convert.ToInt32(this.Kat_e_ga.Text), ishost);
			tdb_e_id.Text = cat.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			cat.InsUpd(false, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Kat_e_parent.SelectedValue,
				(int)this.Kat_e_dltt.SelectedValue, Convert.ToInt32(this.Kat_e_ga.Text), ishost);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			cat.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			cat.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_text.Text = "";
			Kat_e_ga.Text = "1";
		}

		private void FCat_Load(object sender, System.EventArgs e)
		{
			cat.ObjOptional = true;
			cat.SetCombo(this.Kat_e_parent);
			tdbgui.GUIsuptype supt = new tdbgui.GUIsuptype();
			supt.SetCombo(this.Kat_e_dltt);
		}

		private void Kat_e_ishost_CheckedChanged(object sender, System.EventArgs e)
		{
			if (this.Kat_e_ishost.CheckState == CheckState.Checked)
			{
				this.Kat_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Kat_e_parent.Visible = true;
				ishost = false;
			}
		}

		#endregion

	}
}
