using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// City
	/// - add coordinates from a worldmap, get it by a browser or built in
	/// - get timezone from external source, like www or .net culture (make a fetch button)
	/// </summary>
	public class City : tdbroot
	{
		private int landid;
		private string land;
		private int tz;
		private int coord1;
		private int coord2;
		private int citytype;

		#region init
		public City()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.ort;
		}
		#endregion

		public virtual int ObjLandid { get {return landid;} set {landid = value;} }
		public virtual string ObjLand { get {return land;} set {land = value;} }
		public virtual int ObjTz { get {return tz;} set {tz = value;} }
		public virtual int ObjCoord1 { get {return coord1;} set {coord1 = value;} }
		public virtual int ObjCoord2 { get {return coord2;} set {coord2 = value;} }
		public virtual int ObjType { get {return citytype;} set {citytype = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			CityV workDS;

			// get the first suiteable title and return it
			workDS = new CityV();
			sql = String.Format("Select * from tdbadmin.tdbv_city where ort_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_city" });
			Arows = workDS.tdbv_city.Rows.Count;
			CityV.tdbv_cityRow Rwork = workDS.tdbv_city[0];

			// set variables now
			id = Rwork.ORT_ID;
			code = Rwork.KRZL;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			landid = Rwork.LANDID;
			coord1 = Rwork.KOORD1;
			coord2 = Rwork.KOORD2;
			citytype = Rwork.TYPE;
			tz = Rwork.ZEITVER;
			land = Rwork.LANDBEZ;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			CityVsel workDS;

			// get the first suiteable title and return it
			workDS = new CityVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_citysel where ort_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_citysel" });
			CityVsel.tdbv_cityselRow Rwork = workDS.tdbv_citysel[0];
			id = Rwork.ORT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CityVsel workDS;

			// get the first suiteable title and return it
			workDS = new CityVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_citysel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_citysel" });
			Arows = workDS.tdbv_citysel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (CityVsel.tdbv_cityselRow Rwork in workDS.tdbv_citysel)
			{
				result[i,0] = Convert.ToString(Rwork.ORT_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.KRZL;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, string Atext, int Alandid, int Astaid, int Acoord1, int Acoord2, int Atz)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			text = Atext;
			landid = Alandid;
			coord1 = Acoord1;
			coord2 = Acoord2;
			citytype = Astaid;
			tz = Atz;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{

				// first get a new unique ID for bez and then sai
				id = NewID("ort", "ORT_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert sai
				sql = String.Format("insert into tdbadmin.ort values({0}, {1}, {2}, {3}, '{4}', {5}, {6}, {7}, {8})", id, bez_id, landid, text_id, code, tz, coord1, coord2, citytype);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				// update bez with user lang
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.ort set krzl = '{0}', land_id = {1}, zeitver = {2}, koord1 = {3}, koord2 = {4}, ort_typ = {5}, textid = {6} where ort_id = {7}", code, landid, tz, coord1, coord2, citytype, text_id, id);
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
			sql = String.Format("delete from tdbadmin.ort where ort_id = {0}", id);
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
