/*D***********************************************************
 * Modul:     DBI - database select
 *            Reisender - Dienstleistungsnehmer
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLNselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int DLNselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern BUCHUNG bch;
	extern REISENDER_TYP globDLNT;
	extern int sprache;
	extern int *NewLevel[];
	extern char sqlquery[];

	DLN_VIEW *Pdlnv;
	DLN_VIEW *dlntstptr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char sqlordering[_QUERYLEN];
	size_t buffersize;

	/* init of sqlquery string */
	sqlquery[0] = NULL;
	(void)strcpy(sqlordering, _ORDER_DLN_NAME);

	switch (MENUNR)
		{
		case (unsigned char)_BUCHUNG:
		case (unsigned char)_RESERVATION:
		case (unsigned char)_BMDLN:
			(void)strcpy(sqlordering, _ORDER_DLN_ID);
			break;

		default:
			/* do nothing and set the default sqlquery later */
			break;
		}

	/* check status */
	if (status != (int)MPOK)
		return(status);

	/* set default if sqlquery is NULL */
	if (*sqlquery == NULL)
		{
		if (bch.bid > 0)
			(void)sprintf(sqlquery, _SEL_DLNVIEW_BID, bch.bid, sqlordering);
		else if (globDLNT.rkr_id != (int)_UNDEF)
			(void)sprintf(sqlquery, _SEL_DLNVIEW_DLNT, globDLNT.rkr_id, sqlordering);
		else
			(void)sprintf(sqlquery, _SEL_DLNVIEW, sqlordering);
		}

	/* get the data and put it to the SELECT protocol */
	status=MPAPIdb_sqlquery((int)_DLN_VIEW, &sqlmem.buffer, sqlquery, anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	if (status == (int)MPOK)
		{
		if (*anzahl > (int)0 )
			{
			if (sqlmem.alloclen > comm.alloclen)
				{
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
	                    DEFMEMCHUNK, sqlmem.alloclen, sizeof(char));
				buffer = comm.buffer; /* da buffer nur ein -> auf comm.buffer ist */
				}
			dlntstptr = (DLN_VIEW *)sqlmem.buffer;
			*len = (int)0;
			for ( i=0, buffer_ptr = buffer; i < *anzahl; i++ )
				{
				Pdlnv = (DLN_VIEW *)&sqlmem.buffer[i*sizeof(DLN_VIEW)];

				(void)sprintf(tmp_buffer, "%5d", Pdlnv->dln_id);
				buffersize = strlen(tmp_buffer);
				(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNERNORM, TRENNERNORMLEN);
				buffer_ptr += TRENNERNORMLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pdlnv->name, (int)_CHAR512);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNERNORM, TRENNERNORMLEN);
				buffer_ptr += TRENNERNORMLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pdlnv->vor, (int)_CHAR512);
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
int DLNchoose(int table, char *buffer)
{
	extern int sprache;
	extern PERSONEN		pers;
	extern REISENDER		rei;
	extern DLN_VIEW		dlnv;
	extern STATUS_WERTE	sta;
	extern REISENDER_TYP	reit;
	extern SPRACHEN		spr;
	extern LAND				land;
	extern TEXTE			txt;

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char  *ptr;
	int	id;

	(void)memset( (void *)buffer1, NULL, sizeof(buffer1) );
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MDLN_NAM:
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* REISENDER (Name) */
	id = MPAPIselectEntry((int)_DLN_VIEW, buffer, (char *)&dlnv, sizeof(dlnv),
	                     sizeof(dlnv.dln_id));
	if (id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* vererbe DLN ID von view an tables fuer DLNinput() */
	rei.pers_id = pers.pers_id = dlnv.dln_id;
	pers.textid = dlnv.textid;

	/* _UNDEF  DLN-Nummer */
	ptr = buffer;
	(void)sprintf(ptr, "%d", dlnv.dln_id);
	ptr += strlen(buffer);
	*ptr = '\t';
	ptr++;

	/* _REISENDER Name */
	(void)copyTextTo(ptr, (char *)dlnv.name, (int)_CHAR512);
	ptr += strlen(ptr);
	*ptr = '\t';
	ptr++;

	/* _UNDEF  Reisender Vorname */
	(void)copyTextTo(ptr, (char *)dlnv.vor, (int)_CHAR512);
	ptr += strlen(ptr);
	*ptr = '\t';
	ptr++;

	/* _UNDEF  Reisender Ortschaft */
	(void)copyTextTo(ptr, (char *)dlnv.ort, (int)_CHAR256);
	ptr += strlen(ptr);
	*ptr = '\t';
	ptr++;

	/* REISENDER_TYP */
	id = MPAPIselectOneId((int)_REISENDER_TYP, (int)dlnv.rkr_id, (char *)&reit);
	if (id != (int)_UNDEF && SelectBez((int)_REISENDER_TYP, sprache, reit.bez_id, bezeichnung ) != (int)_UNDEF )
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  Geschlecht */
	sta.typ = (int)_SEX;
	id = MPAPIselectOneId((int)_STATUS_WERTE, dlnv.sex, (char *)&sta);
	if (id != (int)_UNDEF && SelectBez((int)_SEX, sprache, sta.bez_id, bezeichnung ) != (int)_UNDEF )
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* SPRACHEN */
	id = MPAPIselectOneId((int)_SPRACHEN, (int)dlnv.s_id, (char *)&spr);
	if (id != (int)_UNDEF && SelectBez((int)_SPRACHEN, sprache, spr.bez_id,
		bezeichnung ) != (int)_UNDEF )
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* LAND */
	id = MPAPIselectOneId((int)_LAND, (int)dlnv.land_id, (char *)&land);
	if (id != (int)_UNDEF && SelectBez((int)_LAND, sprache, land.bez_id,
		bezeichnung ) != (int)_UNDEF )
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Alter */
	(void)copyTextTo(bezeichnung, dlnv.age, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Passnummer */
	(void)copyTextTo(bezeichnung, dlnv.passnr, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Attribut 1 */
	(void)copyTextTo(bezeichnung, dlnv.attr1, (int)_CHAR2000);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Attribut 2 */
	(void)copyTextTo(bezeichnung, dlnv.attr2, (int)_CHAR2000);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE intern */
	if (SelFromTxt(dlnv.textid, sprache, (int)_PERSONEN, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	/* TEXTE extern */
	if ( SelFromTxt(dlnv.ext_txt, sprache, (int)_REISENDER, buffer1) != (int)_UNDEF )
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
