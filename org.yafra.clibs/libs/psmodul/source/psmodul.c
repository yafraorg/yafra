/**************************************************************/
/* Modul:     check if Program is allowed to run              */
/*                                                            */
/* Copyright: Yafra.org, Switzerland                   */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#ifdef ps_unix
#include <unistd.h>
#endif
#include <psmodul.h>


/* RCS version string */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmodul/source/psmodul.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* generic version handling */
#include "version.h"

#define MASKE 0x1
#define ANZ_HP 18
#define ANZ_ULTRIX 1

#ifdef ps_winnt
#include "ntprot.h"
#endif

#ifdef ps_ultrix
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#endif

#ifdef ps_hpux
#include <sys/hilioctl.h>
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#ifdef ps_hpux
static int PSmodulHP(int);
#endif
#ifdef ps_ultrix
static int PSmodulDEC(int);
#endif
#ifdef ps_linux
static int PSmodulLINUX(int);
#endif
#ifdef ps_winnt
static int PSmodulWIN32(int, char*, int);
#endif

/************************************************************
 * LICENSE MODUL check function
 *
 * check if programm is allowed to run
 *
 * returns     char as license return code
 *
 * library:    libpsmodul.a
 *
 * copyright:  Yafra.org, 1994
 *
 * author:     Administrator
 **************************************************************/
int PSmodul(int aAppCode, char* aVersionString, int aTestflag)
{
	int modul_return = 0;

#ifdef ps_ultrix
	modul_return = PSmodulDEC(aAppCode);
#endif

#ifdef ps_hpux
	modul_return = PSmodulHP(aAppCode);
#endif

#ifdef ps_linux
	modul_return = PSmodulLINUX(aAppCode);
#endif

#ifdef ps_winnt
	modul_return = PSmodulWIN32(aAppCode, aVersionString, aTestflag);
#endif

	return(modul_return);
}

#ifdef ps_ultrix
static int PSmodulDEC(int idno)
{
  char s1[40];
  struct ifdevea address;
  int sock;
  int retvalue;
  long id, i;
  static long idmodul[ANZ_ULTRIX][2] = {
  {0x2b1bbb6c, 0x000000ff}, /* Yafra.org   Decstation 200        */
  };

  id = 0;
  bzero(&address, sizeof(address));
  sock = socket(AF_UNIX, SOCK_DGRAM, 0);
  if (sock >= 0) {
	strcpy(address.ifr_name, "ln0");
	if ((retvalue = ioctl(sock, SIOCRPHYSADDR, &address)) < 0) {
		strcpy(address.ifr_name, "se0");
		if ((retvalue = ioctl(sock, SIOCRPHYSADDR, &address)) < 0) {
			strcpy(address.ifr_name, "qe0");
			if ((retvalue = ioctl(sock, SIOCRPHYSADDR, &address)) < 0) {
			}
		}
	}
	close(sock);
	if (retvalue >= 0) {
		sprintf(s1, "%02x%02x%02x%02x%02x%02x", address.default_pa[0],
		address.default_pa[1], address.default_pa[2],
		address.default_pa[3], address.default_pa[4],
		address.default_pa[5]);
		sscanf(s1, "%x", &id);
	}

  for (i=0; i<ANZ_ULTRIX; i++) {
	if (id == idmodul[i][0])
		return((idmodul[i][1] >> bytnr & MASKE) ? TRUE : FALSE);
  }
  return(0);
  }
}
#endif

#ifdef ps_hpux
static int PSmodulHP(int bytnr)
{
  int i, fd, status;
  long wert, val, bufer;
  char describe[11];
  static long idmodul[ANZ_HP][2] = {
  {294452279, 0x000000ff}, /* Yafra.org   INSTALL 300/400                */
  {294439029, 0x000000ff}, /* Yafra.org   INSTALL 700                    */
  };

  fd=open("/dev/IDMODUL", 0);
  status=ioctl(fd, HILSC, describe);
  (void)close(fd);

  bytnr--;
  wert=0.0;
  for (i=4, val=1; i<8; i++, val *= 256){
   wert += (unsigned char)describe[i]*val;
   }

  for (i=0; i<ANZ_HP; i++) {
	if (wert == idmodul[i][0])
		return((idmodul[i][1] >> bytnr & MASKE) ? TRUE : FALSE);
  }
  return(0);
}
#endif

#ifdef ps_linux
static int PSmodulLINUX(int idno)
{
}
#endif

#if defined(ps_winnt) || defined(ps_win95)
static int PSmodulWIN32(int aApplId, char* aVersionString, int aTestflag)
{
	int retVal = 0;
	int errorCode;
	char errorMessage[100];

	retVal = IsHASPAvailable();

	if (retVal) {

		retVal = IsPsHASP();

		if (retVal) {

			retVal = CanApplRun(aApplId, aVersionString, &errorCode);

			if (!retVal) {

				switch (errorCode) {

				case ILLEGAL_ADDRESS:
					strcpy(errorMessage, "Illegal HASP memory access");
					break;

				case READ_FAIL:
					strcpy(errorMessage, "Unable to read HASP memory");
					break;

				case NO_LICENSE:
					strcpy(errorMessage, "No license found for this program");
					break;

				case BAD_VERSION:
					sprintf(errorMessage, "Your license is not valid for this program version - %s", aVersionString);
					break;

				case INVALID_VERSION:
					sprintf(errorMessage, "Invalid version string supplied to function 'CanApplRun'");
					break;

				default:
					strcpy(errorMessage, "Unknown error");

					}

				printf("Application may not run! %s (%d).\n", errorMessage, errorCode);

				}

			}
		else
			printf("Not a Ps HASP!\n");
		}
   else
		printf("HASP not found!\n");
   
   return (retVal);
}
#endif
