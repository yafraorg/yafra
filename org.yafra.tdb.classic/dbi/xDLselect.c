/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Dienstleistung - was macht Reisender
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLselect.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int DLselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern int *NewLevel[];
	extern unsigned char alphaordering;

	extern SAISON globSAI;
	extern ANGEBOTS_TYP globDLAT;
	extern DIENST_TRAEGER dlt;
	extern ARRANGEMENT arr;
	extern BCH_DLN bd;
	extern REISENDER rei;
	extern BUCHUNG bch;
	extern int globA_ZEIT;
	extern int globE_ZEIT;
	extern unsigned char bm_obj;

	DTG_VIEW *Pdlv;
	ARRDL_VIEW *Padv;
	ARRANGEMENT localarr;
   struct tm DateTime;
	int i, id, state;
	int status = (int)MPOK;
	int bchdat;
	int selecttable;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char sqlordering[_QUERYLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	size_t buffersize;

	/* set ordering string for SQL query */
	if (alphaordering == (unsigned char)TRUE)
		(void)strcpy(sqlordering, _ORDER_DL_DAT);
	else
		(void)strcpy(sqlordering, _ORDER_DL_BEZ);

	/* init of sqlquery string and the default selecttable */
	sqlquery[0] = NULL;
	selecttable = (int)_DTG_VIEW;

	/* get menu strings */
	if (MENUNR != (unsigned char)_RESERVATION && MENUNR != (unsigned char)_BMDLN)
		{
		status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
		if (status != MPOK)
			{
			UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}

	switch (MENUNR)
		{
		case (unsigned char)_ARRANGEMENT:
			if ((ACTIONTYP == MPDELETE || ACTIONTYP == UPDATE)
			     && *to_buffers[MARR_BEZ] != NULL)
				{
				/* select active ARRANGEMENT */
				(void)sprintf(tmp_buffer, "%s%s%s", to_buffers[MARR_BEZ],
				              TRENNER, to_buffers[MARR_DAT]);
				id = MPAPIselectEntry(_ARRANGEMENT, tmp_buffer, (char *)&localarr,
				                     sizeof(localarr), sizeof(localarr.arr_id));
				if (id == (int)_UNDEF)
					break;

				/* select all DL's with TEIL and PRIO */
				selecttable = (int)_ARRDL_VIEW;
				(void)sprintf(sqlquery, _SEL_ARRDLVIEW_DL, sprache, localarr.arr_id);
				}
			break;

		case (unsigned char)_BUCHUNG:
			/* 1) ARR   2) DLT+DAT   3) DLT   4) DAT */
			if (*to_buffers[MBCH_ARR] != NULL)
				{
				id = MPAPIselectEntry(_ARRANGEMENT, to_buffers[MBCH_ARR], (char *)&localarr,
				                     sizeof(localarr), sizeof(localarr.arr_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DTGVIEW_ARR, localarr.arr_id, sprache,
				              sqlordering);
				}
			else if (*to_buffers[MBCH_DLT] != NULL && *to_buffers[MBCH_DAT] != NULL)
				{
				dlt.stufe = (int)1;
				id = MPAPIselectEntry(_DIENST_TRAEGER, to_buffers[MBCH_DLT], (char *)&dlt,
				                     sizeof(dlt), sizeof(dlt.dlt_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				ReadDate(&DateTime, (time_t *)&bchdat, to_buffers[MBCH_DAT]);
				(void)sprintf(sqlquery, _SEL_DTG_VIEW_DLTAE, sprache,
				        (bchdat - _DATERANGE), (bchdat + _DATERANGE), dlt.dlt_id);
				}
			else if (*to_buffers[MBCH_DLT] != NULL)
				{
				dlt.stufe = (int)1;
				id = MPAPIselectEntry(_DIENST_TRAEGER, to_buffers[MBCH_DLT], (char *)&dlt,
				                     sizeof(dlt), sizeof(dlt.dlt_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DTGVIEW_DLT, sprache, dlt.dlt_id, sqlordering);
				}
			else if (*to_buffers[MBCH_DAT] != NULL)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				ReadDate(&DateTime, (time_t *)&bchdat, to_buffers[MBCH_DAT]);
				(void)sprintf(sqlquery, _SEL_DTGVIEW_AE, sprache,
				     (bchdat - _DATERANGE), (bchdat + _DATERANGE), sqlordering);
				}
			break;

		case (unsigned char)_RESERVATION:
			/* BCH and BD has to be set from booking masks ! */
			if (bm_obj == (int)_DIENSTLEISTUNG)
				{
				(void)sprintf(sqlquery, _SEL_DTGVIEW_BCHDLN, bd.bid, bd.dln_id,
				              sprache, sqlordering);
				}
			else
				{
				selecttable = (int)_ARRDL_VIEW;
				if (ACTIONTYP == (unsigned char)MPDELETE)
					{
					/*!!! check if BCHDLN.DLN_ID is set */
					(void)sprintf(sqlquery, _SEL_ARRDLVIEW_RES,
					              bch.arr_id, bd.bid, bd.dln_id, sprache);
					}
				else
					(void)sprintf(sqlquery, _SEL_ARRDLVIEW_DL, sprache, bch.arr_id);
				}
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	/* free up menu buffers */
	if (MENUNR != (unsigned char)_RESERVATION && MENUNR != (unsigned char)_BMDLN)
		UtilSplitFreeMenubuffer(to_buffers);

	/* check status */
	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		{
		if (globA_ZEIT != _UNDEF && globE_ZEIT != _UNDEF)
			(void)sprintf(sqlquery, _SEL_DTGVIEW_AE, sprache,
			              globA_ZEIT, globE_ZEIT, sqlordering);
		else if (globA_ZEIT != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DTGVIEW_A, sprache,
		                 globA_ZEIT, sqlordering);
		else if (globE_ZEIT != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DTGVIEW_E, sprache,
		                 globE_ZEIT, sqlordering);
		else if (globDLAT.art_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DTGVIEW_DLAT, sprache,
			              globDLAT.art_id, sqlordering);
		else if (globSAI.sai_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DTGVIEW_SAI, sprache,
			              globSAI.sai_id, sqlordering);
		else
			(void)sprintf(sqlquery, _SEL_DTGVIEW, sprache, sqlordering);
		}


	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery(selecttable, &sqlmem.buffer, sqlquery, anzahl,
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
			for ( i=0, buffer_ptr=buffer; i < *anzahl; i++ )
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_min  = (int)_UNDEF;
				DateTime.tm_hour = (int)_UNDEF;
				DateTime.tm_mday = (int)_UNDEF;
				DateTime.tm_mon  = (int)_UNDEF;
				DateTime.tm_year = (int)_UNDEF;
				if (selecttable == (int)_DTG_VIEW)
					{
					Pdlv = (DTG_VIEW *)&sqlmem.buffer[i*sizeof(DTG_VIEW)];
					Pdlv->bez[_BEZLEN] = (char)NULL;
					buffersize = strlen(Pdlv->bez);
					(void)memcpy((void *)buffer_ptr, (void *)Pdlv->bez, buffersize+(size_t)1);
					buffer_ptr += buffersize;
					(void)memcpy((void *)buffer_ptr, (void *)TRENNER, TRENNERLEN);
					buffer_ptr += TRENNERLEN;
					(void)WriteDate(&DateTime, (time_t *)&Pdlv->a_zeit, tmp_buffer);
					buffersize = strlen( tmp_buffer );
					(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
					buffer_ptr += buffersize;
					}
				else
					{
					Padv = (ARRDL_VIEW *)&sqlmem.buffer[i*sizeof(ARRDL_VIEW)];
					(void)sprintf(tmp_buffer, "%-4d", Padv->teil);
					buffersize = strlen(tmp_buffer);
					(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1);
					buffer_ptr += buffersize;
					(void)sprintf(tmp_buffer, "%-4d:", Padv->prio);
					buffersize = strlen(tmp_buffer);
					(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1);
					buffer_ptr += buffersize;
					Padv->bez[_BEZLEN] = (char)NULL;
					buffersize = strlen(Padv->bez);
					(void)memcpy((void *)buffer_ptr, (void *)Padv->bez, buffersize+(size_t)1);
					buffer_ptr += buffersize;
					(void)memcpy((void *)buffer_ptr, (void *)TRENNER, TRENNERLEN);
					buffer_ptr += TRENNERLEN;
					(void)WriteDate(&DateTime, (time_t *)&Padv->a_zeit, tmp_buffer);
					buffersize = strlen(tmp_buffer);
					(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1);
					buffer_ptr += buffersize;
					}
				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}
			}
		else
			{
			*buffer = NULL;
			if (MENUNR == NewLevel[MENUNR][FELDNR] )
				{
				UtilMsg((int)MPE_NOCHOOSE, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			}
		}
	else
		{
		UtilMsg(status, MSGTYP_ERROR, NULL);
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
int DLchoose(int table, char *buffer)
{
	extern int sprache;
	extern DIENSTLEISTUNG	dtg;
	extern DLG_PART			dlg;
	extern DLG_DLG				dd_old;
	extern AKTIONEN			akt;
	extern char glob_bez_dtg[];
	extern char glob_dat_dtg[];
	extern char glob_dlg_dtg[];

	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	int	id;

	(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
	(void)memset( (void *)buffer1, NULL, sizeof(buffer1) );
	(void)memset( (void *)buffer2, NULL, sizeof(buffer2) );
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDL_BEZ:
			(void)strcpy(glob_bez_dtg, buffer);
			break;
		case MDL_DAT:
			(void)strcpy(glob_dat_dtg, buffer);
			return(MPOK);
			break;
		case MDL_TDL:
			(void)strcpy(glob_dlg_dtg, buffer);
			if (*glob_bez_dtg == NULL)
				return(MPOK);
			else
				if (ACTIONTYP != (unsigned char)INSERT)
					(void)strcpy(buffer, glob_bez_dtg);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* DIENSTLEISTUNG  */
	if (MPAPIselectEntry(table, buffer, (char *)&dtg, sizeof(dtg), sizeof(dtg.dlg_id)) == (int)_UNDEF )
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	dd_old.dlg_id = dtg.dlg_id;
	(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2 );
	buffer1[strlen( buffer1 )-1] = '\0';
	(void)strcpy(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* DLG_PART  */
	dlg.dl_id = (int)0;
	if (MPAPIselectEntry( (int)_DLG_PART, glob_dlg_dtg, (char *)&dlg, sizeof(dlg), sizeof(dlg.dl_id) ) != (int)_UNDEF )
		{
		(void)strcat(buffer, glob_dlg_dtg);
		dd_old.dl_id = dlg.dl_id;
		}
	else
		{
		if ( dlg.dl_id != (int)0 )
			{
			dd_old.dl_id = dlg.dl_id;
			(void)strcat(buffer, glob_dlg_dtg);
			}
		}
	(void)strcat( buffer, "\t" );

	/* TEXTE */
	id = SelFromTxt( dtg.textid, sprache, (int)_DIENSTLEISTUNG, buffer1 );
	if (id != (int)_UNDEF )
		(void)strcat( buffer, buffer1 );
	(void)strcat( buffer, "\t" );

	/* DATUM */
	if ( dtg.a_zeit != (int)_UNDEF )
		{
		DateTime.tm_mday = (int)_UNDEF;
		DateTime.tm_mon  = (int)_UNDEF;
		DateTime.tm_year = (int)_UNDEF;
		DateTime.tm_hour = (int)_UNDEF;
		DateTime.tm_min  = (int)_UNDEF;
		(void)WriteDate( &DateTime, (time_t *)&dtg.a_zeit, bezeichnung );
		(void)strcat( buffer, bezeichnung );
		}
	(void)strcat( buffer, "\t" );

	/* AKTIONEN */
	akt.akt_id = dtg.akt_id;
	id = MPAPIselectOneId( (int)_AKTIONEN, dtg.akt_id, (char *)&akt );
	if (id != (int)_UNDEF && SelectBez((int)_AKTIONEN, sprache, akt.bez_id, bezeichnung) != (int)_UNDEF)
		(void)strcat( buffer, bezeichnung );
	(void)strcat( buffer, "\t" );

	/* UNDEF */
	if (*glob_dlg_dtg != NULL )
		{
		dd_old.ord = (int)_UNDEF;
		id = MPAPIselectOneId( (int)_DLG_DLG, dd_old.dlg_id, (char *)&dd_old );
		if (dd_old.ord > (int)0 )
			{
			sprintf( bezeichnung, "%d", dd_old.ord );
			(void)strcat( buffer, bezeichnung );
			}
		else
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return( (int)MPERROR );
			}
		}
	(void)strcat( buffer, "\t" );

	/* UNDEF  CODE */
   (void)copyTextTo(bezeichnung, dtg.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
