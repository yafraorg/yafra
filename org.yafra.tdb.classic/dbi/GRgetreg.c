/*D***********************************************************
 * Modul:     DBI - graphic modul
 *            read regions and graphic from DB
 *
 * return:    0 if error else the length of the buffer
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRgetreg.c,v 1.3 2008-11-29 21:56:38 mwn Exp $";

#define GRAFORMLEN 120
#define REGIONSLEN 100

int GRgetRegionsFromDB(GRAPHIK *graphik)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern COLORTAB *colorTab;
	extern int AnzCol;
	extern char sqlquery[];

	DLT_VIEW *Pdltv;
	MEMOBJ reg_mem;
	REGIONS *Preg;
	GRAFORM *form;
	char tmpform[_GRAFORMLEN+1];
	char bez_low[_BEZLEN+1];
	char bez_upp[_BEZLEN+1];
	char *ptr;
	unsigned char farbe;

	int status = (int)MPOK;
	int parts, anzdlt, anzreg, anzdltreg;
	int stufe, stufe_ende, stufe_anfang;
	int regcount, lx, intvalue, oldcount;
	int AnzRegPkte = (int)0;
	int anzform;
	int i, j;
	int firstid;
	int nummer;
	int newmemsize;
	size_t laenge;
	long len = 0;
	unsigned long dlen;
	unsigned long alen;

	if (graphik->dlt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOGRADLT, MSGTYP_ERROR, NULL);
		return(0);
		}

	if (ACTIONTYP == (unsigned char)MPDELETE)
		{
		UtilMsg((int)MPE_NOGRAINDELMODE, MSGTYP_ERROR, NULL);
		return(0);
		}

	/* init for get regions from db */
	farbe = NOCOLOR;
	reg_mem.buffer = NULL;
	reg_mem.alloclen = 0;
	reg_mem.datalen = 0;

	/* get all dlt of one host from dlt_view */
	(void)sprintf(sqlquery, _SEL_DLTVIEW_HOST, (int)sprache, graphik->dlt_id);
	status=MPAPIdb_sqlquery((int)_DLT_VIEW, &sqlmem.buffer, sqlquery, &anzdlt,
	                         &sqlmem.datalen, &sqlmem.alloclen);
	Pdltv = (DLT_VIEW *)sqlmem.buffer;

	if (MENUNR == (unsigned char)_BUCHUNG ||
	    MENUNR == (unsigned char)_RESERVATION ||
	    ACTIONTYP == (unsigned char)UPDATE)
		{
		/* get graphic form */
		dlen = alen = 0;
		(void)sprintf(sqlquery, _SEL_FORM_GRA, graphik->gra_id);
		form = NULL;
		status=MPAPIdb_sqlquery((int)_GRAFORM, (char **)&form, sqlquery,
	                         &anzform, &dlen, &alen);

		/* check memory */
		newmemsize = ((anzform * GRAFORMLEN) + (anzdlt * REGIONSLEN));
		if (newmemsize > comm.alloclen)
			comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
			              DEFMEMCHUNK, newmemsize, sizeof(char));

		/* write graphic form into output buffer */
		ptr = comm.buffer;
		(void)sprintf(comm.buffer, "%d\n\0", anzform);
		ptr += strlen(comm.buffer);
		for (i = 0; i < anzform; i++)
			{
			(void)copyTextTo(tmpform, form[i].form, (int)_GRAFORMLEN);
			(void)sprintf(ptr, "%d\t%s\t\n\0", form[i].formnr, tmpform);
			ptr += strlen(ptr);
			}
		len = laenge = (size_t)strlen(comm.buffer);
		MPfree((char *)form);

		/* get all regions */
		(void)sprintf(sqlquery, _SEL_REG_GRA, graphik->dlt_id);
		status=MPAPIdb_sqlquery((int)_REGIONS, &reg_mem.buffer, sqlquery,
		                        &anzreg, &reg_mem.datalen, &reg_mem.alloclen);
		Preg = (REGIONS *)reg_mem.buffer;

		for(i=0; i < anzdlt; i++)
			{
			/* Diensttraeger Bezeichnung */
			(void)copyTextTo(bez_low, Pdltv[i].bez, (int)_BEZLEN);
			(void)strcpy((char *)&comm.buffer[laenge], bez_low);
			laenge += strlen(bez_low);
			if (Pdltv[i].dlt_id != Pdltv[i].host_id)
				{
				for (j=0; j<anzdlt; j++)
					{
					if (Pdltv[j].dlt_id == Pdltv[i].h_dlt_id)
						{
						(void)copyTextTo(bez_upp, Pdltv[j].bez, (int)_BEZLEN);
						(void)strcpy ( (char *)&comm.buffer[laenge], TRENNER);
						laenge += (size_t)TRENNERLEN;
						(void)strcpy ( (char *)&comm.buffer[laenge], bez_upp);
						laenge += strlen ( bez_upp );
						break;
						}
					}
				}

			/* \n */
			(void)strcpy((char *)&comm.buffer[laenge], "\n" );
			laenge++;

			/* Farbe */
			for (j=0; j < AnzCol; j++)
				{
				if (Pdltv[i].kat_id == colorTab[j].KAT_ID)
					{
					farbe = colorTab[j].COL_IDX;
					break;
					}
				}
			sprintf(&comm.buffer[laenge], "%d\n", (int)farbe);
			laenge += strlen(&comm.buffer[laenge]);

			/* get all regions of this dlt */
			anzdltreg = 0;
			firstid = (int)_UNDEF;
			for (j=0; j<anzreg; j++)
				{
				if (Preg[j].dlt_id == Pdltv[i].dlt_id)
					{
					if (firstid == (int)_UNDEF)
						firstid = j;
					anzdltreg++;
					}

				/* !DANGER! Preg is sorted by DLT_ID - check it !! */
				if (Preg[j].dlt_id > Pdltv[i].dlt_id)
					break;
				}

			if (anzdltreg == (int)0)
				{
				sprintf(&comm.buffer[laenge], "0\n");
				laenge += (int)2;
				}
			else
				{
				sprintf(&comm.buffer[laenge], "%d\n", (int)anzdltreg);
				laenge += strlen(&comm.buffer[laenge]);
				for (j=firstid; j<anzreg; j++)
					{
					if (Preg[j].dlt_id == Pdltv[i].dlt_id)
						{
						sprintf(&comm.buffer[laenge], "%d\n", Preg[j].nummer);
						laenge += strlen(&comm.buffer[laenge]);
						}

					/* !DANGER! Preg is sorted by DLT_ID - check it !! */
					if (Preg[j].dlt_id > Pdltv[i].dlt_id)
						break;
					}
				}
			}
		comm.buffer[laenge] = NULL;
		laenge++;
		MPfreeobj(&reg_mem);
		}
	else if (ACTIONTYP == (unsigned char)INSERT && MENUNR == (unsigned char)_GRAPHIK)
		{
		/* check memory */
		newmemsize = ((anzdlt * REGIONSLEN));
		if (newmemsize > comm.alloclen)
			comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
			              DEFMEMCHUNK, newmemsize, sizeof(char));

		/* loesche eventuell vorhandene Regions */
		status = MPAPIdeleteEntry((int)_REGIONS, (char *)graphik);
		// TODO ignore status as a delete could be zero rows affected which does not mean an error but would return an error from deleteEntry
		/*
		if ( status != (int)MPOK )
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)0);
			}
		*/

		/* delete old graphic form data */
		status = MPAPIdeleteEntry((int)_GRAFORM, (char *)graphik);
		// TODO ignore status - same as above - deleted if()

		/* empty graphic form */
		(void)strcpy(comm.buffer, "0\n");
		laenge = (size_t)2;

		for(i=0; i < anzdlt; i++)
			{
			/* Diensttraeger Bezeichnung */
			(void)copyTextTo(bez_low, Pdltv[i].bez, (int)_BEZLEN);
			(void)strcpy((char *)&comm.buffer[laenge], bez_low);
			laenge += strlen(bez_low);
			if (Pdltv[i].dlt_id != Pdltv[i].host_id)
				{
				for (j=0; j<anzdlt; j++)
					{
					if (Pdltv[j].dlt_id == Pdltv[i].h_dlt_id)
						{
						(void)copyTextTo(bez_upp, Pdltv[j].bez, (int)_BEZLEN);
						(void)strcpy ( (char *)&comm.buffer[laenge], TRENNER);
						laenge += (size_t)TRENNERLEN;
						(void)strcpy ( (char *)&comm.buffer[laenge], bez_upp);
						laenge += strlen ( bez_upp );
						break;
						}
					}
				}

			/* \n */
			(void)strcpy((char *)&comm.buffer[laenge], "\n" );
			laenge++;

			/* Farbe */
			for (j=0; j < AnzCol; j++)
				{
				if (Pdltv[i].kat_id == colorTab[j].KAT_ID)
					{
					farbe = colorTab[j].COL_IDX;
					break;
					}
				}
			sprintf(&comm.buffer[laenge], "%d\n", (int)farbe);
			laenge += strlen(&comm.buffer[laenge]);

			/* set region count to zero - we don't have any regions yet */
			sprintf(&comm.buffer[laenge], "0\n");
			laenge += (size_t)2;
			}
		comm.buffer[laenge] = NULL;
		laenge++;
		}
	else
		{
		UtilMsg((int)MPE_PROTOCOL, MSGTYP_ERROR, NULL);
		laenge = 0;
		}

	return (laenge);
}
