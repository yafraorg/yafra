/*D***********************************************************
 * Modul:     DBI - database select                           
 *            date select for _DATUM fields
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDATselect.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

#define  DAT_DLG_MODE   (int)1
#define  DAT_PRE_MODE   (int)2
#define  DAT_ARR_MODE   (int)3
#define  E_DAT_DLG_MODE (int)4

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int DATUMselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern DIENST_TRAEGER globDLT;
	extern SAISON globSAI;
	extern char glob_dlt_bch[];
	extern int sprache;
	extern int *NewLevel[];

   DIENST_TRAEGER dlt;
   DLG_PART *dlg_ptr;
   PREIS *pre_ptr;
   struct tm DateTime;
	struct tm olddate;
	int i, old_dat;
	int status = (int)MPOK;
	int table_number;
	int mode;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;

	mode=(int)DAT_DLG_MODE;
	dlt.dlt_id = (int)_UNDEF;		/* lokaler DLT inaktiv setzten */

	switch ( MENUNR )
		{
		case (unsigned char)_GLOBALMENU:
			switch (FELDNR)
				{
				case	(unsigned char)12:
					mode = (int)E_DAT_DLG_MODE;
					break;

				default:
					mode = (int)DAT_DLG_MODE;
					break;
				}

		case (unsigned char)_BUCHUNG:
			mode = (int)DAT_ARR_MODE;
			table_number = (int)_DLG_PART;

			dlt.stufe = (int)1;
			if ( *glob_dlt_bch == NULL || ( dlt.dlt_id = MPAPIselectEntry( (int)_DIENST_TRAEGER, glob_dlt_bch,
				(char *)&dlt, sizeof( DIENST_TRAEGER ), sizeof( dlt.dlt_id ) ) ) == (int)_UNDEF )
				dlt.dlt_id = (int)_UNDEF;

			if ( dlt.dlt_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_DS_DATUM, dlt.dlt_id, globSAI.sai_id );
			else if ( dlt.dlt_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_D_DATUM, dlt.dlt_id );
			else if ( globDLT.dlt_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_DS_DATUM, globDLT.dlt_id, globSAI.sai_id );
			else if ( globDLT.dlt_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_D_DATUM, globDLT.dlt_id );
			else if ( globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_S_DATUM, globSAI.sai_id );
			else
				(void)sprintf( query, _SEL_ALL_DATUM );
			break;

		case (unsigned char)_DLG_PART:
		case (unsigned char)_DIENSTLEISTUNG:
			table_number = (int)_DLG_PART;
			if ( dlt.dlt_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_DS_DATUM, dlt.dlt_id, globSAI.sai_id );
			else if ( dlt.dlt_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_D_DATUM, dlt.dlt_id );
			else if ( globDLT.dlt_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_DS_DATUM, globDLT.dlt_id, globSAI.sai_id );
			else if ( globDLT.dlt_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_D_DATUM, globDLT.dlt_id );
			else if ( globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_S_DATUM, globSAI.sai_id );
			else
				(void)sprintf( query, _SEL_ALL_DATUM );
			break;

		case (unsigned char)_ARRANGEMENT:
			mode = (int)DAT_ARR_MODE;
			table_number = (int)_DLG_PART;
			if (globDLT.dlt_id != (int)_UNDEF && globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_DS_DATUM, globDLT.dlt_id, globSAI.sai_id );
			else if ( globDLT.dlt_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_D_DATUM, globDLT.dlt_id );
			else if (globSAI.sai_id != (int)_UNDEF )
				(void)sprintf( query, _SEL_S_DATUM, globSAI.sai_id );
			else
				(void)sprintf( query, _SEL_ALL_DATUM );
			break;

		case (unsigned char)_PREIS:
			table_number = (int)_PREIS;
			mode = (int)DAT_PRE_MODE;
			(void)sprintf( query, _SEL_P_DATUM );
			break;

		default:
			UtilMsg((int)MPE_PROTOCOL, MSGTYP_ERROR, NULL);
			(void)MPAPIdb_committrx();
			return((int)MPERROR);
			break;
		}

	status = MPAPIdb_sqlquery( table_number, &sqlmem.buffer, query, anzahl,
                            &sqlmem.datalen, &sqlmem.alloclen );
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
			{
			*len = (int)0;
			old_dat = (int)0;
			buffer_ptr = buffer;
			for (i=0; i < *anzahl; i++)
				{
				switch(mode)
					{
					case	(int)DAT_DLG_MODE :
					case	(int)E_DAT_DLG_MODE :
						dlg_ptr = (DLG_PART *)&sqlmem.buffer[i*sizeof(DLG_PART)];
						(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
						DateTime.tm_mday = (int)_UNDEF;
						DateTime.tm_mon  = (int)_UNDEF;
						DateTime.tm_year = (int)_UNDEF;
						DateTime.tm_hour = (int)_UNDEF;
						DateTime.tm_min  = (int)_UNDEF;
						if ( mode == (int)DAT_DLG_MODE )
							{
							if ( dlg_ptr->a_zeit == (int)_UNDEF || dlg_ptr->a_zeit == old_dat )
								continue;
							else
								{
								(void)WriteDate( &DateTime, (time_t *)&dlg_ptr->a_zeit, tmp_buffer );
								old_dat = dlg_ptr->a_zeit;
								}
							}
						else
							{
							if ( dlg_ptr->e_zeit == (int)_UNDEF || dlg_ptr->e_zeit == old_dat )
								continue;
							else
								{
								(void)WriteDate( &DateTime, (time_t *)&dlg_ptr->e_zeit, tmp_buffer );
								old_dat = dlg_ptr->e_zeit;
								}
							}
						break;

					case	(int)DAT_ARR_MODE :
						dlg_ptr = (DLG_PART *)&sqlmem.buffer[i*sizeof(DLG_PART)];
						(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
						DateTime.tm_mday = (int)_UNDEF;
						DateTime.tm_mon  = (int)_UNDEF;
						DateTime.tm_year = (int)_UNDEF;
						if (dlg_ptr->a_zeit == (int)_UNDEF)
							continue;
						else
							{
							(void)WriteDate(&DateTime, (time_t *)&dlg_ptr->a_zeit, tmp_buffer);
							if (DateTime.tm_mday == olddate.tm_mday && DateTime.tm_mon == olddate.tm_mon &&
							    DateTime.tm_year == olddate.tm_year)
								continue;
							else
								{
								olddate.tm_mday = DateTime.tm_mday;
								olddate.tm_mon = DateTime.tm_mon;
								olddate.tm_year = DateTime.tm_year;
								}
							}
						break;

					case	(int)DAT_PRE_MODE :
						pre_ptr = (PREIS *)&sqlmem.buffer[i*sizeof(PREIS)];
						(void)memset( (void *)&DateTime, NULL, sizeof(DateTime) );
						DateTime.tm_mday = (int)_UNDEF;
						DateTime.tm_mon  = (int)_UNDEF;
						DateTime.tm_year = (int)_UNDEF;
						if ( pre_ptr->glt == (int)_UNDEF || pre_ptr->glt == old_dat )
							continue;
						else
							{
							(void)WriteDate(&DateTime, (time_t *)&pre_ptr->glt, tmp_buffer);
							old_dat = pre_ptr->glt;
							}
						break;
					}	/* Ende switch ( mode ) */

				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;
				(void)memset( (void *)buffer_ptr, '\n', sizeof( char ) );
				buffer_ptr++;
				(void)memset( (void *)buffer_ptr, NULL, sizeof( char ) );
				}		/* Ende for Loop */
			}	/* Ende if *anzahl == 0 */
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
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	*len = (int)strlen( buffer );
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}
