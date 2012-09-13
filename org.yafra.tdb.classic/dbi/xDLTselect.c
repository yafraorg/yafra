/*D***********************************************************
 * Modul:     DBI - database select
 *            Dienstleistungstraeger
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLTselect.c,v 1.5 2009-01-02 16:51:34 mwn Exp $";

/* local prototypes */
static int DLTselectfree(int *, int, int, int, int, time_t);

/*************************************************************
 * Function:  DLTselect
 * Typ:       public
 * Desc:      get 1-n DLT entries from the DB
 *************************************************************/
int DLTselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char sqlquery[];

	extern DIENST_TRAEGER globDLT;
	extern TRAEGER_TYP    globDLTT;
	extern KATEGORIE      globKAT;
	extern DIENST_TRAEGER dlt;
	extern DIENSTLEISTUNG dtg;
	extern KATEGORIE      kat;
	extern KONTINGENT     kon;
	extern HOST_KONT      hkon;
	extern RESERVATION    res;

	TRAEGER_VIEW *trv_ptr;
	TRAEGER_VIEW htrv;
	DLT_VIEW *dltv_ptr;

	int i;
	int status = (int)MPOK;
	int id;
	int selecttable;
	int dl_id, dlpart_id, kat_id, kont_id;
	int *tdlids;
	int tdlcnt;
	size_t buffersize;

	unsigned char hostflag = (unsigned char)FALSE;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];

	/* init of sqlquery string */
	sqlquery[0] = NULL;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		dlt.dlt_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	switch(MENUNR)
		{
		case (unsigned char)_DIENST_TRAEGER:
			if (FELDNR == (unsigned char)MDLT_HOST)
				{
				hostflag = (unsigned char)TRUE;
				if (globDLTT.typ_id != (int)_UNDEF && globDLTT.h_typ_id == (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS_DLTT, sprache, globDLTT.typ_id);
				else
					(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS, sprache);
				}
			else if (FELDNR == (unsigned char)MDLT_HDLT)
				{
				/* if we search an upper dlt, loook for restrictions */
				TRAEGER_TYP dltt;

				/* bringe alle Kinder eines Vaters (HDLT) */
				if (*to_buffers[MDLT_HOST] != NULL && *to_buffers[MDLT_DLTT] != NULL)
					{
					dlt.stufe = (int)1;
					if (MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HOST], (char *)&dlt,
								sizeof(dlt), sizeof(dlt.dlt_id)) != (int)_UNDEF)
						{
						if (MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLT_DLTT], (char *)&dltt,
							sizeof(dltt), sizeof(dltt.typ_id)) != (int)_UNDEF)
							{
							(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT_DLTT, sprache, dlt.dlt_id, dltt.h_typ_id);
							}
						}
					}
				else if (*to_buffers[MDLT_HOST] != NULL)
					{
					/* select only the childs of the current hostdlt */
					dlt.stufe = (int)1;
					if (MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HOST], (char *)&dlt,
								sizeof(dlt), sizeof(dlt.dlt_id)) != (int)_UNDEF)
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT, sprache, dlt.dlt_id);
					}

				else if (*to_buffers[MDLT_DLTT] != NULL)
					{
					/* select only the dlt's of the current dltt */
				   	TRAEGER_TYP dltt;
					if (MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLT_DLTT], (char *)&dltt,
							sizeof(dltt), sizeof(dltt.typ_id)) != (int)_UNDEF)
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_DLTT, sprache, dltt.h_typ_id);
					}
				}
			else
				{
				TRAEGER_TYP dltt;

				/* bringe alle Kinder eines Vaters (HDLT) */
				if (*to_buffers[MDLT_HDLT] != NULL)
					{
					/* set hdltid */
					if ((strstr(to_buffers[MDLT_HDLT], TRENNER)) == NULL)
						dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
					else
						dlt.stufe = 0; /* Eintrag ist unterhalb der obersten Stufe */
					if (MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HDLT],
						 (char *)&dlt,	sizeof(dlt), sizeof(dlt.dlt_id)) == (int)_UNDEF)
						break;
					(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HDLT, sprache, dlt.dlt_id);
					}

				/* bringe alle eines Roots vom spez. Typ */
				else if ((*to_buffers[MDLT_HOST] != NULL || globDLT.dlt_id != _UNDEF) &&
					 (*to_buffers[MDLT_DLTT] != NULL || globDLTT.typ_id != _UNDEF))
					{
					/* set hostid */
					if (*to_buffers[MDLT_HOST] != NULL)
						{
						dlt.stufe = (int)1;
						(void)MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HOST],
						 (char *)&dlt,	sizeof(dlt), sizeof(dlt.dlt_id));
						}
					/* set typid */
					if (*to_buffers[MDLT_DLTT] != NULL)
						(void)MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLT_DLTT],
						      (char *)&dltt, sizeof(dltt), sizeof(dltt.typ_id));

					if (dlt.dlt_id != (int)_UNDEF && dltt.typ_id != (int)_UNDEF)
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT_DLTT, sprache,
						              dlt.dlt_id, dltt.typ_id);
					}

				/* bringe alle eines Roots */
				else if (*to_buffers[MDLT_HOST] != NULL)
					{
					if (*to_buffers[MDLT_HOST] != NULL)
						{
						dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
						if (MPAPIselectEntry((int)_DIENST_TRAEGER, to_buffers[MDLT_HOST],
							 (char *)&dlt,	sizeof(dlt), sizeof(dlt.dlt_id)) != (int)_UNDEF)
							(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT,
							              sprache, dlt.dlt_id);
						}
					}

				/* bringe alle DLTs eines Typs */
				else if (*to_buffers[MDLT_DLTT] != NULL)
					{
					if (*to_buffers[MDLT_DLTT] != NULL)
						{
						if (MPAPIselectEntry((int)_TRAEGER_TYP, to_buffers[MDLT_DLTT],
							 (char *)&dltt, sizeof(dltt), sizeof(dltt.typ_id)) != (int)_UNDEF)
							(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_DLTT, sprache,
							              dltt.typ_id);
						}
					}

				/* bringe alle DLTs einer Kategorie */
				else if (*to_buffers[MDLT_KAT] != NULL)
					{
					if (*to_buffers[MDLT_KAT] != NULL)
						{
						if (MPAPIselectEntry((int)_KATEGORIE, to_buffers[MDLT_KAT],
							 (char *)&kat, sizeof(kat), sizeof(kat.kat_id)) != (int)_UNDEF)
							(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_KAT, sprache, sprache,
								(int)_DIENST_TRAEGER, (int)_DIENST_TRAEGER, kat.kat_id);
						}
					}
				}
			break;

		/* bringe nur HOST Eintr�ge */
		case (unsigned char)_DIENST_ANGEBOT:
		case (unsigned char)_GLOBALMENU:
		case (unsigned char)_OUTPUT:
		case (unsigned char)_GRAPHIK:
			hostflag = (unsigned char)TRUE;
			if (globDLTT.typ_id != (int)_UNDEF && globDLTT.h_typ_id == (int)_UNDEF)
				(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS_DLTT, sprache, globDLTT.typ_id);
			else
				(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS, sprache);
			break;

		case (unsigned char)_BUCHUNG:
			hostflag = (unsigned char)TRUE;
			if (*to_buffers[MBCH_DL] != NULL)
				{
				id = MPAPIselectEntry(_DIENSTLEISTUNG, to_buffers[MBME_DL], (char *)&dtg,
				                     sizeof(dtg), sizeof(dtg.dlg_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS_DL, sprache, dtg.dlg_id);
				}
			else if (globDLTT.typ_id != (int)_UNDEF && globDLTT.h_typ_id == (int)_UNDEF)
				(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS_DLTT, sprache, globDLTT.typ_id);
			else
				(void)sprintf(sqlquery, _SEL_DLTVIEW_HOSTS, sprache);
			break;

		/* arbeite �ber Buffer und nicht �ber DB */
		case (unsigned char)_RESERVATION:
			/* read menu string and set it to RES */
			tdlids = NULL;
			tdlcnt = 0;
			status = BMRESreadprotocol(buffer, &res, &tdlids, &tdlcnt);
			if (status != (int)MPOK)
				{
				UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
				return(status);
				}
			status = DLTselectfree(anzahl, res.dlg_id, res.dl_id, res.kat_id,
			         res.kont_id, (time_t)res.a_zeit);
			comm.datalen = CleanPipeString(comm.buffer);
			*len = comm.datalen;
			MPfree((void *)tdlids);
			UtilSplitFreeMenubuffer(to_buffers);
			return(status);
			break;

		case (unsigned char)_KONT_DETAIL:
			if (*to_buffers[MKOND_HKON] != NULL &&
			    *to_buffers[MKOND_KON] == NULL)
				{
				if (MPAPIselectEntry((int)_HOST_KONT, to_buffers[MKOND_HKON],
				    (char *)&hkon, sizeof(HOST_KONT), sizeof(hkon.hostkont_id)) != (int)_UNDEF)
					{
					if (ACTIONTYP == (unsigned char)INSERT)
						{
						status = MPAPIselectDLT(hkon.dla_id, (int)_UNDEF, hkon.dl_id, &dlt);
						if (status != (int)MPOK)
							break;
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT, sprache,
						              dlt.dlt_id);
						}
					else
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_KOND_HKON,
						              hkon.hostkont_id, sprache);
					}
				}
			else if (*to_buffers[MKOND_KON] != NULL &&
			    *to_buffers[MKOND_HKON] == NULL)
				{
				if (MPAPIselectEntry((int)_KONTINGENT, to_buffers[MKOND_KON], (char *)&kon,
				    sizeof(KONTINGENT), sizeof(kon.kont_id)) != (int)_UNDEF)
					{
					if (ACTIONTYP == (unsigned char)INSERT)
						{
						id = MPAPIselectOneId((int)_HOST_KONT, kon.hostkont_id, (char *)&hkon);
						if (id == (int)_UNDEF)
							break;
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_KOND_HKON,
						              hkon.hostkont_id, sprache);
						}
					else
						(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_KOND_KON,
						              kon.kont_id, sprache);
					}
				}
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;

		}	/* switch () ENDE */

	UtilSplitFreeMenubuffer(to_buffers);

	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		{
		/* bringe alle eines Roots vom spez. Typ */
		if (globDLT.dlt_id != _UNDEF && globDLTT.typ_id != _UNDEF)
			(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT_DLTT, sprache,
				globDLT.dlt_id, globDLTT.typ_id);
		/* bringe alle eines Roots */
		else if (globDLT.dlt_id != _UNDEF)
			(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_HOSTDLT, sprache, globDLT.dlt_id);
		/* bringe alle DLTs eines Typs */
		else if (globDLTT.typ_id != _UNDEF)
			(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_DLTT, sprache, globDLTT.typ_id);
		/* bringe alle DLTs einer Kategorie */
		else if (globKAT.kat_id != _UNDEF)
			(void)sprintf(sqlquery, _SEL_TRAEGERVIEW_KAT, sprache, sprache,
				(int)_DIENST_TRAEGER, (int)_DIENST_TRAEGER, globKAT.kat_id);
		/* bringe alle DLTs */
		else
			(void)sprintf(sqlquery, _SEL_TRAEGERVIEW, sprache);
		}

	/* set the right table to select from later */
	if (hostflag == (unsigned char)TRUE)
		selecttable = (int)_DLT_VIEW;
	else
		selecttable = (int)_TRAEGER_VIEW;

	/* get the data and put it to the SELECT protocol */
	status = MPAPIdb_sqlquery(selecttable, &sqlmem.buffer, sqlquery,
	                           anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
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
			if (hostflag == (unsigned char)TRUE)
				{
				for ( i=0, buffer_ptr=buffer; i < *anzahl; i++ )
					{
					dltv_ptr=(DLT_VIEW *)&sqlmem.buffer[i*sizeof(DLT_VIEW)];
					(void)copyTextTo(tmp_buffer, (char *)dltv_ptr->bez, (int)_BEZLEN);
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
				for ( i=0, buffer_ptr=buffer; i < *anzahl; i++ )
					{
					trv_ptr=(TRAEGER_VIEW *)&sqlmem.buffer[i*sizeof(TRAEGER_VIEW)];
					(void)copyTextTo(tmp_buffer, (char *)trv_ptr->bez, (int)_BEZLEN);
					buffersize = strlen( tmp_buffer );
					(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
					buffer_ptr += buffersize;

					if (trv_ptr->id != trv_ptr->host)
						{
						/* get parent description of this entry */
						id = MPAPIselectOneId( (int)_TRAEGER_VIEW, (int)trv_ptr->hid, (char *)&htrv );
						if (id != (int)_UNDEF)
							{
							(void)memcpy((void *)buffer_ptr, TRENNER, (size_t)TRENNERLEN);
							buffer_ptr += (size_t)TRENNERLEN;
							(void)copyTextTo(tmp_buffer, (char *)htrv.bez, (int)_BEZLEN);
							buffersize = strlen( tmp_buffer );
							(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
							buffer_ptr += buffersize;
							}
						}

					(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
					buffer_ptr++;
					(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
					}
				}
			}
		else
			{
			*buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR])
				{
				UtilMsg( MPE_NOCHOOSE, MSGTYP_ERROR, NULL );
				status = (int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg( status, MSGTYP_DBERROR, NULL );
		status = (int)MPERROR;
		}

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*************************************************************
 * Function:  DLTchoose
 * Typ:       public
 * Desc:      get 1 entry
 *************************************************************/
int DLTchoose(int table, char *buffer)
{
	extern int sprache;
	extern char glob_dltbez[];
	extern char glob_hdlt_dlt[];
	extern char glob_host_dlt[];
	extern DIENST_TRAEGER 	dlt;
	extern KATEGORIE			kat;
	extern TRAEGER_VIEW		trv;
	extern TTYP_VIEW			ttyp;
	extern STATUS_WERTE		sta;

	TRAEGER_VIEW		htrv;
	DLT_VIEW dltv;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char  dltbuffer[RECLAENGE];
	int	id, state;

	(void)memset( (void *)buffer1, NULL, sizeof( buffer1 ) );
	(void)memset( (void *)buffer2, NULL, sizeof( buffer2 ) );
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDLT_BEZ:   /* DIENST_TRAEGER effektiver Dienstleistungstr�ger */
			(void)memcpy(glob_dltbez, buffer, _RECORDLEN);
			break;
		case MDLT_HDLT:  /* Uebergeordneter DLT (parent) */
			(void)strcpy(glob_hdlt_dlt, buffer);
			return(MPOK);
			break;
		case MDLT_HOST: /* Haupt DLT (root) */
			(void)strcpy(glob_host_dlt, buffer);
			return(MPOK);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* create string for menu                           Output: 1 Menu */

	/* DIENST_TRAEGER   effektiver Dienstleistungstr�ger */
	if ((strstr(buffer, TRENNER)) == NULL)
		dlt.stufe = 1; /* Eintrag ist von der obersten Stufe */
	else
		{
		if (*glob_host_dlt != NULL)
			{
			dlt.stufe = 1;
			id = MPAPIselectEntry((int)_DIENST_TRAEGER, glob_host_dlt, (char *)&dlt,
			    sizeof(dlt), sizeof( dlt.dlt_id ));
			if (id == (int)_UNDEF)
				dlt.host_id = (int)_UNDEF;
			else
				dlt.host_id = dlt.dlt_id;
			}
		else
			dlt.host_id = (int)_UNDEF;

		dlt.dlt_id = (int)_UNDEF;
		dlt.h_dlt_id = (int)_UNDEF;
		dlt.stufe = 0; /* Eintrag ist unterhalb der obersten Stufe */
		}
	id = MPAPIselectEntry((int)_DIENST_TRAEGER, buffer, (char *)&dlt, sizeof(dlt),
	    sizeof( dlt.dlt_id ));
	if (id == (int)_UNDEF)
		{
		UtilMsg( (int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL );
		return( (int)MPERROR );
		}
	if (dlt.stufe == (int)1)
		(void)strcpy(dltbuffer, buffer);
	else
		{
		(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2);
		buffer1[strlen(buffer1)-1] = '\0';
		(void)strcpy(buffer, buffer1);
		}
	(void)strcat(buffer, "\t");

	/* KATEGORIE */
	id = MPAPIselectOneId( (int)_KATEGORIE, (int)dlt.kat_id, (char *)&kat );
	if (id != (int)_UNDEF && SelectBez((int)_KATEGORIE, sprache, kat.bez_id, bezeichnung) != (int)_UNDEF )
		(void)strcat( buffer, bezeichnung );
	(void)strcat(buffer, "\t");

	/* DIENST_TRAEGER  �bergeordneter Dienstleistungstr�ger */
	if (dlt.stufe > (int)1)
		{
		id = MPAPIselectOneId((int)_TRAEGER_VIEW, dlt.h_dlt_id, (char *)&trv);
		if ( id != (int)_UNDEF )
			{
			(void)copyTextTo( bezeichnung, trv.bez, (int)_BEZLEN );
			(void)strcat( buffer, bezeichnung );
			if (trv.hid != (int)_UNDEF)
				{
				/* get parent description of this entry */
				id = MPAPIselectOneId( (int)_TRAEGER_VIEW, (int)trv.hid, (char *)&htrv );
				if (id != (int)_UNDEF)
					{
					(void)strcat( buffer, TRENNER);
					(void)copyTextTo( bezeichnung, htrv.bez, (int)_BEZLEN);
					(void)strcat( buffer, bezeichnung );
					}
				}
			}
		}
	(void)strcat(buffer, "\t");

	/* TRAEGER_TYP */
	id = MPAPIselectOneId( (int)_TTYP_VIEW, (int)dlt.typ_id, (char *)&ttyp );
	if ( id != (int)_UNDEF )
		{
		(void)copyTextTo( bezeichnung, ttyp.bez, (int)_BEZLEN);
		(void)strcat( buffer, bezeichnung );
		(void)strcat( buffer, TRENNER);
		(void)copyTextTo( bezeichnung, ttyp.hbez, (int)_BEZLEN);
		(void)strcat( buffer, bezeichnung );
		}
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if ( SelFromTxt( dlt.textid,sprache,(int)_DIENST_TRAEGER,buffer1 ) != (int)_UNDEF )
		(void)strcat( buffer, buffer1 );
	(void)strcat(buffer, "\t");

	/* DIENST_TRAEGER  Hauptdienstleistungstr�ger (aller oberster im Baum) */
	if (dlt.stufe > (int)1)  /* Checke ob gew�hlter DLT nicht schon   */
		{                        /* oberster im Baum ist                  */
		if (*glob_host_dlt != NULL)
			strcat(buffer, glob_host_dlt);
		else
			{
			id = MPAPIselectOneId( (int)_DLT_VIEW, (int)dlt.host_id, (char *)&dltv);
			if (id != (int)_UNDEF )
				{
				(void)copyTextTo( bezeichnung, dltv.bez, (int)_BEZLEN );
				(void)strcat( buffer, bezeichnung );
				}
			}
		}
	else
		strcat(buffer, dltbuffer);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Bestplatzattribute */
	sta.typ = (int)_DLTSTA;
	id = MPAPIselectOneId((int)_STATUS_WERTE, dlt.sta_id, (char *)&sta);
	state =SelectBez((int)_DLTSTA, sprache, sta.bez_id, bezeichnung);
	if (id != (int)_UNDEF && state != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  CODE */
   (void)copyTextTo(bezeichnung, dlt.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Max. Anzahl Personen auf Einheit*/
	if (dlt.anz > (int)0)
		{
		sprintf(bezeichnung, "%d", dlt.anz);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");


	COMMTYP = SELECTITEM;
	return(MPOK);
}




/* privates */

#define _SEL_FREE_DLT_DAT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE DL_ID IN (%s) AND DLT_ID > -1 AND (A_ZEIT <= %d AND E_ZEIT >= %d) \
	ORDER BY DLT_ID, PERS_ID;"

#define _SEL_FREE_DLT "SELECT * FROM TDBADMIN.RESERVATION R \
	WHERE DL_ID IN (%s) AND DLT_ID > -1 ORDER BY DLT_ID, PERS_ID;"

#define _SEL_DLT_HOSTDLT_KAT "SELECT TV.* \
	FROM TDBADMIN.TRAEGER_VIEW TV, TDBADMIN.DIENST_TRAEGER D \
	WHERE D.HOST_ID = %d AND D.KAT_ID = %d \
	AND TV.SPR = %d AND D.DLT_ID = TV.ID ORDER BY TV.BEZ;"

#define _SEL_DLT_HOSTDLT "SELECT * \
	FROM TDBADMIN.TRAEGER_VIEW TV WHERE HOST = %d AND SPR = %d ORDER BY BEZ;"

#define _SEL_DLT_KON "SELECT TV.* \
	FROM TDBADMIN.TRAEGER_VIEW TV, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.KONT_ID = %d AND KD.KAT_ID = -1 AND TV.ID = KD.DLT_ID \
	AND TV.SPR = %d ORDER BY TV.BEZ;"

#define _SEL_DLT_KAT_KON "SELECT TV.* \
	FROM TDBADMIN.TRAEGER_VIEW TV, TDBADMIN.DIENST_TRAEGER D, TDBADMIN.KONT_DETAIL KD \
	WHERE KD.KONT_ID = %d AND D.HOST_ID = %d AND D.KAT_ID = %d \
	AND TV.SPR = %d AND D.DLT_ID = KD.DLT_ID AND TV.ID = D.DLT_ID \
	ORDER BY TV.BEZ;"

/*************************************************************
 * function:  DLTselectfree
 * typ:       privat
 * desc:      get 1-n DLT entries all from the DB
 * input:     DL / DLG_PART / KAT / KONT
 * output:    select list of free DLT's to global comm buffer
 *************************************************************/
static int DLTselectfree(int *anzahl, int dl_id, int dlpart_id,
                  int kat_id, int kont_id, time_t date)
{
	extern MEMOBJ sqlmem;
	extern TRAEGER_VIEW trv;
	extern int sprache;

	TRAEGER_VIEW *dltbuffer = NULL;
	RESERVATION *reservation = NULL;
	DLG_DLG *dlg_dlg = NULL;

	DLG_PART dlpart;
	DIENST_ANGEBOT dla;
	KATEGORIE kat;

	int status = (int)MPOK;
	int anzdlt, anzdlg, anzres;
	int id;
	register int i, j;
	int found;
	unsigned long dlen, alen;
	time_t vondat, bisdat;

	char query[RECLAENGE];
	char tmp_buffer[RECLAENGE];
	char dl_string[RECLAENGE];
	char bez1[_BEZLEN + 1];
	char bez2[_BEZLEN + 1];

	/* init */
	*anzahl = 0;
	comm.buffer[0] = NULL;

	/* get DLG_PARTS for searching in RES */
	if (dlpart_id == (int)_UNDEF)
		{
		/* Ist eine g�ltige aktive Dienstleistung vorhanden */
		/* Alle Teildienstleistungen der DIENSTLEISTUNG */
		(void)sprintf(query, _SEL_DLDLG, dl_id);
		status=MPAPIdb_sqlquery((int)_DLG_DLG, &sqlmem.buffer, query,
		                  &anzdlg, &sqlmem.datalen, &sqlmem.alloclen);
		if (status != (int)MPOK)
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		dlg_dlg = (DLG_DLG *)sqlmem.buffer;
		id = MPAPIselectOneId((int)_DLG_PART, dlg_dlg[0].dl_id, (char *)&dlpart);
		if (id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		for (i=0, *dl_string=(char)NULL; i < anzdlg; i++)
			{
			sprintf(tmp_buffer, "%d,", dlg_dlg[i].dl_id);
			strcat(dl_string, tmp_buffer);
			}
		dl_string[strlen( dl_string )-1] = NULL;
		}
	else
		{
		id = MPAPIselectOneId((int)_DLG_PART, dlpart_id, (char *)&dlpart);
		if (id == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NODLG, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		sprintf(dl_string, "%d", dlpart_id);
		}

	/* get current date if nec. */
	if (dlpart.res_f == (int)_RES_DYNAMIC)
		{
		if (date == (time_t)_UNDEF)
			(void)time(&date);
		}
	else
		date = (time_t)_UNDEF;

	/* Das Angebot der ersten Teildienstleistung aus der datenbank lesen */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dlpart.dla_id, (char *)&dla);
	if (id == (int)_UNDEF)
		{
		/*	Kein Dienstleistungsangebot ist g�ltig */
		UtilMsg( (int)MPE_NODLA, MSGTYP_ERROR, NULL );
		status = (int)MPERROR;
		return( status );
		}
	else
		{
		if ( dla.dlt_id == (int)_UNDEF)
			{
			UtilMsg( (int)MPE_NODLTINDLA, MSGTYP_ERROR, NULL );
			return((int)MPERROR);
			}
		}

	/* get all needed DLT for match with RES */
	dlen = alen = 0;

	if      (kont_id != (int)_UNDEF && kat_id != (int)_UNDEF)
		(void)sprintf(query, _SEL_DLT_KAT_KON, kont_id, dla.dlt_id, kat_id, sprache);

	else if (kont_id != (int)_UNDEF && kat_id == (int)_UNDEF)
		(void)sprintf(query, _SEL_DLT_KON, kont_id, sprache);

	else if (kat_id != (int)_UNDEF && kont_id == (int)_UNDEF)
		(void)sprintf(query, _SEL_DLT_HOSTDLT_KAT, dla.dlt_id, kat_id, sprache);

	else if (kat_id == (int)_UNDEF && kont_id == (int)_UNDEF)
		(void)sprintf(query, _SEL_DLT_HOSTDLT, dla.dlt_id, sprache);

	status=MPAPIdb_sqlquery((int)_TRAEGER_VIEW, (char **)&dltbuffer, query,
	        &anzdlt, &dlen, &alen);
	if (status != (int)MPOK || anzdlt < 1)
		{
		MPfree((void *)dltbuffer);
		UtilMsg((int)MPE_NODLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* Alle Reservationsdaten der Teildienstlesistungen aus der Datenbank lesen */
	if (date > 0)
		(void)sprintf(query, _SEL_FREE_DLT_DAT, dl_string, (int)date, (int)date);
	else
		(void)sprintf(query, _SEL_FREE_DLT, dl_string);

	status = MPAPIdb_sqlquery((int)_RESERVATION, &sqlmem.buffer, query,
	                           &anzres, &sqlmem.datalen, &sqlmem.alloclen);
	reservation = (RESERVATION *)sqlmem.buffer;
	if (status != (int)MPOK)
		{
		MPfree((void *)dltbuffer);
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* match DLT with RES */
	for (i=0; i<anzdlt; i++)
		{
		found = (int)_UNDEF;
		for (j=0; j<anzres; j++)
			{
			if (dltbuffer[i].id == reservation[j].dlt_id)
				{
				found = 0;
				break;
				}
			}
		if (found == (int)_UNDEF)
			{
			(void)copyTextTo(bez1, dltbuffer[i].bez, (int)_BEZLEN);
			if (dltbuffer[i].hid == (int)_UNDEF)
				(void)sprintf(tmp_buffer, "%s\n", bez1);
			else
				{
				(void)copyTextTo(bez2, dltbuffer[i].bez, (int)_BEZLEN);
				(void)sprintf(tmp_buffer, "%s%s%s\n", bez1, TRENNER, bez2);
				}
			(void)strcat(comm.buffer, tmp_buffer);
			*anzahl = *anzahl + 1;
			}
		}

	MPfree((void *)dltbuffer);

	if (*anzahl < 1)
		{
		UtilMsg((int)MPE_NODLTFREE, MSGTYP_ERROR, NULL);
		status = (int)MPERROR;
		comm.datalen = 0;
		}
	else
		{
		comm.datalen = (int)strlen( comm.buffer );
		if (*anzahl == 1)
			comm.buffer[(comm.datalen - 1)] = NULL;
		}

	return( status );
}
