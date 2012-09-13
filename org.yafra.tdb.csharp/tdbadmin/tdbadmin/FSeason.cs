using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace tdbadmin
{
	/// <summary>
	/// Main Form for Season (saison) table.
	/// </summary>
	public class FSeason : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Label Sai_e_id;
		private System.Windows.Forms.TextBox Sai_e_bez;
		private System.Windows.Forms.TextBox Sai_e_code;
		private System.Windows.Forms.TextBox Sai_e_text;
		private System.Windows.Forms.Label Sai_l_text;
		private System.Windows.Forms.Label Sai_l_code;
		private System.Windows.Forms.Label Sai_l_bez;
		private System.Windows.Forms.Label Sai_l_id;
		private System.Windows.Forms.Label Sai_l_bis;
		private System.Windows.Forms.Label Sai_l_von;
		private System.Windows.Forms.MonthCalendar Sai_e_bis;
		private System.Windows.Forms.MonthCalendar Sai_e_von;
		private System.Windows.Forms.GroupBox TDB_abgrp;
		private System.Windows.Forms.Button TDB_ab_clr;
		private System.Windows.Forms.Button TDB_ab_sel;
		private System.Windows.Forms.Button TDB_ab_exit;
		private System.Windows.Forms.Button TDB_ab_del;
		private System.Windows.Forms.Button TDB_ab_upd;
		private System.Windows.Forms.Button TDB_ab_ins;
		private tdbgui.GUIsai Sai;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FSeason()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			Sai = new tdbgui.GUIsai();
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
			this.Sai_e_id = new System.Windows.Forms.Label();
			this.Sai_e_bez = new System.Windows.Forms.TextBox();
			this.Sai_e_code = new System.Windows.Forms.TextBox();
			this.Sai_e_text = new System.Windows.Forms.TextBox();
			this.Sai_l_text = new System.Windows.Forms.Label();
			this.Sai_l_code = new System.Windows.Forms.Label();
			this.Sai_l_bez = new System.Windows.Forms.Label();
			this.Sai_l_id = new System.Windows.Forms.Label();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Sai_l_bis = new System.Windows.Forms.Label();
			this.Sai_l_von = new System.Windows.Forms.Label();
			this.Sai_e_bis = new System.Windows.Forms.MonthCalendar();
			this.Sai_e_von = new System.Windows.Forms.MonthCalendar();
			this.TDB_abgrp = new System.Windows.Forms.GroupBox();
			this.TDB_ab_clr = new System.Windows.Forms.Button();
			this.TDB_ab_sel = new System.Windows.Forms.Button();
			this.TDB_ab_exit = new System.Windows.Forms.Button();
			this.TDB_ab_del = new System.Windows.Forms.Button();
			this.TDB_ab_upd = new System.Windows.Forms.Button();
			this.TDB_ab_ins = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.TDB_abgrp.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Sai_e_id);
			this.groupBox1.Controls.Add(this.Sai_e_bez);
			this.groupBox1.Controls.Add(this.Sai_e_code);
			this.groupBox1.Controls.Add(this.Sai_e_text);
			this.groupBox1.Controls.Add(this.Sai_l_text);
			this.groupBox1.Controls.Add(this.Sai_l_code);
			this.groupBox1.Controls.Add(this.Sai_l_bez);
			this.groupBox1.Controls.Add(this.Sai_l_id);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(608, 192);
			this.groupBox1.TabIndex = 12;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Season Description";
			// 
			// Sai_e_id
			// 
			this.Sai_e_id.Location = new System.Drawing.Point(136, 24);
			this.Sai_e_id.Name = "Sai_e_id";
			this.Sai_e_id.Size = new System.Drawing.Size(64, 16);
			this.Sai_e_id.TabIndex = 9;
			// 
			// Sai_e_bez
			// 
			this.Sai_e_bez.Location = new System.Drawing.Point(136, 40);
			this.Sai_e_bez.Name = "Sai_e_bez";
			this.Sai_e_bez.Size = new System.Drawing.Size(456, 20);
			this.Sai_e_bez.TabIndex = 0;
			this.Sai_e_bez.Text = "";
			// 
			// Sai_e_code
			// 
			this.Sai_e_code.Location = new System.Drawing.Point(136, 64);
			this.Sai_e_code.Name = "Sai_e_code";
			this.Sai_e_code.Size = new System.Drawing.Size(456, 20);
			this.Sai_e_code.TabIndex = 1;
			this.Sai_e_code.Text = "";
			// 
			// Sai_e_text
			// 
			this.Sai_e_text.Location = new System.Drawing.Point(136, 88);
			this.Sai_e_text.Multiline = true;
			this.Sai_e_text.Name = "Sai_e_text";
			this.Sai_e_text.Size = new System.Drawing.Size(456, 88);
			this.Sai_e_text.TabIndex = 2;
			this.Sai_e_text.Text = "";
			// 
			// Sai_l_text
			// 
			this.Sai_l_text.Location = new System.Drawing.Point(8, 121);
			this.Sai_l_text.Name = "Sai_l_text";
			this.Sai_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.Sai_l_text.TabIndex = 4;
			this.Sai_l_text.Text = "Description";
			// 
			// Sai_l_code
			// 
			this.Sai_l_code.Location = new System.Drawing.Point(8, 63);
			this.Sai_l_code.Name = "Sai_l_code";
			this.Sai_l_code.TabIndex = 3;
			this.Sai_l_code.Text = "Code";
			// 
			// Sai_l_bez
			// 
			this.Sai_l_bez.Location = new System.Drawing.Point(8, 39);
			this.Sai_l_bez.Name = "Sai_l_bez";
			this.Sai_l_bez.TabIndex = 2;
			this.Sai_l_bez.Text = "Title";
			// 
			// Sai_l_id
			// 
			this.Sai_l_id.Location = new System.Drawing.Point(8, 21);
			this.Sai_l_id.Name = "Sai_l_id";
			this.Sai_l_id.TabIndex = 1;
			this.Sai_l_id.Text = "ID";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Sai_l_bis);
			this.groupBox2.Controls.Add(this.Sai_l_von);
			this.groupBox2.Controls.Add(this.Sai_e_bis);
			this.groupBox2.Controls.Add(this.Sai_e_von);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox2.Location = new System.Drawing.Point(0, 192);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(608, 208);
			this.groupBox2.TabIndex = 11;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "From / To";
			// 
			// Sai_l_bis
			// 
			this.Sai_l_bis.Location = new System.Drawing.Point(232, 24);
			this.Sai_l_bis.Name = "Sai_l_bis";
			this.Sai_l_bis.Size = new System.Drawing.Size(100, 16);
			this.Sai_l_bis.TabIndex = 3;
			this.Sai_l_bis.Text = "To date";
			// 
			// Sai_l_von
			// 
			this.Sai_l_von.Location = new System.Drawing.Point(8, 24);
			this.Sai_l_von.Name = "Sai_l_von";
			this.Sai_l_von.Size = new System.Drawing.Size(100, 16);
			this.Sai_l_von.TabIndex = 2;
			this.Sai_l_von.Text = "From date";
			// 
			// Sai_e_bis
			// 
			this.Sai_e_bis.Location = new System.Drawing.Point(232, 40);
			this.Sai_e_bis.Name = "Sai_e_bis";
			this.Sai_e_bis.ShowWeekNumbers = true;
			this.Sai_e_bis.TabIndex = 4;
			// 
			// Sai_e_von
			// 
			this.Sai_e_von.Location = new System.Drawing.Point(8, 40);
			this.Sai_e_von.Name = "Sai_e_von";
			this.Sai_e_von.ShowWeekNumbers = true;
			this.Sai_e_von.TabIndex = 3;
			// 
			// TDB_abgrp
			// 
			this.TDB_abgrp.Controls.Add(this.TDB_ab_clr);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_sel);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_exit);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_del);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_upd);
			this.TDB_abgrp.Controls.Add(this.TDB_ab_ins);
			this.TDB_abgrp.Dock = System.Windows.Forms.DockStyle.Fill;
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 400);
			this.TDB_abgrp.Name = "TDB_abgrp";
			this.TDB_abgrp.Size = new System.Drawing.Size(608, 53);
			this.TDB_abgrp.TabIndex = 2;
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
			// Season
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 453);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Name = "Season";
			this.Text = "Season";
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.TDB_abgrp.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Season callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			Sai.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			Sai.Get(id, ref rows);
			Sai_e_id.Text = Sai.ObjId.ToString();
			Sai_e_bez.Text = Sai.ObjBez;
			Sai_e_code.Text = Sai.ObjCode;
			Sai_e_text.Text = Sai.ObjText;
			Sai_e_von.SetDate(Sai.ObjFrom);
			Sai_e_bis.SetDate(Sai.ObjTo);
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			Sai.InsUpd(true, Sai_e_bez.Text, Sai_e_code.Text, Sai_e_von.SelectionStart , Sai_e_bis.SelectionStart, Sai_e_text.Text);
			Sai_e_id.Text = Sai.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			Sai.InsUpd(false, Sai_e_bez.Text, Sai_e_code.Text, Sai_e_von.SelectionStart , Sai_e_bis.SelectionStart, Sai_e_text.Text);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			Sai.Get(Convert.ToInt32(Sai_e_id.Text), ref rows);
			Sai.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			DateTime now = DateTime.Now;
			Sai_e_id.Text = "";
			Sai_e_bez.Text = "";
			Sai_e_code.Text = "";
			Sai_e_text.Text = "";
			this.Sai_e_von.SetDate(now);
			this.Sai_e_bis.SetDate(now);
		}

		#endregion

	}
}
