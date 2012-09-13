using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// category
	/// </summary>
	public class GUIcat : tdb.Category
	{
		private string selectionsql;

		#region init
		public GUIcat()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_catsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void SelTree(System.Windows.Forms.TreeView Atv)
		{
			string sql;
			CatV workDS = new CatV();
			sql = String.Format("Select * from tdbadmin.tdbv_cat where s_id = {0} and h_kat_id < 1 order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cat" });
			foreach (CatV.tdbv_catRow Rwork in workDS.tdbv_cat)
			{
				TreeNode RootNode = new TreeNode(Rwork.BEZ);
				RootNode.Tag = Rwork.CAT_ID;
				Atv.Nodes.Add(RootNode);
				GetChild(Rwork.CAT_ID, RootNode);
			}
		}

		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string sql;
			string [] lstitm = new string [4];
			Alv.Columns.RemoveAt(2);
			System.Windows.Forms.ColumnHeader Sel_dltt = new System.Windows.Forms.ColumnHeader();
			System.Windows.Forms.ColumnHeader Sel_dlttid = new System.Windows.Forms.ColumnHeader();
			Alv.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
																												Sel_dlttid,
																												Sel_dltt});
			Sel_dlttid.Text = "Suppliertype ID";
			Sel_dlttid.Width = 40;
			Sel_dltt.Text = "Suppliertype";
			Sel_dltt.Width = 180;

			// get the first suiteable title and return it
			CatV workDS = new CatV();
			sql = String.Format("Select * from tdbadmin.tdbv_cat where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cat" });
			foreach (CatV.tdbv_catRow Rwork in workDS.tdbv_cat)
			{
				lstitm[0] = Convert.ToString(Rwork.CAT_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Convert.ToString(Rwork.SUPTYPID);
				lstitm[3] = Rwork.SUPTYP;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CatVsel workDS;

			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");

			workDS = new CatVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_catsel" });
			foreach (CatVsel.tdbv_catselRow Rwork in workDS.tdbv_catsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.CAT_ID;
				row["desc"] = Rwork.BEZ;
				workDT.Rows.Add(row);
			}
			if (optional == true)
			{
				row = workDT.NewRow();
				row["id"]   = (int)-1;
				row["desc"] = "";
				workDT.Rows.Add(row);
			}
			Acombo.DataSource  = workDT;
			Acombo.DisplayMember = "desc";
			Acombo.ValueMember  = "id";
		}

		#endregion

		private void GetChild(int Aparentid, TreeNode Aparentnode)
		{
			string sql;
			int rows;
			CatV workDS = new CatV();
			sql = String.Format("Select * from tdbadmin.tdbv_cat where s_id = {0} and h_kat_id = {1} order by bez", tdb.User.Ulangid, Aparentid);
			FillDS(workDS, sql, new string[] { "tdbv_cat" });
			rows = workDS.tdbv_cat.Rows.Count;
			if (rows < 1)
				return;
			foreach (CatV.tdbv_catRow Rwork in workDS.tdbv_cat)
			{
				TreeNode ChildNode = new TreeNode(Rwork.BEZ);
				ChildNode.Tag = Rwork.CAT_ID;
				Aparentnode.Nodes.Add(ChildNode);
				GetChild(Rwork.CAT_ID, ChildNode);
			}
		}
	
	}
}
