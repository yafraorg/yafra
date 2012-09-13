/*D***********************************************************
 * Modul:     DBI - database select                           
 *            DLG_PART - was macht Tr�ger
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xTDLselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int DLGselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern char sqlquery[];
	extern int *NewLevel[];
	extern unsigned char alphaordering;

	extern SAISON globSAI;
	extern ANGEBOTS_TYP globDLAT;
	extern DIENSTLEISTUNG dtg;
	extern int globA_ZEIT;
	extern int globE_ZEIT;
	extern char glob_bez_dtg[];
	extern char glob_akt_out[];

	DLG_VIEW *Ptdlv;
	DIENSTLEISTUNG localdl;
	AKTIONEN akt;

	struct tm DateTime;
	int i, id;
	int status = (int)MPOK;
	int tdlhost_flag;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char sqlordering[_QUERYLEN];
	char sqlhoststring[_QUERYLEN];
	size_t buffersize;

	/* set ordering string for SQL query */
	if (alphaordering == (unsigned char)TRUE)
		(void)strcpy(sqlordering, _ORDER_DLPARTS_DAT);
	else
		(void)strcpy(sqlordering, _ORDER_DLPARTS_BEZ);

	/* init of sqlquery string */
	sqlquery[0] = (char)NULL;
	tdlhost_flag = (int)FALSE;
	(void)strcpy(sqlhoststring, _DLGPARTS_ALL);

	switch (MENUNR)
		{
		case (unsigned char)_DIENSTLEISTUNG:
			if (*glob_bez_dtg != (char)NULL &&
			    (ACTIONTYP == UPDATE || ACTIONTYP == MPDELETE))
				{
				id = MPAPIselectEntry(_DIENSTLEISTUNG, glob_bez_dtg, (char *)&localdl,
				                     sizeof(localdl), sizeof(localdl.dlg_id));
				if (id == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				(void)sprintf(sqlquery, _SEL_DLGVIEW_DL, localdl.dlg_id, sprache, sqlordering);
				}
			break;

		case (unsigned char)_RESERVATION:
			(void)sprintf(sqlquery, _SEL_DLGVIEW_DL, dtg.dlg_id, sprache, sqlordering);
			break;

		case (unsigned char)_KONTINGENT:
			tdlhost_flag = (int)TRUE;
			(void)strcpy(sqlhoststring, _DLGPARTS_ONLYHOSTS);
			break;

		case (unsigned char)_OUTPUT:
			tdlhost_flag = (int)TRUE;
			(void)strcpy(sqlhoststring, _DLGPARTS_ONLYHOSTS);

/*!!! **** check here if akt_id is in akt_detail, if not bring all ***
			if (*glob_akt_out != (char)NULL )
				{
				id = MPAPIselectEntry(_AKTIONEN, glob_akt_out, (char *)&akt,
				                     sizeof(akt), sizeof(akt.akt_id));
				(void)sprintf(sqlquery, _SEL_DLGVIEW_AKTDET, akt.akt_id, sprache,
				              sqlordering);
				}
*********/

			break;

		case (unsigned char)_DLG_PART:
			if (FELDNR == (unsigned char)MDLG_DLGHOST)
				{
				tdlhost_flag = (int)TRUE;
				(void)strcpy(sqlhoststring, _DLGPARTS_ONLYHOSTS);
				}
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	/* check status */
	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == (char)NULL)
		{
		if (globA_ZEIT != _UNDEF && globE_ZEIT != _UNDEF)
			(void)sprintf(sqlquery, _SEL_DLGVIEW_AE, sqlhoststring, sprache,
			              globA_ZEIT, globE_ZEIT, sqlordering);
		else if (globA_ZEIT != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLGVIEW_A, sqlhoststring, sprache,
		                 globA_ZEIT, sqlordering);
		else if (globE_ZEIT != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLGVIEW_E, sqlhoststring, sprache,
		                 globE_ZEIT, sqlordering);
		else if (globDLAT.art_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLGVIEW_DLAT, sqlhoststring, sprache,
		                 globDLAT.art_id, sqlordering);
		else if (globSAI.sai_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLGVIEW_SAI, sqlhoststring,
		                 sprache, globSAI.sai_id, sqlordering);
		else
			(void)sprintf(sqlquery, _SEL_DLGVIEW, sqlhoststring,
			              sprache, sqlordering);
		}


	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_DLG_VIEW, &sqlmem.buffer, sqlquery,
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
			for ( i=0, buffer_ptr=buffer; i < *anzahl; i++ )
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_min  = (int)_UNDEF;
				DateTime.tm_hour = (int)_UNDEF;
				DateTime.tm_mday = (int)_UNDEF;
				DateTime.tm_mon  = (int)_UNDEF;
				DateTime.tm_year = (int)_UNDEF;

				Ptdlv = (DLG_VIEW *)&sqlmem.buffer[i*sizeof(DLG_VIEW)];
				Ptdlv->bez[_BEZLEN] = (char)NULL;
				buffersize = strlen(Ptdlv->bez);
				(void)memcpy((void *)buffer_ptr, (void *)Ptdlv->bez, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNER, TRENNERLEN);
				buffer_ptr += TRENNERLEN;

				(void)WriteDate(&DateTime, (time_t *)&Ptdlv->a_zeit, tmp_buffer);
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
int DLGchoose(int table, char *buffer)
{
	extern int sprache;
	extern DLG_PART			dlg;
	extern DIENST_ANGEBOT	dla;
	extern STATUS_WERTE		sta;
	extern KUN_VIEW			kunv;
	extern SAISON				sai;
	extern char glob_bez_dlg[];

	DLG_PART						hdlg;
	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	int	id;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDLG_DLGPART:
			(void)strcpy(glob_bez_dlg, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* DLG_PART  Teildienstleistung */
	if (MPAPIselectEntry(table, buffer, (char *)&dlg, sizeof(dlg),
		 sizeof(dlg.dl_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2);
	buffer1[strlen(buffer1)-1] = '\0';
	(void)strcpy(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* DLG_PART  Dienstleistung  Oberbegriff aller obigen Teil-DLs */
	id = MPAPIselectOneId((int)_DLG_PART, dlg.h_dl_id, (char *)&hdlg);
	if(id != (int)_UNDEF && SelectBez((int)_DLG_PART, sprache, hdlg.bez_id,
							bezeichnung) != (int)_UNDEF)
		{
		DateTime.tm_mday=(int)_UNDEF;
		DateTime.tm_mon =(int)_UNDEF;
		DateTime.tm_year=(int)_UNDEF;
		DateTime.tm_hour=(int)_UNDEF;
		DateTime.tm_min=(int)_UNDEF;

		(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, " => ");
		(void)WriteDate(&DateTime, (time_t *)&hdlg.a_zeit, bezeichnung);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* DIENST_ANGEBOT  Dienstleistungsangebot */
	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dlg.dla_id, (char *)&dla);
	if(id != (int)_UNDEF && SelectBez((int)_DIENST_ANGEBOT, sprache, dla.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* DATUM  Anfangszeit der Dienstleistung */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&dlg.a_zeit, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* _UNDEF  Endzeit der Dienstleistung */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&dlg.e_zeit, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Reservationsstatus */
	sta.typ=(int)_RES_F;
	id = MPAPIselectOneId((int)_STATUS_WERTE, dlg.res_f, (char *)&sta);
	if(id != (int)_UNDEF && SelectBez((int)_RES_F, sprache, sta.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Anbieter */
	id = KUNmkbez(dlg.kid, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Ertragskontonummer */
	(void)copyTextTo(bezeichnung, (char *)dlg.konto, (int)_CHAR10);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	id = SelFromTxt(dlg.textid,sprache, (int)_DLG_PART,buffer1);
	if	(id != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* SAISON */
	id = MPAPIselectOneId((int)_SAISON, (int)dlg.sai_id, (char *)&sai);
	if(id != (int)_UNDEF && SelectBez((int)_SAISON, sprache, sai.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KUNDEN  Rechnungsstelle */
	id = KUNmkbez(dlg.rechst, buffer1, (int)_RECORDLEN);
	if (id == (int)MPOK)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  CODE */
   (void)copyTextTo(bezeichnung, dlg.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
