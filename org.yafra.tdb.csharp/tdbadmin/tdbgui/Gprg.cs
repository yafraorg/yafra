using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Program Forms addons
	/// </summary>
	public class GUIprg : tdb.Prg
	{
		private string selectionsql;

		#region init
		public GUIprg()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_prgsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion

		#region Object Methods/Functions (get one, selection, insert, update, delete)

		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			PrgVsel workDS = new PrgVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_prgsel" });
			foreach (PrgVsel.tdbv_prgselRow Rwork in workDS.tdbv_prgsel)
			{
				lstitm[0] = Convert.ToString(Rwork.PRG_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			PrgVsel workDS = new PrgVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_prgsel" });
			foreach (PrgVsel.tdbv_prgselRow Rwork in workDS.tdbv_prgsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.PRG_ID;
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
