using System;

namespace tdb
{
	/// <summary>
	/// tdb table types for table bezeichnung, texte and status_werte - load them from XML in the future
	/// </summary>
	abstract public class TableTypes
	{
		public const int sprache = 1;
		public const int status_werte = 2;
		public const int saison = 9;
		public const int land = 10;
		public const int ort = 11;
		public const int waehrung = 12;
		public const int traeger_typ = 15;
		public const int kategorie = 16;
		public const int dienst_traeger = 17;
		public const int angebots_typ = 18;
		public const int aktions_typ = 19;
		public const int aktionen = 21;
		public const int reisender_typ = 35;
		public const int kunden = 25;
		public const int dienst_angebot = 23;
        public const int dlg_parts = 26;
        public const int dienstleistung = 27;
		public const int kunden_typ = 24;
		public const int kollektiv_typ = 32;
		public const int programm = 29;
		public const int arrangement = 30;
		public const int kosten_art = 43;

		private const string rcsid = "$Id: TableTypes.cs,v 1.8 2009-01-04 17:05:32 mwn Exp $";
		private const string tagid = "$Name:  $";
	}
	abstract public class StatusTypes
	{
		public const int prio = 1101;
		public const int ga = 1102;
		public const int stagrp = 1103;
		public const int personentyp = 1104;
		public const int staprice = 1105;
		public const int perssex = 1106; // male/female
		public const int staakt = 1107; // condition of action
		public const int booking = 1108; // status of a booking
		public const int exeflag = 1109; // action execution flag
		public const int personen = 1110;
		public const int adrdelivery = 1111; // delivery to an address (express, normal)
		public const int stares = 1112; // status of a reservation
		public const int staresflag = 1113; // allow to reserve this offer/service
		public const int staexchange = 1114; // type of exchange rate
		public const int valueoperator = 1115; // plus minus multiplication percentage
		public const int stadlt = 1116;
		public const int overbook = 1117;
		public const int msgtype = 1118;
		public const int device = 1119;
		public const int commission = 1120;
		public const int bookexe = 1121;
		public const int security = 1122;
		public const int staort = 1123;
		public const int staadr = 1127; // private second pobox
		public const int unit = 1128; // price unit - per person per group...
		public const int stawhr = 1129;
	}
}
