/*D***********************************************************
 * Name:      AKTiobuffer.c
 * Modul:     AKT base moduls
 *            handling of layout, forms, lines... etc 
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header";

/* MarcoPolo API includes */
#include <mpact.h>         /* Standart Includefile   */


/*P--- PROTOTYPES ----------------------------------------------------------*/


/*P--- GLOBALS -------------------------------------------------------------*/
#ifdef ps_unix
char		TmpOutFilename[] = "/tmp/OUT_BUFFER";
#else
char		TmpOutFilename[] = "\\TEMP\\OUT_BUFFER.txt";
#endif

/*F--------------------------------------------------------------------------
 *  Function:	AKTiobufferInit ()
 *					init the buffer variables and structures 
 *					OutBuffer is a static public buffer to avoid stream positionning 
 *             problems. A dynamic realloc could bring inconsistence.
 *
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int AKTiobufferInit(void)
{
	extern	FILE		*FPoutbuf;
	extern	char		OutBuffer[];    /* this is the tmp-buffer for FPoutbuf */

	int		retcode;

	/*--- general inits ------------*/
	FPoutbuf = fopen( TmpOutFilename, _P_WRITEUPDATE_);
	if (FPoutbuf == NULL)
		return((int)MPERROR);
	/*--- Set FULLY Buffered (all stay in buffer) ------------*/
	retcode = setvbuf( FPoutbuf, OutBuffer, _IOFBF, 15*STARTMEMCHUNK );
	if (retcode != 0)
		return((int)MPERROR);

	return ((int)MPOK);
}



/*F--------------------------------------------------------------------------
 *  Function:	AKTiobufferClose ()
 *					flushing is not necessary but used to control OUT_BUFFER
 *
 *  In:			- 
 *  out:			-
 *  Return:		- 
 *---------------------------------------------------------------------------
 */
int AKTiobufferClose(void)
{
	extern	FILE		*FPoutbuf;

	int		retcode;

	/*--- write data: this enables the file OUT_BUFFER to be inspected -----*/
	retcode = fflush( FPoutbuf);
	/*--- close properly before end of action ------------------------------*/
	retcode = fclose( FPoutbuf);
	if (retcode != 0)
		return((int)MPERROR);

	/*--- erase file to avoid problems when new actions are installed ------*/
#ifdef ps_unix
	(void)sleep(2); 
#endif
	if (unlink(TmpOutFilename) == (int)-1) 
		return((int)MPERROR);

	return ((int)MPOK);
}
