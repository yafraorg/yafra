/*D***********************************************************
 * header:    global vars for travelDB library (GUI and DBI)
 *
 * copyright: yafra.org, Switzerland
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpvarlib.h,v 1.2 2004-02-12 09:14:20 mwn Exp $
*/

/* debugging flag */
int DebugFlag;
char MPversiontext[_RECORDLEN];

/* exit function for signals */
int (*MPfunction_exit)();

/* IPC filedescriptor */
int ipcfd;

/* globale Kommunikationsfelder */
COMMOBJ comm;

/* LOGGING Filepointer */
FILE *fplogBooking = NULL;
unsigned char logging_booking;
FILE *fplogUser = NULL;
unsigned char logging_user;
FILE *fplogMP = NULL;
unsigned char logging_mp;
FILE *fplogSQL = NULL;
unsigned char logging_sql;
unsigned char logging_sqltm; /* performance time logging in sql */
