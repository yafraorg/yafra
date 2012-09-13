/*D************************************************************/
/* Modul:     DBI - database select                           */
/*            manage a select request on a field              */
/*            init message is: STATUS\nROWS\nFIELDS\nrecs...  */
/*                                                            */
/* Copyright: yafra.org, Basel, Switzerland     */
/**************************************************************/
#include <mpnet.h>
#include <mpmsg.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/dbtoascii.c,v 1.3 2008-11-02 19:55:51 mwn Exp $";

static void cutspaces(char *);

int MPNETdbToAscii(int MPtableid, char *inputbuffer, int count, PSmemobj *outmem)
{
	extern int sprache;

	BUCHUNG *Pbch;
	BUCHUNG bch;
	KUNDEN *Pkun;
	KUNDEN kun;
	REISENDER *Prei;
	REISENDER rei;
	PERSADR *Ppadr;
	PERSADR padr;
	MPV_KUNADR *Pkunadr;
	MPV_KUNADR kunadr;
	KOLLEKTIV *Pkol;
	KOLLEKTIV kol;
	KOMMISSION *Pkom;
	KOMMISSION kom;
	KOMM_DETAIL *Pkomdet;
	KOMM_DETAIL komdet;
	SAISON *Psai;
	SAISON sai;
	SAI_VIEW *Psaiv;
	SAI_VIEW saiv;
	PROGRAMM *Pprg;
	PROGRAMM prg;
	ARRANGEMENT *Parr;
	ARRANGEMENT arr;
	ARR_VIEW *Parrv;
	ARR_VIEW arrv;
	ARRDL_VIEW *Padlv;
	ARRDL_VIEW adlv;
	DIENSTLEISTUNG *Pdlg;
	DIENSTLEISTUNG dlg;
	DTG_VIEW *Pdlv;
	DTG_VIEW dlv;
	DLG_PART *Pdlgp;
	DLG_PART dlgp;
	DIENST_ANGEBOT *Pdla;
	DIENST_ANGEBOT dla;
	ANGEBOTS_TYP *Patyp;
	ANGEBOTS_TYP atyp;
	AKTIONEN *Pakt;
	AKTIONEN akt;
	AKTIONSGRP *Paktg;
	AKTIONSGRP aktg;
	HOST_KONT *Phkont;
	HOST_KONT hkont;
	KONTINGENT *Pkont;
	KONTINGENT kont;
	KONT_DETAIL *Pkontd;
	KONT_DETAIL kontd;
	PREIS *Ppre;
	PREIS pre;
	TRAEGER_TYP *Pttyp;
	TRAEGER_TYP ttyp;
	DIENST_TRAEGER *Pdlt;
	DIENST_TRAEGER dlt;
	KATEGORIE *Pkat;
	KATEGORIE kat;
	KAT_VIEW *Pkatv;
	KAT_VIEW katv;
	PCX_FILES *Ppcx;
	PCX_FILES pcx;
	GRAPHIK *Pgra;
	GRAPHIK gra;
	AKTIONS_TYP *Pakttyp;
	AKTIONS_TYP akttyp;
	KOSTEN_ART *Pkar;
	KOSTEN_ART kar;
	KUNDEN_TYP *Pkutyp;
	KUNDEN_TYP kutyp;
	REISENDER_TYP *Prtyp;
	REISENDER_TYP rtyp;
	KOLLEKTIV_TYP *Pkotyp;
	KOLLEKTIV_TYP kotyp;
	STATUS_WERTE *Psta;
	STATUS_WERTE sta;
	SPRACHEN *Pspr;
	SPRACHEN spr;
	WAEHRUNG *Pwhr;
	WAEHRUNG whr;
	LAND *Pland;
	LAND land;
	ORT *Port;
	ORT ort;
	LAND_WHR *Plwhr;
	LAND_WHR lwhr;
	MP_PROFIL *Pmpp;
	MP_PROFIL mpp;
	BEZEICHNUNG *Pbez;
	BEZEICHNUNG bez;
	MP_MSG *Pmesg;
	MP_MSG mesg;

	int i;
	int len;
	int id;
	struct tm DateTime;
	char record[20000];
	char *outputbuffer;
	char tmpbuf1[_RECORDLEN];
	char tmpbuf2[_RECORDLEN];
	char tmpbuf3[_RECORDLEN];

	switch(MPtableid)
		{
		/* BUCHUNG */
		case (int)_BUCHUNG: /* Tabelle 41 */
			len = sizeof(bch);
			outmem->datalen = (len * count);
			outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pbch = (BUCHUNG *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pbch[i].ref);
				cutspaces(Pbch[i].sach);
				sprintf(record, "%d\t%s\t%d\t%s\t\r",
					Pbch[i].bid, Pbch[i].ref, Pbch[i].arr_id, Pbch[i].sach);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_MPV_KUNADR: /* Tabelle 287 */
			len = sizeof(kunadr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkunadr = (MPV_KUNADR *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkunadr[i].ans);
				cutspaces(Pkunadr[i].name);
				cutspaces(Pkunadr[i].adr1);
				cutspaces(Pkunadr[i].adr2);
				cutspaces(Pkunadr[i].adr3);
				cutspaces(Pkunadr[i].plz);
				cutspaces(Pkunadr[i].ort);
				cutspaces(Pkunadr[i].kant);
				cutspaces(Pkunadr[i].tel);
				cutspaces(Pkunadr[i].fax);
				sprintf(record, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d\t%s\t%s\t\r",
					Pkunadr[i].pers_id, Pkunadr[i].ans, Pkunadr[i].name, Pkunadr[i].adr1,
					Pkunadr[i].adr2, Pkunadr[i].adr3, Pkunadr[i].plz, Pkunadr[i].ort,
					Pkunadr[i].kant, Pkunadr[i].land_id, Pkunadr[i].sta_id,
					Pkunadr[i].k_typ_id, Pkunadr[i].tel, Pkunadr[i].fax);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
		case (int)_KUNDEN: /* Tabelle 25 */
			len = sizeof(kun);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkun = (KUNDEN *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkun[i].tel);
				cutspaces(Pkun[i].fax);
				cutspaces(Pkun[i].tlx);
				cutspaces(Pkun[i].konto);
				cutspaces(Pkun[i].leiter);
				cutspaces(Pkun[i].attr1);
				cutspaces(Pkun[i].attr2);
				sprintf(record, "%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t\r",
					Pkun[i].pers_id, Pkun[i].tel, Pkun[i].fax,
					Pkun[i].tlx, Pkun[i].konto, Pkun[i].leiter, Pkun[i].attr1,
					Pkun[i].attr2, Pkun[i].k_typ_id, Pkun[i].whr_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_REISENDER: /* Tabelle 36 */
			len = sizeof(rei);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkun = (REISENDER *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Prei[i].vor);
				cutspaces(Prei[i].age);
				cutspaces(Prei[i].passnr);
				cutspaces(Prei[i].attr1);
				cutspaces(Prei[i].attr2);
				sprintf(record, "%d\t%s\t%d\t%d\t%d\t%s\t%s\t%s\t%s\t\r",
					Prei[i].pers_id, Prei[i].vor, Prei[i].rkr_id, Prei[i].sex,
					Prei[i].mutters_id, Prei[i].age, Prei[i].passnr,
					Prei[i].attr1, Prei[i].attr2);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_PERSADR: /* Tabelle 37 */
			len = sizeof(padr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkun = (PERSADR *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Ppadr[i].ans);
				cutspaces(Ppadr[i].adr1);
				cutspaces(Ppadr[i].adr2);
				cutspaces(Ppadr[i].adr3);
				cutspaces(Ppadr[i].plz);
				sprintf(record, "%d\t%s\t%s\t%s\t%s\t\r",
					Ppadr[i].pers_id, Ppadr[i].ans, Ppadr[i].adr1, Ppadr[i].adr2,
					Ppadr[i].adr3, Ppadr[i].plz, Ppadr[i].sta_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KOLLEKTIV: /* Tabelle 33 */
			len = sizeof(kol);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkun = (KOLLEKTIV *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkol[i].ref);
				sprintf(record, "%d\t%s\t%d\t%d\t%s\t%d\t%d\t%d\t%d\t\r",
					Pkol[i].k_id, Pkol[i].name, Pkol[i].k_typ_id, Pkol[i].kbst,
					Pkol[i].ref, Pkol[i].k_sta, Pkol[i].hauptpers, Pkol[i].kid,
					Pkol[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KOMMISSION: /* Tabelle 44 */
			len = sizeof(kom);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkom = (KOMMISSION *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					Pkom[i].komm_id, Pkom[i].bez_id, Pkom[i].satz_art, Pkom[i].satz,
					Pkom[i].komm_typ, Pkom[i].kbst, Pkom[i].kar_id, Pkom[i].dltt_id,
					Pkom[i].kat_id, Pkom[i].rkr_id, Pkom[i].dla_id, Pkom[i].dl_id,
					Pkom[i].dl_vondat, Pkom[i].dl_bisdat, Pkom[i].kont_id, Pkom[i].bid,
					Pkom[i].history, Pkom[i].sai_id, Pkom[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KOMM_DETAIL: /* Tabelle 45 */
			len = sizeof(komdet);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pkomdet = (KOMM_DETAIL *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t\r",
					Pkomdet[i].komm_id, Pkomdet[i].bid, Pkomdet[i].dln_id,
					Pkomdet[i].kun_id, Pkomdet[i].kol_id, Pkomdet[i].prio);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;


		/* ANGEBOT */
		case (int)_SAISON: /* Tabelle 9 */
			len = sizeof(sai);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Psai = (SAISON *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t\r",
					Psai[i].sai_id, Psai[i].bez_id, Psai[i].von, Psai[i].bis,
					Psai[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_SAI_VIEW: /* View 262 */
			len = sizeof(saiv);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 6);
			len = strlen(outmem->buffer);
			Psaiv = (SAI_VIEW *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Psaiv[i].bez);
				/* DATUM Saison von/bis */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Psaiv[i].von, tmpbuf1);
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Psaiv[i].bis, tmpbuf2);
				sprintf(record, "%d\t%s\t%d\t%s\t%s\t%d\t\r",
					Psaiv[i].sai_id, Psaiv[i].bez, Psaiv[i].s_id, tmpbuf1, tmpbuf2,
					Psaiv[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_PROGRAMM: /* Tabelle 29 */
			len = sizeof(prg);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 4);
			len = strlen(outmem->buffer);
			Pprg = (PROGRAMM *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t\r",
					Pprg[i].prg_id, Pprg[i].bez_id, Pprg[i].textid, Pprg[i].sai_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_ARRANGEMENT: /* Tabelle 30 */
			len = sizeof(arr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 6);
			len = strlen(outmem->buffer);
			Parr = (ARRANGEMENT *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				/* DATUM ARR */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&Parr[i].a_dat, tmpbuf1);
				sprintf(record, "%d\t%d\t%s\t%d\t%d\t%d\t\r",
					Parr[i].arr_id, Parr[i].bez_id, tmpbuf1, Parr[i].prg_id,
					Parr[i].textid, Parr[i].sai_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_ARRDL_VIEW: /* Tabelle 276 */
			len = sizeof(adlv);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 9);
			len = strlen(outmem->buffer);
			Padlv = (ARRDL_VIEW *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				/* DATUM ARR */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&Padlv[i].a_dat, tmpbuf1);
				/* DATUM DL */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&Padlv[i].a_zeit, tmpbuf2);
				(void)sprintf(record, "%d\t%s\t%d\t%s\t%s\t%d\t%d\t%d\t%d\t\r",
					Padlv[i].arr_id, tmpbuf1, Padlv[i].dlg_id, Padlv[i].bez,
					tmpbuf2, Padlv[i].teil, Padlv[i].prio,
				   Padlv[i].akt_id, Padlv[i].s_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_ARR_VIEW: /* View 277 */
			len = sizeof(arrv);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Parrv = (ARR_VIEW *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				/* DATUM ARR */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)0;
				DateTime.tm_min =(int)0;
				(void)WriteDate(&DateTime, (time_t *)&Parrv[i].a_dat, tmpbuf1);
				cutspaces(Parrv[i].bez);
				sprintf(record, "%d\t%s\t%d\t%s\t%d\t%d\t%d\t\r",
					 Parrv[i].arr_id, Parrv[i].bez, Parrv[i].s_id, tmpbuf1,
					 Parrv[i].prg_id, Parrv[i].textid, Parrv[i].sai_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_DIENSTLEISTUNG: /* Tabell 27 */
			len = sizeof(dlg);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 6);
			len = strlen(outmem->buffer);
			Pdlg = (DIENSTLEISTUNG *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pdlg[i].dlg_id, Pdlg[i].bez_id, Pdlg[i].textid,
					 Pdlg[i].sai_id, Pdlg[i].a_zeit, Pdlg[i].akt_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_DTG_VIEW: /* View 275 */
			len = sizeof(dlv);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pdlv = (DTG_VIEW *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pdlv[i].bez);
				/* DATUM DL */
				DateTime.tm_mday=(int)_UNDEF;
				DateTime.tm_mon =(int)_UNDEF;
				DateTime.tm_year=(int)_UNDEF;
				DateTime.tm_hour=(int)_UNDEF;
				DateTime.tm_min =(int)_UNDEF;
				(void)WriteDate(&DateTime, (time_t *)&Pdlv[i].a_zeit, tmpbuf1);
				sprintf(record, "%d\t%s\t%d\t%d\t%d\t%s\t%d\t\r",
					 Pdlv[i].dlg_id, Pdlv[i].bez, Pdlv[i].s_id, Pdlv[i].textid,
					 Pdlv[i].sai_id, tmpbuf1, Pdlv[i].akt_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_DLG_PART: /* Tabelle 26 */
			len = sizeof(dlgp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pdlgp = (DLG_PART *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pdlgp[i].konto);
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t\r",
					 Pdlgp[i].dl_id, Pdlgp[i].h_dl_id, Pdlgp[i].dla_id, Pdlgp[i].bez_id,
					 Pdlgp[i].ord, Pdlgp[i].a_zeit, Pdlgp[i].e_zeit, Pdlgp[i].res_f,
					 Pdlgp[i].kid, Pdlgp[i].konto, Pdlgp[i].textid, Pdlgp[i].sai_id,
					 Pdlgp[i].rechst);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_DIENST_ANGEBOT: /* Tabelle 23 */
			len = sizeof(dla);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pdla = (DIENST_ANGEBOT *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pdla[i].ort);
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pdla[i].dla_id, Pdla[i].h_dla_id, Pdla[i].ord, Pdla[i].dlt_id,
					 Pdla[i].bez_id, Pdla[i].akt_id, Pdla[i].ort, Pdla[i].art_id,
					 Pdla[i].dau, Pdla[i].textid, Pdla[i].von, Pdla[i].nach);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_ANGEBOTS_TYP: /* Tabelle 18 */
			len = sizeof(atyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Patyp = (ANGEBOTS_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t\r",
					 Patyp[i].art_id, Patyp[i].bez_id, Patyp[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_AKTIONEN: /* Tabelle 21 */
			len = sizeof(akt);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pakt = (AKTIONEN *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pakt[i].akt_id, Pakt[i].bez_id, Pakt[i].textid, Pakt[i].a_flag,
					 Pakt[i].b_flag, Pakt[i].m_flag, Pakt[i].a_typ_id, Pakt[i].b2_flag);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_AKTIONSGRP: /* Tabelle 22 */
			len = sizeof(aktg);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Paktg = (AKTIONSGRP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t\r",
					 Paktg[i].parentakt, Paktg[i].childakt, Paktg[i].ord,
					 Paktg[i].h_akt_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_HOST_KONT: /* Tabelle 38 */
			len = sizeof(hkont);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Phkont = (HOST_KONT *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Phkont[i].ref);
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t\r",
					 Phkont[i].hostkont_id, Phkont[i].bez_id, Phkont[i].from_pers,
					 Phkont[i].kbst, Phkont[i].dla_id, Phkont[i].dl_id,
					 Phkont[i].dl_vondat, Phkont[i].dl_bisdat, Phkont[i].textid,
					 Phkont[i].opt_dat, Phkont[i].sai_id, Phkont[i].ref,
					 Phkont[i].history);

				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KONTINGENT: /* Tabelle 39 */
			len = sizeof(kont);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkont = (KONTINGENT *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkont[i].ref);
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t\r",
					 Pkont[i].kont_id, Pkont[i].bez_id, Pkont[i].hostkont_id,
					 Pkont[i].kunden_id, Pkont[i].opt_dat, Pkont[i].ref,
					 Pkont[i].sai_id, Pkont[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KONT_DETAIL: /* Tabelle 40 */
			len = sizeof(kontd);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkontd = (KONT_DETAIL *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pkontd[i].hostkont_id, Pkontd[i].kont_id, Pkontd[i].kat_id,
					 Pkontd[i].dlt_id, Pkontd[i].sta_id, Pkontd[i].anz,
					 Pkontd[i].busy, Pkontd[i].minanz);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_PREIS: /* Tabelle 47 */
			len = sizeof(pre);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Ppre = (PREIS *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%.2f\t%.2f\t%.2f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Ppre[i].pre_id, Ppre[i].apr, Ppre[i].epr, Ppre[i].vpr,
					 Ppre[i].glt, Ppre[i].whr_id, Ppre[i].kbst, Ppre[i].kar_id,
					 Ppre[i].dltt_id, Ppre[i].kat_id, Ppre[i].rkr_id, Ppre[i].dla_id,
					 Ppre[i].dl_id, Ppre[i].dl_vondat, Ppre[i].dl_bisdat, Ppre[i].kont_id,
					 Ppre[i].sta_id, Ppre[i].textid, Ppre[i].history, Ppre[i].sai_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;



		/* STAMM */
		case (int)_TRAEGER_TYP:/* Tabelle 15 */
			len = sizeof(ttyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pttyp = (TRAEGER_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t\r",
					 Pttyp[i].typ_id, Pttyp[i].bez_id, Pttyp[i].h_typ_id,
					 Pttyp[i].host_typ, Pttyp[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_DIENST_TRAEGER: /* Tabelle 17 */
			len = sizeof(dlt);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pdlt = (DIENST_TRAEGER *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pdlt[i].dlt_id, Pdlt[i].bez_id, Pdlt[i].kat_id,
					 Pdlt[i].h_dlt_id, Pdlt[i].dlt_grp_id, Pdlt[i].host_id,
					 Pdlt[i].typ_id, Pdlt[i].textid, Pdlt[i].stufe,
					 Pdlt[i].sta_id);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KATEGORIE: /* Tabelle 16 */
			len = sizeof(kat);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkat = (KATEGORIE *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pkat[i].kat_id, Pkat[i].bez_id, Pkat[i].h_kat_id,
					 Pkat[i].typ_id, Pkat[i].ga, Pkat[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KAT_VIEW: /* Tabelle 268 */
			len = sizeof(katv);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkatv = (KAT_VIEW *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkatv[i].bez);
				(void)strcpy(tmpbuf1, "-");
				sta.typ = (int)_GA;
				id = MPAPIselectOneId((int)_STATUS_WERTE, Pkatv[i].ga, (char *)&sta);
				if (id != (int)_UNDEF)
					id = SelectBez((int)_GA, sprache, sta.bez_id, tmpbuf1);

				sprintf(record, "%d\t%s\t%d\t%d\t%s\t%d\t\r",
					 Pkatv[i].kat_id, Pkatv[i].bez, Pkatv[i].s_id,
					 Pkatv[i].h_kat_id, Pkatv[i].typ_id, tmpbuf1, Pkatv[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_PCX_FILES: /* Tabelle 49 */
			len = sizeof(pcx);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Ppcx = (PCX_FILES *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Ppcx[i].filename);
				sprintf(record, "%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t\r",
					 Ppcx[i].pcx_id, Ppcx[i].bez_id, Ppcx[i].filename,
					 Ppcx[i].x, Ppcx[i].y, Ppcx[i].typ,
					 Ppcx[i].typcode, Ppcx[i].folge);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_GRAPHIK: /* Tabelle 48 */
			len = sizeof(gra);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pgra = (GRAPHIK *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%d\t\r",
					 Pgra[i].gra_id, Pgra[i].bez_id, Pgra[i].dlt_id, Pgra[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_AKTIONS_TYP: /* Tabelle 19 */
			len = sizeof(akttyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pakttyp = (AKTIONS_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pakttyp[i].proz);
				sprintf(record, "%d\t%d\t%s\t%d\t\r",
					 Pakttyp[i].a_typ_id, Pakttyp[i].bez_id, Pakttyp[i].proz,
					 Pakttyp[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KOSTEN_ART: /* Tabelle 43 */
			len = sizeof(kar);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkar = (KOSTEN_ART *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t\r",
					 Pkar[i].kar_id, Pkar[i].bez_id, Pkar[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KUNDEN_TYP: /* Tabelle 24 */
			len = sizeof(kutyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkutyp = (KUNDEN_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkutyp[i].kuncode);
				sprintf(record, "%d\t%d\t%d\t%s\t\r",
					 Pkutyp[i].k_typ_id, Pkutyp[i].bez_id, Pkutyp[i].textid,
					 Pkutyp[i].kuncode);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_REISENDER_TYP: /* Tabelle 35 */
			len = sizeof(rtyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Prtyp = (REISENDER_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Prtyp[i].dlncode);
				sprintf(record, "%d\t%d\t%d\t%s\t%d\t%d\t\r",
					 Prtyp[i].rkr_id, Prtyp[i].bez_id, Prtyp[i].textid,
					 Prtyp[i].dlncode, Prtyp[i].vonalter, Prtyp[i].bisalter);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_KOLLEKTIV_TYP: /* Tabelle 32 */
			len = sizeof(kotyp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pkotyp = (KOLLEKTIV_TYP *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pkotyp[i].kolcode);
				sprintf(record, "%d\t%d\t%s\t%d\t\r",
					 Pkotyp[i].k_typ_id, Pkotyp[i].bez_id, Pkotyp[i].kolcode,
					 Pkotyp[i].textid);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_STATUS_WERTE: /* Tabelle 2 */
			len = sizeof(sta);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Psta = (STATUS_WERTE *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Psta[i].abk);
				cutspaces(Psta[i].sta);
				sprintf(record, "%d\t%s\t%s\t%d\t%.2f\t%d\t\r",
					 Psta[i].sta_id, Psta[i].abk, Psta[i].sta,
					 Psta[i].bez_id, Psta[i].kond, Psta[i].typ);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;


		/* GEOGRAFIE */
		case (int)_SPRACHEN: /* Tabelle 1 */
			len = sizeof(spr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pspr = (SPRACHEN *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pspr[i].sysbez);
				sprintf(record, "%d\t%d\t%d\t%s\t\r",
					 Pspr[i].s_id, Pspr[i].bez_id, Pspr[i].dialog, Pspr[i].sysbez);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_WAEHRUNG: /* Tabelle 12 */
			len = sizeof(whr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pwhr = (WAEHRUNG *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pwhr[i].krzl);
				sprintf(record, "%d\t%d\t%d\t%d\t%s\t\r",
					 Pwhr[i].whr_id, Pwhr[i].bez_id, Pwhr[i].textid, Pwhr[i].status,
					 Pwhr[i].krzl);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_LAND: /* Tabelle 10 */
			len = sizeof(land);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pland = (LAND *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pland[i].krzl);
				cutspaces(Pland[i].dateformat);
				sprintf(record, "%d\t%d\t%d\t%s\t%d\t%d\t%d\t%.2f\t%s\t\r",
					 Pland[i].land_id, Pland[i].bez_id, Pland[i].textid,
					 Pland[i].krzl, Pland[i].haupt_ort, Pland[i].haupt_whr,
					 Pland[i].haupt_spr, Pland[i].vat, Pland[i].dateformat);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_ORT: /* Tabelle 11 */
			len = sizeof(ort);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Port = (ORT *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Port[i].krzl);
				sprintf(record, "%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t\r",
					 Port[i].ort_id, Port[i].bez_id, Port[i].land_id, Port[i].textid,
					 Port[i].krzl, Port[i].zeitver, Port[i].koord1, Port[i].koord2);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_LAND_WHR: /* Tabelle 13 */
			len = sizeof(lwhr);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Plwhr = (LAND_WHR *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				sprintf(record, "%d\t%d\t%d\t%.2f\t%.2f\t\r",
					 Plwhr[i].land_id, Plwhr[i].whr_id, Plwhr[i].kurs_typ,
					 Plwhr[i].a_kurs, Plwhr[i].v_kurs);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;


		/* Administration */
		case (int)_MP_PROFIL: /* Tabelle 55 */
			len = sizeof(mpp);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pmpp = (MP_PROFIL *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pmpp[i].mpuser);
				sprintf(record, "%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\r",
					 Pmpp[i].mpuser, Pmpp[i].bchst, Pmpp[i].seclevel,
					 Pmpp[i].s_id, Pmpp[i].land_id, Pmpp[i].dltt_id,
					 Pmpp[i].dlt_id, Pmpp[i].kat_id, Pmpp[i].dlat_id,
					 Pmpp[i].dlnt_id, Pmpp[i].sai_id, Pmpp[i].prg_id,
					 Pmpp[i].a_zeit, Pmpp[i].e_zeit, Pmpp[i].p_range);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_BEZEICHNUNG: /* Tabelle 3 */
			len = sizeof(bez);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pbez = (BEZEICHNUNG *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pbez[i].bez);
				sprintf(record, "%d\t%d\t%s\t%d\t\r",
					 Pbez[i].bez_id, Pbez[i].s_id, Pbez[i].bez,
					 Pbez[i].typ);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;
		case (int)_MSG: /* Tabelle 7 */ /* _MP_MSG would be better */
			len = sizeof(mesg);
			outmem->datalen = (len * count);
			if (outmem->datalen > outmem->alloclen)
				outmem->buffer = PSSYSallocobj(outmem, PSMEMCHUNK30);
			sprintf(outmem->buffer, "%d\n%d\n%d\n", PSOK, count, 7);
			len = strlen(outmem->buffer);
			Pmesg = (MP_MSG *)inputbuffer;
			for (i = 0; i < count; i++)
				{
				cutspaces(Pmesg[i].text);
				sprintf(record, "%d\t%d\t%d\t%d\t%s\t\r",
					 Pmesg[i].msg_typ, Pmesg[i].msg_id, Pmesg[i].s_id,
					 Pmesg[i].textnr, Pmesg[i].text);
				strcat(outmem->buffer, record);
				}
			outmem->datalen = strlen(outmem->buffer);
			break;

		default:
			break;
		}


	return((int)MPOK);
}

static void cutspaces(char *buf)
{
	int len;
	char *ptr;

	len = strlen(buf);

	ptr = (char *)&buf[len] - (int)1;

	while (*ptr == ' ')
		{
		*ptr = (char)NULL;
		if (buf == ptr)
			break;
		ptr--;
		}

	return;
}
