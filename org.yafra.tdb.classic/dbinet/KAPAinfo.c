/*D***********************************************************
 * Modul:     DBI - matrix
 *            Dienstleistungstraeger
 *            prepare DLT/DL matrix list
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpnet.h>
#include <mpmsg.h>
#include <mpsqlsel.h>
#include <mpstadef.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbinet/KAPAinfo.c,v 1.2 2008-11-02 19:55:51 mwn Exp $";

#define _MX_DLA_NUMFIELDS  1
#define _MX_DLA_XMAX       5
#define _MX_DLA_MAXDAYS		10

static int GetFirstDLAchild(DIENST_ANGEBOT *);

/*************************************************************
 * function:  KAPA VIEW make information string
 * typ:       public
 * desc:      get KAPA VIEW entries for a DL or ARR
 * input:     DL or ARR ID as char buffer (dlid\tarrid\t\0)
 *************************************************************/
int KAPAVinfo(char *aInbuf, PSmemobj *aOutbuf)
{
	extern int sprache;
	extern PREIS pre;

	DLG_PART localtdl;
	MEMOBJ kapavmem;
	MPV_KAPA *Pkapav;
	register int i;
	int status = (int)MPOK;
	int katcnt;
	int kapacnt;
	int buflen;
	char query[_QUERYLEN];
	char bez[_RECORDLEN];
	char text[_RECORDLEN];
	char preistext[_RECORDLEN];
	char freetext[_RECORDLEN];
	char tdl_string[_RECORDLEN];
	char tmp_buffer[_RECORDLEN];
	int MPdlid;
	int MPkatfree;

	aOutbuf->datalen = (10 * _RECORDLEN);
	if (aOutbuf->datalen > aOutbuf->alloclen)
		aOutbuf->buffer = PSSYSallocobj(aOutbuf, PSMEMCHUNK30);

	/********************/
	/* KATEGORIE matrix */
	/********************/

	MPdlid = atoi(aInbuf);
	status = MPAPIselectTDL(MPdlid, &localtdl);

	/* init */
	kapavmem.buffer = NULL;
	kapavmem.datalen = 0;
	kapavmem.alloclen = 0;
	katcnt = 0;

	/* write init MPNET header */
	sprintf(aOutbuf->buffer, "0\n1\n3\n");

	/* get all cell entries via KAPA */
	sprintf(tdl_string, "%d", localtdl.dl_id);
	(void)sprintf(query, _SEL_KAPAV_TDLS, tdl_string, sprache, sprache);
	status=MPAPIdb_sqlquery((int)_MPV_KAPA, (char **)&kapavmem.buffer, query,
	                         &kapacnt, &kapavmem.datalen, &kapavmem.alloclen);
	Pkapav = (MPV_KAPA *)kapavmem.buffer;
	if (status != (int)MPOK || kapacnt < 1)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		MPfreeobj(&kapavmem);
		return((int)MPERROR);		
		}

	/* write row: KATBEZ, PREIS, FREE  */
	for (i=0; i<kapacnt; i++)
		{
		MPkatfree = Pkapav[i].anz - Pkapav[i].busy;

		if ( MPkatfree < (int)1 )
			sprintf( freetext, "gtee" );
		else
			sprintf( freetext, "%4d", MPkatfree );

		(void)copyTextTo(bez, (char *)Pkapav[i].katbez, (int)_BEZLEN);

		if ( Pkapav[i].vpr == (double)0.0 )
			(void)sprintf(preistext, "-");
		else
			(void)sprintf(preistext, "%8.2f", Pkapav[i].vpr);

		(void)sprintf(text, "%d\t%s\t%s\t%s\t\r", Pkapav[i].kat_id, bez,
		              preistext, freetext);
		(void)strcat(aOutbuf->buffer, text);
		}
	MPfreeobj(&kapavmem);

	i = strlen(aOutbuf->buffer);
	aOutbuf->buffer[i-1] = NULL;

	return(MPOK);
}

static int GetFirstDLAchild(DIENST_ANGEBOT *dla)
{
	unsigned long dlen, alen;
	int status;
	int dlacnt;
	DIENST_ANGEBOT *dlamem;
	char query[_QUERYLEN];

	status = (int)MPOK;
	alen = dlen = 0;
	dlamem = NULL;

	(void)sprintf(query, _SEL_DLA_ALLFROMHOST, dla->dla_id);
	status=MPAPIdb_sqlquery((int)_DIENST_ANGEBOT, (char **)&dlamem, query,
	       &dlacnt, &dlen, &alen);
	if (status == (int)MPOK && dlacnt > 0)
		{
		/* overwrite existing host dla entry with first found child ! */
		(void)memcpy((void *)dla, (void *)&dlamem[0], sizeof(DIENST_ANGEBOT));
		}

	MPfree((void *)dlamem);

	return(status);
}
