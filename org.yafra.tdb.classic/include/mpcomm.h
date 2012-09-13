/*D************************************************************/
/* Header:    Prozesskommunikation zwischen DBI und GUI       */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpcomm.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/

/* Anzahl komm Elemente */
#define ANZKOMM		5

/* Kommunikationsstruktur */
typedef struct
{
	unsigned char typ[ANZKOMM];      /* Kommunikationssteuerung   */
	char *buffer;                    /* Kommunikationsbuffer      */
	unsigned long alloclen;          /* L�nge des alloz. Buffers  */
	unsigned long datalen;           /* L�nge der Daten           */
} COMMOBJ;

/* Kommunikationsweg */
#define SEND			(unsigned short int)0
#define RECV			(unsigned short int)1

/* Kommunikationsstatus */
#define COMMSTAT     comm.typ[0]
#define MESSAGEOK 		0x00  /* alles OK                  */
#define MESSAGEWARNING	0x01  /* Warnung                   */
#define MESSAGEERROR 	0x02  /* Error Meldung             */
#define MESSAGEINFO  	0x03  /* Infomeldung               */
#define MESSAGEPCX      0x04  /* Pixelbild als Meldung     */
#define MESSAGEINFOPCX  0x05  /* Infomeldung und Pixelbild */
#define MESSAGEDBERROR  0x06  /* Datenbank Error           */

/* Kommunikationstypen */
#define COMMTYP		comm.typ[1]
#define GLOBAL				0x10   /* standard calls 0x10 - 0x4f */
#define SELECT				0x11
#define CHOOSE				0x12
#define SELECTITEM      0x13
#define ACTION 			0x14
#define ONEITEM			0x15
#define INFO   			0x16
#define DELETEMENU	 	0x17
#define DELETEFIELD		0x18
#define IMMEDIATCALL    0x19
#define NEXTMENU        0x1a
#define OPTIONTOGGLE    0x1b
#define MATRIXSELECT    0x1c   /* select on matrix */
#define MATRIXACTION    0x1d
#define HELPCALL        0x1e   /* GUI calls for a help text */
#define BMSTART         0x50   /* booking calls 0x50 - 0x5f */
#define BMDLN           0x51
#define BMDLNCHOOSE     0x52
#define BMOBJCHOOSE     0x54
#define BMBOOK          0x55
#define BMDLTCHOOSE     0x56
#define BMDLTEND        0x58
#define BMCOMMIT        0x5e
#define BMEND           0x5f
#define GRAINPUT   		0xa0   /* graphic calls  0xa0 - 0xaf */
#define GRASELECT			0xa1
#define GRACHOOSE			0xa2
#define GRAREFRESH  		0xa3
#define GRASEND			0xa4
#define _TEST 				0xff

/* Aktionstypen */
#define ACTIONTYP		comm.typ[2]
#define INSERT				0x10  /* Einfuege Modus            */
#define UPDATE				0x11  /* Mutations Modus           */
#define MPDELETE			0x12  /* Loesch Modus              */
#define GLOBINIT			0x20  /* allg. Init                */
#define GLOBSEND			0x21  /* Globales Menu senden      */
#define QUIT				0x22  /* Ende von MarcoPolo        */
#define LABELINIT			0x23  /* Labels init               */
#define MAKELABELFILE   0x24  /* Labelfile for app-def.    */
#define INFOTXT         0x30
#define INFOPCX         0x31
#define INFOTXTANDPCX   0x32
#define MATRIXBINARY    0x35  /* matrix binary mode             */
#define MATRIXSHOW      0x36  /* matrix show/select mode        */
#define MATRIXEDIT      0x37  /* matrix input/edit mode         */
#define GRASHOWINFO     0x38  /* graphic show info for region   */
#define GRAMAKEACTION   0x39  /* graphic make action for region */

/* Menu */
#define MENUNR			comm.typ[3]
#define NOMENU				0x00

/* Feldnummer */
#define FELDNR			comm.typ[4]
#define NOFIELD			0x00
