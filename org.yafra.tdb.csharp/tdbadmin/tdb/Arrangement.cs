using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Arrangement
	/// - add cascading deletion
	/// </summary>
	public class Arr : tdbroot
	{
		private int sai_id;
		private string sai;
		private int prg_id;
		private DateTime adat;
		private DateTime svon;
		private DateTime sbis;

		#region init
		public Arr()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.arrangement;
		}
		#endregion

		public int ObjSaiid { get {return sai_id;} set {sai_id = value;} }
		public int ObjPrgid { get {return prg_id;} set {prg_id = value;} }
		public DateTime ObjAdat { get {return adat;} set {adat = value;} }
		public string ObjSai { get {return sai;} set {sai = value;} }
		public DateTime ObjSvon { get {return svon;} set {svon = value;} }
		public DateTime ObjSbis { get {return sbis;} set {sbis = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			ArrV workDS;

			// get the first suiteable title and return it
			workDS = new ArrV();
			sql = String.Format("Select * from tdbadmin.tdbv_arr where arr_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_arr" });
			Arows = workDS.tdbv_arr.Rows.Count;
			ArrV.tdbv_arrRow Rwork = workDS.tdbv_arr[0];

			// set variables now
			id = Rwork.ARR_ID;
			code = Rwork.CODE;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			sai_id = Rwork.SAI_ID;
			sai = Rwork.SAI;
			prg_id = Rwork.PRG_ID;
			sai = Rwork.SAI;
			adat = Rwork.ADAT;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			ArrVsel workDS;

			// get the first suiteable title and return it
			workDS = new ArrVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_arrsel where arr_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_arrsel" });
			ArrVsel.tdbv_arrselRow Rwork = workDS.tdbv_arrsel[0];
			id = Rwork.ARR_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			ArrVsel workDS;

			// get the first suiteable title and return it
			workDS = new ArrVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_arrsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_arrsel" });
			Arows = workDS.tdbv_arrsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (ArrVsel.tdbv_arrselRow Rwork in workDS.tdbv_arrsel)
			{
				result[i,0] = Convert.ToString(Rwork.ARR_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Aprgid, DateTime Adat)
		{
			int rowsaffected = 0, udat;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			prg_id = Aprgid;

			tdb.Prg P = new tdb.Prg();
			P.Get(prg_id, ref rowsaffected);
			tdb.Season S = new tdb.Season();
			S.Get(P.ObjSaiid, ref rowsaffected);
			svon = S.ObjFrom;
			sbis = S.ObjTo;
			sai = S.ObjBez;
			if (Adat < svon || Adat > sbis)
			{
				id = -2;
				return;
			}
			sai_id = P.ObjSaiid;
			udat = datetime.ToUnix(Adat);

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("arrangement", "ARR_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.arrangement values({0}, '{1}', {2}, {3}, {4}, {5}, {6})", id, code, bez_id, udat, prg_id, text_id, sai_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.arrangement set code = '{0}', textid = {1}, prg_id = {2}, a_dat = {3}, sai_id = {4} where arr_id = {5}", code, text_id, prg_id, udat, sai_id, id);
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
			sql = String.Format("delete from tdbadmin.arrangement where arr_id = {0}", id);
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
