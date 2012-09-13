/*D***********************************************************
 * Modul:     DBI - database select
 *            Kunden - Buchungsstelle/Rechnungsstelle
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xKUNselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int KUNselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   PERSONEN *Ppers;
	MPV_KUNADR *Pkunadr;
	int i;
	int status = (int)MPOK;
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	char query[RECLAENGE];
	char message[RECLAENGE];
	size_t buffersize;
	int selecttable;

	selecttable = (int)_PERSONEN;

	switch (MENUNR)
		{

/*!!! ev. Einschraenken nach Kundentypen wie Buchungsstelle
		case (unsigned char)_BUCHUNG:
			switch (FELDNR)
				{
				case (unsigned char)MBCH_KUNBCHST:
					selecttable = (int)_KUNDEN_VIEW;
					(void)sprintf(query, _SEL_KUNVIEW_TYP, (int)_PERS_FIRMEN, (int)8);
					break;
				case (unsigned char)MBCH_KUNRECH:
					(void)sprintf(query, _SEL_KUNVIEW, (int)_PERS_FIRMEN);
					break;
				}
			break;
********/

		default:
			selecttable = (int)_MPV_KUNADR;
			(void)sprintf(query, _SEL_KUNADRVIEW );
			break;
		}

	status=MPAPIdb_sqlquery(selecttable, &sqlmem.buffer, query, anzahl,
		                         &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if (*anzahl > (int)0 )
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
				Pkunadr=(MPV_KUNADR *)&sqlmem.buffer[i*sizeof(MPV_KUNADR)];

				(void)sprintf(tmp_buffer, "%5d", Pkunadr->pers_id);
				buffersize = strlen(tmp_buffer);
				(void)memcpy((void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNERNORM, TRENNERNORMLEN);
				buffer_ptr += TRENNERNORMLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pkunadr->name, (int)_CHAR512);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNERNORM, TRENNERNORMLEN);
				buffer_ptr += TRENNERNORMLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pkunadr->plz, (int)_CHAR256);
				buffersize = strlen( tmp_buffer );
				(void)memcpy( (void *)buffer_ptr, (void *)tmp_buffer, buffersize+(size_t)1 );
				buffer_ptr += buffersize;

				(void)memcpy((void *)buffer_ptr, (void *)TRENNERNORM, TRENNERNORMLEN);
				buffer_ptr += TRENNERNORMLEN;

				(void)copyTextTo(tmp_buffer, (char *)Pkunadr->ort, (int)_CHAR256);
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

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int KUNchoose(int table, char *buffer)
{
	extern KUNDEN        kun;
	extern PERSONEN      pers;
   extern PERSADR     adr;
	extern KUNDEN_TYP		kunt;
	extern LAND				land;
	extern WAEHRUNG		whr;
	extern SPRACHEN		spr;
	extern STATUS_WERTE	sta;
	extern int sprache;

	char	bezeichnung[RECLAENGE];
	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	int	id;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen */
	switch(FELDNR)
		{
		case MKUN_NAME:
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* hole KUNDE mit Key Anrede f�r alle weiteren Aktionen */
	if (MPAPIselectEntry((int)_KUNDEN, buffer, (char *)&kun, sizeof(KUNDEN),
						sizeof(kun.pers_id)) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* vererbe Kunden ID von view an tables fuer KUNinput() */
	pers.pers_id = kun.pers_id;
	id = MPAPIselectOneId((int)_PERSONEN, kun.pers_id, (char *)&pers);
	id = MPAPIselectOneId((int)_PERSADR, kun.pers_id, (char *)&adr);

	/* _UNDEF  Kundennummer */
	/* _KUNDEN Kundenname */
	(void)copyTextTo(bezeichnung, pers.name, (int)_CHAR512);
	(void)sprintf(buffer, "%d\t%s\t", kun.pers_id, bezeichnung);

	/* _UNDEF  Ort */
	(void)copyTextTo(bezeichnung, adr.ort, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* KUNDEN_TYP */
	id = MPAPIselectOneId((int)_KUNDEN_TYP, (int)kun.k_typ_id, (char *)&kunt);
	if (id != (int)_UNDEF && SelectBez((int)_KUNDEN_TYP, sprache, kunt.bez_id,
	    bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* LAND */
	id = MPAPIselectOneId((int)_LAND, (int)adr.land_id, (char *)&land);
	if (id != (int)_UNDEF && SelectBez((int)_LAND, sprache, land.bez_id,
	    bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* WAEHRUNG */
	id = MPAPIselectOneId((int)_WAEHRUNG, (int)kun.whr_id, (char *)&whr);
	if (id != (int)_UNDEF && SelectBez((int)_WAEHRUNG, sprache, whr.bez_id,
	    bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* SPRACHE */
	id = MPAPIselectOneId((int)_SPRACHEN, (int)pers.s_id, (char *)&spr);
	if (id != (int)_UNDEF && SelectBez((int)_SPRACHEN, sprache, spr.bez_id,
	    bezeichnung) != (int)_UNDEF)
		(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Telefonnummer */
	(void)copyTextTo(bezeichnung, kun.tel, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Faxnummer */
	(void)copyTextTo(bezeichnung, kun.fax, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Telexnummer */
	(void)copyTextTo(bezeichnung, kun.tlx, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Kontonummer */
	(void)copyTextTo(bezeichnung, kun.konto, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Verantwortlicher */
   /*#4 with db redesign this is a key to PERSONEN, implemented only with TO 2000 */
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Kanton */
	(void)copyTextTo(bezeichnung, adr.kant, (int)_CHAR256);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Attribut1 */
	(void)copyTextTo(bezeichnung, kun.attr1, (int)_CHAR2000);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* UNDEF  Kunden Attribut2 */
	(void)copyTextTo(bezeichnung, kun.attr2, (int)_CHAR2000);
	(void)strcat(buffer, bezeichnung);
	(void)strcat(buffer, "\t");

	/* TEXTE */
	if (SelFromTxt(pers.textid, sprache, (int)_PERSONEN, buffer1) != (int)_UNDEF)
		(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");


	COMMTYP = SELECTITEM;
	return(MPOK);
}
