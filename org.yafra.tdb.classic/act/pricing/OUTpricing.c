/*D***********************************************************
 * program:      OUTpricing
 * descripton:   print out all prices for a country with a currency
 *
 * arguments:    standard arguments
 *               -t  must   action typ           (AKTIONS_TYP  akttid)
 *               -k  must   KUN id               (KUNDEN id)
 *               -f  opt    if set to 1, disable exchange calculating
 *
 * copyright: yafra.org, Switzerland
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/pricing/OUTpricing.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/* version */
#include "version.h"

/* define the entry point of this function for the main() */
int OUTpricing(int, char *[]);
#define ACTIONFUNCTION (OUTpricing)

/*--- MarcoPolo API includes */
#include <mpact.h>

/*--- MarcoPolo API standard main function ! */
#include "AKTmain.h"

/*--- global SQL selects include ----*/
#include <mpsqlsel.h>

/*--- define text ids for language independent text */
#define PRINTCOMMAND1 1

/* margins for AKTobjtxt */
#define LEFTMARGIN	"       "

static int ManagePrices(int, int, int, int);
static int ManageWhr(PREIS, PREIS *, LAND_WHR *);

/*F--------------------------------------------------------------------------
 *  Function:	OUTpricing ()
 *					main function
 *  In:			standard args
 *  out:			e-mail, output (file, printer, ...)
 *  Return:		completion code
 *---------------------------------------------------------------------------
 */
