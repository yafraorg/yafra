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
	public class GUIcustt : tdb.Customertype
	{
		private string selectionsql;

		#region init
		public GUIcustt()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_cuttsel where s_id = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			CustTypVsel workDS = new CustTypVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_cuttsel" });
			foreach (CustTypVsel.tdbv_cuttselRow Rwork in workDS.tdbv_cuttsel)
			{
				lstitm[0] = Convert.ToString(Rwork.CUSTTYPE_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.CODE;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			CustTypVsel workDS = new CustTypVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_cuttsel" });
			foreach (CustTypVsel.tdbv_cuttselRow Rwork in workDS.tdbv_cuttsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.CUSTTYPE_ID;
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
