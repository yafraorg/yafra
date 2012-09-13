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
	public class FBez : System.Windows.Forms.Form
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
		private System.Windows.Forms.Label tdb_l_bez;
		private System.Windows.Forms.Label tdb_l_id;
		private tdbgui.GUIcur Cur;
		private System.Windows.Forms.ComboBox Bez_e_type;
		private System.Windows.Forms.Label Bez_l_type;
        private ComboBox Bez_e_lang;
        private Label Bez_l_lang;
        private GroupBox Bez_grp_translation;
        private Button Bez_b_masstrans;
        private Label Bez_l_trans;
        private ComboBox Bez_e_translang;
        private Label Bez_l_translang;
        private TextBox Bez_e_transbez;
        private Label Bez_l_transbez;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FBez()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Cur = new tdbgui.GUIcur();
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
            this.Bez_grp_translation = new System.Windows.Forms.GroupBox();
            this.Bez_b_masstrans = new System.Windows.Forms.Button();
            this.Bez_l_trans = new System.Windows.Forms.Label();
            this.Bez_e_translang = new System.Windows.Forms.ComboBox();
            this.Bez_l_translang = new System.Windows.Forms.Label();
            this.Bez_e_transbez = new System.Windows.Forms.TextBox();
            this.Bez_l_transbez = new System.Windows.Forms.Label();
            this.Bez_e_lang = new System.Windows.Forms.ComboBox();
            this.Bez_l_lang = new System.Windows.Forms.Label();
            this.Bez_e_type = new System.Windows.Forms.ComboBox();
            this.Bez_l_type = new System.Windows.Forms.Label();
            this.tdb_e_id = new System.Windows.Forms.Label();
            this.tdb_e_bez = new System.Windows.Forms.TextBox();
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
            this.Bez_grp_translation.SuspendLayout();
            this.TDB_abgrp.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Bez_grp_translation);
            this.groupBox1.Controls.Add(this.Bez_e_lang);
            this.groupBox1.Controls.Add(this.Bez_l_lang);
            this.groupBox1.Controls.Add(this.Bez_e_type);
            this.groupBox1.Controls.Add(this.Bez_l_type);
            this.groupBox1.Controls.Add(this.tdb_e_id);
            this.groupBox1.Controls.Add(this.tdb_e_bez);
            this.groupBox1.Controls.Add(this.tdb_l_bez);
            this.groupBox1.Controls.Add(this.tdb_l_id);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(608, 291);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Description";
            // 
            // Bez_grp_translation
            // 
            this.Bez_grp_translation.Controls.Add(this.Bez_b_masstrans);
            this.Bez_grp_translation.Controls.Add(this.Bez_l_trans);
            this.Bez_grp_translation.Controls.Add(this.Bez_e_translang);
            this.Bez_grp_translation.Controls.Add(this.Bez_l_translang);
            this.Bez_grp_translation.Controls.Add(this.Bez_e_transbez);
            this.Bez_grp_translation.Controls.Add(this.Bez_l_transbez);
            this.Bez_grp_translation.Location = new System.Drawing.Point(0, 114);
            this.Bez_grp_translation.Name = "Bez_grp_translation";
            this.Bez_grp_translation.Size = new System.Drawing.Size(605, 119);
            this.Bez_grp_translation.TabIndex = 14;
            this.Bez_grp_translation.TabStop = false;
            this.Bez_grp_translation.Text = "Translation";
            // 
            // Bez_b_masstrans
            // 
            this.Bez_b_masstrans.Location = new System.Drawing.Point(481, 83);
            this.Bez_b_masstrans.Name = "Bez_b_masstrans";
            this.Bez_b_masstrans.Size = new System.Drawing.Size(111, 23);
            this.Bez_b_masstrans.TabIndex = 19;
            this.Bez_b_masstrans.Text = "Mass translation";
            this.Bez_b_masstrans.UseVisualStyleBackColor = true;
            // 
            // Bez_l_trans
            // 
            this.Bez_l_trans.AutoSize = true;
            this.Bez_l_trans.Location = new System.Drawing.Point(12, 16);
            this.Bez_l_trans.Name = "Bez_l_trans";
            this.Bez_l_trans.Size = new System.Drawing.Size(160, 13);
            this.Bez_l_trans.TabIndex = 18;
            this.Bez_l_trans.Text = "Choose language to translate to:";
            // 
            // Bez_e_translang
            // 
            this.Bez_e_translang.Location = new System.Drawing.Point(138, 33);
            this.Bez_e_translang.Name = "Bez_e_translang";
            this.Bez_e_translang.Size = new System.Drawing.Size(256, 21);
            this.Bez_e_translang.TabIndex = 17;
            // 
            // Bez_l_translang
            // 
            this.Bez_l_translang.Location = new System.Drawing.Point(10, 33);
            this.Bez_l_translang.Name = "Bez_l_translang";
            this.Bez_l_translang.Size = new System.Drawing.Size(100, 23);
            this.Bez_l_translang.TabIndex = 16;
            this.Bez_l_translang.Text = "Language";
            // 
            // Bez_e_transbez
            // 
            this.Bez_e_transbez.Location = new System.Drawing.Point(138, 57);
            this.Bez_e_transbez.Name = "Bez_e_transbez";
            this.Bez_e_transbez.Size = new System.Drawing.Size(456, 20);
            this.Bez_e_transbez.TabIndex = 14;
            // 
            // Bez_l_transbez
            // 
            this.Bez_l_transbez.Location = new System.Drawing.Point(10, 56);
            this.Bez_l_transbez.Name = "Bez_l_transbez";
            this.Bez_l_transbez.Size = new System.Drawing.Size(100, 23);
            this.Bez_l_transbez.TabIndex = 15;
            this.Bez_l_transbez.Text = "Description";
            // 
            // Bez_e_lang
            // 
            this.Bez_e_lang.Location = new System.Drawing.Point(136, 65);
            this.Bez_e_lang.Name = "Bez_e_lang";
            this.Bez_e_lang.Size = new System.Drawing.Size(256, 21);
            this.Bez_e_lang.TabIndex = 13;
            // 
            // Bez_l_lang
            // 
            this.Bez_l_lang.Location = new System.Drawing.Point(8, 65);
            this.Bez_l_lang.Name = "Bez_l_lang";
            this.Bez_l_lang.Size = new System.Drawing.Size(100, 23);
            this.Bez_l_lang.TabIndex = 12;
            this.Bez_l_lang.Text = "Language";
            // 
            // Bez_e_type
            // 
            this.Bez_e_type.Location = new System.Drawing.Point(136, 41);
            this.Bez_e_type.Name = "Bez_e_type";
            this.Bez_e_type.Size = new System.Drawing.Size(256, 21);
            this.Bez_e_type.TabIndex = 11;
            // 
            // Bez_l_type
            // 
            this.Bez_l_type.Location = new System.Drawing.Point(8, 41);
            this.Bez_l_type.Name = "Bez_l_type";
            this.Bez_l_type.Size = new System.Drawing.Size(100, 23);
            this.Bez_l_type.TabIndex = 10;
            this.Bez_l_type.Text = "Type";
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
            this.tdb_e_bez.Location = new System.Drawing.Point(136, 89);
            this.tdb_e_bez.Name = "tdb_e_bez";
            this.tdb_e_bez.Size = new System.Drawing.Size(456, 20);
            this.tdb_e_bez.TabIndex = 0;
            // 
            // tdb_l_bez
            // 
            this.tdb_l_bez.Location = new System.Drawing.Point(8, 88);
            this.tdb_l_bez.Name = "tdb_l_bez";
            this.tdb_l_bez.Size = new System.Drawing.Size(100, 23);
            this.tdb_l_bez.TabIndex = 2;
            this.tdb_l_bez.Text = "Description";
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
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 238);
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
            this.TDB_ab_exit.Location = new System.Drawing.Point(530, 16);
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
            // FBez
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(608, 291);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.groupBox1);
            this.Name = "FBez";
            this.Text = "Descriptions";
            this.Load += new System.EventHandler(this.FBez_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.Bez_grp_translation.ResumeLayout(false);
            this.Bez_grp_translation.PerformLayout();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks

        private void TDB_ab_ins_Click(object sender, EventArgs e)
        {

        }

        private void TDB_ab_upd_Click(object sender, EventArgs e)
        {

        }

        private void TDB_ab_del_Click(object sender, EventArgs e)
        {

        }

        private void TDB_ab_sel_Click(object sender, EventArgs e)
        {

        }

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
		}
		private void FBez_Load(object sender, System.EventArgs e)
		{
            // pre load combos here
		}
		#endregion

	}
}