int OUTpricing(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern STATUS_WERTE	sta;	/*--- get BM menu --------------------------*/
	extern int	dialogsprache;
	extern int	aktuellesprache;
	extern int	outputsprache;
	extern int	globalflag;
	extern int	DebugFlag;
	extern STATUS_WERTE sta;

	extern WAEHRUNG whr;
	extern LAND land;

	DEVICE_PORT	*pDev;
	int		status, id;
/*	time_t	clock_value; */
	char     format[_RECORDLEN];
	char     landbez[_RECORDLEN];
	char     whrbez[_RECORDLEN];
	char     kunbez[_RECORDLEN];
	KUN_VIEW prekunv;

	/*--- init ----------------------------------*/
	pDev = &devicePort;
	*language = (char)NULL;
	*format   = (char)NULL;
	*landbez   = (char)NULL;
	*whrbez   = (char)NULL;
	*kunbez   = (char)NULL;
	aktuellesprache = dialogsprache;


	if (DebugFlag)
		(void)printf("\n\ndebug: Version %s\n\n", MAINVERSION);


	/* begin mailing and argument checking */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)           /*>>>> exit */
	/*--- mailing header --------------------------*/
	status = AKTmailHeader();
	if (status != (int)MPOK)
		EXIT_WITH_STATUS(status)                                /*>>>> exit */
	/*--- check if obligatory arguments are set ---*/
	if (akttid == (int)_UNDEF || kunid == (int)_UNDEF)
		{
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		EXIT_WITH_STATUS(MPERROR)                               /*>>>> exit */
		}
	(void)MPAPIdb_committrx();


	/* get KUNDE */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	id = MPAPIselectOneId((int)_KUN_VIEW, kunid, (char *)&prekunv);
	if (id == (int)_UNDEF)
		{
		(void)MPAPIdb_committrx();
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		return(MPERROR);
		}
	(void)copyTextTo(kunbez, (char *)prekunv.name, (int)_CHAR512);
	/* get LAND of KUNDE */
	id = MPAPIselectOneId((int)_LAND, (int)prekunv.land_id, (char *)&land);
	if (id == (int)_UNDEF || SelectBez((int)_LAND, aktuellesprache, land.bez_id,
	    landbez) == (int)_UNDEF)
		{
		(void)MPAPIdb_committrx();
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		return(MPERROR);
		}
	/* get WAEHRUNG of KUNDE */
	id = MPAPIselectOneId((int)_WAEHRUNG, (int)prekunv.whr_id, (char *)&whr);
	if (id == (int)_UNDEF || SelectBez((int)_WAEHRUNG, aktuellesprache,
	    whr.bez_id, whrbez) == (int)_UNDEF)
		{
		(void)MPAPIdb_committrx();
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		return(MPERROR);
		}
	(void)MPAPIdb_committrx();
	(void)fprintf(FPout, "%s%s%sPRICING view", _P_EOL_, _P_EOL_, _P_EOL_);
	(void)fprintf(FPout, "%s%s", _P_EOL_, _P_EOL_);
	(void)fprintf(FPout, "for:           %s, %s", kunbez, prekunv.ort, landbez);
	(void)fprintf(FPout, "%s", _P_EOL_);
	(void)fprintf(FPout, "with currency: %s%s", whrbez, _P_EOL_);
	(void)fprintf(FPout, "%s%s", _P_EOL_, _P_EOL_);
	(void)fprintf(FPout, "ID   Kostenart             Kategorie             Traegertyp      DLN-Typ              Whr              AP        EP        VP    von      bis%s", _P_EOL_);


	/* start detailed output now */
	if (DebugFlag)
		(void)fprintf(stderr, "debug: start pricing with country and currency:");
	status = ManagePrices(kunid, prekunv.land_id, prekunv.whr_id, (int)_UNDEF);
	(void)fprintf(FPout, "%s%s%send of list", _P_EOL_, _P_EOL_, _P_EOL_);


	/*--- Device -------------------------------------------------*/
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	TEST_STATUS_MSG_COMMIT( status, MPA_SELECTERROR)        /*>>>> exit */
	/*--- Get print command -------------------*/
	(void)sprintf(pDev->command, "lp");
	pDev->callnumber[0] = '\0';
	/*--- Device process ----------------------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Status Change: Device error ");
	(void)MPAPIdb_committrx();

exit:
	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

	return(status);
}



static int ManagePrices(int kunid, int landid, int whrid, int dlaid)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];

	extern WAEHRUNG whr;
	extern LAND_WHR lw;

	WAEHRUNG newwhr;
	PREIS newpre;

	PREIS preis;
	PREIS *pre;

	KAR_VIEW kostenart;
	KAT_VIEW kategorie;
	TTYP_VIEW dltt;
	RKR_VIEW reisender_typ;
	DLA_VIEW angebot;
	DTG_VIEW Vdl;
	char buffer[10*_RECORDLEN];
	char outbuf2[_RECORDLEN];
	char outbuf3[_RECORDLEN];
	struct tm DateTime;
	int old_dlaid = (int)_UNDEF;
	int old_dlaglt = (int)_UNDEF;
	int old_dlid = (int)_UNDEF;
	int old_dlglt = (int)_UNDEF;
	int exists=0;
	int status=(int)MPOK;
	int i, id, anzahl;
	int exchangeret;
	int changed;

	/* start trx */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);
	(void)strcpy(sqlquery, "SELECT * FROM TDBADMIN.PREIS ORDER BY DL_ID, DLA_ID, GLT, KAR_ID, KAT_ID, DLTT_ID, RKR_ID;");
	status=MPAPIdb_sqlquery((int)_PREIS, &sqlmem.buffer, sqlquery,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	pre = (PREIS *)sqlmem.buffer;
	if (anzahl < (int)1 || status != (int)MPOK)
		{
		(void)MPAPIdb_committrx();
		AKTmsg( ACT_ERROR, MPA_INVALIDARGS, NULL);
		return(MPERROR);
		}

	/* set country and currency policy */
	lw.land_id = landid;
	lw.kurs_typ = _KURS_CREDIT;

	/* now get all prices and convert them to the KUNDE currency */
	*buffer = (char)NULL;
	for (i=0; i<anzahl; i++)
		{
		changed = (int)FALSE;
		if (pre[i].whr_id != whrid)
			{
			if (specificflag != (int)1)
				{
				lw.whr_id = pre[i].whr_id;
				exchangeret = ManageWhr(pre[i], &newpre, &lw);
				if (exchangeret != (int)MPOK)
					{
					if (DebugFlag)
						(void)fprintf(stderr, "debug: exchange rate not in DB for LAND %d and WHR %d%s", lw.land_id, lw.whr_id, _P_EOL_);
					}
				else
					{
					pre[i].vpr = newpre.vpr;
					pre[i].epr = newpre.epr;
					pre[i].apr = newpre.apr;
					changed = (int)TRUE;
					}
				}
			}

		if (pre[i].dla_id != (int)_UNDEF && (pre[i].dla_id != old_dlaid ||
		    (pre[i].dla_id == old_dlaid && pre[i].glt != old_dlaglt)) )
			{
			preis.dla_id=(int)MPAPIselectOneId((int)_DLA_VIEW, (int)pre[i].dla_id, (char *)&angebot);
			if (preis.dla_id == (int)_UNDEF )
				(void)strcpy(angebot.bez, "FEHLER: DLA NICHT GEFUNDEN");
			(void)strcpy(outbuf2, "Kein Datum");
			if (pre[i].glt != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&pre[i].glt, outbuf2);
				}
			(void)fprintf(FPout, "%sAngebot: %30.30s%sGueltig ab: %s%s",
			              _P_EOL_, angebot.bez, _P_EOL_, outbuf2, _P_EOL_);

			/* set old values */
			old_dlaid = pre[i].dla_id;
			old_dlaglt = pre[i].glt;
			}
		else if (pre[i].dl_id != (int)_UNDEF && (pre[i].dl_id != old_dlid ||
		         (pre[i].dl_id == old_dlid && pre[i].glt != old_dlglt)) )
			{
			preis.dl_id=(int)MPAPIselectOneId((int)_DTG_VIEW, (int)pre[i].dl_id, (char *)&Vdl);
			if (preis.dl_id == (int)_UNDEF )
				(void)strcpy(Vdl.bez, "FEHLER: DL NICHT GEFUNDEN");
			if (pre[i].glt != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&pre[i].glt, outbuf2);
				}
			if (Vdl.a_zeit != (int)_UNDEF)
				{
				(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Vdl.a_zeit, outbuf3);
				}
			else
				(void)strcpy(outbuf3, "-");

			(void)fprintf(FPout, "%sDienstleistung: %30.30s %15.15s%sGueltig ab: %s%s",
			              _P_EOL_, Vdl.bez, outbuf3, _P_EOL_, outbuf2, _P_EOL_);

			/* set old values */
			old_dlid = pre[i].dl_id;
			old_dlglt = pre[i].glt;
			}

		/* KOSTEN_ART */
		preis.kar_id=(int)MPAPIselectOneId((int)_KAR_VIEW, (int)pre[i].kar_id, (char *)&kostenart);
		if (preis.kar_id == (int)_UNDEF )
			(void)strcpy(kostenart.bez, " ");
		/* KATEGORIE */
		preis.kat_id=(int)MPAPIselectOneId((int)_KAT_VIEW, (int)pre[i].kat_id, (char *)&kategorie);
		if (preis.kat_id == (int)_UNDEF )
			(void)strcpy(kategorie.bez, " ");
		/* TRAEGER_TYP */
		preis.dltt_id=(int)MPAPIselectOneId((int)_TTYP_VIEW, (int)pre[i].dltt_id, (char *)&dltt);
		if (preis.dltt_id == (int)_UNDEF )
			(void)strcpy(dltt.bez, " ");
		/* DLN TYP */
		preis.rkr_id=(int)MPAPIselectOneId((int)_RKR_VIEW, (int)pre[i].rkr_id, (char *)&reisender_typ);
		if (preis.rkr_id == (int)_UNDEF )
			(void)strcpy(reisender_typ.bez, " ");
		/* WAEHRUNG */
		preis.whr_id=(int)MPAPIselectOneId((int)_WAEHRUNG, (int)pre[i].whr_id, (char *)&whr);
		if (preis.whr_id == (int)_UNDEF )
			(void)strcpy(whr.krzl, " ");
		if (changed == (int)TRUE)
			{
			id=(int)MPAPIselectOneId((int)_WAEHRUNG, (int)whrid, (char *)&newwhr);
			if (id == (int)_UNDEF )
				(void)strcpy(newwhr.krzl, " ");
			}
		/* DL VONDAT */
		if (pre[i].dl_vondat != (int)_UNDEF)
			{
			(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)_UNDEF;
			DateTime.tm_min =(int)_UNDEF;
			(void)WriteDate(&DateTime, (time_t *)&pre[i].dl_vondat, outbuf2);
			}
		else
			(void)strcpy(outbuf2, " ");
		/* DL BISDAT */
		if (pre[i].dl_bisdat != (int)_UNDEF)
			{
			(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));
			DateTime.tm_mday=(int)_UNDEF;
			DateTime.tm_mon =(int)_UNDEF;
			DateTime.tm_year=(int)_UNDEF;
			DateTime.tm_hour=(int)_UNDEF;
			DateTime.tm_min =(int)_UNDEF;
			(void)WriteDate(&DateTime, (time_t *)&pre[i].dl_bisdat, outbuf3);
			}
		else
			(void)strcpy(outbuf3, " ");

		if (changed == (int)TRUE)
			{
			(void)fprintf(FPout, "%-4.0d %-20.20s  %-20.20s  %-15.15s %-20.20s %-3.3s (%-3.3s): %8.2f  %8.2f  %8.2f %-8.8s %-8.8s%s",
		      pre[i].pre_id, kostenart.bez, kategorie.bez, dltt.bez, reisender_typ.bez,
		      newwhr.krzl, whr.krzl, pre[i].apr, pre[i].epr, pre[i].vpr, outbuf2, outbuf3, _P_EOL_);
			}
		else
			{
			(void)fprintf(FPout, "%-4.0d %-20.20s  %-20.20s  %-15.15s %-20.20s %-3.3s:       %8.2f  %8.2f  %8.2f %-8.8s %-8.8s%s",
		      pre[i].pre_id, kostenart.bez, kategorie.bez, dltt.bez, reisender_typ.bez,
		      whr.krzl, pre[i].apr, pre[i].epr, pre[i].vpr, outbuf2, outbuf3, _P_EOL_);
			}
		}

	(void)MPAPIdb_committrx();
	return(status);
}



