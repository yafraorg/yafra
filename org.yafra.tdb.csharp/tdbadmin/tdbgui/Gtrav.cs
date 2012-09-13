using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Country.
	/// - add culture and region info from .NET
	/// - dateformat has to be alligned to the culture country part
	/// </summary>
	public class GUItrav : tdb.Traveler
	{
		private string selectionsql;

		#region init
		public GUItrav()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_custsel order by name");
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [2];
			Alv.Columns.RemoveAt(2);
			CustVsel workDS = new CustVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_custsel" });
			foreach (CustVsel.tdbv_custselRow Rwork in workDS.tdbv_custsel)
			{
				lstitm[0] = Convert.ToString(Rwork.PERS_ID);
				lstitm[1] = Rwork.NAME;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CustVsel workDS = new CustVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_custsel" });
			foreach (CustVsel.tdbv_custselRow Rwork in workDS.tdbv_custsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.PERS_ID;
				row["desc"] = Rwork.NAME;
				workDT.Rows.Add(row);
			}
			Acombo.DataSource  = workDT;
			Acombo.DisplayMember = "desc";
			Acombo.ValueMember  = "id";
		}



		#endregion
	}
}
