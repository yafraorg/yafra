/*D***********************************************************
 * Modul:     DBI - database select                           
 *            OUTPUT Menu
 *            create a dynamic OUTPUT-menu dependend on
 *            the parameters of a AKTION
 *            this choose is different to the others. If an AKTION is
 *            choosed, it sends data for a new menu - a dynamic menu !
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xOUTselect.c,v 1.2 2008-11-02 19:55:35 mwn Exp $";

/*F***********************************************************
 * Function:  Choose                                         
 *************************************************************/
int OUTchoose(int table, char *buffer)
{
	extern MEMOBJ      sqlmem;
	extern int         sprache;
	extern int         *NewLevel[];
	extern int         *NEWOUTlevel;
	extern int         OUTlevel[];
	extern AKTIONEN    akt;
	extern AKTIONSGRP  aktgrp;
	extern AKTIONS_TYP aktt;
	extern STATUS_WERTE	sta;
	extern char glob_dlg_out[];
	extern char glob_akt_out[];

	static AKTIONSPARA apara;

	AKTIONSPARA        *paraptr;
	DLG_PART	dlg;
	char	buffer1[RECLAENGE];
	char	buffer2[RECLAENGE];
	char	message[RECLAENGE];
	char  query[RECLAENGE];
	char  bez[(2*_BEZLEN)+5];
	char  mstabez[_BEZLEN];
	char  sstabez[_BEZLEN];
	char  tstabez[_BEZLEN];
	int   status;
	int   id;
	int   anzahl;
	int   i;
	int   j;
	char  *bufferptr;

	(void)memset((void *)buffer1, NULL, sizeof(buffer1));
	(void)memset((void *)buffer2, NULL, sizeof(buffer2));
	COMMTYP = CHOOSE;

	switch(FELDNR)
		{
		case MOUT_AKTT:
			akt.a_typ_id = 0;
			(void)strcpy(bez, buffer);
			id = MPAPIselectEntry((int)_AKTIONEN, bez, (char *)&akt,
			         sizeof(akt), sizeof(akt.akt_id));
			if (id == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			/* copy the name of aktion into the global area for selects coming soon */
			strcpy(glob_akt_out, bez);

			id = MPAPIselectOneId((int)_AKTIONS_TYP, akt.a_typ_id, (char *)&aktt);
			if (id == (int)_UNDEF)
				return(MPERROR);

			/* STATUS_WERTE  Medium */
			sta.typ=(int)_DEVICE;
			id = MPAPIselectOneId((int)_STATUS_WERTE, akt.m_flag, (char *)&sta);
			id = SelectBez((int)_DEVICE, sprache, sta.bez_id, mstabez);
			if (id == (int)_UNDEF || id == (int)_UNDEF)
				*mstabez = NULL;

			/* STATUS_WERTE  Ausf�hrung bei welchem Reservations-Sta */
			sta.typ=(int)_R_STA;
			id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b_flag, (char *)&sta);
			if(id == (int)_UNDEF || SelectBez((int)_R_STA, sprache, sta.bez_id,
											sstabez) == (int)_UNDEF)
				*sstabez = NULL;

			/* STATUS_WERTE  nach Ausf�hrung welchen Reservations-Sta setzen */
			sta.typ=(int)_R_STA;
			id = MPAPIselectOneId((int)_STATUS_WERTE, akt.b2_flag, (char *)&sta);
			if(id == (int)_UNDEF || SelectBez((int)_R_STA, sprache, sta.bez_id,
											tstabez) == (int)_UNDEF)
				*tstabez = NULL;

			/* hole Parameter zum Aktionstyp */
			apara.a_typ_id = aktt.a_typ_id;
			(void)sprintf(query, _SEL_PARA_AKTT, apara.a_typ_id);
			status=MPAPIdb_sqlquery(_AKTIONSPARA, &sqlmem.buffer, query,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
			if (status != MPOK)
				return(MPERROR);
			sprintf(comm.buffer, "1\n%d\n%s\t%s\t%s\t%s\t2\n%d", DEFAULTFIELDS,
			     bez, mstabez, sstabez, tstabez, anzahl);
			if (anzahl == 0)
				return(MPOK);

			/* NewLevel neu setzen */
			i = anzahl + DEFAULTFIELDS;

			/*!!! sorry but this is leaking */
			NEWOUTlevel = (int *)realloc(NEWOUTlevel, (size_t)(i*(sizeof(int))));
			for (j=0; j<DEFAULTFIELDS; j++)
				NEWOUTlevel[j] = OUTlevel[j];

			bufferptr = &buffer[(strlen(buffer))];
			paraptr = (AKTIONSPARA *)sqlmem.buffer;
			for (i=0; i<anzahl; i++, j++)
				{
				strcpy(bufferptr, "\n");
				bufferptr++;
				(void)sprintf(bufferptr, "%d\t", paraptr[i].nr);
				bufferptr += strlen(bufferptr);
				if (paraptr[i].typ == _UNDEF)
					{
					(void)copyTextTo(buffer1, paraptr[i].bez, _PARALEN);
					(void)sprintf(bufferptr, "%s\t%d\t%d", buffer1,
					                      (int)SEDITFIELD, paraptr[i].muss);
					NEWOUTlevel[j] = _UNDEF;
					}
				else
					{
					status = SelectBez(paraptr[i].typ, sprache, (int)_TYPENBEZID, bez);
					if (status == UNDEF)
						(void)copyTextTo(bez, paraptr[i].bez, _PARALEN);
					(void)sprintf(bufferptr, "%s\t%d\t%d", bez,
					                      (int)SELECTFIELD, paraptr[i].muss);
					NEWOUTlevel[j] = paraptr[i].typ;
					}
				bufferptr += strlen(bufferptr);
				
				}
			strcpy(bufferptr, "\n");
			bufferptr++;
			*bufferptr = NULL;			
			NewLevel[_OUTPUT] = NEWOUTlevel;
			return(MPOK);
			break;
			
		default:
			break;
		}

	return(MPOK);
}
