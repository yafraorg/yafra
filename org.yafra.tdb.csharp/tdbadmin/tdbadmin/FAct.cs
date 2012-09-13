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
	public class FAct : System.Windows.Forms.Form
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
		private tdbgui.GUIact AT;
		private System.Windows.Forms.ComboBox Act_e_fromres;
		private System.Windows.Forms.ComboBox Act_e_tores;
		private System.Windows.Forms.Label Act_l_exeflag;
		private System.Windows.Forms.ComboBox Act_e_exeflag;
		private System.Windows.Forms.Label Act_l_dev;
		private System.Windows.Forms.ComboBox Act_e_dev;
		private System.Windows.Forms.ComboBox Act_e_actt;
		private System.Windows.Forms.Label Act_l_actt;
		private System.Windows.Forms.Label Act_l_ressta;
		private System.Windows.Forms.ComboBox Act_e_parent;
		private System.Windows.Forms.Label Act_l_parent;
		private System.Windows.Forms.Label Act_l_ord;
		private System.Windows.Forms.NumericUpDown Act_e_ord;
		private System.Windows.Forms.CheckBox Act_e_top;
		private bool ishost;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FAct()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			AT = new tdbgui.GUIact();
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
			this.Act_l_actt = new System.Windows.Forms.Label();
			this.Act_e_actt = new System.Windows.Forms.ComboBox();
			this.Act_e_dev = new System.Windows.Forms.ComboBox();
			this.Act_l_dev = new System.Windows.Forms.Label();
			this.Act_e_exeflag = new System.Windows.Forms.ComboBox();
			this.Act_l_exeflag = new System.Windows.Forms.Label();
			this.Act_e_tores = new System.Windows.Forms.ComboBox();
			this.Act_e_fromres = new System.Windows.Forms.ComboBox();
			this.Act_l_ressta = new System.Windows.Forms.Label();
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
			this.Act_e_parent = new System.Windows.Forms.ComboBox();
			this.Act_l_parent = new System.Windows.Forms.Label();
			this.Act_l_ord = new System.Windows.Forms.Label();
			this.Act_e_ord = new System.Windows.Forms.NumericUpDown();
			this.Act_e_top = new System.Windows.Forms.CheckBox();
			this.groupBox1.SuspendLayout();
			this.TDB_abgrp.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.Act_e_ord)).BeginInit();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.Act_e_top);
			this.groupBox1.Controls.Add(this.Act_e_ord);
			this.groupBox1.Controls.Add(this.Act_l_ord);
			this.groupBox1.Controls.Add(this.Act_l_parent);
			this.groupBox1.Controls.Add(this.Act_e_parent);
			this.groupBox1.Controls.Add(this.Act_l_actt);
			this.groupBox1.Controls.Add(this.Act_e_actt);
			this.groupBox1.Controls.Add(this.Act_e_dev);
			this.groupBox1.Controls.Add(this.Act_l_dev);
			this.groupBox1.Controls.Add(this.Act_e_exeflag);
			this.groupBox1.Controls.Add(this.Act_l_exeflag);
			this.groupBox1.Controls.Add(this.Act_e_tores);
			this.groupBox1.Controls.Add(this.Act_e_fromres);
			this.groupBox1.Controls.Add(this.Act_l_ressta);
			this.groupBox1.Controls.Add(this.tdb_e_id);
			this.groupBox1.Controls.Add(this.tdb_e_bez);
			this.groupBox1.Controls.Add(this.tdb_e_text);
			this.groupBox1.Controls.Add(this.tdb_l_text);
			this.groupBox1.Controls.Add(this.tdb_l_bez);
			this.groupBox1.Controls.Add(this.tdb_l_id);
			this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
			this.groupBox1.Location = new System.Drawing.Point(0, 0);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(608, 296);
			this.groupBox1.TabIndex = 13;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Description";
			// 
			// Act_l_actt
			// 
			this.Act_l_actt.Location = new System.Drawing.Point(368, 232);
			this.Act_l_actt.Name = "Act_l_actt";
			this.Act_l_actt.Size = new System.Drawing.Size(100, 16);
			this.Act_l_actt.TabIndex = 18;
			this.Act_l_actt.Text = "Actiontype";
			// 
			// Act_e_actt
			// 
			this.Act_e_actt.Location = new System.Drawing.Point(368, 248);
			this.Act_e_actt.Name = "Act_e_actt";
			this.Act_e_actt.Size = new System.Drawing.Size(224, 21);
			this.Act_e_actt.TabIndex = 17;
			// 
			// Act_e_dev
			// 
			this.Act_e_dev.Location = new System.Drawing.Point(136, 248);
			this.Act_e_dev.Name = "Act_e_dev";
			this.Act_e_dev.Size = new System.Drawing.Size(216, 21);
			this.Act_e_dev.TabIndex = 16;
			// 
			// Act_l_dev
			// 
			this.Act_l_dev.Location = new System.Drawing.Point(8, 248);
			this.Act_l_dev.Name = "Act_l_dev";
			this.Act_l_dev.TabIndex = 15;
			this.Act_l_dev.Text = "Device";
			// 
			// Act_e_exeflag
			// 
			this.Act_e_exeflag.Location = new System.Drawing.Point(136, 224);
			this.Act_e_exeflag.Name = "Act_e_exeflag";
			this.Act_e_exeflag.Size = new System.Drawing.Size(216, 21);
			this.Act_e_exeflag.TabIndex = 14;
			// 
			// Act_l_exeflag
			// 
			this.Act_l_exeflag.Location = new System.Drawing.Point(8, 224);
			this.Act_l_exeflag.Name = "Act_l_exeflag";
			this.Act_l_exeflag.TabIndex = 13;
			this.Act_l_exeflag.Text = "Execution flag";
			// 
			// Act_e_tores
			// 
			this.Act_e_tores.Location = new System.Drawing.Point(368, 192);
			this.Act_e_tores.Name = "Act_e_tores";
			this.Act_e_tores.Size = new System.Drawing.Size(224, 21);
			this.Act_e_tores.TabIndex = 12;
			// 
			// Act_e_fromres
			// 
			this.Act_e_fromres.Location = new System.Drawing.Point(136, 192);
			this.Act_e_fromres.Name = "Act_e_fromres";
			this.Act_e_fromres.Size = new System.Drawing.Size(216, 21);
			this.Act_e_fromres.TabIndex = 11;
			// 
			// Act_l_ressta
			// 
			this.Act_l_ressta.Location = new System.Drawing.Point(8, 192);
			this.Act_l_ressta.Name = "Act_l_ressta";
			this.Act_l_ressta.Size = new System.Drawing.Size(120, 32);
			this.Act_l_ressta.TabIndex = 10;
			this.Act_l_ressta.Text = "Set from / to reservation status";
			// 
			// tdb_e_id
			// 
			this.tdb_e_id.Location = new System.Drawing.Point(136, 56);
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
			this.tdb_e_bez.Text = "";
			// 
			// tdb_e_text
			// 
			this.tdb_e_text.Location = new System.Drawing.Point(136, 96);
			this.tdb_e_text.Multiline = true;
			this.tdb_e_text.Name = "tdb_e_text";
			this.tdb_e_text.Size = new System.Drawing.Size(456, 88);
			this.tdb_e_text.TabIndex = 2;
			this.tdb_e_text.Text = "";
			// 
			// tdb_l_text
			// 
			this.tdb_l_text.Location = new System.Drawing.Point(8, 128);
			this.tdb_l_text.Name = "tdb_l_text";
			this.tdb_l_text.RightToLeft = System.Windows.Forms.RightToLeft.No;
			this.tdb_l_text.TabIndex = 4;
			this.tdb_l_text.Text = "Description";
			// 
			// tdb_l_bez
			// 
			this.tdb_l_bez.Location = new System.Drawing.Point(8, 72);
			this.tdb_l_bez.Name = "tdb_l_bez";
			this.tdb_l_bez.TabIndex = 2;
			this.tdb_l_bez.Text = "Title";
			// 
			// tdb_l_id
			// 
			this.tdb_l_id.Location = new System.Drawing.Point(8, 56);
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
			this.TDB_abgrp.Location = new System.Drawing.Point(0, 296);
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
			// Act_e_parent
			// 
			this.Act_e_parent.Location = new System.Drawing.Point(136, 16);
			this.Act_e_parent.Name = "Act_e_parent";
			this.Act_e_parent.Size = new System.Drawing.Size(264, 21);
			this.Act_e_parent.TabIndex = 19;
			// 
			// Act_l_parent
			// 
			this.Act_l_parent.Location = new System.Drawing.Point(8, 16);
			this.Act_l_parent.Name = "Act_l_parent";
			this.Act_l_parent.Size = new System.Drawing.Size(64, 16);
			this.Act_l_parent.TabIndex = 20;
			this.Act_l_parent.Text = "Parent";
			// 
			// Act_l_ord
			// 
			this.Act_l_ord.Location = new System.Drawing.Point(256, 47);
			this.Act_l_ord.Name = "Act_l_ord";
			this.Act_l_ord.Size = new System.Drawing.Size(80, 23);
			this.Act_l_ord.TabIndex = 21;
			this.Act_l_ord.Text = "Order number";
			// 
			// Act_e_ord
			// 
			this.Act_e_ord.Location = new System.Drawing.Point(352, 48);
			this.Act_e_ord.Maximum = new System.Decimal(new int[] {
																						1000,
																						0,
																						0,
																						0});
			this.Act_e_ord.Name = "Act_e_ord";
			this.Act_e_ord.Size = new System.Drawing.Size(48, 20);
			this.Act_e_ord.TabIndex = 22;
			// 
			// Act_e_top
			// 
			this.Act_e_top.Location = new System.Drawing.Point(440, 32);
			this.Act_e_top.Name = "Act_e_top";
			this.Act_e_top.TabIndex = 23;
			this.Act_e_top.Text = "Top / Root ?";
			this.Act_e_top.CheckedChanged += new System.EventHandler(this.Act_e_top_CheckedChanged);
			// 
			// FAct
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(608, 349);
			this.Controls.Add(this.TDB_abgrp);
			this.Controls.Add(this.groupBox1);
			this.Name = "FAct";
			this.Text = "Actions";
			this.Load += new System.EventHandler(this.FAct_Load);
			this.groupBox1.ResumeLayout(false);
			this.TDB_abgrp.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.Act_e_ord)).EndInit();
			this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			AT.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			AT.Get(id, ref rows);
			tdb_e_id.Text = AT.ObjId.ToString();
			tdb_e_bez.Text = AT.ObjBez;
			tdb_e_text.Text = AT.ObjText;
			this.Act_e_exeflag.SelectedValue = AT.ObjExeflag;
			this.Act_e_fromres.SelectedValue = AT.ObjFrom;
			this.Act_e_tores.SelectedValue = AT.ObjTo;
			this.Act_e_dev.SelectedValue = AT.ObjDev;
			this.Act_e_actt.SelectedValue = AT.ObjActt;
			this.Act_e_ord.Value = AT.ObjOrd;
			if (AT.ObjParent == -1)
			{
				this.Act_e_top.CheckState = CheckState.Checked;
				this.Act_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Act_e_parent.SelectedValue = AT.ObjParent;
				this.Act_e_top.CheckState = CheckState.Unchecked;
				this.Act_e_parent.Visible = true;
				ishost = false;
			}
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			AT.InsUpd(true, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Act_e_exeflag.SelectedValue,
				(int)this.Act_e_fromres.SelectedValue, (int)this.Act_e_tores.SelectedValue,
				(int)this.Act_e_dev.SelectedValue, (int)this.Act_e_actt.SelectedValue);
			tdb_e_id.Text = AT.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			AT.InsUpd(false, tdb_e_bez.Text, tdb_e_text.Text, (int)this.Act_e_exeflag.SelectedValue,
				(int)this.Act_e_fromres.SelectedValue, (int)this.Act_e_tores.SelectedValue,
				(int)this.Act_e_dev.SelectedValue, (int)this.Act_e_actt.SelectedValue);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			AT.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			AT.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_text.Text = "";
			this.Act_e_fromres.SelectedValue = -1;
			this.Act_e_tores.SelectedValue = -1;
			this.Act_e_exeflag.SelectedValue = -1;
			this.Act_e_dev.SelectedValue = -1;
			this.Act_e_ord.Value = 1;
		}

		private void Act_e_top_CheckedChanged(object sender, System.EventArgs e)
		{
			if (this.Act_e_top.CheckState == CheckState.Checked)
			{
				this.Act_e_parent.Visible = false;
				ishost = true;
			}
			else
			{
				this.Act_e_parent.Visible = true;
				ishost = false;
			}
		}

		private void FAct_Load(object sender, System.EventArgs e)
		{
			tdbgui.GUIsta Sexe = new tdbgui.GUIsta();
			Sexe.ObjOptional = true;
			Sexe.ObjTyp = tdb.StatusTypes.exeflag;
			Sexe.SetCombo(this.Act_e_exeflag);

			tdbgui.GUIsta From = new tdbgui.GUIsta();
			From.ObjOptional = true;
			From.ObjTyp = tdb.StatusTypes.stares;
			From.SetCombo(this.Act_e_fromres);
			tdbgui.GUIsta To = new tdbgui.GUIsta();
			To.ObjTyp = tdb.StatusTypes.stares;
			To.ObjOptional = true;
			To.SetCombo(this.Act_e_tores);

			tdbgui.GUIsta Sdev = new tdbgui.GUIsta();
			Sdev.ObjOptional = true;
			Sdev.ObjTyp = tdb.StatusTypes.device;
			Sdev.SetCombo(this.Act_e_dev);

			tdbgui.GUIactt At = new tdbgui.GUIactt();
			At.SetCombo(this.Act_e_actt);

			tdbgui.GUIact A = new tdbgui.GUIact();
			A.SetCombo(this.Act_e_parent);
		}

		#endregion

	}
}
