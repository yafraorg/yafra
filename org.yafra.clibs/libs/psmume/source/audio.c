/*D***********************************************************
 * modul:     AUDIO - player function
 *
 * copyright: Yafra.org, Switzerland     
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/audio.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <psmume.h>
#include "version.h"

/************************************************************
 * play an audio WAV file on a workstation with sound support
 *
 * audio player
 *
 * returns     int as an error code
 * 
 * library:    audio
 *
 * include:    psaudio.h
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
int PSAUDIOplay(char *filename, char *server, int stereoflag, int loop)
{
	int status = 0;

#if defined (ps_hpux)
	status = HPaudio_play(filename, server, stereoflag, loop);
#endif
#if defined (ps_linux)
	status = LINUXaudio_play(filename, server, stereoflag, loop);
#endif
#if defined (ps_win)
	status = WINaudio_play(filename, server, stereoflag, loop);
#endif

	return(status);
}

int PSAUDIOrecord(char *filename, char *server, int stereoflag, int loop)
{
	int status = 0;

	return(status);
}
