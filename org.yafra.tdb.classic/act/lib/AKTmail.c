/*D***********************************************************
 * Name:      AKTmail.c
 * Modul:     AKT base moduls
 *            prepare mail messages
 *
 * Copyright: yafra.org, Basel, Switzerland
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTmail.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */



/*F************************************************************
 * Function:  AKTmailHeader
 *            write the header of mail text
 *            Dialogsprache is used
 *
 **************************************************************/
int AKTmailHeader(void)
{
	extern char		userid[];                /* MPdbi_glob.h defines */
	extern int		dialogsprache;
	extern char		mailstring[];
	extern	SPRACHEN			spr;
	extern	STATUS_WERTE	sta;
	extern	DEVICE_PORT		devicePort;
	extern int targetsta;
	extern int sourcesta;

	DEVICE_PORT	*pDev;
	int		id;
	char		cdate[_DATELEN];               /* Current Date */
	char		ctime[_DATELEN];               /* Current Time */
	char     format[_RECORDLEN];
	char		bezeichnung[_RECORDLEN];
	char		language[_CHAR30+1];                               /* sprache */

	/*--- general inits ------------*/
	pDev = &devicePort;
	*language		= (char)NULL;
	*bezeichnung	= (char)NULL;


	/*--- Date and time --------------------*/
	id = MPAPIselectOneId((int)_SPRACHEN, dialogsprache, (char *)&spr);
	if (id != (int)_UNDEF)
		copyTextTo( language, spr.sysbez, _CHAR20);
	else
		sprintf( language, "%s", DEFAULTLANGTEXT);
	(void)put_date_in(cdate, ctime, language, "%b %d %y", "%X" );
	AKTmsgget( MPA_MAILHEADER1, format);
	(void)sprintf( mailstring, format, cdate, ctime);
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

	/*--- User -----------------------------*/
	AKTmsgget( MPA_MAILHEADER2, format);
	(void)sprintf( mailstring, format, userid);
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

	/*--- Device ---------------------------*/
	*bezeichnung	= (char)NULL;
	sta.typ = (int)_DEVICE;
	id = MPAPIselectOneId((int)_STATUS_WERTE, pDev->type, (char *)&sta);
	(void)AKTobjbez((int)_DEVICE, sta.bez_id, bezeichnung);
	/*--- Device type ----*/
	AKTmsgget(MPA_OUTPUTTYP, format);
	(void)sprintf(mailstring, format, bezeichnung);       /*selected or nothing*/
	AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
	/*--- File name ------*/
	AKTmsgget(MPA_FILENAME, format);
	(void)sprintf(mailstring, format, pDev->filename);
	AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);

	/*--- Execution type -------------------*/
	*bezeichnung	= (char)NULL;
	sta.typ = (int)_A_FLG;
	id = MPAPIselectOneId((int)_STATUS_WERTE, pDev->delay, (char *)&sta);
	(void)AKTobjbez((int)_A_FLG, sta.bez_id, bezeichnung);
	AKTmsgget(MPA_EXECTYP, format);
	(void)sprintf(mailstring, format, bezeichnung);
	AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);


	/*--- source RESERVATION Status -------------------*/
	if (sourcesta != (int)_UNDEF)
	{
		*bezeichnung	= (char)NULL;
		sta.typ = (int)_R_STA;
		id = MPAPIselectOneId((int)_STATUS_WERTE, sourcesta, (char *)&sta);
		(void)AKTobjbez((int)_R_STA, sta.bez_id, bezeichnung);
		AKTmsgget(MPA_SRCRSTA, format);
		(void)sprintf(mailstring, format, bezeichnung);
		AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
	}

	/*--- target RESERVATION Status -------------------*/
	if (targetsta != (int)_UNDEF)
	{
		*bezeichnung	= (char)NULL;
		sta.typ = (int)_R_STA;
		id = MPAPIselectOneId((int)_STATUS_WERTE, targetsta, (char *)&sta);
		(void)AKTobjbez((int)_R_STA, sta.bez_id, bezeichnung);
		AKTmsgget(MPA_TARGETRSTA, format);
		(void)sprintf(mailstring, format, bezeichnung);
		AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
	}


	return((int)MPOK);
}


/*F************************************************************
 * Function:  AKTmailArrangement
 *            write information about Arrangement
 *
 *
 **************************************************************/
