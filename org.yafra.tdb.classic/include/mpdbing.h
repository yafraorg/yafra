/*D***********************************************************
 * Header:    HP ALLBASE/SQL
 *            Datenbankspezifische Angaben      
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdbing.h,v 1.2 2008-11-02 19:55:32 mwn Exp $

 Log Information:
 $Log: mpdbing.h,v $
 Revision 1.2  2008-11-02 19:55:32  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:22:49  mw
 NT 4.0 release und WWW Teil

 Revision 2.2  1994/03/31 14:27:35  mw
 delete field defs

 * Revision 2.1  94/03/29  13:07:16  13:07:16  mw (Administrator)
 * new database release 2
 * 
 * Revision 1.2  94/03/23  14:55:54  14:55:54  rh (Roland Haas)
 * generate structures
 * 
 * Revision 1.1  94/02/16  15:54:43  15:54:43  mw (Administrator)
 * Initial revision
 * 
 * Revision 1.1  92/12/23  12:28:01  12:28:01  mw (Administrator)
 * Initial revision
 * 
 * Revision 1.1  92/11/26  12:31:42  12:31:42  mw ()
 * Initial revision
 * 
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
 * These are the data type used by Ingres
 * in the SQLDA
 */

#define IngresDateType		3
#define IngresMoneyType		5
#define IngresCharType		20
#define IngresVarCharType	21
#define IngresIntType		30
#define IngresFloatType		31
#define IngresTableType		52
#define IngresDateLengType	25

/*
 * This is the delimiter used by the connect string
 */

#define CONNECTDELIMITER  '/'

/*
 * Various database-specific defines
 */

#define		SQLOK					 ((int) 0)
#define     SQLNULL            ((int) -1)
#define		NO_DATA_FOUND		 ((int) 1403)
