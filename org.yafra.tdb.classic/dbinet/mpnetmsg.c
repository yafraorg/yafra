/*D***********************************************************
 * Modul:     DBI - utilities
 *            put text for a message code
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/mpnetmsg.c,v 1.2 2008-11-02 19:55:51 mwn Exp $";
static int UtilMsgReadDB(int, int, char *);

#define MPWWW_NOMSG "Keine Meldung gefunden zu dieser Nummer"


/*F************************************************************
 * Function:  get a message and write it to the message buffer
 **************************************************************/
void UtilMsg(int msgnr, int msgtyp, char *additionaltext)
{
	static char message[4*RECLAENGE];

	/* get the message with no. */
	UtilMsgGet(msgnr, msgtyp, message);

	if (additionaltext != NULL)
		strcat(message, additionaltext);

	/* write the message to the message buffer */
	UtilMsgWrite(message);
}


/*F************************************************************
 * Function:  get a message
 **************************************************************/
void UtilMsgGet(int msgnr, int msgtyp, char *msg)
{
	extern int sprache;
	extern int FatalError;

	int status = (int)MPOK;
	char *ptr;
	char logstring[_RECORDLEN];

	/* set to msg buffer typ and nr for info */
	*msg = NULL;
	ptr = msg;
	if (msgtyp != MSGTYP_INFO)
		{
		sprintf(msg, "%d  -  %d\n\n\0", msgtyp, msgnr);
		ptr += strlen(msg);
		}

	/* checke Typ und setze Message */
	switch(msgtyp)
		{
		case MSGTYP_DBERROR:
		case MSGTYP_ERROR:
			if (msgnr < 0)
				msgtyp = MSGTYP_DBERROR;
			status = UtilMsgReadDB(abs(msgnr), msgtyp, ptr);
			if (status != (int)MPOK)
				{
				FatalError = TRUE;
				(void)strcpy(ptr, MPWWW_NOMSG);
				}
			break;

		case MSGTYP_SYSTEM:
		case MSGTYP_WARNING:
		case MSGTYP_INFO:
			status = UtilMsgReadDB(msgnr, msgtyp, ptr);
			if (status != (int)MPOK)
				{
				FatalError = TRUE;
				(void)strcpy(ptr, MPWWW_NOMSG);
				}
			break;

		default:
			(void)sprintf(ptr, "%s %d %d %d", MPWWW_NOMSG, msgnr, sprache, msgtyp);
			break;
		}
}


/*F************************************************************
 * Function:  write a message to the message buffer
 **************************************************************/
void UtilMsgWrite(char *msg)
{
	extern char messageBuffer[];

	/* write message into global message-buffer */
	(void)strcat(messageBuffer, msg);
	(void)strcat(messageBuffer, MSGTRENNER);
}

/*SF***********************************************************
 * Function:  get a message from the database
 * Parameter: msgnr  message number
 *            msgtyp typ of message (error, warning, ...)
 *            msg    buffer to copy the message in
 * Return:    db state
 **************************************************************/
static int UtilMsgReadDB(int msgnr, int msgtyp, char *msg)
{
	extern int sprache;
	extern MEMOBJ msgmem;

	MP_MSG *pMSG;
	char query[RECLAENGE];
	char	buffer1[4*RECLAENGE];
	char	record[RECLAENGE];
	int status = (int)MPOK;
	int anzahl;
	int i;

	(void)sprintf(query, _SEL_MSGTXT, msgtyp, msgnr, sprache);
	status=MPAPIdb_sqlquery((int)_MSG, &msgmem.buffer, query, &anzahl,
	                         &msgmem.datalen, &msgmem.alloclen);
	if (status == (int)MPOK)
		{
		if (anzahl > 0)
			{
			*buffer1=NULL;
			for(i=(int)0; i<anzahl; i++)
				{
				pMSG=(MP_MSG *)&msgmem.buffer[i*sizeof(MP_MSG)];
				(void)copyTextTo(record, pMSG->text, _TEXTLEN);
				(void)strcat(msg, record);
				if (msgtyp != MSGTYP_INFO)
					(void)strcat(msg, "\n");
				}
			}
		}

	return(status);
}
