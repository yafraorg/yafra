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
	public class GUIperst : tdb.Persontype
	{
		private string selectionsql;

		#region init
		public GUIperst()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_perstsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			PersTypVsel workDS = new PersTypVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_perstsel" });
			foreach (PersTypVsel.tdbv_perstselRow Rwork in workDS.tdbv_perstsel)
			{
				lstitm[0] = Convert.ToString(Rwork.PERSTYPE_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			PersTypVsel workDS = new PersTypVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_perstsel" });
			foreach (PersTypVsel.tdbv_perstselRow Rwork in workDS.tdbv_perstsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.PERSTYPE_ID;
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
