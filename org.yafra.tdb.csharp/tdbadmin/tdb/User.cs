using System;
using System.Data;
using org.swyn.foundation.db;
using org.swyn.foundation.utils;
using tdb.DS;

namespace tdb
{
	/// <summary>
	/// Handle user data associated with login and tdb profile data
	/// </summary>
	public class User
		{
		// class variables static for exe lifetime usage
		static public AdoHelper Uhelper;
		static public string Udbcon;
		static public string Uadostr;
		static public string Udbhost;
		static public string Udbtype;
		static public string Udbname;
		static public string Uname;
		static public string Upwd;
		static public int Useclevel;
		static public int Uofficeid;
		static public string Uoffice;
		static public int Ulangid;
		static public string Ulang;
		static public int Udlatid;
		static public string Udlat;
		static public int Usaiid;
		static public string Usai;
		static public int Uprgid;
		static public string Uprg;
		private DBtools dbt;
		
		public User()
			{
			}


		public string DBado { get { return Uadostr; } }
		public AdoHelper DBhelper { get { return Uhelper; } }
		public string DBcon { get { return Udbcon; } }
		public string Username { get { return Uname; } }
		public int LangId { get { return Ulangid; } }
		
		public void LoadProfile(string Auser)
			{
			dbt = new DBtools(tdb.User.Uhelper, tdb.User.Udbcon);
			tdb.Season sai = new tdb.Season();
			tdb.Language lang = new tdb.Language();
			tdb.Customer pers = new tdb.Customer();
			ProfileDS prof;
			string sql;

			// load profile from DB by user name
			prof = new ProfileDS();
			sql = String.Format("Select * from tdbadmin.mp_profil where mpuser like '{0}'", Auser);
			dbt.FillDS(prof, sql, new string[] { "mp_profil" });
			ProfileDS.mp_profilRow Rprof = prof.mp_profil[0];

			// set now the user profile data
			// Console.WriteLine("Prof Id {0}", Rprof.MPID);
			Useclevel = Rprof.SECLEVEL;
			Ulangid = Rprof.S_ID;
			if (Ulangid > 0)
				Ulang = lang.GetBez(Ulangid);
			else
				Ulang = "";
			Uofficeid = Rprof.BCHST;
			if (Uofficeid > 0)
				Uoffice = pers.GetBez(Uofficeid);
			else
				Ulang = "";
			Udlatid = Rprof.DLAT_ID;
			Usaiid = Rprof.SAI_ID;
			if (Usaiid > 0)
				Usai = sai.GetBez(Usaiid);
			else 
				Usai = "";
			}
		public void WriteProfile()
			{
			// write profile to DB
			
			}
		public void SetLogin(string Auser, string Apwd, string Adbname, string Adbtype, string Adbhost)
			{
			// update Userprofile class with login data and create ADO.NET connection string
			Uname = String.Copy(Auser);
			Upwd = String.Copy(Apwd);
			Udbname = String.Copy(Adbname);
			Udbtype = String.Copy(Adbtype);
			Udbhost = String.Copy(Adbhost);

			if (Adbtype == "Oracle")
				Udbcon = String.Format("Data Source={0};user id={1};pwd={2}", Udbname, Uname, Upwd);
			else
				Udbcon = String.Format("Data Source={0};Initial catalog={1};user id={2};pwd={3}", Udbhost, Udbname, Uname, Upwd);
			Uadostr = String.Format("org.swyn.foundation.db.{0}", Udbtype);
			Uhelper = AdoHelper.CreateHelper("org.swyn.foundation", Uadostr);
			// check if Uhelper is null and raise error event
			}

		}
}
