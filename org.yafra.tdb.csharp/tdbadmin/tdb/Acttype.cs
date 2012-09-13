using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Actiontype.
	/// - add new Form for parameters when you click on a parameter entry in the datagrid
	/// </summary>
	public class Acttype : tdbroot
	{
		#region init
		public Acttype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.aktions_typ;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			ActtypeV workDS;

			// get the first suiteable title and return it
			workDS = new ActtypeV();
			sql = String.Format("Select * from tdbadmin.tdbv_actt where acttype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_actt" });
			Arows = workDS.tdbv_actt.Rows.Count;
			ActtypeV.tdbv_acttRow Rwork = workDS.tdbv_actt[0];

			// set variables now
			id = Rwork.ACTTYPE_ID;
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
			ActtypeVsel workDS;

			// get the first suiteable title and return it
			workDS = new ActtypeVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_acttsel where acttype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_acttsel" });
			ActtypeVsel.tdbv_acttselRow Rwork = workDS.tdbv_acttsel[0];
			id = Rwork.ACTTYPE_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			ActtypeVsel workDS;

			// get the first suiteable title and return it
			workDS = new ActtypeVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_acttsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_acttsel" });
			Arows = workDS.tdbv_acttsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (ActtypeVsel.tdbv_acttselRow Rwork in workDS.tdbv_acttsel)
			{
				result[i,0] = Convert.ToString(Rwork.ACTTYPE_ID);
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
				id = NewID("aktions_typ", "A_TYP_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.aktions_typ values({0}, {1}, '{2}', {3})", id, bez_id, code, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.aktions_typ set proz = '{0}', textid = {1} where a_typ_id = {2}", code, text_id, id);
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
			sql = String.Format("delete from tdbadmin.aktions_typ where a_typ_id = {0}", id);
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
