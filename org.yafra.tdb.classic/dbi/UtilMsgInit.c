/*D***********************************************************
 * Modul:     DBI - msg init
 *            read all entries of table MSG
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilMsgInit.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int UtilMsgInit(void)
{
	extern char **sql_message;
	extern char **sys_message;
	extern int sys_maxmessage;
	extern int sql_maxmessage;
	extern int sprache;
	extern int FatalError;
	extern MEMOBJ sqlmem;
	extern unsigned char logging_mp;
	extern MEMOBJ msgmem;

	MP_MSG *msgptr;
	MP_MSG *nextmsgptr;

	MEMOBJ work;
	MEMOBJ record;
	char query[_QUERYLEN];
	char log[_RECORDLEN];
	int laenge, i;
	int status=(int)MPOK;
	int anzahl, msgid, nextid, msgtyp;
	int lastmsg = FALSE;
	unsigned long alloclen = 0;

	/* init */
	msgmem.buffer = NULL;
	msgmem.alloclen = 0;
	msgmem.datalen = 0;

	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	sql_maxmessage=MPAPIid_max(_MSG, MSGTYP_DBERROR, NULL);
	sys_maxmessage=MPAPIid_max(_MSG, MSGTYP_SYSTEM, NULL);
	(void)MPAPIdb_committrx();

	if (logging_mp)
		{
		(void)sprintf(log, "read into memory %d SQL messages", sql_maxmessage);
		MPlog(_LOGMP, MSGTYP_MSG, log, __FILE__);
		(void)sprintf(log, "read into memory %d system messages", sys_maxmessage);
		MPlog(_LOGMP, MSGTYP_MSG, log, __FILE__);
		}

	/* Alloc der Anzahl Meldungen */
	alloclen = 0;
	sql_message=(char **)MPalloc((void *)sql_message, &alloclen, 1,
	               (sql_maxmessage+1), sizeof(char *));
	if (sql_message == NULL)
		{
		UtilMsgWrite("fatal error - no internal memory for messages !");
		FatalError = TRUE;
		return((int)MPERROR);
		}
	for (i=0; i<(sql_maxmessage+1); i++)
		sql_message[i] = NULL;
	alloclen = 0;
	sys_message=(char **)MPalloc((void *)sys_message, &alloclen, 1,
	               (sys_maxmessage+1), sizeof(char *));
	if (sys_message == NULL)
		{
		UtilMsgWrite("fatal error - no internal memory for messages !");
		FatalError = TRUE;
		return((int)MPERROR);
		}
	for (i=0; i<(sys_maxmessage+1); i++)
		sys_message[i] = NULL;

	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	(void)sprintf(query, _SEL_ALL_MEMORYMSG, sprache, (int)MSGTYP_DBERROR, (int)MSGTYP_SYSTEM);
	status=MPAPIdb_sqlquery((int)_MSG, &sqlmem.buffer, query, &anzahl,
          &sqlmem.datalen, &sqlmem.alloclen);
	(void)MPAPIdb_committrx();

	if (status != (int)MPOK)
		{
		if (logging_mp)
			MPlog(_LOGMP, MSGTYP_ERROR, "Fehler beim MSG select query in", __FILE__);
		UtilMsgWrite("fatal error - read error messages from DB !");
		FatalError = TRUE;
		return((int)MPERROR);
		}
	else if (anzahl == (int)0)
		{
		if (logging_mp)
			MPlog(_LOGMP, MSGTYP_ERROR, "MSG Anzahl ist Null", __FILE__);
		UtilMsgWrite("fatal error - no internal messages found in DB !");
		FatalError = TRUE;
		return((int)MPERROR);
		}
	else
		{
		record.datalen = sizeof(msgptr->text);
		record.alloclen = 0;
		record.buffer = NULL;
		record.buffer = (char *)MPalloc((void *)record.buffer, &record.alloclen,
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
				(void)strcat(work.buffer, "\n");
				(void)strcat(work.buffer, record.buffer);
				}
			else  /* Gruppenwechsel */
				{
				laenge=strlen(work.buffer);
				if (msgtyp == MSGTYP_DBERROR) /* SQL_Fehlermeldung */
					{
					alloclen = 0;
					sql_message[abs(msgid)]=(char *)MPalloc((void *)sql_message[abs(msgid)],
					      &alloclen, 1, (laenge+1), sizeof(char));
					if (sql_message[abs(msgid)] == NULL)
						return(MPE_ALLOC);
					(void)strcpy(sql_message[abs(msgid)], work.buffer);
					}
				else if (msgtyp == MSGTYP_SYSTEM) /* PRG-Fehlermeldung */
					{
					alloclen = 0;
					sys_message[msgid]=(char *)MPalloc((void *)sys_message[msgid],
					      &alloclen, 1, (laenge+1), sizeof(char));
					if (sys_message[msgid] == NULL)
						return(MPE_ALLOC);
					(void)strcpy(sys_message[msgid], work.buffer);
					}
				else /* weder noch -> Datenbestand Fehler */
					UtilMsgWrite("fatal error - wrong message typ !");

				/* Falls nur 1 Record, verlasse Schleife */
				if (lastmsg == TRUE)
					break;

				/* n�chste MSG kopieren */
				(void)strcpy(work.buffer, record.buffer);
				}
			}
		free((void *)record.buffer);
		free((void *)work.buffer);
		}

	return(status);
}
