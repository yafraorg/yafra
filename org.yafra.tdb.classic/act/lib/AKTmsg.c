/*D***********************************************************
 * Modul:     AKT base moduls
 *            manage action error messages
 *            also handle the database interface messages
 *            the db interface (ex. functions.sql) calls UtilMsgWrite
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTmsg.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";

/* MarcoPolo API includes */
#include <mpact.h>         /* default include  */

#define _SEL_ALL_AKTMSG "SELECT * FROM TDBADMIN.MSG \
	WHERE S_ID = %d AND MSG_TYP = %d \
	ORDER BY MSG_TYP, MSG_ID, TEXTNR;"

/*F************************************************************
 * Function:  initialize messages
 *            Alloc memory for max messages 
 *            Query the action messages for dialoglangage
 *            for all messages process ?....
 *
 *
 **************************************************************/
int AKTmsginit(void)
{
	extern char **akt_message;
	extern int akt_maxmessage;
	extern int dialogsprache;
	extern int FatalError;
	extern int DebugFlag;
	extern MEMOBJ sqlmem;
	extern unsigned char logging_mp;
	extern MEMOBJ msgmem;
	extern FILE *FPout;

	MP_MSG *msgptr;
	MP_MSG *nextmsgptr;

	MEMOBJ work;
	MEMOBJ record;
	char query[RECLAENGE];
	char log[RECLAENGE];
	int laenge, i;
	int status=(int)MPOK;
	int anzahl, msgid, nextid, msgtyp;
	int lastmsg = FALSE;
	int alloclen = 0;

	/* init */
	msgmem.buffer = NULL;
	msgmem.alloclen = 0;
	msgmem.datalen = 0;
	
	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	akt_maxmessage=MPAPIid_max(_MSG, MSGTYP_ACTION, NULL);
	(void)MPAPIdb_committrx();

	/* Alloc der Anzahl Meldungen */
	alloclen = 0;
	akt_message=(char **)MPalloc((void *)akt_message, (unsigned long *)&alloclen, 1,
	               (akt_maxmessage+1), sizeof(char *));
	if (akt_message == NULL)
		return((int)MPERROR);
	for (i=0; i<(akt_maxmessage+1); i++)
		akt_message[i] = NULL;

	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	(void)sprintf(query, _SEL_ALL_AKTMSG, dialogsprache, MSGTYP_ACTION);
	status=MPAPIdb_sqlquery((int)_MSG, &sqlmem.buffer, query, &anzahl,
          &sqlmem.datalen, &sqlmem.alloclen);
	(void)MPAPIdb_committrx();

	if (status != (int)MPOK || anzahl < 1)
		return((int)MPERROR);
	else
		{
		record.datalen = sizeof(msgptr->text);
		record.alloclen = 0;
		record.buffer = NULL;
		record.buffer = (char *)MPalloc((void *)record.buffer,&record.alloclen,
			                         STARTMEMCHUNK, record.datalen, sizeof(char));

		work.datalen = sizeof(msgptr->text);
		work.alloclen = 0;
		work.buffer = NULL;
		work.buffer = (char *)MPalloc((void *)work.buffer, &work.alloclen,
			                         STARTMEMCHUNK, work.datalen, sizeof(char));

		(void)copyTextTo(work.buffer, ((MP_MSG *)sqlmem.buffer)->text, _CHAR80);
		for(i=0; i<anzahl; i++)
			{
			msgptr=(MP_MSG *)&sqlmem.buffer[i*sizeof(MP_MSG)];
			msgid  = msgptr->msg_id;
			msgtyp = msgptr->msg_typ;
			if (i == (anzahl - 1))
				{
				nextmsgptr  = NULL;
				nextid  = UNDEF;
				lastmsg = TRUE;
				}
			else
				{
				nextmsgptr  =(MP_MSG *)&sqlmem.buffer[(i+1)*sizeof(MP_MSG)];
				nextid  = nextmsgptr->msg_id;
				(void)copyTextTo(record.buffer, nextmsgptr->text, _CHAR80);
				}

			if (lastmsg != TRUE && nextid == msgid) /* innerhalb gleicher Gruppe */
				{
				if ((strlen(record.buffer) + strlen(work.buffer)) > work.alloclen)
					work.buffer = (char *)MPalloc((void *)work.buffer, &work.alloclen,
			                    STARTMEMCHUNK, (strlen(record.buffer) + strlen(work.buffer)), sizeof(char));
				(void)strcat(work.buffer, _P_EOL_ );
				(void)strcat(work.buffer, record.buffer);
				}
			else  /* Gruppenwechsel */
				{
				laenge=strlen(work.buffer);
				if (msgtyp == MSGTYP_ACTION) /* Aktions Fehlermeldung */
					{
					alloclen = 0;
					akt_message[abs(msgid)]=(char *)MPalloc((void *)akt_message[abs(msgid)],
					      (unsigned long *)&alloclen, 1, (laenge+1), sizeof(char));
					if (akt_message[abs(msgid)] == NULL)
						return(MPERROR);
					(void)strcpy(akt_message[abs(msgid)], work.buffer);
					}
				else /* weder noch -> Datenbestand Fehler */
					fprintf(stderr, "fatal error - wrong message typ !");

				/* Falls nur 1 Record, verlasse Schleife */
				if (lastmsg == TRUE)
					break;

				/* n�chste MP_MSG kopieren */
				(void)strcpy(work.buffer, record.buffer);
				}
			}
		free((void *)record.buffer);
		free((void *)work.buffer);
		}

/*DEBUG*****************/
	if (DebugFlag)
		printf("%sdebug: read all messages into memory with code %d %s", _P_EOL_, status, _P_EOL_ );
/*DEBUG*****************/

	return(status);
}


