using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// category
	/// </summary>
	public class Category : tdbroot
	{
		private int hkat_id;
		private int suptid;
		private string supt;
		private int color;

		// there is no CODE in kategorie

		#region init
		public Category()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.kategorie;
		}
		#endregion

		public virtual int ObjSupType { get {return suptid;} set {suptid = value;} }
		public virtual int ObjParentId { get {return hkat_id;} set {hkat_id = value;} }
		public virtual int ObjColor { get {return color;} set {color = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			CatV workDS;

			// get the first suiteable title and return it
			workDS = new CatV();
			sql = String.Format("Select * from tdbadmin.tdbv_cat where cat_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_cat" });
			Arows = workDS.tdbv_cat.Rows.Count;
			CatV.tdbv_catRow Rwork = workDS.tdbv_cat[0];

			// set variables now
			id = Rwork.CAT_ID;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			hkat_id = Rwork.H_KAT_ID;
			suptid = Rwork.SUPTYPID;
			supt = Rwork.SUPTYP;
			color = Rwork.GA;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			CatVsel workDS;

			// get the first suiteable title and return it
			workDS = new CatVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_catsel where cat_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_catsel" });
			CatVsel.tdbv_catselRow Rwork = workDS.tdbv_catsel[0];
			id = Rwork.CAT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CatVsel workDS;

			// get the first suiteable title and return it
			workDS = new CatVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_catsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_catsel" });
			Arows = workDS.tdbv_catsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (CatVsel.tdbv_catselRow Rwork in workDS.tdbv_catsel)
			{
				result[i,0] = Convert.ToString(Rwork.CAT_ID);
				result[i,1] = Rwork.BEZ;
				i++;
			}
			return(result);
		}

		public void InsUpd(bool Ainsert, string Abez, string Atext, int Aparentid, int Asuptypeid, int Acolor, bool Ahost)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			text = Atext;
			suptid = Asuptypeid;
			color = Acolor;
			if (Ahost == false)
				hkat_id = Aparentid;
			else
				hkat_id = -1;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then cat
				id = NewID("kategorie", "KAT_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.kategorie values({0}, {1}, {2}, {3}, {4}, {5})", id, bez_id, hkat_id, suptid, color, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.kategorie set h_kat_id = {0}, typ_id = {1}, ga = {2}, textid = {3} where kat_id = {4}", hkat_id, suptid, color, text_id, id);
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
			sql = String.Format("delete from tdbadmin.kategorie where kat_id = {0}", id);
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
