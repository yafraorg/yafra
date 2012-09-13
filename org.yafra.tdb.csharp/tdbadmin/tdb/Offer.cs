using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Offer (DLA) (dla_id, code, h_dla_id, ord, dlt_id, bez_id, akt_id, ort, art_id, dau, textid, von, nach)
	/// - add button for grouping
	/// - add support for mp_file if needed
	/// </summary>
	public class Offer : tdbroot
	{
        private int parentid;
        private int order;
        private int supid;
        private int actid;
		private string location;
		private int offtype;
		private DateTime duration;
		private int fromcity;
		private int tocity;

        public int ObjParentId { get { return parentid; } set { parentid = value; } }
        public int ObjOrder { get { return order; } set { order = value; } }
        public int ObjSuplier { get { return supid; } set { supid = value; } }
        public int ObjAction { get { return actid; } set { actid = value; } }
        public string ObjLocation { get { return location; } set { location = value; } }
        public int ObjType { get { return offtype; } set { offtype = value; } }
        public int ObjFrom { get { return fromcity; } set { fromcity = value; } }
        public int ObjTo { get { return tocity; } set { tocity = value; } }
        public DateTime ObjDuration { get { return duration; } set { duration = value; } }


		#region init
		public Offer()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.dienst_angebot;
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;

			// get the first suiteable title and return it
			OffV workDS = new OffV();
			sql = String.Format("Select * from tdbadmin.tdbv_o where o_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_o" });
			Arows = workDS.tdbv_o.Rows.Count;
			OffV.tdbv_oRow Rwork = workDS.tdbv_o[0];

			// set variables now
			id = Rwork.O_ID;
			// no code
            code = Rwork.CODE;
            fromcity = Rwork.FROMCITYID;
            tocity = Rwork.TOCITYID;
			order = Rwork.ORD;
            duration = Rwork.DURATION;
            offtype = Rwork.OTID;
            location = Rwork.LOCATION;
            supid = Rwork.SUPID;
            actid = Rwork.ACTID;
			parentid = Rwork.HOSTO_ID;
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
			OffVsel workDS;

			// get the first suiteable title and return it
			workDS = new OffVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_osel where o_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_osel" });
			OffVsel.tdbv_oselRow Rwork = workDS.tdbv_osel[0];
			id = Rwork.O_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			OffVsel workDS;

			// get the first suiteable title and return it
			workDS = new OffVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_osel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_osel" });
			Arows = workDS.tdbv_osel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (OffVsel.tdbv_oselRow Rwork in workDS.tdbv_osel)
			{
				result[i,0] = Convert.ToString(Rwork.O_ID);
                result[i,1] = Rwork.CODE;
				result[i,2] = Rwork.BEZ;
				i++;
			}
			return(result);
		}
        public void InsUpd(bool Ainsert, string Abez, string Atext, int Aparentid, string Acode, int Asupid, int Aofftype, DateTime Aduration, int Aactid, int Afromcity, int Atocity, int Aorder, string Alocation)
		{
			int udat, rowsaffected =0;
			string sql;

			// set to new one
			bez = Abez;
			text = Atext;
            code = Acode;
            parentid = Aparentid;
            supid = Asupid;
			fromcity = Afromcity;
			tocity = Atocity;
            duration = Aduration;
            udat = datetime.ToUnix(Aduration);
            order = Aorder;
            location = Alocation;
            offtype = Aofftype;
			actid = Aactid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("dienst_angebot", "DLA_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.dienst_angebot values({0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12})",
					id, code, parentid, order, supid, bez_id, actid, location, offtype, udat, text_id, fromcity, tocity);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
                sql = String.Format("update tdbadmin.dienst_angebot set code = {0}, h_dla_id = {1}, ord = {2}, dlt_id = {3}, akt_id = {4}, ort = {5}, art_id = {6}, art_id = {7}, dau = {8}, textid = {9}, von = {10}, nach = {11} where dla_id = {12}",
					code, parentid, order, supid, actid, location, offtype, udat, text_id, fromcity, tocity, id);
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
            sql = String.Format("delete from tdbadmin.dienst_angebot where dla_id = {0}", id);
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
