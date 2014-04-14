/**************************************************************/
/* Modul:     modem input/output functions                    */
/*                                                            */
/* Functions: mdm_read                                        */
/*            mdm_write                                       */
/*            mdm_send                                        */
/*            mdm_receive                                     */
/*            mdm_chat                                        */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/mdm_io.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#ifdef ps_cygwin
#undef ps_unix
#endif

#ifdef ps_unix

/* Includes */
#include <pssercom.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

extern FILE *PortLog;   /* Logfile for communication port */

/*************************************************************
 * read one byte from modem
 *
 * read one byte from the modem device, the device (a file descriptor)
 * has to be open
 *
 * returns     int as error code
 *
 * library:    modem
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator
 **************************************************************/
int mdm_read(int mdm_dev,  /* modem file descriptor */
		char *buf,           /* buffer */
		size_t buf_size      /* buffer length */)
{
	int cret;

	cret = read(mdm_dev, buf, buf_size);

#ifdef DEBUG
	if (cret == 1)
		fprintf(PortLog, "\n IN:  %c", *buf);
	else if (cret > 1)
		fprintf(PortLog, "\n IN:  %s", buf);
	else
		fprintf(PortLog, "\n IN:  no data available");
#endif

	return(cret);
}

/*************************************************************
 * write one byte to the modem
 *
 * write one byte to the modem device, the device (a file descriptor)
 * has to be open
 *
 * returns     int as error code
 *
 * library:    modem
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator
 **************************************************************/
int mdm_write(int mdm_dev, /* modem file descriptor */
		char *buf,           /* buffer */
		size_t buf_size      /* buffer size */)
{
	int cret;

	cret = write(mdm_dev, buf, buf_size);

#ifdef DEBUG
	if (cret == 1)
		fprintf(PortLog, "\n OUT: %c", *buf);
	else if (cret > 1)
		fprintf(PortLog, "\n OUT: %s", buf);
	else
		fprintf(PortLog, "\n OUT: no data write");
#endif

	return(cret);
}


/*************************************************************
 * send a string to the modem
 *
 * send a string to the modem device, the device (a file descriptor)
 * has to be open. This function calls the mdm_write().
 *
 * returns     int as error code
 *
 * library:    modem
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator
 **************************************************************/
int mdm_send(int mdm_dev, char *cp)
{
	(void)mdm_write(mdm_dev, cp, strlen(cp));
	(void)mdm_write(mdm_dev, "\r", 1);
}


/*************************************************************
 * receive a string from the modem
 *
 * receive a string from the modem device, the device (a file descriptor)
 * has to be open. This function calls the mdm_read().
 *
 * returns     int as error code
 *
 * library:    modem
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator
 **************************************************************/
int mdm_receive(int mdm_dev, char *cp)
{
	char c;
	long chars;

	while (*cp)
		{
		ioctl(mdm_dev, FIONREAD, &chars);
		if (chars > 0)
			{
			(void)mdm_read(mdm_dev, &c, 1);
			printf("%c", c);
			if (c == *cp)
				cp++;
			}
		}

	for (;;)
		{
		ioctl(mdm_dev, FIONREAD, &chars);
		if (chars > 0)
			{
			(void)mdm_read(mdm_dev, &c, 1);
			if (c == 0x0a)
				break;
			}
		}
}


/*************************************************************
 * chat with the modem
 *
 * send and receive strings from the modem
 *
 * returns     int as error code
 *
 * library:    modem
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator
 **************************************************************/
int mdm_chat(int mdm_dev, char *cp)
{
	char buf[400];
	int out = 1;

	strcpy (buf, cp);
	cp = strtok(buf, "\t");
	if (cp)
		{
		do {
			if (out)
				(void)mdm_send(mdm_dev, cp);
			else
				(void)mdm_receive(mdm_dev, cp);
			out = !out;
			} while(cp = strtok(NULL, "\t"));
		}
}

#endif
