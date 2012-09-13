/*************************************************************/
/*                                                           */
/* File:        PSCGIutil.c                                  */
/*                                                           */
/* Modul:       CGI utilities                                */
/*                                                           */
/* Description: C functions to help with CGI development     */
/*                                                           */
/* Copyright: Yafra.org    */
/*                                                           */
/*************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/cgi.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <pssys.h>
#include <stdio.h>

char PSCGIHex2char(FILE *f)
	/**************************************************/
	/*                                                */
	/*  PSCGIHex2char                                 */
	/*                                                */
	/*  reads a hex-code from a file and returns      */
	/*  the associated char code                      */
	/*                                                */
	/**************************************************/
	{
	char c, ch_ret;

	c= (char) fgetc(f);
	if (c>='A') ch_ret = (c & 0xdf) - 'A' + 10;
	else ch_ret = c - '0';
	ch_ret *= 16;
	c = (char) fgetc(f);
	if (c>='A') ch_ret += (c & 0xdf) - 'A' + 10;
	else ch_ret += c - '0';

	return ch_ret;
	}
/* end PSCGIHex2char */




char PSCGIChInterpret(FILE *f, char c, int *count)
	/**************************************************/
	/*                                                */
	/*  PSCGIChInterpret                              */
	/*                                                */
	/*  translates the input character from           */
	/*  HTTP format into ASCII code                   */
	/*                                                */
	/**************************************************/
	{
	char ch_ret;

	switch(c) {
	  case '+':
		ch_ret = ' ';
		break;
	  case '%':
		ch_ret = PSCGIHex2char(f);
		--(*count);
		--(*count);
		break;
	  default:
		ch_ret = c;
	  }
	/* endswitch */

	return ch_ret;
	}
/* end PSCGIChInterpret */



char *PSCGIreadname(FILE *f, int *count, PSmemobj *aStringObj)
	/**************************************************/
	/*                                                */
	/*  PSCGIreadname                                 */
	/*                                                */
	/*  reads a name (HTTP-format) from a file        */
	/*  and decrements a counter of characters        */
	/*                                                */
	/**************************************************/
	{
	register int j;
	char c;
    int wsize;
	char *name;
	int EndName = BOOL_FALSE;

	InitStringObj(aStringObj);
	j = 0;
	wsize = WORDSIZE;
	name = AllocString(aStringObj, wsize, 1);
	if (name == NULL) exit(1);
	
	do {
		if ((c = (char) fgetc(f)) == '=') EndName = BOOL_TRUE;
		--(*count);

		if (j==wsize)
			{
			wsize *= 2;
			name = AllocString(aStringObj, wsize, 1);
			}
		/* endif */

		name[j] = PSCGIChInterpret(f,c,count);
		j++;

	   } while (!EndName); 

	/* enddowhile */

	if (j) name[j-1] = '\0';
	
	}
/* PSCGIreadname */




void PSCGIreadvalue(FILE *f, int *count, PSmemobj *aStringObj)
	/**************************************************/
	/*                                                */
	/*  PSCGIreadvalue                                */
	/*                                                */
	/*  reads a value (HTTP-format) from a file       */
	/*  and decrements a counter of characters   	  */
	/*                                                */
	/**************************************************/
    {
	register int j;
	char c;
    int wsize;
	char *value;
	int EndValue = BOOL_FALSE;

	InitStringObj(aStringObj);

	if (( !feof(f) && (*count)))
	   {
	   j=0;
	   wsize = WORDSIZE;
	   value = AllocString(aStringObj, wsize, 1);
	   if (value == NULL) exit(1);

	   do {
		if ((c = (char) fgetc(f)) == '&') EndValue = BOOL_TRUE;
		--(*count);

		if (j==wsize)
			{
			wsize *= 2;
			value = AllocString(aStringObj, wsize, 1);
			}
		/* endif */

		value[j] = PSCGIChInterpret(f,c,count);
		j++;

	      } while ((!EndValue) && (!feof(f)) && (*count));

	   /* enddowhile */

	   if ( j && (value[j-1] == '&')) value[j-1] = '\0';
	   else value[j] = '\0';

	   }
	else value = NULL;
	/* endif */

}
/* PSCGIreadvalue */


