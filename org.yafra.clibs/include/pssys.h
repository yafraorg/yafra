/*!************************************************************
 * @file pssys.h
 * @brief    global include for the pssys library
 *
 * copyright: yafra.org, Switzerland, 2002
 **************************************************************/
/*R
  RCS Information:
  $Header: /yafraorg/cvsroot/foundation/ansic/include/pssys.h,v 1.2 2002-11-17 14:41:31 mwn Exp $
*/

#ifndef _PSSYS_H
#define _PSSYS_H

#include <stdio.h>
#include <time.h>

#include <psshared.h>

/* Message codes */
#define PSOK           0 /* OK */
#define PSERROR        1 /* error */
#define PSWARNING      2 /* warning */
#define PSALLOC       11 /* Allocationsfehler - zu wenig Speicher frei */
#define PSOPEN        12 /* Dateioeffnungsfehler */
#define PSREAD        13 /* Lese Fehler */
#define PSWRITE       14 /* Schreib Fehler */
#define PSNODATE      15 /* kein Datum */

/* memory management */
typedef struct
{
   char *buffer;                   /* memory allocation         */
   unsigned int alloclen;          /* memory allocation length  */
   unsigned int datalen;           /* effective data length     */
} PSmemobj; //!< memory object
#define PSMEMCHUNK    (int)4096      /*   4 kb increase       */
#define PSMEMCHUNK30  (int)30720     /*  30 kb increase       */
#define PSMEMCHUNK100 (int)1024000   /* 100 kb increase       */

/* state definition (true and false) */
#ifndef TRUE
#define  TRUE  1
#define  FALSE 0
#endif

/* default language SPRACHE */
#define PS_DEFAULTLANGUAGE  1
#define PS_DEFAULTLANGTEXT  "german"

/* internal GUI - DBI communication delimiters */
#define _PSSYMBLEN   1
#define _PSSYMB_TAB  '\t'
#define _PSSYMB_CR   '\n'
#define _PSSYMB_NULL '\0'
#define _PSSYMB_CRLF "\f\n"

/* default name of log file */
#define PS_DEFAULTLOGNAME "/tmp/pssys.log"

#define PS_MAXMSGLEN 2048

/* log types */
#define _PSLOG_OPEN     1
#define _PSLOG_CLOSE    2
#define _PSLOG          3  /* general message */
#define _PSLOG_EMERG    4  /* panic condition. reaction is immediately req. */
#define _PSLOG_ERROR    5  /* error message */
#define _PSLOG_WARNING  6  /* warning message */
#define _PSLOG_INFO     7  /* info message */
#define _PSLOG_DEBUG    8  /* debug message */

/* date formats */
#define PSSYS_DAT_UNDEF  -1
#define PSSYS_DAT_NODATE  0

#define PSSYS_DAT_GERMAN  10
#define PSSYS_TIME_GERMAN 11
#define PSSYS_TIMESEC_GERMAN 12
#define PSSYS_DAT_USA     20
#define PSSYS_TIME_USA    21
#define PSSYS_DAT_ENGLISH 30
#define PSSYS_TIME_ENGLISH 31
#define PSSYS_DAT_FRENCH  40
#define PSSYS_TIME_FRENCH 41
#define PSSYS_DAT_SPANISH 50
#define PSSYS_TIME_SPANISH 51

/* DDE progis */
#define PSSYS_PRG_WINWORD 1
#define PSSYS_PRG_EXCEL 2
#define PSSYS_PRG_ACCESS 3
#define PSSYS_PRG_POWERPOINT 4
#define PSSYS_PRG_OUTLOOK 5
#define PSSYS_PRG_IE 6
#define PSSYS_PRG_NETSCAPE 7

/* Internet Tools */
#define PSSYS_WWWTYPNS  1
#define PSSYS_WWW_NS_CMD "netscape"
#define PSSYS_WWW_NS_SERVICENAME "NETSCAPE"
#define PSSYS_WWW_NS_SYSTEMTOPIC "WWW_OpenURL"

#define PSSYS_WWWTYPIE  2
#define PSSYS_WWW_IE_CMD "Iexplore"
#define PSSYS_WWW_IE_SERVICENAME "IEXPLORE"
#define PSSYS_WWW_IE_SYSTEMTOPIC "WWW_OpenURL"

#define PSSYS_WWWTYPORA 3
#define PSSYS_WWW_ORA_CMD "powerb"
#define PSSYS_WWW_ORA_SERVICENAME "POWERBROSER"
#define PSSYS_WWW_ORA_SYSTEMTOPIC "WWW_OpenURL"

