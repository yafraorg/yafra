/*D***********************************************************
 * Modul:     DBI - graphic                           
   Beschreibung: Erzeugt eine Liste mit den Regions des DLT's
					  Wenn im SELECTGRA-Fall keine Regionsdaten vor-
					  handen sind, wird ein normales SelectMenu
					  gef�llt und auf den ersten Character im buffer
					  ein \n geschrieben, was bedeutet, dass kein
					  Graphikfile gelesen werden kann.
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRwrite.c,v 1.2 2008-11-02 19:55:41 mwn Exp $";

static int GRwriteGraphicform(char *, int *, GRAPHIK *);

int GRwrite(int len, char *buffer)
{
	extern GRAPHIK gra;

	DIENST_TRAEGER dlt;
	REGIONS *regions;
	char message[RECLAENGE];
	char *ptr;
	char *regbuffer;
	int  formlen = 0;
	int reglen = 0;
	int anzreg, i;
	int status=(int)MPOK;

	/* a graphic must be activ */
	if (gra.dlt_id == (int)_UNDEF)
		{
		UtilMsg((int)MPE_NOGRADLT, MSGTYP_ERROR, NULL);
		return((int)MPERROR);
		}

	/* delete old regions of activ graphic */
	status = MPAPIdeleteEntry((int)_REGIONS, (char *)&gra);
	if ( status != (int)MPOK && status != (int)MPE_NOINSUPDDEL)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	(void)MPAPIdb_committrx();

	status=MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* delete old graphic form data */
	status = MPAPIdeleteEntry((int)_GRAFORM, (char *)&gra);
	if (status != (int)MPOK && status != (int)MPE_NOINSUPDDEL)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	(void)MPAPIdb_committrx();

	status=MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* write graphic form data */
	status = GRwriteGraphicform(buffer, &formlen, &gra);
	if (status != (int)MPOK)
		return((int)MPERROR);
	reglen = len - formlen;
	regbuffer = &buffer[formlen];

	(void)MPAPIdb_committrx();

	status=MPAPIdb_begintrx(SQLISOLATION_RR, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	/* let's write the regions to the db */
	regions = (REGIONS *)NULL;
	for (ptr = regbuffer; ptr < regbuffer + reglen;)
		{
		anzreg = GRnextRegion((char **)&ptr, regbuffer, (REGIONS **)&regions);
		if (anzreg > (int)0)
			{
			status = GRtestRegion(regions, anzreg);
			if (status == (int)MPOK)
				{
				for (i=0; i<anzreg; i++)
					{
					/* insert new regions of the activ graphic */
					status=MPAPIinsertEntry((int)_REGIONS,(char *)&regions[i],(BEZEICHNUNG *)NULL);
					if (status != (int)MPOK )
						{
						UtilMsg(status, MSGTYP_DBERROR, NULL);
						return((int)MPERROR);
						}
					}
				}
			else
				{
				UtilMsg((int)MPE_TESTREGION, MSGTYP_ERROR, NULL);
				return((int)MPERROR);
				}
			}
		else
			continue;
		}

	comm.datalen=(int)0;
	comm.buffer[0] = NULL;

	MPfree((void *)regions);
	return(status);
}

static int GRwriteGraphicform(char *buffer, int *len, GRAPHIK *gra)
{
	GRAFORM form;
	char *ptr;
	int status = (int)MPOK;
	int anzahl;
	int i;
	int linelen;
	int tmplen = 0;

	/* init */
	form.gra_id = gra->gra_id;

	ptr = buffer;
	for (tmplen = 0; *buffer != '\n'; buffer++)
		tmplen++;
	*buffer = NULL;
	anzahl = atoi(ptr);
	buffer++;
	tmplen++;
	ptr = buffer;

	for (i=0; i < anzahl; i++)
		{
		/* read line no */
		for (; *buffer != '\t'; buffer++)
			tmplen++;
		*buffer = NULL;
		form.formnr = atoi(ptr);
		buffer++;
		tmplen++;
		ptr = buffer;

		/* read format */
		for (linelen = 0; *buffer != '\t'; buffer++, linelen++)
			tmplen++;
		*buffer = NULL;
		if (linelen > _GRAFORMLEN)
			{
			UtilMsg((int)MPE_GRAFORMTOOLONG, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		(void)strcpy(form.form, ptr);
		status=MPAPIinsertEntry((int)_GRAFORM, (char *)&form, (BEZEICHNUNG *)NULL);
		if (status != (int)MPOK )
			{
			UtilMsg(status, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		buffer++;
		if (*buffer != '\n')
			{
			UtilMsg((int)MPE_GRAFORMTOOLONG, MSGTYP_DBERROR, NULL);
			return((int)MPERROR);
			}
		buffer++;
		tmplen += 2;
		ptr = buffer;
		}
	*len = tmplen;
	return((int)MPOK);
}
