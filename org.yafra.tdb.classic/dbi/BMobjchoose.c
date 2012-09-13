/*D***********************************************************
 * Modul:     DBI - booking modul
 *            send DL choice (only if more than one)
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMobjchoose.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

int BMobjChoose(int len, char *buffer)
{
	extern BUCHUNG bch;
	extern REISENDER rei;
	extern DIENSTLEISTUNG dtg;
	extern unsigned char bm_obj;

	char message[_RECORDLEN];
	int status = MPOK;
	int anzahl;
	long dlbufferlen;
	unsigned char oldmenunr;

	switch(ACTIONTYP)
		{
		case (unsigned char)INSERT:
			if (bm_obj == (unsigned char)_DIENSTLEISTUNG)
				{
				if (dtg.dlg_id != (int)_UNDEF)
					status = BMRESsend(len, comm.buffer);
				else
					{
					oldmenunr = MENUNR;
					MENUNR = _BMDLN;
					status = DLselect(&dlbufferlen, comm.buffer, &anzahl);
					MENUNR = oldmenunr;
					if (status != (int)MPOK)
						return(status);

					if (anzahl == 1)
						status = BMRESsend(len, comm.buffer);
					else
						COMMTYP = (unsigned char)BMOBJCHOOSE;
					}
				}
			else
				{
				oldmenunr = MENUNR;
				MENUNR = _RESERVATION;
				status = DLselect(&dlbufferlen, comm.buffer, &anzahl);
				MENUNR = oldmenunr;
				if (status != (int)MPOK)
					return(status);

				if (anzahl == 1)
					status = BMRESsend(len, comm.buffer);
				else
					COMMTYP = (unsigned char)BMOBJCHOOSE;
				}
			break;

		case (unsigned char)UPDATE:
			/* get all DL's currently booked or in current ARR */
			/* bch.bid and rei.uid must be set correctly       */
			oldmenunr = MENUNR;
			if (bm_obj == (unsigned char)_DIENSTLEISTUNG)
				{
				/* check up if we need to insert or to modify DL's */
				/* TRUE is update  FALSE is insert */
				UtilMsgGet((int)MPW_DLINSORUPD, MSGTYP_WARNING, message);
				status = UtilImmediatCall(message);
				if (status == (int)TRUE)
					MENUNR = (unsigned char)_RESERVATION;
				else
					{
					ACTIONTYP = (unsigned char)INSERT;
					MENUNR = (unsigned char)_BMDLN;
					}
				}
			else
				MENUNR = (unsigned char)_RESERVATION;

			status = DLselect(&dlbufferlen, comm.buffer, &anzahl);
			MENUNR = oldmenunr;
			if (status != (int)MPOK)
				return(status);
			if (anzahl == 1)
				status = BMRESsend(len, comm.buffer);
			else if (anzahl > 1)
				COMMTYP = (unsigned char)BMOBJCHOOSE;
			break;

		case (unsigned char)MPDELETE:
			oldmenunr = MENUNR;
			MENUNR = (unsigned char)_RESERVATION;
			status = DLselect(&dlbufferlen, comm.buffer, &anzahl);
			MENUNR = oldmenunr;
			if (status != (int)MPOK)
				return(status);
			if (anzahl == 1)
				status = BMRESsend(len, comm.buffer);
			else
				COMMTYP = (unsigned char)BMOBJCHOOSE;
			break;
		}

	return(status);
}
