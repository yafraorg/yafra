using System;
using System.Data;
using org.swyn.foundation.db;
using tdb;
using tdb.DS;

namespace traveldb.testsuite
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class tests
		{
		/// <summary>
		/// The main entry point for the application.
		/// Use arguments 1=dbname, 2=servername, 3=dbtype (like MySQL)
		/// </summary>
		[STAThread]
		static void Main(string[] args)
			{
			tdb.Language Lang;
			int rows = 0;
			string dbname, servername, dbtype;

			//
			// TODO: Add code to start application here
			//
			Console.WriteLine("start testsuite for travelDB");
			// Test if input arguments were supplied:
        	if (args.Length == 0)
        		{
				Console.WriteLine("enter database name:");
		        dbname = Console.ReadLine();
		        if (dbname == null)
					return;
				Console.WriteLine("enter server name:");
		        servername = Console.ReadLine();
		        if (servername == null)
					return;
				Console.WriteLine("enter db typ (MySQL, SqlServer, Oracle, Odbc):");
		        dbtype = Console.ReadLine();
	        	if (dbtype == null)
					return;
		        }
			else
			{
				dbname = args[0];
				servername = args[1];
				dbtype = args[2];
			}
			Console.WriteLine("make login");
			// load and set profile and open database
			try
			{
				tdb.User prof = new tdb.User();
				prof.SetLogin("tdbadmin", "yafra", dbname, dbtype, servername);
				prof.LoadProfile("tdbadmin");
			}
			catch (System.Data.SqlClient.SqlException)
			{
				Console.WriteLine("travelDB error: Could not open the database");
			}
			
			Console.WriteLine("print out dataset sprachen first row");
			string[,] result = new string[1000, 3];
			Lang = new tdb.Language();
			result = Lang.Sel(ref rows);
			for (int i = 0; i < result.GetLength(0); i++)
				{
				Console.WriteLine("list of languages {0} {1} {2}", result[i,0], result[i,1], result[i,2]);
				}

			Console.WriteLine("finish and exit");
			}
		}
}
