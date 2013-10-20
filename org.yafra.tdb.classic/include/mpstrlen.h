/*D**********************************************************
 * Header:    MPstrlen
 *            string length
 *
 * Copyright: yafra.org, Basel, Switzerland
 ************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpstrlen.h,v 1.5 2009-01-02 21:30:21 mwn Exp $
*/

/* varchar lens in SQL tables */
#define _CHAR128		(int)128
#define _CHAR256		(int)256
#define _CHAR512		(int)512
#define _CHAR1024		(int)1024
#define _CHAR2000		(int)1024

#define _CHARMAXLEN	(int)_CHAR2000

/* default string length */
#define   _RECORDLEN     _CHAR1024 /* TDB standard record length */
#define   _LABELLEN      (int)40   /* labels */
#define   _SHORTLEN      (int)8    /* short */
#define   _INTLEN        (int)16   /* int */
#define   _BEZLEN        _CHAR1024   /* description (BEZ) */
#define   _PARALEN       _CHAR1024   /* action parameters */
#define   _PROZLEN       _CHAR1024  /* process length */
#define   _TEXTLEN       _CHAR1024   /* text */
#define   _KRZLLEN       (int)10   /* shortcut */
#define   _FILELEN       (int)127  /* filename */
#define   _DATLEN        (int)12   /* date */
#define   _GRAFORMLEN    (int)160  /* graphics */
#define   _USERLEN       (int)128  /* user name */
#define   _PWDLEN        (int)20   /* password */
#define   _NUMLEN        (int)9    /* PLZ/ZIP / KONTO len */
#define   _DATELEN       (int)64   /* datestring */
#define   _FLAGLEN       (int)8    /* flag field */

#define   _QUERYLEN      (int)10240 /* SQL query length */

#define   _CHAR1         (int)1
#define   _CHAR2         (int)2
#define   _CHAR4         (int)4
#define   _CHAR5         (int)5
#define   _CHAR8         (int)8
#define   _CHAR10        (int)10
#define   _CHAR20        (int)20
#define   _CHAR30        (int)30
#define   _CHAR39        (int)39
#define   _CHAR80        (int)80
#define   _CHAR200       (int)200

