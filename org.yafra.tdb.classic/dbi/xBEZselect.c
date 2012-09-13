/*D***********************************************************
 * Modul:     DBI - database select
 *            Bezeichnungen
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xBEZselect.c,v 1.3 2009-01-02 16:51:34 mwn Exp $";

/*F***********************************************************
 * Function:  Select
 *************************************************************/
int BEZselect(long *len, char *buffer, int *anzahl)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];
	extern char sqlquery[];
	extern SPRACHEN spr;

	extern int glob_typ_bez;
	extern int glob_spr_bez;

   BEZEICHNUNG *bez_ptr;
	BEZEICHNUNG typbez;
	int i;
	int status = (int)MPOK;
	char *to_buffers[MAX_MENU_ITEMS];
	char *buffer_ptr;
	char tmp_buffer[RECLAENGE];
	size_t buffersize;

	/* init of sqlquery string */
	sqlquery[0] = NULL;

	glob_spr_bez = (int)_UNDEF;
	glob_typ_bez = (int)_UNDEF;

	/* get menu strings */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	if (MENUNR == (unsigned char)_BEZEICHNUNG)
		{
		switch(FELDNR)
			{
			case MBEZ_BEZTYP: /* hole alle Bezeichnungstypen */
				if (*to_buffers[MBEZ_SPR] == NULL)
					{
					UtilMsg((int)MPE_NOSPR, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				else
					{
					spr.s_id = MPAPIselectEntry((int)_SPRACHEN, to_buffers[MBEZ_SPR],
					           (char *)&spr, sizeof(SPRACHEN), sizeof(spr.s_id));
					(void)sprintf(sqlquery, _SEL_BEZ_BEZ, _TYPENBEZID, spr.s_id);
					}
				break;
			case MBEZ_BEZ:    /* hole alle Bezeichnungen eines Typs */
				if (*to_buffers[MBEZ_SPR] == NULL || *to_buffers[MBEZ_BEZTYP] == NULL)
					{
					UtilMsg((int)MPE_NOSPR, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				else
					{
					spr.s_id = MPAPIselectEntry((int)_SPRACHEN, to_buffers[MBEZ_SPR],
					           (char *)&spr, sizeof(SPRACHEN), sizeof(spr.s_id));
					typbez.s_id = spr.s_id;
					typbez.typ  = (int)_UNDEF;
					(void)strcpy(typbez.bez, to_buffers[MBEZ_BEZTYP]);
					typbez.bez_id = MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MBEZ_BEZTYP],
					      (char *)&typbez, sizeof(BEZEICHNUNG), sizeof(typbez.bez_id));
					(void)sprintf(sqlquery, _SEL_BEZ_BEZ_TYP, spr.s_id, typbez.typ);

					glob_spr_bez = spr.s_id;
					glob_typ_bez = typbez.typ;
					}
				break;
			default:
				UtilMsg((int)MPE_NOSPR, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				break;
			}
		}
	else
		(void)sprintf(sqlquery, _SEL_BEZ_BEZ, _TYPENBEZID, sprache);

	UtilSplitFreeMenubuffer(to_buffers);

	if (status != (int)MPOK)
		return(status);

	status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, sqlquery, anzahl,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( *anzahl > (int)0 )
			{
			*len = (int)0;
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
		else /* Fehler: keine Daten gefunden */
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

	*len = (int)strlen(buffer);
	if (*anzahl == 1)
		buffer[(*len - 1)] = NULL;
	return( status );
}

/*F***********************************************************
 * Function:  Choose
 *************************************************************/
int BEZchoose(int table, char *buffer)
{
	extern int sprache;
	extern BEZEICHNUNG	bez;
	extern SPRACHEN		spr;

	extern int glob_typ_bez;
	extern int glob_spr_bez;

	BEZEICHNUNG				tmpbez;
	char	buffer1[RECLAENGE];
	char	message[RECLAENGE];
	int status = (int)MPOK;
	char  bezstring[_BEZLEN];

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	COMMTYP = CHOOSE;

	/* Einschr�nkungen �berpr�fen */
	switch(FELDNR)
		{
		case MBEZ_BEZ:
			strcpy(buffer1, buffer);
			break;
		default:
			return(MPOK);
			break;
		}

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* SPRACHEN */
	if (MPAPIselectOneId((int)_SPRACHEN, glob_spr_bez, (char *)&spr) != (int)_UNDEF)
		{
		if (SelectBez((int)_SPRACHEN, glob_spr_bez, spr.bez_id, bezstring) != (int)_UNDEF)
			(void)strcpy(buffer, bezstring);
		else
			{
			UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
			return((int)MPERROR);
			}
		}
	else
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, "\t");

	/* BEZEICHNUNG  Bezeichnungstyp  BEZ_ID = 0 */
	if (SelectBez(glob_typ_bez, glob_spr_bez, (int)_TYPENBEZID, bezstring) == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, bezstring);
	(void)strcat(buffer, "\t");

	/* BEZEICHNUNG  Bezeichnung */
	(void)strcat(buffer, buffer1);
	(void)strcat(buffer, "\t");

	(void)strcat(buffer, "\t");  /* SPRACHEN Uebersetzungssprache     */
	(void)strcat(buffer, "\t");  /* UNDEF    Uebersetzungsbezeichnung */

	bez.typ=glob_typ_bez;	bez.s_id=spr.s_id;

	COMMTYP = SELECTITEM;
	return(MPOK);
}
