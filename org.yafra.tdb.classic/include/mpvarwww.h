/*D***********************************************************
 * header:    global vars for OUTput programs       mpvaract.h
 *
 * copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpvarwww.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/


/*--- SQL-Memory im DBI */
MEMOBJ			sqlmem;
char sqlquery[_QUERYLEN]; /* global SQL query buffer */
char Clientname[_RECORDLEN];

/*--- some globals only for actions -----------*/
int globalflag = 0;
int FatalError;		/* Fataler Fehler beim Aufstarten */

/*--- global language fields ------------------*/
int	aktuellesprache;         /* current      */
char	language[_CHAR20+1];     /* sprache bez  */

/*--- error messages read from DB to memory for access at every point */
int		akt_maxmessage;               /* count of action messages          */
char		**akt_message;                /* system messages in memory from DB */
MEMOBJ	msgmem;


/****************************************************************
 *  *  F L A G S  *
 ****************************************************************/
/* -D */ /* see mpvarlib.h */	/* debug flag */
/* -d */ char DBname[_RECORDLEN];	/* Datenbankname */
/* -L */ int dialogsprache;	/* can overwrite user language */
/* -l */ int outputsprache;	/* can overwrite receiver language */
/* -X */ int LockAction;      /* locking of an action */
