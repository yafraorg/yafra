using System;
using System.Data;
using System.Windows.Forms;
using org.swyn.foundation.utils;
using tdb;
using tdb.DS;


namespace tdbgui
{
	/// <summary>
	/// Languages
	/// - sysbez has to be alligned to the language part of the .NET culture
	/// </summary>
	public class GUIlang : tdb.Language
	{
		private string selectionsql;

		#region init
		public GUIlang()
		{
			//
			// TODO: Add constructor logic here
			//
			selectionsql = String.Format("Select * from tdbadmin.tdbv_langsel where bezsprid = {0} order by bez", tdb.User.Ulangid);
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public void Sel(System.Windows.Forms.ListView Alv)
		{
			string [] lstitm = new string [3];
			LangVsel workDS = new LangVsel();
			FillDS(workDS, selectionsql, new string[] { "tdbv_langsel" });
			foreach (LangVsel.tdbv_langselRow Rwork in workDS.tdbv_langsel)
			{
				lstitm[0] = Convert.ToString(Rwork.S_ID);
				lstitm[1] = Rwork.BEZ;
				lstitm[2] = Rwork.SYSBEZ;
				Alv.Items.Add(new ListViewItem(lstitm));
			}
		}

		public void SetCombo(System.Windows.Forms.ComboBox Acombo)
		{
			DataTable workDT = new DataTable();
			DataRow row;
			LangVsel workDS = new LangVsel();
			workDT.Columns.Add("id", typeof(int));
			workDT.Columns.Add("desc");
			FillDS(workDS, selectionsql, new string[] { "tdbv_langsel" });
			foreach (LangVsel.tdbv_langselRow Rwork in workDS.tdbv_langsel)
			{
				row = workDT.NewRow();
				row["id"]   = Rwork.S_ID;
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
