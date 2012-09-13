/**************************************************************
 * Modul:     AKT base moduls
 *            control state of action
 *            control typ and data is in parameter
 *            cntrltyp and ctrl_ad defined
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/

#include <mpact.h>         /* Standart Includefile   */

#include "version.h"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTcntrl.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/*P--- EXTERNALS -----------------------------------------------------------*/


/*P--- PROTOTYPES ----------------------------------------------------------*/


/*P--- LAYOUT --------------------------------------------------------------*/


/*P--- GLOBALS  ------------------------------------------------------------*/


/*P--- STATICS -------------------------------------------------------------*/
static int LocalActionNumber = (int)_UNDEF;

/*P--- SQL ------------------------------------------------------------------*/

#define _SQL_AKTCTRLSELECT "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE BID =%d AND A_TYP_ID = %d;"
#define _SQL_AKTCTRLSELECTDL "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE BID =%d AND A_TYP_ID = %d AND DLG_ID = %d;"
#define _SQL_AKTCTRLRESSTA "UPDATE TDBADMIN.RESERVATION \
	SET R_STA = %d WHERE BID = %d AND DLG_ID = %d;"

#define _SEL_BID_AKT_NR "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE A_TYP_ID = %d AND BID = %d AND DL_ID = %d;"
#define _SEL_DLN_AKT_NR "SELECT * FROM TDBADMIN.AKT_DETAIL \
	WHERE A_TYP_ID = %d AND BID = %d AND PERS_ID = %d AND DL_ID = %d;"

/*F--------------------------------------------------------------------------
 * Function:  AKTcntrl
 *            control state of action 
 *---------------------------------------------------------------------------
 */
