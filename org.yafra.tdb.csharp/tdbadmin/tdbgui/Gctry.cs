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
	public class GUIctry : tdb.Country
	{
		private string selectionsql;

		#region init
		public GUIctry()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_countrysel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			CountryVsel workDS = new CountryVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_countrysel" });
			foreach (CountryVsel.tdbv_countryselRow Rwork in workDS.tdbv_countrysel)
			{
				lstitm[0] = Convert.ToString(Rwork.LAND_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.KRZL;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CountryVsel workDS = new CountryVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_countrysel" });
			foreach (CountryVsel.tdbv_countryselRow Rwork in workDS.tdbv_countrysel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.LAND_ID;
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
