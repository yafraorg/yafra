/*D***********************************************************
 * Header:    HP ALLBASE/SQL
 *            Datenbankspezifische Angaben      
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdbora.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/

/*-----	Definition der CLUSTER- und UNIQUE- Flags -------------------------*/
#define	_UNIQUE	(short)1
#define	_CLUSTER	(short)1
#define	_DESC		(short)6

/*-----	Definition aller allgemeinen SQL-Befehle --------------------------*/
#define	_UPDT_STA_TXT	"UPDATE STATISTICS FOR TABLE TDBADMIN.TEXTE;"
#define	_UPDT_STA_BEZ	"UPDATE STATISTICS FOR TABLE TDBADMIN.BEZEICHNUNG;"

/*-----	Definition aller SYSTEM.---- SQL-Befehle --------------------------*/
#define	__SYS_COLUMN "SELECT * FROM SYSTEM.COLUMN WHERE TABLENAME = \'%s\';"
#define	__SYS_INDEX  "SELECT * FROM SYSTEM.INDEX WHERE TABLENAME = \'%s\';"

/*-----	Definition der Tabellen Strukturen --------------------------------*/
typedef struct {
	char	colname[20];		/* Kolonnen Name */
	char	tablename[20];		/* Tabellen Name */
	char	owner[20];			/* Tabellen Owner */
	int	column;				/* Interne Kolonnen Nummer */
	int	length;				/* Interne Kolonnen Laenge */
	int	avglen;				/* Intern  Optimizer */
	short	typecode;			/* Datentyp */
	short	nulls;				/* Null Indikator */
	short	precision;			/* Anzahl signifikannte Ziffern */
	short	scale;				/* Anzahl Nachkommastellen */
	short	languageid;			/* LANG der Spalte */
	short	defaulttype;		/* Default Wert einer Kolonne */
	char	dbefileset[20];	/* Name des DBE_fileset mit LONG Datentypen */
} SYS_COLUMN;

typedef struct {
	char	indexname[20];		/* Index Name */
	char	tablename[20];		/* Tabellen Name */
	char	owner[20];			/* Tabellen Owner */
	int	numc;					/* Anzahl Kolonnen des Index */
	short	int columns[16];	/* Kolonnennummern des Index */
	int	npages;				/* anzahl belegte pages */
	int	ccounts;				/* pseudo hitrate */
	char	ctime[16];			/* creation time */
	short	unique;				/* unique Index Flag */
	short	cluster;				/* Cluster Index Flag */
	short	int coldirs[16];	/* intern */
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
 * These are the data type used by Oracle
 * in the SQLDA
 */

#define OracleVarCharType	1
#define OracleCharType		96
#define OracleNumType		2
#define OracleLongType		8
#define OracleRowIdType		11
#define OracleDateType		12
#define OracleRawType		23
#define OracleLongRawType	24

/*
 * This is the delimiter used by the connect string
 */

#define CONNECTDELIMITER  '/'

/*
 * Various database-specific defines
 */

#define		SQLOK					 ((int) 0)
#define     SQLNULL            ((int) -1)
#define     NO_DATA_FOUND      ((int) 1403)
