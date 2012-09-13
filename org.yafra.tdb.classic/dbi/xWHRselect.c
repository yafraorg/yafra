/*D***********************************************************
 * Modul:     DBI - database select                           
 *            W�hrung
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xWHRselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int WHRselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern WAEHRUNG whr;
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bezptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	(void)sprintf(query, _SEL_BEZ_WHR, sprache, (int)_WAEHRUNG);
	status=MPAPIdb_sqlquery(_BEZEICHNUNG, &sqlmem.buffer, query,
	                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
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
				bezptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, bezptr->bez, _BEZLEN);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
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

	*len = (int)strlen(buffer);
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return(status);
}


/*F***********************************************************
 * Function:  Choose                                         
 *************************************************************/
int WHRchoose(int table, char *buffer)
{
	extern int      sprache;
	extern WAEHRUNG whr;
	extern char     glob_bez_whr[];

	char buffer1[RECLAENGE];
	unsigned char paraset = FALSE;
	int id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MWHR_BEZ:
			(void)strcpy(glob_bez_whr, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* WAEHRUNG */
	if (MPAPIselectEntry(table, buffer, (char *)&whr, sizeof(whr),
		 sizeof(whr.whr_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Status */
	(void)strcat(buffer, "\t");

	/* UNDEF     K�rzel */
	(void)strcat(buffer, whr.krzl);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(whr.textid, sprache, (int)_WAEHRUNG, buffer1);
	if (id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
