using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Persontype
	/// - add check method to see of person fits to the age range with birthday
	/// </summary>
	public class Persontype : tdbroot
	{
		private int von;
		private int bis;

		#region init
		public Persontype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.reisender_typ;
		}
		#endregion

		public int ObjFrom { get {return von;} set {von = value;} }
		public int ObjTo { get {return bis;} set {bis = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			PersTypV workDS;

			// get the first suiteable title and return it
			workDS = new PersTypV();
			sql = String.Format("Select * from tdbadmin.tdbv_perst where perstype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_perst" });
			Arows = workDS.tdbv_perst.Rows.Count;
			PersTypV.tdbv_perstRow Rwork = workDS.tdbv_perst[0];

			// set variables now
			id = Rwork.PERSTYPE_ID;
			code = Rwork.CODE;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			von = Rwork.VONALTER;
			bis = Rwork.BISALTER;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			PersTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new PersTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_perstsel where custtype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_perstsel" });
			PersTypVsel.tdbv_perstselRow Rwork = workDS.tdbv_perstsel[0];
			id = Rwork.PERSTYPE_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			PersTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new PersTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_perstsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_perstsel" });
			Arows = workDS.tdbv_perstsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (PersTypVsel.tdbv_perstselRow Rwork in workDS.tdbv_perstsel)
			{
				result[i,0] = Convert.ToString(Rwork.PERSTYPE_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Avon, int Abis)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			von = Avon;
			bis = Abis;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("reisender_typ", "RKR_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.reisender_typ values({0}, '{1}', {2}, {3}, {4}, {5})", id, code, bez_id, von, bis, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.reisender_typ set dlncode = '{0}', vonalter = {1}, bisalter = {2}, textid = {3} where rkr_id = {4}", code, von, bis, text_id, id);
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
			sql = String.Format("delete from tdbadmin.reisender_typ where rkr_id = {0}", id);
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
