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
	public class Sup : tdbroot
	{
		private int parentid;
		private int host;
		private int dlt_grp_id;
		private int kat_id;
		private string kat;
		private int typ_id;
		private string suptyp;
		private int capacity;
		private int level;
		private int staid;

		#region init
		public Sup()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.dienst_traeger;
			dlt_grp_id = -1;
		}
		#endregion

		public virtual int ObjHost { get {return host;} set {host = value;} }
		public virtual int ObjParentId { get {return parentid;} set {parentid = value;} }
		public virtual int ObjGroup { get {return dlt_grp_id;} set {dlt_grp_id = value;} }
		public virtual int ObjCategory { get {return kat_id;} set {kat_id = value;} }
		public virtual int ObjSuptype { get {return typ_id;} set {typ_id = value;} }
		public virtual string ObjCatT { get {return kat;} set {kat = value;} }
		public virtual string ObjSupT { get {return suptyp;} set {suptyp = value;} }
		public virtual int ObjCapacity { get {return capacity;} set {capacity = value;} }
		public virtual int ObjLevel { get {return level;} set {level = value;} }
		public virtual int ObjSta { get {return staid;} set {staid = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			DltV workDS;

			// get the first suiteable title and return it
			workDS = new DltV();
			sql = String.Format("Select * from tdbadmin.tdbv_dlt where dlt_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dlt" });
			Arows = workDS.tdbv_dlt.Rows.Count;
			DltV.tdbv_dltRow Rwork = workDS.tdbv_dlt[0];

			// set variables now
			id = Rwork.DLT_ID;
			code = Rwork.CODE;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			parentid = Rwork.H_DLT_ID;
			host = Rwork.HOSTID;
			kat_id = Rwork.CAT_ID;
			kat = Rwork.CAT;
			typ_id = Rwork.TYPID;
			suptyp = Rwork.TYP;
			capacity = Rwork.NUMPLACE;
			level = Rwork.LEVELPLACE;
			staid = Rwork.STAID;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			DltVsel workDS;

			// get the first suiteable title and return it
			workDS = new DltVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_dltsel where dlt_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dltsel" });
			DltVsel.tdbv_dltselRow Rwork = workDS.tdbv_dltsel[0];
			id = Rwork.DLT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			DltVsel workDS;

			// get the first suiteable title and return it
			workDS = new DltVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_dltsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_dltsel" });
			Arows = workDS.tdbv_dltsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (DltVsel.tdbv_dltselRow Rwork in workDS.tdbv_dltsel)
			{
				result[i,0] = Convert.ToString(Rwork.DLT_ID);
				result[i,1] = Rwork.CODE;
				result[i,2] = Rwork.BEZ;
				i++;
			}
			return(result);
		}

		public void InsUpd(bool Ainsert, string Abez, string Atext, string Acode,
			int Aparentid, bool Ahost, int Acat, int Asupt, int Asta, int Alev, int Acapa)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			text = Atext;
			code = Acode;
			if (Ahost == false)
			{
				DltV workDS = new DltV();
				sql = String.Format("Select * from tdbadmin.tdbv_dlt where dlt_id = {0} and s_id = {1}", Aparentid, tdb.User.Ulangid);
				FillDS(workDS, sql, new string[] { "tdbv_dlt" });
				DltV.tdbv_dltRow Rwork = workDS.tdbv_dlt[0];
				parentid = Aparentid;
				host = Rwork.HOSTID;
			}
			kat_id = Acat;
			typ_id = Asupt;
			capacity = Acapa;
			level = Alev;
			staid = Asta;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("dienst_traeger", "DLT_ID");
				if (Ahost == true)
				{
					parentid = -1;
					host = id;
				}
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.dienst_traeger values({0}, '{1}', {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11})",
					id, code, bez_id, kat_id, parentid, dlt_grp_id, host, typ_id, text_id, level, staid, capacity);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				if (Ahost == true)
				{
					parentid = -1;
					host = id;
				}
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.dienst_traeger set h_dlt_id = {0}, host_id = {1}, kat_id = {2}, typ_id = {3}, sta_id ={4}, stufe = {5}, anz = {6}, dlt_grp_id = {7}, code = '{8}', textid = {9} where dlt_id = {10}",
					parentid, host, kat_id, typ_id, staid, level, capacity, dlt_grp_id, code, text_id, id);
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
			sql = String.Format("delete from tdbadmin.dienst_traeger where dlt_id = {0}", id);
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
