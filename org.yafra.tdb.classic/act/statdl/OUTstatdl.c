/*D***********************************************************
 * Programm:     OUTstatnew
 * Beschreibung: prints a statistik from date to date
 *
 * arguments:    standard arguments
 *               -A  must   main ANGEBOT
 *               -e  must   time end
 *               -E  must   time start
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/*--- RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/statdl/OUTstatdl.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/*--- define the entry point of this function for the main() */
int OUTstatdl(int, char *[]);
#define ACTIONFUNCTION OUTstatdl

/*--- MarcoPolo API includes */
#include <mpact.h>

/*--- MarcoPolo API standard main function ! */
#include "AKTmain.h"

#include "version.h"

#define _SEL_DLT_DET  "SELECT * FROM TDBADMIN.DLT_VIEW WHERE HOST_ID = %d AND \
KAT_ID = %d AND S_ID = %d;"

#define _SEL_DLA_ID   "SELECT * FROM TDBADMIN.DLA_VIEW WHERE (DLA_ID = %d OR \
H_DLA_ID = %d) AND S_ID = %d;"

#define _SEL_RES_DL   "SELECT * FROM TDBADMIN.RESERVATION WHERE DLG_ID = %d AND \
(KAT_ID = %d OR KAT_ID = -1) AND \
((NOT(E_ZEIT <= %d OR A_ZEIT >= %d)) OR (A_ZEIT = -1 AND E_ZEIT = -1)) \
ORDER BY bid, pers_id, teil;"

#define _SEL_KATVIEW_DLT "SELECT DISTINCT KV.* \
FROM TDBADMIN.KAT_VIEW KV, TDBADMIN.DIENST_TRAEGER D \
WHERE D.HOST_ID = %d AND KV.S_ID = %d \
AND KV.KAT_ID > 0 AND KV.KAT_ID = D.KAT_ID \
ORDER BY KV.BEZ;"

#define _SEL_DTG_H_DLA "SELECT DISTINCT DL.* FROM TDBADMIN.DTG_VIEW DL, \
TDBADMIN.DLG_DLG DD, TDBADMIN.DLG_PARTS TDL, TDBADMIN.DIENST_ANGEBOT DLA WHERE \
DL.S_ID = %d AND ((DL.A_ZEIT >= %d AND DL.A_ZEIT <= %d) OR DL.A_ZEIT = -1) AND \
DLA.H_DLA_ID = %d AND TDL.DLA_ID = DLA.DLA_ID AND DD.DL_ID = TDL.DL_ID AND \
DL.DLG_ID = DD.DLG_ID ORDER BY DL.A_ZEIT;"

#define _SEL_DTG_DLA  "SELECT DISTINCT DL.* FROM TDBADMIN.DTG_VIEW DL, \
TDBADMIN.DLG_DLG DD, TDBADMIN.DLG_PARTS TDL, TDBADMIN.DIENST_ANGEBOT DLA WHERE \
DL.S_ID = %d AND ((DL.A_ZEIT >= %d AND DL.A_ZEIT <= %d) OR DL.A_ZEIT = -1) AND \
DLA.DLA_ID = %d AND TDL.DLA_ID = DLA.DLA_ID AND DD.DL_ID = TDL.DL_ID AND \
DL.DLG_ID = DD.DLG_ID ORDER BY DL.A_ZEIT;"


/*P--- PROTOTYPES ----------------------------------------------------------*/
static int	OUTstatArrangement ( KAT_VIEW *kategorie, int AnzKat, int host_id, int dlg_id,
										  char * traeger_bez, char *startdate, char *dienstBez,
										  char *akthauptdiensttraeger, char *vondate, char *bisdate );
static int  OUTstatDynamicDL ( KAT_VIEW *kategorie, int AnzKat, int host_id, int dlg_id,
										char * traeger_bez, char *startdate, char *dienstBez,
										char *akthauptdiensttraeger, char *vondate, char *bisdate );
static int	OUTstatDienstAngebot( int dla_id, MEMOBJ *pAngmem, int *AnzAng);
static int	OUTstatGetRes(int dlg_id, int kat_id, MEMOBJ *pResmem, int *AnzRes);
static int	OUTstatDienstTraeger ( DLA_VIEW dienstAngebot,DLT_VIEW *dlt_view,
                                   char *akthauptdiensttraeger, char *traeger_bez );
static int	OUTstatGetKat ( int *AnzKat, MEMOBJ *pKatmem, int dlt_id );
static int	OUTstatDienstTraegerDetail ( MEMOBJ *pDltmem, int *AnzDlt, int kategorie,
													 int host_id );
static int	OUTstatGetDlgDlg1 ( int *AnzDtg, MEMOBJ *pDtgme, int dlaid );
static void	OUTstatHeaderDyn ( int *line, int SeiteNr, char *traeger_bez, char *startdate,
										char *dienstBez, char *akthauptdiensttraeger, char *vondate,
										char *bisdate );
static void	OUTstatHeaderArr ( int *line, int SeiteNr, char *traeger_bez, char *startdate,
										char *dienstBez, char *akthauptdiensttraeger, char *vondate,
										char *bisdate );
static void	OUTstatBodyDyn ( char *KatBez, double gebucht, int totplaetze,int *line,
									 double totalopt, double totalepr, double totalvpr,
									 double totalred );
static void	OUTstatBodyArr ( char *KatBez, int gebucht, int totplaetze,int *line,
									 int totalopt, double totalepr, double totalvpr,
									 double totalred, char last );
static void	OUTstatTailDyn ( int totplaetze, double totgebucht, int *line,
									 double totalopt, double totalepr, double totalvpr,
									 double totalred );
static void	OUTstatTailArr ( int totplaetze, int totgebucht, int *line, int totalopt,
									 double totalepr, double totalvpr, double totalred );
static void	OUTintToDate( int time, char *date);
static int OUTstatPriceMatrixPrepare( RESERVATION *pRes, int aRkrid );
static int OUTstatUpgradeToAdult( REISENDER rei, int anzEffektiv );

/*P--- EXTERNALS -----------------------------------------------------------*/
extern int	aktuellesprache;
extern int	dialogsprache;
extern int	outputsprache;
extern int	time_start, time_end;
extern int	dlaid;

int   ReiType ;                  /* reisender typ          */
int   TarifLimit ;               /* when tarif must change */
int   Zusatzid ;                 /* Zusatzbett id          */
int   UpgradeBabyAdult ;         /* Bei nur einem Erw. Korrektur Erw. Preis   */
int   UpgradeYouthAdult ;        /* Bei nur einem Erw. Korrektur Erw. Preis   */
int   UpgradeChildAdult ;        /* Bei nur einem Erw. Korrektur Erw. Preis   */

/*P--- GLOBALS -------------------------------------------------------------*/


/*--- define text ids for language independend text */
#define TEXTID1			1
#define TEXTID2			2
#define TEXTID3			3
#define TEXTID4			4
#define TEXTID5			5
#define TEXTID6			6
#define TEXTID7			7
#define TEXTID8			8
#define TEXTID9			9
#define TEXTID10			10
#define TEXTID11			11
#define TEXTID12			12
#define TEXTID13			13
#define TEXTID14			14
#define TEXTID15			15
#define TEXTID16			16
#define TEXTID17			17
#define TEXTID18			18
#define TEXTID19			19

#define MAXLINES			40
#define ANFLEER			"     "
#define ZWILEER1			" "
#define ZWILEER			"|      "
#define TOT_ULINE_DYN	"----------------------------------------------------------------------------------------------------------------------------------------------------"
#define TOT_ULINE_ARR	"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------"

#define NBDISCOUNT		3
#define PRICEMEMCHUNK		20

/*F--------------------------------------------------------------------------
 *  Function:  OUTstatnew ()
 *             Statistik
 *
 *  In:        -
 *  out:       -
 *  Return:    -completion code
 *---------------------------------------------------------------------------
 */
