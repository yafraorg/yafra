using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Summary description for Country.
	/// </summary>
	public class Currency : tdbroot
	{
		private int staid;

		#region init
		public Currency()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.waehrung;
		}
		#endregion

		public virtual int ObjStaid { get {return staid;} set {staid = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows = 0;
			CurV workDS;

			// get the first suiteable title and return it
			workDS = new CurV();
			sql = String.Format("Select * from tdbadmin.tdbv_cur where whr_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cur" });
			Arows = workDS.tdbv_cur.Rows.Count;
			CurV.tdbv_curRow Rwork = workDS.tdbv_cur[0];

			// set variables now
			id = Rwork.WHR_ID;
			code = Rwork.KRZL;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			staid = Rwork.STATUS;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			CurVsel workDS;

			// get the first suiteable title and return it
			workDS = new CurVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_cursel where whr_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cursel" });
			CurVsel.tdbv_curselRow Rwork = workDS.tdbv_cursel[0];
			id = Rwork.WHR_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CurVsel workDS;

			// get the first suiteable title and return it
			workDS = new CurVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_cursel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cursel" });
			Arows = workDS.tdbv_cursel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (CurVsel.tdbv_curselRow Rwork in workDS.tdbv_cursel)
			{
				result[i,0] = Convert.ToString(Rwork.WHR_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.KRZL;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Astaid)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			staid = Astaid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{

				// first get a new unique ID for bez and then sai
				id = NewID("waehrung", "WHR_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert object
				sql = String.Format("insert into tdbadmin.waehrung values({0}, {1}, {2}, {3}, '{4}')", id, bez_id, text_id, staid, code);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				// update bez with user lang
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update object
				sql = String.Format("update tdbadmin.waehrung set krzl = '{0}', status = {1}, textid = {2} where whr_id = {3}", code, staid, text_id, id);
				rowsaffected = DBcmd(sql);
			}
			// commit
			Commit();
		}
		public override void Delete()
		{
			int rowsaffected;
			string sql;

			// delete Country
			sql = String.Format("delete from tdbadmin.waehrung where whr_id = {0}", id);
			rowsaffected = DBcmd(sql);
			// IMPLEMENT cascading deletion if still dependencies here ??
			if (rowsaffected > 0)
			{
				// delete bezeichnung
				sql = String.Format("delete from tdbadmin.bezeichnung where bez_id = {0} and typ = {1}", bez_id, typ);
				rowsaffected = DBcmd(sql);

				// if textid is not set to undef (-1) delete text entries
				if (text_id > 0)
				{
					sql = String.Format("delete from tdbadmin.texte where textid = {0} and typ = {1}", text_id, typ);
					rowsaffected = DBcmd(sql);
				}
			}
		}
		#endregion
	}
}
