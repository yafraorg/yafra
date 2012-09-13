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
	public class FPersType : System.Windows.Forms.Form
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
		private tdbgui.GUIperst PT;
		private System.Windows.Forms.Label Perst_l_von;
		private System.Windows.Forms.Label Perst_l_bis;
		private System.Windows.Forms.NumericUpDown Perst_e_von;
		private System.Windows.Forms.NumericUpDown Perst_e_bis;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FPersType()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			PT = new tdbgui.GUIperst();
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
            this.Perst_e_bis = new System.Windows.Forms.NumericUpDown();
            this.Perst_e_von = new System.Windows.Forms.NumericUpDown();
            this.Perst_l_bis = new System.Windows.Forms.Label();
            this.Perst_l_von = new System.Windows.Forms.Label();
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
            ((System.ComponentModel.ISupportInitialize)(this.Perst_e_bis)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Perst_e_von)).BeginInit();
            this.TDB_abgrp.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.Perst_e_bis);
            this.groupBox1.Controls.Add(this.Perst_e_von);
            this.groupBox1.Controls.Add(this.Perst_l_bis);
            this.groupBox1.Controls.Add(this.Perst_l_von);
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
            this.groupBox1.Size = new System.Drawing.Size(608, 309);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Description";
            // 
            // Perst_e_bis
            // 
            this.Perst_e_bis.Location = new System.Drawing.Point(464, 200);
            this.Perst_e_bis.Maximum = new decimal(new int[] {
            130,
            0,
            0,
            0});
            this.Perst_e_bis.Name = "Perst_e_bis";
            this.Perst_e_bis.Size = new System.Drawing.Size(48, 20);
            this.Perst_e_bis.TabIndex = 13;
            this.Perst_e_bis.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            // 
            // Perst_e_von
            // 
            this.Perst_e_von.Location = new System.Drawing.Point(136, 200);
            this.Perst_e_von.Name = "Perst_e_von";
            this.Perst_e_von.Size = new System.Drawing.Size(48, 20);
            this.Perst_e_von.TabIndex = 12;
            // 
            // Perst_l_bis
            // 
            this.Perst_l_bis.Location = new System.Drawing.Point(336, 200);
            this.Perst_l_bis.Name = "Perst_l_bis";
            this.Perst_l_bis.Size = new System.Drawing.Size(100, 23);
            this.Perst_l_bis.TabIndex = 11;
            this.Perst_l_bis.Text = "To age:";
            // 
            // Perst_l_von
            // 
            this.Perst_l_von.Location = new System.Drawing.Point(8, 200);
            this.Perst_l_von.Name = "Perst_l_von";
            this.Perst_l_von.Size = new System.Drawing.Size(100, 23);
            this.Perst_l_von.TabIndex = 10;
            this.Perst_l_von.Text = "From age:";
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
            // TDB_abgrp
            // 
            this.TDB_abgrp.Controls.Add(this.TDB_ab_clr);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_sel);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_exit);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_del);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_upd);
            this.TDB_abgrp.Controls.Add(this.TDB_ab_ins);
            this.TDB_abgrp.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 256);
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
            // FPersType
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(608, 309);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.groupBox1);
            this.Name = "FPersType";
            this.Text = "Traveller Type";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.Perst_e_bis)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Perst_e_von)).EndInit();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			PT.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			PT.Get(id, ref rows);
			tdb_e_id.Text = PT.ObjId.ToString();
			tdb_e_bez.Text = PT.ObjBez;
			tdb_e_code.Text = PT.ObjCode;
			tdb_e_text.Text = PT.ObjText;
			Perst_e_von.Value = PT.ObjFrom;
			Perst_e_bis.Value = PT.ObjTo;
		}

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
			int v, b;
			v = (int)this.Perst_e_von.Value;
			b = (int)this.Perst_e_bis.Value;
			if (v >= b)
				MessageBox.Show("travelDB error: from age has to be lower than to age !");
			else
			{
				PT.InsUpd(true, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, v, b);
				tdb_e_id.Text = PT.ObjId.ToString();
			}
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
			int v, b;
			v = (int)this.Perst_e_von.Value;
			b = (int)this.Perst_e_bis.Value;
			if (v >= b)
				MessageBox.Show("travelDB error: from age has to be lower than to age !");
			else
				PT.InsUpd(false, tdb_e_bez.Text, tdb_e_code.Text, tdb_e_text.Text, v, b);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
			PT.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
			PT.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_code.Text = "";
			tdb_e_text.Text = "";
		}

		#endregion
	}
}
