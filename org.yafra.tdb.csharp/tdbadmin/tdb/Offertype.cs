using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Offertype
	/// - add cascading deletion
	/// </summary>
	public class Offertype : tdbroot
	{
		#region init
		public Offertype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.angebots_typ;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			OffertypeV workDS;

			// get the first suiteable title and return it
			workDS = new OffertypeV();
			sql = String.Format("Select * from tdbadmin.tdbv_ot where ot_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_ot" });
			Arows = workDS.tdbv_ot.Rows.Count;
			OffertypeV.tdbv_otRow Rwork = workDS.tdbv_ot[0];

			// set variables now
			id = Rwork.OT_ID;
			code = "";
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
			OffertypeVsel workDS;

			// get the first suiteable title and return it
			workDS = new OffertypeVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_otsel where custtype_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_otsel" });
			OffertypeVsel.tdbv_otselRow Rwork = workDS.tdbv_otsel[0];
			id = Rwork.OT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			OffertypeVsel workDS;

			// get the first suiteable title and return it
			workDS = new OffertypeVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_otsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_otsel" });
			Arows = workDS.tdbv_otsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (OffertypeVsel.tdbv_otselRow Rwork in workDS.tdbv_otsel)
			{
				result[i,0] = Convert.ToString(Rwork.OT_ID);
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
				id = NewID("angebots_typ", "ART_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.angebots_typ values({0}, {1}, {2})", id, bez_id, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.angebots_typ set textid = {0} where art_id = {1}", text_id, id);
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
			sql = String.Format("delete from tdbadmin.angebots_typ where art_id = {0}", id);
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
