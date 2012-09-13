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
	public class Fer : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox TDB_abgrp;
		private System.Windows.Forms.Button TDB_ab_clr;
		private System.Windows.Forms.Button TDB_ab_sel;
		private System.Windows.Forms.Button TDB_ab_exit;
		private System.Windows.Forms.Button TDB_ab_del;
		private System.Windows.Forms.Button TDB_ab_upd;
        private System.Windows.Forms.Button TDB_ab_ins;
		private tdbgui.GUIcur Cur;
		private System.Windows.Forms.ComboBox ER_e_type;
		private System.Windows.Forms.Label ER_l_type;
        private ComboBox ER_e_country;
        private Label ER_l_country;
        private ComboBox ER_e_cur;
        private Label ER_l_cur;
        private Label ER_l_buy;
        private Label ER_l_valid;
        private MonthCalendar ER_e_date;
        private TextBox Buy_e_sell;
        private Label ER_l_sell;
        private TextBox ER_e_buy;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public Fer()
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
            this.ER_l_valid = new System.Windows.Forms.Label();
            this.ER_e_date = new System.Windows.Forms.MonthCalendar();
            this.Buy_e_sell = new System.Windows.Forms.TextBox();
            this.ER_l_sell = new System.Windows.Forms.Label();
            this.ER_e_buy = new System.Windows.Forms.TextBox();
            this.ER_l_buy = new System.Windows.Forms.Label();
            this.ER_e_cur = new System.Windows.Forms.ComboBox();
            this.ER_l_cur = new System.Windows.Forms.Label();
            this.ER_e_country = new System.Windows.Forms.ComboBox();
            this.ER_l_country = new System.Windows.Forms.Label();
            this.ER_e_type = new System.Windows.Forms.ComboBox();
            this.ER_l_type = new System.Windows.Forms.Label();
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
            this.groupBox1.Controls.Add(this.ER_l_valid);
            this.groupBox1.Controls.Add(this.ER_e_date);
            this.groupBox1.Controls.Add(this.Buy_e_sell);
            this.groupBox1.Controls.Add(this.ER_l_sell);
            this.groupBox1.Controls.Add(this.ER_e_buy);
            this.groupBox1.Controls.Add(this.ER_l_buy);
            this.groupBox1.Controls.Add(this.ER_e_cur);
            this.groupBox1.Controls.Add(this.ER_l_cur);
            this.groupBox1.Controls.Add(this.ER_e_country);
            this.groupBox1.Controls.Add(this.ER_l_country);
            this.groupBox1.Controls.Add(this.ER_e_type);
            this.groupBox1.Controls.Add(this.ER_l_type);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(567, 268);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Description";
            // 
            // ER_l_valid
            // 
            this.ER_l_valid.AutoSize = true;
            this.ER_l_valid.Location = new System.Drawing.Point(402, 27);
            this.ER_l_valid.Name = "ER_l_valid";
            this.ER_l_valid.Size = new System.Drawing.Size(54, 13);
            this.ER_l_valid.TabIndex = 21;
            this.ER_l_valid.Text = "Valid date";
            // 
            // ER_e_date
            // 
            this.ER_e_date.Location = new System.Drawing.Point(395, 49);
            this.ER_e_date.Name = "ER_e_date";
            this.ER_e_date.TabIndex = 20;
            // 
            // Buy_e_sell
            // 
            this.Buy_e_sell.Location = new System.Drawing.Point(107, 129);
            this.Buy_e_sell.Name = "Buy_e_sell";
            this.Buy_e_sell.Size = new System.Drawing.Size(254, 20);
            this.Buy_e_sell.TabIndex = 19;
            // 
            // ER_l_sell
            // 
            this.ER_l_sell.AutoSize = true;
            this.ER_l_sell.Location = new System.Drawing.Point(8, 132);
            this.ER_l_sell.Name = "ER_l_sell";
            this.ER_l_sell.Size = new System.Drawing.Size(45, 13);
            this.ER_l_sell.TabIndex = 18;
            this.ER_l_sell.Text = "Sell rate";
            // 
            // ER_e_buy
            // 
            this.ER_e_buy.Location = new System.Drawing.Point(107, 103);
            this.ER_e_buy.Name = "ER_e_buy";
            this.ER_e_buy.Size = new System.Drawing.Size(254, 20);
            this.ER_e_buy.TabIndex = 17;
            // 
            // ER_l_buy
            // 
            this.ER_l_buy.AutoSize = true;
            this.ER_l_buy.Location = new System.Drawing.Point(8, 106);
            this.ER_l_buy.Name = "ER_l_buy";
            this.ER_l_buy.Size = new System.Drawing.Size(46, 13);
            this.ER_l_buy.TabIndex = 16;
            this.ER_l_buy.Text = "Buy rate";
            // 
            // ER_e_cur
            // 
            this.ER_e_cur.FormattingEnabled = true;
            this.ER_e_cur.Location = new System.Drawing.Point(107, 49);
            this.ER_e_cur.Name = "ER_e_cur";
            this.ER_e_cur.Size = new System.Drawing.Size(254, 21);
            this.ER_e_cur.TabIndex = 15;
            // 
            // ER_l_cur
            // 
            this.ER_l_cur.AutoSize = true;
            this.ER_l_cur.Location = new System.Drawing.Point(8, 52);
            this.ER_l_cur.Name = "ER_l_cur";
            this.ER_l_cur.Size = new System.Drawing.Size(49, 13);
            this.ER_l_cur.TabIndex = 14;
            this.ER_l_cur.Text = "Currency";
            // 
            // ER_e_country
            // 
            this.ER_e_country.FormattingEnabled = true;
            this.ER_e_country.Location = new System.Drawing.Point(107, 22);
            this.ER_e_country.Name = "ER_e_country";
            this.ER_e_country.Size = new System.Drawing.Size(254, 21);
            this.ER_e_country.TabIndex = 13;
            // 
            // ER_l_country
            // 
            this.ER_l_country.AutoSize = true;
            this.ER_l_country.Location = new System.Drawing.Point(8, 25);
            this.ER_l_country.Name = "ER_l_country";
            this.ER_l_country.Size = new System.Drawing.Size(43, 13);
            this.ER_l_country.TabIndex = 12;
            this.ER_l_country.Text = "Country";
            // 
            // ER_e_type
            // 
            this.ER_e_type.Location = new System.Drawing.Point(107, 76);
            this.ER_e_type.Name = "ER_e_type";
            this.ER_e_type.Size = new System.Drawing.Size(254, 21);
            this.ER_e_type.TabIndex = 11;
            // 
            // ER_l_type
            // 
            this.ER_l_type.Location = new System.Drawing.Point(8, 79);
            this.ER_l_type.Name = "ER_l_type";
            this.ER_l_type.Size = new System.Drawing.Size(61, 23);
            this.ER_l_type.TabIndex = 10;
            this.ER_l_type.Text = "Status";
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
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 215);
            this.TDB_abgrp.Name = "TDB_abgrp";
            this.TDB_abgrp.Size = new System.Drawing.Size(567, 53);
            this.TDB_abgrp.TabIndex = 15;
            this.TDB_abgrp.TabStop = false;
            this.TDB_abgrp.Text = "Actions";
            // 
            // TDB_ab_clr
            // 
            this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_clr.Location = new System.Drawing.Point(414, 16);
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
            this.TDB_ab_exit.Location = new System.Drawing.Point(489, 16);
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
            // Fer
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(567, 268);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.groupBox1);
            this.Name = "Fer";
            this.Text = "Exchange rates";
            this.Load += new System.EventHandler(this.FPrg_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			Cur.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
		}
		private void FPrg_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIsta S = new tdbgui.GUIsta();
			S.ObjTyp = tdb.StatusTypes.stawhr;
			S.SetCombo(this.ER_e_type);
		}
		#endregion


	}
}
