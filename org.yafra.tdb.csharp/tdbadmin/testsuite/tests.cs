using System;
using System.Data;
using org.swyn.foundation.db;

namespace traveldb.testsuite
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public class tests
		{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
			{
			tdb.LanguageDS lang;
			tdb.Title bez;
			tdb.Language tlang;
			string[] tabs;
			string sql, sql2;
			string user = "mwn";

			//
			// TODO: Add code to start application here
			//
			Console.WriteLine("start testsuite for travelDB");
			Console.WriteLine("make login");
			Login dbc = new Login();

			Console.WriteLine("get user profile for {0}", user);
			tdb.User prof = new tdb.User();
			prof.LoadProfile(user);

			Console.WriteLine("print out dataset sprachen first row");
			lang = new tdb.LanguageDS();
			// tabs = new string[] { "sprachen", "bezeichnung" };
			sql = "Select * from root.sprachen";
			tdb.User.Uhelper.FillDataset(tdb.User.Udbcon, CommandType.Text, sql, lang, new string[] { "sprachen" } );
			tdb.LanguageDS.sprachenRow Rlang = lang.sprachen[0];
			Console.WriteLine("Sprache Id {0}, sysbez = {1}", Rlang.S_ID, Rlang.SYSBEZ);

			Console.WriteLine("get bezeichnung of first sprache");
			bez = new tdb.Title();
			Console.WriteLine("Sprache Id {0}, sysbez = {1}, named {2}", Rlang.S_ID, Rlang.SYSBEZ, (bez.GetTitle(Rlang.BEZ_ID, Rlang.S_ID, tdb.TableTypes.sprache)));

			Console.WriteLine("get bezeichnung of first sprache by Language class");
			tlang = new tdb.Language();
			sql = tlang.GetLang(1, 1);
			Console.WriteLine("Sprache named {0}", sql);

			Console.WriteLine("finish and exit");
			}
		}

	public class Login
		{
		public Login()
		{
			// init of class
			tdb.User prof;
			prof = new tdb.User();
			prof.SetLogin("root", "root", "traveldb", "SqlServer", "localhost");
		}
	}
}
