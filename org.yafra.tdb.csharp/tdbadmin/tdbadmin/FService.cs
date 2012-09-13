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
	public class FService : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox Ser_b_arrdl;
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
        private System.Windows.Forms.Label Ser_l_act;
		private System.Windows.Forms.Label Ser_l_season;
		private System.Windows.Forms.ComboBox Ser_e_act;
        private System.Windows.Forms.Label Ser_l_starttime;
		private tdbgui.GUIservice service;
		private System.Windows.Forms.TextBox tdb_e_code;
        private System.Windows.Forms.Label tdb_l_code;
        private DateTimePicker Ser_e_starttime;
        private Button Ser_b_mapdetails;
        private Button Ser_b_maparr;
        private CheckBox Ser_e_onlytime;
        private ComboBox Ser_e_season;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public FService()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			service = new tdbgui.GUIservice();
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
            this.Ser_b_arrdl = new System.Windows.Forms.GroupBox();
            this.Ser_e_onlytime = new System.Windows.Forms.CheckBox();
            this.Ser_b_mapdetails = new System.Windows.Forms.Button();
            this.Ser_b_maparr = new System.Windows.Forms.Button();
            this.Ser_e_starttime = new System.Windows.Forms.DateTimePicker();
            this.tdb_e_code = new System.Windows.Forms.TextBox();
            this.tdb_l_code = new System.Windows.Forms.Label();
            this.Ser_l_starttime = new System.Windows.Forms.Label();
            this.Ser_e_act = new System.Windows.Forms.ComboBox();
            this.Ser_l_act = new System.Windows.Forms.Label();
            this.Ser_l_season = new System.Windows.Forms.Label();
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
            this.Ser_e_season = new System.Windows.Forms.ComboBox();
            this.Ser_b_arrdl.SuspendLayout();
            this.TDB_abgrp.SuspendLayout();
            this.SuspendLayout();
            // 
            // Ser_b_arrdl
            // 
            this.Ser_b_arrdl.Controls.Add(this.Ser_e_season);
            this.Ser_b_arrdl.Controls.Add(this.Ser_e_onlytime);
            this.Ser_b_arrdl.Controls.Add(this.Ser_b_mapdetails);
            this.Ser_b_arrdl.Controls.Add(this.Ser_b_maparr);
            this.Ser_b_arrdl.Controls.Add(this.Ser_e_starttime);
            this.Ser_b_arrdl.Controls.Add(this.tdb_e_code);
            this.Ser_b_arrdl.Controls.Add(this.tdb_l_code);
            this.Ser_b_arrdl.Controls.Add(this.Ser_l_starttime);
            this.Ser_b_arrdl.Controls.Add(this.Ser_e_act);
            this.Ser_b_arrdl.Controls.Add(this.Ser_l_act);
            this.Ser_b_arrdl.Controls.Add(this.Ser_l_season);
            this.Ser_b_arrdl.Controls.Add(this.tdb_e_id);
            this.Ser_b_arrdl.Controls.Add(this.tdb_e_bez);
            this.Ser_b_arrdl.Controls.Add(this.tdb_e_text);
            this.Ser_b_arrdl.Controls.Add(this.tdb_l_text);
            this.Ser_b_arrdl.Controls.Add(this.tdb_l_bez);
            this.Ser_b_arrdl.Controls.Add(this.tdb_l_id);
            this.Ser_b_arrdl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Ser_b_arrdl.Location = new System.Drawing.Point(0, 0);
            this.Ser_b_arrdl.Name = "Ser_b_arrdl";
            this.Ser_b_arrdl.Size = new System.Drawing.Size(613, 346);
            this.Ser_b_arrdl.TabIndex = 13;
            this.Ser_b_arrdl.TabStop = false;
            this.Ser_b_arrdl.Text = "Description";
            // 
            // Ser_e_onlytime
            // 
            this.Ser_e_onlytime.AutoSize = true;
            this.Ser_e_onlytime.Location = new System.Drawing.Point(228, 240);
            this.Ser_e_onlytime.Name = "Ser_e_onlytime";
            this.Ser_e_onlytime.Size = new System.Drawing.Size(67, 17);
            this.Ser_e_onlytime.TabIndex = 23;
            this.Ser_e_onlytime.Text = "only time";
            this.Ser_e_onlytime.UseVisualStyleBackColor = true;
            // 
            // Ser_b_mapdetails
            // 
            this.Ser_b_mapdetails.Location = new System.Drawing.Point(355, 262);
            this.Ser_b_mapdetails.Name = "Ser_b_mapdetails";
            this.Ser_b_mapdetails.Size = new System.Drawing.Size(130, 23);
            this.Ser_b_mapdetails.TabIndex = 22;
            this.Ser_b_mapdetails.Text = "Map to service details";
            this.Ser_b_mapdetails.UseVisualStyleBackColor = true;
            // 
            // Ser_b_maparr
            // 
            this.Ser_b_maparr.Location = new System.Drawing.Point(491, 262);
            this.Ser_b_maparr.Name = "Ser_b_maparr";
            this.Ser_b_maparr.Size = new System.Drawing.Size(114, 23);
            this.Ser_b_maparr.TabIndex = 21;
            this.Ser_b_maparr.Text = "Map to packages";
            this.Ser_b_maparr.UseVisualStyleBackColor = true;
            // 
            // Ser_e_starttime
            // 
            this.Ser_e_starttime.Format = System.Windows.Forms.DateTimePickerFormat.Time;
            this.Ser_e_starttime.Location = new System.Drawing.Point(136, 240);
            this.Ser_e_starttime.Name = "Ser_e_starttime";
            this.Ser_e_starttime.Size = new System.Drawing.Size(79, 20);
            this.Ser_e_starttime.TabIndex = 20;
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
            // Ser_l_starttime
            // 
            this.Ser_l_starttime.Location = new System.Drawing.Point(8, 240);
            this.Ser_l_starttime.Name = "Ser_l_starttime";
            this.Ser_l_starttime.Size = new System.Drawing.Size(100, 23);
            this.Ser_l_starttime.TabIndex = 16;
            this.Ser_l_starttime.Text = "Start time";
            // 
            // Ser_e_act
            // 
            this.Ser_e_act.Location = new System.Drawing.Point(136, 216);
            this.Ser_e_act.Name = "Ser_e_act";
            this.Ser_e_act.Size = new System.Drawing.Size(248, 21);
            this.Ser_e_act.TabIndex = 15;
            // 
            // Ser_l_act
            // 
            this.Ser_l_act.Location = new System.Drawing.Point(8, 216);
            this.Ser_l_act.Name = "Ser_l_act";
            this.Ser_l_act.Size = new System.Drawing.Size(104, 23);
            this.Ser_l_act.TabIndex = 12;
            this.Ser_l_act.Text = "Process / action";
            // 
            // Ser_l_season
            // 
            this.Ser_l_season.Location = new System.Drawing.Point(8, 192);
            this.Ser_l_season.Name = "Ser_l_season";
            this.Ser_l_season.Size = new System.Drawing.Size(100, 23);
            this.Ser_l_season.TabIndex = 10;
            this.Ser_l_season.Text = "Season";
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
            this.TDB_abgrp.Location = new System.Drawing.Point(0, 290);
            this.TDB_abgrp.Name = "TDB_abgrp";
            this.TDB_abgrp.Size = new System.Drawing.Size(613, 56);
            this.TDB_abgrp.TabIndex = 15;
            this.TDB_abgrp.TabStop = false;
            this.TDB_abgrp.Text = "Actions";
            // 
            // TDB_ab_clr
            // 
            this.TDB_ab_clr.Dock = System.Windows.Forms.DockStyle.Right;
            this.TDB_ab_clr.Location = new System.Drawing.Point(460, 16);
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
            this.TDB_ab_exit.Location = new System.Drawing.Point(535, 16);
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
            // Ser_e_season
            // 
            this.Ser_e_season.FormattingEnabled = true;
            this.Ser_e_season.Location = new System.Drawing.Point(136, 189);
            this.Ser_e_season.Name = "Ser_e_season";
            this.Ser_e_season.Size = new System.Drawing.Size(248, 21);
            this.Ser_e_season.TabIndex = 24;
            // 
            // FService
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(613, 346);
            this.Controls.Add(this.TDB_abgrp);
            this.Controls.Add(this.Ser_b_arrdl);
            this.Name = "FService";
            this.Text = "Service";
            this.Ser_b_arrdl.ResumeLayout(false);
            this.Ser_b_arrdl.PerformLayout();
            this.TDB_abgrp.ResumeLayout(false);
            this.ResumeLayout(false);

		}
		#endregion

		#region Form callbacks
		private void TDB_ab_sel_Click(object sender, System.EventArgs e)
		{
			SelForm Fsel = new SelForm();
			service.Sel(Fsel.GetLV);
			Fsel.Accept += new EventHandler(TDB_ab_sel_Click_Return);
			Fsel.ShowDialog(this);
		}

		void TDB_ab_sel_Click_Return(object sender, EventArgs e) 
		{
			int id = -1, rows = 0;
			SelForm Fsel = (SelForm)sender;
			id = Fsel.GetID;
			service.Get(id, ref rows);
            tdb_e_id.Text = service.ObjId.ToString();
            tdb_e_bez.Text = service.ObjBez;
            tdb_e_text.Text = service.ObjText;
            tdb_e_code.Text = service.ObjCode;
            this.Ser_e_act.SelectedValue = service.ObjAction;
            this.Ser_e_season.SelectedValue = service.ObjSeasonId;
            this.Ser_e_starttime.Value = service.ObjStartdate;
        }

		private void TDB_ab_exit_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void TDB_ab_ins_Click(object sender, System.EventArgs e)
		{
            service.InsUpd(true, tdb_e_bez.Text, tdb_e_text.Text, tdb_e_code.Text, (int)this.Ser_e_season.SelectedValue,
                this.Ser_e_starttime.Value, (int)this.Ser_e_act.SelectedValue);
            tdb_e_id.Text = service.ObjId.ToString();
		}

		private void TDB_ab_upd_Click(object sender, System.EventArgs e)
		{
            service.InsUpd(false, tdb_e_bez.Text, tdb_e_text.Text, tdb_e_code.Text, (int)this.Ser_e_season.SelectedValue,
				this.Ser_e_starttime.Value, (int)this.Ser_e_act.SelectedValue);
		}

		private void TDB_ab_del_Click(object sender, System.EventArgs e)
		{
			int rows = 0;
            service.Get(Convert.ToInt32(tdb_e_id.Text), ref rows);
            service.Delete();
		}

		private void TDB_ab_clr_Click(object sender, System.EventArgs e)
		{
			tdb_e_id.Text = "";
			tdb_e_bez.Text = "";
			tdb_e_text.Text = "";
            this.Ser_e_act.Text = "";
            this.Ser_e_season.Text = "";
        }

		private void FService_Load(object sender, System.EventArgs e)
		{
            tdbgui.GUIact A = new tdbgui.GUIact();
            A.SetCombo(this.Ser_e_act);
            tdbgui.GUIsai S = new tdbgui.GUIsai();
            S.SetCombo(this.Ser_e_season);
        }
		#endregion
	}
}