void AKTmailArrangement( int aArrid )
{
	extern char		mailstring[];
	extern int		dialogsprache;
	extern ARRANGEMENT	arr;

	int		id;
	struct tm DateTime;
	char     format[_RECORDLEN];
	char		bez1[_BEZLEN+1];
	char		bez2[_BEZLEN+1];
	char		bezArr[_RECORDLEN];

	/*--- Inits -----*/
   *bez1		= (char)NULL;
   *bez2		= (char)NULL;
   *bezArr	= (char)NULL;
	(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));

	/*--- Arrangement name -------------------------*/
	if (aArrid != (int)_UNDEF)
	{
		id = MPAPIselectOneId( (int)_ARRANGEMENT, aArrid, (char *)&arr);
		(void)AKTobjbez((int)_ARRANGEMENT, arr.bez_id, bez1);
		(void)WriteDate(&DateTime, (time_t *)&arr.a_dat, bez2);
		(void)sprintf(bezArr, "%s %s", bez1, bez2);
		AKTmsgget( MPA_OBJECTARR, format);
		(void)sprintf(mailstring, format, aArrid, bezArr);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
	}
}



/*F************************************************************
 * Function:  AKTmailDetail
 *            write specialized mail text
 *
 **************************************************************/
int AKTmailDetail(int bch_id, int dl_id, int tdl_id, int dla_id, int dlt_id)
{
	extern char		mailstring[];
	extern int		dialogsprache;

	BUCHUNG				bch;
	DIENST_ANGEBOT		dla;
	DIENSTLEISTUNG		dl;
	DLG_PART				dlg_part;
	DIENST_TRAEGER		dlt;
	TRAEGER_TYP			dltt;
	int		id;
	struct tm DateTime;
	char     format[_RECORDLEN];
	char		bezAll[_RECORDLEN];
	char		bez1[_CHAR30+1];
	char		bez2[_CHAR30+1];

	/*--- Inits -----*/
   *bez1		= (char)NULL;
   *bez2		= (char)NULL;
   *bezAll	= (char)NULL;
	(void)memset((void *)&DateTime, (int)NULL, sizeof(DateTime));

	/*--- bch info ------------------------*/
	if (bch_id != (int)_UNDEF)
	{
		id = MPAPIselectOneId( (int)_BUCHUNG, bch_id, (char *)&bch);
		AKTmsgget( MPA_OBJECTBCH, format);
		(void)copyTextTo(bez1, bch.ref, _CHAR256);
		(void)sprintf( mailstring, format, bch_id, bez1);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		*bez1		= (char)NULL;
	}

	/*--- dl info ------------------------*/
	if (dl_id != (int)_UNDEF)
	{
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		id = MPAPIselectOneId( (int)_DIENSTLEISTUNG, dl_id, (char *)&dl);
		(void)AKTobjbez((int)_DIENSTLEISTUNG, dl.bez_id, bez1);
		(void)WriteDate(&DateTime, (time_t *)&dl.a_zeit, bez2);
		(void)sprintf( bezAll, "%s %s", bez1, bez2);

		AKTmsgget( MPA_OBJECTDL, format);
		(void)sprintf(mailstring, format, dl_id, bezAll);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		*bez1		= (char)NULL;
		*bez2		= (char)NULL;
		*bezAll		= (char)NULL;
	}

	/*--- dl_part info --------------------*/
	if (tdl_id != (int)_UNDEF)
	{
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min =(int)_UNDEF;
		id = MPAPIselectOneId((int)_DLG_PART, tdl_id, (char *)&dlg_part);
		(void)AKTobjbez((int)_DLG_PART, dlg_part.bez_id, bez1);
		(void)WriteDate(&DateTime, (time_t *)&dlg_part.a_zeit, bez2);
		(void)sprintf( bezAll, "%s %s", bez1, bez2);

		AKTmsgget( MPA_OBJECTDLID, format);
		(void)sprintf( mailstring, format, tdl_id, bezAll);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		*bez1		= (char)NULL;
		*bez2		= (char)NULL;
		*bezAll		= (char)NULL;
	}

	/*--- dla info ------------------------*/
	if (dla_id != (int)_UNDEF)
	{
		id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dla_id, (char *)&dla);
		(void)AKTobjbez((int)_DIENST_ANGEBOT, dla.bez_id, bez1);
		AKTmsgget( MPA_OBJECTDLA, format);
		(void)sprintf( mailstring, format, dla_id, bez1);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		*bez1		= (char)NULL;
	}

	/*--- dlt info ------------------------*/
	if (dlt_id != (int)_UNDEF)
	{
		id = MPAPIselectOneId( (int)_DIENST_TRAEGER, dlt_id, (char *)&dlt);
		(void)AKTobjbez((int)_DIENST_TRAEGER, dlt.bez_id, bez2);

		id = MPAPIselectOneId( (int)_TRAEGER_TYP, dlt.typ_id, (char *)&dltt);
		if (id != (int)_UNDEF )
			(void)AKTobjbez((int)_TRAEGER_TYP, dltt.bez_id, bez1);

		AKTmsgget( MPA_OBJECTDLT, format);
		(void)sprintf( mailstring, format, dlt_id, bez1, bez2);
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		*bez1		= (char)NULL;
		*bez2		= (char)NULL;
	}

	return( (int)MPOK);
}



