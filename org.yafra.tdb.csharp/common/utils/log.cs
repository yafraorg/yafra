using System;
using System.IO;

namespace org.swyn.foundation.utils
{
	#region Interface definition
	interface IswynLog
	{
		void Init(bool a, bool b);
		void Debug(string a);
		void LogFile(string a);
		void LogEvent(string a);
		void Close();
	}
	#endregion

	/// <summary>
	/// Logging and debugging class, supports console, files, eventlogs.
	/// </summary>
	public class log : IswynLog
	{
		static private bool DebugFlag = false;
		static private bool cons = false;
		static private string application_name;
		static private string logpath = @"C:\TEMP\";
		static private string logfile = "TDB_log.txt";
		static private string dbgfile = "TDB_debug.txt";
		static private Stream Slog;
		static private Stream Sdebug;
		static private TextWriter SlogW;
		static private TextWriter SdebugW;

		public log()
		{
			//
			// TODO: Add constructor logic here
			//
		}


		#region Get and Set flags and vars
		public bool IsDebug
		{
			get
			{
				return DebugFlag;
			}
		}
		public bool IsConsole
		{
			get
			{
				return cons;
			}
		}
		#endregion

		#region Methods
		public void Init(bool Adbg, bool Acons)
		{
			// init filename to open
			string tmplog, tmpdbg;
			tmplog = String.Format("{0}{1}", logpath, logfile);
			tmpdbg = String.Format("{0}{1}", logpath, dbgfile);

			// set flags
			cons = Acons;
			DebugFlag = Adbg;

			// check to see if we need files or console writes
			if (!cons)
			{
				Slog = File.OpenWrite(tmplog);
				SlogW = new StreamWriter(Slog);
				if (DebugFlag)
				{
					Sdebug = File.OpenWrite(tmpdbg);
					SdebugW = new StreamWriter(Sdebug);
				}
			}

			// write init message with apps name
			if (cons)
			{
				Console.WriteLine("travelDB logging init\n\n");
				if (DebugFlag)
					Console.WriteLine("travelDB debugging init\n\n");
			}
			else
			{
				SlogW.WriteLine("travelDB logging init\n\n");			
				if (DebugFlag)
					SdebugW.WriteLine("travelDB debugging init\n\n");			
			}
		}
		public void Close()
		{
			if (!cons)
			{
				// write close message with apps name
				SlogW.WriteLine("travelDB logging init\n\n");			
				SlogW.Close();
				Slog.Close();
				if (DebugFlag)
				{
					SdebugW.WriteLine("travelDB debugging init\n\n");			
					SdebugW.Close();
					Sdebug.Close();
				}
			}
		}
		public void Debug(string Amsg)
		{
			if (DebugFlag)
			{
				if (cons)
					Console.WriteLine("debug: {0}", Amsg);
				else
					SdebugW.WriteLine("debug: {0}", Amsg);
			}
		}
		public void LogFile(string Amsg)
		{
			if (cons)
				Console.WriteLine("logging: {0}", Amsg);
			else
				SlogW.WriteLine("logging: {0}", Amsg);
		}
		public void LogEvent(string Amsg)
		{
		}
		#endregion
	}
}
