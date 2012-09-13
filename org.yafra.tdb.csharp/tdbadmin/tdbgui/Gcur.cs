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
	public class GUIcur : tdb.Currency
	{
		private string selectionsql;

		#region init
		public GUIcur()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_cursel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			CurVsel workDS = new CurVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_cursel" });
			foreach (CurVsel.tdbv_curselRow Rwork in workDS.tdbv_cursel)
			{
				lstitm[0] = Convert.ToString(Rwork.WHR_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.KRZL;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CurVsel workDS = new CurVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_cursel" });
			foreach (CurVsel.tdbv_curselRow Rwork in workDS.tdbv_cursel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.WHR_ID;
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
