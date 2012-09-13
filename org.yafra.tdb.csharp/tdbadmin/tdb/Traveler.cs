using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Customer.
	/// - delete first name as soon traveler is done
	/// </summary>
	public class Traveler : tdbroot
	{
		// person properties (name is code, NO bez)
		private const int perstyp = 1; // persontype is traveler
		private int langid;
		private int staid;

		// customer properties
		private string tel;
		private string handy;
		private string fax;
		private string tlx;
		private string email;
		private string web;
		private string account;
		private int manager;
		private string attr1;
		private string attr2;
		private int custtypid;
		private int curid;

		#region init
		public Traveler()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.kunden;
			bez = "";
			bez_id = -1;
		}
		#endregion

		public virtual int ObjLangid { get {return langid;} set {langid = value;} }
		public virtual int ObjCusttypid { get {return custtypid;} set {custtypid = value;} }
		public virtual string ObjTel { get {return tel;} set {tel = value;} }
		public virtual string ObjHandy { get {return handy;} set {handy = value;} }
		public virtual string ObjFax { get {return fax;} set {fax = value;} }
		public virtual string ObjTlx { get {return tlx;} set {tlx = value;} }
		public virtual string ObjMail { get {return email;} set {email = value;} }
		public virtual string ObjAcc { get {return account;} set {account = value;} }
		public virtual string ObjA1 { get {return attr1;} set {attr1 = value;} }
		public virtual string ObjA2 { get {return attr2;} set {attr2 = value;} }
		public virtual string ObjWww { get {return web;} set {web = value;} }
		public virtual int ObjCurid { get {return curid;} set {curid = value;} }
		public virtual int ObjStaid { get {return staid;} set {staid = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			int rows;
			CustV workDS;

			// get the first suiteable title and return it
			workDS = new CustV();
			sql = String.Format("Select * from tdbadmin.tdbv_cust where pers_id = {0}", Aid);
			FillDS(workDS, sql, new string[] { "tdbv_cust" });
			Arows = workDS.tdbv_cust.Rows.Count;
			CustV.tdbv_custRow Rwork = workDS.tdbv_cust[0];

			// set variables now
			id = Rwork.PERS_ID;
			code = Rwork.NAME;
			curid = Rwork.CURID;
			langid = Rwork.S_ID;

			staid = Rwork.STA_ID;
			tel = Rwork.TEL;
			handy = Rwork.HANDY;
			fax = Rwork.FAX;
			tlx = Rwork.TLX;
			email = Rwork.EMAIL;
			web = Rwork.WEB;
			account = Rwork.ACCOUNT;
			manager = Rwork.MANAGER;
			attr1 = Rwork.ATTR1;
			attr2 = Rwork.ATTR2;
			custtypid = Rwork.CUSTTYPEID;
			text_id = Rwork.TEXTID;
			if (text_id > 0)
				rows = GetText();
			else
				text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			CustVsel workDS;

			// get the first suiteable title and return it
			workDS = new CustVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_custsel where pers_id = {0}", Aid);
			FillDS(workDS, sql, new string[] { "tdbv_custsel" });
			CustVsel.tdbv_custselRow Rwork = workDS.tdbv_custsel[0];
			id = Rwork.PERS_ID;
			return(Rwork.NAME);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			CustVsel workDS;

			// get the first suiteable title and return it
			workDS = new CustVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_custsel order by name");
			FillDS(workDS, sql, new string[] { "tdbv_custsel" });
			Arows = workDS.tdbv_custsel.Rows.Count;
			string[,] result = new string[Arows, 2];
			foreach (CustVsel.tdbv_custselRow Rwork in workDS.tdbv_custsel)
			{
				result[i,0] = Convert.ToString(Rwork.PERS_ID);
				result[i,1] = Rwork.NAME;
				i++;
			}
			return(result);
		}

		public void InsUpd(bool Ainsert, string Aname, int Alangid, int Akunt, string Atel,
			string Ahandy, string Afax, string Atlx, string Amail, string Aweb, int Aleiter,
			string Akonto, string Aa1, string Aa2, int Acurid, int Astaid, string Atext)
		{
			int rowsaffected;
			string sql;

			// set person to this new one
			code = Aname;
			text = Atext;
			curid = Acurid;
			langid = Alangid;
			staid = Astaid;
			tel = Atel;
			handy = Ahandy;
			fax = Afax;
			tlx = Atlx;
			email = Amail;
			web = Aweb;
			account = Akonto;
			manager = Aleiter;
			attr1 = Aa1;
			attr2 = Aa2;
			custtypid = Akunt;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{

				// first get a new unique ID for bez and then sai
				id = NewID("personen", "PERS_ID");
				rowsaffected = InsText();
				// insert sai
				sql = String.Format("insert into tdbadmin.personen values({0}, {1}, '{2}', {3}, {4}, {5})", id, perstyp, code, langid, staid, text_id);
				rowsaffected = DBcmd(sql);
				sql = String.Format("insert into tdbadmin.kunden values({0}, '{1}', '{2}', '{3}', '{4}', '{5}', '{6}', '{7}', {8}, '{9}', '{10}', {11}, {12})", id, tel, handy, fax, tlx, email, web, account, manager, attr1, attr2, custtypid, curid);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdText();
				// update sai
				sql = String.Format("update tdbadmin.personen set name = '{0}', s_id = {1}, sta_id = {2}, textid = {3} where pers_id = {4}", code, langid, staid, text_id, id);
				rowsaffected = DBcmd(sql);
				sql = String.Format("update tdbadmin.kunden set tel = '{0}', handy = '{1}', fax = '{2}', tlx = '{3}', email = '{4}', web = '{5}', konto = '{6}', leiter = {7}, attr1 = '{8}', attr2 = '{9}', k_typ_id = {10}, whr_id = {11} where pers_id = {12}", tel, handy, fax, tlx, email, web, account, manager, attr1, attr2, custtypid, curid, id);
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
			sql = String.Format("delete from tdbadmin.persadr where pers_id = {0}", id);
			rowsaffected = DBcmd(sql);
			sql = String.Format("delete from tdbadmin.kunden where pers_id = {0}", id);
			rowsaffected = DBcmd(sql);
			sql = String.Format("delete from tdbadmin.personen where pers_id = {0}", id);
			rowsaffected = DBcmd(sql);
			// IMPLEMENT cascading deletion if still dependencies here ??
			if (rowsaffected > 0)
			{
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
