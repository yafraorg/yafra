/*D***********************************************************
 * Modul:     DBI - database select
 *            Statuswerte
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xSTAselect.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int STAselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern KOMMISSION kom;
	extern int glob_typ_sta;
	extern int sprache;
	extern int *NewLevel[];
	extern char glob_satztyp_kom[];
	extern char sqlquery[];

   BEZEICHNUNG *bez_ptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;


	/* Dort wo nur 1 Statuswert im Menu ist braucht es keine weitere
	 * Abfrage auf FELDNR !
	 */

	switch (MENUNR)
		{
		case (unsigned char)_STATUS_WERTE:
			switch (FELDNR)
				{
				case (unsigned char)MSTA_BEZ:
					if (glob_typ_sta == (int)_UNDEF)
						/* alle Statuswerte */
						(void)sprintf( sqlquery, _SEL_BEZ_STA_SEL, sprache );
					else
						/* alle Statuswerte eines Typs */
						(void)sprintf( sqlquery, _SEL_BEZ_ONE_TYP, sprache, glob_typ_sta );
					break;
				case (unsigned char)MSTA_TYP:
					/* alle Status Typen die mutiert werden d�rfen */
					(void)sprintf( sqlquery, _SEL_BEZ_STA_NAM, sprache );
					break;
				}
			break;

		case (unsigned char)_BEZEICHNUNG:
			(void)sprintf( sqlquery, _SEL_BEZ_STA_ALL, _TYPENBEZID, sprache );
			break;

		case (unsigned char)_ORT:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_STA_ORT, (int)_STA_ORT );
			break;

		case (unsigned char)_MSG:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_MSGTYP, (int)_MSGTYP );
			break;

		case (unsigned char)_AKTIONEN:
			switch (FELDNR)
				{
				case (unsigned char)MAKT_STAAUS:
					(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_A_FLG, (int)_A_FLG );
					break;

				case (unsigned char)MAKT_STAINRES:
				case (unsigned char)MAKT_STAOUTRES:
					(void)sprintf( sqlquery, _SEL_BEZ_STA_ORDSTA, sprache, (int)_R_STA, (int)_R_STA );
					break;

				case (unsigned char)MAKT_STADEV:
					(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_DEVICE, (int)_DEVICE);
					break;
				}
			break;

		case (unsigned char)_ARRANGEMENT:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_PRIO, (int)_PRIO );
			break;

		case (unsigned char)_DLG_PART:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_RES_F, (int)_RES_F );
			break;

		case (unsigned char)_KATEGORIE:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_GA, (int)_GA );
			break;

		case (unsigned char)_LAND_WHR:
			(void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_KURSTYP, (int)_KURSTYP);
			break;

		case (unsigned char)_DIENST_TRAEGER:
			(void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_DLTSTA, (int)_DLTSTA);
			break;

		case (unsigned char)_KONT_DETAIL:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_U_FAK, (int)_U_FAK );
			break;

		case (unsigned char)_RESERVATION:
			(void)sprintf(sqlquery, _SEL_BEZ_STA_ORDSTA, sprache, (int)_R_STA, (int)_R_STA);
			break;

		case (unsigned char)_BUCHUNG:
			(void)sprintf(sqlquery, _SEL_BEZ_STA_ORDSTA, sprache, (int)_BSTA, (int)_BSTA);
			break;

		case	(unsigned char)_REISENDER:
			(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_SEX, (int)_SEX );
			break;

		case (unsigned char)_PERSADR:
			switch (FELDNR)
				{
				case (unsigned char)MADR_STA:
			      (void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_ADRSTA, (int)_ADRSTA);
					break;
				}
			break;

		case (unsigned char)_OUTPUT:
			switch (FELDNR)
				{
				case (unsigned char)MOUT_STAINRES:
				case (unsigned char)MOUT_STAOUTRES:
					(void)sprintf( sqlquery, _SEL_BEZ_STA_ORDSTA, sprache, (int)_R_STA, (int)_R_STA );
					break;

				case (unsigned char)MOUT_DEV:
					(void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_DEVICE, (int)_DEVICE);
					break;
				}
			break;

		case (unsigned char)_KOMMISSION:
			switch (FELDNR)
				{
				case (unsigned char)MKOM_TYP:
					(void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_KOMMTYP, (int)_KOMMTYP);
					break;
				case (unsigned char)MKOM_SATZTYP:
					(void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_SATZTYP, (int)_SATZTYP );
					break;
				}
			break;

		case (unsigned char)_PREIS:
			switch (FELDNR)
				{
				case (unsigned char)MPRE_STA:
			      (void)sprintf(sqlquery, _SEL_BEZ_STA, sprache, (int)_PREISSTA, (int)_PREISSTA);
					break;
				case (unsigned char)MPRE_UNITTYP:
			      (void)sprintf( sqlquery, _SEL_BEZ_STA, sprache, (int)_STA_UNIT, (int)_STA_UNIT );
					break;
				}
			break;

		}


	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery,
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
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
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
int STAchoose(int table, char *buffer)
{
	extern int sprache;
	extern STATUS_WERTE		sta;
	extern STATUS_WERTE		sta_old;
	extern BEZEICHNUNG		bez;
	extern char glob_typbez_sta[];
	extern int glob_typ_sta;

	BEZEICHNUNG					tmpbez;
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char	message[RECLAENGE];
	char dbbuffer[RECLAENGE];

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	/* feldspezifischen Einschr�nkungen */
	switch(FELDNR)
		{
		case MSTA_BEZ:
			break;
		case MSTA_TYP:
			tmpbez.s_id=(int)sprache;
			tmpbez.typ = (int)_NAMEN;
			(void)strcpy(tmpbez.bez, buffer);
			(void)strcpy(glob_typbez_sta, buffer);
			if ( *buffer != NULL && MPAPIselectEntry((int)_BEZEICHNUNG, buffer, (char *)&tmpbez,
						sizeof(BEZEICHNUNG), sizeof(tmpbez.bez_id) ) != (int)_UNDEF )
				glob_typ_sta = tmpbez.typ;
			else
				glob_typ_sta = (int)_UNDEF;
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

	/* STATUS_WERTE  Bezeichnung */
	strcpy(dbbuffer, buffer);
	(void)ConvertSpecialChar(dbbuffer, NULL);
	sta.typ=glob_typ_sta;
	if (getAttribut((int)sta.typ, dbbuffer) != (int)MPOK)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* UNDEF  Abk�rzung */
	(void)copyTextTo(buffer1, sta.abk, (int)_CHAR39);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Wert / Inhalt / Code */
	(void)copyTextTo(buffer1, sta.sta, (int)_CHAR39);
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* UNDEF  Konditionen */
	(void)sprintf(buffer2, "%f", sta.kond);
	(void)strcat(buffer, buffer2);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Typ */
	(void)strcat(buffer, glob_typbez_sta);
	(void)strcat(buffer, "\t");

	(void)memcpy((void *)&sta_old, (void *)&sta, sizeof(sta));	/* f�r Update */

	COMMTYP = SELECTITEM;
	return(MPOK);
}
