using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for SelTreeForm.
	/// </summary>
	public class SelTreeForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TreeView treeView1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button Sel_b_cancel;
		private System.Windows.Forms.Button Sel_b_search;
		private System.Windows.Forms.Button Sel_b_ok;
		public event EventHandler Accept;
		private bool itemselected;
		private int selid;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public SelTreeForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			itemselected = false;
			selid = -1;
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
			this.treeView1 = new System.Windows.Forms.TreeView();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Sel_b_cancel = new System.Windows.Forms.Button();
			this.Sel_b_search = new System.Windows.Forms.Button();
			this.Sel_b_ok = new System.Windows.Forms.Button();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeView1.ImageIndex = -1;
			this.treeView1.Location = new System.Drawing.Point(0, 0);
			this.treeView1.Name = "treeView1";
			this.treeView1.SelectedImageIndex = -1;
			this.treeView1.Size = new System.Drawing.Size(448, 413);
			this.treeView1.Sorted = true;
			this.treeView1.TabIndex = 0;
			this.treeView1.DoubleClick += new System.EventHandler(this.Sel_b_ok_Click);
			this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Sel_b_cancel);
			this.groupBox2.Controls.Add(this.Sel_b_search);
			this.groupBox2.Controls.Add(this.Sel_b_ok);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBox2.Location = new System.Drawing.Point(0, 357);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(448, 56);
			this.groupBox2.TabIndex = 2;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Actions";
			// 
			// Sel_b_cancel
			// 
			this.Sel_b_cancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.Sel_b_cancel.Location = new System.Drawing.Point(216, 24);
			this.Sel_b_cancel.Name = "Sel_b_cancel";
			this.Sel_b_cancel.TabIndex = 2;
			this.Sel_b_cancel.Text = "Cancel";
			this.Sel_b_cancel.Click += new System.EventHandler(this.Sel_b_cancel_Click);
			// 
			// Sel_b_search
			// 
			this.Sel_b_search.Location = new System.Drawing.Point(112, 24);
			this.Sel_b_search.Name = "Sel_b_search";
			this.Sel_b_search.TabIndex = 1;
			this.Sel_b_search.Text = "Search";
			this.Sel_b_search.Click += new System.EventHandler(this.Sel_b_search_Click);
			// 
			// Sel_b_ok
			// 
			this.Sel_b_ok.Location = new System.Drawing.Point(8, 24);
			this.Sel_b_ok.Name = "Sel_b_ok";
			this.Sel_b_ok.TabIndex = 0;
			this.Sel_b_ok.Text = "OK";
			this.Sel_b_ok.Click += new System.EventHandler(this.Sel_b_ok_Click);
			// 
			// SelTreeForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(448, 413);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.treeView1);
			this.Name = "SelTreeForm";
			this.Text = "Selection dialog";
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Get and Set flags and vars
		public int GetID { get {return selid;}}
		public TreeView GetTV { get {return treeView1;}}

		#endregion

		#region Callbacks
		private void Sel_b_ok_Click(object sender, System.EventArgs e)
		{
			if (!itemselected)
				MessageBox.Show("please select an item first");
			else
			{
				Accept(this, EventArgs.Empty);
				this.Close();
			}
		}

		private void Sel_b_search_Click(object sender, System.EventArgs e)
		{
		
		}

		private void Sel_b_cancel_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		
		private void treeView1_AfterSelect(object sender, System.Windows.Forms.TreeViewEventArgs e)
		{
			itemselected = true;
			selid = (int)e.Node.Tag;
		}

		#endregion
	}
}
