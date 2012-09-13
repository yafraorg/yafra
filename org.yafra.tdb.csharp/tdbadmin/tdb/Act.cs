using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Action
	/// - add button for grouping
	/// - add support for mp_file if needed
	/// </summary>
	public class Act : tdbroot
	{
		private int exesta;
		private int fromressta;
		private int toressta;
		private int device;
		private int acttypeid;
		private int fileid;
		private int parentid;
		private int order;

		public int ObjExeflag { get {return exesta;} set {exesta = value;} }
		public int ObjFrom { get {return fromressta;} set {fromressta = value;} }
		public int ObjTo { get {return toressta;} set {toressta = value;} }
		public int ObjDev { get {return device;} set {device = value;} }
		public int ObjActt { get {return acttypeid;} set {acttypeid = value;} }
		public int ObjFile { get {return fileid;} set {fileid = value;} }
		public int ObjParent { get {return parentid;} set {parentid = value;} }
		public int ObjOrd { get {return order;} set {order = value;} }


		#region init
		public Act()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.aktionen;
			fileid = -1; // don't support the mp_file of the JAVA version
		}
		#endregion


		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;

			// get the first suiteable title and return it
			ActV workDS = new ActV();
			sql = String.Format("Select * from tdbadmin.tdbv_act where act_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_act" });
			Arows = workDS.tdbv_act.Rows.Count;
			ActV.tdbv_actRow Rwork = workDS.tdbv_act[0];

			// get the first suiteable title and return it
			ActGrp work2 = new ActGrp();
			sql = String.Format("Select * from tdbadmin.aktionsgrp where childakt = {0}", Aid);
			FillDS(work2, sql, new string[] { "aktionsgrp" });
			rows = work2.aktionsgrp.Rows.Count;
			ActGrp.aktionsgrpRow Rwork2 = work2.aktionsgrp[0];

			// set variables now
			id = Rwork.ACT_ID;
			// no code
			exesta = Rwork.AFLAGID;
			fromressta = Rwork.BFLAGID;
			toressta = Rwork.B2FLAGID;
			device = Rwork.MFLAGID;
			acttypeid = Rwork.ACTTYPEID;
			fileid = Rwork.FILE_ID;
			order = Rwork2.ORD;
			parentid = Rwork2.PARENTAKT;
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
			ActVsel workDS;

			// get the first suiteable title and return it
			workDS = new ActVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_actsel where act_id = {0} and s_id = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_actsel" });
			ActVsel.tdbv_actselRow Rwork = workDS.tdbv_actsel[0];
			id = Rwork.ACT_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			ActVsel workDS;

			// get the first suiteable title and return it
			workDS = new ActVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_actsel where s_id = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_actsel" });
			Arows = workDS.tdbv_actsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (ActVsel.tdbv_actselRow Rwork in workDS.tdbv_actsel)
			{
				result[i,0] = Convert.ToString(Rwork.ACT_ID);
				result[i,1] = Rwork.BEZ;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Atext, int Aexesta, int Afromres, int Atores, int Adev, int Aacttypeid)
		{
			int rowsaffected;
			string sql;

			// set to new one
			bez = Abez;
			text = Atext;
			exesta = Aexesta;
			fromressta = Afromres;
			toressta = Atores;
			device = Adev;
			acttypeid = Aacttypeid;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("aktionen", "AKT_ID");
				rowsaffected = InsBez();
				rowsaffected = InsText();
				// insert
				sql = String.Format("insert into tdbadmin.aktionen values({0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8})",
					id, bez_id, text_id, exesta, fromressta, device, acttypeid, toressta, fileid);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.aktionen set a_flag = {0}, b_flag = {1}, b2_flag = {2}, m_flag = {3}, a_typ_id = {4}, textid = {5} where akt_id = {6}",
					exesta, fromressta, toressta, device, acttypeid, text_id, id);
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
			sql = String.Format("delete from tdbadmin.aktionen where akt_id = {0}", id);
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
