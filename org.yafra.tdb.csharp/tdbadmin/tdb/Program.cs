using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Program.
	/// - add cascading deletion
	/// </summary>
	public class Prg : tdbroot
	{
		private int sai_id;

		#region init
		public Prg()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.programm;
		}
		#endregion

		public int ObjSaiid { get {return sai_id;} set {sai_id = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			PrgV workDS;

			// get the first suiteable title and return it
			workDS = new PrgV();
			sql = String.Format("Select * from tdbadmin.tdbv_prg where prg_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prg" });
			Arows = workDS.tdbv_prg.Rows.Count;
			PrgV.tdbv_prgRow Rwork = workDS.tdbv_prg[0];

			// set variables now
			id = Rwork.PRG_ID;
			code = Rwork.CODE;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			sai_id = Rwork.SAI_ID;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			PrgVsel workDS;

			// get the first suiteable title and return it
			workDS = new PrgVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_prgsel where prg_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prgsel" });
			PrgVsel.tdbv_prgselRow Rwork = workDS.tdbv_prgsel[0];
			id = Rwork.PRG_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			PrgVsel workDS;

			// get the first suiteable title and return it
			workDS = new PrgVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_prgsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prgsel" });
			Arows = workDS.tdbv_prgsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (PrgVsel.tdbv_prgselRow Rwork in workDS.tdbv_prgsel)
			{
				result[i,0] = Convert.ToString(Rwork.PRG_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Asaiid)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			sai_id = Asaiid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("programm", "PRG_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.programm values({0}, '{1}', {2}, {3}, {4})", id, code, bez_id, text_id, sai_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.programm set code = '{0}', textid = {1}, sai_id = {2} where prg_id = {3}", code, text_id, sai_id, id);
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
			sql = String.Format("delete from tdbadmin.programm where prg_id = {0}", id);
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
