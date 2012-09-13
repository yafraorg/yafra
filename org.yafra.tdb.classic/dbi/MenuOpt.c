/*D***********************************************************
 * Modul:     DBI - control
 *            option toggles
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/MenuOpt.c,v 1.2 2008-11-02 19:55:39 mwn Exp $";

int MenuOptiontoggles(int len, char *buffer)
{
	extern unsigned char logging_sql;
	extern unsigned char logging_sqltm;
	extern unsigned char logging_user;
	extern unsigned char logging_booking;
	extern unsigned char bm_dlnatonce;
	extern unsigned char alphaordering;
	extern unsigned char AutoInfo;
	extern unsigned char selectfromtemp;
	extern int DebugFlag;
	extern FILE *MP_DBIDEBUGFILE;

	int cret;
	int status=(int)MPOK;
	int next = (int)TRUE;
	int state;
	int toggle;
	char *ptr;

	ptr = comm.buffer;
	while (next == (int)TRUE)
		{
		if (*ptr == NULL)
			{
			next = (int)FALSE;
			continue;
			}		
		cret = sscanf(ptr, "%d%*1c%d", &toggle, &state);
		if (cret != 2)
			{
			next = (int)FALSE;
			continue;
			}
		switch(toggle)
			{
			case (unsigned char)_TOGDBLOG:
				if (state == (int)TRUE)
					{
					logging_sql = (unsigned char)TRUE;
					logging_sqltm = (unsigned char)FALSE;
					}
				else
					{
					logging_sql = (unsigned char)FALSE;
					logging_sqltm = (unsigned char)FALSE;
					}
				break;
			case (unsigned char)_TOGUSERLOG:
				if (state == (int)TRUE)
					{
					logging_user = (unsigned char)TRUE;
					logging_booking = (unsigned char)TRUE;
					}
				else
					{
					logging_user = (unsigned char)FALSE;
					logging_booking = (unsigned char)FALSE;
					}
				break;
			case (unsigned char)_TOGAUTOINFO:
				if (state == (int)TRUE)
					AutoInfo = (unsigned char)TRUE;
				else
					AutoInfo = (unsigned char)FALSE;
				break;
			case (unsigned char)_TOGDLN:
				if (state == (int)TRUE)
					bm_dlnatonce = (unsigned char)TRUE;
				else
					bm_dlnatonce = (unsigned char)FALSE;
				break;
			case (unsigned char)_TOGDATORDER:
				if (state == (int)TRUE)
					alphaordering = (unsigned char)TRUE;
				else
					alphaordering = (unsigned char)FALSE;
				break;
			case (unsigned char)_TOGSELFROMTMP:
				if (state == (int)TRUE)
					selectfromtemp = (unsigned char)TRUE;
				else
					selectfromtemp = (unsigned char)FALSE;
				break;
			case (unsigned char)_TOGDEBUG:
				if (state == (int)TRUE)
					DebugFlag = (unsigned char)TRUE;
				else
					DebugFlag = (unsigned char)FALSE;
				if (DebugFlag)
					PSSYSdebug(MP_DBIDEBUGFILE, PROGRAMNAME, "toggled DebugFlag %d", DebugFlag);
				break;
			default:
				break;
			}
		ptr = strchr(ptr, (int)_MPSYMB_CR);
		ptr++;
		}

	comm.datalen = 0;
	comm.buffer[0] = NULL;

	return(status);
}
