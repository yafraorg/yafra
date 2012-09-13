/*D***********************************************************
 * Modul:     DBI - database select
 *            message
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xMSGselect.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int MSGselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern int glob_typ_msg;

   MP_MSG *pMSG;
	int i;
	int intfield;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	if (glob_typ_msg != _UNDEF)
		(void)sprintf(query, _SEL_MSG, sprache, glob_typ_msg);
	else
		(void)sprintf(query, _SEL_MSG, sprache, (int)MSGTYP_MSG);

	status=MPAPIdb_sqlquery(_INTEGER, &sqlmem.buffer, query, anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0)
			{
			*len = (int)0;
			if (sqlmem.alloclen > comm.alloclen)
				{
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
	                    DEFMEMCHUNK, sqlmem.alloclen, sizeof(char));
				buffer = comm.buffer; /* da buffer nur ein -> auf comm.buffer ist */
				}
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				memcpy((void *)&intfield, (void *)&sqlmem.buffer[i*sizeof(int)], sizeof(int));
				sprintf(tmp_buffer, "%d\0", intfield);
				strcpy(buffer_ptr, tmp_buffer);
				buffer_ptr += strlen(tmp_buffer);
				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}
			}
		else /* Fehler: keine Daten gefunden */
			{
			*buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR])
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen(buffer);
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int MSGchoose(int table, char *buffer)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern BEZEICHNUNG	bez;
	extern SPRACHEN		spr;
	extern int glob_spr_bez;
	extern int glob_typ_msg;

	BEZEICHNUNG	tmpbez;
	MP_MSG *pMSG;
	char query[RECLAENGE];
	char	buffer1[4*RECLAENGE];
	char	message[RECLAENGE];
	char	record[RECLAENGE];
	int status = (int)MPOK;
	char  bezstring[_BEZLEN];
	int msgid;
	int msgtyp;
	int anzahl;
	int i;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen �berpr�fen */
	switch(FELDNR)
		{
		case MMSG_NR:
			strcpy(buffer1, buffer);
			break;
		case MMSG_TYP:
			glob_typ_msg = (int)MSGTYP_MSG;
			return(MPOK);
			break;
		case MMSG_SPR:
			glob_spr_bez = sprache;
			return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* MSG  Typ */
	if (glob_typ_msg == _UNDEF)
		msgtyp = (int)MSGTYP_MSG;
	else
		msgtyp = glob_typ_msg;
	(void)strcpy(buffer, "Meldungen");
	(void)strcat(buffer, "\t");

	/* MSG  Nummer */
	msgid = atoi(buffer1);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* SPRACHEN */
	if (glob_spr_bez < 1)
		glob_spr_bez = sprache;
	if (MPAPIselectOneId((int)_SPRACHEN, glob_spr_bez, (char *)&spr) != (int)_UNDEF)
		{
		if (SelectBez((int)_SPRACHEN, glob_spr_bez, spr.bez_id, bezstring) != (int)_UNDEF)
			(void)strcat(buffer, bezstring);
		else
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}
	else
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF   Msg Text */
	(void)sprintf(query, _SEL_MSGTXT, msgtyp, msgid, spr.s_id);
	status=MPAPIdb_sqlquery((int)_MSG, &sqlmem.buffer, query, &anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
		{
		if (anzahl > 0)
			{
			*buffer1=NULL;
			for(i=(int)0; i<anzahl; i++)
				{
				pMSG=(MP_MSG *)&sqlmem.buffer[i*sizeof(MP_MSG)];
				(void)copyTextTo(record, pMSG->text, _TEXTLEN);
				if (i == (int)0)
					(void)strcat(buffer, record);
				else
					{
					(void)strcat(buffer, "\n");
					(void)strcat(buffer, record);
					}
				}
			}
		(void)strcat(buffer, "\n");
		}
	else
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	COMMTYP = SELECTITEM;
	return(MPOK);
}
