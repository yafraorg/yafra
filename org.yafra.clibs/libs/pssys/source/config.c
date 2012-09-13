/**************************************************************
 * modul:     Configuration Tools
 *
 * tools:     DDE write only as client
 *            OLE integration as client
 *
 * copyright: Yafra.org, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/config.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* piso includes */
#include <stdlib.h>
#include <pssys.h>

#ifdef ps_cygwin
#undef ps_unix
#define ps_win
#endif

#ifdef ps_win
#include <windows.h>
#endif

/************************************************************
 * Config Key reader
 *
 * read a configuration entry identified by the aKey name
 * from the aConfig source and put it to aValue as return.
 * Integers are converted to characters.
 * In Windows Environment the aConfig is the registry classname,
 * like HKEY_LOCAL_MACHINE.
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1997
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSkeyRead(int aConfigtyp,
           char *aConfig,
           char *aKey,
           char *aValue,
           size_t aValueLen)
{
	int cret = PSOK;

#ifdef ps_win
	HKEY keyHandle;
	HKEY keyID;

	DWORD keyMaxValueLen, keySubKeys, keyMaxSubKeyLen, keyMaxClassLen;
	DWORD keyValues, keyMaxValueNameLen, keySecurityDescriptor;
	DWORD keyLen = (DWORD)(aValueLen - 1);
	FILETIME keyLastWrite;

	switch (aConfigtyp)
		{
		case 1:
			keyID = HKEY_LOCAL_MACHINE;
			break;
		case 2:
			keyID = HKEY_CURRENT_CONFIG;
			break;
		case 3:
			keyID = HKEY_CLASSES_ROOT;
			break;
		case 4:
			keyID = HKEY_CURRENT_USER;
			break;
		case 5:
			keyID = HKEY_USERS;
			break;
		default:
			keyID = HKEY_LOCAL_MACHINE;
		}

	if (RegOpenKey(keyID, aConfig, &keyHandle) == ERROR_SUCCESS)
		{
		RegQueryInfoKey(keyHandle, NULL, NULL, NULL, &keySubKeys, &keyMaxSubKeyLen,
		    &keyMaxClassLen, &keyValues, &keyMaxValueNameLen, &keyMaxValueLen,
		    &keySecurityDescriptor, &keyLastWrite);
		if (keyMaxValueLen > 0)
			{
			RegQueryValueEx(keyHandle, (LPTSTR)aKey, (LPDWORD)NULL,
			    (LPDWORD)NULL, (LPBYTE)aValue, &keyLen);
			}
		else
			cret = PSERROR;
		RegCloseKey(keyHandle);
		}
	else
		cret = PSERROR;
#endif

	return(cret);
}

/************************************************************
 * Write a configuration Key information
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
PS_DLLAPI int PSSYSkeyWrite(int aConfigtype,
              char *aConfig,
              char *aKey,
              char *aValue)
{
	int cret = PSOK;
	return(cret);
}

/************************************************************
 * read subkeys from a config key
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
PS_DLLAPI int PSSYSkeyReadTree(int aConfigtype,
char *aConfig, char *aKey, int aCount, char **aValue)
{
	int cret = PSOK;
	return(cret);
}

PS_DLLAPI int PSSYSkeyWriteTree(int aConfigtype,
          char *aConfig,
          char *aKey,
          int aCount,
          char **aName,
          char **aValue)
{
	int cret = PSOK;
	return(cret);
}
