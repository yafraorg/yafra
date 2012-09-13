/*D***********************************************************
 * Modul:     DBI - database action
 *            MESSAGE
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xMSGinput.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

/* local function prototyps */
static int MsgTextWrite(MP_MSG *, char *);

int MSGinput(int len, char *buffer)
{
	extern MP_MSG msg;
	extern STATUS_WERTE sta;
	extern int sprache;

	char *to_buffers[MAX_MENU_ITEMS];
	int  status = MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		msg.msg_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (ACTIONTYP == (unsigned char)INSERT)
		msg.msg_id=(int)_UNDEF;


	if (*to_buffers[MMSG_NR] != NULL)
		msg.msg_id = atoi(to_buffers[MMSG_NR]);
	else
		msg.msg_id = (int)_UNDEF;

	if (*to_buffers[MMSG_SPR] != NULL)
		msg.s_id = sprache;
	else
		msg.s_id = sprache;

	/* Meldungstyp setzen - default ist Typ MESSAGE */
	sta.typ = (int)_MSGTYP;
	if (getAttribut((int)_MSGTYP, to_buffers[MMSG_TYP]) != (int)MPERROR)
		msg.msg_typ = sta.sta_id;
	else
		msg.msg_typ = (int)MSGTYP_MSG; /* default */

	/* initialisiere Textsegment */
	msg.textnr = 0;
	*msg.text = NULL;

	/* insert/update a msg or delete a msg */
	if (msg.msg_id != (int)_UNDEF)
		{
		status = MPAPIdeleteEntry((int)_MSG, (char *)&msg);
		if ((ACTIONTYP == (unsigned char)INSERT ||
			 ACTIONTYP == (unsigned char)UPDATE) &&
			 status != (int)MPERROR)
			status = MsgTextWrite(&msg, to_buffers[MMSG_TXT]);

		if (status != (int)MPERROR)
			(void)WriteInfo((int)_MSG, (char *)&msg, buffer);
		else
			msg.msg_id = (int)_UNDEF;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}

static int MsgTextWrite(MP_MSG *pMSG, char *msgtxt)
{
	char *ptr, *oldptr;
	int anzahl, anzchar, i;
	int status=(int)MPOK;
	int first = (int)TRUE;

	for(oldptr=ptr=msgtxt, anzchar=(int)0;; ptr++)
		{
		if (*ptr == '\n'  || *ptr == '\t')
			{
			pMSG->textnr++;
			(void)memcpy((void *)pMSG->text, (void *)oldptr, (size_t)anzchar);
			pMSG->text[anzchar]=(char)NULL;
			status = MPAPIinsertEntry((int)_MSG, (char *)pMSG, (BEZEICHNUNG *)NULL);
			if (status == (int)MPERROR)
				break;

			oldptr = ptr+1;
			anzchar = (int)0;
			}
		else
			anzchar++;

		if (*ptr == (char)NULL)
			break;
		}

	return(status);
}
