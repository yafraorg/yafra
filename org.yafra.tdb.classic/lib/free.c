/*D************************************************************/
/* modul:     free a buffer                                   */
/*                                                            */
/* copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpdef.h>
#include <mpprolib.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/free.c,v 1.3 2008-11-23 15:44:39 mwn Exp $";


/***************************************************************
 * function:   free a memory pointer
 *
 ***************************************************************/
void MPfree(void *ptr)
{
	if (ptr != NULL)
		free(ptr);

	ptr = NULL;
}


/***************************************************************
 * function:   free up a MEMOBJ
 *
 ***************************************************************/
void MPfreeobj(MEMOBJ *memobj)
{
	if (memobj->buffer != NULL)
		free(memobj->buffer);

	memobj->buffer = 0;
	memobj->datalen = 0;
	memobj->alloclen = 0;
}


/***************************************************************
 * function:   free up an array
 *
 ***************************************************************/
void MPfreearray(char **ptr, int arraysize)
{
	int i;

	// TODO on other than HP-UX bugy - check if still valid with XP+ or Ubuntu

	/* free arrays */
	for (i=0; i<arraysize; i++)
		{
		if (ptr[i] != NULL)
			free((void *)ptr[i]);
		}

	/* free pointer to arrays */
	if (ptr != NULL)
		free((void *)ptr);
}