int OUTstatdl(int argc, char *argv[])
{
	extern STATUS_WERTE sta;

	DEVICE_PORT *pDev					= (DEVICE_PORT *)NULL;
	DLA_VIEW *dienstAngebot			= (DLA_VIEW *)NULL;
	DLG_VIEW *dlg_part				= (DLG_VIEW *)NULL;
	KAT_VIEW *kategorie				= (KAT_VIEW *)NULL;
	DTG_VIEW *dtg						= (DTG_VIEW *)NULL;
	DLT_VIEW dienstTraeger;

	MEMOBJ angmem, *pAngmem;        /* memory for Angebot */
	MEMOBJ katmem, *pKatmem;        /* memory for Kategorie */
	MEMOBJ dtgmem, *pDtgmem;        /* memory for DTG */

	int	g = (int)0;               /* LoopCounter for dlg_parts */
	int	d = (int)0;               /* LoopCounter for dtg */
	int	p = (int)0;               /* LoopCounter for dlg_part auf res_f */
	int	a = (int)0;               /* LoopCounter for anz.Arra.in dieser Zeit */
	int	AnzAng = (int)0;          /* Anzahl Angebote */
	int	AnzDid = (int)0;          /* Anzahl Teildienstleistungen id */
	int	AnzKat = (int)0;          /* Anzahl Kategorie */
	int	AnzDtg = (int)0;          /* Anzahl Dtg */
	int	dlg_id = (int)0;          /* dlg_id holen */

	int	status = (int)MPOK;   /* Statusabfrage 0/ -1 */


	char akthauptdiensttraeger[_CHAR30+2]; /* Hoechste Traeger Bezeichnung */
	char traeger_bez[_CHAR80+2];    /* Traegerbezeichnung */
	char dynamicDL = (char)0;       /* Flag ob Dyn. Buchungen vorhanden sind */
	char vondate[_DATELEN];         /* Startdatum von der Statistik dd.mm.yy */
	char startdate[_DATELEN];       /* Startdatum der Dienstleistung dd.mm.yy */
	char bisdate[_DATELEN];         /* Enddatum von der Statistik dd.mm.yy */
	char format[RECLAENGE];         /* Deviceformat */
	char dienstBez[_CHAR30+2];      /* Dienstleistungsbezeichnung */


	/*--- init ----------------------------------*/
	pDev    = &devicePort;
	pAngmem = &angmem;
	pKatmem = &katmem;
	pDtgmem = &dtgmem;

	TarifLimit        = (int)3;
	Zusatzid          = (int)9;
	ReiType           = (int)1;
	UpgradeBabyAdult  = (int)4 ;
	UpgradeYouthAdult = (int)2 ;
	UpgradeChildAdult = (int)7 ;

	/*--- Alloc memory for operations -----------*/
	angmem.buffer   = NULL;
	angmem.alloclen = 0;
	angmem.datalen  = 0;

	katmem.buffer   = NULL;
	katmem.alloclen = 0;
	katmem.datalen  = 0;

	dtgmem.buffer   = NULL;
	dtgmem.alloclen = 0;
	dtgmem.datalen  = 0;


	/*--- action specific language --------------*/
	aktuellesprache = dialogsprache;

	/*--- mailing header ------------------------*/
	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	status = AKTmailHeader() ;
	TEST_STATUS(status)                             /*>>>>>>>>> exit */
	(void)MPAPIdb_committrx();

	/*--- check if all needed arguments are set -*/
	if (dlaid == (int)_UNDEF || time_start == (int)_UNDEF ||
	    time_end == (int)_UNDEF)
	{
		AKTmsg(ACT_ERROR, MPA_INVALIDARGS, NULL);
		TEST_STATUS(MPERROR)                             /*>>>>>>>>> exit */
	}

	/*--- Startdatum der Statistik --------------*/
	/* (void)convdate((time_t)time_start, "%b %d %y", "american", vondate);*/
	(void)OUTintToDate( time_start, vondate);
	
	/*--- Enddatum der Statistik ----------------*/
	/* (void)convdate((time_t)time_end, "%b %d %y", "american", bisdate);*/
	(void)OUTintToDate( time_end, bisdate);

	if (outputsprache == (int)UNDEF)
	{
		aktuellesprache = dialogsprache;
	}
	else
	{
		aktuellesprache = outputsprache;
	}

	/*--- Get all Dienstangebote ----------------*/
	status = OUTstatDienstAngebot ( dlaid, pAngmem, &AnzAng );
	TEST_STATUS(status)                             /*>>>>>>>>> exit */

	dienstAngebot = (DLA_VIEW *)angmem.buffer;


	/*--- Get all Kategorie ---------------------*/
	status = OUTstatGetKat ( &AnzKat, pKatmem, dienstAngebot[0].dlt_id );
	TEST_STATUS(status)                             /*>>>>>>>>> exit */

	kategorie = (KAT_VIEW *)katmem.buffer;


	/*--- Get Diensttraeger Host ----------------*/
	status = OUTstatDienstTraeger ( dienstAngebot[0], &dienstTraeger,
	                               akthauptdiensttraeger, traeger_bez);
	TEST_STATUS(status)                             /*>>>>>>>>> exit */


	status = OUTstatGetDlgDlg1 ( &AnzDtg, pDtgmem, dlaid );
	TEST_STATUS(status)                             /*>>>>>>>>> exit */
	dtg = (DTG_VIEW *)dtgmem.buffer;

	for ( d = 0; d < AnzDtg; d++ )
	{
		strcpy( dienstBez, dtg[d].bez );
		dienstBez[31] = '\0';
		for ( p = _CHAR30; p >= 0; p-- )
		{
			if ( dienstBez[p] != ' ' )
			{
				dienstBez[p+1] = '\0';
				break;
			}
		}
		dlg_id = dtg[d].dlg_id;


		/*--- mailing Dlgpart and Traeger -----------*/
		(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
		status = AKTmailDetail((int)_UNDEF, (int)_UNDEF, dlg_id, dlaid, dienstTraeger.dlt_id);
		TEST_STATUS(status)                             /*>>>>>>>>> exit */
		(void)MPAPIdb_committrx();

		*startdate = (char *)NULL;
		dynamicDL = (char)1;
		if ( dtg[d].a_zeit > (int)0 )
		{
			(void)OUTintToDate( dtg[d].a_zeit, startdate);
			dynamicDL = (char)0;
		}


		/*--- Loop ueber alle Dienstleistungs-Parts -*/
		/*for ( g = 0; g < AnzDlg; g++ )*/
		{
			if ( d != (int)0 && d < AnzDtg )
			{
				fprintf(FPout,"%s", _P_EOL_ );
			}

			if ( dynamicDL )
			{
				status = OUTstatDynamicDL ( kategorie, AnzKat,dienstTraeger.host_id,
		                            	    dlg_id, traeger_bez, startdate,
		                            	    dienstBez, akthauptdiensttraeger,
			                        	    vondate, bisdate );
			}
			else
			{
				status = OUTstatArrangement ( kategorie, AnzKat,
				                              dienstTraeger.host_id,
			                                 dlg_id, traeger_bez, startdate,
			                                 dienstBez, akthauptdiensttraeger,
			                                 vondate, bisdate );
			}
			TEST_STATUS(status)                       /*>>>>>>>>> exit */

		} /*** end loop dlg_part ***/

	} /*** end loop dtg_view ***/


   /*-----------------------------------------------------------------------*/
   /*--- Conclusion after all bookings                                      */
   /*-----------------------------------------------------------------------*/

   /*--- Device --------------------------------*/
   pDev->callnumber[0] = '\0';
   (void)LanguageDependentText((int)TEXTID5, (int)_STATISTIK_TYP,
			 aktuellesprache,
          aktuellesprache, format);
   (void)sprintf(pDev->command, "%s", format);
   /*--- Device process ------------------------*/
   status = AKTdeviceOuput();
   if (status != MPOK)
      AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");


   /*--- Mailing foot --------------------------*/
   AKTmailFoot(status);

exit:
   /*--- free memory ---------------------------*/
	MPfree((void *)angmem.buffer);
	MPfree((void *)katmem.buffer);
	MPfree((void *)dtgmem.buffer);

	return(status);
}
/*F--------------------------------------------------------------------------
 *  Function:	OUTstatDynamicDL ()
 *
 *
 *  In:			- dla_id
 *  out:			- Anzahl dlg-parts, dlg-parts-Buffer, h_dl_id
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatDynamicDL ( KAT_VIEW *kategorie, int AnzKat, int host_id,
                              int dlg_id, char *traeger_bez, char *startdate,
                              char *dienstBez, char *akthauptdiensttraeger,
                              char *vondate, char *bisdate )
{
	extern int  time_start, time_end;

	DLT_VIEW *dienstTraegerDetail = (DLT_VIEW *)NULL;
	RESERVATION *reservation      = (RESERVATION *)NULL;

	MEMOBJ dltmem, *pDltmem;        /* memory for Dl-Traeger Details*/
	MEMOBJ resmem, *pResmem;        /* memory for Reservation */

	static int   SeiteNr = (int)1;  /* Seitennummer auf der Liste */

	char ohnekategorie[_CHAR80+1];  /* Text fuer Kat. ohne Kategorie */

	int   k = (int)0;               /* LoopCounter for kategorie */
	int   r = (int)0;               /* LoopCounter for Reservationen */

	int   AnzDlt = (int)0;          /* Anzahl Diienstleistungs-Traeger Details */
	int   AnzRes = (int)0;          /* Anzahl Reservationen */
   int   bidOld = (int)0;          /* Alte Buchungsnummer */
   int   dltOld = (int)0;          /* Alte Dienstleistungsnummer */

	int	effdays = (int)0;         /* Effektive Anzahl Tage */
	int	days = (int)0;            /* Anzahl Tage die gebucht wurden */
	int	optdays = (int)0;         /* Optionale Anzahl Tage mit Kat */
	int	oOptKatdays = (int)0;     /* Optionale Anzahl Tage ohne Kat */
	int	totaldays = (int)0;       /* Total Tage */
	int	totaloptdays = (int)0;    /* Total Optionale Tage */

   int   totplaetze = (int)0;      /* Summe der Kapazitaet */
   int   line = (int)MAXLINES+1;   /* Max-Zeilen drucken */
   int   status = (int)MPOK;   /* Statusabfrage 0/ -1 */

   double totalepr = (double)0;    /* Total Einkaufspreis */
   double totalvpr = (double)0.0;  /* Total Verkaufspreis */
   double totalred = (double)0.0;  /* Total Reduktionen auf den Verkaufspreis */
   double gebucht = (double)0.0;   /* Summe der Reserv. Plaetze in % in der Z.*/
	double totalopt = (double)0.0;  /* Optional gebucht dlt_id = -1 */

	/*--- init ----------------------------------*/
	*ohnekategorie = (char *)NULL;

	pDltmem = &dltmem;
	pResmem = &resmem;

	/*--- Alloc memory for operations -----------*/
	dltmem.buffer   = NULL;
   dltmem.alloclen = 0;
   dltmem.datalen  = 0;

   resmem.buffer   = NULL;
   resmem.alloclen = 0;
   resmem.datalen  = 0;
	

	effdays += (double)(time_end - time_start) / (double)(24*60*60) + 1;

	/*--- Loop ueber alle Kategorie ----------*/
	for ( k = 0; k < AnzKat; k++ )
	{
		/*--- Get Diensttraeger Detail --------*/
		status = OUTstatDienstTraegerDetail ( pDltmem, &AnzDlt,
		                                      kategorie[k].kat_id,
		                                      host_id );
		TEST_STATUS(status)                       /*>>>>>>>>> exit */

		dienstTraegerDetail = (DLT_VIEW *)dltmem.buffer;
		totplaetze += AnzDlt;

		/*--- Count all Reservation from this Dienstleistungsteil ------*/
		status = OUTstatGetRes( dlg_id, kategorie[k].kat_id, pResmem,
		                        &AnzRes );

		TEST_STATUS(status)                     /*>>>>>>>>> exit */

		reservation = (RESERVATION *)resmem.buffer;

		bidOld = (int)0;
		dltOld = (int)0;
		days   = (int)0;
		optdays   = (int)0;
		for ( r = 0; r < AnzRes; r++ )
		{
			if ( reservation[r].kat_id != (int)_UNDEF )
			{
				if ( bidOld == reservation[r].bid )
				{
					if ( dltOld == reservation[r].dlt_id &&
					     reservation[r-1].kat_id != _UNDEF)
					{
						continue;
					}
					else
					{
						if ( reservation[r].dlt_id == (int)_UNDEF )
						{
							optdays += (int)(reservation[r].e_zeit -
						                       reservation[r].a_zeit) /
					       	                 (int)(24*60*60) + 1;
						}
						else
						{
							days += (int)(reservation[r].e_zeit -
						                    reservation[r].a_zeit) /
					                       (int)(24*60*60) + 1;
						}
					}
				}
				else
				{
					bidOld = reservation[r].bid;
					dltOld = reservation[r].dlt_id;
					if ( reservation[r].dlt_id == (int)_UNDEF )
					{
						optdays += (int)(reservation[r].e_zeit -
					                       reservation[r].a_zeit) /
					     	                 (int)(24*60*60) + 1;
					}
					else
					{
						days += (int)(reservation[r].e_zeit -
					                    reservation[r].a_zeit) /
					                    (int)(24*60*60) + 1;
					}
				}
			}
			else
			{
				if ( bidOld == reservation[r].bid )
				{
					if ( dltOld == reservation[r].dlt_id &&
					     reservation[r-1].kat_id == _UNDEF )
					{
						continue;
					}
					else
					{
						if ( k == (int)0 )
						{
							oOptKatdays += (int)(reservation[r].e_zeit -
					                   		   	reservation[r].a_zeit) /
					      	             			(int)(24*60*60) + 1;
						}
					}
				}
				else
				{
					bidOld = reservation[r].bid;
					dltOld = reservation[r].dlt_id;
					if ( k == (int)0 )
					{
						oOptKatdays += (int)(reservation[r].e_zeit -
					                  			reservation[r].a_zeit) /
					     	             			(int)(24*60*60) + 1;
					}
				}
			}
		}

		/*--- Header --------------------------*/
		if (line > MAXLINES)
		{
			if ( k != 0 )
			{
				fprintf(FPout, "\f");
			}
			(void)OUTstatHeaderDyn ( &line, SeiteNr, traeger_bez, startdate,
		                      	    dienstBez, akthauptdiensttraeger, vondate,
		                      	    bisdate );
			SeiteNr++;
		}
		/*--- BODY ----------------------------*/
		if ( AnzDlt > (int)0 )
		{
			gebucht = (double)(100 * days) / (AnzDlt * effdays);
			totalopt = (double)(100 * optdays)/ (AnzDlt * effdays);
		}
		else
		{
			gebucht = (double)0.0;
			totalopt = (double)0.0;
		}

		totaldays += days;
		totaloptdays += optdays;

		(void)OUTstatBodyDyn ( kategorie[k].bez, gebucht, AnzDlt, &line,
		                       totalopt, totalepr, totalvpr, totalred );

	} /*** end loop Kategorie ***/

	/*--- Header -----------------------------*/
	if (line > MAXLINES)
	{
		if ( k != 0 )
		{
			fprintf(FPout, "\f");
		}
		SeiteNr++;

		(void)OUTstatHeaderDyn ( &line, SeiteNr, traeger_bez, startdate,
		                         dienstBez, akthauptdiensttraeger, vondate,
		                         bisdate );
	}
	/*--- BODY -------------------------------*/
	if ( totplaetze > (int)0 )
	{
		gebucht = (double)0.0;
		totalopt = (double)(100 * oOptKatdays) / (totplaetze * effdays);
	}
	else
	{
		gebucht = (double)0.0;
		totalopt = (double)0.0;
	}

	(void)LanguageDependentText( TEXTID19,
	                             (int)_STATISTIK_TYP,
	                             aktuellesprache,
	                             aktuellesprache,
	                             ohnekategorie );

	(void)OUTstatBodyDyn ( ohnekategorie, gebucht, (int)0, &line,
		                    totalopt, totalepr, totalvpr, totalred);


   /*--- Header --------------------------------*/
   if (line+3 > MAXLINES)
   {
      if ( k != 0 )
      {
         fprintf(FPout, "\f");
      }
      (void)OUTstatHeaderDyn ( &line, SeiteNr, traeger_bez, startdate,
		                         dienstBez, akthauptdiensttraeger, vondate,
		                         bisdate );
   }

	if ( AnzDlt > (int)0 )
	{
		gebucht = (double)(100 * totaldays) / (totplaetze * effdays);
		totalopt = (double)(100*(totaloptdays+oOptKatdays))/(totplaetze*effdays);
	}
	else
	{
		gebucht = (double)0.0;
		totalopt = (double)0.0;
	}


   (void)OUTstatTailDyn ( totplaetze, gebucht, &line,
	                       totalopt, totalepr, totalvpr, totalred);

exit:
   /*--- free memory ---------------------------*/
	MPfree((void *)dltmem.buffer);
	MPfree((void *)resmem.buffer);

	return(status);
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatArrangement ()
 *
 *
 *  In:			- dla_id
 *  out:			- Anzahl dlg-parts, dlg-parts-Buffer, h_dl_id
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatArrangement ( KAT_VIEW *kategorie, int AnzKat, int host_id,
                                int dlg_id, char *traeger_bez, char *startdate,
                                char *dienstBez, char *akthauptdiensttraeger,
                                char *vondate, char *bisdate )
{
	extern int   TarifLimit;		  /* Grenze der Zusatzbetten */
	extern int   Zusatzid;		     /* Upgrade typ_id bei Zusatzbett */
	extern int   ReiType;		     /* Upgrade reit_id */

	DLT_VIEW *dienstTraegerDetail = (DLT_VIEW *)NULL;
	RESERVATION *reservation      = (RESERVATION *)NULL;
	BUCHUNG Bch;
	BUCHUNG *pBch;

	MEMOBJ dltmem, *pDltmem;        /* memory for Dl-Traeger Details*/
	MEMOBJ resmem, *pResmem;        /* memory for Reservation */

	static int   SeiteNr = (int)1;  /* Seitennummer auf der Liste */

	char ohnekategorie[_CHAR80+1];  /* Text fuer Kat. ohne Kategorie */
	char last = FALSE;              /* Optionale Zeile Drucken */
	char	format[RECLAENGE];

	int   k = (int)0;               /* LoopCounter for kategorie */
	int   r = (int)0;               /* LoopCounter for Reservationen */

	int   AnzDlt = (int)0;          /* Anzahl Diienstleistungs-Traeger Details */
	int   AnzRes = (int)0;          /* Anzahl Reservationen */
   int   bidOld = (int)0;          /* Alte Buchungsnummer */
   int   dltOld = (int)0;          /* Alte Dienstleistungsnummer */
	int   theRkrid, nbCom;
	int   AnzDln = (int)0;          /* count of travellers in a booking */
	int   OldDln = (int)0;          /* count of travellers in a booking */

   int   line = (int)MAXLINES+1;   /* Max-Zeilen drucken */
   int   status = (int)MPOK;       /* Statusabfrage 0/ -1 */
	int	anzEffektiv	= (int)0;	  /* Anzahl effektive Dln's  */


   int   totplaetze = (int)0;      /* Summe der Kapazitaet */
   int   totgebucht = (int)0;      /* Summe der Gebuchten Plaetze */
   int   gebucht = (int)0;         /* Summe der Reserv. Plaetze */
	int   totalopt = (int)0;        /* Optional gebucht dlt_id = -1 */
	int	optional = (int)0;        /* Summer der Optionalen Plaetze */
	int	optOhneKat = (int)0;      /* Summer der ohne Kat. gebuchten Plaetze */

   double totalepr = (double)0;    /* Total Einkaufspreis */
   double totalvpr = (double)0.0;  /* Total Verkaufspreis */
   double totalred = (double)0.0;  /* Total Reduktionen auf den Verkaufspreis */
   double totalgteeepr = (double)0.0;    /* Total Einkaufspreis */
   double totalgteevpr = (double)0.0;  /* Total Verkaufspreis */
   double totalgteered = (double)0.0;  /* Total Reduktionen auf den Verkaufspreis */
   double subvpr = (double)0.0;  /* Total Verkaufspreis */
   double subepr = (double)0.0;  /* Total Einstandspreis */
   double subred = (double)0.0;  /* Total Reduktionen auf den Verkaufspreis */
   double vpr = (double)0.0;       /* Verkaufspreis */
   double apr = (double)0.0;       /* Ankaufspreis */
   double epr = (double)0.0;       /* Einstandpreis */
   double red = (double)0.0;       /* Reduktionen auf den Verkaufspreis */

	/*--- init ----------------------------------*/
	*ohnekategorie = NULL;

	pDltmem = &dltmem;
	pResmem = &resmem;
	pBch    = &Bch;

	/*--- Alloc memory for operations -----------*/
	dltmem.buffer   = NULL;
   dltmem.alloclen = 0;
   dltmem.datalen  = 0;

   resmem.buffer   = NULL;
   resmem.alloclen = 0;
   resmem.datalen  = 0;
	
	/*--- Loop ueber alle Kategorien ----------*/
	for ( k = 0; k < AnzKat; k++ )
		{
		/*--- Get Diensttraeger Detail --------*/
		status = OUTstatDienstTraegerDetail ( pDltmem, &AnzDlt,
		                                      kategorie[k].kat_id,
		                                      host_id );
		TEST_STATUS(status)                       /*>>>>>>>>> exit */

		dienstTraegerDetail = (DLT_VIEW *)dltmem.buffer;
		totplaetze += AnzDlt;

		/*--- Count all Reservation from this Dienstleistungsteil ------*/
		status = OUTstatGetRes( dlg_id, kategorie[k].kat_id, pResmem,
		                        &AnzRes );

		TEST_STATUS(status)                     /*>>>>>>>>> exit */

		reservation = (RESERVATION *)resmem.buffer;

		bidOld = (int)0;
		dltOld = (int)0;
		gebucht = (int)0;
		optional = (int)0;
		subvpr = (double)0.0;
		subepr = (double)0.0;
		subred = (double)0.0;

		for ( r = 0; r < AnzRes; r++ )
			{
			vpr = (double)0.0;
			red = (double)0.0;

			if ( reservation[r].kat_id != (int)_UNDEF )
				{
				if ( bidOld == reservation[r].bid )	
					{
					anzEffektiv++;
					if ( dltOld == reservation[r].dlt_id &&
					     reservation[r-1].kat_id != _UNDEF)
						{
						continue;
						}
					else
						{
						if ( reservation[r].dlt_id == (int)_UNDEF )
							optional ++;
						else
							gebucht ++;
						}
					}
				else
					{
					anzEffektiv = (int)1;
					bidOld = reservation[r].bid;
					dltOld = reservation[r].dlt_id;
					if ( reservation[r].dlt_id == (int)_UNDEF )
						optional ++;
					else
						gebucht ++;
					}
				}
			else
				{
				if ( bidOld == reservation[r].bid )
					{
					anzEffektiv++;
					if ( dltOld == reservation[r].dlt_id &&
					     reservation[r-1].kat_id == _UNDEF )
						continue;
					else
						{
						if ( k == (int)0 )
							optOhneKat ++;
						}
					}
				else
					{
					anzEffektiv = (int)1;
					bidOld = reservation[r].bid;
					dltOld = reservation[r].dlt_id;
					if ( k == (int)0 )
						optOhneKat ++;
					}
				}

			/*--- PRICES AND COMMISSIONS --------------------------------------*/
			/*--- check if correction are necessary (nb of persons) -----------*/

			/*--- Get structures  --------------------------------*/
			status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
			
			MPAPIselectOneId( (int)_PERSONEN, reservation[r].pers_id, (char *)&pers);
			MPAPIselectOneId( (int)_REISENDER, reservation[r].pers_id, (char *)&rei);
			MPAPIselectOneId( (int)_BUCHUNG, reservation[r].bid, (char *)&Bch );

			AnzDln = MPAPIid_count((int)_BUCHUNG, (int)_BCH_DLN, (char *)&Bch);
			
		   MPAPIdb_committrx();
			

/*!!! no Travelertyp check *
			if (anzEffektiv < TarifLimit)
				theRkrid = OUTstatUpgradeToAdult( rei, anzEffektiv );
			else
********/
				theRkrid = rei.rkr_id;

			/*-- check if correction of nb of persons -------*/
			if (anzEffektiv >= TarifLimit)
				reservation[r].typ_id = Zusatzid;

			status = OUTstatPriceMatrixPrepare( &reservation[r], theRkrid );
			TEST_STATUS_COMMIT(status)
			if ( anzMatrix == 0)	
				{
				status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
				AKTmailPriceProblem( pBch->bid, reservation[r].dl_id ); 
				MPAPIdb_committrx();
				return ( (int)MPERROR );  /* >>>> exit */
				}
			AKTpriceMatrixGetSum( &vpr, (int)UNDEF );    /* for all  */
			AKTpriceMatrixGetAESum( &apr, &epr, (int)UNDEF );    /* for all  */

			/*--- Kommission suchen -------------*/
			status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
			AKTcommisPrepare( &priceMatrix[0], (int)UNDEF, pBch->k_id );
			AKTcommisDeleteItemWhen(  MP_MATCHING, "UBT" );
			MPAPIdb_committrx();
			nbCom = AKTcommisCountValid( );
			if ( nbCom > NBDISCOUNT)	
				{
				AKTmsgget( MPA_KOMMERROR, format);
				(void)sprintf( mailstring, format, pBch->bid, "UBT");
				AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
				MPAPIdb_committrx();
				return ( (int)MPERROR );  /* >>>> exit */
				}
			/*-- UBT compute -----------------------------*/
			status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
			AKTcommisComputeResult( NBDISCOUNT, vpr, &red );
			MPAPIdb_committrx();

#ifndef MPACT_STATDL_PERUNIT
			vpr = vpr * AnzDln;
			epr = epr * AnzDln;
			red = red * AnzDln;
#endif

			if ( reservation[r].kat_id != (int)_UNDEF )
				{
				subvpr += vpr;
				subepr += epr;
				subred += red;
				}
			else
				{
				/* gtee */
				totalgteevpr += vpr;
				totalgteeepr += epr;
				totalgteered += red;
				}                            

			} /* Ende for ( r = 0; r < AnzRes; r++ ) */


		/*--- Header --------------------------*/
		if (line > MAXLINES)
			{
			if ( k != 0 )
				fprintf(FPout, "\f");

			(void)OUTstatHeaderArr ( &line, SeiteNr, traeger_bez, startdate,
		                      	    dienstBez, akthauptdiensttraeger, vondate,
		                      	    bisdate );
			SeiteNr++;
			}
		/*--- BODY ----------------------------*/
		(void)OUTstatBodyArr ( kategorie[k].bez, gebucht, AnzDlt, &line,
		                       optional, subepr, subvpr, subred, last );


		totgebucht += gebucht;
		totalopt += optional;
		totalvpr += subvpr;
		totalred += subred;
		totalepr += subepr;
		

		} /*** end loop k Kategorie ***/

	/*--- Header -----------------------------*/
	if (line > MAXLINES)
		{
		if ( k != 0 )
			fprintf(FPout, "\f");
		SeiteNr++;

		(void)OUTstatHeaderArr ( &line, SeiteNr, traeger_bez, startdate,
		                         dienstBez, akthauptdiensttraeger, vondate,
		                         bisdate );
		}

	/*--- BODY -------------------------------*/
	(void)LanguageDependentText( TEXTID19,
	                             (int)_STATISTIK_TYP,
	                             aktuellesprache,
	                             aktuellesprache,
	                             ohnekategorie );

	last = TRUE;
	(void)OUTstatBodyArr ( ohnekategorie, (int)0, totplaetze, &line,
		                    optOhneKat, totalgteeepr, totalgteevpr, totalgteered, last);
	last = FALSE;

   /*--- Header --------------------------------*/
   if (line+3 > MAXLINES)
	   {
      if ( k != 0 )
         fprintf(FPout, "\f");

      (void)OUTstatHeaderArr ( &line, SeiteNr, traeger_bez, startdate,
		                         dienstBez, akthauptdiensttraeger, vondate,
		                         bisdate );
	   }

   (void)OUTstatTailArr ( totplaetze, totgebucht, &line,
	                       totalopt+optOhneKat, totalepr+totalgteevpr,
								  totalvpr+totalgteevpr, totalred+totalgteered);

	fprintf(FPout, "\f");

exit:
   /*--- free memory ---------------------------*/
	MPfree((void *)dltmem.buffer);
	MPfree((void *)resmem.buffer);

	return(status);
}


/*F--------------------------------------------------------------------------
 *  Function:	OUTstatDienstAngebot ()
 *
 *
 *  In:			- dla_id
 *  out:			- Anzahl DienstAngebote, DienstAngebote-Buffer
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatDienstAngebot ( int dla_id, MEMOBJ *pAngmem, int *AnzAng )
{
	DIENST_ANGEBOT dla;

	char	query[_QUERYLEN];
	int	id;
	int	status;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	id			= (int)_UNDEF;
	status	= (int)MPOK;

	/* Test ob dla_id auf oberster Stufe */
	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dla_id, (char *)&dla);

	if ( id != (int)_UNDEF )
	{
		/*--- Hole alle Angebote (Teile) ---------*/
		(void)sprintf(query, _SEL_DLA_ID, dla_id, dla_id, dialogsprache);

		pAngmem->buffer = NULL;
		pAngmem->alloclen = 0;
		pAngmem->datalen = 0;

		status = MPAPIdb_sqlquery( (int)_DLA_VIEW,
	                              (char **)(&pAngmem->buffer),
	                              query,
	                              AnzAng,
	                              &pAngmem->datalen,
	                              &pAngmem->alloclen );
	}
	else
	{
		status = (int)MPERROR;
	}

	(void)MPAPIdb_committrx();

	return status;
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatGetRes ()
 *
 *
 *  In:			- dlg_id, dlt_id, kat_id
 *  out:			- Anzahl Reservationen, Reservationen-Buffer
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatGetRes( int dlg_id, int kat_id, MEMOBJ *pResmem, int *AnzRes )
{
	extern int	time_start, time_end;
	char	query[_QUERYLEN];
	int	status;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	status	= (int)MPOK;

	/*--- Get Reservation, from this Dienstleistung ------------*/
	(void)sprintf(query, _SEL_RES_DL, dlg_id, kat_id,
	                                  time_start, time_end);

	pResmem->buffer = NULL;
	pResmem->alloclen = 0;
	pResmem->datalen = 0;

	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	status = MPAPIdb_sqlquery((int)_RESERVATION,
	                          (char **)&pResmem->buffer,
	                          query,
	                          AnzRes,
	                          &pResmem->datalen,
	                          &pResmem->alloclen );

	(void)MPAPIdb_committrx();

	return status;
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatDienstTraeger ()
 *
 *
 *  In:			- Dla-Buffer
 *  out:			- dlt-Buffer, Traegerbez, Hauptdiensttraegerbez
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatDienstTraeger ( DLA_VIEW Dla, DLT_VIEW *dlt_view,
	                                char *akthauptdiensttraeger,
                                   char *traeger_bez )
{
	TRAEGER_TYP Temptraeger_typ;
	char	query[_QUERYLEN];
	int	status;
	int	i;
	int	id;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	status	= (int)MPOK;
	id			= (int)_UNDEF;

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	id = MPAPIselectOneId((int)_DLT_VIEW, Dla.dlt_id, (char *)dlt_view);

	if ( id != (int)_UNDEF )
	{
		*akthauptdiensttraeger = NULL;
		strcpy(akthauptdiensttraeger, dlt_view->bez);
		akthauptdiensttraeger[31] = '\0';

		for ( i = _CHAR30; i >= 0; i-- )
		{
			if ( akthauptdiensttraeger[i] != ' ' )
			{
				akthauptdiensttraeger[i+1] = '\0';
				break;
			}
		}

		id = (int)_UNDEF;
		id = MPAPIselectOneId((int)_TRAEGER_TYP, dlt_view->typ_id,
	                         (char *)&Temptraeger_typ);

		if ( id != (int)_UNDEF )
		{
			*traeger_bez = NULL;
			SelectBez((int)_TRAEGER_TYP, aktuellesprache, Temptraeger_typ.bez_id,
	             traeger_bez);

			traeger_bez[81] = '\0';
			for ( i = _CHAR80; i >= 0; i-- )
			{
				if ( traeger_bez[i] != ' ' )
				{
					traeger_bez[i+1] = '\0';
					break;
				}
			}
		}
		else
		{
			status = (int)MPERROR;
		}
	}
	else
	{
		status = (int)MPERROR;
	}

	(void)MPAPIdb_committrx();

	return status;
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatGetKat ()
 *
 *
 *  In:			- dlt_id
 *  out:			- Anzahl Kategorie, Kategorie-Buffer
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatGetKat ( int *AnzKat, MEMOBJ *pKatmem, int dlt_id )
{
	char	query[_QUERYLEN];
	int	status;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	status	= (int)MPOK;

	/* Bestimme alle moeglichen Kategorien */
	sprintf(query, _SEL_KATVIEW_DLT, dlt_id, aktuellesprache);

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	pKatmem->buffer = NULL;
	pKatmem->alloclen = 0;
	pKatmem->datalen = 0;

	status = MPAPIdb_sqlquery( (int)_KAT_VIEW,
	                           (char **)(&pKatmem->buffer),
	                           query,
	                           AnzKat,
	                           &pKatmem->datalen,
	                           &pKatmem->alloclen );

	MPAPIdb_committrx();

	return status;

}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatDienstTraegerDetail ()
 *
 *
 *  In:			- kategorie, host_id
 *  out:			- Anzahl DienstleistungsTeile, DienstleistungsTeile-Buffer
 *  Return:		- status code 0 / -1
 *---------------------------------------------------------------------------
 */

static int OUTstatDienstTraegerDetail ( MEMOBJ *pDltmem, int *AnzDlt,
                                         int kategorie, int host_id )
{
	char	query[_QUERYLEN];
	int	status;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	status	= (int)MPOK;

	/* Bestimme alle DLT */
	sprintf(query, _SEL_DLT_DET, host_id, kategorie, aktuellesprache);

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	pDltmem->buffer = NULL;
	pDltmem->alloclen = 0;
	pDltmem->datalen = 0;

	status = MPAPIdb_sqlquery( (int)_DLT_VIEW,
	                           (char **)(&pDltmem->buffer),
	                           query,
	                           AnzDlt,
	                           &pDltmem->datalen,
	                           &pDltmem->alloclen );

	MPAPIdb_committrx();

	return status;

}


/*F--------------------------------------------------------------------------
 *  Function:	OUTstatHeaderDyn ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatHeaderDyn ( int *line, int SeiteNr, char *traeger_bez,
                               char *startdate, char *dienstBez,
                               char *akthauptdiensttraeger,
				                   char *vondate, char *bisdate )
{
	/*************************************/
	/*****  Texte aus der Datenbank  *****/
	/*************************************/

	static char formkategorie[_CHAR80+1] = {""};
	static char formanzplatz[_CHAR80+1] = {""};
	static char formfgebuchtp[_CHAR80+1] = {""};
	static char formogebuchtp[_CHAR80+1] = {""};
	static char formeinkauf[_CHAR80+1] = {""};
	static char formumsatz[_CHAR80+1] = {""};
	static char formmarge[_CHAR80+1] = {""};
	static char formreduktion[_CHAR80+1] = {""};
	static char formreduktp[_CHAR80+1] = {""};
	static char formtitel[_CHAR80+1] = {""};
	static char formunderl[_CHAR80+1] = {""};
	static char formseite[_CHAR80+1] = {""};

	if (!*formseite)
	{
		(void)LanguageDependentText( TEXTID1, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formseite );
	}

	if (!*formkategorie)
	{
		(void)LanguageDependentText( TEXTID3, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formkategorie);
	}

	if (!*formanzplatz)
	{
		(void)LanguageDependentText( TEXTID4,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formanzplatz);
	}

	if (!*formfgebuchtp)
	{
		(void)LanguageDependentText( TEXTID17,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formfgebuchtp);
	}

	if (!*formogebuchtp)
	{
		(void)LanguageDependentText( TEXTID18,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formogebuchtp);
	}

	if (!*formeinkauf)
	{
		(void)LanguageDependentText( TEXTID10,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formeinkauf);
	}

	if (!*formumsatz)
	{
		(void)LanguageDependentText( TEXTID11,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formumsatz);
	}

	if (!*formreduktion)
	{
		(void)LanguageDependentText( TEXTID12,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formreduktion);
	}

	if (!*formreduktp)
	{
		(void)LanguageDependentText( TEXTID13,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formreduktp);
	}

	if (!*formmarge)
	{
		(void)LanguageDependentText( TEXTID14,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formmarge);
	}

	if (!*formtitel)
	{
		(void)LanguageDependentText( TEXTID15,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formtitel);
	}

	if (!*formunderl)
	{
		(void)LanguageDependentText( TEXTID16,
	                                (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formunderl );
	}


	/*--- Headerinformation ---------------------*/
	(*line) = 0;
	fprintf(FPout, "%168.168s", ZWILEER1);
	fprintf(FPout, "%-s  %-2.d", formseite, SeiteNr);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	fprintf(FPout, "%s", formtitel);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	fprintf(FPout, "%s", formunderl);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	
	if ( *startdate != NULL )
	{
		fprintf(FPout, "%s %s    %s  %s", traeger_bez,
	                                     akthauptdiensttraeger,
                                  	    dienstBez, startdate);
	}
	else
	{
		fprintf(FPout, "%s %s    %s  %s  -  %s", traeger_bez,
	                                            akthauptdiensttraeger,
		                                         dienstBez,
                                   		        vondate, bisdate);
	}
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_DYN);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, "%-20.20s|", formkategorie);
	fprintf(FPout, "%11.11s|", formanzplatz);
	fprintf(FPout, "%11.11s|", formfgebuchtp);
	fprintf(FPout, "%11.11s|", formogebuchtp);
	fprintf(FPout, "%20.20s|", formeinkauf);
	fprintf(FPout, "%20.20s|", formumsatz);
	fprintf(FPout, "%18.18s|", formreduktion);
	fprintf(FPout, "%18.18s|", formmarge);
	fprintf(FPout, "%11.11s", formreduktp);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_DYN);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatBodyDyn ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatBodyDyn ( char *katBez, double gebucht, int totplaetze,
                             int *line, double optional, double ePreis,
                             double vPreis, double reduktion )
{
	double proz = (double)0.0;      /* Prozentwerte Temp. Abspeichern */
	char cashstring[_CHAR80+1];


	/*--- Anfang leer ---------------------------*/
	fprintf(FPout, ANFLEER);

	/*--- Kategorie Bezeichnung -----------------*/
	fprintf(FPout, "%-20.20s", katBez);
	fprintf(FPout, ZWILEER);

	/*--- Anzahl Plaetze ------------------------*/
	fprintf(FPout, "%5d", totplaetze);
	fprintf(FPout, ZWILEER);

	/*--- fest gebucht in Prozenten -------------*/
	fprintf(FPout, "%5.1f", gebucht);
	fprintf(FPout, ZWILEER);

	/*--- optional gebucht in % ----------------------*/
	fprintf(FPout, "%5.1f", optional);
	fprintf(FPout, ZWILEER);

	/*--- Einkauf -------------------------------*/
	cashdouble(ePreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Umsatz --------------------------------*/
	cashdouble(vPreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Ermaessigungen, Marge -----------------*/
	cashdouble(reduktion, cashstring);
	fprintf(FPout, "%12.12s", cashstring);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0)
	{
		proz = vPreis - ePreis;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%12.2f", proz);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0)
	{
		proz = (vPreis - ePreis) / vPreis;
		proz *= 100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;

}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatTailDyn ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatTailDyn ( int totplaetze, double totgebucht, int *line,
                             double optional, double ePreis, double vPreis,
                             double reduktion )
{

	static char formtotal[_CHAR80+1] = { "" };
	double proz = (double)0.0;      /* Prozentwerte Temp. Abspeichern */
	char cashstring[_CHAR80+1];

	if (!*formtotal)
	{
		(void)LanguageDependentText( TEXTID2, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formtotal );
	}

	/*--- Total ---------------------------------*/
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_DYN);
	fprintf(FPout, "%s", _P_EOL_);
	line++;

	/*--- Anfang leer ---------------------------*/
	fprintf(FPout, ANFLEER);

	/*--- Kategorie Bezeichnung -----------------*/
	fprintf(FPout, "%-20.20s", formtotal);
	fprintf(FPout, ZWILEER);

	/*--- Anzahl Plaetze ------------------------*/
	fprintf(FPout, "%5d", totplaetze);
	fprintf(FPout, ZWILEER);

	/*--- fest gebucht in % ---------------------*/
	fprintf(FPout, "%5.1f", totgebucht);
	fprintf(FPout, ZWILEER);

	/*--- optional gebucht in % -----------------*/
	fprintf(FPout, "%5.1f", optional);
	fprintf(FPout, ZWILEER);

	/*--- Einkauf -------------------------------*/
	cashdouble(ePreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Umsatz --------------------------------*/
	cashdouble(vPreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Ermaessigungen, Marge -----------------*/
	cashdouble(reduktion, cashstring);
	fprintf(FPout, "%12.12s", cashstring);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0) {
		proz = vPreis - ePreis;
	} else {
		proz = (double)0.0;
	}
	fprintf(FPout, "%12.2f", proz);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0) {
		proz = (vPreis - ePreis) / vPreis;
		proz *= 100.0;
	} else {
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, "%s", _P_EOL_);
	line++;

	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_DYN);
	fprintf(FPout, "%s", _P_EOL_);

}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatHeaderArr ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatHeaderArr ( int *line, int SeiteNr, char *traeger_bez,
                               char *startdate, char *dienstBez,
                               char *akthauptdiensttraeger,
				                   char *vondate, char *bisdate )
{
	/*************************************/
	/*****  Texte aus der Datenbank  *****/
	/*************************************/

	static char formkategorie[_CHAR80+1] = {""};
	static char formanzplatz[_CHAR80+1] = {""};
	static char formfgebucht[_CHAR80+1] = {""};
	static char formfgebuchtp[_CHAR80+1] = {""};
	static char formogebucht[_CHAR80+1] = {""};
	static char formogebuchtp[_CHAR80+1] = {""};
	static char formeinkauf[_CHAR80+1] = {""};
	static char formumsatz[_CHAR80+1] = {""};
	static char formmarge[_CHAR80+1] = {""};
	static char formreduktion[_CHAR80+1] = {""};
	static char formreduktp[_CHAR80+1] = {""};
	static char formtitel[_CHAR80+1] = {""};
	static char formunderl[_CHAR80+1] = {""};
	static char formseite[_CHAR80+1] = {""};

	if (!*formseite)
	{
		(void)LanguageDependentText( TEXTID1, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formseite );
	}

	if (!*formkategorie)
	{
		(void)LanguageDependentText( TEXTID3, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formkategorie);
	}

	if (!*formanzplatz)
	{
		(void)LanguageDependentText( TEXTID4,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formanzplatz);
	}

	if (!*formfgebucht)
	{
		(void)LanguageDependentText( TEXTID6,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formfgebucht);
	}

	if (!*formfgebuchtp)
	{
		(void)LanguageDependentText( TEXTID7,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formfgebuchtp);
	}

	if (!*formogebucht)
	{
		(void)LanguageDependentText( TEXTID8,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formogebucht);
	}

	if (!*formogebuchtp)
	{
		(void)LanguageDependentText( TEXTID9,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formogebuchtp);
	}

	if (!*formeinkauf)
	{
		(void)LanguageDependentText( TEXTID10,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formeinkauf);
	}

	if (!*formumsatz)
	{
		(void)LanguageDependentText( TEXTID11,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formumsatz);
	}

	if (!*formreduktion)
	{
		(void)LanguageDependentText( TEXTID12,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache,formreduktion);
	}

	if (!*formreduktp)
	{
		(void)LanguageDependentText( TEXTID13,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formreduktp);
	}

	if (!*formmarge)
	{
		(void)LanguageDependentText( TEXTID14,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formmarge);
	}

	if (!*formtitel)
	{
		(void)LanguageDependentText( TEXTID15,
	                                (int)_STATISTIK_TYP, aktuellesprache,
	                                aktuellesprache, formtitel);
	}

	if (!*formunderl)
	{
		(void)LanguageDependentText( TEXTID16,
	                                (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formunderl );
	}


	/*--- Headerinformation ---------------------*/
	(*line) = 0;
	fprintf(FPout, "%168.168s", ZWILEER1);
	fprintf(FPout, "%-s  %-2.d", formseite, SeiteNr);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	fprintf(FPout, "%s", formtitel);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	fprintf(FPout, "%s", formunderl);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%60.60s", ZWILEER1);
	
	if ( *startdate != NULL )
	{
		fprintf(FPout, "%s %s    %s  %s", traeger_bez,
	                                     akthauptdiensttraeger,
                                  	    dienstBez, startdate);
	}
	else
	{
		fprintf(FPout, "%s %s    %s  %s  -  %s", traeger_bez,
	                                            akthauptdiensttraeger,
		                                         dienstBez,
                                   		        vondate, bisdate);
	}
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_ARR);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, "%-20.20s|", formkategorie);
	fprintf(FPout, "%11.11s|", formanzplatz);
	fprintf(FPout, "%11.11s|", formfgebucht);
	fprintf(FPout, "%11.11s|", formfgebuchtp);
	fprintf(FPout, "%11.11s|", formogebucht);
	fprintf(FPout, "%11.11s|", formogebuchtp);
	fprintf(FPout, "%20.20s|", formeinkauf);
	fprintf(FPout, "%20.20s|", formumsatz);
	fprintf(FPout, "%18.18s|", formreduktion);
	fprintf(FPout, "%18.18s|", formmarge);
	fprintf(FPout, "%11.11s", formreduktp);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_ARR);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatBodyArr ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatBodyArr ( char *katBez, int gebucht, int totplaetze,
                             int *line, int optional, double ePreis,
                             double vPreis, double reduktion, char last )
{
	double proz = (double)0.0;      /* Prozentwerte Temp. Abspeichern */
	char cashstring[_CHAR80+1];
	int  totalpl = (int)0;


	/*--- Anfang leer ---------------------------*/
	fprintf(FPout, ANFLEER);

	/*--- Kategorie Bezeichnung -----------------*/
	fprintf(FPout, "%-20.20s", katBez);
	fprintf(FPout, ZWILEER);

	/*--- Anzahl Plaetze ------------------------*/
	if ( last == TRUE )
	{
		totalpl = (int)0;
	}
	else
	{
		totalpl = totplaetze;
	}

	fprintf(FPout, "%5d", totalpl);
	fprintf(FPout, ZWILEER);

	/*--- fest gebucht --------------------------*/
	fprintf(FPout, "%5d", gebucht);
	fprintf(FPout, ZWILEER);

	/*--- fest gebucht in Prozenten -------------*/
	if ( gebucht > (int)0 && totplaetze > (int)0 )
	{
		proz =  (double)gebucht / (double)totplaetze;
		proz *= (double)100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, ZWILEER);

	/*--- optional gebucht ----------------------*/
	fprintf(FPout, "%5d", optional);
	fprintf(FPout, ZWILEER);

	/*--- optional gebucht in Prozenten ---------*/
	if ((double)optional > (double)0.0 && (double)totplaetze > (double)0.0)
	{
		proz = (double)optional / (double)totplaetze;
		proz *= 100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, ZWILEER);

	/*--- Einkauf -------------------------------*/
	cashdouble(ePreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Umsatz --------------------------------*/
	cashdouble(vPreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Ermaessigungen, Marge -----------------*/
	cashdouble(reduktion, cashstring);
	fprintf(FPout, "%12.12s", cashstring);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0)
	{
		proz = vPreis - ePreis;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%12.2f", proz);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0)
	{
		proz = (vPreis - ePreis) / vPreis;
		proz *= 100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, "%s", _P_EOL_);
	(*line)++;

}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatTailArr ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTstatTailArr ( int totplaetze, int totgebucht, int *line,
                             int optional, double ePreis, double vPreis,
                             double reduktion )
{

	static char formtotal[_CHAR80+1] = { "" };
	double proz = (double)0.0;      /* Prozentwerte Temp. Abspeichern */
	char cashstring[_CHAR80+1];

	if (!*formtotal)
	{
		(void)LanguageDependentText( TEXTID2, (int)_STATISTIK_TYP,
	                                aktuellesprache,
	                                aktuellesprache,
	                                formtotal );
	}

	/*--- Total ---------------------------------*/
	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_ARR);
	fprintf(FPout, "%s", _P_EOL_);
	line++;

	/*--- Anfang leer ---------------------------*/
	fprintf(FPout, ANFLEER);

	/*--- Kategorie Bezeichnung -----------------*/
	fprintf(FPout, "%-20.20s", formtotal);
	fprintf(FPout, ZWILEER);

	/*--- Anzahl Plaetze ------------------------*/
	fprintf(FPout, "%5d", totplaetze);
	fprintf(FPout, ZWILEER);

	/*--- fest gebucht --------------------------*/
	fprintf(FPout, "%5d", totgebucht);
	fprintf(FPout, ZWILEER);
	if ((double)totgebucht > (double)0.0 && (double)totplaetze > (double)0.0)
	{
		proz = (double)totgebucht/(double)totplaetze;
		proz *= 100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, ZWILEER);

	/*--- optional gebucht ----------------------*/
	fprintf(FPout, "%5d", optional);
	fprintf(FPout, ZWILEER);
	if ((double)optional > (double)0.0 && (double)totplaetze > (double)0.0)
	{
		proz = (double)optional/(double)totplaetze;
		proz *= 100.0;
	}
	else
	{
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, ZWILEER);

	/*--- Einkauf -------------------------------*/
	cashdouble(ePreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Umsatz --------------------------------*/
	cashdouble(vPreis, cashstring);
	fprintf(FPout, "%14.14s", cashstring);
	fprintf(FPout, ZWILEER);

	/*--- Ermaessigungen, Marge -----------------*/
	cashdouble(reduktion, cashstring);
	fprintf(FPout, "%12.12s", cashstring);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0) {
		proz = vPreis - ePreis;
	} else {
		proz = (double)0.0;
	}
	fprintf(FPout, "%12.2f", proz);
	fprintf(FPout, ZWILEER);
	if (vPreis > (double)0.0 && ePreis > (double)0.0) {
		proz = (vPreis - ePreis) / vPreis;
		proz *= 100.0;
	} else {
		proz = (double)0.0;
	}
	fprintf(FPout, "%5.1f", proz);
	fprintf(FPout, "%s", _P_EOL_);
	line++;

	fprintf(FPout, ANFLEER);
	fprintf(FPout, TOT_ULINE_ARR);
	fprintf(FPout, "%s", _P_EOL_);

}

/*F--------------------------------------------------------------------------
 *  Function:	OUTintToDate ()
 *
 *
 *  In:			-
 *  out:			-
 *  Return:		- keiner
 *---------------------------------------------------------------------------
 */

static void OUTintToDate( int time, char *date)
{
	struct tm DateTime;
	int    i;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));

	DateTime.tm_min  = (int)_UNDEF;
	DateTime.tm_hour = (int)_UNDEF;
	DateTime.tm_mday = (int)_UNDEF;
	DateTime.tm_mon  = (int)_UNDEF;
	DateTime.tm_year = (int)_UNDEF;

	(void)WriteDate(&DateTime, (time_t *)&time, date);

	for ( i = strlen(date); i >= 0; i-- )
	{
		if ( date[i] == ' ' )
		{
			date[i+1] = '\0';
			break;
		}
	}
}

