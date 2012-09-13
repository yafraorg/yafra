using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Actiontype Forms addons
	/// </summary>
	public class GUIactt : tdb.Acttype
	{
		private string selectionsql;

		#region init
		public GUIactt()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_acttsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			ActtypeVsel workDS = new ActtypeVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_acttsel" });
			foreach (ActtypeVsel.tdbv_acttselRow Rwork in workDS.tdbv_acttsel)
			{
				lstitm[0] = Convert.ToString(Rwork.ACTTYPE_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			ActtypeVsel workDS = new ActtypeVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_acttsel" });
			foreach (ActtypeVsel.tdbv_acttselRow Rwork in workDS.tdbv_acttsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.ACTTYPE_ID;
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
	}
}
