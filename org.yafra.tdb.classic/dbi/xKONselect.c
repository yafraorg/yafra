/*D***********************************************************
 * Modul:     DBI - database select
 *            Kontingent
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKONselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define MSG5	(int)197
#define MSG6	(int)291

static int buildSQLquery(int, RESERVATION *);

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KONselect(long *len, char *buffer, int *anzahl)
{
	extern int sprache;
	extern MEMOBJ sqlmem;
	extern int *NewLevel[];
	extern char sqlquery[];

	int *tdlids;
	int tdlcnt;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	size_t buffersize;
	BEZEICHNUNG *bez_ptr;
	RESERVATION tmpres;
	PERSONEN rechst;

	switch(MENUNR)
		{
		case (unsigned char)_RESERVATION:
			/* read menu string and set it to RES */
			tdlids = NULL;
			tdlcnt = 0;
			status = BMRESreadprotocol(buffer, &tmpres, &tdlids, &tdlcnt);
			if (status != (int)MPOK)
				{
				UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
				return(status);
				}
			status = MPAPIselectRECHST(tmpres.bid, &rechst);
			status = buildSQLquery(rechst.pers_id, &tmpres);
			break;

		default:
			(void)sprintf(sqlquery, _SEL_BEZ_KON, sprache, (int)_KONTINGENT);
			break;
		}

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery,
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
			if (MENUNR == (unsigned char)_RESERVATION)
				{
				UtilMsg((int)MSG6, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			else if (MENUNR == NewLevel[MENUNR][FELDNR] )
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
int KONchoose(int table, char *buffer)
{
	extern int				sprache;
	extern KONTINGENT		kon;
	extern HOST_KONT  	hkon;
	extern KUNDEN			kun;
	extern STATUS_WERTE	sta;

	struct tm	DateTime;
	char			bezeichnung[RECLAENGE];
	char			buffer1[RECLAENGE];
	int			id;
	int			status = (int)MPOK;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen */
	switch(FELDNR)
		{
		case MKON_BEZ:
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
	if (MPAPIselectEntry((int)_KONTINGENT, buffer, (char *)&kon, sizeof(kon), sizeof(kon.kont_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* HOST_KONT */
	id = MPAPIselectOneId((int)_HOST_KONT, kon.hostkont_id, (char *)&hkon);
	if (id != (int)_UNDEF && SelectBez((int)_HOST_KONT, sprache, hkon.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Weitergabe an Kunde */
	id = KUNmkbez(kon.kunden_id, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");
	
	/* UNDEF  Options Verfalldatum */
	if (kon.opt_dat != (int)0)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		(void)WriteDate(&DateTime, (time_t *)&kon.opt_dat, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Referenz */
	(void)copyTextTo(bezeichnung, (char *)kon.ref, (int)_BEZLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(kon.textid, sprache, (int)_KONTINGENT, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}

static int buildSQLquery(int rechst_id, RESERVATION *Ares)
{
	extern char sqlquery[];
	extern DIENST_ANGEBOT dla;
	extern int sprache;

	int status = (int)MPOK;
	DIENST_TRAEGER tmpdlt;

	status = MPAPIselectDLT((int)_UNDEF, (int)_UNDEF, Ares->dlg_id, &tmpdlt);		

	if (rechst_id != (int)_UNDEF)
		(void)sprintf(sqlquery, _SEL_BEZ_KON_DL_KUN, Ares->dlg_id, dla.dla_id,
		              rechst_id, sprache, (int)_KONTINGENT);
	else
		(void)sprintf(sqlquery, _SEL_BEZ_KON_DL, Ares->dlg_id, dla.dla_id,
		              sprache, (int)_KONTINGENT);

	return(status);
}
