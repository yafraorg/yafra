/*D***********************************************************
 * Modul:     DBI - database action
 *            Aktionstyp
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTTinput.c,v 1.4 2009-01-02 21:30:21 mwn Exp $";

int AKTTinput(int len, char *buffer)
{
	extern BEZEICHNUNG bez;
	extern AKTIONS_TYP aktt;
	extern AKTIONSPARA para;
	extern TEXTE txt;
	extern int sprache;

	AKTIONS_TYP orgaktt;
	char	tmp_buffer[_CHARMAXLEN];
	char	message[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		aktt.a_typ_id=(int)_UNDEF;
		para.a_typ_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	switch (ACTIONTYP)
		{
		case MPDELETE:
			if (*to_buffers[MAKTT_BEZ] == NULL)
				{
				UtilMsg((int)MPE_NOAKTT, MSGTYP_ERROR, NULL);
				aktt.a_typ_id = (int)_UNDEF;
				status = (int)MPERROR;
				}
			else
				{
				if (MPAPIselectEntry((int)_AKTIONS_TYP, to_buffers[MAKTT_BEZ], (char *)&aktt,
					     sizeof(aktt), sizeof(aktt.a_typ_id)) == (int)_UNDEF)
					{
					UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				if (*to_buffers[MAKTT_PARANR] == NULL)
					{
					para.a_typ_id=(int)_UNDEF;
					para.nr = (int)_UNDEF;
					status = WriteEntry((int)_AKTIONS_TYP, (char *)&aktt, &bez);
					}
				else
					{
					para.a_typ_id=aktt.a_typ_id;
					(void)readInteger(&para.nr, to_buffers[MAKTT_PARANR]);
					status = WriteEntry((int)_AKTIONSPARA, (char *)&para, (BEZEICHNUNG *)NULL);
					}
				}
			break;

		case INSERT:
		case UPDATE:
			if (ACTIONTYP == (unsigned char)INSERT)
				{
				aktt.a_typ_id=(int)_UNDEF;
				aktt.textid=(int)_UNDEF;
				txt.textid=(int)_UNDEF;
				para.nr = _UNDEF;
				para.a_typ_id = (int)_UNDEF;
				}

			if (*to_buffers[MAKTT_BEZ] != NULL)
				{
				bez.s_id=(int)sprache;
				bez.typ=(int)_AKTIONS_TYP;
				(void)copyTextTo(bez.bez, to_buffers[MAKTT_BEZ], (int)_BEZLEN);
				orgaktt.a_typ_id = MPAPIselectEntry((int)_AKTIONS_TYP, bez.bez,
			    (char *)&orgaktt, sizeof(AKTIONS_TYP), sizeof(orgaktt.a_typ_id));
				if ((ACTIONTYP == (unsigned char)INSERT &&
				    orgaktt.a_typ_id == (int)_UNDEF) ||
					 ACTIONTYP == (unsigned char)UPDATE)
					{
					if (*to_buffers[MAKTT_PROZ] != NULL)
						{
						(void)copyTextTo(aktt.proz, to_buffers[MAKTT_PROZ], (int)_PROZLEN);

						txt.typ=(int)_AKTIONS_TYP;
						txt.s_id=sprache;
						txt.textid=aktt.textid;
						aktt.textid=xTxtWrite(to_buffers[MAKTT_TXT]);

						status=WriteEntry((int)_AKTIONS_TYP, (char *)&aktt, &bez);
						if (status == (int)MPERROR)
							aktt.a_typ_id=(int)_UNDEF;
						else
							(void)WriteInfo((int)_AKTIONS_TYP, (char *)&aktt, buffer);
						}
					else
						{
						UtilMsg((int)MPE_NOAKTTPROZ, MSGTYP_ERROR, NULL);
						aktt.a_typ_id=(int)_UNDEF;
						status=(int)MPERROR;
						}
					}
				}
			else
				{
				UtilMsg((int)MPE_NOBEZ, MSGTYP_ERROR, NULL);
				aktt.a_typ_id=(int)_UNDEF;
				status=(int)MPERROR;
				}

			/* Manage the AKTIONSPARA */
			if (status == (int)MPOK && (MPAPIselectEntry((int)_AKTIONS_TYP,
				 to_buffers[MAKTT_BEZ], (char *)&aktt,
			    sizeof(aktt), sizeof(aktt.a_typ_id))) != UNDEF)
				{

				if (*to_buffers[MAKTT_PARA] == NULL &&
					 *to_buffers[MAKTT_PARANR] == NULL)
					break;

				para.a_typ_id = aktt.a_typ_id;
				if (*to_buffers[MAKTT_PARANR] != NULL)
					status = readInteger(&para.nr, to_buffers[MAKTT_PARANR]);
				else
					{
					para.nr = MPAPIid_max((int)_AKTIONS_TYP, (int)_ORD, (char *)&para);
					para.nr = para.nr + 1;
					if (para.nr < 1)
						para.nr = 1;
					}

				if (*to_buffers[MAKTT_PARATYP] != NULL)
					{
					bez.s_id=sprache;
					bez.typ=(int)_UNDEF;
					(void)strcpy(bez.bez, to_buffers[MAKTT_PARATYP]);
					if (MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MAKTT_PARATYP],
						 (char *)&bez, sizeof(BEZEICHNUNG), sizeof(bez.bez_id)) != (int)_UNDEF)
						para.typ = bez.typ;
					else
						para.typ = _UNDEF;
					}
				else
					para.typ = _UNDEF;
				if (*to_buffers[MAKTT_PARA] != NULL)
					(void)memcpy((void *)para.bez, (void *)to_buffers[MAKTT_PARA], (size_t)_PARALEN);
				else
					{
					/* I need a parameter BEZ */
					UtilMsg((int)MPE_NOPARABEZ, MSGTYP_ERROR, NULL);
					aktt.a_typ_id=(int)_UNDEF;
					para.a_typ_id=(int)_UNDEF;
					UtilSplitFreeMenubuffer(to_buffers);
					return((int)MPERROR);
					}

				if (*to_buffers[MAKTT_PARAMUSS] != NULL)
					{
					(void)copyTextTo(tmp_buffer, to_buffers[MAKTT_PARAMUSS], (int)_FLAGLEN);
					UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
					if (strstr(message, tmp_buffer) != NULL)
						para.muss = (int)TRUE;
					else
						para.muss = (int)FALSE;
					}
				else
					para.muss = (int)FALSE;

				if (*to_buffers[MAKTT_PARAFLAG] != NULL)
					{
					(void)copyTextTo(tmp_buffer, to_buffers[MAKTT_PARAFLAG], (int)_FLAGLEN);
					UtilMsgGet((int)MPI_YES_TRUE, MSGTYP_INFO, message);
					if (strstr(message, tmp_buffer) != NULL)
						para.flag = (int)TRUE;
					else
						para.flag = (int)FALSE;
					}
				else
					para.flag = (int)FALSE;


				if (para.flag == (int)TRUE && para.typ > (int)_UNDEF)
					{
					/* this is not possible */
					UtilMsg((int)MPE_PARAMISMATCH, MSGTYP_ERROR, NULL);
					aktt.a_typ_id=(int)_UNDEF;
					para.a_typ_id=(int)_UNDEF;
					UtilSplitFreeMenubuffer(to_buffers);
					return((int)MPERROR);
					}
				txt.typ=(int)_AKTIONSPARA;
				txt.s_id=sprache;
				txt.textid=para.textid;
				para.textid=xTxtWrite(to_buffers[MAKTT_PARATXT]);

				status=WriteEntry((int)_AKTIONSPARA, (char *)&para, NULL);
				if (status == (int)MPERROR)
					{
					para.a_typ_id=(int)_UNDEF;
					para.nr = (int)_UNDEF;
					}
				}
			break;
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}
