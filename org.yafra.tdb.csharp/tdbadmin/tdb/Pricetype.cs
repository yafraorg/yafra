using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Pricetype like VAT
	/// </summary>
	public class Pricetype : tdbroot
	{
		#region init
		public Pricetype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.kosten_art;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			PrtV workDS;

			// get the first suiteable title and return it
			workDS = new PrtV();
			sql = String.Format("Select * from tdbadmin.tdbv_prt where prt_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prt" });
			Arows = workDS.tdbv_prt.Rows.Count;
			PrtV.tdbv_prtRow Rwork = workDS.tdbv_prt[0];

			// set variables now
			id = Rwork.PRT_ID;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			PrtVsel workDS;

			// get the first suiteable title and return it
			workDS = new PrtVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_prtsel where prt_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prtsel" });
			PrtVsel.tdbv_prtselRow Rwork = workDS.tdbv_prtsel[0];
			id = Rwork.PRT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			PrtVsel workDS;

			// get the first suiteable title and return it
			workDS = new PrtVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_prtsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_prtsel" });
			Arows = workDS.tdbv_prtsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (PrtVsel.tdbv_prtselRow Rwork in workDS.tdbv_prtsel)
			{
				result[i,0] = Convert.ToString(Rwork.PRT_ID);
				result[i,1] = Rwork.BEZ;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Atext)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			text = Atext;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("kosten_art", "KAR_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.kosten_art values({0}, {1}, {2})", id, bez_id, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.kosten_art set textid = {0} where kar_id = {1}", text_id, id);
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
			sql = String.Format("delete from tdbadmin.kosten_art where kar_id = {0}", id);
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
