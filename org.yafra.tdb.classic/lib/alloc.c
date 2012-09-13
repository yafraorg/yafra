/**************************************************************/
/* modul:     alloc / realloc memory                          */
/*                                                            */
/* copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpdef.h>
#include <mpprolib.h>
#include "version.h"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/lib/alloc.c,v 1.2 2008-11-02 19:55:33 mwn Exp $";


/***************************************************************
 * function:   alloc/realloc a buffer with memchung as init
 *
 ***************************************************************/
void *MPalloc(void *oldptr, unsigned long *aktsize, long memchunk,
              unsigned long newsize, long structsize)
{
	long i, effnewsize;
	void *memptr;

	if (newsize > *aktsize)
		{
		if (memchunk > 0)
			{
			i = newsize / memchunk+1;
			effnewsize = i*memchunk*structsize;
			}
		else
			effnewsize = newsize * structsize;

		memptr = realloc(oldptr, (size_t)effnewsize);
		if (!memptr)
			{
			fprintf(stderr, "Fehler beim alloc von %d bytes", effnewsize);
			return(NULL);
			}
		*aktsize = effnewsize/structsize;
		return(memptr);
		}
	else
		return(oldptr);
}



/***************************************************************
 * function:   alloc/realloc a MEMOBJ with memchunk as init
 *
 ***************************************************************/
void *MPallocobj(MEMOBJ *memobj, int memchunk)
{
	unsigned int i, effnewsize;
	void *memptr;

	if (memobj->datalen > memobj->alloclen)
		{
		if (memchunk > 0)
			{
			i = memobj->datalen / memchunk+1;
			effnewsize = i*memchunk;
			}
		else
			effnewsize = memobj->datalen;

		memptr = realloc((void *)memobj->buffer, (size_t)effnewsize);
		if (!memptr)
			{
			fprintf(stderr, "Fehler beim alloc von %d bytes", effnewsize);
			return(NULL);
			}
		memobj->alloclen = (unsigned long)effnewsize;
		return(memptr);
		}
	else
		return((void *)memobj->buffer);
}
