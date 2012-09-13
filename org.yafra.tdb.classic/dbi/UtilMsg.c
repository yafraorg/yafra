/*D***********************************************************
 * Modul:     DBI - utilities
 *            put text for a message code
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilMsg.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";
static int UtilMsgReadDB(int, int, char *);


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
	extern char **sql_message;
	extern char **sys_message;
	extern int sql_maxmessage, sys_maxmessage;
	extern unsigned char logging_mp;

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
			if (abs(msgnr) < (sql_maxmessage+1))
				{
				if (sql_message[abs(msgnr)] != NULL)
					(void)strcpy(ptr, sql_message[abs(msgnr)]);
				else
					(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
				}
			else
				(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
			break;

		case MSGTYP_ERROR:
			if (msgnr < (int)0)  /*!!! zur kompatibilitaet bis alles umgestellt */
				{
				if (abs(msgnr) < (sql_maxmessage+1))
					{
					if (sql_message[abs(msgnr)] != NULL)
						(void)strcpy(ptr, sql_message[abs(msgnr)]);
					else
						(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
					}
				else
					(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
				}
			else
				{
				status = UtilMsgReadDB(msgnr, MSGTYP_ERROR, ptr);
				if (status != (int)MPOK)
					{
					FatalError = TRUE;
					(void)strcpy(ptr, sys_message[MPS_MSGERROR]);
					}
				}
			break;

		case MSGTYP_WARNING:
		case MSGTYP_INFO:
			status = UtilMsgReadDB(msgnr, msgtyp, ptr);
			if (status != (int)MPOK)
				{
				FatalError = TRUE;
				(void)strcpy(ptr, sys_message[MPS_MSGERROR]);
				}
			break;

		case MSGTYP_SYSTEM:
			if (msgnr < (sys_maxmessage+1))
				{
				if (sys_message[msgnr] != NULL)
					(void)strcpy(ptr, sys_message[msgnr]);
				else
					(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
				}
			else
				(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
			break;


		default:
			(void)sprintf(ptr, sys_message[MPS_NOMSG], msgnr, sprache, msgtyp);
			break;
		}

	/* log the message if required */
	if (logging_mp == (unsigned char)TRUE && msgtyp != MSGTYP_INFO &&
	    msgtyp != MSGTYP_WARNING)
		{
		sprintf(logstring, "error/msg ocurred with no %d and from typ %d", msgnr, msgtyp);
		MPlog(_LOGMP, MSGTYP_ERROR, logstring, __FILE__);
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




/************ OLD style MSG routines *****************************/

int find_text_nr(int nummer, char *text)
{
	UtilMsgGet(nummer, MSGTYP_ERROR, text);

	return((int)MPOK);
}

int xSqlMessage(char *message)
{
	UtilMsgWrite(message);

	return((int)MPOK);
}
