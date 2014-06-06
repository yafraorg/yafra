/*
 *  Copyright 2002 yafra.org
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*!
 * @file pssys.h
 * @brief    global include for the pssys library
 */

#ifndef _PSSYS_H
#define _PSSYS_H

#include <stdio.h>
#include <time.h>

#include <psshared.h>

/* Message codes */
#define PSOK           0 /*!< message code OK */
#define PSERROR        1 /*!< message code error */
#define PSWARNING      2 /*!< message code warning */
#define PSALLOC       11 /*!< message code memory error */
#define PSOPEN        12 /*!< message code file open error */
#define PSREAD        13 /*!< message code file read error */
#define PSWRITE       14 /*!< message code file write error */
#define PSNODATE      15 /*!< message code no date */

/*! @brief memory management object */
typedef struct
{
   char *buffer;                   /*!< memory allocation         */
   unsigned int alloclen;          /*!< memory allocation length  */
   unsigned int datalen;           /*!< effective data length     */
} PSmemobj;
#define PSMEMCHUNK    (int)4096      /*!< memory chunck 4 kb increase       */
#define PSMEMCHUNK30  (int)30720     /*!<   30 kb increase       */
#define PSMEMCHUNK100 (int)1024000   /*!<  100 kb increase       */

/* state definition (true and false) */
#ifndef TRUE
#define  TRUE  1 /*!< true 1 */
#define  FALSE 0 /*!< false 0 */
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
#define _PSLOG_OPEN     1 /*!< log open */
#define _PSLOG_CLOSE    2 /*!< log close */
#define _PSLOG          3  /*!< log general message */
#define _PSLOG_EMERG    4  /*!< log panic condition. reaction is immediately req. */
#define _PSLOG_ERROR    5  /*!< log error message */
#define _PSLOG_WARNING  6  /*!< log warning message */
#define _PSLOG_INFO     7  /*!< log info message */
#define _PSLOG_DEBUG    8  /*!< log debug message */

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
/*! @brief CGI object */
typedef struct {
	PSmemobj nameobj; //!< name //
	PSmemobj valobj; //!< value //
} PSCGIentry;
typedef enum {PSPOSTMETHOD, PSGETMETHOD} PSreqmethod;

/* prototypes */

/*! @brief Memory allocation function
 * @param voidptr Memory pointer
 * @param intptr b length
 * @param c test1
 * @param d test2
 * @param e test3
 * @return Updated or new memory pointer
 */
PS_DLLAPI void *PSSYSalloc(void *, unsigned int *, int , unsigned int , size_t );

PS_DLLAPI void *PSSYSallocobj(PSmemobj *, int);

/*! @brief Free up memory
 * @param pointer Memory pointer to be freed up
 */
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
