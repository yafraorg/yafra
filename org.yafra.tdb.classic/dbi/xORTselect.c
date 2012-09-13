/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Ort
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xORTselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int ORTselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern ORT ort;
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

	(void)sprintf(query, _SEL_BEZ_ORT, sprache, (int)_ORT);
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
int ORTchoose(int table, char *buffer)
{
	extern int	sprache;
	extern ORT  ort;
	extern LAND land;
	extern STATUS_WERTE		sta;
	extern char glob_bez_ort[];
	extern char glob_bez_land[];

	char bez[_BEZLEN];
   char	bezeichnung[_BEZLEN];
	char buffer1[RECLAENGE];
	char buffer2[RECLAENGE];
	char message[RECLAENGE];
	unsigned char paraset = FALSE;
	int id, state;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MORT_BEZ:
			(void)strcpy(glob_bez_ort, buffer);
			break;
		case MORT_LAND:
			(void)strcpy(glob_bez_land, buffer);
			return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* ORT */
	if (MPAPIselectEntry(table, buffer, (char *)&ort, sizeof(ort),
		 sizeof(ort.ort_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* LAND  Zugeh�rigkeit */
	id = MPAPIselectOneId((int)_LAND, (int)ort.land_id, (char *)&land);
	if (id != (int)_UNDEF)
		{
		id = SelectBez((int)_LAND, sprache, land.bez_id, buffer1);
		if (id != (int)_UNDEF)
			(void)strcat(buffer, buffer1);
		}
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Orttyp */
	sta.typ = (int)_STA_ORT;
	id = MPAPIselectOneId((int)_STATUS_WERTE, ort.ort_typ, (char *)&sta);
	state=SelectBez((int)_STA_ORT, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF     K�rzel */
	(void)strcat(buffer, ort.krzl);
	(void)strcat(buffer, "\t");

	/* UNDEF  Zeitverschiebung */
	(void)sprintf(buffer1, "%d", ort.zeitver);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Koordinate 1 */
	(void)sprintf(buffer1, "%d", ort.koord1);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Koordinate 2 */
	(void)sprintf(buffer1, "%d", ort.koord2);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(ort.textid, sprache, (int)_ORT, buffer1);
	if (id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
