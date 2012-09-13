/*D***********************************************************
 * modul:     API - calculate reduktion
 *
 *            reduziert einen Betrag value mit einem Status
 *            und rundet das Resultat mit round. Der errechnete
 *            Abzug in wird in abzug und die prozentuale
 *            Reduktion in commisson gehalten.
 *
 * return:    Reduzierter neuer Wert fuer value
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/reduktion.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

double MPAPIreduktion(STA_VIEW *status, double value, int round,
                      double *abzug, double *commission)
{
	switch (status->sta[0])
		{
		case '%':
			*commission = status->kond;
			*abzug = status->kond/100.*value;
			break;
		case '-':
			*commission = (status->kond / value) * (double)100.0;
			*abzug = status->kond;
			break;
		case '+':
			*commission = (status->kond / value) * (double)-100.0;
			*abzug = (double)-1 * status->kond;
			break;
		case '!':
			*commission = 0;
			*abzug = value-status->kond;
			break;
		}
	*abzug = (double)((int)(*abzug * (double)round + 0.5) / round);
	return(value - *abzug);
}
