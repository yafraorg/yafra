/*************************************************************
 * header:    IPC library local header file for SOCKETS
 *
 * copyright: Yafra.org, Switzerland, www.pisoag.com
 *************************************************************/
/*R
 RCS Information:
 $Id: socket.h,v 1.2 2004-02-01 22:09:29 mwn Exp $
*/

#ifndef PSSOCKETDEFINED
#define PSSOCKETDEFINED

/* Includes */
#ifdef ps_unix
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#endif