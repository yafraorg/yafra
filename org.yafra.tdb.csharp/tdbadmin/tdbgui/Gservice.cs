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
	public class GUIservice : tdb.Service
	{
		private string selectionsql;

		#region init
		public GUIservice()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_servsel where s_id = {0} order by bez", tdb.User.Ulangid);
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
            ServVsel workDS = new ServVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_servsel" });
            foreach (ServVsel.tdbv_servselRow Rwork in workDS.tdbv_servsel)
			{
				lstitm[0] = Convert.ToString(Rwork.SERV_ID);
				lstitm[1] = Rwork.BEZ;
                lstitm[2] = Rwork.CODE;
                lstitm[3] = Rwork.ADAT.ToString();
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
            ServVsel workDS = new ServVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_servsel" });
            foreach (ServVsel.tdbv_servselRow Rwork in workDS.tdbv_servsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.SERV_ID;
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
