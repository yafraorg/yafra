using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Season.
	/// - the season is set within a program and inherited to all others (arr, services, bookings, ...)
	/// - this can be used as well for data retention topcis
	/// - add cascading deletion
	/// - add move of a whole season to a backup device and restore
	/// </summary>
	public class Season : tdbroot
	{
		private DateTime von;
		private DateTime bis;

		#region init
		public Season()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.saison;
		}
		#endregion

		public virtual DateTime ObjFrom { get {return von;} set {von = value;} }
		public virtual DateTime ObjTo { get {return bis;} set {bis = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			SeasonV workDS;

			// get the first suiteable title and return it
			workDS = new SeasonV();
			sql = String.Format("Select * from tdbadmin.tdbv_sai where sai_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_sai" });
			Arows = workDS.tdbv_sai.Rows.Count;
			SeasonV.tdbv_saiRow Rwork = workDS.tdbv_sai[0];

			// set variables now
			id = Rwork.SAI_ID;
			code = Rwork.CODE;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			von = Rwork.VON;
			bis = Rwork.BIS;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			SeasonVsel workDS;

			// get the first suiteable title and return it
			workDS = new SeasonVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_saisel where sai_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_saisel" });
			SeasonVsel.tdbv_saiselRow Rwork = workDS.tdbv_saisel[0];
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			SeasonVsel workDS;

			// get the first suiteable title and return it
			workDS = new SeasonVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_saisel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_saisel" });
			Arows = workDS.tdbv_saisel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (SeasonVsel.tdbv_saiselRow Rwork in workDS.tdbv_saisel)
			{
				result[i,0] = Convert.ToString(Rwork.SAI_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, DateTime Avon, DateTime Abis, string Atext)
		{
			int rowsaffected, uvon, ubis;
			string sql;

			// set season to this new one
			bez = Abez;
			code = Acode;
			von = Avon;
			bis = Abis;
			text = Atext;

			// convert to unix timestamp
			uvon = datetime.ToUnix(Avon);
			ubis = datetime.ToUnix(Abis);

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("saison", "SAI_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert sai
				sql = String.Format("insert into tdbadmin.saison values({0}, '{1}', {2}, {3}, {4}, {5})", id, Acode, bez_id, uvon, ubis, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				// update bez with user lang
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.saison set code = '{0}', von = {1}, bis = {2}, textid = {3} where sai_id = {4}", code, uvon, ubis, text_id, id);
				rowsaffected = DBcmd(sql);
			}
			// commit
			Commit();
		}

		public override void Delete()
		{
			int rowsaffected;
			string sql;

			// delete season
			sql = String.Format("delete from tdbadmin.saison where sai_id = {0}", id);
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
