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
	public class GUIserviceoffer : tdb.Serviceoffer
	{
		private string selectionsql;

		#region init
        public GUIserviceoffer()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_sosel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [4];
            System.Windows.Forms.ColumnHeader Sel_dat;
            Sel_dat = new System.Windows.Forms.ColumnHeader();
            Sel_dat.Text = "Date";
            Sel_dat.Width = 140;
            Alv.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
				Sel_dat});
            SoVsel workDS = new SoVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_sosel" });
            foreach (SoVsel.tdbv_soselRow Rwork in workDS.tdbv_sosel)
			{
				lstitm[0] = Convert.ToString(Rwork.SO_ID);
				lstitm[1] = Rwork.BEZ;
                lstitm[2] = Rwork.CODE;
                lstitm[3] = Rwork.STARTDAT.ToString();
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
            SoVsel workDS = new SoVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_sosel" });
            foreach (SoVsel.tdbv_soselRow Rwork in workDS.tdbv_sosel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.SO_ID;
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
