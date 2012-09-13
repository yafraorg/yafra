using System;
using System.Drawing;
using System.Collections;
using System.Data;
using System.Text.RegularExpressions; 
using System.ComponentModel;
using System.Windows.Forms;

namespace tdbadmin
{
	/// <summary>
	/// Summary description for ActionSelForm.
	/// </summary>
	public class SelForm : System.Windows.Forms.Form
	{
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button Sel_b_ok;
		private System.Windows.Forms.Button Sel_b_search;
		private System.Windows.Forms.Button Sel_b_cancel;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.ColumnHeader Sel_id;
		private System.Windows.Forms.ColumnHeader Sel_bez;
		private System.Windows.Forms.ColumnHeader Sel_code;
		private bool itemselected;
		private int selid;
		public event EventHandler Accept;
		private ListViewColumnSorter lvwColumnSorter;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public SelForm()
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

			// Create an instance of a ListView column sorter and assign it 
			// to the ListView control.
			lvwColumnSorter = new ListViewColumnSorter();
			this.listView1.ListViewItemSorter = lvwColumnSorter;
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
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Sel_b_cancel = new System.Windows.Forms.Button();
			this.Sel_b_search = new System.Windows.Forms.Button();
			this.Sel_b_ok = new System.Windows.Forms.Button();
			this.listView1 = new System.Windows.Forms.ListView();
			this.Sel_id = new System.Windows.Forms.ColumnHeader();
			this.Sel_bez = new System.Windows.Forms.ColumnHeader();
			this.Sel_code = new System.Windows.Forms.ColumnHeader();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Sel_b_cancel);
			this.groupBox2.Controls.Add(this.Sel_b_search);
			this.groupBox2.Controls.Add(this.Sel_b_ok);
			this.groupBox2.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBox2.Location = new System.Drawing.Point(0, 333);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(568, 56);
			this.groupBox2.TabIndex = 1;
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
			// 
			// Sel_b_ok
			// 
			this.Sel_b_ok.Location = new System.Drawing.Point(8, 24);
			this.Sel_b_ok.Name = "Sel_b_ok";
			this.Sel_b_ok.TabIndex = 0;
			this.Sel_b_ok.Text = "OK";
			this.Sel_b_ok.Click += new System.EventHandler(this.Sel_b_ok_Click);
			// 
			// listView1
			// 
			this.listView1.AllowColumnReorder = true;
			this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																												this.Sel_id,
																												this.Sel_bez,
																												this.Sel_code});
			this.listView1.Dock = System.Windows.Forms.DockStyle.Top;
			this.listView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.listView1.ForeColor = System.Drawing.SystemColors.HotTrack;
			this.listView1.FullRowSelect = true;
			this.listView1.GridLines = true;
			this.listView1.Location = new System.Drawing.Point(0, 0);
			this.listView1.MultiSelect = false;
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(568, 312);
			this.listView1.TabIndex = 2;
			this.listView1.View = System.Windows.Forms.View.Details;
			this.listView1.DoubleClick += new System.EventHandler(this.Sel_b_ok_Click);
			this.listView1.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.listView1_ColumnClick);
			this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
			// 
			// Sel_id
			// 
			this.Sel_id.Text = "ID";
			this.Sel_id.Width = 50;
			// 
			// Sel_bez
			// 
			this.Sel_bez.Text = "Title";
			this.Sel_bez.Width = 250;
			// 
			// Sel_code
			// 
			this.Sel_code.Text = "Code";
			this.Sel_code.Width = 250;
			// 
			// SelForm
			// 
			this.AcceptButton = this.Sel_b_ok;
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.CancelButton = this.Sel_b_cancel;
			this.ClientSize = new System.Drawing.Size(568, 389);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.groupBox2);
			this.MinimizeBox = false;
			this.Name = "SelForm";
			this.Text = "Selection";
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		#region Get and Set flags and vars
		public int GetID { get {return selid;}}
		public ListView GetLV { get {return listView1;}}
		#endregion

		#region Callbacks
		private void Sel_b_cancel_Click(object sender, System.EventArgs e)
		{
			Close();
		}

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

		private void listView1_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			int k;
			k = listView1.SelectedItems.Count;
			if (k == 0)
				itemselected = false;
			else
			{
				itemselected = true;
				foreach (ListViewItem lvi in listView1.SelectedItems)
					selid = Convert.ToInt32(lvi.Text);
			}
		}
		private void listView1_ColumnClick(object sender, System.Windows.Forms.ColumnClickEventArgs e)
		{
			// Determine if clicked column is already the column that is being sorted.
			if ( e.Column == lvwColumnSorter.SortColumn )
			{
				// Reverse the current sort direction for this column.
				if (lvwColumnSorter.Order == SortOrder.Ascending)
				{
					lvwColumnSorter.Order = SortOrder.Descending;
				}
				else
				{
					lvwColumnSorter.Order = SortOrder.Ascending;
				}
			}
			else
			{
				// Set the column number that is to be sorted; default to ascending.
				lvwColumnSorter.SortColumn = e.Column;
				lvwColumnSorter.Order = SortOrder.Ascending;
			}

			// Perform the sort with these new sort options.
			this.listView1.Sort();

		}

		#endregion
	}

	#region List view sorter class
	/// <summary>
	/// This class is an implementation of the 'IComparer' interface.
	/// </summary>
	public class ListViewColumnSorter : IComparer
	{
		/// <summary>
		/// Specifies the column to be sorted
		/// </summary>
		private int ColumnToSort;
		/// <summary>
		/// Specifies the order in which to sort (i.e. 'Ascending').
		/// </summary>
		private SortOrder OrderOfSort;
		/// <summary>
		/// Case insensitive comparer object
		/// </summary>  private NumberCaseInsensitiveComparer ObjectCompare;
		private ImageTextComparer FirstObjectCompare;
		private NumberCaseInsensitiveComparer ObjectCompare;
		/// <summary>
		/// Class constructor.  Initializes various elements
		/// </summary>
		public ListViewColumnSorter()
		{
			// Initialize the column to '0'
			ColumnToSort = 0;
			// Initialize the sort order to 'none'
			//OrderOfSort = SortOrder.None;
			OrderOfSort = SortOrder.Ascending;
			// Initialize my implementationof CaseInsensitiveComparer object
			ObjectCompare = new NumberCaseInsensitiveComparer();
			FirstObjectCompare = new ImageTextComparer();
		}  /// <summary>
		/// This method is inherited from the IComparer interface.
		/// It compares the two objects passed\
		/// using a case insensitive comparison.
		/// </summary>
		/// <param name="x">First object to be compared</param>
		/// <param name="y">Second object to be compared</param>
		/// <returns>The result of the comparison. "0" if equal,
		/// negative if 'x' is less than 'y' and positive
		/// if 'x' is greater than 'y'</returns>
		public int Compare(object x, object y)
		{
			int compareResult;
			ListViewItem listviewX, listviewY;
			// Cast the objects to be compared to ListViewItem objects
			listviewX = (ListViewItem)x;
			listviewY = (ListViewItem)y;
			if (ColumnToSort == 0)
			{
				compareResult = FirstObjectCompare.Compare(x,y);
			}
			else
			{
				// Compare the two items
				compareResult = 
					ObjectCompare.Compare(listviewX.SubItems[ColumnToSort].Text,
					listviewY.SubItems[ColumnToSort].Text);
			}
			// Calculate correct return value based on object comparison
			if (OrderOfSort == SortOrder.Ascending)
			{
				// Ascending sort is selected,
				// return normal result of compare operation
				return compareResult;
			}
			else if (OrderOfSort == SortOrder.Descending)
			{
				// Descending sort is selected,
				// return negative result of compare operation
				return (-compareResult);
			}
			else
			{
				// Return '0' to indicate they are equal
				return 0;
			}
		}
    
		/// <summary>
		/// Gets or sets the number of the column to which
		/// to apply the sorting operation (Defaults to '0').
		/// </summary>
		public int SortColumn
		{
			set
			{
				ColumnToSort = value;
			}
			get
			{
				return ColumnToSort;
			}
		}
		/// <summary>
		/// Gets or sets the order of sorting to apply
		/// (for example, 'Ascending' or 'Descending').
		/// </summary>
		public SortOrder Order
		{
			set
			{
				OrderOfSort = value;
			}
			get
			{
				return OrderOfSort;
			}
		}
    
	}
	public class ImageTextComparer : IComparer
	{
		//private CaseInsensitiveComparer ObjectCompare;
		private NumberCaseInsensitiveComparer ObjectCompare;
        
		public ImageTextComparer()
		{
			// Initialize the CaseInsensitiveComparer object
			ObjectCompare = new NumberCaseInsensitiveComparer();
		}
		public int Compare(object x, object y)
		{
			//int compareResult;
			int image1, image2;
			ListViewItem listviewX, listviewY;
			// Cast the objects to be compared to ListViewItem objects
			listviewX = (ListViewItem)x;
			image1 = listviewX.ImageIndex;
			listviewY = (ListViewItem)y;
			image2 = listviewY.ImageIndex;
			if (image1 < image2)
			{
				return -1;
			}
			else if (image1 == image2)
			{
				return ObjectCompare.Compare(listviewX.Text,listviewY.Text);
			}
			else
			{
				return 1;
			}
		}
	}
	public class NumberCaseInsensitiveComparer : CaseInsensitiveComparer
	{
		public NumberCaseInsensitiveComparer ()
		{
   
		}
		public new int Compare(object x, object y)
		{ 
			// in case x,y are strings and actually number,
			// convert them to int and use the base.Compare for comparison
			if ((x is System.String) && IsWholeNumber((string)x) 
				&& (y is System.String) && IsWholeNumber((string)y))
			{
				return base.Compare(System.Convert.ToInt32(x),
					System.Convert.ToInt32(y));
			}
			else
			{
				return base.Compare(x,y);
			}
		}
		private bool IsWholeNumber(string strNumber)
		{ // use a regular expression to find out if string is actually a number
			Regex objNotWholePattern=new Regex("[^0-9]");
			return !objNotWholePattern.IsMatch(strNumber);
		}  
	}

	#endregion

}
