/*D***********************************************************
 * Modul:     DBI - database select                           
 *            Arrangement
 *                                                            
 * Copyright: yafra.org, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xARRselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int ARRselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern unsigned char alphaordering;
	extern char sqlquery[];

	extern DIENSTLEISTUNG dtg;
	extern PROGRAMM globPRG;
	extern SAISON globSAI;
	extern int globA_ZEIT;
	extern int globE_ZEIT;

	ARR_VIEW *Parrv;
   struct tm DateTime;
	int i;
	int status = (int)MPOK;
	int bchdat;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char *to_buffers[MAX_MENU_ITEMS];
	char sqlordering[_QUERYLEN];
	size_t buffersize;

	/* set ordering string for SQL query */
	if (alphaordering == (unsigned char)TRUE)
		(void)strcpy(sqlordering, _ORDER_ARR_DAT);
	else
		(void)strcpy(sqlordering, _ORDER_ARR_BEZ);

	/* init of sqlquery string */
	sqlquery[0] = NULL;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	switch(MENUNR)
		{
		case (unsigned char)_BUCHUNG:
			if (*to_buffers[MBCH_DL] != NULL && ((MPAPIselectEntry((int)_DIENSTLEISTUNG,
			    to_buffers[MBCH_DL], (char *)&dtg, sizeof(dtg),
			    sizeof(dtg.dlg_id))) != (int)_UNDEF))
				{
				(void)sprintf(sqlquery, _SEL_ARRVIEW_DL, dtg.dlg_id, sprache,
				              sqlordering);
				}
			else if (*to_buffers[MBCH_DAT] != NULL)
				{
				(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				ReadDate(&DateTime, (time_t *)&bchdat, to_buffers[MBCH_DAT]);
				(void)sprintf(sqlquery, _SEL_ARRVIEW_AE, sprache,
				     (bchdat - _DATERANGE), (bchdat + _DATERANGE), sqlordering);
				}
			break;

		case (unsigned char)_ARRANGEMENT:
			if (*to_buffers[MARR_DL] != NULL && ((MPAPIselectEntry((int)_DIENSTLEISTUNG,
			    to_buffers[MARR_DL], (char *)&dtg, sizeof(dtg),
			    sizeof(dtg.dlg_id))) != (int)_UNDEF))
				{
				(void)sprintf(sqlquery, _SEL_ARRVIEW_DL, dtg.dlg_id, sprache,
				              sqlordering);
				}
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
		{
		if (globA_ZEIT != _UNDEF && globE_ZEIT != _UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_AE, sprache,
			              globA_ZEIT, globE_ZEIT, sqlordering);
		else if (globPRG.prg_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_PRG_SAI, sprache, globPRG.prg_id,
			              globSAI.sai_id, sqlordering);
		else if (globA_ZEIT != _UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_AE, sprache,
			              (globA_ZEIT - _DATERANGE), (globA_ZEIT + _DATERANGE), sqlordering);
		else if (globE_ZEIT != _UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_AE, sprache,
			              (globE_ZEIT - _DATERANGE), (globE_ZEIT + _DATERANGE), sqlordering);
		else if (globPRG.prg_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_PRG, sprache, globPRG.prg_id,
			              sqlordering);
		else if (globSAI.sai_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_ARRVIEW_SAI, sprache, globSAI.sai_id,
			              sqlordering);
		else
			(void)sprintf(sqlquery, _SEL_ARRVIEW, sprache, sqlordering);
		}


	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_ARR_VIEW, &sqlmem.buffer, sqlquery,
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
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				Parrv = (ARR_VIEW *)&sqlmem.buffer[i*sizeof(ARR_VIEW)];
				Parrv->bez[_BEZLEN] = (char)NULL;
				buffersize = strlen(Parrv->bez);
				(void)memcpy( (void *)buffer_ptr, (void *)Parrv->bez, buffersize+(size_t)1);
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNER, TRENNERLEN);
				buffer_ptr += TRENNERLEN;

				(void)WriteDate(&DateTime, (time_t *)&Parrv->a_dat, tmp_buffer);
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
			if ( MENUNR == NewLevel[MENUNR][FELDNR] )
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
int ARRchoose(int table, char *buffer)
{
	extern int					sprache;
	extern ARRANGEMENT		arr;
	extern ARR_DLG				ad;
	extern DIENSTLEISTUNG	dtg;
	extern PROGRAMM			prg;
	extern STATUS_WERTE		sta;
	extern char glob_bez_arr[];
	extern char glob_dtg_arr[];	/* gew�hlte Dienstleistung auf Arr */

	struct tm DateTime;
	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char  dlbez[_BEZLEN+1];
	char  priobuf[6];
	char  teilbuf[6];
	char *ptr;
	int	id, state;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MARR_ARR:
			(void)strcpy(glob_bez_arr, buffer);
			break;
		case MARR_DTG:  /* DIENSTLEISTUNG */
			(void)strcpy(glob_dtg_arr, buffer);
			if (*glob_bez_arr == NULL)
				return(MPOK);
			else
				if (ACTIONTYP != (unsigned char)INSERT)
					(void)strcpy(buffer, glob_bez_arr);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* ARRANGEMENT */
	state = MPAPIselectEntry(table, buffer, (char *)&arr, sizeof(arr), sizeof(arr.arr_id));
	if (state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	ad.arr_id = arr.arr_id;
	(void)sscanf(buffer, "%[^=]%*3c%31c", buffer1, buffer2);
	buffer1[strlen(buffer1)-1] = '\0';
	(void)strcpy(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* DATUM   beginn des Arrangements */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&arr.a_dat, bezeichnung);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* PROGRAMM   Typ des Arrangements */
	id = MPAPIselectOneId((int)_PROGRAMM, (int)arr.prg_id, (char *)&prg);
	if(id != (int)_UNDEF && SelectBez((int)_PROGRAMM, sprache, prg.bez_id,
							bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* nur falls DIENSTLEISTUNG bekannt */
	if (*glob_dtg_arr != NULL)
		{
		sscanf(glob_dtg_arr, "%4c%4c", teilbuf, priobuf);
		teilbuf[4] = NULL;
		priobuf[4] = NULL;
		ad.teil = atoi(teilbuf);
		ad.prio = atoi(priobuf);
		if (ad.teil == 0 || ad.prio == 0)
			{
			(void)strcat(buffer, "\t");               /* STATUS_WERTE Priorit�t */
			state = SelFromTxt(arr.textid, sprache,
		         	(int)_ARRANGEMENT, buffer1); 		/* TEXTE */
			if (state != (int)_UNDEF)
				(void)strcat(buffer, buffer1);
			(void)strcat(buffer, "\t");
			(void)strcat(buffer, "\t");               /* DIENSTLEISTUNG */
			(void)strcat(buffer, "\t");               /* UNDEF Teilst�cknr */
	      /* UNDEF  CODE */
	      (void)copyTextTo(bezeichnung, arr.code, (int)_KRZLLEN);
	      (void)strcat(buffer, bezeichnung);
	      (void)strcat(buffer, "\t");
			COMMTYP = SELECTITEM;
			return(MPOK);
			}
		ptr = strchr(glob_dtg_arr, ':');
		ptr++;
		(void)strcpy(dlbez, ptr);
		(void)strcpy(glob_dtg_arr, dlbez);

		/* hole DIENSTLEISTUNG Daten */
		dtg.a_zeit = (int)_UNDEF;
		state = MPAPIselectEntry((int)_DIENSTLEISTUNG, dlbez, (char *)&dtg, sizeof(dtg), sizeof(dtg.dlg_id));
		if (state == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		ad.dlg_id = dtg.dlg_id;

		/* get ARR_DLG for input procedure */
		state = MPAPIselectOneId((int)_ARR_DLG, ad.arr_id, (char *)&ad);
		if (state == (int)_UNDEF)
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}

		/* STATUS_WERTE  Priorit�t */
		sta.typ = (int)_PRIO;
		id = MPAPIselectOneId((int)_STATUS_WERTE, ad.prio, (char *)&sta);
		if (id != (int)_UNDEF && SelectBez((int)_PRIO, sprache, sta.bez_id,
							bezeichnung) != (int)_UNDEF)
			(void)strcat(buffer, bezeichnung);
		(void)strcat(buffer, "\t");

		/* TEXTE */
		state = SelFromTxt(arr.textid, sprache, (int)_ARRANGEMENT, buffer1); 
		if (state != (int)_UNDEF)
			(void)strcat(buffer, buffer1);
		(void)strcat(buffer, "\t");

		/* DIENSTLEISTUNG */
		if(dtg.a_zeit != (int)_UNDEF)
			(void)strcat(buffer, dlbez);
		(void)strcat(buffer, "\t");

		/* UNDEF  Teilst�cknummer */
		if (ad.teil > (int)0)
			{
			sprintf(bezeichnung, "%d", ad.teil);
			(void)strcat(buffer, bezeichnung);
			}
		(void)strcat(buffer, "\t");
		}
	else
		{
		(void)strcat(buffer, "\t");               /* STATUS_WERTE Priorit�t */
		state = SelFromTxt(arr.textid, sprache,
		         (int)_ARRANGEMENT, buffer1); 		/* TEXTE */
		if (state != (int)_UNDEF)
			(void)strcat(buffer, buffer1);
		(void)strcat(buffer, "\t");
		(void)strcat(buffer, "\t");               /* DIENSTLEISTUNG */
		(void)strcat(buffer, "\t");               /* UNDEF Teilst�cknr */
		}

	/* UNDEF  CODE */
   (void)copyTextTo(bezeichnung, arr.code, (int)_KRZLLEN);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
