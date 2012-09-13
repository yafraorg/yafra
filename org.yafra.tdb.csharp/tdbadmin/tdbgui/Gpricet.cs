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
	public class GUIpricet : tdb.Pricetype
	{
		private string selectionsql;

		#region init
		public GUIpricet()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_prtsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [2];
			Alv.Columns.RemoveAt(2);
			PrtVsel workDS = new PrtVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_prtsel" });
			foreach (PrtVsel.tdbv_prtselRow Rwork in workDS.tdbv_prtsel)
			{
				lstitm[0] = Convert.ToString(Rwork.PRT_ID);
				lstitm[1] = Rwork.BEZ;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			PrtVsel workDS = new PrtVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_prtsel" });
			foreach (PrtVsel.tdbv_prtselRow Rwork in workDS.tdbv_prtsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.PRT_ID;
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
