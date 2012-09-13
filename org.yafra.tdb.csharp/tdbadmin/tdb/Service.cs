using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
    /// Service (DLG DIENSTLEISTUNG) [dlg_id, code, bez_id, textid, sai_id, a_zeit, akt_id]
	/// - add tree with arr->dlg->dl->dla
	/// </summary>
	public class Service : tdbroot
	{
		private int seasonid;
        private string season;
        private DateTime startdate;
		private int actionid;

        public string ObjSeason { get { return season; } set { season = value; } }
        public int ObjSeasonId { get { return seasonid; } set { seasonid = value; } }
        public DateTime ObjStartdate { get { return startdate; } set { startdate = value; } }
        public int ObjAction { get { return actionid; } set { actionid = value; } }


		#region init
		public Service()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.dienstleistung;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;

			// get the first suiteable title and return it
            ServV workDS = new ServV();
			sql = String.Format("Select * from tdbadmin.tdbv_serv where serv_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_serv" });
			Arows = workDS.tdbv_serv.Rows.Count;
			ServV.tdbv_servRow Rwork = workDS.tdbv_serv[0];

			// set variables now
			id = Rwork.SERV_ID;
			// no code
            seasonid = Rwork.SEASONID;
            season = Rwork.SEASON;
            actionid = Rwork.ACTID;
            startdate = Rwork.ADAT;
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
			ServVsel workDS;

			// get the first suiteable title and return it
			workDS = new ServVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_servsel where serv_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_servsel" });
			ServVsel.tdbv_servselRow Rwork = workDS.tdbv_servsel[0];
			id = Rwork.SERV_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			ServVsel workDS;

			// get the first suiteable title and return it
			workDS = new ServVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_servsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_servsel" });
			Arows = workDS.tdbv_servsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (ServVsel.tdbv_servselRow Rwork in workDS.tdbv_servsel)
			{
				result[i,0] = Convert.ToString(Rwork.SERV_ID);
				result[i,1] = Rwork.BEZ;
                result[i,2] = Rwork.CODE;
                i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Atext, string Acode, int Aseasonid, DateTime Astartdate, int Aactionid)
		{
			int rowsaffected=0, udat;
			string sql;

			// set to new one
			bez = Abez;
			text = Atext;
			code = Acode;
            startdate = Astartdate;
            udat = datetime.ToUnix(startdate);
            actionid = Aactionid;
            seasonid = Aseasonid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("dienstleistung", "DLG_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.dienstleistung values({0}, {1}, {2}, {3}, {4}, {5}, {6})",
					id, code, bez_id, text_id, seasonid, udat, actionid);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.dienstleistung set sai_id = {0}, a_zeit = {1}, akt_id = {2}, code = {3}, textid = {4} where dlg_id = {5}",
					seasonid, udat, actionid, code, text_id, id);
				rowsaffected = DBcmd(sql);
			}
			// commit
			Commit();
		}
		public override void Delete()
		{
			int rowsaffected;
			string sql;

			// delete
            sql = String.Format("delete from tdbadmin.dienstleistung where dlg_id = {0}", id);
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
