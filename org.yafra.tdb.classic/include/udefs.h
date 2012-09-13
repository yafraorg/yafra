/*IH***********************************************************
 * Header:        User Interface
 * Description:   global defines
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
*/
/* RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/udefs.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/


/*--- BM general definitions --------------------------------*/
#define	_OK					0
#define	_NOTOK				-1
#define	_NOSELECT			-1

/*---- Define f�r PCX Images --------------------------------*/
#define MAXIMAGES                       3

/*---- shells  ----------------------------------------------*/
#define TEXTSHELL                       0
#define LISTSHELL                       1
#define DIALSHELL                       2

/*------- Message-Info types --------------------------------*/
#define _MSG_HELP                       0
#define _MSG_INFO                       1
#define _MSG_WARNING                    2
#define _MSG_ERROR                      3

/*------- Graphic mode flag when calling xGRchange()---------*/
#define XGRSELGRAFIC                    1
#define XGRINPGRAFIC                    2
#define XGRSHOWGRAFIC                   3
#define XGRCHOOSEITEM                   4
#define XGRWRITEGRA                     5
#define XGRBOOKING                      6

/****************************************************************************
 * ERROR section
 ****************************************************************************/
/*------- Error numbers index in error  flag for messages ---*/
#define XUIOK                            0
#define XUIDBOK                          0
#define XUIDBLIZENZ                      1
#define XUIDBCONNECT                     2
#define XUIDBLABELS                      3
#define XUINOHELPFILE                    4
#define XUINOCOMM                        5
#define XUINOMEMORY                      6
#define XUINOGRAPHIK                     7
#define XUIIPCNOSOCKET                   8
#define XUIIPCNOCONNECT                  9
#define XUINOSENDPOSSIBLE               10
#define XUIIPCNOHOST                    11
#define XUIIPCNOPIPE                    12
#define XUIIPCNOSERVICE                 13
#define XUIPRINT                        14

/*-------- Error text -----------*/
#define GUI_ERROR_DEFAULT		"\nMARCO POLO - Internal error"
#define GUI_ERROR_SETUP			"\nMARCO POLO - Setup file not found "
#define GUI_ERROR_IPC			"\nMARCO POLO - No IPC communication "
#define GUI_ERROR_LICENSE		"\nMARCO POLO - No license authorisation "
#define GUI_ERROR_ARGUMENTS	"\nMARCO POLO - Invalid argument(s) "
#define GUI_ERROR_LABELS		"\nMARCO POLO - Not enough memory for labels"


/*-- Kommunikationstyp --------------------------------------*/
#define XUIPIPE                          1
#define XUISOCKET                        2

/*-- Toggle options  ----------------------------------------*/
#define _MAXBUTTONS_					10		/* number of option buttons max  */
#define _MAXBUTTONSCOLUMN_			5		/* limit for buttons in edition column */

#define XUIDIALOG_SELECTION            100

/* M_PI not defined under Windows32 */
#ifdef ps_win
#define M_PI 3.1415926535
#endif
