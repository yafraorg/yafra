/*D***********************************************************
 * Modul:     DBI - database action
 *            Programm
 *
 * Copyright: yafra.org, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPRGinput.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

#define MSG1	(int)15
#define MSG2	(int)26
#define MSG3	(int)64

int PRGinput(int len , char *buffer )
{
	extern PROGRAMM prg;
	extern BEZEICHNUNG bez;
	extern TEXTE txt;
	extern SAISON sai;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL );
	if (status != (int)MPOK )
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		prg.prg_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		{
		prg.prg_id = (int)_UNDEF;
		prg.textid = (int)_UNDEF;
		txt.textid = (int)_UNDEF;
		}

	bez.s_id = (int)sprache;
	bez.typ = (int)_PROGRAMM;
	(void)copyTextTo( bez.bez, to_buffers[MPRG_BEZ], (int)_CHAR30 );
	if (*bez.bez != NULL )
		{
		if ( *to_buffers[MPRG_SAI] != NULL )
			prg.sai_id = (int)MPAPIselectEntry( (int)_SAISON, to_buffers[MPRG_SAI],
			   (char *)&sai, sizeof( SAISON ), sizeof( prg.sai_id ) );
		else
			prg.sai_id = (int)_UNDEF;

     	(void)copyTextTo(prg.code, to_buffers[MPRG_CODE], (int)_KRZLLEN);

		txt.typ = (int)_PROGRAMM;
		txt.s_id = (int)sprache;
		txt.textid = prg.textid;
		prg.textid = xTxtWrite( to_buffers[MPRG_TXT] );

		status = WriteEntry( (int)_PROGRAMM, (char *)&prg, &bez );
		if ( status == (int)MPERROR )
			prg.prg_id = (int)_UNDEF;
		else
			(void)WriteInfo((int)_PROGRAMM, (char *)&prg, buffer);
		}
	else
		{
		UtilMsg((int)MSG2, MSGTYP_ERROR, NULL);
		prg.prg_id = (int)_UNDEF;
		status = (int)MPERROR;
		}

	UtilSplitFreeMenubuffer( to_buffers );
	return( status );
}
