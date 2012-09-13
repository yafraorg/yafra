/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Kommission
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKOMselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

static int KOMDETchoose(char *);

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int KOMselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char glob_typ_kom[];
	extern char sqlquery[];

   BEZEICHNUNG *bez_ptr;
	BEZEICHNUNG tmpbez;
	int i;
	int id;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	size_t buffersize;

	/* init of sqlquery string */
	sqlquery[0] = NULL;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	switch (MENUNR)
		{
		case (unsigned char)_KOMMISSION:
			if (*glob_typ_kom != NULL)
				{
				tmpbez.typ = (int)_NAMEN;
				tmpbez.s_id = sprache;
				(void)copyTextTo(tmpbez.bez, glob_typ_kom, (int)_CHAR30);
				id = MPAPIselectEntry((int)_BEZEICHNUNG, glob_typ_kom,
	   		   (char *)&tmpbez, sizeof(BEZEICHNUNG), sizeof(tmpbez.bez_id));
				if (id == (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_BEZ_KOM, sprache, (int)_KOMMISSION);
				else
					(void)sprintf(sqlquery, _SEL_BEZ_KOM_TYP, tmpbez.typ, sprache, (int)_KOMMISSION);
				}
			else
				(void)sprintf(sqlquery, _SEL_BEZ_KOM, sprache, (int)_KOMMISSION);
			break;

		case (unsigned char)_KOMM_DETAIL:
			if (*to_buffers[MKOMD_BCH] != NULL || *to_buffers[MKOMD_DLN] != NULL)
				(void)sprintf(sqlquery, _SEL_BEZ_KOM_KOMTYP, _KOMM_DLN, 
				              sprache, (int)_KOMMISSION);
			else if (*to_buffers[MKOMD_KOL] != NULL)
				(void)sprintf(sqlquery, _SEL_BEZ_KOM_KOMTYP, _KOMM_KOLLEKTIV, 
				              sprache, (int)_KOMMISSION);
			else if (*to_buffers[MKOMD_KUN] != NULL)
				(void)sprintf(sqlquery, _SEL_BEZ_KOM_KOMTYP, _KOMM_KUNDE, 
				              sprache, (int)_KOMMISSION);
			else
				(void)sprintf(sqlquery, _SEL_BEZ_KOM, sprache, (int)_KOMMISSION);
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	/* free up menu buffers */
	UtilSplitFreeMenubuffer(to_buffers);

	/* check status */
	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		(void)sprintf(sqlquery, _SEL_BEZ_KOM, sprache, (int)_KOMMISSION);

	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery,
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
int KOMchoose(int table, char *buffer)
{
	extern int sprache;
	extern KOMMISSION			kom;
	extern BEZEICHNUNG		bez;
	extern STATUS_WERTE		sta;
	extern KOSTEN_ART			kar;
	extern TRAEGER_TYP      dltt;
	extern KATEGORIE			kat;
	extern REISENDER_TYP		reit;
	extern DIENST_ANGEBOT	dla;
	extern BUCHUNG				bch;
	extern char glob_bez_kom[];
	extern char glob_typ_kom[];
	extern char glob_kar_kom[];
	extern char glob_satztyp_kom[];
	extern char glob_satz_kom[];

	BEZEICHNUNG					tmpbez;
	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[_RECORDLEN];
	char	message[RECLAENGE];
	char dbbuffer[RECLAENGE];
	char satzstring[_RECORDLEN];
	int	id, state;
	int   status = MPOK;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MKOM_BEZ:
			(void)strcpy(glob_bez_kom, buffer);
			break;
		case MKOM_TYP:
			(void)strcpy(glob_typ_kom, buffer);
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

	/* KOMMISSION */
	strcpy(dbbuffer, buffer);
	(void)ConvertSpecialChar(dbbuffer, NULL);
	if (MPAPIselectEntry((int)_KOMMISSION, dbbuffer, (char *)&kom,
					sizeof(KOMMISSION), sizeof(kom.komm_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  _KOMMTYP */
	sta.typ = (int)_KOMMTYP;
	id = MPAPIselectOneId((int)_STATUS_WERTE, kom.komm_typ, (char *)&sta);
	state =SelectBez((int)_KOMMTYP, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  _SATZTYP */
	sta.typ = (int)_SATZTYP;
	id = MPAPIselectOneId((int)_STATUS_WERTE, kom.satz_art, (char *)&sta);
	state =SelectBez((int)_SATZTYP, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF satz */
	(void)sprintf(satzstring, "%8.2f", kom.satz);
	(void)strcat(buffer, satzstring);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Kommissionsinhaber */
	id = KUNmkbez(kom.kbst, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* KOSTEN_ART */
	id = MPAPIselectOneId((int)_KOSTEN_ART, kom.kar_id, (char *)&kar);
	if (id != (int)_UNDEF && SelectBez((int)_KOSTEN_ART, sprache, kar.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KATEGORIE */
	id = MPAPIselectOneId((int)_KATEGORIE, kom.kat_id, (char *)&kat);
	if (id != (int)_UNDEF && SelectBez((int)_KATEGORIE, sprache, kat.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* REISENDER_TYP */
	id = MPAPIselectOneId((int)_REISENDER_TYP, kom.rkr_id, (char *)&reit);
	if (id != (int)_UNDEF && SelectBez((int)_REISENDER_TYP, sprache, reit.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DIENST_ANGEBOT */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, kom.dla_id, (char *)&dla);
	if (id != (int)_UNDEF && SelectBez((int)_DIENST_ANGEBOT, sprache, dla.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DIENSTLEISTUNG */
	status = MPAPIselectDLbez(kom.dl_id, sprache, bezeichnung, (int)_RECORDLEN);
	if (status == (int)MPOK)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	(void)strcat(buffer, "\t");
	(void)strcat(buffer, "\t");
	(void)strcat(buffer, "\t");

	/* BUCHUNG  Buchungsreferenz */
	bch.bid=(int)_UNDEF;
	(void)MPAPIselectOneId((int)_BUCHUNG, kom.bid, (char *)&bch);
	if (bch.bid != (int)_UNDEF)
		{
		(void)copyTextTo(buffer1, (char *)bch.ref, (int)_BEZLEN);
		(void)strcat(buffer, buffer1);
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(kom.textid, sprache, (int)_KOMMISSION, buffer1);
	if	(id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* TRAEGER_TYP */
	id = MPAPIselectOneId((int)_TRAEGER_TYP, kom.dltt_id, (char *)&dltt);
	if (id != (int)_UNDEF && SelectBez((int)_TRAEGER_TYP, sprache,
	    dltt.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