static int	OUTstatGetDlgDlg1 ( int *AnzDtg, MEMOBJ *dtgmem, int dlaid )
{
	extern int	time_start, time_end;
	char	query[_QUERYLEN];
	int	status;

	/*--- Init ----------------------------------*/
	*query	= NULL;
	status	= (int)MPOK;

	/*--- Bestimme alle DLT ---------------------*/

	sprintf(query, _SEL_DTG_H_DLA, dialogsprache, time_start, time_end, dlaid);

	dtgmem->buffer = NULL;
	dtgmem->alloclen = 0;
	dtgmem->datalen = 0;

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	status = MPAPIdb_sqlquery((int)_DTG_VIEW,
	                          (char **)(&dtgmem->buffer),
	                          query,
	                          AnzDtg,
	                          &dtgmem->datalen,
	                          &dtgmem->alloclen );

	MPAPIdb_committrx();

	if ( (*AnzDtg) == (int)0 )
	{
		sprintf(query, _SEL_DTG_DLA, dialogsprache, time_start, time_end, dlaid);

		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

		status = MPAPIdb_sqlquery((int)_DTG_VIEW,
	                             (char **)(&dtgmem->buffer),
	                             query,
	                             AnzDtg,
	                             &dtgmem->datalen,
	                             &dtgmem->alloclen );

		MPAPIdb_committrx();
	}

	return status;
}


