/*D***********************************************************
 * modul:     API - update global booking STATUS
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilUpdateBookSta.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

#define _SEL_CNT_RESSTA "SELECT COUNT(R_STA) FROM TDBADMIN.RESERVATION \
	WHERE BID = %d;"

#define _SEL_MIN_RESSTA "SELECT MIN(R_STA) FROM TDBADMIN.RESERVATION \
	WHERE BID = %d;"

#define _UPDATE_BCH "UPDATE TDBADMIN.BUCHUNG SET M_DAT = %d \
	WHERE BID = %d;"

#define _UPDATE_BCH_STA "UPDATE TDBADMIN.BUCHUNG SET STA = %d, M_DAT = %d \
	WHERE BID = %d;"

int MPAPIupdate_booksta(int bid)
{
	extern MEMOBJ apimem;

	BUCHUNG bch;
	char query[_QUERYLEN];
	int anzahl, i;
	int status=(int)MPOK;
	int mod_date;
	int minimum;
	int count;

	/* init */
	minimum = (int)_RES_ENTER;

	/* check how many entries are there - if zero then set to
	 * _RES_ENTER and go back, else select min id */
	(void)sprintf(query, _SEL_CNT_RESSTA, bid);
	status=MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, query, &anzahl,
	                          &apimem.datalen, &apimem.alloclen);
	if (status == (int)MPOK && anzahl > (int)0)
		{
		(void)memcpy((void *)&count, (void *)apimem.buffer, sizeof(int));
		if (count > 1)
			{
			/* get the min RESERVATION.R_STA for a dossier */
			(void)sprintf(query, _SEL_MIN_RESSTA, bid);
			status=MPAPIdb_sqlquery((int)_INTEGER, &apimem.buffer, query, &anzahl,
			                          &apimem.datalen, &apimem.alloclen);
			if (status == (int)MPOK && anzahl > (int)0)
				(void)memcpy((void *)&minimum, (void *)apimem.buffer, sizeof(int));
			}
		}

	/* update booking */
	(void)time((time_t *)&mod_date);
	if (status != (int)MPOK || minimum < 1)
		(void)sprintf(query, _UPDATE_BCH, mod_date, bid);
	else
		(void)sprintf(query, _UPDATE_BCH_STA, minimum, mod_date, bid);
	status = MPAPIdb_sqlcommand(query, &anzahl);

	/* if anzahl is 0 then set error code */
	if (status == (int)MPOK && anzahl == 0)
		status = (int)MPE_NOINSUPDDEL;

	return(status);
}
