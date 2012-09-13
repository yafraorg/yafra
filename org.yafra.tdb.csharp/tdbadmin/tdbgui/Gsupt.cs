using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// supplier type.
	/// </summary>
	public class GUIsuptype : tdb.Suptype
	{
		private string selectionsql;

		#region init
		public GUIsuptype()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_dlttsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void SelTree(System.Windows.Forms.TreeView Atv)
		{
			string sql;
			DlttV workDS = new DlttV();
			sql = String.Format("Select * from tdbadmin.tdbv_dltt where s_id = {0} and h_typ_id < 1 order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dltt" });
			foreach (DlttV.tdbv_dlttRow Rwork in workDS.tdbv_dltt)
			{
				TreeNode RootNode = new TreeNode(Rwork.BEZ);
				RootNode.Tag = Rwork.TYP_ID;
				Atv.Nodes.Add(RootNode);
				GetChild(Rwork.TYP_ID, RootNode);
			}
		}

		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [2];
			DlttVsel workDS;
			Alv.Columns.RemoveAt(2);

			// get the first suiteable title and return it
			workDS = new DlttVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_dlttsel" });
			foreach (DlttVsel.tdbv_dlttselRow Rwork in workDS.tdbv_dlttsel)
			{
				lstitm[0] = Convert.ToString(Rwork.TYP_ID);
				lstitm[1] = Rwork.BEZ;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			DlttVsel workDS;

			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");

			workDS = new DlttVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_dlttsel" });
			foreach (DlttVsel.tdbv_dlttselRow Rwork in workDS.tdbv_dlttsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.TYP_ID;
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
			DlttV workDS = new DlttV();
			sql = String.Format("Select * from tdbadmin.tdbv_dltt where s_id = {0} and h_typ_id = {1} order by bez", tdb.User.Ulangid, Aparentid);
			FillDS(workDS, sql, new string[] { "tdbv_dltt" });
			rows = workDS.tdbv_dltt.Rows.Count;
			if (rows < 1)
				return;
			foreach (DlttV.tdbv_dlttRow Rwork in workDS.tdbv_dltt)
			{
				TreeNode ChildNode = new TreeNode(Rwork.BEZ);
				ChildNode.Tag = Rwork.TYP_ID;
				Aparentnode.Nodes.Add(ChildNode);
				GetChild(Rwork.TYP_ID, ChildNode);
			}
		}
	
	}
}
