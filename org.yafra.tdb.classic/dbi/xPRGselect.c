/*D***********************************************************
 * Modul:     DBI - database select
 *            Programm - abstrakte Definition eines Arrangements
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPRGselect.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int PRGselect(long *len , char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern SAISON globSAI;
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[_RECORDLEN];
	char query[_QUERYLEN];
	size_t buffersize;

	if ( globSAI.sai_id != (int)_UNDEF )
		(void)sprintf( query, _SEL_BEZ_PRG_SAI, sprache, (int)_PROGRAMM, globSAI.sai_id );
	else
		(void)sprintf( query, _SEL_BEZ_PRG, sprache, (int)_PROGRAMM );

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query, anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
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
			if ( MENUNR == NewLevel[MENUNR][FELDNR])
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
int PRGchoose(int table, char *buffer)
{
	extern int sprache;

	extern PROGRAMM	prg;
	extern SAISON		sai;

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	int	id;
	int   state;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	switch(FELDNR)
		{
		case (unsigned char)MPRG_BEZ:
			break;
		default:
			return(MPOK);
			break;
		}

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* PROGRAMM */
	state = MPAPIselectEntry(table, buffer, (char *)&prg, sizeof(prg), sizeof(prg.prg_id));
	if(state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  CODE */
   (void)copyTextTo(bezeichnung, prg.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	state = SelFromTxt(prg.textid, sprache, (int)_PROGRAMM, buffer1);
	if(state != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* SAISON */
	id = MPAPIselectOneId((int)_SAISON, (int)prg.sai_id, (char *)&sai);
	if(id != (int)_UNDEF && SelectBez((int)_SAISON, sprache, sai.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
