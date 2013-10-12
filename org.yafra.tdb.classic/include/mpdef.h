/*D***********************************************************
 * Modul:     General defs - include        MPdef.h
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdef.h,v 1.3 2008-11-17 10:42:51 mwn Exp $
*/


/************************************************************
 * Sektion:  memory defines and objects
 *************************************************************/

/* memory management */
typedef struct
{
   char *buffer;                    /* buffer pointer    */
   unsigned long alloclen;          /* length of buffer  */
   unsigned long datalen;           /* length of data (must be lower or equal to alloclen! */
} MEMOBJ;
#define STARTMEMCHUNK   (int)30720     /*  30 kb initial size   */
#define DEFMEMCHUNK     (int)4096      /*   4 kb increase       */
#define BIGMEMCHUNK     (int)102400    /* 100 kb increase       */
#define LITTELMEMCHUNK  (int)1024      /*   1 kb increase       */
#define RECLAENGE       (int)8192      /*   8 kb increase       */

/************************************************************
 * Sektion:  global defines
 *************************************************************/

/* true / false definition */
#ifndef TRUE
#define  TRUE  1
#define  FALSE 0
#endif

/* default language SPRACHE */
#define DEFAULTLANGUAGE  1
#define DEFAULTLANGTEXT  "german"

/* program name */
#define PROGRAMNAME "travelDB"

/* error/debug/log handling */
#define MP_GUI_D "MPGUI debug:"
#define MP_GUI_E "MPGUI error:"
#define MP_GUIDEBUGFILE stdout

#define MP_DBI_D "MPDBI debug:"
#define MP_DBI_E "MPDBI error:"
#define MP_DBIDEBUGFILE mpdbifile
#ifdef ps_win
#define MP_DBIDEBUGFILENAME "\\temp\\MPdbidebug.txt"
#else
#define MP_DBIDEBUGFILENAME "/tmp/MPdbidebug"
#endif

#define MP_ACT_D "MPACT debug:"
#define MP_ACT_E "MPACT error:"
#define MP_ACTDEBUGFILE stdout

/* setupfile name */
/* system default is /etc/x.pro and user default is $HOME/.x */
#define MP_SETUPFILE "mpgui"

/* Trennzeichen zwischen zwei Subobjekte */
#define TRENNERNORM   " : "
#define TRENNERNORMLEN (size_t)3
#define TRENNER       " => "
#define TRENNERLEN    (size_t)4
#define UNDEFSYMB     "-"
#define UNDEFSYMBLEN  1
#define MSGTRENNER    "\n--------------------------------------------------------------------------------\n"
#define MSGTRENNERLEN (size_t)82

/* interne Trennzeichen zwischen GUI - DBI, Aktionen layout */
#define _MPSYMBLEN   1
#define _MPSYMB_TAB  '\t'
#define _MPSYMB_CR   '\n'
#define _MPSYMB_NULL '\0'
#define _MPSYMB_FF 	'\f'
#define _MPSYMB_CRLF "\r\n"

/* split buffer symbols */
#define NOPARTS    0
#define SINGLESEL  1
#define MULTISEL   2


#define DEFAULTLANG 1

/* Terminalsteuerungsbefehle */
#define CLS           "\033&a0y0C\033J"
#define BEEP          "\007"

/* SQL isolation level defines for BEGIN WORK */
#define SQLISOLATION_RR  (int)1
#define SQLISOLATION_CS  (int)2
#define SQLISOLATION_RC  (int)3
#define SQLISOLATION_RU  (int)4

/* SQL priority number for BEGION WORK */
#define SQLPRIO_LOWEST   (int)255
#define SQLPRIO_NORMAL   (int)127
#define SQLPRIO_HIGHEST  (int)0


/* Maximalwerte */
#define   MAX_SQL_ROWS        (int)10000
#define   MAX_MENU_ITEMS      (int)50
#define   MAX_AKTIONEN        (int)100
#define   MAX_DETAIL          (int)100
#define   MAX_REISENDE        (int)100
#define   MAX_ARG             (int)100

/*--- color flag for GRcolor ---*/
#define NOCOLOR      255

/*--- Execution flags  Context for UtilExec.c --------*/
#define NORMAL			0
#define BACKGROUND	1


/*--- Aktionen ---*/
#define SINGLEAKT    0
#define MULTIPLEAKT  1

/*--- date range for search on date within this range ---*/
#define _DATERANGE   1000000    /* 14 days range */

/*--- Buchungsmaske DLNSHORT ---*/
#define BMDLNFIELDS  6

/* for UtilIDmax function */
#define _ORD         (int)-2

/* for readdate function */
#define DEZIMAL      (int)10

/* for XXXdelete functions - return from UtilIDcount() */
#define EMPTY        (int)0

/*--- Option Toggles ---*/
#define _TOGDBLOG       (int)0
#define _TOGUSERLOG     (int)1
#define _TOGAUTOINFO    (int)2
#define _TOGGRAPHIC     (int)3
#define _TOGDLN         (int)4
#define _TOGGLOBAL      (int)5
#define _TOGDATORDER    (int)6
#define _TOGAUDIO       (int)7
#define _TOGDEBUG       (int)8
#define _TOGSELFROMTMP  (int)9

/* AKTcntrl flags */
#define _CHECK_FLAG       2
#define _UPDATE_FLAG      3
#define _AKT_NR           4
#define _AKTCNTRL_CHECK   5
#define _AKTCNTRL_CONFIRM 6
#define _AKTCNTRL_ERROR   7
#define _AKTCNTRL_REINIT  8

/* booking states */
#define _BM_NOP           0  /* no operation */
#define _BM_BCH           1  /* enter a BCH */
#define _BM_DLN           2  /* enter a DLN */
#define _BM_RES           3  /* enter a RES */
#define _BM_KONTUPDATED   4  /* KONT_DETAIL updated */
#define _BM_RESWRITTEN    5  /* RES written */
#define _BM_AKT           6  /* exec an AKT */
