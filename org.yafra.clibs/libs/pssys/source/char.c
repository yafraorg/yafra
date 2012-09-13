/**************************************************************
 * modul:     character handling
 *
 * copyright: Yafra.org, Switzerland
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/char.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <signal.h>
#include <ctype.h>

/* piso includes */
#include <pssys.h>

/************************************************************
 * install a signal handler
 *
 * install a signal handler
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
PS_DLLAPI void PSSYSstrLower(char *aStr  /* string to convert to lower chars */)
{
	int i;

	for (i=0;;i++)
		{
		if (aStr[i] == NULL)
			break;
		aStr[i] = tolower((int)aStr[i]);	
		}
}

PS_DLLAPI void PSSYSstrUpper(char *aStr  /* string to convert to upper chars */)
{
	int i;

	for (i=0;;i++)
		{
		if (aStr[i] == NULL)
			break;
		aStr[i] = toupper((int)aStr[i]);	
		}
}