/*F************************************************************
 * Function:  get a message
 **************************************************************/
void AKTmsgget(int msgnr, char *msg)
{
	extern int FatalError;
	extern char **akt_message;
	extern int akt_maxmessage;

	if (msg == NULL)
		return;

	if (msgnr < (akt_maxmessage+1))
		{
		if (akt_message[msgnr] != NULL)
			(void)strcpy(msg, akt_message[msgnr]);
		else
			(void)strcpy(msg, "Fatal error in making message");
		}
	else
		(void)strcpy(msg, "Fatal error in making message");
}


/*F************************************************************
 * Function:  free message buffer memory
 **************************************************************/
int AKTmsgfree(void)
{
	extern char **akt_message;
	extern int akt_maxmessage;
	extern MEMOBJ msgmem;

	int i;
	int status = MPOK;

	MPfree((void *)msgmem.buffer);
	msgmem.datalen = msgmem.alloclen = 0;

	if (akt_message != NULL && akt_maxmessage > 0)
		{
		for (i=0; i<(akt_maxmessage+1); i++)
			MPfree((void *)akt_message[i]);
		MPfree((void *)akt_message);
		akt_maxmessage = 0;
		}
	else
		status = MPERROR;

	return(status);
}


/*F************************************************************
 * Function:  general message interface
 **************************************************************/
void AKTmsg(int typ, int msgid, char *text)
{
	char tmpbuf[_RECORDLEN];

	if (msgid > (int)_UNDEF)
		{
		AKTmsgget(msgid, tmpbuf);
		AKTmsghandler(typ, tmpbuf);
		}
	else if (text != NULL)
		AKTmsghandler(typ, text);
	else
		return;
}


/*F************************************************************
 * Function:  general handling modul for AKTIONEN messages
 **************************************************************/
void AKTmsghandler(int typ, char *text)
{
	extern FILE *FPmail;
	extern int DebugFlag;

	char tmpbuf[_RECORDLEN];
	char tmpdebug[_RECORDLEN];

	if (text == NULL)
		return;

	switch(typ)
		{
		case ACT_OSERROR:
			(void)MailAdd(FPmail, _P_EOL_ );
			AKTmsgget(MPA_OSERRORHEADER, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			(void)MailAdd(FPmail, _P_EOL_ );

			(void)MailAdd(FPmail, text);
			(void)MailAdd(FPmail, _P_EOL_ );

/*DEBUG*****************/
			if (DebugFlag)
				{
				sprintf(tmpdebug, "%sdebug: OSERROR - %s", _P_EOL_, text);
				perror(tmpdebug);
				}
/*DEBUG*****************/

			AKTmsgget(MPA_SUPPORT, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			break;

		case ACT_SQLERROR:
			(void)MailAdd(FPmail, _P_EOL_ );
			AKTmsgget(MPA_SQLERRORHEADER, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			(void)MailAdd(FPmail, _P_EOL_);

			(void)MailAdd(FPmail, text);
			(void)MailAdd(FPmail, _P_EOL_ );

/*DEBUG*****************/
			if (DebugFlag)
				fprintf(stderr, "%sdebug: SQLERROR - %s", _P_EOL_, text);
/*DEBUG*****************/

			AKTmsgget(MPA_SUPPORT, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			break;

		case ACT_WARNING:
		case ACT_ERROR:
			(void)MailAdd(FPmail, _P_EOL_ );
			AKTmsgget(MPA_ERRORHEADER, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			(void)MailAdd(FPmail, _P_EOL_ );

			(void)MailAdd(FPmail, text);
			(void)MailAdd(FPmail, _P_EOL_ );

/*DEBUG*****************/
			if (DebugFlag)
				fprintf(stderr, "%sdebug: MPERROR - %s", _P_EOL_, text);
/*DEBUG*****************/

			AKTmsgget(MPA_SUPPORT, tmpbuf);
			(void)MailAdd(FPmail, tmpbuf);
			break;

		case ACT_INFO:
			(void)MailAdd(FPmail, text);
			break;

		default:
			break;
		}
}

/* keep this function for the database interface (ex. functions.sql) */
/* I can not use the same as in the daemon, because in the actions */
/* it's a little diffrent management of messages than in the daemon */

/*F************************************************************
 * Function:  write a db interface message
 **************************************************************/
void UtilMsgWrite(char *msg)
{
	AKTmsghandler(ACT_SQLERROR, msg);
	return;
}
