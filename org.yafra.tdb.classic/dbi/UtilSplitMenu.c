/*D***********************************************************
 * Modul:     API - utilities                           
 *            split a whole buffer in parts
 *            splitpoint is given by separator
 *            buffer must be terminated by NULL
 *
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpprodbi.h>		/* Prototypes f�r ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/dbi/UtilSplitMenu.c,v 1.2 2008-11-02 19:55:34 mwn Exp $";

/* wrap old function to new API function */
char *UtilSplitBuffer(char *buffer, int *anzahl, char separator)
{
	char *retptr;
	retptr = MPAPIbufferSplit(buffer, anzahl, separator);
	return(retptr);
}

/*F***********************************************************
 * Function:  split menubuffer from GUI into field buffers for DBI
 * In:        char *buffer    the source buffer from the GUI
 *            char *tobuffers the target buffer for splitting
 *            char separator  the separator char to split for
 * In/Out:    int  status     the state of the trx
 * Return:    _UNDEF  if error
 *            NULL    if no separator in source buffer
 *            count   how many split buffers
 **************************************************************/
int UtilSplitMenubuffer(char *buffer, char *tobuffers[], char separator)
{
	char *ptr;
	char message[RECLAENGE];
	int entry=(int)0;
	int status=(int)MPOK;
	int len;
	int parts;
	unsigned long alen, dlen;

	/* init */
	(void)memset((void *)tobuffers, NULL, (int)MAX_MENU_ITEMS*(int)sizeof(char *));

	/* check if MENUNR is not GLOBAL MENU */
	if (MENUNR == (unsigned char)_GLOBALMENU)
		return((int)MPOK);

	/* get number of fields */
	parts = MPgetSection(buffer, &len, (char)_MPSYMB_CR);
	buffer = buffer + (len+_MPSYMBLEN);

	/* convert special chars */
	buffer = ConvertSpecialChar(buffer, separator);
	len = strlen(buffer);

	/* alloc new buffers */
	alen = 0;
	dlen = (unsigned long)_RECORDLEN;
	tobuffers[entry] = NULL;
	ptr = tobuffers[entry] = (char *)MPalloc((void *)tobuffers[entry], &alen,
	                         (long)_RECORDLEN, dlen, sizeof(char));
	while ( *buffer != NULL )
		{
		if (*buffer == (char)_MPSYMB_TAB)
			{
/*
 *			---------------------------------------------
 *			Tabulator als Trennsymbol des Buffers erkannt
 *			Teilbuffer mit NULL-char beenden.
 *			Einen neuen Characterbuffer allocieren
 *			---------------------------------------------
 */
			*ptr = NULL;
			entry++;
			alen = 0;
			dlen = (unsigned long)_RECORDLEN;
			tobuffers[entry] = NULL;
			ptr = tobuffers[entry] = (char *)MPalloc((void *)tobuffers[entry], &alen,
			                         (long)_RECORDLEN, dlen, sizeof(char));
			}
		else
			*ptr++ = *buffer;

		buffer++;
		}

	if ( parts != entry )
		status = (int)MPERROR;

	return(status);
}

void UtilSplitFreeMenubuffer(char *tobuffers[])
{
	int i;

	for (i=0; i<MAX_MENU_ITEMS; i++)
		{		
		if (tobuffers[i] != NULL)
			{
			MPfree((void *)tobuffers[i]);
			tobuffers[i] = NULL;            /* init pointer to NULL for reuse */
			}
		}

	return;
}
