/*D***********************************************************
 * Modul:     DBI - database select
 *            DLN - make a bez-string
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectBezDLN.c,v 1.3 2009-01-02 16:51:35 mwn Exp $";

#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

/*************************************************************
 * function:  make a bez-string for KUNDEN
 *
 * return:    found/ok or not found
 *************************************************************/
int DLNmkbez(int dlnid, char *bezeichnung, int len)
{
	extern DLN_VIEW dlnv;

	int status = (int)MPOK;
	int id;
	char tmp_bez1[_BEZLEN+1];
	char tmp_bez2[_BEZLEN+1];

	id = MPAPIselectOneId((int)_DLN_VIEW, dlnid, (char *)&dlnv);
	if (id != (int)_UNDEF)
		{
		(void)copyTextTo(tmp_bez1, (char *)dlnv.name, (int)_CHAR512);
		(void)copyTextTo(tmp_bez2, (char *)dlnv.vor, (int)_CHAR512);
		(void)sprintf(bezeichnung, "%d%s%s%s%s", dlnv.dln_id, TRENNERNORM,
		              tmp_bez1, TRENNERNORM, tmp_bez2);
		}
	else
		status = MPE_NOENTRYFOUND;

	return(status);
}
