/*D***********************************************************
 * Modul:     DBI - database select                           
 *            DLAT - ANGEBOTS_TYP
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xDLATselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $

 Log Information:
 $Log: xDLATselect.c,v $
 Revision 1.2  2008-11-02 19:55:37  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:35:01  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:34:34  16:34:34  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  93/09/08  15:10:31  15:10:31  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLATselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int DLATselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	(void)sprintf(query, _SEL_BEZ_DLAT, sprache, (int)_ANGEBOTS_TYP);

	status=MPAPIdb_sqlquery( (int)_BEZEICHNUNG, &sqlmem.buffer, query,
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
				bez_ptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, (char *)bez_ptr->bez, (int)_CHAR30);
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
		UtilMsg(status, MSGTYP_ERROR, NULL);
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
int DLATchoose(int table, char *buffer)
{
	extern int sprache;
	extern ANGEBOTS_TYP dlat;

	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	int   id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/*!! keine feldspezifischen Einschr�nkungen */

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* ANGEBOTS_TYP */
	if (MPAPIselectEntry(table, buffer, (char *)&dlat, sizeof(dlat),
		 sizeof(dlat.art_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(dlat.textid,sprache, (int)_ANGEBOTS_TYP, buffer1);
	if (id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
