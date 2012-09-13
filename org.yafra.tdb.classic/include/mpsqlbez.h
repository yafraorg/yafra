/**************************************************************/
/* Header:    SQL dynam. statements for BEZ and TXT in API    */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpsqlbez.h,v 1.2 2008-11-02 19:55:33 mwn Exp $

 Log Information:
 $Log: mpsqlbez.h,v $
 Revision 1.2  2008-11-02 19:55:33  mwn
 re branded code - tested with oracle instant client 11.1 under ubuntu linux - add deploy to main makefile

 Revision 1.1.1.1  2002-10-26 21:10:43  mwn
 inital release

 Revision 3.1  1997/04/02 06:22:49  mw
 NT 4.0 release und WWW Teil

 Revision 2.1  1994/03/29 13:07:42  mw
 new database release 2

 * Revision 1.3  94/02/16  15:55:33  15:55:33  mw (Administrator)
 * update filename for dos
 * 
 * Revision 1.2  93/09/22  11:19:31  11:19:31  mw (Administrator)
 * new sel bez
 * 
 * Revision 1.1  93/02/09  22:44:33  22:44:33  mw (Administrator)
 * Initial revision
 * 
*/

#define	_SELECT_BEZ     "SELECT * FROM TDBADMIN.BEZEICHNUNG WHERE BEZ_ID = %d AND S_ID = %d AND TYP = %d;"
#define	_SELECT_TXT     "SELECT * FROM TDBADMIN.TEXTE WHERE TEXTID = %d AND S_ID = %d AND TYP = %d ORDER BY TEXTNR;"

#define _INSERT_SPR_TXT_OUT "INSERT INTO TDBADMIN.TMP_TEXTE SELECT TEXTID, %d, TEXTNR, TEXT, TYP FROM TDBADMIN.TEXTE WHERE S_ID = %d;"
#define _INSERT_SPR_TXT_IN  "INSERT INTO TDBADMIN.TEXTE SELECT TEXTID, S_ID, TEXTNR, TEXT, TYP FROM TDBADMIN.TMP_TEXTE WHERE S_ID = %d;"
#define _INSERT_SPR_BEZ_OUT "INSERT INTO TDBADMIN.TMP_BEZEICHNUNG SELECT BEZ_ID, %d, BEZ, TYP FROM TDBADMIN.BEZEICHNUNG WHERE S_ID = %d;"
#define _INSERT_SPR_BEZ_IN  "INSERT INTO TDBADMIN.BEZEICHNUNG SELECT BEZ_ID, S_ID, BEZ, TYP FROM TDBADMIN.TMP_BEZEICHNUNG WHERE S_ID = %d;"

#define _DELETE_SPR_BEZ	"DELETE FROM TDBADMIN.BEZEICHNUNG WHERE S_ID = %d;"
#define _DELETE_TMP_BEZ	"DELETE FROM TDBADMIN.TMP_BEZEICHNUNG WHERE S_ID = %d;"
#define _DELETE_SPR_TXT	"DELETE FROM TDBADMIN.TEXTE WHERE S_ID = %d;"
#define _DELETE_TMP_TXT	"DELETE FROM TDBADMIN.TMP_TEXTE WHERE S_ID = %d;"
#define _DELETE_SPR_AKTTXT "DELETE FROM TDBADMIN.AKTIONSTEXTE WHERE S_ID = %d;"
#define _DELETE_SPR_HELP "DELETE FROM TDBADMIN.HELP WHERE S_ID = %d;"
#define _DELETE_SPR_MSG "DELETE FROM TDBADMIN.MSG WHERE S_ID = %d;"
#define _DELETE_SPR_LABEL "DELETE FROM TDBADMIN.LABEL WHERE S_ID = %d;"
