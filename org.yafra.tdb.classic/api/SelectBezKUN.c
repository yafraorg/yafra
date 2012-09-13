/*D***********************************************************
 * Modul:     DBI - database select
 *            Kunden - make a bez-string
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectBezKUN.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

/*************************************************************
 * function:  make a bez-string for KUNDEN
 *
 * return:    found/ok or not found
 *************************************************************/
int KUNmkbez(int kunid, char *bezeichnung, int len)
{
	extern MPV_KUNADR kunadrv;

	int status = (int)MPOK;
	int id;
	char tmp_bez1[_BEZLEN+1];
	char tmp_bez2[_BEZLEN+1];
	char tmp_bez3[_BEZLEN+1];

	id = MPAPIselectOneId((int)_MPV_KUNADR, kunid, (char *)&kunadrv);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(tmp_bez1, (char *)kunadrv.name, (int)_CHAR512);
		(void)copyTextTo(tmp_bez2, (char *)kunadrv.plz, (int)_CHAR256);
		(void)copyTextTo(tmp_bez3, (char *)kunadrv.ort, (int)_CHAR256);
		(void)sprintf(bezeichnung, "%d%s%s%s%s%s%s", kunadrv.pers_id, TRENNERNORM,
		              tmp_bez1, TRENNERNORM, tmp_bez2, TRENNERNORM, tmp_bez3);
		}
	else
		status = MPE_NOENTRYFOUND;

	return(status);
}
