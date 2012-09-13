/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Kostenart
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKARselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KARselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern char sqlquery[];
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[_RECORDLEN];
	size_t buffersize;

	(void)sprintf(sqlquery, _SEL_BEZ_KAR, sprache, (int)_KOSTEN_ART);
	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery,
	                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
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
			for (i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				bez_ptr = (BEZEICHNUNG *)&sqlmem.buffer[i*sizeof(BEZEICHNUNG)];
				(void)copyTextTo(tmp_buffer, (char *)bez_ptr->bez, (int)_BEZLEN);
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
int KARchoose(int table, char *buffer)
{
	extern int sprache;
	extern KOSTEN_ART		kar;

	char buffer1[_RECORDLEN];
	char dbbuffer[_RECORDLEN];

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/*!! keine feldspezifischen Einschr�nkungen */

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* KOSTEN_ART */
	strcpy(dbbuffer, buffer);
	(void)ConvertSpecialChar(dbbuffer, NULL);
	if (MPAPIselectEntry(table, dbbuffer, (char *)&kar, sizeof(kar),
						sizeof(kar.kar_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(kar.textid, sprache, (int)_KOSTEN_ART, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
