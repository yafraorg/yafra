/**************************************************************/
/* Modul:     manage communication port                       */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/mdm_port.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#ifdef ps_unix

/* Includes */
#include <string.h>
#include <unistd.h>
#include <pssercom.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

/**************************************************************/
/* Function:  open a communication device/port                */
/*                                                            */
/**************************************************************/
int mdm_open(MODEM_DATA *mdm)
{
	int modem;
#ifdef ps_osx
	struct termios attr;
#elif
	struct termio attr;
#endif
	int fstat;

	modem = open(mdm->port, O_RDWR|O_NONBLOCK);
	if (modem < 0)
		return(0);

	if (mdm_lock(mdm->port))
		fatal ("Device locked");

	fstat = fcntl(modem, F_GETFL, 0);
	if (fcntl(modem, F_SETFL, fstat & ~O_NONBLOCK) == -1)
		return(0);

/*	ioctl(modem, TCGETA, &old_attr); */
	memset(&attr, 0, sizeof(attr));

// TODO migrate to tcsetattr instead of ioctl
#ifdef ps_osx
	/* Set raw mode on tty device 'modem' */
	attr.c_iflag = IGNBRK|IGNPAR;
	attr.c_oflag = 0;
	attr.c_cflag = mdm->baud|CS8|CREAD|CLOCAL|HUPCL;
	attr.c_lflag = 0;
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 2;
	ioctl(modem, TIOCSETAF, &attr);
#elif
	/* Set raw mode on tty device 'modem' */
	attr.c_iflag = IGNBRK|IGNPAR;
	attr.c_oflag = 0;
	attr.c_cflag = mdm->baud|CS8|CREAD|CLOCAL|HUPCL;
	attr.c_lflag = 0;
	attr.c_line  = 0;
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 2;
	ioctl(modem, TCSETAF, &attr);
#endif
	sleep(1);

	return(modem);
}

/**************************************************************/
/* Function:  close a communication device/port               */
/*                                                            */
/**************************************************************/
int mdm_close(int modem)
{
	close(modem);
	mdm_unlock();
}

#endif
