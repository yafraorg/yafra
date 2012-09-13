/**************************************************************/
/* Header:    global header file for MODEM library            */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/**************************************************************/
/*** RCS Information ***
$Header: /yafraorg/cvsroot/foundation/ansic/include/pssercom.h,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $
****/

#ifndef _PSSERCOM_H
#define _PSSERCOM_H

#include <stdio.h>
#include <psportable.h>
#include <psshared.h>

typedef struct 
{
	char port[100];                    /* hardware port adress    */
	char parity;                       /* parity           N,O,E  */
	unsigned short int bytelen;        /* length of byte   7,8    */
	unsigned short int stopbits;       /* no of stop bits  1,2    */
	int baud;                          /* speed in baud    75,... */
} MODEM_DATA;

int mdm_open(MODEM_DATA *);
int mdm_close(int);
int mdm_read(int, char *, size_t);
int mdm_write(int, char *, size_t);
int mdm_send(int, char *);
int mdm_receive(int, char *);
int mdm_chat(int, char *);
int mdm_lock(char *);
int mdm_unlock(void);

/*------ Error types in fax programs ---------------------------*/
#define	_noError_			(int)0
#define	_error_				(int)1
#define	_warning_			(int)2


/*----------------- Debugging level ----------------------------*/
#define	_NODEBUG				0
#define	_DEBUG				1

/*----------------- Delayed ------------------------------------*/
#define	_FAX_NOW				0
#define	_FAX_SPOOL			1

/*----------------- Devices -------------------------------------*/
#define	_DEVPRINTER			1		/* Druckerausgabe               */
#define	_DEVFAX				2		/* FAX-Ausgabe                  */
#define	_DEVTELEX			3		/* Telexausgabe                 */
#define	_DEVMODEM			4		/* MODEM-Ausgabe                */
#define	_DEVSCREEN			5		/* Bildschirmausgabe via Mail   */
#define	_DEVFILE				6		/* Ausgabe in Datei             */

/*----------- General----- --------*/
#define	_stringMax_			(int)128

/*----------- config file  --------*/
#define FAXCONFNAME			"psfaxconfig"
#define FAXCONFPATH			"/usr/fax"
#define _FAX_TMP				"/tmp"
#define _TIMESTAMPLEN		20
#define _FAX_BR_UNIPLEX		0
#define _FAX_MODEM			1

/*P----- fax configuration ---------------------------------*/
typedef struct {
   char   daemon[_stringMax_+1];			/*M where MARCO daemon is */
   char   node[_stringMax_+1];			/*N where utility is installed */
   char   path[_stringMax_+1];			/*P  */
   char   temp[_stringMax_+1];			/*T  */
   char   utility[_stringMax_+1];		/*U  */
} FAXCONFIG ;

/*----------------- Fax functions --- ----------------------------*/
PS_DLLAPI int PSSERCOM_fax(char *, char *, int, int, int);
PS_DLLAPI int PSSERCOM_faxsetConfig(char *);

/* global local FAX functions */
#ifdef ps_unix
int fax_Uniplex(char *, char *, int, int, int);
int fax_Hylafax(char *, char *, int, int, int);
#endif

#endif
