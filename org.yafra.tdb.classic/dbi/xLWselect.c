/*D***********************************************************
 * Modul:     DBI - database select                           
 *            W�hrung
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xLWselect.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

/*F***********************************************************
 * Function:  Select                                         
 *************************************************************/
int LWselect(long *len, char *buffer, int *anzahl)
{
	int status = (int)MPOK;

	buffer[0] = NULL;
	return(status);
}


/*F***********************************************************
 * Function:  Choose                                         
 *************************************************************/
int LWchoose(int table, char *buffer)
{
	extern int      sprache;
	extern WAEHRUNG whr;
	extern LAND land;
	extern STATUS_WERTE sta;
	extern LAND_WHR lw;
	extern char glob_lw_land[];
	extern char glob_lw_whr[];
	extern char glob_lw_kurstyp[];

	struct tm DateTime;
	char kursstring[_BEZLEN];
	int id;

	(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MLW_LAND:
			(void)strcpy(glob_lw_land, buffer);
			break;
		case MLW_WHR:
			(void)strcpy(glob_lw_whr, buffer);
			break;
		case MLW_KURSTYP:
			(void)strcpy(glob_lw_kurstyp, buffer);
			break;
		default:
			return(MPOK);
			break;
		}
	/* check statics if we can get an entry */
	if (*glob_lw_land == NULL || *glob_lw_whr == NULL ||
	    *glob_lw_kurstyp == NULL)
		return(MPOK); /* we can't get an entry, so return to menu */

	/* Falls im INSERT Modus nicht mehr weiter suchen   Output: 1 Feld */
	if (ACTIONTYP == INSERT)
		return(MPOK);

	/* F�lle das Menu so viel wie m�glich               Output: 1 Menu */

	/* LAND */
	if (MPAPIselectEntry((int)_LAND, glob_lw_land, (char *)&land, sizeof(land),
		 sizeof(land.land_id)) == (int)_UNDEF)
		{
		glob_lw_land[0] = NULL;
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	lw.land_id = land.land_id;
	(void)strcpy(buffer, glob_lw_land);
	(void)strcat(buffer, "\t");

	/* WAEHRUNG */
	if (MPAPIselectEntry((int)_WAEHRUNG, glob_lw_whr, (char *)&whr, sizeof(whr),
		 sizeof(whr.whr_id)) == (int)_UNDEF)
		{
		glob_lw_whr[0] = NULL;
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	lw.whr_id = whr.whr_id;
	(void)strcat(buffer, glob_lw_whr);
	(void)strcat(buffer, "\t");

	/* STATUS_WERTE  _KURSTYP */
	sta.typ = (int)_KURSTYP;
	if (getAttribut((int)_KURSTYP, glob_lw_kurstyp) != (int)MPOK)
		{
		glob_lw_kurstyp[0] = NULL;
		UtilMsg((int)MPE_NOSTA, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	lw.kurs_typ = sta.sta_id;
	(void)strcat(buffer, glob_lw_kurstyp);
	(void)strcat(buffer, "\t");

	id = MPAPIselectOneId((int)_LAND_WHR, land.land_id, (char *)&lw);
	if (id == (int)_UNDEF)
		{
/*!!! new msg */
		UtilMsg((int)MPE_NOWHR, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* _UNDEF  Ankaufskurs */
	(void)sprintf(kursstring, "%f", lw.a_kurs);
	(void)strcat(buffer, kursstring);
	(void)strcat(buffer, "\t");

	/* _UNDEF  Verkaufskurs */
	(void)sprintf(kursstring, "%f", lw.v_kurs);
	(void)strcat(buffer, kursstring);
	(void)strcat(buffer, "\t");

	/* DATUM   Kurs g�ltig ab */
	DateTime.tm_mday=(int)_UNDEF;
	DateTime.tm_mon =(int)_UNDEF;
	DateTime.tm_year=(int)_UNDEF;
	(void)WriteDate(&DateTime, (time_t *)&lw.von_dat, kursstring);
	(void)strcat(buffer, kursstring);
	(void)strcat(buffer, "\t");

	COMMTYP = SELECTITEM;
	return(MPOK);
}
