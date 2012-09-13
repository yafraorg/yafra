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
	public class FCountry : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.GroupBox TDB_abgrp;
		private System.Windows.Forms.Button TDB_ab_clr;
		private System.Windows.Forms.Button TDB_ab_sel;
		private System.Windows.Forms.Button TDB_ab_exit;
		private System.Windows.Forms.Button TDB_ab_del;
		private System.Windows.Forms.Button TDB_ab_upd;
		private System.Windows.Forms.Button TDB_ab_ins;
		private System.Windows.Forms.Label Land_l_capital;
		private System.Windows.Forms.ComboBox Land_e_capital;
		private System.Windows.Forms.ComboBox Land_e_lang;
		private System.Windows.Forms.ComboBox Land_e_cur;
		private System.Windows.Forms.TextBox Land_e_vat;
		private System.Windows.Forms.TextBox Land_e_dateformat;
		private System.Windows.Forms.Label Land_l_cur;
		private System.Windows.Forms.Label Land_l_lang;
		private System.Windows.Forms.Label Land_l_vat;
		private System.Windows.Forms.Label Land_l_dateformat;
		private System.Windows.Forms.Label tdb_e_id;
		private System.Windows.Forms.TextBox tdb_e_bez;
		private System.Windows.Forms.TextBox tdb_e_code;
		private System.Windows.Forms.TextBox tdb_e_text;
		private System.Windows.Forms.Label tdb_l_text;
		private System.Windows.Forms.Label tdb_l_code;
		private System.Windows.Forms.Label tdb_l_bez;
		private System.Windows.Forms.Label tdb_l_id;
		private tdbgui.GUIctry Ctry;
        private Button Land_e_addlang;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FCountry()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Ctry = new tdbgui.GUIctry();
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
            this.tdb_e_id = new System.Windows.Forms.Label();
            this.tdb_e_bez = new System.Windows.Forms.TextBox();
            this.tdb_e_code = new System.Windows.Forms.TextBox();
            this.tdb_e_text = new System.Windows.Forms.TextBox();
            this.tdb_l_text = new System.Windows.Forms.Label();
            this.tdb_l_code = new System.Windows.Forms.Label();
            this.tdb_l_bez = new System.Windows.Forms.Label();
            this.tdb_l_id = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.Land_l_dateformat = new System.Windows.Forms.Label();
            this.Land_l_vat = new System.Windows.Forms.Label();
            this.Land_l_lang = new System.Windows.Forms.Label();
            this.Land_l_cur = new System.Windows.Forms.Label();
            this.Land_e_dateformat = new System.Windows.Forms.TextBox();
            this.Land_e_vat = new System.Windows.Forms.TextBox();
            this.Land_e_cur = new System.Windows.Forms.ComboBox();
            this.Land_e_lang = new System.Windows.Forms.ComboBox();
            this.Land_e_capital = new System.Windows.Forms.ComboBox();
            this.Land_l_capital = new System.Windows.Forms.Label();
            this.TDB_abgrp = new System.Windows.Forms.GroupBox();
            this.TDB_ab_clr = new System.Windows.Forms.Button();
            this.TDB_ab_sel = new System.Windows.Forms.Button();
            this.TDB_ab_exit = new System.Windows.Forms.Button();
            this.TDB_ab_del = new System.Windows.Forms.Button();
            this.TDB_ab_upd = new System.Windows.Forms.Button();
            this.TDB_ab_ins = new System.Windows.Forms.Button();
            this.Land_e_addlang = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.TDB_abgrp.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tdb_e_id);
            this.groupBox1.Controls.Add(this.tdb_e_bez);
            this.groupBox1.Controls.Add(this.tdb_e_code);
            this.groupBox1.Controls.Add(this.tdb_e_text);
            this.groupBox1.Controls.Add(this.tdb_l_text);
            this.groupBox1.Controls.Add(this.tdb_l_code);
            this.groupBox1.Controls.Add(this.tdb_l_bez);
            this.groupBox1.Controls.Add(this.tdb_l_id);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(640, 192);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Description";
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
            // 
            // tdb_e_code
            // 
            this.tdb_e_code.Location = new System.Drawing.Point(136, 64);
            this.tdb_e_code.Name = "tdb_e_code";
            this.tdb_e_code.Size = new System.Drawing.Size(456, 20);
            this.tdb_e_code.TabIndex = 1;
            // 
            // tdb_e_text
            // 
            this.tdb_e_text.Location = new System.Drawing.Point(136, 88);
            this.tdb_e_text.Multiline = true;
            this.tdb_e_text.Name = "tdb_e_text";
            this.tdb_e_text.Size = new System.Drawing.Size(456, 88);
            this.tdb_e_text.TabIndex = 2;
            // 
            // tdb_l_text
            // 
            this.tdb_l_text.Location = new System.Drawing.Point(8, 121);
            this.tdb_l_text.Name = "tdb_l_text";
            this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tdb_l_text.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_text.TabIndex = 4;
            this.tdb_l_text.Text = "Description";
            // 
            // tdb_l_code
            // 
            this.tdb_l_code.Location = new System.Drawing.Point(8, 63);
            this.tdb_l_code.Name = "tdb_l_code";
            this.tdb_l_code.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_code.TabIndex = 3;
            this.tdb_l_code.Text = "Code";
            // 
            // tdb_l_bez
            // 
            this.tdb_l_bez.Location = new System.Drawing.Point(8, 39);
            this.tdb_l_bez.Name = "tdb_l_bez";
            this.tdb_l_bez.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_bez.TabIndex = 2;
            this.tdb_l_bez.Text = "Title";
            // 
            // tdb_l_id
            // 
            this.tdb_l_id.Location = new System.Drawing.Point(8, 21);
            this.tdb_l_id.Name = "tdb_l_id";
            this.tdb_l_id.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_id.TabIndex = 1;
            this.tdb_l_id.Text = "ID";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.Land_e_addlang);
            this.groupBox2.Controls.Add(this.Land_l_dateformat);
            this.groupBox2.Controls.Add(this.Land_l_vat);
            this.groupBox2.Controls.Add(this.Land_l_lang);
            this.groupBox2.Controls.Add(this.Land_l_cur);
            this.groupBox2.Controls.Add(this.Land_e_dateformat);
            this.groupBox2.Controls.Add(this.Land_e_vat);
            this.groupBox2.Controls.Add(this.Land_e_cur);
            this.groupBox2.Controls.Add(this.Land_e_lang);
            this.groupBox2.Controls.Add(this.Land_e_capital);
            this.groupBox2.Controls.Add(this.Land_l_capital);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(0, 192);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(640, 253);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Details";
            // 
            // Land_l_dateformat
            // 
            this.Land_l_dateformat.Location = new System.Drawing.Point(8, 162);
            this.Land_l_dateformat.Name = "Land_l_dateformat";
            this.Land_l_dateformat.Size = new System.Drawing.Size(100, 16);
            this.Land_l_dateformat.TabIndex = 11;
            this.Land_l_dateformat.Text = "Date Time format";
            // 
            // Land_l_vat
            // 
            this.Land_l_vat.Location = new System.Drawing.Point(8, 122);
            this.Land_l_vat.Name = "Land_l_vat";
            this.Land_l_vat.Size = new System.Drawing.Size(100, 16);
            this.Land_l_vat.TabIndex = 10;
            this.Land_l_vat.Text = "VAT";
            // 
            // Land_l_lang
            // 
            this.Land_l_lang.Location = new System.Drawing.Point(8, 50);
            this.Land_l_lang.Name = "Land_l_lang";
            this.Land_l_lang.Size = new System.Drawing.Size(100, 16);
            this.Land_l_lang.TabIndex = 9;
            this.Land_l_lang.Text = "Main language";
            // 
            // Land_l_cur
            // 
            this.Land_l_cur.Location = new System.Drawing.Point(8, 82);
            this.Land_l_cur.Name = "Land_l_cur";
            this.Land_l_cur.Size = new System.Drawing.Size(100, 16);
            this.Land_l_cur.TabIndex = 8;
            this.Land_l_cur.Text = "Currency";
            // 
            // Land_e_dateformat
            // 
            this.Land_e_dateformat.Location = new System.Drawing.Point(136, 160);
            this.Land_e_dateformat.Name = "Land_e_dateformat";
            this.Land_e_dateformat.Size = new System.Drawing.Size(304, 20);
            this.Land_e_dateformat.TabIndex = 7;
            // 
            // Land_e_vat
            // 
            this.Land_e_vat.Location = new System.Drawing.Point(136, 120);
            this.Land_e_vat.Name = "Land_e_vat";
            this.Land_e_vat.Size = new System.Drawing.Size(304, 20);
            this.Land_e_vat.TabIndex = 6;
            // 
            // Land_e_cur
            // 
            this.Land_e_cur.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Land_e_cur.Location = new System.Drawing.Point(136, 80);
            this.Land_e_cur.Name = "Land_e_cur";
            this.Land_e_cur.Size = new System.Drawing.Size(304, 21);
            this.Land_e_cur.TabIndex = 5;
            // 
            // Land_e_lang
            // 
            this.Land_e_lang.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Land_e_lang.Location = new System.Drawing.Point(136, 48);
            this.Land_e_lang.Name = "Land_e_lang";
            this.Land_e_lang.Size = new System.Drawing.Size(304, 21);
            this.Land_e_lang.TabIndex = 4;
            // 
            // Land_e_capital
            // 
            this.Land_e_capital.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.Land_e_capital.Location = new System.Drawing.Point(136, 14);
            this.Land_e_capital.Name = "Land_e_capital";
            this.Land_e_capital.Size = new System.Drawing.Size(304, 21);
            this.Land_e_capital.TabIndex = 3;
            this.Land_e_capital.SelectedIndexChanged += new System.EventHandler(this.Land_e_capital_SelectedIndexChanged);
            this.Land_e_capital.DropDown += new System.EventHandler(this.Land_e_capital_SelectedIndexChanged);
            // 
            // Land_l_capital
            // 
            this.Land_l_capital.Location = new System.Drawing.Point(8, 16);
            this.Land_l_capital.Name = "Land_l_capital";
            this.Land_l_capital.Size = new System.Drawing.Size(100, 16);
            this.Land_l_capital.TabIndex = 2;
            this.Land_l_capital.Text = "Capital city";
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
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 392);
            this.TDB_abgrp.Name = "TDB_abgrp";
            this.TDB_abgrp.Size = new System.Drawing.Size(640, 53);
            this.TDB_abgrp.TabIndex = 15;
            this.TDB_abgrp.TabStop = false;
            this.TDB_abgrp.Text = "Actions";
            // 
            // TDB_ab_clr
            // 
            this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_clr.Location = new System.Drawing.Point(487, 16);
            this.TDB_ab_clr.Name = "TDB_ab_clr";
            this.TDB_ab_clr.Size = new System.Drawing.Size(75, 34);
            this.TDB_ab_clr.TabIndex = 10;
            this.TDB_ab_clr.Text = "Clear";
            this.TDB_ab_clr.Click += new System.EventHandler(this.TDB_ab_clr_Click);
            // 
            // TDB_ab_sel
            // 
            this.TDB_ab_sel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(192)))), ((int)(((byte)(255)))));
            this.TDB_ab_sel.Dock = System.Windows.Forms.DockStyle.Left;
            this.TDB_ab_sel.Location = new System.Drawing.Point(228, 16);
            this.TDB_ab_sel.Name = "TDB_ab_sel";
            this.TDB_ab_sel.Size = new System.Drawing.Size(80, 34);
            this.TDB_ab_sel.TabIndex = 8;
            this.TDB_ab_sel.Text = "Select";
            this.TDB_ab_sel.UseVisualStyleBackColor = false;
            this.TDB_ab_sel.Click += new System.EventHandler(this.TDB_ab_sel_Click);
            // 
            // TDB_ab_exit
            // 
            this.TDB_ab_exit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.TDB_ab_exit.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_exit.Location = new System.Drawing.Point(562, 16);
            this.TDB_ab_exit.Name = "TDB_ab_exit";
            this.TDB_ab_exit.Size = new System.Drawing.Size(75, 34);
            this.TDB_ab_exit.TabIndex = 9;
            this.TDB_ab_exit.Text = "Exit";
            this.TDB_ab_exit.UseVisualStyleBackColor = false;
            this.TDB_ab_exit.Click += new System.EventHandler(this.TDB_ab_exit_Click);
            // 
            // TDB_ab_del
            // 
            this.TDB_ab_del.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.TDB_ab_del.Dock = System.Windows.Forms.DockStyle.Left;
            this.TDB_ab_del.Location = new System.Drawing.Point(153, 16);
            this.TDB_ab_del.Name = "TDB_ab_del";
            this.TDB_ab_del.Size = new System.Drawing.Size(75, 34);
            this.TDB_ab_del.TabIndex = 7;
            this.TDB_ab_del.Text = "Delete";
            this.TDB_ab_del.UseVisualStyleBackColor = false;
            this.TDB_ab_del.Click += new System.EventHandler(this.TDB_ab_del_Click);
            // 
            // TDB_ab_upd
            // 
            this.TDB_ab_upd.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.TDB_ab_upd.Dock = System.Windows.Forms.DockStyle.Left;
            this.TDB_ab_upd.Location = new System.Drawing.Point(78, 16);
            this.TDB_ab_upd.Name = "TDB_ab_upd";
            this.TDB_ab_upd.Size = new System.Drawing.Size(75, 34);
            this.TDB_ab_upd.TabIndex = 6;
            this.TDB_ab_upd.Text = "Update";
            this.TDB_ab_upd.UseVisualStyleBackColor = false;
            this.TDB_ab_upd.Click += new System.EventHandler(this.TDB_ab_upd_Click);
            // 
            // TDB_ab_ins
            // 
            this.TDB_ab_ins.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.TDB_ab_ins.Dock = System.Windows.Forms.DockStyle.Left;
            this.TDB_ab_ins.Location = new System.Drawing.Point(3, 16);
            this.TDB_ab_ins.Name = "TDB_ab_ins";
            this.TDB_ab_ins.Size = new System.Drawing.Size(75, 34);
            this.TDB_ab_ins.TabIndex = 5;
            this.TDB_ab_ins.Text = "Insert";
            this.TDB_ab_ins.UseVisualStyleBackColor = false;
            this.TDB_ab_ins.Click += new System.EventHandler(this.TDB_ab_ins_Click);
            // 
            // Land_e_addlang
            // 
            this.Land_e_addlang.Location = new System.Drawing.Point(487, 43);
            this.Land_e_addlang.Name = "Land_e_addlang";
            this.Land_e_addlang.Size = new System.Drawing.Size(126, 23);
            this.Land_e_addlang.TabIndex = 12;
            this.Land_e_addlang.Text = "Additional languages";
            this.Land_e_addlang.UseVisualStyleBackColor = true;
            // 
            // FCountry
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(640, 445);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "FCountry";
            this.Text = "Country";
            this.Load += new System.EventHandler(this.Country_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			Ctry.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			Ctry.Get(id, ref rows);
			tdb_e_id.Text = Ctry.ObjId.ToString();
			tdb_e_bez.Text = Ctry.ObjBez;
			tdb_e_code.Text = Ctry.ObjCode;
			tdb_e_text.Text = Ctry.ObjText;
			// first add items and AFTERWARDS the text !!
			this.Land_e_capital.SelectedValue = Ctry.ObjCapid;
			this.Land_e_cur.SelectedValue = Ctry.ObjCurid;
			this.Land_e_lang.SelectedValue = Ctry.ObjLangid;
			this.Land_e_vat.Text = Ctry.ObjVat.ToString();
			this.Land_e_dateformat.Text = Ctry.ObjDateformat;
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			Ctry.InsUpd(true, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text,
				(int)this.Land_e_capital.SelectedValue, (int)this.Land_e_cur.SelectedValue,
				(int)this.Land_e_lang.SelectedValue, Convert.ToDouble(this.Land_e_vat.Text),
				this.Land_e_dateformat.Text);
			tdb_e_id.Text = Ctry.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			Ctry.InsUpd(false, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text,
				(int)this.Land_e_capital.SelectedValue, (int)this.Land_e_cur.SelectedValue,
				(int)this.Land_e_lang.SelectedValue, Convert.ToDouble(this.Land_e_vat.Text),
				this.Land_e_dateformat.Text);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			Ctry.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			Ctry.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_code.Text = "";
			tdb_e_text.Text = "";
			Land_e_vat.Text = "0";
			Land_e_dateformat.Text = "";
		}
		private void Country_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIcity C = new tdbgui.GUIcity();
			C.SetCombo(this.Land_e_capital);

			tdbgui.GUIlang L = new tdbgui.GUIlang();
			L.SetCombo(this.Land_e_lang);

			tdbgui.GUIcur Cur = new tdbgui.GUIcur();
			Cur.SetCombo(this.Land_e_cur);
		}


		#endregion

		private void Land_e_capital_SelectedIndexChanged(object sender, System.EventArgs e)
		{
		}

	}
}
