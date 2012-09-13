/*D*************************************************************************
 * Modul:			GUI - dialog
 * Description: 	Audio and sound handling functions
 *						
 * Copyright: yafra.org, Basel, Switzerland
 * Author:    Administrator
 ***************************************************************************
 */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/uaudio.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";

#include <uinclude.h>
#include <psmume.h>

/*F--------------------------------------------------------------------------
 *  Function:	xUIaudioPlay ()
 *					General wrapping routine           
 *
 *  In:			a wave file 
 *  out:			-
 *  Return:		-
 *---------------------------------------------------------------------------
 */
void xUIaudioPlay(char *aWavefile)
{
	extern int DebugFlag;
	extern ApplicationData app_data;   /* xUIappdefaults.h */
	extern MP_GLOBALPROFIL globprof;
	extern Boolean audioflag;

	/*-- Play audio file ----------*/
	if (audioflag == True)
		{
		PSAUDIOplay(aWavefile, globprof.hostname, 0, 1);
		if (DebugFlag)
			PSSYSdebug(NULL, NULL, "playing sound file: %s", aWavefile);
		}
}
