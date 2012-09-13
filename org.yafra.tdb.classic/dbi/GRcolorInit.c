/*D***********************************************************
 * Modul:     DBI - graphic modul
 *            make a colors per categorie table
 *
 * Copyright: yafra.org, Basel, Switzerland     
 * Autor:     Administrator
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/GRcolorInit.c,v 1.2 2008-11-02 19:55:40 mwn Exp $";

int GRcolorInit(char **outcolorListe, int *outlen)
{
	extern MEMOBJ sqlmem;
	extern COLORTAB *colorTab;
	extern int AnzCol;
	extern char sqlquery[];

	KATEGORIE *kat;
	STATUS_WERTE *colorPtr;
	int anzahl;
	char *colorListe;
	int len = 0;
	int found;
	int i, y;
	int status=(int)MPOK;
	unsigned long dlen = 0;
	unsigned long alen = 0;

	(void)MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	(void)strcpy(sqlquery, _SEL_BEZ_STA_COL);
	status=MPAPIdb_sqlquery(_STATUS_WERTE, &sqlmem.buffer, sqlquery,
	                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ((status == (int)MPOK) && (anzahl > 0))
		{
		colorPtr = (STATUS_WERTE *)sqlmem.buffer;
		colorListe = malloc(anzahl * (_CHAR39 + 1));
		if (!colorListe)
			return(-1);
		for (i=0; i < anzahl; i++)
			{
			copyTextTo(&colorListe[len], colorPtr[i].sta, _CHAR39);
			len = strlen(colorListe);
			colorListe[len++] = ' ';			
			}
		colorListe[len - 1] = NULL;			

		kat = NULL;
		(void)strcpy(sqlquery, _SEL_ALL_KAT);
		status=MPAPIdb_sqlquery(_KATEGORIE, (char **)&kat, sqlquery,
		                         &AnzCol, &dlen, &alen);
		(void)MPAPIdb_committrx();
		if ((status == (int)MPOK) && (AnzCol > 0))
			{
			colorTab = (COLORTAB *)malloc(sizeof(COLORTAB) * AnzCol);
			for (y=0; y < AnzCol; y++)
				{
				found = NOCOLOR;
				for (i=0; i < anzahl; i++)
					{
					if (kat[y].ga == colorPtr[i].sta_id)
						{
						found = i;
						break;
						}							
					}
				colorTab[y].KAT_ID = kat[y].kat_id;
				colorTab[y].COL_IDX = found;
				}
			}
		}
	*outlen = len;
	*outcolorListe = colorListe;
	MPfree((char *)kat);
	return(status);
}
