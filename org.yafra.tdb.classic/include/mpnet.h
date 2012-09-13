/*DH**********************************************************
 * header:    MPNET - main include for all dbinet files
 *
 * copyright: yafra.org, Switzerland, 2004
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.4 $
 **************************************************************/


/* protocol definitions:

see mapo/xml for the following definitions:

INIT:
1) client sends tdb-login.xml
2) server reads & updates tdb-login.xml
3) server updates tdb-login.xml
4) server sends tdb-login.xml
5) client reads tdb-login.xml

*/

/* PS system library */
#include <pssys.h>

#include <string.h>
#include <stdlib.h>

/* MAPO comm defines for travelDB library */
#include <mpcomm.h>
extern COMMOBJ comm;

/* MAPO Object length */
#include <mpstrlen.h>

/* MAPO Objektdefinitionen (defines and structures) */
#include <mpobjdef.h>
#include <mpobjvar.h>

/* MAPO General definitions */
#include <mpdef.h>

/* MAPO Prototypes */
#include <mpprolib.h>

/* general service definitions for the server part */
#define MPNET_SERVICE "mpnet"
#define MPNET_PROT "tcp"

#define MPNET_QUERYDYN		1
#define MPNET_QUERYCMD		2
#define MPNET_DBIINFO		3
#define MPNET_WWW				4

#define MPNET_OK				0
#define MPNET_NOK				1
#define MPNET_DBCERROR		2
#define MPNET_SQLERROR		3
#define MPNET_SYSTEMERROR	4

/* set it to NULL if you need output on console else set it to a filename */
#define MPNET_DBGFILE      NULL

/* includes of libXML */
#include <libxml/encoding.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#define MY_ENCODING "ISO-8859-1"
