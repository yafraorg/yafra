/*D***********************************************************
 * program:      OUTstatkont
 * description:  statistics about KONTINGENTE
 *
 * arguments:    standard arguments
 *               -c  opt    DLG_PART (cruise) Kreuzfahrt
 *
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/statkont/OUTstatkont.c,v 1.2 2008-11-02 19:55:52 mwn Exp $";

/* define the entry point of this function for the main() */
int OUTstatkont(int, char *[]);
#define ACTIONFUNCTION OUTstatkont

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */

/* MarcoPolo API standard main function */
#include "AKTmain.h"       /* Standard main Funktion */

#include "version.h"

#define _SEL_KON_HKON "SELECT * FROM TDBADMIN.KONTINGENT \
	WHERE HOSTKONT_ID = %d;"
#define _SEL_KOND_HKON "SELECT * FROM TDBADMIN.KONT_DETAIL \
	WHERE HOSTKONT_ID = %d ORDER BY KAT_ID, DLT_ID;"
#define _SEL_KOND_KON "SELECT * FROM TDBADMIN.KONT_DETAIL \
	WHERE KONT_ID = %d ORDER BY KAT_ID, DLT_ID;"

/*F--------------------------------------------------------------------------
 *  Function:	OUTstatkont()
 *---------------------------------------------------------------------------
 */
int OUTstatkont(int argc, char *argv[])
{
	extern DEVICE_PORT	devicePort;
	extern STATUS_WERTE	sta;
	extern int dialogsprache;
	extern int outputsprache;
	extern int DebugFlag;
	extern char sqlquery[];
	extern MEMOBJ sqlmem;

	extern DIENST_TRAEGER dlt;
	extern KATEGORIE kat;
	extern TTYP_VIEW ttyp;
	extern HOST_KONT hkon;
	extern KONTINGENT kon;

	AKT_DETAIL	adcntrl;
	DEVICE_PORT	*pDev;

	int status, id, state;
	int i, j, k;
	char bezeichnung[_BEZLEN+5];
	char tmp_bez[_RECORDLEN];
	char tmp_buffer[RECLAENGE];
	char tmp_buffer2[RECLAENGE];
	char cdate[_DATELEN];		/* Current Date */
	char ctime[_DATELEN];		/* Current Time */
	char format[_RECORDLEN];
	char typbez[_BEZLEN+1];
	char dltbez[_BEZLEN+1];
	char katbez[_BEZLEN+1];
	char hkonbez[_BEZLEN+1];
	char konbez[_BEZLEN+1];
	char dlbez[_RECORDLEN];
	char kunbez[_RECORDLEN];
	DLT_VIEW dltv;
	TTYP_VIEW dlttv;
	KAT_VIEW katv;

	KONTINGENT *Pkon;
	int countkon;
	MEMOBJ konmem;

	KONT_DETAIL *Pkd;
	int countkd;

	/*--- init ------*/
	pDev = &devicePort;
	konmem.buffer = NULL;
	konmem.alloclen = 0;
	konmem.datalen = 0;

	/*--- set right language ----------------------------------------------*/
	if (outputsprache == (int)UNDEF)
		aktuellesprache = dialogsprache;
	else
		aktuellesprache = outputsprache;
	sprache = aktuellesprache;

	/* DB: beging work */
	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);

	/*--- mailing header --------------------------------------------------*/
	status = AKTmailHeader() ;
	if (status != (int)MPOK)
		return(status);

	/*--- check if all needed arguments are set (-h) ----------------*/
	if (hostkontid == (int)_UNDEF)
		{
		AKTmsg(ACT_ERROR, MPA_INVALIDARGS, NULL);
		return((int)MPERROR);
		}

	/******** B O D Y ****************/

	/* get host kont */
	(void)MPAPIselectOneId((int)_HOST_KONT, (int)hostkontid, (char *)&hkon);
	(void)SelectBez((int)_HOST_KONT, sprache, hkon.bez_id, hkonbez);
	status = MPAPIselectDLT(hkon.dla_id, (int)_UNDEF, hkon.dl_id, &dlt);
	if (status == (int)MPOK)
		(void)SelectBez((int)_DIENST_TRAEGER, aktuellesprache, dlt.bez_id, dltbez);
	else
		(void)strcpy(dltbez, "-");

	if (hkon.dla_id == (int)_UNDEF)
		(void)MPAPIselectDLbez(hkon.dl_id, aktuellesprache, dlbez, (int)_RECORDLEN);
	else
		{
		(void)MPAPIselectOneId((int)_DIENST_ANGEBOT, (int)hkon.dla_id, (char *)&dla);
		(void)SelectBez((int)_DIENST_ANGEBOT, aktuellesprache, dla.bez_id, dlbez);
		}

	/* update mailing with dlt info */
	AKTmsgget(MPA_OBJECTHKON, format);
	(void)sprintf(mailstring, format, hkonbez);
	AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);