/*F************************************************************
 * Function:  AKTmailDevice
 *            write information about client and callnumber
 *            for the kind of devices having these infos
 *
 **************************************************************/
void AKTmailDevice( char *clientname, char *callnr)
{
	extern char		mailstring[];

	char     format[_RECORDLEN];

	/*--- add fax destination to mailing --------------------------*/
	AKTmsgget( MPA_FAXTLXTO, format);
	(void)sprintf( mailstring, format, clientname, callnr);
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
}



/*F************************************************************
 * Function:  AKTmailStatusWrong
 *            write information about source status
 *            which is not compatible with action
 *
 **************************************************************/
void AKTmailStatusWrong( int aBid, int aStatus )
{
	extern char		mailstring[];
	extern	STATUS_WERTE	sta;

	int		id;
	char     format[_RECORDLEN];
	char     bezTxt[_BEZLEN+1];

	/*--- get status description --------------*/
	id = MPAPIselectOneId((int)_STATUS_WERTE, aStatus, (char *)&sta);
	(void)AKTobjbez((int)_R_STA, sta.bez_id, bezTxt);

	/*--- write message -----------------------*/
	AKTmsgget( MPA_SOURCESTAWRONG, format);
	(void)sprintf( mailstring, format, aBid, bezTxt);
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
}



/*F************************************************************
 * Function:  AKTmailPriceProblem
 *            write the detail of price problem
 *            Dialogsprache is used
 *
 **************************************************************/
int AKTmailPriceProblem( int aBid, int aDlid )
{
	extern char		mailstring[];
	extern	DIENSTLEISTUNG		dl;
	extern	BUCHUNG				bch;

	int		id;
	char		tmpbuf[_RECORDLEN];
	char     format[_RECORDLEN];
	char		bchBez[_RECORDLEN];
	char		dlBez[_RECORDLEN];

	/*--- general inits ------------*/
	*tmpbuf	= (char)NULL;
	*bchBez	= (char)NULL;
	*dlBez	= (char)NULL;


	/*--- Error message ! -------------------*/
	AKTmsgget( MPA_ERRORHEADER, tmpbuf);
	(void)sprintf( mailstring, "%s%s %s %s ", _P_EOL_, _P_EOL_, tmpbuf, _P_EOL_ );
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

	/*--- Buchung ---------------------------*/
	if (aBid != (int)_UNDEF)
	{
		id = MPAPIselectOneId( (int)_BUCHUNG, aBid, (char *)&bch);
		(void)copyTextTo(bchBez, bch.ref, _CHAR256);
	}
	/*--- Dienstleistung --------------------*/
	if (aDlid != (int)_UNDEF)
	{
		id = MPAPIselectOneId((int)_DIENSTLEISTUNG, aDlid, (char *)&dl);
		(void)AKTobjbez( (int)_DIENSTLEISTUNG, dl.bez_id, dlBez);
	}
	AKTmsgget( MPA_PRICEERROR, format);
	(void)sprintf( mailstring, format, bchBez, dlBez);
	AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

	return((int)MPOK);
}





/*F************************************************************
 * Function:  AKTmailFoot
 *            write the foot of mail text
 *
 **************************************************************/
void AKTmailFoot( int status)
{
	/*---- check status  -------------*/
	if (status == (int)MPOK)
		AKTmsg(ACT_INFO,  MPA_CONFIRMMSG, NULL);
	else
		AKTmsg(ACT_ERROR, MPA_NOSTART,    NULL);
}