#define PSSYS_WWWTYPMAPI 4

#define PSSYS_WWWTYPUNIXMAIL 5
#define PSSYS_WWW_UNIXMAIL_CMD "mailx"

/* CGI stuff */
#define START_ENTRIES 16
#define BOOL_FALSE 0
#define BOOL_TRUE 1
#define WORDSIZE 16
typedef struct {
	PSmemobj nameobj;
	PSmemobj valobj;
} PSCGIentry;
typedef enum {PSPOSTMETHOD, PSGETMETHOD} PSreqmethod;

/* prototypes */

/*! @brief Memory allocation function
 * @param a Memory pointer
 * @param b length
 * @param c test1
 * @param d test2
 * @param e test3
 * @return Updated or new memory pointer
 */
PS_DLLAPI void *PSSYSalloc(void *a, unsigned int *b, int c, unsigned int d, size_t e);

PS_DLLAPI void *PSSYSallocobj(PSmemobj *, int);

PS_DLLAPI void  PSSYSfree(void *);
PS_DLLAPI void  PSSYSfreeobj(PSmemobj *);
PS_DLLAPI void  PSSYSfreearray(char **, int);

PS_DLLAPI int   PSSYSgetUser(int *, char *);
PS_DLLAPI int   PSSYSsetUser(int *, char *);

PS_DLLAPI int   PSSYSexecute(char *);

PS_DLLAPI int PSSYSddeOpen(char *, int *, int);
PS_DLLAPI int PSSYSddeWrite(int, const char *, ...);
PS_DLLAPI int PSSYSddeClose(int);

PS_DLLAPI int PSSYSkeyRead(int, char *, char *, char *, size_t);
PS_DLLAPI int PSSYSkeyWrite(int, char *, char *, char *);
PS_DLLAPI int PSSYSkeyReadTree(int, char *, char *, int, char **);
PS_DLLAPI int PSSYSkeyWriteTree(int, char *, char *, int, char **, char **);

PS_DLLAPI void  PSSYSlog(int, char *, char *, const char *, ...);
PS_DLLAPI void  PSSYSsyslog(int, char *, const char *, ...);
PS_DLLAPI void  PSSYSdebug(FILE *, char *, const char *, ...);
PS_DLLAPI void  PSSYSerrorlog(int, FILE *, char *, const char *, ...);

PS_DLLAPI void  PSSYSwriteDate(time_t, char *, char *, size_t, int);
PS_DLLAPI int   PSSYSint2datetime(struct tm *, time_t *, char *, size_t, char *, int);
PS_DLLAPI int   PSSYSdatetime2int(struct tm *, time_t *, char *, int);

PS_DLLAPI void  PSSYSinstallSignal(int, int (*function)());

PS_DLLAPI void  PSSYSstrLower(char *);
PS_DLLAPI void  PSSYSstrUpper(char *);

PS_DLLAPI void  PSSYShelp(char *);

PS_DLLAPI void  PSSYSwww(char *, int);
PS_DLLAPI void  PSSYSmail(char *, char *, int, int);
PS_DLLAPI int   PSSYSsendmail(char *, char *, char *, char *, int, int);
PS_DLLAPI void  PSSYSnews(char *, int);

PS_DLLAPI void InitStringObj(PSmemobj *);
PS_DLLAPI void InitEntriesObj(PSmemobj *);
PS_DLLAPI char *AllocString(PSmemobj *, unsigned int, int);
PS_DLLAPI PSCGIentry *AllocEntries(PSmemobj *, int, int);

PS_DLLAPI void PSSYShtmlInitText(char *);
PS_DLLAPI void PSSYShtmlHeadingText(int, char *);
PS_DLLAPI void PSSYShtmlParagraph(void);
PS_DLLAPI void PSSYShtmlLinkRef(char *, char *);
PS_DLLAPI void PSSYShtmlAnchor(char *, char *);
PS_DLLAPI void PSSYShtmlImage(char *);
PS_DLLAPI void PSSYShtmlImageMiddle(char *);
PS_DLLAPI void PSSYShtmlImageTop(char *);
PS_DLLAPI void PSSYShtmlBeginOList(void);
PS_DLLAPI void PSSYShtmlEndOList(void);
PS_DLLAPI void PSSYShtmlHiddenText(char *, char *);
PS_DLLAPI void PSSYShtmlSubmitInput(char *);
PS_DLLAPI void PSSYShtmlTextInput(char *, char *, char *, char *);
PS_DLLAPI void PSSYShtmlResetInput(char *);

#endif