void PSCGIcheckenv(PSreqmethod aRequestMethod)
{
	/*----------------------------------------------*/
	/* PSCGIcheckenv - check environment for errors */
	/*----------------------------------------------*/
	
	switch(aRequestMethod)
	{
		case PSPOSTMETHOD:
			if (strcmp(getenv("REQUEST_METHOD"),"POST"))
				{
				printf("This script should be referenced with a METHOD of POST.\n");
				printf("If you don't understand this, see this ");
				printf("forms overview.\n");
				exit(1);
				}

			if (strcmp(getenv("CONTENT_TYPE"),"application/x-www-form-urlencoded"))
				{
				printf("This script can only be used to decode form results. \n");
				exit(1);
				}
			break;
		case PSGETMETHOD:
			printf("Get method utilities not yet implemented.\n");
			exit(1);
		default:
			printf("Request method not recognized\n");
			exit(1);		
	} /* switch */	
	
} /* PSCGIcheckenv */

PSCGIentry *PSCGIgetentries(PSmemobj *aEntriesObj, int *NumEntries)
{
	/*----------------------------------------------*/
	/* PSCGIgetentries   - read entries from stdin  */
	/* aEntriesObj       - memory object to manage  */
	/*                     memory space for entries */
	/* NumEntries        - pointer to number of     */
	/*                     entries                  */
	/*----------------------------------------------*/
	
	int cl;
	int EntriesSize = START_ENTRIES;
	PSCGIentry *entries;
	
	/* give memory for entries and check it */
	
	entries = AllocEntries(aEntriesObj,EntriesSize,START_ENTRIES);
	if (entries == NULL) exit(1);
			
	cl = atoi(getenv("CONTENT_LENGTH"));	/* cl is the length of the input (HTTP text) */
	(*NumEntries) = 0;    				

	while (cl && (!feof(stdin))) {
		/* check the memory allocated for entries and allocate more if necesary */
		if ((*NumEntries)==EntriesSize)
			{
			EntriesSize += START_ENTRIES;
			entries = AllocEntries(aEntriesObj,EntriesSize,START_ENTRIES);
			} /* endif */

		/* read name from stdin */
		PSCGIreadname(stdin,&cl,&entries[(*NumEntries)].nameobj);
		
		/* read value from stdin */
		PSCGIreadvalue(stdin,&cl,&entries[(*NumEntries)].valobj);

		(*NumEntries)++;
		}
	/* endwhile */
	
	(*NumEntries)--;
	
	return(entries);
	
} /* PSCGIgetentries */


char *PSCGIentrystring(PSCGIentry *entries, char *name, int NumEntries)
{
	/*----------------------------------------------------------*/
	/* EntryString - get string value                           */
	/* entries     - entry list                                 */
	/* name        - we want to know the string value           */
	/*               associated to name                         */
	/* NumEntries  - number of entries in the list              */
	/*----------------------------------------------------------*/
	
	register int i;

	for (i=0; strcmp(name, entries[i].nameobj.buffer) && i<=NumEntries; i++) ;
	if (i>NumEntries) return(NULL); /* name not found */
	else return(entries[i].valobj.buffer);

} /* PSCGIentrystring */


long PSCGIentrylong(PSCGIentry *entries, char *name, int NumEntries)
{
	/*----------------------------------------------------------*/
	/* PSCGIentrylong - get long value                          */
	/* entries        - entry list                              */
	/* name           - we want to know the long value          */
	/*                  associated to name                      */
	/* NumEntries     - number of entries in the list           */
	/*----------------------------------------------------------*/

	register int i;

	for (i=0; strcmp(name, entries[i].nameobj.buffer) && i<=NumEntries; i++);
	if (i>NumEntries) return(0); /* name not found */
	else return(atol(entries[i].valobj.buffer));

} /* PSCGIentrylong */


double PSCGIentrydouble(PSCGIentry *entries, char *name, int NumEntries)
{
	/*----------------------------------------------------------*/
	/* PSCGIentrydouble - get double value                      */
	/* entries          - entry list                            */
	/* name             - we want to know the double value      */
	/*                    associated to name                    */
	/* NumEntries       - number of entries in the list         */
	/*----------------------------------------------------------*/

	register int i;

	for (i=0; strcmp(name, entries[i].nameobj.buffer) && i<=NumEntries; i++)
		;

	if (i>NumEntries)
		return((double)0); /* name not found */
	else
		return(atof(entries[i].valobj.buffer));

} /* PSCGIentrydouble */


