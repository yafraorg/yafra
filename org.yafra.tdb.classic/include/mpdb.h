/*D***********************************************************
 * Header:    Datenbankspezifische Angaben
 *            Hier wird das Header der spezifischen DB angegeben
 *
 * Copyright: yafra.org, Switzerland, 2004
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdb.h,v 1.2 2004-01-26 21:01:05 mwn Exp $
*/


/*
 * These are used by the
 * data descriptor mechanism.
 */

#define DB_DUMMY				0
#define DB_CHAR				1
#define DB_SHORT				2
#define DB_INT					3
#define DB_LONG				4
#define DB_DOUBLE				5
#define DB_FLOAT				6
#define DB_NULLIND			7
#define DB_DATE				8

/* SQL SERVER */
#if defined(MPDBMSSQL)
#include <mpdbmssql.h>
/* ORACLE */
#elif defined(MPDBORACLE)
#include <mpdbora.h>
/* ODBC */
#elif defined(MPDBODBC)
#include <mpdbodbc.h>


/* INGRES */
#elif defined(MPDBINGRES)
#include <mpdbing.h>
/* ADABAS */
#elif defined(MPDBADABAS)
#include <mpdbada.h>
/* if no db is specified, include the HP/Allbase MPDBHPSQL defines */
#else
#include <mpdbhp.h>
#endif
