using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Offertype Forms addons
	/// </summary>
	public class GUIofft : tdb.Offertype
	{
		private string selectionsql;

		#region init
		public GUIofft()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_otsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [2];
			Alv.Columns.RemoveAt(2);
			OffertypeVsel workDS = new OffertypeVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_otsel" });
			foreach (OffertypeVsel.tdbv_otselRow Rwork in workDS.tdbv_otsel)
			{
				lstitm[0] = Convert.ToString(Rwork.OT_ID);
				lstitm[1] = Rwork.BEZ;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			OffertypeVsel workDS = new OffertypeVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_otsel" });
			foreach (OffertypeVsel.tdbv_otselRow Rwork in workDS.tdbv_otsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.OT_ID;
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
