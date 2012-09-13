/*D***********************************************************
 * Modul:     API - utilities                           
 *            split a whole buffer in parts
 *            splitpoint is given by separator
 *            buffer must be terminated by NULL
 *
 * Copyright: yafra.org, Basel, Switzerland     
 **************************************************************/
#include <mpmain.h>
#include <mpproapi.h>		/* Prototypes fuer ANSI-C */

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/UtilSplit.c,v 1.2 2008-11-02 19:55:48 mwn Exp $";

#define MAXSPLITS  30

/*F***********************************************************
 * Function:  split buffer
 * In:        char *buffer   the source buffer
 *            char separator the separator char to split for
 * In/Out:    char **split   the destination buffer 2-D array                           
 * Return:    _UNDEF  if error
 *            NULL    if no separator in source buffer
 *            count   how many split buffers
 **************************************************************/
char *MPAPIbufferSplit(char *buffer, int *anzahl, char separator)
{
	char *ptr;
	char **split;
	char message[RECLAENGE];
	int entry=(int)0;
	int status=(int)MPOK;
	int len;
	unsigned long aktlen = 0;
	unsigned long newlen = 1;  /* dummy feld: 1 = nimm chunk size */

	split = NULL;
	*anzahl = (int)_UNDEF;

	if ((strchr(buffer, (int)separator)) == NULL)
		{
		*anzahl = (int)0;
		return((int)NULL);
		}

	/* alloc array */
	split = (char **)MPalloc((void *)split, &aktlen, (long)MAXSPLITS,
	                      newlen, sizeof(char *));
	if (split == NULL)
		return(NULL);

	/* init */
	len = strlen(buffer);

	aktlen = 0;
	split[entry] = NULL;
	ptr = split[entry] = (char *)MPalloc((void *)split[entry], &aktlen, 
	                              (long)len, newlen, sizeof(char));
	if (split[entry] == NULL)
		return(NULL);
	entry++;
	while (*buffer != NULL)
		{
		if (*buffer == separator)
			{
			*ptr = NULL;
			aktlen = 0;
			split[entry] = NULL;
			ptr = split[entry] = (char *)MPalloc((void *)split[entry], &aktlen, 
			                              (long)len, newlen, sizeof(char));
			if (split[entry] == NULL)
				return(NULL);
			entry++;
			}
		else
			*ptr++ = *buffer;

		buffer++;
		}
	*ptr = NULL;

	*anzahl = entry;
	return((char *)split);
}
