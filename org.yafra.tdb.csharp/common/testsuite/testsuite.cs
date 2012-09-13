using System;
using System.Data;
using org.swyn.foundation.db;
using org.swyn.foundation.utils;

namespace org.swyn.foundation.testsuite
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class TestsuiteClass
		{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
			{
			// start testsuite here
			log l = new log();
			l.Init(true, true);
			l.Debug("Start foundation testsuite");
			l.LogFile("Start foundation testsuite logfile");
			l.Close();

			// log test here

			// datetime here
			Console.WriteLine("Start foundation testsuite");
            // SQL Server Express
            // testdb("Data Source=VMSQL\\SQLEXPRESS;Initial catalog=traveldb;user id=yafraadmin;pwd=yafra", "org.swyn.foundation.db.SqlServer");
            // Oracle 10g Express
            // testdb("Data Source=//vmora:1521/XE;user id=yafraadmin;password=yafra", "org.swyn.foundation.db.Oracle");
            // MySQL 5
            testdb("Data Source=webdevelop;user id=tdbadmin;pwd=yafra", "org.swyn.foundation.db.MySQL");
            }

		private static void testdb(string conn, string provider)
			{
			AdoHelper helper;
			string sql;
			IDataReader reader;

			// start testsuite here
			Console.WriteLine("Start database testsuite");
			helper = AdoHelper.CreateHelper("org.swyn.foundation", provider );

			sql = "Select * from tdbadmin.sprachen";
			reader = helper.ExecuteReader(conn, CommandType.Text, sql);
			while(reader.Read())
				{
				Console.WriteLine("Sprache ID:{0} Bezeichnung: {1}", reader.GetInt32(0), reader.GetString(3));
				}
			reader.Close();
			}
		}
}
