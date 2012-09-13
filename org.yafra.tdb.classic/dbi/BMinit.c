/*D***********************************************************
 * Modul:     DBI - BM
 *            init every booking object
 *
 * Copyright: yafra.org, Aesch, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/BMinit.c,v 1.4 2009-01-02 16:51:35 mwn Exp $";

void BMinit(void)
{
	extern BUCHUNG bch;
	extern BCH_DLN bd;
	extern PERSONEN pers;
   extern PERSADR adr;
	extern REISENDER rei;
	extern RESERVATION res;
	extern ARRANGEMENT arr;
	extern DIENSTLEISTUNG dtg;
	extern MP_PROFIL prof;

	extern unsigned char bm_obj;
	extern unsigned char bm_state;
	extern unsigned int  bm_dlncnt;
	extern int glob_teil;

	bch.mpid = prof.mpid;
	bch.sach = prof.mpid;
	bch.bid     = (int)_UNDEF;
	bch.ast     = (int)_UNDEF;
	bch.b_text  = (int)_UNDEF;
	bch.history = (int)_UNDEF;

	bd.dln_id = (int)_UNDEF;
	bd.bid    = (int)_UNDEF;

	pers.pers_id = (int)_UNDEF;
	*pers.name  = (char)NULL;
	*adr.ort = (char)NULL;
	pers.sta_id = (int)_UNDEF;
	pers.textid = (int)_UNDEF;

	rei.pers_id = (int)_UNDEF;
	*rei.vor    = NULL;
	rei.rkr_id = (int)_UNDEF;
	adr.land_id = (int)_UNDEF;
	rei.mutters_id = (int)_UNDEF;
	*rei.passnr = NULL;
	*rei.age = NULL;
	*rei.attr1 = NULL;
	*rei.attr2 = NULL;

	res.dl_id   = (int)_UNDEF;
	res.dlg_id  = (int)_UNDEF;
	res.textid  = (int)_UNDEF;

	dtg.dlg_id  = (int)_UNDEF;

	arr.arr_id  = (int)_UNDEF;

	bm_obj = NULL;
	bm_state = _BM_NOP;
	bm_dlncnt = 0;
	glob_teil = (int)_UNDEF;
}
