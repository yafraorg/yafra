using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for Country.
	/// </summary>
	public class FCustomer : System.Windows.Forms.Form
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
		private System.Windows.Forms.TextBox tdb_e_text;
		private System.Windows.Forms.Label tdb_l_text;
		private System.Windows.Forms.Label tdb_l_id;
		private System.Windows.Forms.TextBox Kun_e_name;
		private System.Windows.Forms.Label Kun_l_name;
		private System.Windows.Forms.Label Kun_l_lang;
		private System.Windows.Forms.Label Kun_l_cur;
		private System.Windows.Forms.ComboBox Kun_e_cur;
		private System.Windows.Forms.ComboBox Kun_e_lang;
		private System.Windows.Forms.Label Kun_l_tel;
		private System.Windows.Forms.Label Kun_l_handy;
		private System.Windows.Forms.Label Kun_l_fax;
		private System.Windows.Forms.Label Kun_l_tlx;
		private System.Windows.Forms.Label Kun_l_email;
		private System.Windows.Forms.Label Kun_l_web;
		private System.Windows.Forms.Label Kun_l_konto;
		private System.Windows.Forms.Label Kun_l_leiter;
		private System.Windows.Forms.TextBox Kun_e_tel;
		private System.Windows.Forms.TextBox Kun_e_handy;
		private System.Windows.Forms.TextBox Kun_e_fax;
		private System.Windows.Forms.TextBox Kun_e_tlx;
		private System.Windows.Forms.TextBox Kun_e_email;
		private System.Windows.Forms.TextBox Kun_e_www;
		private System.Windows.Forms.TextBox Kun_e_konto;
		private System.Windows.Forms.TextBox Kun_e_leiter;
		private System.Windows.Forms.Label Kun_l_attr1;
		private System.Windows.Forms.Label Kun_l_attr2;
		private System.Windows.Forms.TextBox Kun_e_attr1;
		private System.Windows.Forms.TextBox Kun_e_attr2;
		private System.Windows.Forms.ComboBox Kun_e_kunt;
		private System.Windows.Forms.Label Kun_l_kunt;
		private System.Windows.Forms.ComboBox Kun_e_sta;
		private System.Windows.Forms.Label Kun_l_sta;
		private System.Windows.Forms.Button Kun_b_email;
		private System.Windows.Forms.Button Kun_b_www;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.DataGrid Kun_e_adr;
		private tdb.DS.PersonAdrDS personAdrDS;
		private tdbgui.GUIcust Cust;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FCustomer()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Cust = new tdbgui.GUIcust();
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
			this.Kun_b_www = new System.Windows.Forms.Button();
			this.Kun_b_email = new System.Windows.Forms.Button();
			this.Kun_e_sta = new System.Windows.Forms.ComboBox();
			this.Kun_l_sta = new System.Windows.Forms.Label();
			this.Kun_e_kunt = new System.Windows.Forms.ComboBox();
			this.Kun_l_kunt = new System.Windows.Forms.Label();
			this.Kun_e_attr2 = new System.Windows.Forms.TextBox();
			this.Kun_e_attr1 = new System.Windows.Forms.TextBox();
			this.Kun_l_attr2 = new System.Windows.Forms.Label();
			this.Kun_l_attr1 = new System.Windows.Forms.Label();
			this.Kun_e_leiter = new System.Windows.Forms.TextBox();
			this.Kun_e_konto = new System.Windows.Forms.TextBox();
			this.Kun_e_www = new System.Windows.Forms.TextBox();
			this.Kun_e_email = new System.Windows.Forms.TextBox();
			this.Kun_e_tlx = new System.Windows.Forms.TextBox();
			this.Kun_e_fax = new System.Windows.Forms.TextBox();
			this.Kun_e_handy = new System.Windows.Forms.TextBox();
			this.Kun_e_tel = new System.Windows.Forms.TextBox();
			this.Kun_l_leiter = new System.Windows.Forms.Label();
			this.Kun_l_konto = new System.Windows.Forms.Label();
			this.Kun_l_web = new System.Windows.Forms.Label();
			this.Kun_l_email = new System.Windows.Forms.Label();
			this.Kun_l_tlx = new System.Windows.Forms.Label();
			this.Kun_l_fax = new System.Windows.Forms.Label();
			this.Kun_l_handy = new System.Windows.Forms.Label();
			this.Kun_l_tel = new System.Windows.Forms.Label();
			this.tdb_e_id = new System.Windows.Forms.Label();
			this.Kun_e_name = new System.Windows.Forms.TextBox();
			this.tdb_e_text = new System.Windows.Forms.TextBox();
			this.tdb_l_text = new System.Windows.Forms.Label();
			this.Kun_l_name = new System.Windows.Forms.Label();
			this.tdb_l_id = new System.Windows.Forms.Label();
			this.Kun_l_lang = new System.Windows.Forms.Label();
			this.Kun_e_lang = new System.Windows.Forms.ComboBox();
			this.Kun_e_cur = new System.Windows.Forms.ComboBox();
			this.Kun_l_cur = new System.Windows.Forms.Label();
			this.TDB_abgrp = new System.Windows.Forms.GroupBox();
			this.TDB_ab_clr = new System.Windows.Forms.Button();
			this.TDB_ab_sel = new System.Windows.Forms.Button();
			this.TDB_ab_exit = new System.Windows.Forms.Button();
			this.TDB_ab_del = new System.Windows.Forms.Button();
			this.TDB_ab_upd = new System.Windows.Forms.Button();
			this.TDB_ab_ins = new System.Windows.Forms.Button();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Kun_e_adr = new System.Windows.Forms.DataGrid();
			this.personAdrDS = new tdb.DS.PersonAdrDS();
			this.groupBox1.SuspendLayout();
			this.TDB_abgrp.SuspendLayout();
			this.groupBox2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.Kun_e_adr)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.personAdrDS)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Kun_b_www);
			this.groupBox1.Controls.Add(this.Kun_b_email);
			this.groupBox1.Controls.Add(this.Kun_e_sta);
			this.groupBox1.Controls.Add(this.Kun_l_sta);
			this.groupBox1.Controls.Add(this.Kun_e_kunt);
			this.groupBox1.Controls.Add(this.Kun_l_kunt);
			this.groupBox1.Controls.Add(this.Kun_e_attr2);
			this.groupBox1.Controls.Add(this.Kun_e_attr1);
			this.groupBox1.Controls.Add(this.Kun_l_attr2);
			this.groupBox1.Controls.Add(this.Kun_l_attr1);
			this.groupBox1.Controls.Add(this.Kun_e_leiter);
			this.groupBox1.Controls.Add(this.Kun_e_konto);
			this.groupBox1.Controls.Add(this.Kun_e_www);
			this.groupBox1.Controls.Add(this.Kun_e_email);
			this.groupBox1.Controls.Add(this.Kun_e_tlx);
			this.groupBox1.Controls.Add(this.Kun_e_fax);
			this.groupBox1.Controls.Add(this.Kun_e_handy);
			this.groupBox1.Controls.Add(this.Kun_e_tel);
			this.groupBox1.Controls.Add(this.Kun_l_leiter);
			this.groupBox1.Controls.Add(this.Kun_l_konto);
			this.groupBox1.Controls.Add(this.Kun_l_web);
			this.groupBox1.Controls.Add(this.Kun_l_email);
			this.groupBox1.Controls.Add(this.Kun_l_tlx);
			this.groupBox1.Controls.Add(this.Kun_l_fax);
			this.groupBox1.Controls.Add(this.Kun_l_handy);
			this.groupBox1.Controls.Add(this.Kun_l_tel);
			this.groupBox1.Controls.Add(this.tdb_e_id);
			this.groupBox1.Controls.Add(this.Kun_e_name);
			this.groupBox1.Controls.Add(this.tdb_e_text);
			this.groupBox1.Controls.Add(this.tdb_l_text);
			this.groupBox1.Controls.Add(this.Kun_l_name);
			this.groupBox1.Controls.Add(this.tdb_l_id);
			this.groupBox1.Controls.Add(this.Kun_l_lang);
			this.groupBox1.Controls.Add(this.Kun_e_lang);
			this.groupBox1.Controls.Add(this.Kun_e_cur);
			this.groupBox1.Controls.Add(this.Kun_l_cur);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(728, 328);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Kun_b_www
			// 
			this.Kun_b_www.Location = new System.Drawing.Point(696, 136);
			this.Kun_b_www.Name = "Kun_b_www";
			this.Kun_b_www.Size = new System.Drawing.Size(24, 23);
			this.Kun_b_www.TabIndex = 37;
			this.Kun_b_www.Text = "W";
			this.Kun_b_www.Click += new System.EventHandler(this.Kun_b_www_Click);
			// 
			// Kun_b_email
			// 
			this.Kun_b_email.Location = new System.Drawing.Point(696, 112);
			this.Kun_b_email.Name = "Kun_b_email";
			this.Kun_b_email.Size = new System.Drawing.Size(24, 23);
			this.Kun_b_email.TabIndex = 36;
			this.Kun_b_email.Text = "M";
			this.Kun_b_email.Click += new System.EventHandler(this.Kun_b_email_Click);
			// 
			// Kun_e_sta
			// 
			this.Kun_e_sta.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.Kun_e_sta.Location = new System.Drawing.Point(448, 240);
			this.Kun_e_sta.Name = "Kun_e_sta";
			this.Kun_e_sta.Size = new System.Drawing.Size(240, 21);
			this.Kun_e_sta.TabIndex = 34;
			// 
			// Kun_l_sta
			// 
			this.Kun_l_sta.Location = new System.Drawing.Point(360, 240);
			this.Kun_l_sta.Name = "Kun_l_sta";
			this.Kun_l_sta.Size = new System.Drawing.Size(64, 16);
			this.Kun_l_sta.TabIndex = 35;
			this.Kun_l_sta.Text = "Status";
			// 
			// Kun_e_kunt
			// 
			this.Kun_e_kunt.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.Kun_e_kunt.Location = new System.Drawing.Point(448, 72);
			this.Kun_e_kunt.Name = "Kun_e_kunt";
			this.Kun_e_kunt.Size = new System.Drawing.Size(240, 21);
			this.Kun_e_kunt.TabIndex = 32;
			// 
			// Kun_l_kunt
			// 
			this.Kun_l_kunt.Location = new System.Drawing.Point(360, 72);
			this.Kun_l_kunt.Name = "Kun_l_kunt";
			this.Kun_l_kunt.Size = new System.Drawing.Size(72, 16);
			this.Kun_l_kunt.TabIndex = 33;
			this.Kun_l_kunt.Text = "Type";
			// 
			// Kun_e_attr2
			// 
			this.Kun_e_attr2.Location = new System.Drawing.Point(448, 208);
			this.Kun_e_attr2.Name = "Kun_e_attr2";
			this.Kun_e_attr2.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_attr2.TabIndex = 31;
			this.Kun_e_attr2.Text = "";
			// 
			// Kun_e_attr1
			// 
			this.Kun_e_attr1.Location = new System.Drawing.Point(96, 208);
			this.Kun_e_attr1.Name = "Kun_e_attr1";
			this.Kun_e_attr1.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_attr1.TabIndex = 30;
			this.Kun_e_attr1.Text = "";
			// 
			// Kun_l_attr2
			// 
			this.Kun_l_attr2.Location = new System.Drawing.Point(360, 208);
			this.Kun_l_attr2.Name = "Kun_l_attr2";
			this.Kun_l_attr2.Size = new System.Drawing.Size(88, 23);
			this.Kun_l_attr2.TabIndex = 29;
			this.Kun_l_attr2.Text = "Free field 2";
			// 
			// Kun_l_attr1
			// 
			this.Kun_l_attr1.Location = new System.Drawing.Point(8, 208);
			this.Kun_l_attr1.Name = "Kun_l_attr1";
			this.Kun_l_attr1.Size = new System.Drawing.Size(72, 23);
			this.Kun_l_attr1.TabIndex = 28;
			this.Kun_l_attr1.Text = "Free field 1";
			// 
			// Kun_e_leiter
			// 
			this.Kun_e_leiter.Location = new System.Drawing.Point(448, 184);
			this.Kun_e_leiter.Name = "Kun_e_leiter";
			this.Kun_e_leiter.Size = new System.Drawing.Size(24, 20);
			this.Kun_e_leiter.TabIndex = 27;
			this.Kun_e_leiter.Text = "";
			// 
			// Kun_e_konto
			// 
			this.Kun_e_konto.Location = new System.Drawing.Point(448, 160);
			this.Kun_e_konto.Name = "Kun_e_konto";
			this.Kun_e_konto.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_konto.TabIndex = 26;
			this.Kun_e_konto.Text = "";
			// 
			// Kun_e_www
			// 
			this.Kun_e_www.Location = new System.Drawing.Point(448, 136);
			this.Kun_e_www.Name = "Kun_e_www";
			this.Kun_e_www.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_www.TabIndex = 25;
			this.Kun_e_www.Text = "";
			// 
			// Kun_e_email
			// 
			this.Kun_e_email.Location = new System.Drawing.Point(448, 112);
			this.Kun_e_email.Name = "Kun_e_email";
			this.Kun_e_email.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_email.TabIndex = 24;
			this.Kun_e_email.Text = "";
			// 
			// Kun_e_tlx
			// 
			this.Kun_e_tlx.Location = new System.Drawing.Point(96, 184);
			this.Kun_e_tlx.Name = "Kun_e_tlx";
			this.Kun_e_tlx.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_tlx.TabIndex = 23;
			this.Kun_e_tlx.Text = "";
			// 
			// Kun_e_fax
			// 
			this.Kun_e_fax.Location = new System.Drawing.Point(96, 160);
			this.Kun_e_fax.Name = "Kun_e_fax";
			this.Kun_e_fax.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_fax.TabIndex = 22;
			this.Kun_e_fax.Text = "";
			// 
			// Kun_e_handy
			// 
			this.Kun_e_handy.Location = new System.Drawing.Point(96, 136);
			this.Kun_e_handy.Name = "Kun_e_handy";
			this.Kun_e_handy.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_handy.TabIndex = 21;
			this.Kun_e_handy.Text = "";
			// 
			// Kun_e_tel
			// 
			this.Kun_e_tel.Location = new System.Drawing.Point(96, 112);
			this.Kun_e_tel.Name = "Kun_e_tel";
			this.Kun_e_tel.Size = new System.Drawing.Size(240, 20);
			this.Kun_e_tel.TabIndex = 20;
			this.Kun_e_tel.Text = "";
			// 
			// Kun_l_leiter
			// 
			this.Kun_l_leiter.Location = new System.Drawing.Point(360, 184);
			this.Kun_l_leiter.Name = "Kun_l_leiter";
			this.Kun_l_leiter.Size = new System.Drawing.Size(88, 23);
			this.Kun_l_leiter.TabIndex = 19;
			this.Kun_l_leiter.Text = "Manager";
			// 
			// Kun_l_konto
			// 
			this.Kun_l_konto.Location = new System.Drawing.Point(360, 160);
			this.Kun_l_konto.Name = "Kun_l_konto";
			this.Kun_l_konto.Size = new System.Drawing.Size(88, 23);
			this.Kun_l_konto.TabIndex = 18;
			this.Kun_l_konto.Text = "Account No";
			// 
			// Kun_l_web
			// 
			this.Kun_l_web.Location = new System.Drawing.Point(360, 136);
			this.Kun_l_web.Name = "Kun_l_web";
			this.Kun_l_web.Size = new System.Drawing.Size(88, 23);
			this.Kun_l_web.TabIndex = 17;
			this.Kun_l_web.Text = "WWW Address";
			// 
			// Kun_l_email
			// 
			this.Kun_l_email.Location = new System.Drawing.Point(360, 112);
			this.Kun_l_email.Name = "Kun_l_email";
			this.Kun_l_email.Size = new System.Drawing.Size(88, 23);
			this.Kun_l_email.TabIndex = 16;
			this.Kun_l_email.Text = "E-Mail";
			// 
			// Kun_l_tlx
			// 
			this.Kun_l_tlx.Location = new System.Drawing.Point(8, 184);
			this.Kun_l_tlx.Name = "Kun_l_tlx";
			this.Kun_l_tlx.Size = new System.Drawing.Size(56, 23);
			this.Kun_l_tlx.TabIndex = 15;
			this.Kun_l_tlx.Text = "Telex";
			// 
			// Kun_l_fax
			// 
			this.Kun_l_fax.Location = new System.Drawing.Point(8, 160);
			this.Kun_l_fax.Name = "Kun_l_fax";
			this.Kun_l_fax.Size = new System.Drawing.Size(64, 23);
			this.Kun_l_fax.TabIndex = 14;
			this.Kun_l_fax.Text = "Fax";
			// 
			// Kun_l_handy
			// 
			this.Kun_l_handy.Location = new System.Drawing.Point(8, 136);
			this.Kun_l_handy.Name = "Kun_l_handy";
			this.Kun_l_handy.Size = new System.Drawing.Size(64, 23);
			this.Kun_l_handy.TabIndex = 13;
			this.Kun_l_handy.Text = "Handy";
			// 
			// Kun_l_tel
			// 
			this.Kun_l_tel.Location = new System.Drawing.Point(8, 112);
			this.Kun_l_tel.Name = "Kun_l_tel";
			this.Kun_l_tel.Size = new System.Drawing.Size(64, 23);
			this.Kun_l_tel.TabIndex = 12;
			this.Kun_l_tel.Text = "Phone";
			// 
			// tdb_e_id
			// 
			this.tdb_e_id.Location = new System.Drawing.Point(96, 24);
			this.tdb_e_id.Name = "tdb_e_id";
			this.tdb_e_id.Size = new System.Drawing.Size(64, 16);
			this.tdb_e_id.TabIndex = 9;
			// 
			// Kun_e_name
			// 
			this.Kun_e_name.Location = new System.Drawing.Point(96, 40);
			this.Kun_e_name.Name = "Kun_e_name";
			this.Kun_e_name.Size = new System.Drawing.Size(592, 20);
			this.Kun_e_name.TabIndex = 0;
			this.Kun_e_name.Text = "";
			// 
			// tdb_e_text
			// 
			this.tdb_e_text.Location = new System.Drawing.Point(96, 272);
			this.tdb_e_text.Multiline = true;
			this.tdb_e_text.Name = "tdb_e_text";
			this.tdb_e_text.Size = new System.Drawing.Size(592, 48);
			this.tdb_e_text.TabIndex = 2;
			this.tdb_e_text.Text = "";
			// 
			// tdb_l_text
			// 
			this.tdb_l_text.Location = new System.Drawing.Point(8, 280);
			this.tdb_l_text.Name = "tdb_l_text";
			this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.tdb_l_text.Size = new System.Drawing.Size(64, 23);
			this.tdb_l_text.TabIndex = 4;
			this.tdb_l_text.Text = "Description";
			// 
			// Kun_l_name
			// 
			this.Kun_l_name.Location = new System.Drawing.Point(8, 39);
			this.Kun_l_name.Name = "Kun_l_name";
			this.Kun_l_name.Size = new System.Drawing.Size(72, 23);
			this.Kun_l_name.TabIndex = 2;
			this.Kun_l_name.Text = "Name";
			// 
			// tdb_l_id
			// 
			this.tdb_l_id.Location = new System.Drawing.Point(8, 21);
			this.tdb_l_id.Name = "tdb_l_id";
			this.tdb_l_id.Size = new System.Drawing.Size(64, 23);
			this.tdb_l_id.TabIndex = 1;
			this.tdb_l_id.Text = "ID";
			// 
			// Kun_l_lang
			// 
			this.Kun_l_lang.Location = new System.Drawing.Point(8, 72);
			this.Kun_l_lang.Name = "Kun_l_lang";
			this.Kun_l_lang.Size = new System.Drawing.Size(72, 16);
			this.Kun_l_lang.TabIndex = 9;
			this.Kun_l_lang.Text = "Language";
			// 
			// Kun_e_lang
			// 
			this.Kun_e_lang.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.Kun_e_lang.Location = new System.Drawing.Point(96, 72);
			this.Kun_e_lang.Name = "Kun_e_lang";
			this.Kun_e_lang.Size = new System.Drawing.Size(240, 21);
			this.Kun_e_lang.TabIndex = 4;
			// 
			// Kun_e_cur
			// 
			this.Kun_e_cur.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.Kun_e_cur.Location = new System.Drawing.Point(96, 240);
			this.Kun_e_cur.Name = "Kun_e_cur";
			this.Kun_e_cur.Size = new System.Drawing.Size(240, 21);
			this.Kun_e_cur.TabIndex = 5;
			// 
			// Kun_l_cur
			// 
			this.Kun_l_cur.Location = new System.Drawing.Point(8, 240);
			this.Kun_l_cur.Name = "Kun_l_cur";
			this.Kun_l_cur.Size = new System.Drawing.Size(80, 16);
			this.Kun_l_cur.TabIndex = 8;
			this.Kun_l_cur.Text = "Currency";
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
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 472);
			this.TDB_abgrp.Name = "TDB_abgrp";
			this.TDB_abgrp.Size = new System.Drawing.Size(728, 53);
			this.TDB_abgrp.TabIndex = 15;
			this.TDB_abgrp.TabStop = false;
			this.TDB_abgrp.Text = "Actions";
			// 
			// TDB_ab_clr
			// 
			this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
			this.TDB_ab_clr.Location = new System.Drawing.Point(575, 16);
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
			this.TDB_ab_exit.Location = new System.Drawing.Point(650, 16);
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
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Kun_e_adr);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.groupBox2.Location = new System.Drawing.Point(0, 328);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(728, 144);
			this.groupBox2.TabIndex = 16;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Addresses";
			// 
			// Kun_e_adr
			// 
			this.Kun_e_adr.DataMember = "";
			this.Kun_e_adr.DataSource = this.personAdrDS.persadr;
			this.Kun_e_adr.Dock = System.Windows.Forms.DockStyle.Fill;
			this.Kun_e_adr.HeaderForeColor = System.Drawing.SystemColors.ControlText;
			this.Kun_e_adr.Location = new System.Drawing.Point(3, 16);
			this.Kun_e_adr.Name = "Kun_e_adr";
			this.Kun_e_adr.Size = new System.Drawing.Size(722, 125);
			this.Kun_e_adr.TabIndex = 0;
			// 
			// personAdrDS
			// 
			this.personAdrDS.DataSetName = "PersonAdrDS";
			this.personAdrDS.Locale = new System.Globalization.CultureInfo("en-US");
			// 
			// FCustomer
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(728, 525);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FCustomer";
			this.Text = "Customer";
			this.Load += new System.EventHandler(this.FCustomer_Load);
			this.groupBox1.ResumeLayout(false);
			this.TDB_abgrp.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.Kun_e_adr)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.personAdrDS)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			Cust.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			Cust.Get(id, ref rows);
			tdb_e_id.Text = Cust.ObjId.ToString();
			Kun_e_name.Text = Cust.ObjCode;
			tdb_e_text.Text = Cust.ObjText;
			this.Kun_e_cur.SelectedValue = Cust.ObjCurid;
			this.Kun_e_sta.SelectedValue = Cust.ObjStaid;
			this.Kun_e_lang.SelectedValue = Cust.ObjLangid;
			this.Kun_e_kunt.SelectedValue = Cust.ObjCusttypid;
			Kun_e_tel.Text = Cust.ObjTel;
			Kun_e_handy.Text = Cust.ObjHandy;
			Kun_e_fax.Text = Cust.ObjFax;
			Kun_e_tlx.Text = Cust.ObjTlx;
			Kun_e_email.Text = Cust.ObjMail;
			Kun_e_www.Text = Cust.ObjWww;
			Kun_e_konto.Text = Cust.ObjAcc;
			Kun_e_attr1.Text = Cust.ObjA1;
			Kun_e_attr2.Text = Cust.ObjA2;

			// get all addresses for this customer
			string sql;
			this.personAdrDS.Clear();
			sql = String.Format("Select * from tdbadmin.persadr where pers_id = {0}", id);
			tdb.User.Uhelper.FillDataset(tdb.User.Udbcon, CommandType.Text, sql, this.personAdrDS, new string[] { "persadr" } );
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			Cust.InsUpd(true, this.Kun_e_name.Text, 
				(int)this.Kun_e_lang.SelectedValue,
				(int)this.Kun_e_kunt.SelectedValue,
				Kun_e_tel.Text, Kun_e_handy.Text, Kun_e_fax.Text, Kun_e_tlx.Text,
				Kun_e_email.Text, Kun_e_www.Text, (int)-1, Kun_e_konto.Text,
				Kun_e_attr1.Text, Kun_e_attr2.Text,
				(int)this.Kun_e_cur.SelectedValue,
				(int)this.Kun_e_sta.SelectedValue,
				tdb_e_text.Text);
			tdb_e_id.Text = Cust.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			Cust.InsUpd(false, this.Kun_e_name.Text, 
				(int)this.Kun_e_lang.SelectedValue,
				(int)this.Kun_e_kunt.SelectedValue,
				Kun_e_tel.Text, Kun_e_handy.Text, Kun_e_fax.Text, Kun_e_tlx.Text,
				Kun_e_email.Text, Kun_e_www.Text, (int)-1, Kun_e_konto.Text,
				Kun_e_attr1.Text, Kun_e_attr2.Text,
				(int)this.Kun_e_cur.SelectedValue,
				(int)this.Kun_e_sta.SelectedValue,
				tdb_e_text.Text);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			Cust.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			Cust.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_text.Text = "";
			this.Kun_e_name.Text = "";
			Kun_e_tel.Text = "";
			Kun_e_handy.Text = "";
			Kun_e_fax.Text = "";
			Kun_e_tlx.Text = "";
			Kun_e_email.Text = "";
			Kun_e_www.Text = "";
			Kun_e_konto.Text = "";
			Kun_e_attr1.Text = "";
			Kun_e_attr2.Text = "";
		}
		private void FCustomer_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIcustt CT = new tdbgui.GUIcustt();
			CT.SetCombo(this.Kun_e_kunt);

			tdbgui.GUIlang L = new tdbgui.GUIlang();
			L.SetCombo(this.Kun_e_lang);

			tdbgui.GUIcur Cur = new tdbgui.GUIcur();
			Cur.SetCombo(this.Kun_e_cur);

			tdbgui.GUIsta S = new tdbgui.GUIsta();
			S.ObjTyp = tdb.StatusTypes.personen;
			S.SetCombo(this.Kun_e_sta);
		}

		#endregion


		private void Kun_b_email_Click(object sender, System.EventArgs e)
		{
		
		}


		private void Kun_b_www_Click(object sender, System.EventArgs e)
		{
		
		}

	}
}
