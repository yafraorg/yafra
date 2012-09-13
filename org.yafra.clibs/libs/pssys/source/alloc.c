/**************************************************************
 * modul:     system memory allocation routines
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/alloc.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <stdlib.h>

/* piso includes */
#include <pssys.h>


/************************************************************
 * alloc/realloc a chunk of bytes to a pointer
 *
 * alloc/realloc a chunk of bytes to a pointer. It's similar
 * to alloc, but it's for chunk allocation.
 *
 * returns     pointer of new buffer or NULL if error
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI void *PSSYSalloc(void *oldptr,     /* pointer to the current memory, for init set it to NULL */
                 unsigned int *aktsize, /* actual memory size */
                 int memchunk,     /* size of memory chunk */
                 unsigned int newsize, /* size of new memory pointer */
                 size_t structsize /* sizeof of memory pointer value */ )
{
	unsigned int i, effnewsize;
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



/************************************************************
 * alloc/realloc a memory object (MEMOBJ)
 *
 * if the old pointer and old alloclen is NULL, then alloc
 * new memory, else realloc to the new desired size with
 * filling up to the chunk value
 *
 * returns     the new pointer or NULL if error
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland
 *
 * author:     Administrator, 1993
 **************************************************************/
PS_DLLAPI void *PSSYSallocobj(PSmemobj *memobj,  /* memeory object to realloc */
                   int memchunk        /* memchunk size */)
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
