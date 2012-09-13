/*D***********************************************************
 * Modul:     read/get protocol buffer functions
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/lib/getbuf.c,v 1.2 2008-11-02 19:55:34 mwn Exp $
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpobjdef.h>
#include <mpmsg.h>
#include <mpdef.h>
#include <mpstrlen.h>
#include <mpprolib.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/getbuf.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

int MPgetSection(char *ptr, int *sectionlen, char terminator)
{
	int i;
	int section;
	char sect[_RECORDLEN];
	unsigned char endsection;

	/* init */
	endsection = (unsigned char)FALSE;
	*sect = NULL;
	section = (int)_UNDEF;
	i = 0;

	/* get characters until a terminator is found */
	while (!endsection)
		{
		/* check memory length */
		if (i > (int)_RECORDLEN)
			return(section);

		if (ptr[i] == terminator)
			{
			sect[i] = NULL;
			endsection = TRUE;
			continue;
			}
		sect[i] = ptr[i];
		i++;
		}

	/* set length of section string */
	*sectionlen = i;

	/* convert ascii to int */
	if (*sect != NULL)
		section = atoi(sect);

	return(section);
}


int MPgetTextsegment(char *ptr, MEMOBJ *dest, char terminator)
{
	unsigned int i = 0;

	/* init */
	dest->buffer[0] = NULL;

	/* get string till the terminator */
	for (i=0; *ptr != terminator; ptr++, i++)
		{
		/* check up memory length */
		if (i > dest->alloclen)
			{
			dest->buffer[0] = NULL;
			return((int)MPERROR);
			}
		dest->buffer[i] = *ptr;
		}

	/* set last char + 1 to NULL */
	dest->buffer[i] = NULL;

	/* set the string len */
	dest->datalen = i;

	return((int)MPOK);
}
