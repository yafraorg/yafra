using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Country.
	/// - add culture and region info from .NET
	/// - dateformat has to be alligned to the culture country part
	/// </summary>
	public class Country : tdbroot
	{
		private int capitalid;
		private string capital;
		private int curid;
		private string cur;
		private int langid;
		private string lang;
		private double vat;
		private string dateformat;

		#region init
		public Country()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.land;
		}
		#endregion

		public virtual int ObjCapid { get {return capitalid;} set {capitalid = value;} }
		public virtual string ObjCap { get {return capital;} set {capital = value;} }
		public virtual int ObjCurid { get {return curid;} set {curid = value;} }
		public virtual string ObjCur { get {return cur;} set {cur = value;} }
		public virtual int ObjLangid { get {return langid;} set {langid = value;} }
		public virtual string ObjLang { get {return lang;} set {lang = value;} }
		public virtual double ObjVat { get {return vat;} set {vat = value;} }
		public virtual string ObjDateformat { get {return dateformat;} set {dateformat = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			CountryV workDS;

			// get the first suiteable title and return it
			workDS = new CountryV();
			sql = String.Format("Select * from tdbadmin.tdbv_countryd where land_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_countryd" });
			Arows = workDS.tdbv_countryd.Rows.Count;
			CountryV.tdbv_countrydRow Rwork = workDS.tdbv_countryd[0];

			// set variables now
			id = Rwork.LAND_ID;
			code = Rwork.KRZL;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			capitalid = Rwork.CAPITALID;
			capital = Rwork.CAPITAL;
			curid = Rwork.CURID;
			cur = Rwork.CURRENCY;
			langid = Rwork.LANGID;
			lang = Rwork.LANG;
			vat = Rwork.VAT;
			dateformat = Rwork.DATEFORMAT;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			CountryVsel workDS;

			// get the first suiteable title and return it
			workDS = new CountryVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_countrysel where land_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_countrysel" });
			CountryVsel.tdbv_countryselRow Rwork = workDS.tdbv_countrysel[0];
			id = Rwork.LAND_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CountryVsel workDS;

			// get the first suiteable title and return it
			workDS = new CountryVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_countrysel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_countrysel" });
			Arows = workDS.tdbv_countrysel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (CountryVsel.tdbv_countryselRow Rwork in workDS.tdbv_countrysel)
			{
				result[i,0] = Convert.ToString(Rwork.LAND_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.KRZL;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Acapitalid, int Acurid, int Alangid, double Avat, string Adateformat)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			capitalid = Acapitalid;
			curid = Acurid;
			langid = Alangid;
			vat = Avat;
			dateformat = Adateformat;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{

				// first get a new unique ID for bez and then sai
				id = NewID("land", "LAND_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert sai
				sql = String.Format("insert into tdbadmin.land values({0}, {1}, {2}, '{3}', {4}, {5}, {6}, {7}, '{8}')", id, bez_id, text_id, code, capitalid, curid, langid, vat, dateformat);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.land set krzl = '{0}', haupt_ort = {1}, haupt_whr = {2}, haupt_spr = {3}, vat = {4}, dateformat = '{5}', textid = {6} where land_id = {7}", code, capitalid, curid, langid, vat, dateformat, text_id, id);
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
			sql = String.Format("delete from tdbadmin.land where land_id = {0}", id);
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
