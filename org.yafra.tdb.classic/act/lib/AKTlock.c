/*D***********************************************************
 * modul:      ACT locking functions for ACTs
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpact.h>         /* Standart Includefile   */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTlock.c,v 1.2 2008-11-02 19:55:50 mwn Exp $";


#define WAITSECONDS 5
#define RETRYAMOUNT 100
/*SF***********************************************************
 * function:        set a AKT lock
 * arguments:       none
 * return:          state
 *************************************************************/
int UtilSetAKTlock(void)
{
	extern int DebugFlag;

	MAXIMA aktlock;
	int status;
	int id;
	unsigned int i, j;

	aktlock.tabelle = (int)_AKT_DETAIL;
	aktlock.typ     = (int)TRUE;
	aktlock.max_id  = (int)0;
	aktlock.min_id  = (int)0;
	aktlock.incr    = (int)0;

	for (i=0; i < RETRYAMOUNT; i++)
		{
		/* start db transaction and */
		/* check if it's ok to run this action */
		status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
		if (status != (int)MPOK)
			return(status);
		id = MPAPIselectOneId((int)_MAXIMA, aktlock.tabelle, (char *)&aktlock);
		if (id == (int)_UNDEF)
			{
			status = MPAPIinsertEntry((int)_MAXIMA, (char *)&aktlock, NULL);

/*DEBUG*****************/
			if (DebugFlag)
				printf("%sdebug: setting AKT lock with state %d%s", _P_EOL_, status, _P_EOL_);
/*DEBUG*****************/

			MPAPIdb_committrx();

			if (status == (int)MPOK)
				break;
			else
				{
				status = (int)MPOK; /* force status to OK */
				continue;
				}
			}
		else
			{
			MPAPIdb_committrx();

/*DEBUG*****************/
			if (DebugFlag)
				printf("%sdebug: already locked - waiting%s", _P_EOL_, _P_EOL_ );
/*DEBUG*****************/

			/* wait for retry */
#ifdef ps_unix
			(void)sleep((unsigned int)WAITSECONDS);
#endif
			}
		}

/*DEBUG*****************/
			if (DebugFlag)
				printf("%sdebug: exit setting AKT lock%s", _P_EOL_, _P_EOL_ );
/*DEBUG*****************/

	return(status);
}


/*SF***********************************************************
 * function:        unset AKT lock
 * arguments:       none
 * return:          state
 *************************************************************/
int UtilUnsetAKTlock(void)
{
	extern int DebugFlag;

	MAXIMA aktlock;
	int status;

	aktlock.tabelle = (int)_AKT_DETAIL;
	aktlock.typ     = (int)TRUE;
	aktlock.max_id  = (int)0;
	aktlock.min_id  = (int)0;
	aktlock.incr    = (int)0;

	/* start db transaction and */
	/* check if it's ok to run this action */
	status = MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		return(status);

	status = MPAPIdeleteEntry((int)_MAXIMA, (char *)&aktlock);


/*DEBUG*****************/
	if (DebugFlag)
		printf("%sdebug: releasing AKT lock with state %d%s", _P_EOL_, status, _P_EOL_ );
/*DEBUG*****************/

	MPAPIdb_committrx();

	return(status);
}
