/**************************************************************
 * modul:     Windows Tools - connection to Office Progis
 *
 * tools:     DDE write only as client
 *            OLE integration as client
 *
 * copyright: Yafra.org, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/wintools.c,v 1.2 2004-02-05 18:47:30 mwn Exp $";

/* piso includes */
#include <pssys.h>
#include <psportable.h>

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#ifdef ps_win
#include <fcntl.h>
static void DDEstartserver(int, int);
#endif

#ifdef ps_unix
#include <unistd.h>
#include <fcntl.h>
#endif

/************************************************************
 * DDE starter
 *
 * starts a DDE communication
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSddeOpen(char *aDDEsource, int *aDDEfd, int aDDEtype)
{
	extern int errno;

	int cret = PSOK;
	int dde_fd = 0;
	int trycnt = 0;

#ifdef ps_win

tryagain:
	if (trycnt < 3)
		{
		dde_fd = open(aDDEsource, O_WRONLY);
		if (dde_fd < 1)
			{
			/* error or DDE server not running */
			if (errno == 0)
				{
				/* start server, sleep and tryagain */
				DDEstartserver(aDDEtype, trycnt);
//				sleep(3);
				trycnt++;
				goto tryagain;
				}
			else
				{
				/* it's an error with opening this source */
				cret = errno;
				return(cret);
				}
			}
		else
			*aDDEfd = dde_fd;
		}
	else
		return(PSERROR);

#endif

	return(cret);
}

/************************************************************
 * Write to DDE Server
 *
 * help is integrated over WWW Browsers. So the page string
 * has to be an URL with help infos in it.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSddeWrite(int aDDEfd,
          const char *aMsg,
          ... )
{
	extern int errno;

	va_list ap;
	char tmpbuf[2*PS_MAXMSGLEN];
	int cret;
	size_t len;

	/* if no msg return */
	if (aMsg == NULL)
		return(PSERROR);

	/* manage variable arguments */
	va_start(ap, aMsg);
	cret = vsprintf(tmpbuf, aMsg, ap);

	len = strlen(tmpbuf);
	cret = write(aDDEfd, tmpbuf, len);

	cret = errno;

	va_end(ap);

	return(cret);
}

/************************************************************
 * close a DDE connection
 *
 * help is integrated over WWW Browsers. So the page string
 * has to be an URL with help infos in it.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSddeClose(int aDDEfd)
{
	int cret = PSOK;

	cret = close(aDDEfd);

	return(cret);
}


/**************************** STATIC **************************************/

#define KEYLEN 1024

static void DDEstartserver(int type, int trycnt)
{
	size_t execlen = KEYLEN;
	char exec[KEYLEN];
	char tmpexec[KEYLEN];
	int cret;

#ifndef ps_unix
	switch (type)
		{
		case PSSYS_PRG_WINWORD:
			/* WinWord */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "WinWord.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				case 1:
					cret = PSSYSkeyRead(1, "SOFTWARE\\Microsoft\\Office\\8.0\\Word\\InstallRoot",
					       "Path", exec, execlen);

					if (cret == PSOK)
						{
						execlen = strlen(exec);
						exec[execlen-1] = (char)NULL;
						(void)sprintf(tmpexec, "%s%s", exec, "\\WinWord.exe\"");
						(void)PSSYSexecute(tmpexec);
						}
					break;
				case 2:
					cret = PSSYSkeyRead(1, "SOFTWARE\\Microsoft\\Microsoft Office\\95\\InstallRoot",
					       NULL, exec, execlen);

					if (cret == PSOK)
						{
						execlen = strlen(exec);
						exec[execlen-1] = (char)NULL;
						(void)sprintf(tmpexec, "%s%s", exec, "\\WinWord\\WinWord.exe\"");
						(void)PSSYSexecute(tmpexec);
						}
					break;
				default:
					break;
				}
			break;
		case PSSYS_PRG_EXCEL:
			/* Excel */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "Excel.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		case PSSYS_PRG_ACCESS:
			/* Access */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "Msaccess.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		case PSSYS_PRG_POWERPOINT:
			/* PowerPoint */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "Powerpnt.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		case PSSYS_PRG_OUTLOOK:
			/* Outlook */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "Outlook.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		case PSSYS_PRG_IE:
			/* IE */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "Iexplore.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		case PSSYS_PRG_NETSCAPE:
			/* Netscape */
			switch (trycnt)
				{
				case 0:
					(void)sprintf(tmpexec, "%s", "netscape.exe");
					(void)PSSYSexecute(tmpexec);
					break;
				}
			break;
		}
#endif
}
