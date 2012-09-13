using System;
using System.Data;
using org.swyn.foundation.utils;
using tdb.DS;


namespace tdb
{
	/// <summary>
	/// Languages
	/// - sysbez has to be alligned to the language part of the .NET culture
	/// </summary>
	public class Language : tdbroot
	{
		// private variables
		// sysbez field is equal to code
		private int dialog;
		private int output;
		private int gui;

		#region init
		public Language()
		{
			//
			// TODO: Add constructor logic here
			//
			typ = TableTypes.sprache;
		}
		#endregion

		public virtual int ObjDialog { get {return dialog;} set {dialog = value;} }
		public virtual int ObjOutput { get {return output;} set {output = value;} }
		public virtual int ObjGui { get {return gui;} set {gui = value;} }

		#region Object Methods/Functions (get one, selection, insert, update, delete)
		public override void Get(int Aid, ref int Arows)
		{
			string sql;
			LangV workDS;

			// get the first suiteable title and return it
			workDS = new LangV();
			sql = String.Format("Select * from tdbadmin.tdbv_lang where s_id = {0} and bezsprid = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_lang" });
			Arows = workDS.tdbv_lang.Rows.Count;
			LangV.tdbv_langRow Rwork = workDS.tdbv_lang[0];

			// set variables now
			id = Rwork.S_ID;
			code = Rwork.SYSBEZ;
			bez = Rwork.BEZ;
			bez_id = Rwork.BEZ_ID;
			dialog = Rwork.DIALOG;
			output = Rwork.OUTPUT;
			gui = Rwork.GUI;
			text_id = -1;
			text = "";
		}
		public override string GetBez(int Aid)
		{
			string sql;
			LangVsel workDS;

			// get the first suiteable title and return it
			workDS = new LangVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_langsel where s_id = {0} and bezsprid = {1}", Aid, tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_langsel" });
			LangVsel.tdbv_langselRow Rwork = workDS.tdbv_langsel[0];
			id = Rwork.S_ID;
			return(Rwork.BEZ);
		}

		public override string[,] Sel(ref int Arows)
		{
			string sql;
			int i=0;
			LangVsel workDS;

			// get the first suiteable title and return it
			workDS = new LangVsel();
			sql = String.Format("Select * from tdbadmin.tdbv_langsel where bezsprid = {0} order by bez", tdb.User.Ulangid);
			FillDS(workDS, sql, new string[] { "tdbv_langsel" });
			Arows = workDS.tdbv_langsel.Rows.Count;
			string[,] result = new string[Arows, 3];
			foreach (LangVsel.tdbv_langselRow Rwork in workDS.tdbv_langsel)
			{
				result[i,0] = Convert.ToString(Rwork.S_ID);
				result[i,1] = Rwork.BEZ;
				result[i,2] = Rwork.SYSBEZ;
				i++;
			}
			return(result);
		}
		public void InsUpd(bool Ainsert, string Abez, string Acode, int Adialog, int Aoutput, int Agui)
		{
			int rowsaffected;
			string sql;

			// set Country to this new one
			bez = Abez;
			code = Acode;
			dialog = Adialog;
			output = Aoutput;
			gui = Agui;

			// Begin Trx
			BeginTrx();

			if (Ainsert)
			{
				// first get a new unique ID for bez and then sai
				id = NewID("sprachen", "S_ID");
				rowsaffected = InsBez();
				sql = String.Format("insert into tdbadmin.sprachen values({0}, {1}, {2}, '{3}', {4}, {5})", id, bez_id, dialog, code, output, gui);
				rowsaffected = DBcmd(sql);
			}
			else
			{
				rowsaffected = UpdBez();
				sql = String.Format("update tdbadmin.sprachen set sysbez = '{0}', dialog = {1}, output = {2}, gui = {3} where s_id = {4}", code, dialog, output, gui, id);
				rowsaffected = DBcmd(sql);
			}
			// commit
			Commit();
		}

		public override void Delete()
		{
			int rowsaffected;
			string sql;

			// if dialog language, delete all text, descriptions and others
			if (dialog == 1)
			{
				// sql = String.Format("delete from tdbadmin.bezeichnung where s_id = {0}", id);
				// rowsaffected = DBcmd(sql);
				// sql = String.Format("delete from tdbadmin.texte where s_id = {0}", id);
				// rowsaffected = DBcmd(sql);
			}

			// delete
			sql = String.Format("delete from tdbadmin.sprachen where id = {0}", id);
			rowsaffected = DBcmd(sql);
			// IMPLEMENT cascading deletion if still dependencies here ??
			if (rowsaffected > 0)
			{
				// delete bezeichnung
				sql = String.Format("delete from tdbadmin.bezeichnung where bez_id = {0} and typ = {1}", bez_id, typ);
				rowsaffected = DBcmd(sql);
			}
		}
		#endregion

	}
}
