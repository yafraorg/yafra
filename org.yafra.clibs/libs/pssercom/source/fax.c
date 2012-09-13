/*D***********************************************************
 * Module:		faxconfig.c
 * 				telex, telefax configuration file handling
 *                                                            
 * Functions:	ACTgetfaxconfig()                                                            
 *                                                            
 *                                                            
 * Copyright: Yafra.org, Switzerland     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/fax.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

/* version handling */
#include "version.h"

#include <signal.h>
#include <errno.h> 
#include <time.h>

/*--- Public interface with library -------------*/
#include <pssercom.h>

static void fax_timeStamp(char *);
static int fax_getConfig(char *, FAXCONFIG *);

/*G--------------------- GLOBALS -----------------------------------------*/
FAXCONFIG  faxconfig;

/***************************************************************************
 *  Interface for sending files to Telex or Fax 
 *
 *  The function reads a config file "FAXCONFIG" defined in fax_def.h.
 *  Config file path can also be set in fax_def.h.				
 *  The function selects the fax/telex utility (like Boll&Reich) and sends 
 *  the file.
 *
 *  returns:	-completion code 
 *
 *  Author:    ja. Copyright: Yafra.org 
 ***************************************************************************
 */
PS_DLLAPI int PSSERCOM_fax(char *filename,  /* the file to send       */
						char *phoneNr,	 /* where to send          */
						int device,		 /* tells fax or telex     */
						int delay,		 /* immediate or spooled   */
						int debug		 /* debugging purpose      */)
{
	FILE		*FDfax, *FDconf;
	char		configfile[_stringMax_], file[_stringMax_], path[_stringMax_] ;
	int		status = 0;
	char		*tmpName;

#ifdef COMPILE
	/*--- user specific config file  ------*/
	(void)sprintf(file, ".%s", FAXCONFNAME);
	(void)sprintf(path, "%s", getenv("HOME"));
	(void)sprintf(configfile, "%s/%s", path, file);
#endif

	/*--- host based config file ----------*/
	(void)sprintf(configfile, "%s/%s", FAXCONFPATH, FAXCONFNAME);

	/*--- read config file ----------------*/
	status = fax_getConfig(configfile, &faxconfig);
	if (status != _noError_ )
		return (_error_);

	/*--- check utility -------------------*/
#ifdef ps_unix
	if ( atoi(faxconfig.utility) == _FAX_BR_UNIPLEX )
		status = fax_Hylafax(filename, phoneNr, device, delay, debug);
	if ( atoi(faxconfig.utility) ==  _FAX_MODEM )
		status = fax_Hylafax(filename, phoneNr, device, delay, debug);
#endif

	return(status);
}

/*F--------------------------------------------------------------------------
 *  Function:	ACTsetFaxConfig ()
 *					write fax configuration parameters to file 
 *					faxconfig struct is public 
 *
 *  In:			-file name
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
PS_DLLAPI int PSSERCOM_faxsetConfig(char *configfile)
{
	FILE	*fp;
	int	status = 0;
	char	paramtext[_stringMax_+1] ; 

   /*--- process whole file --------------*/
	fp = fopen(configfile, _P_WRITE_);
	if (fp)
		{
		/*???? change get procedure (pad and unpad spaces) to use fwrite !!*/
		fclose(fp);
		status = _noError_; 
		}
	else  /*-- fopen failed */
		{
		perror("\n ACTsetFaxConfig: FAX Config file konnte nicht geschriben werden\n");
		status = _error_; 
		}

	return(status); 
}




/*F--------------------------------------------------------------------------
 *  Function:	ACTgetFaxConfig ()
 *					read the fax configuration parameters snd fill struct
 *					faxconfig struct is public 
 *
 *  In:			-file name
 *  out:			-
 *  Return:		-completion code 
 *---------------------------------------------------------------------------
 */
static int fax_getConfig(char * configfile, FAXCONFIG *faxconfig)
{
	FILE	*fp;
	int	i = 0;
	int	status = 0;
	char	rec[_stringMax_], *ptr;
	char	paramtext[_stringMax_+1] ; 
   char	f1 ;

   /*--- process whole file --------------*/
	fp = fopen(configfile, _P_READ_);
	if (fp)
	{
      /*--- read all lines  --------------*/
		while (fgets(rec, sizeof(rec), fp)) 
      {
         /*-- force line termination with '\0' ---- */
			ptr = &rec[strlen(rec)-1];
			if (*ptr == '\n')  *ptr = 0;

			/*--- bail out comments and other exotic lines ----------*/
         if ( isalpha(rec[0]) )
			{
	         /*-- extract switch and text, '\0' is added! ---- */
				paramtext[0] = '\0';							/*for missing param*/			
				sscanf (rec, "%1c%*[ ]%s[^0]", &f1, paramtext ); 
				switch (f1)
				{
					case 'D': 
						strcpy (faxconfig->daemon, paramtext); 
						break; 
					case 'N': 
						strcpy (faxconfig->node, paramtext); 
						break; 
					case 'P': 
						strcpy (faxconfig->path, paramtext); 
						break; 
					case 'T': 
						strcpy (faxconfig->temp, paramtext); 
						break; 
					case 'U': 
						strcpy (faxconfig->utility, paramtext); 
						break; 
				}
			}
		}
		fclose(fp);
		status = _noError_; 
	}
	else  /*-- fopen failed */
	{
		perror("\n ACTgetConfig: FAX Config file konnte nicht ge�ffnet werden\n");
		status = _error_; 
	}
	return (status); 
}/**/



/*F--------------------------------------------------------------------------
 *  Function: ACTtimeStamp ()
 *            build a name with date and time fragments
 *					day(0-365)Hour(0-31)Min(0-59)Sec(0-59)
 *
 *  In:       - 
 *  out:      -modified string
 *  Return:   -
 *---------------------------------------------------------------------------
 */
static void fax_timeStamp(char *str )
{
	struct	tm	*ptr, *localtime(); 
	int		size; 
	time_t	time(), nseconds; 

	nseconds = time(NULL); 
	ptr = localtime(&nseconds); 
	size = strftime(str, _TIMESTAMPLEN-2, "%j%H%M%S", ptr);
}