int AKTcntrl(int cntrltyp, AKT_DETAIL *ctrl_ad, int resstat)
{
	extern char mailstring[];

	MEMOBJ admem;
	AKT_DETAIL *ad;
	AKTIONEN aktion;
	int status = (int)MPOK;
	int anzad;
	int anzahl;
	int i;
	int id;
	char query[_RECORDLEN];
	char format[_RECORDLEN];

	/* init */
	admem.buffer = NULL;
	admem.datalen = 0;
	admem.alloclen = 0;

	if (ctrl_ad->bid == (int)_UNDEF || ctrl_ad->a_typ_id == (short)_UNDEF)
		return(MPERROR);

	if (ctrl_ad->dlg_id != (int)_UNDEF)
		(void)sprintf(query, _SQL_AKTCTRLSELECTDL, ctrl_ad->bid,
		                     ctrl_ad->a_typ_id, ctrl_ad->dlg_id);
	else
		(void)sprintf(query, _SQL_AKTCTRLSELECT, ctrl_ad->bid, ctrl_ad->a_typ_id);
	status = MPAPIdb_sqlquery((int)_AKT_DETAIL, (char **)&admem.buffer, query,
	        &anzad, &admem.datalen, &admem.alloclen);

   /* first check if there are any entries in AKT_DETAIL, because of TO 2000 */
   /* if there are no entries, exit with no error code */
	if (status == (int)MPOK && anzad == (int)0)
		{
		free(admem.buffer);
		return((int)MPOK);
		}

   /* if status is not ok or the count of AKT_DETAIL is below 1 - exit with error */
	if (status != (int)MPOK || anzad < 1)
		{
		free(admem.buffer);
		return((int)MPERROR);
		}

	ad = (AKT_DETAIL *)admem.buffer;
	switch(cntrltyp)
		{
		case _AKTCNTRL_CHECK:
			for(i=0; i<anzad; i++)
				{

				/*-- check if already done or multiple exec. forces to ready */
				if ((ad[i].z_flag == _AKT_OK) && (ctrl_ad->z_flag != _AKT_READYTOSTART))
					{
					AKTmsgget(MPA_ALREADYOK, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}

				/* check if already started right now */
				if (ad[i].z_flag == _AKT_ONEXECUTION)
					{
					AKTmsgget(MPA_ALREADYSTARTED, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}

				/* check if action is on fatal error state */
				if (ad[i].z_flag == _AKT_FATALERROR)
					{
					AKTmsgget(MPA_FATALERRORSTATE, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}

				/* set action number and state flag */
				ad[i].akt_nr = MPAPIid_max((int)_AKT_DETAIL, (int)ad[i].a_typ_id,
				                          (char *)NULL)+1;
				ad[i].z_flag = (int)_AKT_ONEXECUTION;
				status = MPAPIupdateEntry((int)_AKT_DETAIL, (char *)&ad[i],
				                        (BEZEICHNUNG *)NULL );
				if (status != (int)MPOK)
					{
					AKTmsgget(MPA_CNTRLDBERROR, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}
				}
			break;

		case _AKTCNTRL_CONFIRM:
			for (i=0; i<anzad; i++)
				{
				/* get target res state if not as argument set */
				if (resstat == (int)_UNDEF)
					{
					/* get the right resstat from the AKTIONEN tabel */
					id = MPAPIselectOneId((int)_AKTIONEN, ad[i].akt_id, (char *)&aktion);
					if (id != (int)_UNDEF)
						resstat = aktion.b2_flag;
					}

				/* only if a target res state is set, set res to this state */
				/* else let it be as it is now */
				if (resstat != (int)_UNDEF)
					{
					(void)sprintf(query, _SQL_AKTCTRLRESSTA, resstat, ad[i].bid,
					                      ad[i].dlg_id);
					status = MPAPIdb_sqlcommand(query, &anzahl);
					if (status != (int)MPOK)
						{
						AKTmsgget(MPA_NOCONFIRM, format);
						(void)sprintf(mailstring, format, ad[i].bid);
						AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
						status = (int)MPERROR;
						break;
						}
					}

				/* set state of AKTION execution to OK in AKT_DETAIL */
				(void)time((time_t *)&ad[i].exec_dat); /* Ausfuehrungsdatum setzen */
				ad[i].z_flag = (int)_AKT_OK;
				status = MPAPIupdateEntry((int)_AKT_DETAIL, (char *)&ad[i], (BEZEICHNUNG *)NULL );
				if ( status != (int)MPOK ) 
					{
					AKTmsgget(MPA_NOCONFIRM, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}

				/* commit data so we can update the right RES_STA */
				(void)MPAPIdb_committrx();
				(void)MPAPIdb_begintrx(SQLISOLATION_RC, SQLPRIO_NORMAL);

				/* try to update STA of BUCHUNG */
				(void)MPAPIupdate_booksta(ad[i].bid);
				}
			break;

		case _AKTCNTRL_ERROR:
			for (i=0; i<anzad; i++)
				{
				ad[i].exec_dat = (int)_UNDEF;
				ad[i].z_flag = (int)_AKT_ERROR;
				status = MPAPIupdateEntry((int)_AKT_DETAIL, (char *)&ad[i], (BEZEICHNUNG *)NULL );
				if ( status != (int)MPOK ) 
					{
					AKTmsgget(MPA_CNTRLDBERROR, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					}
				}
			AKTmsgget(MPA_SETTOERROR, format);
			(void)sprintf(mailstring, format, ad[i].bid);
			AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
			break;

		case _AKTCNTRL_REINIT:
			for(i=0; i<anzad; i++)
				{
				ad[i].z_flag = (int)_AKT_READYTOSTART;
				status = MPAPIupdateEntry((int)_AKT_DETAIL, (char *)&ad[i],
				                        (BEZEICHNUNG *)NULL );
				if (status != (int)MPOK)
					{
					AKTmsgget(MPA_CNTRLDBERROR, format);
					(void)sprintf(mailstring, format, ad[i].bid);
					AKTmsg(ACT_INFO, (int)_UNDEF, mailstring);
					status = (int)MPERROR;
					break;
					}
				}
			break;

		default:
			status = (int)MPERROR;
			break;
		}

	free(admem.buffer);
	return(status);
}



/*SF-------------------------------------------------------------------------
 *  Function:  AKTcntrlGiveActionNumber()
 *             - sucht zur Buchungs-Id die Ticketnummer
 *  In:        - AktionsTyp, BuchungsId, DlgId, fpMail
 *  out:       - none
 *  Return:    - Ticketnummer
 *---------------------------------------------------------------------------
 */
int AKTcntrlGiveActionNumber ( int aAktionsTyp, int aBuchungsId, int aDlnId, int aDlgId, int flag )
{
	extern int  ActionNumber;

	AKT_DETAIL	*aktDet		= NULL;
	int			status		= (int)MPOK;
	int			TicketNr		= (int)0;
	int			anzAkt		= (int)0;
	int         i;
	unsigned long dataLen	= (unsigned long)0;
	unsigned long allocLen	= (unsigned long)0;
	
	char mailstring[_RECORDLEN];
	char query[_QUERYLEN];

	/*--- init ----------------------------------*/
	*mailstring	= (char)NULL;
	*query		= (char)NULL;

	if ( aDlnId == (int)_UNDEF )
	{
		/*---- Take all entries of one Booking ----*/
		(void)sprintf( query, _SEL_BID_AKT_NR, aAktionsTyp, aBuchungsId, aDlgId );
	}
	else
	{
		/*---- take only the entries of one booking and one pers_id ----*/
		(void)sprintf( query, _SEL_DLN_AKT_NR, aAktionsTyp, aBuchungsId, aDlnId, aDlgId );
	}

	status = MPAPIdb_sqlquery( (int)_AKT_DETAIL, (char **)&aktDet, query,
									  &anzAkt, &dataLen, &allocLen );

	if ( status == (int)MPOK )
	{
		/*---- We have found some akt_detail records ----*/
		if ( anzAkt > (int)0 )
		{
			/*---- There is an ActionNumber given as Parameter -----*/
			if ( flag == (int)MP_MATCHING )
			{
				TicketNr = LocalActionNumber;
			}
			else if ( ActionNumber != (int)_UNDEF && aktDet[0].akt_nr < (int)1 )
			{
				if ( LocalActionNumber == (int)_UNDEF )
				{
					LocalActionNumber = ActionNumber;
					TicketNr = LocalActionNumber;
				}
				else
				{
					LocalActionNumber++;
					TicketNr = LocalActionNumber;
				}
			}
			else if ( aktDet[0].akt_nr > (int)0 )
			{			
				/*--- we have already a ticketnumber; use it again */
				TicketNr = aktDet[0].akt_nr;
				LocalActionNumber = TicketNr;
			}
			else
			{
				/*---- search for a new action number ----*/
				TicketNr = MPAPIid_max((int)_AKT_DETAIL, (int)aktDet[0].a_typ_id, (char *)NULL)+1;
				LocalActionNumber = TicketNr;
			}

			/*---- Update akt_detail entries with the new actionnumber and exec_date ----*/
			for ( i = 0; i < anzAkt; i++ )
			{
				(void)time((time_t *)&aktDet[i].exec_dat); /* Ausfuehrungsdatum setzen */
				aktDet[i].z_flag = (int)_AKT_OK;
				aktDet[i].akt_nr = LocalActionNumber;

				status = MPAPIupdateEntry((int)_AKT_DETAIL, (char *)&aktDet[i], (BEZEICHNUNG *)NULL );
				if ( status != (int)MPOK )
				{
					sprintf(mailstring, "DBERR number %d in query%s%s", status, _P_EOL_, query );
					AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
				}
			}
		}
		else
		{
			/*-- we don't have any akt_detail entries -----*/
			TicketNr = (int)UNDEF;
			sprintf ( mailstring, "No entries of typ %d found for bid %d",
						aAktionsTyp, aBuchungsId  );
			AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);
		}
	}
	else
	{
		sprintf(mailstring, "DBERR number %d in query%s%s", status, _P_EOL_, query );
		AKTmsg( ACT_INFO, (int)_UNDEF, mailstring);

		TicketNr = (int)_UNDEF;
	}

	MPfree((void *)aktDet);
	
	return( TicketNr );
}


