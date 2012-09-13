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
#define _CHAR2000		(int)1024

#define _CHARMAXLEN	(int)_CHAR2000

/* default string len */
#define   _RECORDLEN     (int)1024 /* MarcoPolo record length */
#define   _LABELLEN      (int)40   /* Labell�nge */
#define   _SHORTLEN      (int)8    /* Shortl�nge */
#define   _INTLEN        (int)16   /* Integerl�nge */
#define   _BEZLEN        _CHAR2000   /* Bezeichnungsl�nge */
#define   _PARALEN       (int)1024   /* Parameterl�nge */
#define   _PROZLEN       (int)1024  /* Prozessl�nge */
#define   _TEXTLEN       _CHAR2000   /* Textl�nge */
#define   _KRZLLEN       (int)10   /* K�rzell�nge */
#define   _FILELEN       (int)127  /* Dateiname und Pfad Laenge */
#define   _DATLEN        (int)12   /* Datum/Zeit Laenge */
#define   _GRAFORMLEN    (int)160  /* Grafik Formatlaenge */
#define   _USERLEN       (int)128  /* len of user name */
#define   _PWDLEN        (int)20   /* len of password */
#define   _NUMLEN        (int)9    /* PLZ/ZIP / KONTO len */
#define   _QUERYLEN      (int)10240 /* SQL query length */
#define   _DATELEN       (int)64   /* Length of Datestring */
#define   _FLAGLEN       (int)8    /* lenght of a flag field */

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