static int ManageWhr(PREIS actpre, PREIS *newpre, LAND_WHR *usedlw)
{
	LAND_WHR currlw;
	int id;
	double tmppre;
	int abspre;

	(void)memcpy((void *)newpre, (void *)&actpre, sizeof(PREIS));

	currlw.land_id = usedlw->land_id;
	currlw.whr_id = usedlw->whr_id;
	currlw.kurs_typ = usedlw->kurs_typ;

	id = MPAPIselectOneId((int)_LAND_WHR, (int)currlw.land_id, (char *)&currlw);
	if (id == (int)_UNDEF)
		return(MPERROR);
	usedlw->a_kurs = currlw.a_kurs;
	usedlw->v_kurs = currlw.v_kurs;

	newpre->vpr = actpre.vpr * currlw.v_kurs;
	if (newpre->vpr != (double)0)
		{
		tmppre = actpre.vpr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->vpr = (double)abspre / (double)10.0;
			}
		}
	newpre->epr = actpre.epr * currlw.v_kurs;
	if (newpre->epr != (double)0)
		{
		tmppre = actpre.epr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->epr = (double)abspre / (double)10.0;
			}
		}
	newpre->apr = actpre.apr * currlw.v_kurs;
	if (newpre->apr != (double)0)
		{
		tmppre = actpre.apr * currlw.v_kurs;
		tmppre = tmppre * (double)10.0;
		abspre = (int)tmppre;
		tmppre = tmppre - (double)abspre;
		if (tmppre != (double)0.0)
			{
			abspre = abspre + (int)1;
			newpre->apr = (double)abspre / (double)10.0;
			}
		}

	if (DebugFlag)
		(void)fprintf(stderr, "debug: WHR %d calculated with EXCHANGE RATE of %3.6f%s", actpre.whr_id, currlw.v_kurs, _P_EOL_);

	return(MPOK);
}
