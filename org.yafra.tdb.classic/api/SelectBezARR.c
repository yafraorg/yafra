/*D***********************************************************
 * Modul:     API - select a special BEZEICHNUNG                           
 *            ARRANGEMENT
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectBezARR.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

/*************************************************************
 * function:  make a bez-string for ARR
 *
 * return:    found/ok or not found
 *************************************************************/
int MPAPIselectARRbez(int arrid, int sid, char *bezeichnung, int len)
{
	extern ARRANGEMENT arr;

	int status = (int)MPOK;
	int id;
	char tmp_bez1[_BEZLEN+1];
	char tmp_bez2[_BEZLEN+1];
	struct tm DateTime;

	id = MPAPIselectOneId((int)_ARRANGEMENT, arrid, (char *)&arr);
	if (id != (int)_UNDEF)
		{
		(void)memset((void *)&DateTime, NULL, sizeof(DateTime));
		DateTime.tm_min  = (int)_UNDEF;
		DateTime.tm_hour = (int)_UNDEF;
		DateTime.tm_mday = (int)_UNDEF;
		DateTime.tm_mon  = (int)_UNDEF;
		DateTime.tm_year = (int)_UNDEF;

		(void)SelectBez((int)_ARRANGEMENT, sid, arr.bez_id, tmp_bez2);
		(void)copyTextTo(tmp_bez1, (char *)tmp_bez2, (int)_BEZLEN);
		(void)WriteDate(&DateTime, (time_t *)&arr.a_dat, tmp_bez2);
		(void)sprintf(bezeichnung, "%s%s%s%s%s", tmp_bez1, TRENNER, tmp_bez2);
		}
	else
		status = MPE_NOENTRYFOUND;

	return(status);
}
