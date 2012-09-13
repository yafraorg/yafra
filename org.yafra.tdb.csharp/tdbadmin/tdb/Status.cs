using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Status values - dynamic states sorted by a type id.
	/// (for the type id see the tdb.TableTypes!)
	/// </summary>
	public class Status : tdbroot
	{
		protected int status_typ;
		private string status;
		private double kond;
		// abk is code

		#region init
		public Status()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.status_werte; // will be overriden by status_typ
		}
		#endregion

		public override int ObjTyp { get {return status_typ;} set {status_typ = value; this.typ = status_typ;} }
		public virtual string ObjSta { get {return status;} set {status = value;} }
		public virtual double ObjKond { get {return kond;} set {kond = value;} }


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			StatusV workDS;

			// get the first suiteable title and return it
			workDS = new StatusV();
			sql = String.Format("Select * from tdbadmin.tdbv_sta where sta_id = {0} and s_id = {1} and typ = {2}", Aid, tdb.User.Ulangid, status_typ);
			FillDS(workDS, sql, new string[] { "tdbv_sta" });
			Arows = workDS.tdbv_sta.Rows.Count;
			StatusV.tdbv_staRow Rwork = workDS.tdbv_sta[0];

			// set variables now
			id = Rwork.STA_ID;
			code = Rwork.ABK;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			status = Rwork.STA;
			kond = Rwork.KOND;
			status_typ = Rwork.TYP;
		}
		public override string GetBez(int Aid)
		{
			string sql;
			StatusVsel workDS;

			// get the first suiteable title and return it
			workDS = new StatusVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_stasel where sta_id = {0} and s_id = {1} and typ = {2}", Aid, tdb.User.Ulangid, status_typ);
			FillDS(workDS, sql, new string[] { "tdbv_stasel" });
			StatusVsel.tdbv_staselRow Rwork = workDS.tdbv_stasel[0];
			id = Rwork.STA_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			StatusVsel workDS;

			// get the first suiteable title and return it
			workDS = new StatusVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_stasel where s_id = {0} and typ = {1} order by bez", tdb.User.Ulangid, status_typ);
			FillDS(workDS, sql, new string[] { "tdbv_stasel" });
			Arows = workDS.tdbv_stasel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (StatusVsel.tdbv_staselRow Rwork in workDS.tdbv_stasel)
			{
				result[i,0] = Convert.ToString(Rwork.STA_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.CODE;
				i++;
			}
			return(result);
		}

		public string[,] SelTyp(ref int Arows)
		{
			string sql;
			int i=0;
			TitleDS workDS;

			// get the first suiteable title and return it
			workDS = new TitleDS();
			sql = String.Format("Select * from tdbadmin.bezeichnung where s_id = {0} and bez_id = 0 and typ > 999 order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "bezeichnung" });
			Arows = workDS.bezeichnung.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (TitleDS.bezeichnungRow Rwork in workDS.bezeichnung)
			{
				result[i,0] = Convert.ToString(Rwork.TYP);
				result[i,1] = Rwork.BEZ;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Asta, string Aabk, double Akond, int Atyp)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Aabk;
			status = Asta;
			status_typ = Atyp;
			typ = Atyp; // set type of bezeichnung to status_typ !
			kond = Akond;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("status_werte", "STA_ID");
				rowsaffected = InsBez();
				// insert
				sql = String.Format("insert into tdbadmin.status_werte values({0}, '{1}', '{2}', {3}, {4}, {5})", id, code, status, bez_id, kond, status_typ);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				// update sai
				sql = String.Format("update tdbadmin.status_werte set sta = '{0}', abk = '{1}', kond = {2} where typ = {3} and sta_id = {4}", status, code, kond, status_typ, id);
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
			sql = String.Format("delete from tdbadmin.status_werte where sta_id = {0} and typ = {1}", id, status_typ);
			rowsaffected = DBcmd(sql);
			// IMPLEMENT cascading deletion if still dependencies here ??
			if (rowsaffected > 0)
			{
				// delete bezeichnung
				sql = String.Format("delete from tdbadmin.bezeichnung where bez_id = {0} and typ = {1}", bez_id, status_typ);
				rowsaffected = DBcmd(sql);
			}
		}
		#endregion
	}
}
