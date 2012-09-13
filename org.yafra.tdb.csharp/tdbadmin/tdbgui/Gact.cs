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
	public class GUIact : tdb.Act
	{
		private string selectionsql;

		#region init
		public GUIact()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_actsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [2];
			ActVsel workDS = new ActVsel();
			Alv.Columns.RemoveAt(2);
			FillDS(workDS, selectionsql, new string[] { "tdbv_actsel" });
			foreach (ActVsel.tdbv_actselRow Rwork in workDS.tdbv_actsel)
			{
				lstitm[0] = Convert.ToString(Rwork.ACT_ID);
				lstitm[1] = Rwork.BEZ;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			ActVsel workDS = new ActVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_actsel" });
			foreach (ActVsel.tdbv_actselRow Rwork in workDS.tdbv_actsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.ACT_ID;
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
