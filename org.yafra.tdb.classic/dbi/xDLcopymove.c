/*D***********************************************************
 * Modul:     DBI - database insert/update/delete                           
 *            kopieren/bewegen von ganzen Dienstleistungen
 *            mit neuer Bezeichnungsvorgabe (flaggesteuert)
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 * Autor:     Administrator
 **************************************************************/
#include <mpsqlsel.h>
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f?r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xDLcopymove.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

static int DLexists(char *tdlbez, int newdat, int *id_that_exists );

int DLcopymove(DIENSTLEISTUNG *org_dl, char *newdat, int newbezflag )
{
	extern DIENSTLEISTUNG dtg;
	extern int sprache;
	extern char glob_bez_dtg[];

	DIENSTLEISTUNG new_dl;
	DLG_PART dlpart;
	DLG_PART hostdlpart;
	BEZEICHNUNG newbez;
	DLG_DLG *dl_dlpart = NULL;
	int status=MPOK;
	int cret=MPOK;
	int id;
	int i;
	int tdl_exists;
	int id_that_exists;
	int anzahl = 0;
	int dohostdlpart = TRUE;
	int datumsdiff = 0;
	int DtgSavepoint;
	unsigned long dlen = 0;
	unsigned long alen = 0;
	char message[RECLAENGE];
	char query[RECLAENGE];
	char bezstring[RECLAENGE];
	char *buffer_ptr;
	struct tm DateTime;

	/* DELETE Modus hat keine Kopier/Bewegungs - Funktion */
	if (ACTIONTYP == MPDELETE)
		return(MPNOP);

	/* wandle neues Datum von String zu time_t um und berechne Differenz */
	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	DateTime.tm_hour=(int)_UNDEF;
	DateTime.tm_min =(int)_UNDEF;
	(void)ReadDate(&DateTime, (time_t *)&new_dl.a_zeit, newdat);
	if (new_dl.a_zeit == org_dl->a_zeit)
		return(MPNOP);  /* Datum hat nicht ge?ndert */
	datumsdiff = (new_dl.a_zeit - org_dl->a_zeit);

	/* Neue DL schreiben */
	status = MPAPIdb_setsavepoint(&DtgSavepoint);
	new_dl.dlg_id = _UNDEF;
	new_dl.bez_id = org_dl->bez_id;
	new_dl.textid = org_dl->textid;
	new_dl.sai_id = org_dl->sai_id;
	new_dl.akt_id = org_dl->akt_id;
	newbez.s_id = (int)sprache;
	(void)copyTextTo(new_dl.code, org_dl->code, (int)_KRZLLEN);
	newbez.bez_id = SelectBez(_DIENSTLEISTUNG, sprache, new_dl.bez_id, bezstring);
	if (newbez.bez_id == (int)_UNDEF)
		return(MPNOP);

	newbez.typ = (int)_DIENSTLEISTUNG;
	if ( newbezflag == (int)TRUE )
		(void)sprintf( newbez.bez, "c_%s", bezstring );
	else
		(void)sprintf( newbez.bez, "%s", bezstring );
	status = MPAPIinsertEntry(_DIENSTLEISTUNG, (char *)&new_dl, &newbez);
	if (status != MPOK)
		return(MPNOP);

	/* init of host tdl id for parent of first tdl */
	hostdlpart.dl_id = (int)_UNDEF;

	/* Alte DL-Teile lesen und neue DL-Teile schreiben */
	(void)sprintf(query, _SEL_DLDLG, org_dl->dlg_id);
	status=MPAPIdb_sqlquery((int)_DLG_DLG, (char **)&dl_dlpart, query, &anzahl,
	                         &dlen, &alen);
	if (status != MPOK)
		{
		MPfree((char *)dl_dlpart);
		return(MPNOP);
		}
	for (i = 0; i < anzahl; i++)
		{
		id = MPAPIselectOneId(_DLG_PART, dl_dlpart[i].dl_id, (char *)&dlpart);
		if (id == (int)_UNDEF)
			{
			status = (int)MPERROR;
			break;
			}
		/* copy first the host DLPART if it's not a host by itself */
		if (dohostdlpart == TRUE && dlpart.h_dl_id != (int)_UNDEF)
			{
			id = MPAPIselectOneId(_DLG_PART, dlpart.h_dl_id, (char *)&hostdlpart);
			if (id == (int)_UNDEF)
				{
				status = (int)MPERROR;
				break;
				}
			hostdlpart.a_zeit += datumsdiff;
			hostdlpart.e_zeit += datumsdiff;
			hostdlpart.h_dl_id = (int)_UNDEF;  /* security aproach */
			hostdlpart.dl_id = (int)_UNDEF;
			newbez.s_id = (int)sprache;
			newbez.bez_id = SelectBez(_DLG_PART, sprache, hostdlpart.bez_id, bezstring);
			if (newbez.bez_id == (int)_UNDEF)
				break;

			tdl_exists = DLexists( bezstring, hostdlpart.a_zeit, &id_that_exists );
			if ( tdl_exists == (int)FALSE && id_that_exists == (int)_UNDEF )
			   {
				/*--- tdl existiert nicht, neu schreiben ---*/
				newbez.typ = (int)_DLG_PART;
				if ( newbezflag == (int)TRUE )
					(void)sprintf( newbez.bez, "c_%s", bezstring );
				else
					(void)sprintf( newbez.bez, "%s", bezstring );
				status = MPAPIinsertEntry(_DLG_PART, (char *)&hostdlpart, &newbez);
				if (status != MPOK)
					break;
			   }
			else if ( tdl_exists == (int)TRUE && id_that_exists != (int)_UNDEF )
			   {
				/*--- tdl existiert, nicht neu schreiben ---*/
				hostdlpart.dl_id = id_that_exists;
			   }
			dohostdlpart = FALSE;
			}
		dlpart.a_zeit += datumsdiff;
		dlpart.e_zeit += datumsdiff;
		dlpart.dl_id = (int)_UNDEF;
		dlpart.h_dl_id = hostdlpart.dl_id;
		newbez.s_id = (int)sprache;
		newbez.bez_id = SelectBez(_DLG_PART, sprache, dlpart.bez_id, bezstring);
		if (newbez.bez_id == (int)_UNDEF)
			break;

		tdl_exists = DLexists( bezstring, dlpart.a_zeit, &id_that_exists );
		if ( tdl_exists == (int)FALSE && id_that_exists == (int)_UNDEF )
		   {
			newbez.typ = (int)_DLG_PART;
			if ( newbezflag == (int)TRUE )
				(void)sprintf( newbez.bez, "c_%s", bezstring );
			else
				(void)sprintf( newbez.bez, "%s", bezstring );
			status = MPAPIinsertEntry(_DLG_PART, (char *)&dlpart, &newbez);
			if (status != MPOK)
				break;
		   }
		else if ( tdl_exists == (int)TRUE && id_that_exists != (int)_UNDEF )
		   {
			dlpart.dl_id = id_that_exists;
		   }
		dl_dlpart[i].dl_id = dlpart.dl_id;   /* setze jetzt neue DL ID      */
		dl_dlpart[i].dlg_id = new_dl.dlg_id;  /* setze jetzt neue DLGPART ID */
		}
	if (status == MPOK)
		{
		org_dl->dlg_id = new_dl.dlg_id;
		for (i = 0; i < anzahl; i++)
			{
			status = MPAPIinsertEntry(_DLG_DLG, (char *)&dl_dlpart[i], NULL);
			if (status != MPOK)
				break;
			}
		}

	if (MENUNR == (unsigned char)_DIENSTLEISTUNG && status == MPOK)
		{
		(void)memcpy((void *)&dtg, (void *)&new_dl, sizeof(DIENSTLEISTUNG));
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_min  = (int)_UNDEF;
		DateTime.tm_hour = (int)_UNDEF;
		DateTime.tm_mday = (int)_UNDEF;
		DateTime.tm_mon  = (int)_UNDEF;
		DateTime.tm_year = (int)_UNDEF;
		buffer_ptr = (char *)strstr(glob_bez_dtg, TRENNER);
		if (buffer_ptr == NULL)
			buffer_ptr = glob_bez_dtg;
		else
			buffer_ptr += (size_t)4;
		(void)WriteDate(&DateTime, (time_t *)&new_dl.a_zeit, buffer_ptr);
		(void)strcat(buffer_ptr, "\n");
		}

	/* Falls Fehler zur?ck zum savepoint */
	if (status != MPOK)
		cret = MPAPIdb_rollbacksavepoint(&DtgSavepoint);

	MPfree((char *)dl_dlpart);

	return(status);
}

