using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Grouptype
	/// </summary>
	public class Grouptype : tdbroot
	{
		#region init
		public Grouptype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.kollektiv_typ;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			GrpTypV workDS;

			// get the first suiteable title and return it
			workDS = new GrpTypV();
			sql = String.Format("Select * from tdbadmin.tdbv_grpt where grptype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_grpt" });
			Arows = workDS.tdbv_grpt.Rows.Count;
			GrpTypV.tdbv_grptRow Rwork = workDS.tdbv_grpt[0];

			// set variables now
			id = Rwork.GRPTYPE_ID;
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
			GrpTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new GrpTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_grptsel where grptype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_grptsel" });
			GrpTypVsel.tdbv_grptselRow Rwork = workDS.tdbv_grptsel[0];
			id = Rwork.GRPTYPE_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			GrpTypVsel workDS;

			// get the first suiteable title and return it
			workDS = new GrpTypVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_grptsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_grptsel" });
			Arows = workDS.tdbv_grptsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (GrpTypVsel.tdbv_grptselRow Rwork in workDS.tdbv_grptsel)
			{
				result[i,0] = Convert.ToString(Rwork.GRPTYPE_ID);
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
				id = NewID("kollektiv_typ", "K_TYP_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.kollektiv_typ values({0}, '{1}', {2}, {3})", id, code, bez_id, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.kollektiv_typ set kolcode = '{0}', textid = {1} where k_typ_id = {2}", code, text_id, id);
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
			sql = String.Format("delete from tdbadmin.kollektiv_typ where k_typ_id = {0}", id);
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
