using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Summary description for Country.
	/// </summary>
	public class GUIcity : tdb.City
	{
		private string selectionsql;

		#region init
		public GUIcity()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_citysel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)

		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			CityVsel workDS = new CityVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_citysel" });
			foreach (CityVsel.tdbv_cityselRow Rwork in workDS.tdbv_citysel)
			{
				lstitm[0] = Convert.ToString(Rwork.ORT_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.KRZL;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CityVsel workDS = new CityVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_citysel" });
			foreach (CityVsel.tdbv_cityselRow Rwork in workDS.tdbv_citysel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.ORT_ID;
				row["desc"] = Rwork.BEZ;
				workDT.Rows.Add(row);
			}
			Acombo.DataSource  = workDT;
			Acombo.DisplayMember = "desc";
			Acombo.ValueMember  = "id";
		}

		#endregion
	}
}
