/**************************************************************/
/* Modul:     hostname and tcp utilities                      */
/*                                                            */
/* Copyright: Yafra.org     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/utils.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>

#include <psipc.h>

/* for registry keys include windows stuff */
#ifdef ps_win
#include <windows.h>
#endif

#define PSIPC_DEFNAME "localhost"
#ifdef ps_winnt
#define PSIPC_DEFREGKEY "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters"
#else
#define PSIPC_DEFREGKEY "SYSTEM\\CurrentControlSet\\Control\\ComputerName\\ComputerName"
#endif

/************************************************************
 * IPC get the local hostname
 *
 * retreives the hostname of the current machine resp. the
 * local hostname. Under Windows NT it's getting it from the
 * registry settings from the TCP/IP DNS configuration, cause of
 * some problems with Exceed or other gethostbyname problems.
 * You can specify if you need only hostname or FQDN with aFlag.
 * aFlag == 0 means only hostname and aFlag == 1 means FQDN.
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCgetHostname(char *aName,  /* IP hostname */
                               int aNamelen, /* length of aName pointer */
                               int aFlag     /* Flag if FQDN or not */)
{
	int cret;
	size_t len;

#ifdef ps_win
	HKEY hKey;
	LONG cbMaxValueLen, cbMRUList = 25;
	LPDWORD hostlen = IPCMAXHOSTLEN - 1;
	LPBYTE hostname[IPCMAXHOSTLEN];
#endif

#ifdef ps_unix
	char hostname[IPCMAXHOSTLEN];
	int hostlen = IPCMAXHOSTLEN - 1;
#endif

	cret = (int)IPCOK;
	(void)strcpy(hostname, PSIPC_DEFNAME);

#ifdef ps_win
	if (RegOpenKey(HKEY_LOCAL_MACHINE, PSIPC_DEFREGKEY, &hKey) == ERROR_SUCCESS)
		{
		RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		    NULL, &cbMaxValueLen, NULL, NULL ) ;
		if (cbMaxValueLen > 0)
			{
			// Get MRUList value
#ifdef ps_winnt
			RegQueryValueEx(hKey, "Hostname", NULL, NULL, hostname, &hostlen) ;
#else
			RegQueryValueEx(hKey, "ComputerName", NULL, NULL, hostname, &hostlen) ;
#endif
			}   
		// Close registry key
		RegCloseKey(hKey) ;
		}
#endif

#ifdef ps_unix
	cret = gethostname(hostname, hostlen);
#endif

	len = strlen((char *)hostname);
	if (len > (size_t)aNamelen)
		{
		}
	else
		(void)strcpy(aName, (char *)hostname);

	return(IPCOK);
}
