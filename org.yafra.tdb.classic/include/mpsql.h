/**************************************************************/
/* Header:    SQL dynam. select statements                    */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpsql.h,v 1.2 2008-11-02 19:55:32 mwn Exp $

 Log Information:
 $Log: mpsql.h,v $
 Revision 1.2  2008-11-02 19:55:32  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:22:49  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/29 13:07:40  mw
 new database release 2

 * Revision 1.3  94/02/16  15:55:32  15:55:32  mw (Administrator)
 * update filename for dos
 * 
 * Revision 1.2  93/05/05  01:11:20  01:11:20  mw (Administrator)
 * "hope I can eliminate this file soon"
 * 
 * Revision 1.1  92/11/26  12:32:39  12:32:39  mw ()
 * Initial revision
 * 
*/


/*
* Definition aller verwendbaren SQL-Index Befehlen
*/
#define _DROP_INDEX      "DROP INDEX %s FROM TDBADMIN.%s;"
#define _CREATE_UC_INDEX "CREATE UNIQUE CLUSTERING INDEX %s ON TDBADMIN.%s (%s);"
#define _CREATE_U_INDEX  "CREATE UNIQUE INDEX %s ON TDBADMIN.%s (%s);"
#define _CREATE_C_INDEX  "CREATE CLUSTERING INDEX %s ON TDBADMIN.%s (%s);"
#define _CREATE_INDEX    "CREATE INDEX %s ON TDBADMIN.%s (%s);"