/*DEBUG*****************/
	if (DebugFlag)
		printf("%sdebug: START statistic of host_kont %d - %s now !%s",
				 _P_EOL_, hostkontid, hkonbez, _P_EOL_);
/*DEBUG*****************/



	/***********************************************************************/
	/* FIRST PAGE DESCRIBES THE HOST_KONT                                  */
	/* with all SUB-KONTINGENTE as an overview and all KONT_DETAIL         */
   /* entries for this HOST_KONT                                          */
	/***********************************************************************/

	/* OUT: title */
	(void)fprintf(FPout, "%s%sKontingent-Auswertung:%s%s",
					  _P_EOL_, _P_EOL_, _P_EOL_, _P_EOL_);

	/* OUT: HOST_KONT header */
	(void)fprintf(FPout,    "%sOberkontingent: %s", _P_EOL_, hkonbez);
	if (hkon.from_pers != (int)_UNDEF)
		{
		(void)KUNmkbez(hkon.from_pers, kunbez, (int)_RECORDLEN);
		(void)fprintf(FPout, "%s     Verwalter: %s", _P_EOL_, kunbez);
		}
	else
		(void)fprintf(FPout, "%s     Verwalter: lokal", _P_EOL_);
	(void)fprintf(FPout,    "%s        Tr�ger: %s", _P_EOL_, dltbez);
	if (hkon.dla_id != (int)_UNDEF)
		(void)fprintf(FPout, "%s       Angebot: %s", _P_EOL_, dlbez);
	else
		(void)fprintf(FPout, "%sDienstleistung: %s", _P_EOL_, dlbez);
	(void)fprintf(FPout,  "%s%sSubkontingente:%s%s",
					  _P_EOL_, _P_EOL_, _P_EOL_, _P_EOL_);

	/*--- get all needed SUB-KONTINGENTE ---------------*/
	(void)sprintf(sqlquery, _SEL_KON_HKON, hostkontid);
	status = MPAPIdb_sqlquery((int)_KONTINGENT, (char **)&konmem.buffer,
	                sqlquery, &countkon, &konmem.datalen, &konmem.alloclen);
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}
	Pkon = (KONTINGENT *)konmem.buffer;
	for (i=0;i<countkon;i++)
		{
		if (Pkon[i].kunden_id != (int)_UNDEF)
			{
			(void)KUNmkbez(Pkon[i].kunden_id, kunbez, (int)_RECORDLEN);
			(void)sprintf(tmp_bez, " an Kunde %s", kunbez);
			}
		else
			strcpy(tmp_bez, " ");

		(void)SelectBez((int)_KONTINGENT, aktuellesprache, Pkon[i].bez_id, konbez);
		(void)fprintf(FPout, "%s   - %s %s", _P_EOL_, konbez, tmp_bez);
		}

	(void)fprintf(FPout,  "%s%sGesamt-Mengendefinition:%s%s",
					  _P_EOL_, _P_EOL_, _P_EOL_, _P_EOL_);

	/*--- get all needed KONT_DETAIL for HOST_KONT -------------*/
	(void)sprintf(sqlquery, _SEL_KOND_HKON, hostkontid);
	status = MPAPIdb_sqlquery((int)_KONT_DETAIL, (char **)&sqlmem.buffer,
	                sqlquery, &countkd, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != MPOK)
		{
		AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
		return(MPERROR);
		}
	Pkd = (KONT_DETAIL *)sqlmem.buffer;
	for (i=0; i<countkd; i++)
		{
		if (Pkd[i].kat_id != (int)_UNDEF)
			{
			id = MPAPIselectOneId((int)_KAT_VIEW, (int)Pkd[i].kat_id,
			     (char *)&katv);
			(void)copyTextTo(tmp_bez, katv.bez, _BEZLEN);

			/*!!! hardcoded */
			(void)fprintf(FPout, "%s  mit %d Einheiten%s", tmp_bez, Pkd[i].anz, _P_EOL_);
			}
		else if (Pkd[i].dlt_id != (int)_UNDEF)
			{
			id = MPAPIselectOneId((int)_DLT_VIEW, Pkd[i].dlt_id, (char *)&dltv);
			/* get dltt of host dlt */
			id = MPAPIselectOneId((int)_TTYP_VIEW, (int)dltv.typ_id, (char *)&dlttv);
			if (id != (int)_UNDEF)
				{
				(void)copyTextTo(typbez, dlttv.bez, (int)_BEZLEN);
				(void)strcat(typbez, ": ");
				}
			else
				typbez[0] = (char)NULL;

			(void)copyTextTo(tmp_bez, dltv.bez, _BEZLEN);
			(void)fprintf(FPout, "%s%s%s", typbez, tmp_bez, _P_EOL_);
			}
		
		}


	/***********************************************************************/
	/* A DESCRIPTION OF A SUB-KONTINGENT PER PAGE !!                       */
   /* with all KONT_DETAIL entries                                        */
	/***********************************************************************/
	for (i=0;i<countkon;i++)
		{
		/* OUT: new page */
		fprintf(FPout, "%s", _P_EOL_ );    /* LF + CR */

		(void)SelectBez((int)_KONTINGENT, aktuellesprache, Pkon[i].bez_id, konbez);
		(void)fprintf(FPout, "%s%s%s%s%s%s%s",
						  _P_EOL_, _P_EOL_, _P_EOL_, konbez, _P_EOL_, _P_EOL_, _P_EOL_);

		/*--- get all needed KONT_DETAIL for current SUB-KONTINGENT ---------*/
		(void)sprintf(sqlquery, _SEL_KOND_KON, Pkon[i].kont_id);
		status = MPAPIdb_sqlquery((int)_KONT_DETAIL, (char **)&sqlmem.buffer,
		                sqlquery, &countkd, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != MPOK)
			{
			AKTmsg(ACT_SQLERROR, MPA_SELECTERROR, NULL);
			return(MPERROR);
			}
		Pkd = (KONT_DETAIL *)sqlmem.buffer;
		for (j=0; j<countkd; j++)
			{
			if (Pkd[j].kat_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_KAT_VIEW, (int)Pkd[j].kat_id,
				     (char *)&katv);
				(void)copyTextTo(tmp_bez, katv.bez, _BEZLEN);

				/*!!! hardcoded */
				(void)fprintf(FPout, "%s  mit %d Einheiten%s",
								  tmp_bez, Pkd[j].anz, _P_EOL_);
				}
			else if (Pkd[j].dlt_id != (int)_UNDEF)
				{
				id = MPAPIselectOneId((int)_DLT_VIEW, Pkd[j].dlt_id, (char *)&dltv);
				/* get dltt of host dlt */
				id = MPAPIselectOneId((int)_TTYP_VIEW, (int)dltv.typ_id, (char *)&dlttv);
				if (id != (int)_UNDEF)
					{
					(void)copyTextTo(typbez, dlttv.bez, (int)_BEZLEN);
					(void)strcat(typbez, ": ");
					}
				else
					typbez[0] = (char)NULL;

				(void)copyTextTo(tmp_bez, dltv.bez, _BEZLEN);
				(void)fprintf(FPout, "%s%s%s", typbez, tmp_bez, _P_EOL_);
				}
			}
		}



	/***********************************************************************/
	/* A SHORT STATISTIC ON THE LAST PAGE                                  */
   /* statistic for the whole stuff (HOSTS and SUBS)                      */
	/***********************************************************************/

	MPAPIdb_committrx();
	MPfree(konmem.buffer);

	/*--- Device start output ---------------------------------------------*/
	pDev->callnumber[0] = '\0';
	(void)sprintf(pDev->command, "%s", "lp -odouble -ohalf");
	/*--- Device process ------*/
	status = AKTdeviceOuput();
	if (status != MPOK)
		AKTmsg(ACT_ERROR, (int)_UNDEF, "Action Program: Device error ");

/*DEBUG*****************/
	if (DebugFlag)
		printf("%s%sdebug: EXIT with status: %d, mailingadr: %s%s%s",
				 _P_EOL_, _P_EOL_, status, userid, _P_EOL_, _P_EOL_);
/*DEBUG*****************/

	/*--- Mailing foot -------------------------------------------*/
	AKTmailFoot(status);

	return(status);
}

