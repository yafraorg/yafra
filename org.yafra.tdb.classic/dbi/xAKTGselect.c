/**************************************************************/
/* Modul:     DBI - database select                           */
/*            Aktionsgruppen                                  */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/dbi/xAKTGselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $

 Log Information:
 $Log: xAKTGselect.c,v $
 Revision 1.2  2008-11-02 19:55:38  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:42  mwn
 inital release

 Revision 3.1  1997/04/02 07:00:34  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/04/05 21:34:34  mw
 update to new DB release 2.0

 * Revision 1.2  94/02/16  16:14:04  16:14:04  mw (Administrator)
 * update headerfilenames for dos
 * 
 * Revision 1.1  94/02/10  10:18:18  10:18:18  mw (Administrator)
 * Initial revision
 * 
*/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTGselect.c,v 1.2 2008-11-02 19:55:38 mwn Exp $";

/**************************************************************/
/* Function:  Select                                          */
/**************************************************************/
int AKTGselect(long *len, char *buffer, int *anzahl)
{
	int status = (int)MPOK;

	buffer[0] = NULL;

	*len = (int)strlen(buffer);

	return(status);
}


/**************************************************************/
/* Function:  Choose                                          */
/**************************************************************/
int AKTGchoose(int table, char *buffer)
{
	extern int				sprache;
	extern AKTIONEN		akt;
	extern AKTIONSGRP    aktgrp;
	extern char glob_parent_aktg[];
	extern char glob_child_aktg[];

	AKTIONEN					hakt;
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char	bezeichnung[RECLAENGE];
	int	id;
	int   state;

	/* Buffer init */

	aktgrp.ord = (int)_UNDEF; /*!!!! delete this if everything is done */

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MAKTG_HAKT:
			(void)strcpy(glob_parent_aktg, buffer);
			if (*glob_child_aktg == NULL)
				return(MPOK);
			break;
		case MAKTG_AKT:
			(void)strcpy(glob_child_aktg, buffer);
			if (*glob_parent_aktg == NULL)
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

	/* HOST AKTION */
	state = MPAPIselectEntry((int)_AKTIONEN, glob_parent_aktg, (char *)&akt,
	        sizeof(akt), sizeof(akt.akt_id));
	if (state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcpy(buffer, glob_parent_aktg);
	(void)strcat(buffer, "\t");
	aktgrp.parentakt = akt.akt_id;

	/* CHILD AKTION */
	state = MPAPIselectEntry((int)_AKTIONEN, glob_child_aktg, (char *)&akt,
	            sizeof(akt), sizeof(akt.akt_id));
	if (state == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}
	(void)strcat(buffer, glob_child_aktg);
	(void)strcat(buffer, "\t");
	aktgrp.childakt = akt.akt_id;

	/*!!! get here the best AKTIONSGRP entry */

	/* UNDEF Reihenfolge */
	if (aktgrp.ord != (int)_UNDEF)
		{
		(void)sprintf(bezeichnung, "%d", aktgrp.ord);
		(void)strcat(buffer, bezeichnung);
		}
	(void)strcat(buffer, "\t");

	/* reinit the globals */
	*glob_parent_aktg = NULL;
	*glob_child_aktg = NULL;

	COMMTYP = SELECTITEM;
	return(MPOK);
}
