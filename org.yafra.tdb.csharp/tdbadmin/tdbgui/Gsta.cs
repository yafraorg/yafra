using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;

namespace tdbgui
{
	/// <summary>
	/// Status values Forms addons
	/// </summary>
	public class GUIsta : tdb.Status
	{
		#region init
		public GUIsta()
		{
			//
			// TODO: Add constructor logic here
			//
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			string sql;
			StatusVsel workDS = new StatusVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_stasel where s_id = {0} and typ = {1} order by bez", tdb.User.Ulangid, status_typ);
			FillDS(workDS, sql, new string[] { "tdbv_stasel" });
			foreach (StatusVsel.tdbv_staselRow Rwork in workDS.tdbv_stasel)
			{
				lstitm[0] = Convert.ToString(Rwork.STA_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			string sql;
			DataTable workDT = new DataTable();
			DataRow row;
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			StatusVsel workDS = new StatusVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_stasel where s_id = {0} and typ = {1} order by bez", tdb.User.Ulangid, status_typ);
			FillDS(workDS, sql, new string[] { "tdbv_stasel" });
			foreach (StatusVsel.tdbv_staselRow Rwork in workDS.tdbv_stasel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.STA_ID;
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


		public void SetComboTyp(System.Windows.Forms.ComboBox Acombo)
		{
			string sql;
			DataTable workDT = new DataTable();
			DataRow row;
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			TitleDS workDS = new TitleDS();
			sql = String.Format("Select * from tdbadmin.bezeichnung where s_id = {0} and bez_id = 0 and typ > 999 order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "bezeichnung" });
			foreach (TitleDS.bezeichnungRow Rwork in workDS.bezeichnung)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.TYP;
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
