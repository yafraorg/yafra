using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Arrangement Forms addons.
	/// - add start date to arrsel view for selection and probably for combox as string concat
	/// </summary>
	public class GUIarr : tdb.Arr
	{
		private string selectionsql;

		#region init
		public GUIarr()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_arrsel where s_id = {0} order by bez", tdb.User.Ulangid);
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
			ArrVsel workDS = new ArrVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_arrsel" });
			foreach (ArrVsel.tdbv_arrselRow Rwork in workDS.tdbv_arrsel)
			{
				lstitm[0] = Convert.ToString(Rwork.ARR_ID);
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
			string arrbez;
			ArrVsel workDS = new ArrVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_arrsel" });
			foreach (ArrVsel.tdbv_arrselRow Rwork in workDS.tdbv_arrsel)
			{
				arrbez = String.Format("{0} {1}", Rwork.BEZ, Rwork.ADAT.ToString());
				row = workDT.NewRow();
				row["id"]   = Rwork.ARR_ID;
				row["desc"] = arrbez;
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