/*F***********************************************************
 * Function:  check DLG_PART entry
 **************************************************************/
static int DLexists(char *tdlbez, int newdat, int *id_that_exists )
{
	DLG_PART dlpart;

	int status = FALSE;
	char tmp_bez1[_BEZLEN+1];
	char tmp_bez2[_BEZLEN+1];
	char tmp_bez3[RECLAENGE];
	struct tm DateTime;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	DateTime.tm_min  = (int)_UNDEF;
	DateTime.tm_hour = (int)_UNDEF;
	DateTime.tm_mday = (int)_UNDEF;
	DateTime.tm_mon  = (int)_UNDEF;
	DateTime.tm_year = (int)_UNDEF;
	
	(void)copyTextTo(tmp_bez1, (char *)tdlbez, (int)_BEZLEN);
	(void)WriteDate(&DateTime, (time_t *)&newdat, tmp_bez2);
	(void)sprintf(tmp_bez3, "c_%s%s%s", tmp_bez1, TRENNER, tmp_bez2);
	status = MPAPIselectEntry((int)_DLG_PART, tmp_bez3, (char *)&dlpart,
									  sizeof(DLG_PART), sizeof(dlpart.dl_id));
	if ( status == (int)_UNDEF )
	   {
		*id_that_exists = (int)_UNDEF;
		status = (int)FALSE;
	   }
	else
	   {
		*id_that_exists = dlpart.dl_id;
		status = (int)TRUE;
	   }

	return( status );
}
