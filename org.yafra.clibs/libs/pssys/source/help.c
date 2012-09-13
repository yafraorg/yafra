/**************************************************************
 * modul:     system memory allocation routines
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/help.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* piso includes */
#include <stdlib.h>
#include <pssys.h>

/************************************************************
 * help function
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
PS_DLLAPI void PSSYShelp(char *page /* Help page in URL syntax*/)
{
	PSSYSwww(page, PSSYS_WWWTYPNS);
}
