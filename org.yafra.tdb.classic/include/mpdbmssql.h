/*D***********************************************************
 * Header:    Microsoft ODBC interface
 *            Datenbankspezifische Angaben
 *
 * Copyright: yafra.org, Switzerland, 2004
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdbmssql.h,v 1.2 2004-01-26 21:01:06 mwn Exp $
*/

/*-----	Definition der CLUSTER- und UNIQUE- Flags -------------------------*/
#define	_UNIQUE	(short)1
#define	_CLUSTER	(short)1
#define	_DESC		(short)6

/*-----	Definition aller allgemeinen SQL-Befehle --------------------------*/
#define	_UPDT_STA_TXT	"UPDATE STATISTICS FOR TABLE TDBADMIN.TEXTE;"
#define	_UPDT_STA_BEZ	"UPDATE STATISTICS FOR TABLE TDBADMIN.BEZEICHNUNG;"

/*-----	Definition aller SYSTEM.---- SQL-Befehle --------------------------*/
#define	__SYS_COLUMN	"SELECT * FROM SYSTEM.COLUMN WHERE TABLENAME = \'%s\';"
#define	__SYS_INDEX	"SELECT * FROM SYSTEM.INDEX WHERE TABLENAME = \'%s\';"

/*-----	Definition der Tabellen Strukturen --------------------------------*/
typedef struct {
	int	column;				/* Interne Kolonnen Nummer */
	int	length;				/* Interne Kolonnen Laenge */
	char	colname[32];		/* Kolonnen Name */
	int	avglen;				/* Intern  Optimizer */
	char	tablename[32];		/* Tabellen Name */
} SYS_COLUMN;

typedef struct {
	int	numc;					/* Anzahl Kolonnen des Index */
	int	npages;				/* anzahl belegte pages */
	char	indexname[32];		/* Index Name */
	int	ccounts;				/* pseudo hitrate */
	char	tablename[32];		/* Tabellen Name */
} SYS_INDEX;

/*********************************************************************
*
*  Oracle spezifische definitionen
*
**********************************************************************/

#define RECLENGTH RECLAENGE         /* speak English or die */

#if !defined TRUE
#define TRUE  1
#define FALSE 0
#endif

/*
 * This is the delimiter used by the connect string
 */

#define CONNECTDELIMITER  '/'

/*
 * Various database-specific defines
 */
#define		SQLOK					 ((int) 0)
#define     SQLNULL            ((int) -1)
