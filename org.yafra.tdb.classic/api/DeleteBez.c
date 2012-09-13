/*D***********************************************************
 * Modul:     DBI - database delete
 *            Dienstleistungstr�ger
 *
 * Copyright: yafra.org, Aesch, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes fvr ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/DeleteBez.c,v 1.2 2008-11-02 19:55:47 mwn Exp $";

/*************************************************************
 * Function:  DeleteBEZ
 * Typ:       public
 * Desc:      delete a BEZ object language independent
 *************************************************************/
int DeleteBEZ(int objecttyp, char *object, int newbezid)
{
	extern BEZEICHNUNG bez;
	int status = MPOK;
	int count = 0;
	int oldbezid;

	AKTIONEN *akt;
	AKTIONS_TYP *aktt;
	ARRANGEMENT *arr;
	DIENST_ANGEBOT *dla;
	ANGEBOTS_TYP *dlat;
	DIENSTLEISTUNG *dtg;
	DLG_PART *dlg;
	DIENST_TRAEGER *dlt;
	TRAEGER_TYP *dltt;
	GRAPHIK *gra;
	KATEGORIE *kat;
	KOLLEKTIV *kol;
	KOLLEKTIV_TYP *kolt;
	HOST_KONT *hkon;
	KONTINGENT *kon;
	KOMMISSION *kom;
	KUNDEN_TYP *kunt;
	PCX_FILES *pcx;
	PROGRAMM *prg;
	REISENDER_TYP *reit;
	KOSTEN_ART *kar;
	SAISON *sai;
	SPRACHEN *spr;
	STATUS_WERTE *sta;
	BEZEICHNUNG *bez_ptr;
	LAND *land;
	ORT *ort;
	WAEHRUNG *whr;

	switch(objecttyp)
		{
		case _AKTIONEN:
			akt=(AKTIONEN *)object;
			oldbezid = akt->bez_id;
			break;
		case _AKTIONS_TYP:
			aktt=(AKTIONS_TYP *)object;
			oldbezid = aktt->bez_id;
			break;
		case _ARRANGEMENT:
			arr=(ARRANGEMENT *)object;
			oldbezid = arr->bez_id;
			break;
		case _DIENST_ANGEBOT:
			dla=(DIENST_ANGEBOT *)object;
			oldbezid = dla->bez_id;
			break;
		case _ANGEBOTS_TYP:
			dlat=(ANGEBOTS_TYP *)object;
			oldbezid = dlat->bez_id;
			break;
		case _DIENSTLEISTUNG:
			dtg=(DIENSTLEISTUNG *)object;
			oldbezid = dtg->bez_id;
			break;
		case _DLG_PART:
			dlg=(DLG_PART *)object;
			oldbezid = dlg->bez_id;
			break;
		case _DIENST_TRAEGER:
			dlt=(DIENST_TRAEGER *)object;
			oldbezid = dlt->bez_id;
			break;
		case _TRAEGER_TYP:
			dltt=(TRAEGER_TYP *)object;
			oldbezid = dltt->bez_id;
			break;
		case _GRAPHIK:
			gra=(GRAPHIK *)object;
			oldbezid = gra->bez_id;
			break;
		case _KATEGORIE:
			kat=(KATEGORIE *)object;
			oldbezid = kat->bez_id;
			break;
		case _KOLLEKTIV_TYP:
			kolt=(KOLLEKTIV_TYP *)object;
			oldbezid = kolt->bez_id;
			break;
		case _HOST_KONT:
			hkon=(HOST_KONT *)object;
			oldbezid = hkon->bez_id;
			break;
		case _KONTINGENT:
			kon=(KONTINGENT *)object;
			oldbezid = kon->bez_id;
			break;
		case _KUNDEN_TYP:
			kunt=(KUNDEN_TYP *)object;
			oldbezid = kunt->bez_id;
			break;
		case _PCX_FILES:
			pcx=(PCX_FILES *)object;
			oldbezid = pcx->bez_id;
			break;
		case _PROGRAMM:
			prg=(PROGRAMM *)object;
			oldbezid = prg->bez_id;
			break;
		case	_REISENDER_TYP	:
			reit=(REISENDER_TYP *)object;
			oldbezid = reit->bez_id;
			break;
		case	_KOSTEN_ART	:
			kar=(KOSTEN_ART *)object;
			oldbezid = kar->bez_id;
			break;
		case	_SAISON	:
			sai=(SAISON *)object;
			oldbezid = sai->bez_id;
			break;
		case	_STATUS_WERTE	:
			sta=(STATUS_WERTE *)object;
			oldbezid = sta->bez_id;
			break;
		case	_KOMMISSION	:
			kom=(KOMMISSION *)object;
			oldbezid = kom->bez_id;
			break;

		case	_SPRACHEN	:
			spr=(SPRACHEN *)object;
			oldbezid = spr->bez_id;
			break;
		case _LAND:
			land=(LAND *)object;
			oldbezid = land->bez_id;
			break;
		case _ORT:
			ort=(ORT *)object;
			oldbezid = ort->bez_id;
			break;
		case _WAEHRUNG:
			whr=(WAEHRUNG *)object;
			oldbezid = whr->bez_id;
			break;
			
		case _BEZEICHNUNG:
			bez_ptr=(BEZEICHNUNG *)object;
			oldbezid = bez_ptr->bez_id;
			break;
		}

	if (newbezid < 1 || oldbezid < 1)
		return((int)MPE_BEZDELWRONG);

	if (newbezid == oldbezid)
		return((int)MPOK);

	/* delete BEZ */
	/* bez.typ should be set correct */
	bez.bez_id = oldbezid;
	count = MPAPIid_count((int)_BEZEICHNUNG, objecttyp, (char *)&bez);
	if (count < (int)2)
		{
		bez.typ = (int)objecttyp;
		if (MPAPIdeleteEntry((int)_BEZEICHNUNG, (char *)&bez) == (int)MPERROR)
			status=(int)MPE_NOBEZDEL;
		}

	return(status);
}
