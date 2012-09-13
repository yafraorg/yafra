/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Sprache
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSPRselect.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int SPRselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

	SPR_VIEW *sprptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	switch (MENUNR)
		{
		case (unsigned char)_BEZEICHNUNG:
		case (unsigned char)_TEXTE:
		case (unsigned char)_LABEL:
		case (unsigned char)_MSG:
		case (unsigned char)_HELP:
		case (unsigned char)_GLOBALMENU:
			(void)sprintf(query, _SEL_BEZ_SPRDIALOG, sprache);
			break;
		default:
			(void)sprintf(query, _SEL_BEZ_SPR, sprache);
			break;
		}

	status=MPAPIdb_sqlquery((int)_SPR_VIEW, &sqlmem.buffer, query,
	                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
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
				sprptr = (SPR_VIEW *)&sqlmem.buffer[i*sizeof(SPR_VIEW)];
				(void)copyTextTo(tmp_buffer, (char *)sprptr->bez, (int)_BEZLEN);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;
				(void)memset((void *)buffer_ptr, '\n', sizeof(char));
				buffer_ptr++;
				(void)memset((void *)buffer_ptr, NULL, sizeof(char));
				}
			}
		else
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

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose                                          
 *************************************************************/
int SPRchoose(int table, char *buffer)
{
	extern SPRACHEN spr;

	char	message[_RECORDLEN];

	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MSPR_BEZ:
			break;
		default:
			return((int)MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* SPRACHEN */
	if (MPAPIselectEntry(table, buffer, (char *)&spr, sizeof(spr),
	                sizeof(spr.s_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* _UNDEF  Dialogflag */
	if (spr.dialog == (int)TRUE)
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
	else
		UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
	(void)strcat(buffer, message);
	(void)strcat(buffer, "\t");

	/* _UNDEF  NLS system bezeichnung */
	(void)copyTextTo(message, spr.sysbez, (int)_CHAR20);
	(void)strcat(buffer, message);
	(void)strcat(buffer, "\t");

	/* _UNDEF  Outputflag */
	if (spr.output == (int)TRUE)
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
	else
		UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
	(void)strcat(buffer, message);
	(void)strcat(buffer, "\t");

	/* _UNDEF  To 2000 GUI Flag */
	if (spr.gui == (int)TRUE)
		UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
	else
		UtilMsgGet((int)MPI_NO_FALSE, MSGTYP_INFO, message);
	(void)strcat(buffer, message);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
