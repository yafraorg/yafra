/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Kollektiv
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOLselect.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KOLselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   KOLLEKTIV *kol_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	size_t buffersize;
	char query[RECLAENGE];

	(void)strcpy(query, _SEL_BEZ_KOL);
	status=MPAPIdb_sqlquery((int)_KOLLEKTIV, &sqlmem.buffer, query,
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
			for (i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				kol_ptr = (KOLLEKTIV *)&sqlmem.buffer[i*sizeof(KOLLEKTIV)];
				(void)copyTextTo(tmp_buffer, (char *)kol_ptr->name, (int)_BEZLEN);
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

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose                                          
 *************************************************************/
int KOLchoose(int table, char *buffer)
{
	extern int sprache;
	extern KOLLEKTIV			kol;
	extern KOLLEKTIV_TYP		kolt;
	extern KOMMISSION			kom;

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	int	id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MKOL_BEZ:
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* KOLLEKTIV */
	if (MPAPIselectEntry(table, buffer, (char *)&kol, sizeof(kol),
					sizeof(kol.k_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* REISENDER  Verantwortlicher */
	id = DLNmkbez(kol.hauptpers, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KOLLEKTIV_TYP */
	id = MPAPIselectOneId((int)_KOLLEKTIV_TYP, (int)kol.k_typ_id, (char *)&kolt);
	if(id != (int)_UNDEF && SelectBez((int)_KOLLEKTIV_TYP, sprache, kolt.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(kol.textid, sprache, (int)_KOLLEKTIV, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Rechnungsempf�nger */
	id = KUNmkbez(kol.kid, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Buchungsstelle */
	id = KUNmkbez(kol.kbst, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kollektivreferenz */
	(void)copyTextTo(buffer1, (char *)kol.ref, (int)_CHAR30);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
