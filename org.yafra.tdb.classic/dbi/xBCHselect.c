/*D***********************************************************
 * Modul:     DBI - database select                           
 *            BUCHUNG and BMMAIN
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xBCHselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

#define  BCH_MODE       (int)1
#define  BID_MODE       (int)2

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int BCHselect(long *len, char *buffer, int *anzahl)
{
	extern MP_PROFIL prof;
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char sqlquery[];
	extern REISENDER rei;
	extern KUNDEN kun;
	extern char glob_arr_bch[];

   ARRANGEMENT arr;
   BUCHUNG *bch_ptr;

	int i, id;
	int status = (int)MPOK;
	int mode;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char ordering[_QUERYLEN];
	char security[_QUERYLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	size_t buffersize;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* init of sqlquery string */
	sqlquery[0] = NULL;
	security[0] = NULL;
	strcpy(ordering, _ORDER_BCH_REF);
	mode = BCH_MODE;

	switch (prof.seclevel)
		{
		case _SECLEVEL_DBA:
			break;
		case _SECLEVEL_USER:
			(void)sprintf(security, _SEC_BCHST, prof.bchst);
			break;
		case _SECLEVEL_BOOKING:
		case _SECLEVEL_READONLY:
			(void)sprintf(security, _SEC_USERBCHST, prof.bchst, prof.mpuser);
			break;
		}

	switch (MENUNR)
		{
		case	(unsigned char)_BUCHUNG	:
			switch (FELDNR)
				{
				case MBCH_BCHNR:  /* falls Buchungsnummer gew�hlt */
					mode = BID_MODE;
					break;
				case MBCH_BCHHAUPT:
				case MBCH_BCHREF:
					mode = BCH_MODE;
					break;
				}

			if (mode == BID_MODE)
				strcpy(ordering, _ORDER_BCH_ID);

			/*--- Liste der Buchungen pro Kunde und Arrangement ---*/
			if (*to_buffers[MBCH_KUNRECH] != NULL && *to_buffers[MBCH_ARR] != NULL)
				{
				id = MPAPIselectEntry((int)_KUNDEN, to_buffers[MBCH_KUNRECH], (char *)&kun,
				     sizeof(rei), sizeof(kun.pers_id));
				if (id != (int)_UNDEF)
				   {
					id = MPAPIselectEntry((int)_ARRANGEMENT, to_buffers[MBCH_ARR],
												 (char *)&arr, sizeof(ARRANGEMENT), sizeof(arr.arr_id));
					if (id != (int)_UNDEF)
						(void)sprintf(sqlquery, _SEL_REF_BCH_ARRKUN, arr.arr_id, kun.pers_id,
										  security, ordering);
				   }
				}
			/*--- Liste der Buchungen pro Arrangement ---*/
			else if (*to_buffers[MBCH_ARR] != NULL )
				{
				id = MPAPIselectEntry((int)_ARRANGEMENT, to_buffers[MBCH_ARR],
				      (char *)&arr, sizeof(ARRANGEMENT), sizeof(arr.arr_id));
				if (id != (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_REF_BCH_ARR, arr.arr_id, security, ordering);
				}
			/*--- Liste der Buchungen pro Reisender ---*/
			else if (*to_buffers[MBCH_DLN] != NULL)
				{
				id = MPAPIselectEntry((int)_REISENDER, to_buffers[MBCH_DLN], (char *)&rei,
				     sizeof(rei), sizeof(rei.pers_id));
				if (id != (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_REF_BCH_DLN, rei.pers_id, security, ordering);
				}
			/*--- Liste der Buchungen pro Kunde Rechnungsstelle ---*/
			else if (*to_buffers[MBCH_KUNRECH] != NULL)
				{
				id = MPAPIselectEntry((int)_KUNDEN, to_buffers[MBCH_KUNRECH], (char *)&kun,
				     sizeof(rei), sizeof(kun.pers_id));
				if (id != (int)_UNDEF)
					(void)sprintf(sqlquery, _SEL_REF_BCH_KUN, kun.pers_id, security, ordering);
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
		if (mode == BID_MODE)
			strcpy(ordering, _ORDER_BCH_ID);
		(void)sprintf(sqlquery, _SEL_REF_BCH, security, ordering);
		}

	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_BUCHUNG, &sqlmem.buffer, sqlquery, anzahl,
	                          &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
			{
			if (sqlmem.alloclen > comm.alloclen)
				{
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
	                    DEFMEMCHUNK, sqlmem.alloclen, sizeof(char));
				buffer = comm.buffer; /* da buffer nur ein -> auf comm.buffer ist */
				}
			*len = (int)0;
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				bch_ptr=(BUCHUNG *)&sqlmem.buffer[i*sizeof(BUCHUNG)];
				if ( mode == (int)BID_MODE )
					(void)sprintf(tmp_buffer, "%04d", bch_ptr->bid);
				else if ( mode == (int)BCH_MODE )
					(void)copyTextTo(tmp_buffer, (char *)bch_ptr->ref, (int)_CHAR30);

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

