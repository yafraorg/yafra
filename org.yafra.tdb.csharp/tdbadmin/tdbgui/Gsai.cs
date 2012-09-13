using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Season Forms addons.
	/// </summary>
	public class GUIsai : tdb.Season
	{
		private string selectionsql;

		#region init
		public GUIsai()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_saisel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			// get the first suiteable title and return it
			SeasonVsel workDS = new SeasonVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_saisel" });
			foreach (SeasonVsel.tdbv_saiselRow Rwork in workDS.tdbv_saisel)
			{
				lstitm[0] = Convert.ToString(Rwork.SAI_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			SeasonVsel workDS = new SeasonVsel();

			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");

			FillDS(workDS, selectionsql, new string[] { "tdbv_saisel" });
			foreach (SeasonVsel.tdbv_saiselRow Rwork in workDS.tdbv_saisel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.SAI_ID;
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
