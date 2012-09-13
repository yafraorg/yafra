/**************************************************************/
/* Modul:     DBI - database select                           */
/*            Aktionen                                        */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTselect.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/**************************************************************/
/* Function:  Select                                          */
/**************************************************************/
int AKTselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ		sqlmem;
	extern DLG_PART	dlg;
	extern int			sprache;
	extern int			*NewLevel[];

	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[_RECORDLEN];
	char query[_QUERYLEN];
	size_t buffersize;
	BEZEICHNUNG *bez_ptr;

	switch(MENUNR)
		{
		case (unsigned char)_AKTIONSGRP:
			if (FELDNR == (unsigned char)MAKTG_HAKT &&
			    (ACTIONTYP == (unsigned char)UPDATE || ACTIONTYP == (unsigned char)MPDELETE))
				(void)sprintf(query, _SEL_BEZ_HAKT, sprache, (int)_AKTIONEN);
			else
				(void)sprintf(query, _SEL_BEZ_AKT, sprache, (int)_AKTIONEN);
			break;

		case (unsigned char)_OUTPUT:
			(void)sprintf(query, _SEL_BEZ_OUTAKT, sprache, (int)_AKTIONEN, (int)_AKT_NOEXEC);
			break;

		default:
			(void)sprintf(query, _SEL_BEZ_AKT, sprache, (int)_AKTIONEN);
			break;
		}

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
                         anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
			{
			*len = 0;
			for (i=0, buffer_ptr = buffer; i < *anzahl; i++)
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
	else  /* error in select */
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen(buffer);
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return(status);
}


/**************************************************************/
/* Function:  Choose                                          */
/**************************************************************/
int AKTchoose(int table, char *buffer)
{
	extern int				sprache;
	extern AKTIONEN		akt;
	extern AKTIONS_TYP	aktt;
	extern STATUS_WERTE	sta;
	extern char glob_bez_akt[];

	char	buffer1[_RECORDLEN];
	char  bezeichnung[_RECORDLEN];
	int	id;
	int   state;

	/* Buffer init */
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MAKT_BEZ:
			(void)strcpy(glob_bez_akt, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* AKTIONEN  Aktion */
	state = MPAPIselectEntry(table, glob_bez_akt, (char *)&akt, sizeof(akt), sizeof(akt.akt_id));
	if (state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcpy(buffer, glob_bez_akt);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Medium */
	sta.typ=(int)_DEVICE;
	id = MPAPIselectOneId((int)_STATUS_WERTE, akt.m_flag, (char *)&sta);
	state = SelectBez((int)_DEVICE, sprache, sta.bez_id, bezeichnung);
	if (id == (int)_UNDEF || state == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");
		}

	/* TEXTE */
	if (SelFromTxt(akt.textid, sprache, (int)_AKTIONEN, buffer1) == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, buffer1);
		(void)strcat(buffer, "\t");
		}

	/* STATUS_WERTE  Ausf�hrungsflag */
	sta.typ=(int)_A_FLG;
	id = MPAPIselectOneId((int)_STATUS_WERTE, akt.a_flag, (char *)&sta);
	state = SelectBez((int)_A_FLG, sprache, sta.bez_id, bezeichnung);
	if(id == (int)_UNDEF || state == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");
		}

	/* STATUS_WERTE  Ausf�hrung bei welchem Reservations-Sta */
	sta.typ=(int)_R_STA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b_flag, (char *)&sta);
	if(id == (int)_UNDEF || SelectBez((int)_R_STA, sprache, sta.bez_id,
											bezeichnung) == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");
		}

	/* AKTIONS_TYP */
	id = MPAPIselectOneId((int)_AKTIONS_TYP, (int)akt.a_typ_id, (char *)&aktt);
	if (id == (int)_UNDEF || SelectBez((int)_AKTIONS_TYP, sprache, aktt.bez_id,
		                                bezeichnung) == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");
		}

	/* STATUS_WERTE  nach Ausf�hrung welchen Reservations-Sta setzen */
	sta.typ=(int)_R_STA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b2_flag, (char *)&sta);
	if(id == (int)_UNDEF || SelectBez((int)_R_STA, sprache, sta.bez_id,
											bezeichnung) == (int)_UNDEF)
		(void)strcat(buffer, "\t");
	else
		{
		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");
		}

	COMMTYP = SELECTITEM;
	return(MPOK);
}
