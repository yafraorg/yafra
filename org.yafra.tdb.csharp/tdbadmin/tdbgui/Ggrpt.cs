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
	public class GUIgrpt : tdb.Grouptype
	{
		private string selectionsql;

		#region init
		public GUIgrpt()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_grptsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			GrpTypVsel workDS = new GrpTypVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_grptsel" });
			foreach (GrpTypVsel.tdbv_grptselRow Rwork in workDS.tdbv_grptsel)
			{
				lstitm[0] = Convert.ToString(Rwork.GRPTYPE_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			GrpTypVsel workDS = new GrpTypVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_grptsel" });
			foreach (GrpTypVsel.tdbv_grptselRow Rwork in workDS.tdbv_grptsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.GRPTYPE_ID;
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
