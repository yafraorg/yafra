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
	/// offer Form.
	/// </summary>
	public class FServiceoffer : System.Windows.Forms.Form
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
		private System.Windows.Forms.CheckBox Off_e_ishost;
		private System.Windows.Forms.Label Off_l_dlt;
		private System.Windows.Forms.ComboBox Off_e_parent;
		private System.Windows.Forms.Label Off_l_parent;
		private System.Windows.Forms.ComboBox Off_e_dlt;
        private System.Windows.Forms.Label Off_l_ord;
		private System.Windows.Forms.TextBox tdb_e_code;
		private System.Windows.Forms.Label tdb_l_code;
        private ComboBox Off_e_act;
        private Label Off_l_act;
        private ComboBox Off_e_offtype;
        private Label Off_l_offtype;
        private Label Off_l_dur;
        private NumericUpDown Off_e_ord;
        private TextBox Off_e_location;
        private Label Off_l_loc;
        private ComboBox Off_e_from;
        private Label Off_l_from;
        private Button Off_b_createserv;
        private DateTimePicker Off_e_duration;
        private DateTimePicker Off_e_enddate;
        private Label label1;
        private ComboBox comboBox1;
        private Label label2;
        private bool ishost;
        private tdbgui.GUIoffer offer;
        private tdbgui.GUIserviceoffer serviceoffer;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FServiceoffer()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			offer = new tdbgui.GUIoffer();
            serviceoffer = new tdbgui.GUIserviceoffer();
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
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.Off_e_enddate = new System.Windows.Forms.DateTimePicker();
            this.label1 = new System.Windows.Forms.Label();
            this.Off_e_duration = new System.Windows.Forms.DateTimePicker();
            this.Off_b_createserv = new System.Windows.Forms.Button();
            this.Off_e_location = new System.Windows.Forms.TextBox();
            this.Off_l_loc = new System.Windows.Forms.Label();
            this.Off_e_from = new System.Windows.Forms.ComboBox();
            this.Off_l_from = new System.Windows.Forms.Label();
            this.Off_l_dur = new System.Windows.Forms.Label();
            this.Off_e_ord = new System.Windows.Forms.NumericUpDown();
            this.Off_e_offtype = new System.Windows.Forms.ComboBox();
            this.Off_l_offtype = new System.Windows.Forms.Label();
            this.Off_e_act = new System.Windows.Forms.ComboBox();
            this.Off_l_act = new System.Windows.Forms.Label();
            this.tdb_e_code = new System.Windows.Forms.TextBox();
            this.tdb_l_code = new System.Windows.Forms.Label();
            this.Off_l_ord = new System.Windows.Forms.Label();
            this.Off_e_dlt = new System.Windows.Forms.ComboBox();
            this.Off_e_ishost = new System.Windows.Forms.CheckBox();
            this.Off_l_dlt = new System.Windows.Forms.Label();
            this.Off_e_parent = new System.Windows.Forms.ComboBox();
            this.Off_l_parent = new System.Windows.Forms.Label();
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
            ((System.ComponentModel.ISupportInitialize)(this.Off_e_ord)).BeginInit();
            this.TDB_abgrp.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.comboBox1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.Off_e_enddate);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.Off_e_duration);
            this.groupBox1.Controls.Add(this.Off_b_createserv);
            this.groupBox1.Controls.Add(this.Off_e_location);
            this.groupBox1.Controls.Add(this.Off_l_loc);
            this.groupBox1.Controls.Add(this.Off_e_from);
            this.groupBox1.Controls.Add(this.Off_l_from);
            this.groupBox1.Controls.Add(this.Off_l_dur);
            this.groupBox1.Controls.Add(this.Off_e_ord);
            this.groupBox1.Controls.Add(this.Off_e_offtype);
            this.groupBox1.Controls.Add(this.Off_l_offtype);
            this.groupBox1.Controls.Add(this.Off_e_act);
            this.groupBox1.Controls.Add(this.Off_l_act);
            this.groupBox1.Controls.Add(this.tdb_e_code);
            this.groupBox1.Controls.Add(this.tdb_l_code);
            this.groupBox1.Controls.Add(this.Off_l_ord);
            this.groupBox1.Controls.Add(this.Off_e_dlt);
            this.groupBox1.Controls.Add(this.Off_e_ishost);
            this.groupBox1.Controls.Add(this.Off_l_dlt);
            this.groupBox1.Controls.Add(this.Off_e_parent);
            this.groupBox1.Controls.Add(this.Off_l_parent);
            this.groupBox1.Controls.Add(this.tdb_e_id);
            this.groupBox1.Controls.Add(this.tdb_e_bez);
            this.groupBox1.Controls.Add(this.tdb_e_text);
            this.groupBox1.Controls.Add(this.tdb_l_text);
            this.groupBox1.Controls.Add(this.tdb_l_bez);
            this.groupBox1.Controls.Add(this.tdb_l_id);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(620, 452);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Description";
            // 
            // comboBox1
            // 
            this.comboBox1.Location = new System.Drawing.Point(136, 373);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(248, 21);
            this.comboBox1.TabIndex = 38;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(8, 373);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(122, 23);
            this.label2.TabIndex = 37;
            this.label2.Text = "Season";
            // 
            // Off_e_enddate
            // 
            this.Off_e_enddate.CustomFormat = "dd.MM.yyyy HH:mm";
            this.Off_e_enddate.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.Off_e_enddate.Location = new System.Drawing.Point(432, 347);
            this.Off_e_enddate.Name = "Off_e_enddate";
            this.Off_e_enddate.Size = new System.Drawing.Size(118, 20);
            this.Off_e_enddate.TabIndex = 36;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(304, 351);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 23);
            this.label1.TabIndex = 35;
            this.label1.Text = "End date";
            // 
            // Off_e_duration
            // 
            this.Off_e_duration.CustomFormat = "dd.MM.yyyy HH:mm";
            this.Off_e_duration.Format = System.Windows.Forms.DateTimePickerFormat.Custom;
            this.Off_e_duration.Location = new System.Drawing.Point(136, 347);
            this.Off_e_duration.Name = "Off_e_duration";
            this.Off_e_duration.Size = new System.Drawing.Size(118, 20);
            this.Off_e_duration.TabIndex = 34;
            // 
            // Off_b_createserv
            // 
            this.Off_b_createserv.Enabled = false;
            this.Off_b_createserv.Location = new System.Drawing.Point(518, 373);
            this.Off_b_createserv.Name = "Off_b_createserv";
            this.Off_b_createserv.Size = new System.Drawing.Size(96, 23);
            this.Off_b_createserv.TabIndex = 33;
            this.Off_b_createserv.Text = "Map to service";
            this.Off_b_createserv.UseVisualStyleBackColor = true;
            this.Off_b_createserv.Click += new System.EventHandler(this.Off_b_createserv_Click);
            // 
            // Off_e_location
            // 
            this.Off_e_location.Location = new System.Drawing.Point(136, 294);
            this.Off_e_location.Name = "Off_e_location";
            this.Off_e_location.Size = new System.Drawing.Size(248, 20);
            this.Off_e_location.TabIndex = 31;
            // 
            // Off_l_loc
            // 
            this.Off_l_loc.Location = new System.Drawing.Point(8, 297);
            this.Off_l_loc.Name = "Off_l_loc";
            this.Off_l_loc.Size = new System.Drawing.Size(100, 23);
            this.Off_l_loc.TabIndex = 32;
            this.Off_l_loc.Text = "Account no";
            // 
            // Off_e_from
            // 
            this.Off_e_from.Location = new System.Drawing.Point(136, 320);
            this.Off_e_from.Name = "Off_e_from";
            this.Off_e_from.Size = new System.Drawing.Size(248, 21);
            this.Off_e_from.TabIndex = 28;
            // 
            // Off_l_from
            // 
            this.Off_l_from.Location = new System.Drawing.Point(8, 323);
            this.Off_l_from.Name = "Off_l_from";
            this.Off_l_from.Size = new System.Drawing.Size(85, 23);
            this.Off_l_from.TabIndex = 27;
            this.Off_l_from.Text = "Invoice from";
            // 
            // Off_l_dur
            // 
            this.Off_l_dur.Location = new System.Drawing.Point(8, 351);
            this.Off_l_dur.Name = "Off_l_dur";
            this.Off_l_dur.Size = new System.Drawing.Size(70, 23);
            this.Off_l_dur.TabIndex = 25;
            this.Off_l_dur.Text = "Start date";
            // 
            // Off_e_ord
            // 
            this.Off_e_ord.Location = new System.Drawing.Point(498, 236);
            this.Off_e_ord.Name = "Off_e_ord";
            this.Off_e_ord.Size = new System.Drawing.Size(36, 20);
            this.Off_e_ord.TabIndex = 24;
            // 
            // Off_e_offtype
            // 
            this.Off_e_offtype.Location = new System.Drawing.Point(136, 215);
            this.Off_e_offtype.Name = "Off_e_offtype";
            this.Off_e_offtype.Size = new System.Drawing.Size(248, 21);
            this.Off_e_offtype.TabIndex = 23;
            // 
            // Off_l_offtype
            // 
            this.Off_l_offtype.Location = new System.Drawing.Point(8, 215);
            this.Off_l_offtype.Name = "Off_l_offtype";
            this.Off_l_offtype.Size = new System.Drawing.Size(104, 23);
            this.Off_l_offtype.TabIndex = 22;
            this.Off_l_offtype.Text = "Offer";
            // 
            // Off_e_act
            // 
            this.Off_e_act.Location = new System.Drawing.Point(136, 267);
            this.Off_e_act.Name = "Off_e_act";
            this.Off_e_act.Size = new System.Drawing.Size(248, 21);
            this.Off_e_act.TabIndex = 21;
            // 
            // Off_l_act
            // 
            this.Off_l_act.Location = new System.Drawing.Point(8, 267);
            this.Off_l_act.Name = "Off_l_act";
            this.Off_l_act.Size = new System.Drawing.Size(122, 23);
            this.Off_l_act.TabIndex = 20;
            this.Off_l_act.Text = "Customer";
            // 
            // tdb_e_code
            // 
            this.tdb_e_code.Location = new System.Drawing.Point(136, 48);
            this.tdb_e_code.Name = "tdb_e_code";
            this.tdb_e_code.Size = new System.Drawing.Size(456, 20);
            this.tdb_e_code.TabIndex = 18;
            // 
            // tdb_l_code
            // 
            this.tdb_l_code.Location = new System.Drawing.Point(8, 48);
            this.tdb_l_code.Name = "tdb_l_code";
            this.tdb_l_code.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_code.TabIndex = 19;
            this.tdb_l_code.Text = "Code";
            // 
            // Off_l_ord
            // 
            this.Off_l_ord.Location = new System.Drawing.Point(429, 238);
            this.Off_l_ord.Name = "Off_l_ord";
            this.Off_l_ord.Size = new System.Drawing.Size(63, 23);
            this.Off_l_ord.TabIndex = 16;
            this.Off_l_ord.Text = "Ordering";
            // 
            // Off_e_dlt
            // 
            this.Off_e_dlt.Location = new System.Drawing.Point(136, 240);
            this.Off_e_dlt.Name = "Off_e_dlt";
            this.Off_e_dlt.Size = new System.Drawing.Size(248, 21);
            this.Off_e_dlt.TabIndex = 15;
            // 
            // Off_e_ishost
            // 
            this.Off_e_ishost.Location = new System.Drawing.Point(432, 192);
            this.Off_e_ishost.Name = "Off_e_ishost";
            this.Off_e_ishost.Size = new System.Drawing.Size(141, 24);
            this.Off_e_ishost.TabIndex = 14;
            this.Off_e_ishost.Text = "Root serviceoffer ?";
            this.Off_e_ishost.CheckedChanged += new System.EventHandler(this.Off_e_ishost_CheckedChanged);
            // 
            // Off_l_dlt
            // 
            this.Off_l_dlt.Location = new System.Drawing.Point(8, 240);
            this.Off_l_dlt.Name = "Off_l_dlt";
            this.Off_l_dlt.Size = new System.Drawing.Size(104, 23);
            this.Off_l_dlt.TabIndex = 12;
            this.Off_l_dlt.Text = "Reservation flag";
            // 
            // Off_e_parent
            // 
            this.Off_e_parent.Location = new System.Drawing.Point(136, 192);
            this.Off_e_parent.Name = "Off_e_parent";
            this.Off_e_parent.Size = new System.Drawing.Size(248, 21);
            this.Off_e_parent.TabIndex = 11;
            // 
            // Off_l_parent
            // 
            this.Off_l_parent.Location = new System.Drawing.Point(8, 192);
            this.Off_l_parent.Name = "Off_l_parent";
            this.Off_l_parent.Size = new System.Drawing.Size(100, 23);
            this.Off_l_parent.TabIndex = 10;
            this.Off_l_parent.Text = "Parent serviceoffer";
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
            this.tdb_e_bez.Location = new System.Drawing.Point(136, 72);
            this.tdb_e_bez.Name = "tdb_e_bez";
            this.tdb_e_bez.Size = new System.Drawing.Size(456, 20);
            this.tdb_e_bez.TabIndex = 0;
            // 
            // tdb_e_text
            // 
            this.tdb_e_text.Location = new System.Drawing.Point(136, 96);
            this.tdb_e_text.Multiline = true;
            this.tdb_e_text.Name = "tdb_e_text";
            this.tdb_e_text.Size = new System.Drawing.Size(456, 88);
            this.tdb_e_text.TabIndex = 2;
            // 
            // tdb_l_text
            // 
            this.tdb_l_text.Location = new System.Drawing.Point(8, 128);
            this.tdb_l_text.Name = "tdb_l_text";
            this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tdb_l_text.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_text.TabIndex = 4;
            this.tdb_l_text.Text = "Description";
            // 
            // tdb_l_bez
            // 
            this.tdb_l_bez.Location = new System.Drawing.Point(8, 72);
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
            // TDB_abgrp
            // 
            this.TDB_abgrp.Controls.Add(this.TDB_ab_clr);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_sel);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_exit);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_del);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_upd);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_ins);
            this.TDB_abgrp.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 396);
            this.TDB_abgrp.Name = "TDB_abgrp";
            this.TDB_abgrp.Size = new System.Drawing.Size(620, 56);
            this.TDB_abgrp.TabIndex = 15;
            this.TDB_abgrp.TabStop = false;
            this.TDB_abgrp.Text = "Actions";
            // 
            // TDB_ab_clr
            // 
            this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_clr.Location = new System.Drawing.Point(467, 16);
            this.TDB_ab_clr.Name = "TDB_ab_clr";
            this.TDB_ab_clr.Size = new System.Drawing.Size(75, 37);
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
            this.TDB_ab_sel.Size = new System.Drawing.Size(80, 37);
            this.TDB_ab_sel.TabIndex = 8;
            this.TDB_ab_sel.Text = "Select";
            this.TDB_ab_sel.UseVisualStyleBackColor = false;
            this.TDB_ab_sel.Click += new System.EventHandler(this.TDB_ab_sel_Click);
            // 
            // TDB_ab_exit
            // 
            this.TDB_ab_exit.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.TDB_ab_exit.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_exit.Location = new System.Drawing.Point(542, 16);
            this.TDB_ab_exit.Name = "TDB_ab_exit";
            this.TDB_ab_exit.Size = new System.Drawing.Size(75, 37);
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
            this.TDB_ab_del.Size = new System.Drawing.Size(75, 37);
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
            this.TDB_ab_upd.Size = new System.Drawing.Size(75, 37);
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
            this.TDB_ab_ins.Size = new System.Drawing.Size(75, 37);
            this.TDB_ab_ins.TabIndex = 5;
            this.TDB_ab_ins.Text = "Insert";
            this.TDB_ab_ins.UseVisualStyleBackColor = false;
            this.TDB_ab_ins.Click += new System.EventHandler(this.TDB_ab_ins_Click);
            // 
            // FServiceoffer
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(620, 452);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.groupBox1);
            this.Name = "FServiceoffer";
            this.Text = "Serviceoffer";
            this.Load += new System.EventHandler(this.FOff_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Off_e_ord)).EndInit();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			serviceoffer.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
            serviceoffer.Get(id, ref rows);
            tdb_e_id.Text = offer.ObjId.ToString();
            tdb_e_bez.Text = offer.ObjBez;
            tdb_e_text.Text = offer.ObjText;
            tdb_e_code.Text = offer.ObjCode;
			if (offer.ObjParentId == -1)
			{
				this.Off_e_parent.SelectedValue = -1;
				this.Off_e_ishost.CheckState = CheckState.Checked;
				this.Off_e_parent.Visible = false;
				ishost = true;
                this.Off_b_createserv.Enabled = true;
			}
			else
			{
                this.Off_e_parent.SelectedValue = offer.ObjParentId;
				this.Off_e_ishost.CheckState = CheckState.Unchecked;
				this.Off_e_parent.Visible = true;
				ishost = false;
                this.Off_b_createserv.Enabled = false;
			}
            Off_e_ord.Text = offer.ObjOrder.ToString();
            //this.Off_e_duration.Value = offer.ObjDuration;
            //this.Off_e_location.Text = offer.ObjLocation;
            //this.Off_e_dlt.SelectedValue = offer.ObjSuplier;
            //this.Off_e_from.SelectedValue = offer.ObjFrom;
            //this.Off_e_act.SelectedValue = offer.ObjAction;
            //this.Off_e_offtype.SelectedValue = offer.ObjType;
        }

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			offer.InsUpd(true, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Off_e_parent.SelectedValue,
				tdb_e_code.Text, (int)this.Off_e_dlt.SelectedValue, (int)this.Off_e_offtype.SelectedValue,
                this.Off_e_duration.Value, (int)this.Off_e_act.SelectedValue, (int)this.Off_e_from.SelectedValue,
                (int)this.Off_e_from.SelectedValue, Convert.ToInt32(this.Off_e_ord.Text), Off_e_location.Text);
			tdb_e_id.Text = offer.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
            offer.InsUpd(false, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Off_e_parent.SelectedValue,
                tdb_e_code.Text, (int)this.Off_e_dlt.SelectedValue, (int)this.Off_e_offtype.SelectedValue,
                this.Off_e_duration.Value, (int)this.Off_e_act.SelectedValue, (int)this.Off_e_from.SelectedValue,
                (int)this.Off_e_from.SelectedValue, Convert.ToInt32(this.Off_e_ord.Text), Off_e_location.Text);
        }

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			offer.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			offer.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_text.Text = "";
            tdb_e_code.Text = "";
			this.Off_e_ord.Text = "1";
            this.Off_e_location.Text = "";
            this.Off_e_act.Text = "";
            this.Off_e_from.Text = "";
            this.Off_e_parent.Text = "";
            this.Off_e_dlt.Text = "";
        }

		private void FOff_Load(object sender, System.EventArgs e)
		{
            // combos sup, act, offtype, tocity, fromcity, parentoffer
			tdbgui.GUIsup S = new tdbgui.GUIsup();
            S.SetCombo(this.Off_e_dlt);
            tdbgui.GUIact A = new tdbgui.GUIact();
            A.SetCombo(this.Off_e_act);
            tdbgui.GUIofft OT = new tdbgui.GUIofft();
            OT.SetCombo(this.Off_e_offtype);
            tdbgui.GUIcity C2 = new tdbgui.GUIcity();
            C2.SetCombo(this.Off_e_from);
            tdbgui.GUIoffer P = new tdbgui.GUIoffer();
            P.SetCombo(this.Off_e_parent);
        }

		private void Off_e_ishost_CheckedChanged(object sender, System.EventArgs e)
		{
			if (this.Off_e_ishost.CheckState == CheckState.Checked)
			{
				this.Off_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Off_e_parent.Visible = true;
				ishost = false;
			}
		}


        private void Off_b_createserv_Click(object sender, EventArgs e)
        {
            // only visible if it's a root offer object
            FWcreateserv Fw = new FWcreateserv();
            Fw.ObjOffer = offer;
            Fw.doPages();
            Fw.ShowDialog();

        }

        
        
        #endregion

    }
}
