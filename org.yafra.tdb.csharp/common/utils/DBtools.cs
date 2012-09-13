using System;
using System.Data;
using org.swyn.foundation.db;

namespace org.swyn.foundation.utils
{
	/// <summary>
	/// Easy SQL functions.
	/// </summary>
	public class DBtools
	{
		private AdoHelper dbhelper;
		private string dbcon;
		private IDbConnection con;
		private IDbTransaction tran;

		public DBtools(AdoHelper Ahlp, string Adbcon)
		{
			//
			// TODO: Add constructor logic here
			//
			dbhelper = Ahlp;
			dbcon = Adbcon;
			con = dbhelper.GetConnection(dbcon);

			// begin transaction here
		}
		public void BeginTrx()
		{
			// con.Open();
			// tran = con.BeginTransaction();
		}
		public void Commit()
		{
			// tran.Commit();
		}
		public void Rollback()
		{
			// tran.Rollback();
		}
		public int NewID(string Atable, string Aidname)
		{
			string sql;
			sql = String.Format("select MAX({0}) from tdbadmin.{1}", Aidname, Atable);
			int newid = (int)dbhelper.ExecuteScalar(dbcon, CommandType.Text, sql);
			if (newid < 0)
				newid = 0;
			newid++;
			return newid;
		}
		public int DBcmd(string Acmd)
		{
			int affrows = (int)dbhelper.ExecuteNonQuery(dbcon, CommandType.Text, Acmd);
			return affrows;
		}
		public void FillDS(DataSet Ads, string Asql, string[] Atabs)
		{
			dbhelper.FillDataset(dbcon, CommandType.Text, Asql, Ads, Atabs );
		}
		public void UpdDS(DataSet Ads, string Aicmd, string [] Aiarg, string Aucmd, string [] Auarg, string Adcmd, string [] Adarg, string Atabs)
		{
			IDbCommand inscmd = dbhelper.CreateCommand(con, Aicmd, Aiarg);
			IDbCommand updcmd = dbhelper.CreateCommand(con, Aucmd, Auarg);
			IDbCommand delcmd = dbhelper.CreateCommand(con, Adcmd, Adarg);
			dbhelper.UpdateDataset(inscmd, delcmd, updcmd, Ads, Atabs);
		}
	}
}
