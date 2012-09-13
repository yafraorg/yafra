using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
    /// Service (DL DLG_PART) [dl_id, code, bez_id, h_dl_id, dla_id, ord, a_zeit, e_zeit, res_f, kid, konto, textid, sai_id, rechst]
	/// - add tree with arr->dlg->dl->dla
	/// </summary>
	public class Serviceoffer : tdbroot
	{
		private string parent;
        private int parentid;
        private int offerid;
        private string offer;
        private int order;
        private DateTime startdate;
        private DateTime enddate;
        private int customerid;
        private string customer;
        private string account;
        private int reservationflagid;
        private string reservationflag;
        private int invoicefromid;
        private string invoicefrom;
        private int seasonid;
        private string season;

        public string ObjParent { get { return parent; } set { parent = value; } }
        public int ObjParentId { get { return parentid; } set { parentid = value; } }
        public string ObjOffer { get { return offer; } set { offer = value; } }
        public int ObjOfferId { get { return offerid; } set { offerid = value; } }
        public DateTime ObjStartdate { get { return startdate; } set { startdate = value; } }
        public DateTime ObjEnddate { get { return enddate; } set { enddate = value; } }
        public string ObjCustomer { get { return customer; } set { customer = value; } }
        public int ObjCustomerId { get { return customerid; } set { customerid = value; } }
        public string ObjAccount { get { return account; } set { account = value; } }
        public string ObjResflag { get { return reservationflag; } set { reservationflag = value; } }
        public int ObjResflagId { get { return reservationflagid; } set { reservationflagid = value; } }
        public string ObjInvoicefrom { get { return invoicefrom; } set { invoicefrom = value; } }
        public int ObjInvoicefromId { get { return invoicefromid; } set { invoicefromid = value; } }
        public string ObjSeason { get { return season; } set { season = value; } }
        public int ObjSeasonId { get { return seasonid; } set { seasonid = value; } }

		#region init
        public Serviceoffer()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.dlg_parts;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;

			// get the first suiteable title and return it
            SoV workDS = new SoV();
			sql = String.Format("Select * from tdbadmin.tdbv_so where so_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_so" });
			Arows = workDS.tdbv_so.Rows.Count;
            SoV.tdbv_soRow Rwork = workDS.tdbv_so[0];

			// set variables now
			id = Rwork.SO_ID;
			// no code
            seasonid = Rwork.SEASONID;
            season = Rwork.SEASON;
            startdate = Rwork.STARTDAT;
            enddate = Rwork.STOPDAT;
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
			SoVsel workDS;

			// get the first suiteable title and return it
            workDS = new SoVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_sosel where so_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_sosel" });
            SoVsel.tdbv_soselRow Rwork = workDS.tdbv_sosel[0];
			id = Rwork.SO_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
            SoVsel workDS;

			// get the first suiteable title and return it
            workDS = new SoVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_sosel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_sosel" });
			Arows = workDS.tdbv_sosel.Rows.Count;
			string[,] result = new string[Arows, 3];
            foreach (SoVsel.tdbv_soselRow Rwork in workDS.tdbv_sosel)
			{
				result[i,0] = Convert.ToString(Rwork.SO_ID);
				result[i,1] = Rwork.BEZ;
                result[i,2] = Rwork.CODE;
                i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Atext, string Acode, int Aseasonid, DateTime Astartdate, DateTime Aenddate)
		{
			int rowsaffected=0, udat, udat2;
			string sql;

			// set to new one
			bez = Abez;
			text = Atext;
			code = Acode;
            startdate = Astartdate;
            udat = datetime.ToUnix(startdate);
            enddate = Aenddate;
            udat2 = datetime.ToUnix(enddate);
            seasonid = Aseasonid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("dlg_parts", "DL_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.dlg_parts values({0}, {1}, {2}, {3}, {4}, {5}, {6})",
					id, code, bez_id, text_id, seasonid, udat, udat2);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.dlg_parts set sai_id = {0}, a_zeit = {1}, e_zeit = {2}, code = {3}, textid = {4} where dl_id = {5}",
					seasonid, udat, udat2, code, text_id, id);
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
            sql = String.Format("delete from tdbadmin.dlg_parts where dl_id = {0}", id);
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
