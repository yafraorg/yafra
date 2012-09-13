/*D***********************************************************
 * Modul:     DBI - database info                           
 *            view a whole group with all members
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xAKTGinfo.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";

int AKTGinfo(char *buffer)
{
	extern MEMOBJ		sqlmem;
	extern int sprache;
	extern AKTIONEN akt;
	extern STATUS_WERTE sta;

	AKTIONSGRP *Paktg;
	char aktbez[_BEZLEN];
	char sourcebez[_BEZLEN];
	char targetbez[_BEZLEN];
	char medbez[_BEZLEN];
	char execbez[_BEZLEN];
	char query[_QUERYLEN];
	char tmp_buffer[_RECORDLEN];
	char *to_buffers[MAX_MENU_ITEMS];
	int status=(int)MPOK;
	int i, anzahl, anzchar, id, state;

	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		return((int)MPERROR);
		}

	if (MPAPIselectEntry((int)_AKTIONEN, to_buffers[MAKTG_HAKT], (char *)&akt,
		 sizeof(AKTIONEN), sizeof(akt.akt_id) ) != (int)_UNDEF )
		{
		(void)sprintf(query, _SEL_AKTG_PARENT, akt.akt_id);
		status=MPAPIdb_sqlquery((int)_AKTIONSGRP, &sqlmem.buffer, query,
		                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
		Paktg = (AKTIONSGRP *)sqlmem.buffer;
		if ( anzahl == (int)0 )
			{
			UtilMsg((int)MPE_NOAKT, MSGTYP_ERROR, NULL);
			akt.akt_id=(int)_UNDEF;
			status = MPWARNING;
			}
		else
			{
			(void)copyTextTo(tmp_buffer, to_buffers[MAKTG_HAKT], (int)_BEZLEN);
			(void)strcpy(buffer, tmp_buffer);

			anzchar=(int)strlen(buffer);
			(void)strcat(buffer, "\n");
			for ( i=0; i<anzchar; i++ )
				strcat(buffer, "=");
			(void)strcat(buffer, "\n\n");

			for(i=0; i<anzahl; i++)
				{
				id = MPAPIselectOneId((int)_AKTIONEN, Paktg[i].childakt, (char *)&akt);
				status = SelectBez((int)_AKTIONEN, sprache, akt.bez_id, aktbez);

				/* STATUS_WERTE  Ausf�hrungsflag */
				sta.typ=(int)_A_FLG;
				id = MPAPIselectOneId((int)_STATUS_WERTE, akt.a_flag, (char *)&sta);
				state = SelectBez((int)_A_FLG, sprache, sta.bez_id, execbez);

				/* STATUS_WERTE  Medium */
				sta.typ=(int)_DEVICE;
				id = MPAPIselectOneId((int)_STATUS_WERTE, akt.m_flag, (char *)&sta);
				state = SelectBez((int)_DEVICE, sprache, sta.bez_id, medbez);

				/* STATUS_WERTE  source r_sta */
				if (akt.b_flag != (int)_UNDEF)
					{
					sta.typ=(int)_R_STA;
					id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b_flag, (char *)&sta);
					status = SelectBez((int)_R_STA, sprache, sta.bez_id, sourcebez);
					}
				else
					(void)strcpy(sourcebez, "-");

				/* STATUS_WERTE  target r_sta */
				if (akt.b2_flag != (int)_UNDEF)
					{
					sta.typ=(int)_R_STA;
					id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b2_flag, (char *)&sta);
					status = SelectBez((int)_R_STA, sprache, sta.bez_id, targetbez);
					}
				else
					(void)strcpy(targetbez, "-");

				(void)sprintf(tmp_buffer, " %2.0d %-30.30s : %-30.30s -> %-30.30s :  %s, %s",
				    Paktg[i].ord, aktbez, sourcebez, targetbez, medbez, execbez);
				(void)strcat(buffer, tmp_buffer);
				(void)strcat(buffer, "\n");
				/* OK it seems that everything is fine, so give OK back */
				status = MPOK;
				}
			}
		}
	else
		{
		UtilMsg((int)MPE_NOAKT, MSGTYP_ERROR, NULL);
		akt.akt_id=(int)_UNDEF;
		status = MPWARNING;
		}

	UtilSplitFreeMenubuffer(to_buffers);
	return(status);
}
