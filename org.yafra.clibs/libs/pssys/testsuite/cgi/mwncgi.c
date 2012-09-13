/*D***********************************************************
 * modul:     API - CGI C client which uses pssys lib
 *
 *
 * copyright: yafra.org, 2002, Switzerland
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.1 $
 **************************************************************/
static char rcsid[]="$Id: mwncgi.c,v 1.1 2002-11-23 09:28:07 mwn Exp $";

/* Include or define globals */
#include <stdio.h>
#include <stdlib.h>
#include <ipc.h>
#include <pssys.h>

#define CLBUFSIZE 1024


/* global variables */
	PSmemobj EntriesObj;    /* entries memory object                */
	int	NumEntries;         /* number of entries read               */
/* end globals */


void ShowEntries(PSCGIentry *entries, int NumEntries)
{
	/*----------------------------------------------*/
	/* Show the name/value pairs submitted          */
	/*----------------------------------------------*/

	char *name;
	char *value;
	int i;

	PSSYShtmlInitText("Show entries");
	PSSYShtmlHeadingText(1,"Show entries");
	if (NumEntries >= 0)
		{
		printf("You submitted the following name/value pairs");
		PSSYShtmlParagraph();
		PSSYShtmlBeginUList();
 		for (i=0; i <= NumEntries; i++)
 			{
 			name = entries[i].nameobj.buffer;
			value = PSCGIentrystring(entries,name,NumEntries);
 			PSSYShtmlListItemTag();
			PSSYShtmlCodeText(name);
			printf(" = %s%c", value,10);
			}
    	PSSYShtmlEndUList();
		}
	PSSYShtmlEndText();

} /* ShowEntries */


int main(int argc, char *argv[])
{
	PSCGIentry *entries;    /* name/value pairs given by form       */

	entries = PSCGIinitpost(&EntriesObj,&NumEntries);
	ShowEntries(entries, NumEntries);
	PSCGIfreeEntries(&EntriesObj,NumEntries);

} /* main */
