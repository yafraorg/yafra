using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Customertype
	/// </summary>
	public class Customertype : tdbroot
	{
		#region init
		public Customertype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.kunden_typ;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			CustTypV workDS;

			// get the first suiteable title and return it
			workDS = new CustTypV();
			sql = String.Format("Select * from tdbadmin.tdbv_cutt where custtype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cutt" });
			Arows = workDS.tdbv_cutt.Rows.Count;
			CustTypV.tdbv_cuttRow Rwork = workDS.tdbv_cutt[0];

			// set variables now
			id = Rwork.CUSTTYPE_ID;
			code = Rwork.CODE;
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
			CustTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new CustTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_cuttsel where custtype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cuttsel" });
			CustTypVsel.tdbv_cuttselRow Rwork = workDS.tdbv_cuttsel[0];
			id = Rwork.CUSTTYPE_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CustTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new CustTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_cuttsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cuttsel" });
			Arows = workDS.tdbv_cuttsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (CustTypVsel.tdbv_cuttselRow Rwork in workDS.tdbv_cuttsel)
			{
				result[i,0] = Convert.ToString(Rwork.CUSTTYPE_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("kunden_typ", "K_TYP_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.kunden_typ values({0}, '{1}', {2}, {3})", id, code, bez_id, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.kunden_typ set kuncode = '{0}', textid = {1} where k_typ_id = {2}", code, text_id, id);
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
			sql = String.Format("delete from tdbadmin.kunden_typ where k_typ_id = {0}", id);
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
