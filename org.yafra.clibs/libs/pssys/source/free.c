/**************************************************************
 * modul:     system memory freeing routines
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/free.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <stdlib.h>

/* piso includes */
#include <pssys.h>


/************************************************************
 * free up memory
 *
 * free up memory at pointer aPtr
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
void PSSYSfree(void *aPtr /* pointer for freeing memory */)
{
	if (aPtr != NULL)
		free(aPtr);

	aPtr = NULL;
}

/************************************************************
 * free up a memory object
 *
 * free up a memory object
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
void PSSYSfreeobj(PSmemobj *aMemobj /* memory object to free */)
{
	if (aMemobj->buffer != NULL)
		free(aMemobj->buffer);

	aMemobj->buffer = 0;
	aMemobj->datalen = 0;
	aMemobj->alloclen = 0;
}


/************************************************************
 * free up a memory array with all it's pointer
 *
 * free up all elements in an dynamic allocated array
 * and at last free up the array memory at pointer aPtr
 *
 * returns     nothing
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator, 1994
 **************************************************************/
void PSSYSfreearray(char **aPtr,    /* pointer of array to free */
                    int aArraysize  /* count of elements in thist array */)
{
	int i;

	/*!!! on other than HP-UX bugy !!! */

	/* free arrays */
	for (i=0; i < aArraysize; i++)
		{
		if (aPtr[i] != NULL)
			free((void *)aPtr[i]);
		}

	/* free pointer to arrays */
	if (aPtr != NULL)
		free((void *)aPtr);
}
