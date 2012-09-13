/*D***********************************************************
 * Modul:     DBI - database select
 *            get a DIENST_TRAEGER from DL, DLG_PARTS or DLA
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes f�r ANSI-C */
#include <mpsqlsel.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/SelectDLT.c,v 1.3 2008-11-23 15:44:38 mwn Exp $";

/* local protos */
static int getDLTfromDLA(int, DIENST_TRAEGER *);
static int getDLTfromTDL(int, DIENST_TRAEGER *);
static int getDLTfromDL(int, DIENST_TRAEGER *);

int MPAPIselectDLT(int dla_id, int tdl_id, int dl_id, DIENST_TRAEGER *Pdlt)
{
	int status=(int)MPOK;

	if (dla_id != (int)_UNDEF)
		status = getDLTfromDLA(dla_id, Pdlt);
	else if (tdl_id != (int)_UNDEF)
		status = getDLTfromTDL(tdl_id, Pdlt);
	else if (dl_id != (int)_UNDEF)
		status = getDLTfromDL(dl_id, Pdlt);
	else
		return((int)MPERROR);

	return(status);
}


static int getDLTfromDL(int dl_id, DIENST_TRAEGER *Pdlt)
{
	extern MEMOBJ apimem;
	extern char sqlquery[];
	DLG_DLG *Pdl_dl;
	int id;
	int anzahl;
	int status = (int)MPOK;

	(void)sprintf(sqlquery, _SEL_DLDLG, dl_id);
	status = MPAPIdb_sqlquery((int)_DLG_DLG, &apimem.buffer, sqlquery,
	       &anzahl, &apimem.datalen, &apimem.alloclen);
	if (status == (int)MPOK && anzahl > 0)
		{
		// TODO check here if host TDL is changing and if it's changing
		//      look if the DLT on the DLA is also changing (that would be hard)
		Pdl_dl = (DLG_DLG *)apimem.buffer;
		status = getDLTfromTDL(Pdl_dl[0].dl_id, Pdlt);
		}
	else
		status = (int)MPERROR;

	return(status);
}

static int getDLTfromTDL(int tdl_id, DIENST_TRAEGER *Pdlt)
{
	extern DLG_PART dlg;
	int id;
	int status = (int)MPOK;

	id = MPAPIselectOneId((int)_DLG_PART, tdl_id, (char *)&dlg);
	if (id == (int)_UNDEF)
		return((int)MPERROR);
	if (dlg.h_dl_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId((int)_DLG_PART, dlg.h_dl_id, (char *)&dlg);
		if (id == (int)_UNDEF)
			return((int)MPERROR);
		}
	status = getDLTfromDLA(dlg.dla_id, Pdlt);

	return(status);
}

static int getDLTfromDLA(int dla_id, DIENST_TRAEGER *Pdlt)
{
	extern DIENST_ANGEBOT dla;
	int id;

	/* init */
	Pdlt->dlt_id = (int)_UNDEF;

	id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dla_id, (char *)&dla);
	if (id == (int)_UNDEF)
		return((int)MPERROR);
	if (dla.h_dla_id != (int)_UNDEF)
		{
		id = MPAPIselectOneId((int)_DIENST_ANGEBOT, dla.h_dla_id, (char *)&dla);
		if (id == (int)_UNDEF)
			return((int)MPERROR);
		}
	id = MPAPIselectOneId((int)_DIENST_TRAEGER, dla.dlt_id, (char *)Pdlt);
	if (id == (int)_UNDEF)
		return((int)MPERROR);

	return((int)MPOK);
}
