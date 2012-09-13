using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// supplier type.
	/// - add sel tree
	/// </summary>
	public class Suptype : tdbroot
	{
		private int htyp_id;
		private int host;

		#region init
		public Suptype()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.traeger_typ;
		}
		#endregion

		public virtual int ObjHost { get {return host;} set {host = value;} }
		public virtual int ObjParentId { get {return htyp_id;} set {htyp_id = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			DlttV workDS;

			// get the first suiteable title and return it
			workDS = new DlttV();
			sql = String.Format("Select * from tdbadmin.tdbv_dltt where typ_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dltt" });
			Arows = workDS.tdbv_dltt.Rows.Count;
			DlttV.tdbv_dlttRow Rwork = workDS.tdbv_dltt[0];

			// set variables now
			id = Rwork.TYP_ID;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			htyp_id = Rwork.H_TYP_ID;
			host = Rwork.HOST_TYP;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			DlttVsel workDS;

			// get the first suiteable title and return it
			workDS = new DlttVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_dlttsel where typ_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dlttsel" });
			DlttVsel.tdbv_dlttselRow Rwork = workDS.tdbv_dlttsel[0];
			id = Rwork.TYP_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			DlttVsel workDS;

			// get the first suiteable title and return it
			workDS = new DlttVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_dlttsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dlttsel" });
			Arows = workDS.tdbv_dlttsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (DlttVsel.tdbv_dlttselRow Rwork in workDS.tdbv_dlttsel)
			{
				result[i,0] = Convert.ToString(Rwork.TYP_ID);
				result[i,1] = Rwork.BEZ;
				i++;
			}
			return(result);
		}

		public void InsUpd(bool Ainsert, string Abez, string Atext, int Aparentid, bool Ahost)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			text = Atext;
			if (Ahost == false)
			{
				DlttV workDS = new DlttV();
				sql = String.Format("Select * from tdbadmin.tdbv_dltt where typ_id = {0} and s_id = {1}", Aparentid, tdb.User.Ulangid);
				FillDS(workDS, sql, new string[] { "tdbv_dltt" });
				DlttV.tdbv_dlttRow Rwork = workDS.tdbv_dltt[0];
				htyp_id = Aparentid;
				host = Rwork.HOST_TYP;
			}

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("traeger_typ", "TYP_ID");
				if (Ahost == true)
				{
					htyp_id = -1;
					host = id;
				}
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.traeger_typ values({0}, {1}, {2}, {3}, {4})", id, bez_id, htyp_id, host, text_id);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				if (Ahost == true)
				{
					htyp_id = -1;
					host = id;
				}
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.traeger_typ set h_typ_id = {0}, host_typ = {1}, textid = {2} where typ_id = {3}", htyp_id, host, text_id, id);
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
			sql = String.Format("delete from tdbadmin.traeger_typ where typ_id = {0}", id);
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
