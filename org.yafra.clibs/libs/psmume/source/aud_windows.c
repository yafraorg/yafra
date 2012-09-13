/*D***********************************************************
 * modul:     AUDIO functions for PC with MS-Windows
 *
 * copyright: Yafra.org, Switzerland     
 **************************************************************/
#ifdef ps_win

static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psmume/source/aud_windows.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <windows.h>
#include <mmsystem.h>
#include <psmume.h>

/************************************************************
 * play an audio WAV file on a Aserver
 *
 * audio player for LINUX
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
int WINaudio_play(char *filename, char *server, int stereoflag, int loop)
{
	BOOL cret;

	cret = PlaySound((LPCTSTR)filename, (HMODULE)NULL, SND_FILENAME);
	return(cret);
}
#endif
