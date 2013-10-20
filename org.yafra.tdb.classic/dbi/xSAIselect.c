/*D***********************************************************
 * Modul:     DBI - database select
 *            Saison
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/

#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSAIselect.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int SAIselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[STDMEMCHUNK];
	char query[STDMEMCHUNK];
	char message[STDMEMCHUNK];
	size_t buffersize;

	(void)sprintf(query, _SEL_BEZ_SAI, sprache, (int)_SAISON);

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
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
	return( status );
}

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int SAIchoose(int table, char *buffer)
{
	extern int sprache;
	extern SAISON	sai;

	struct tm DateTime;
	time_t date;
	char	bezeichnung[STDMEMCHUNK];
	char	buffer1[STDMEMCHUNK];
	char	message[STDMEMCHUNK];

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/*!! keine feldspezifischen Einschr�nkungen */

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* SAISON */
	if(MPAPIselectEntry(table, buffer, (char *)&sai, sizeof(sai),
						sizeof(sai.sai_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Saison CODE */
   (void)copyTextTo(bezeichnung, sai.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Saisonbeginn */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	date = (time_t)sai.von;
	(void)WriteDate(&DateTime, &date, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Saisonende */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	date = (time_t)sai.bis;
	(void)WriteDate(&DateTime, &date, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(sai.textid,sprache, (int)_SAISON, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
