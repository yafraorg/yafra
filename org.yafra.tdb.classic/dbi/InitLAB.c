/*D***********************************************************
 * Modul:     DBI - init
 *            read all labels from DB table LABEL
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpsqlsel.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/InitLAB.c,v 1.2 2008-11-02 19:55:36 mwn Exp $";

int InitLAB(int label_prg)
{
	extern MEMOBJ sqlmem;
	extern int sprache;
	extern int *NewLevel[];

   LABEL *lab_ptr;

	register int i;
	int anzahl;
	int status = (int)MPOK;

	char *buffer_ptr;
	char labelbez[_LABELLEN+1];
	char query[_QUERYLEN];

	size_t buffersize;

	(void)sprintf(query, _SEL_ALL_LAB, sprache);

	status = MPAPIdb_begintrx(SQLISOLATION_RU, SQLPRIO_NORMAL);
	if (status != (int)MPOK)
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		return((int)MPERROR);
		}

	status=MPAPIdb_sqlquery((int)_LABEL, &sqlmem.buffer, query,
                         &anzahl, &sqlmem.datalen, &sqlmem.alloclen);
	if ( status == (int)MPOK )
		{
		if ( anzahl > (int)0 )
			{
			lab_ptr = (LABEL *)sqlmem.buffer;
			comm.datalen = anzahl * sizeof(lab_ptr);  /* begin out buffering */
			if (comm.datalen > comm.alloclen)
				comm.buffer = (char *)MPalloc((void *)comm.buffer, &comm.alloclen,
				               DEFMEMCHUNK, comm.datalen, sizeof(char));
			for ( i=0, buffer_ptr = comm.buffer; i < anzahl; i++ )
				{
				lab_ptr = (LABEL *)&sqlmem.buffer[i*sizeof(LABEL)];
				(void)copyTextTo(labelbez, (char *)lab_ptr->label, (int)_LABELLEN);
				(void)sprintf(buffer_ptr, "%d\t%d\t%d\t%d\t%s\n", lab_ptr->label_prg,
				   lab_ptr->label_typ, lab_ptr->stufe1, lab_ptr->stufe2, labelbez);
				buffersize = strlen((char *)buffer_ptr);
				buffer_ptr += buffersize;
				}
			}
		else  /* keine labels gefunden */
			{
			UtilMsg((int)MPE_NOLABELS, MSGTYP_ERROR, NULL);
			status=(int)MPERROR;
			}
		}
	else  /* select error */
		{
		UtilMsg(status, MSGTYP_DBERROR, NULL);
		status = (int)MPERROR;
		}

	(void)MPAPIdb_committrx();

	/* Ermittle die Datenlaenge */
	comm.datalen = (long)strlen(comm.buffer);

	return(status);
}
