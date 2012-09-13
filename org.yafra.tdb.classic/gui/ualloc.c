/*D*************************************************************************
 * Modul:			GUI - Dialog		   ualloc.c 
 *            
 * Description:	Allocate memory for Marco Polo
 *						stop the main if error
 *
 * Functions:
 * 
 * 
 * Copyright: yafra.org, Basel, Switzerland
 ***************************************************************************
 */


#include <uinclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/ualloc.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";


/*F--------------------------------------------------------------------------
 *  Function:	xUIalloc ()
 *					a function requests memory to handle is job, check if possible
 *  In:			-old pointer and size parameters
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */

void *xUIalloc(
		void *oldptr,
		long *aktsize,
		long memchunk,
		long newsize,
		long structsize
		)

{
	long i, effnewsize;
	void *memptr;

#ifdef COMPILE
	if (newsize > *aktsize) {
		i =  newsize/memchunk+1;
		effnewsize = i*memchunk*structsize;
		memptr = realloc(oldptr, (size_t)effnewsize);
		if (!memptr)
			 xUImainStop( -1);
		*aktsize = effnewsize/structsize;
		return(memptr);
	} else {
		return(oldptr);
	}
#endif

	memptr = MPalloc( oldptr, (unsigned long *)aktsize, memchunk, newsize, structsize);
	if (!memptr)
		xUImainStop( -1);
	else
		return(memptr);
}
