/*D***********************************************************
 * Modul:     DBI - database select
 *            Kontingent
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONHselect.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

#define MSG5	(int)197
#define MSG6	(int)291

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KONHselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern BUCHUNG bch;
	extern KUN_VIEW globBCHST;	/* Buchungsstelle */
	extern int sprache;
	extern int *NewLevel[];

   BEZEICHNUNG *bez_ptr;
   KOLLEKTIV kol;
   DIENST_ANGEBOT dla;
	int dla_id, dl_id, k_id, kid;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	size_t buffersize;

	switch(MENUNR)
		{
		default:
			if (globBCHST.kun_id != (int)_UNDEF)
				(void)sprintf(query, _SEL_BEZ_HKON_BST, sprache, (int)_HOST_KONT, globBCHST.kun_id );
			else
				(void)sprintf(query, _SEL_BEZ_HKON, sprache, (int)_HOST_KONT);
			break;
		}

	status = MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
	                        anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
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
			for (i=0, buffer_ptr = buffer; i < *anzahl; i++ )
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
			if (MENUNR == NewLevel[MENUNR][FELDNR])
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			else
				*buffer = NULL;
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
int KONHchoose(int table, char *buffer)
{
	extern int		sprache;
	extern HOST_KONT hkon;
	extern KUNDEN		kun;
	extern DIENST_ANGEBOT	dla;
	extern DIENSTLEISTUNG	dtg;
	extern STATUS_WERTE	sta;

	struct tm DateTime;
	char	bezeichnung[_RECORDLEN];
	char	buffer1[_RECORDLEN];
	int	id;
	int	status = (int)MPOK;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen */
	switch(FELDNR)
		{
		case MHKON_BEZ:
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* KONTINGENT */
	if (MPAPIselectEntry((int)_HOST_KONT, buffer, (char *)&hkon, sizeof(hkon),
	   sizeof(hkon.hostkont_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* KUNDEN  Ueberreicher / von Kunde */
	id = KUNmkbez(hkon.from_pers, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Buchungsstelle */
	id = KUNmkbez(hkon.kbst, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* DIENST_ANGEBOT */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, hkon.dla_id, (char *)&dla);
	if (id != (int)_UNDEF && SelectBez((int)_DIENST_ANGEBOT, sprache, dla.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DIENSTLEISTUNG */
	status = MPAPIselectDLbez(hkon.dl_id, sprache, bezeichnung, (int)_RECORDLEN);
	if (status == (int)MPOK)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	(void)strcat(buffer, "\t");
	(void)strcat(buffer, "\t");
	
	/* UNDEF  Options Verfalldatum */
	if (hkon.opt_dat != (int)0)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)WriteDate(&DateTime, (time_t *)&hkon.opt_dat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Referenz */
	(void)copyTextTo(bezeichnung, (char *)hkon.ref, (int)_BEZLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(hkon.textid, sprache, (int)_HOST_KONT, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
