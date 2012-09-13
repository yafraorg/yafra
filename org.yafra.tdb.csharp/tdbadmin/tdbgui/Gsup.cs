using System;
using System.Data;
//using System.Data.DataSetExtensions;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// supplier type.
	/// </summary>
	public class GUIsup : tdb.Sup
	{
		private string selectionsql;

		#region init
		public GUIsup()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_dltsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void SelTree(System.Windows.Forms.TreeView Atv)
		{
			string sql;
			DltV workDS = new DltV();
			sql = String.Format("Select * from tdbadmin.tdbv_dlt where s_id = {0} and h_dlt_id < 1 order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dlt" });
            foreach (DltV.tdbv_dltRow Rwork in workDS.tdbv_dlt)
			{
				TreeNode RootNode = new TreeNode(Rwork.BEZ);
				RootNode.Tag = Rwork.DLT_ID;
				Atv.Nodes.Add(RootNode);
				GetChild(Rwork.DLT_ID, RootNode);
			}
		}

		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			DltVsel workDS;

			// get the first suiteable title and return it
			workDS = new DltVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_dltsel" });
			foreach (DltVsel.tdbv_dltselRow Rwork in workDS.tdbv_dltsel)
			{
				lstitm[0] = Convert.ToString(Rwork.DLT_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			DltVsel workDS;

			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");

			workDS = new DltVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_dltsel" });
			foreach (DltVsel.tdbv_dltselRow Rwork in workDS.tdbv_dltsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.DLT_ID;
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
			DltV workDS = new DltV();
			sql = String.Format("Select * from tdbadmin.tdbv_dlt where s_id = {0} and h_dlt_id = {1} order by bez", tdb.User.Ulangid, Aparentid);
			FillDS(workDS, sql, new string[] { "tdbv_dlt" });
			rows = workDS.tdbv_dlt.Rows.Count;
			if (rows < 1)
				return;
			foreach (DltV.tdbv_dltRow Rwork in workDS.tdbv_dlt)
			{
				TreeNode ChildNode = new TreeNode(Rwork.BEZ);
				ChildNode.Tag = Rwork.DLT_ID;
				Aparentnode.Nodes.Add(ChildNode);
				GetChild(Rwork.DLT_ID, ChildNode);
			}
		}
	
	}
}