/*F--------------------------------------------------------------------------
 *  Function:	OUTstatPriceMatrixPrepare ()
 *					get DLA and get prices  
 *  In:			-reisender typ 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
static int OUTstatPriceMatrixPrepare( RESERVATION *pRes, int aRkrid )
{
	extern 	DLN_VIEW			dlnv;
	extern	KOSTEN_ART		kar;
	extern	DIENST_TRAEGER dlt;
	extern	DIENST_ANGEBOT	dla;
	extern	PREIS			*preis ;
	extern	int			anzPreis;
	extern	PRICERESULT		*priceMatrix;
	extern	MEMOBJ		matrixmem;
	extern	int			anzMatrix;
	
	DLG_PART			dlg_part;
	PREIS				*pPreis;
	PRICERESULT		*pPrMat;
	int		m, k, id, status, count, result; 
	int		theDlaid ;
	
	/*--- inits ------------------*/
	status = (int)MPOK ;
		
	anzMatrix = 0;
	
	/*--- valid Dl for operation ------------------------------------*/
	if (pRes->dlg_id != (int)_UNDEF )
	{
		status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

		/*--- find dla  !! mw special trick !!! through dlt ----------------*/
		status = MPAPIselectDLT( (int)_UNDEF, (int)_UNDEF, pRes->dlg_id, &dlt);
		if (status != (int)MPOK)
		{ 
			AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
			return( (int)MPERROR );                           /* >>>> exit */
		}
		else
			theDlaid = dla.dla_id;
		
		/*--- get prices --------------------------------------------*/
		status = AKTpriceFindAll( theDlaid, pRes->dlg_id);   
		if (status != (int)MPOK)
		{
			AKTmsg( ACT_ERROR, MPA_SELECTERROR, NULL);
			return ( (int)MPERROR );                             /* >>>> exit */
		}
		
		/*--- there must be a price otherwise smthg is wrong --------*/
		status =  AKTpriceVerify( pRes, aRkrid );
		if ( status == (int)MPERROR )
		{
			AKTmailPriceProblem( pRes->bid, pRes->dlg_id); 
			AKTpricePrintAllValid( );
			/* continue with pricing without exit */
		}
		
		/*--- Dl_part bez for res_flag --------*/
		id = MPAPIselectOneId((int)_DLG_PART, pRes->dl_id, (char *)&dlg_part);
		
		/*--- Build price matrix ------------------------------------------*/
		for (m=0;  m < anzPreis;  m++)
		{
			pPreis = &preis[m];
			/*--- Kosten art  -------------*/
			if (( pPreis->pre_id != (int)_UNDEF) && (pPreis->kar_id != (int)_UNDEF) )
			{
				/*--- Price matrix -----------------------*/
				matrixmem.datalen = (anzMatrix+1)* sizeof(PRICERESULT);
				matrixmem.buffer = (char *)MPallocobj( &matrixmem,
																  PRICEMEMCHUNK * sizeof(PRICERESULT) );
				priceMatrix = (PRICERESULT *)matrixmem.buffer;
				pPrMat = &priceMatrix[anzMatrix];
				pPrMat->preid    = pPreis->pre_id ;
				pPrMat->bid      = pRes->bid ;
				pPrMat->dlnid    = pRes->pers_id ;
				pPrMat->karid    = pPreis->kar_id ;
				pPrMat->dlttid   = pPreis->dltt_id ;
				pPrMat->katid    = pRes->kat_id ;
				pPrMat->rkrid    = aRkrid ;
				pPrMat->dlaid    = theDlaid ;
				pPrMat->dlgid    = pRes->dlg_id ;
				pPrMat->kontid   = pRes->kont_id ;
				pPrMat->resflag  = dlg_part.res_f; 
				pPrMat->azeit    = pRes->a_zeit;  
				pPrMat->ezeit    = pRes->e_zeit;
				pPrMat->ankaufVal   = pPreis->apr;
				pPrMat->einstandVal = pPreis->epr;
				pPrMat->verkaufVal  = pPreis->vpr;
				anzMatrix++ ;
			} 
		}
		MPAPIdb_committrx();
	}

	return ( (int)MPOK );
}

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatUpgradeToAdult ()
 *					Change the rkr_id of Reisender if only one adult is in the cabin
 *             and there have to be two ! Festival only
 *  In:			REISENDER rei
 *             int anzEffektiv
 *  out:			-
 *  Return:		theRkrid 
 *---------------------------------------------------------------------------
 */
static int OUTstatUpgradeToAdult( REISENDER rei, int anzEffektiv )
{
  
	extern int   TarifLimit ;
	extern int   ReiType ;
	extern int   UpgradeBabyAdult ;
	extern int   UpgradeYouthAdult ;
	extern int   UpgradeChildAdult ;

   int theRkrid;                   
	
	/*--- Check for all Upgrades  -----------------------------------*/
	if (anzEffektiv < TarifLimit)
	{
		if ( rei.rkr_id == UpgradeBabyAdult )           /* Baby --> Adult */
			rei.rkr_id = ReiType;
		else if ( rei.rkr_id == UpgradeChildAdult )     /* Child --> Adult */
			rei.rkr_id = ReiType;
		else if ( rei.rkr_id == UpgradeYouthAdult )     /* Youth --> Adult */
			rei.rkr_id = ReiType;
	}

	theRkrid = rei.rkr_id ;
	return( theRkrid );
}
/***************************************************************/
/************************              *************************/
/*********************>  ENDE STATISTIK  <**********************/
/************************              *************************/
/***************************************************************/