void PSCGIfreeEntries(PSmemobj *aEntriesObj, int NumEntries)
{
	/*------------------------------------------*/
	/* PSCGIfreeEntries - free allocated space  */
	/*------------------------------------------*/

	register int i;
	PSCGIentry *entries;

	entries = (PSCGIentry *)aEntriesObj->buffer;

	for(i=0; i <= NumEntries; i++)
	{
		PSSYSfreeobj(&entries[i].nameobj);
		PSSYSfreeobj(&entries[i].valobj);
	}
	PSSYSfreeobj(aEntriesObj);
		
} /* PSCGIfreeEntries */


void PSCGImimeheader(char *aMimeType)
{
	/*----------------------------------------------------*/
	/* PSCGImimeheader - write mime heading in stdout     */
	/* aMimeType       - mime type to write               */
	/*----------------------------------------------------*/
	int cret;
	
	cret = printf("Content-type: %s\n\n",aMimeType);
	cret = fflush(stdout);
	
} /* MimeHeader */ 


PSCGIentry *PSCGIinitpost(PSmemobj *aEntriesObj, int *NumEntries)
{
	/*----------------------------------------------*/
	/* PSCGIinitpost - call procedures to handle    */
	/*                 post method                  */
	/* aEntriesObj   - memory object to manage      */
	/*                 memory space for entries     */
	/* NumEntries    - pointer to number of entries */
	/*----------------------------------------------*/

	PSCGImimeheader("text/html");
	InitStringObj(aEntriesObj);
	PSCGIcheckenv(PSPOSTMETHOD);
	return(PSCGIgetentries(aEntriesObj,NumEntries));
}



/*************************************************************/
/*                                                           */
/* File:        PStypealloc.c                                */
/*                                                           */
/* Modul:		PSallocobj utilities                         */
/*                                                           */
/* Description: Memory allocation with types                 */
/*                                                           */
/* Copyright: Yafra.org    */
/*                                                           */
/*************************************************************/
void InitStringObj(PSmemobj *aStringObj)
{
	/*-----------------------------------------------*/
	/* InitStringObj - Initialize the string object  */
	/*-----------------------------------------------*/

	aStringObj->buffer = NULL;
	aStringObj->datalen = 0;
	aStringObj->alloclen = 0;
	
} /* InitStringObj */

void InitEntriesObj(PSmemobj *aEntriesObj)
{
	/*------------------------------------------------*/
	/* InitEntriesObj - Initialize the entries object */
	/*------------------------------------------------*/

	aEntriesObj->buffer = NULL;
	aEntriesObj->datalen = 0;
	aEntriesObj->alloclen = 0;
	
} /* InitEntriesObj */

char *AllocString(PSmemobj *aStringObj, unsigned int aLength, int memchunk)
{
	/*-----------------------------------------------*/
	/* AllocString - Allocates memory for a string   */
	/*               using PSSYSallocobj             */
	/* aStringObj  - String object                   */
	/* aLength     - Number of caracters to allocate */
	/* memchunk    - size of memory chunk            */
	/*-----------------------------------------------*/
	
	aStringObj->datalen = aLength*sizeof(char);
	return((char *)(aStringObj->buffer=PSSYSallocobj(aStringObj, memchunk)));
	
} /* AllocString */

PSCGIentry *AllocEntries(PSmemobj *aEntriesObj, int aLength, int memchunk)
{
	/*-----------------------------------------------*/
	/* AllocEntries - Allocates memory for a group   */
	/*                of entries using PSSYSallocobj */
	/* aEntriesObj  - Group of entries object        */
	/* aLength      - Number of entries to allocate  */
	/* memchunk     - Size of memory chunk           */
	/*-----------------------------------------------*/

	aEntriesObj->datalen = aLength*sizeof(PSCGIentry);
	return((PSCGIentry *)(aEntriesObj->buffer=PSSYSallocobj(aEntriesObj, memchunk)));
	
} /* AllocEntry */

