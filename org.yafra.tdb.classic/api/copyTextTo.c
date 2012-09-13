/*D***********************************************************
 * Modul:     API - mem copy of strings
 *            copy string and deletes white spaces / blanks
 *
 * copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/copyTextTo.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

char *copyTextTo(char *nachBuffer , char *vonBuffer , int anzByte )
{
	char *ptr;

// TODO check string end NULL - strncpy would be saver but seems to generate issues - not clear happens at label, msg
//	nachBuffer[anzByte-1] = (char)NULL;
//	vonBuffer[anzByte-1] = (char)NULL;
//	(void)strncpy(nachBuffer, vonBuffer, (size_t)anzByte-1);
	(void)memcpy((void *)nachBuffer, (void *)vonBuffer, (size_t)anzByte);
	nachBuffer[anzByte-1] = (char)NULL;
	ptr = (char *)&nachBuffer[anzByte] - (int)1;

	while ( (*ptr == ' ') || (*ptr == (char)NULL) )
		{
		*ptr = (char)NULL;
		if (nachBuffer == ptr)
			break;
		ptr--;
		}

	return(nachBuffer);
}
