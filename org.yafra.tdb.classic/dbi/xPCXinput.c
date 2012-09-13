/**************************************************************/
/* Modul:     DBI - database select                           */
/*            get a pixel image                               */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/xPCXinput.c,v 1.2 2008-11-02 19:55:37 mwn Exp $";
static int PCXfindIDwithBEZID(int, int);

int PCXinput(int len , char *buffer )
{
	extern MEMOBJ sqlmem;
	extern PCX_FILES pcx;
	extern BEZEICHNUNG bez;
	extern int sprache;

	BEZEICHNUNG *Pbez;
	BEZEICHNUNG localbez;
	char *to_buffers[MAX_MENU_ITEMS];
	char query[_RECORDLEN];
	int status=MPOK;
	int anzahl;

	/* init at insert mode */
	if (ACTIONTYP == (unsigned char)INSERT)
		{
		pcx.pcx_id = (int)_UNDEF;
		pcx.x = (int)0;
		pcx.y = (int)0;
		pcx.folge = (int)0;
		}

	/* get menu fields */
	status = UtilSplitMenubuffer(buffer, to_buffers, (char)NULL);
	if (status != MPOK)
		{
		UtilMsg((int)MPE_CUTBUFFERIN, MSGTYP_ERROR, NULL);
		pcx.pcx_id = (int)_UNDEF;
		return((int)MPERROR);
		}

	/* check up BEZEICHNUNG */
	if (*to_buffers[MPCX_BEZ] == NULL)
		{
		UtilMsg((int)MPE_NOPCX, MSGTYP_ERROR, NULL);
		UtilSplitFreeMenubuffer(to_buffers);
		return((int)MPERROR);
		}

	/* manage */
	switch(ACTIONTYP)
		{
		case (unsigned char)INSERT:
		case (unsigned char)UPDATE:
			/* it's not allowed to entries with the same bez */
			if (ACTIONTYP == (unsigned char)INSERT)
				{
				if (MPAPIselectEntry(_PCX_FILES, to_buffers[MPCX_BEZ], (char *)&pcx,
				    sizeof(pcx), sizeof(pcx.pcx_id)) != (int)_UNDEF)
					{
					UtilMsg((int)MPE_PCXINPUT, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					break;
					}
				}
			/* file name must be present */
			if (*to_buffers[MPCX_FILE] == NULL)
				{
				UtilMsg((int)MPE_PCXINPUT, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				break;
				}

			bez.s_id=(int)sprache;
			bez.typ=(int)_PCX_FILES;
			(void)copyTextTo(bez.bez, to_buffers[MPCX_BEZ], (int)_BEZLEN);
			(void)copyTextTo(pcx.filename, to_buffers[MPCX_FILE], (int)_FILELEN);

			/* typ, objekt, folge */
			localbez.s_id=(int)sprache;
			localbez.typ=(int)_UNDEF;
			(void)strcpy(localbez.bez, to_buffers[MPCX_TYP]);
			if (MPAPIselectEntry((int)_BEZEICHNUNG, to_buffers[MPCX_TYP], (char *)&localbez,
			    sizeof(BEZEICHNUNG), sizeof(localbez.bez_id)) != (int)_UNDEF)
				{
				pcx.typ = localbez.typ;
				(void)sprintf(query, _SEL_BEZ_FROMTYP, to_buffers[MPCX_TYPCODE],
				         sprache, pcx.typ);
				status=MPAPIdb_sqlquery((int)_BEZEICHNUNG, &sqlmem.buffer, query,
				                   &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
				if (status == (int)MPOK && anzahl > 0)
					{
					Pbez = (BEZEICHNUNG *)sqlmem.buffer;
					pcx.typcode = Pbez[0].bez_id;
					if (pcx.typcode != (int)_UNDEF)
						{
						/* image nr and koordinates */
						if (*to_buffers[MPCX_NR] != NULL)
							readInteger(&pcx.folge, to_buffers[MPCX_NR]);
						if (*to_buffers[MPCX_X] != NULL)
							readInteger(&pcx.x, to_buffers[MPCX_X]);
						if (*to_buffers[MPCX_Y] != NULL)
		   				readInteger(&pcx.y, to_buffers[MPCX_Y]);
						}
					else
						{
						UtilMsg((int)MPE_PCXINPUT, MSGTYP_ERROR, NULL);
						status = (int)MPERROR;
						}
					}
				else
					{
					UtilMsg((int)MPE_PCXINPUT, MSGTYP_ERROR, NULL);
					status = (int)MPERROR;
					}
				}
			else
				{
				UtilMsg((int)MPE_PCXINPUT, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			break;
		case (unsigned char)MPDELETE:
			if (MPAPIselectEntry(_PCX_FILES, to_buffers[MPCX_BEZ], (char *)&pcx,
			    sizeof(pcx), sizeof(pcx.pcx_id)) == (int)_UNDEF)
				{
				UtilMsg((int)MPE_NOENTRYFOUND, MSGTYP_ERROR, NULL);
				status = (int)MPERROR;
				}
			break;
		}

	if (status == (int)MPOK)
		{
		/* write entry or delete entry */
		status=WriteEntry((int)_PCX_FILES, (char *)&pcx, &bez);
		if (status != (int)MPOK)
			pcx.pcx_id=(int)_UNDEF;
		else
			(void)WriteInfo((int)_PCX_FILES, (char *)&pcx, buffer);
		}

	UtilSplitFreeMenubuffer(to_buffers);

	return(status);
}

static int PCXfindIDwithBEZID(int bezid, int typ)
{
	extern MEMOBJ sqlmem;

	int status = (int)MPOK;
	int anzahl;
	char query[_RECORDLEN];
	DIENST_TRAEGER *Pdlt;
	TRAEGER_TYP    *Pdltt;
	KATEGORIE      *Pkat;
	DIENST_ANGEBOT *Pdla;
	DIENSTLEISTUNG *Pdl;

	switch(typ)
		{
		case (int)_DIENST_TRAEGER:
			sprintf(query, "SELECT * FROM TDBADMIN.DIENST_TRAEGER WHERE BEZ_ID = %d;",
			        bezid);
			break;
		case (int)_TRAEGER_TYP:
			sprintf(query, "SELECT * FROM TDBADMIN.TRAEGER_TYP WHERE BEZ_ID = %d;",
			        bezid);
			break;
		case (int)_KATEGORIE:
			sprintf(query, "SELECT * FROM TDBADMIN.KATEGORIE WHERE BEZ_ID = %d;",
			        bezid);
			break;
		case (int)_DIENST_ANGEBOT:
			sprintf(query, "SELECT * FROM TDBADMIN.DIENST_ANGEBOT WHERE BEZ_ID = %d;",
			        bezid);
			break;
		case (int)_DIENSTLEISTUNG:
			sprintf(query, "SELECT * FROM TDBADMIN.DIENSTLEISTUNG WHERE BEZ_ID = %d;",
			        bezid);
			break;
		default:
			return((int)_UNDEF);
			break;
		}

	status=MPAPIdb_sqlquery((int)typ, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if (status != (int)MPOK && anzahl < 1)
		return((int)_UNDEF);

	switch(typ)
		{
		case (int)_DIENST_TRAEGER:
			Pdlt = (DIENST_TRAEGER *)sqlmem.buffer;
			return(Pdlt[0].dlt_id);
			break;
		case (int)_TRAEGER_TYP:
			Pdltt = (TRAEGER_TYP *)sqlmem.buffer;
			return((int)Pdltt[0].typ_id);
			break;
		case (int)_KATEGORIE:
			Pkat = (KATEGORIE *)sqlmem.buffer;
			return((int)Pkat[0].kat_id);
			break;
		case (int)_DIENST_ANGEBOT:
			Pdla = (DIENST_ANGEBOT *)sqlmem.buffer;
			return(Pdla[0].dla_id);
			break;
		case (int)_DIENSTLEISTUNG:
			Pdl = (DIENSTLEISTUNG *)sqlmem.buffer;
			return(Pdl[0].dlg_id);
			break;
		default:
			return((int)_UNDEF);
			break;
		}

	return((int)_UNDEF);
}
