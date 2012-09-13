/*D***********************************************************
 * Name:      AKTdevice.c
 * Modul:     AKT base moduls
 *            Handle all device re-routing processes
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/act/lib/AKTdevice.c,v 1.2 2008-11-02 19:55:49 mwn Exp $";

/* MarcoPolo Standard Action include */
#include <mpact.h>

#include <fcntl.h>
#include <pssercom.h>

/*P--- PROTOTYPES --------------------------------------------------------*/
static int     AKTdevicePrintCtrlWenger   ( FILE *FPoutbuf, int sequence );
static int     AKTdevicePrintCtrlLaserJet ( FILE *FPoutbuf, int sequence );
static void		AKTcompactDigitString      ( char *aString );
static int		AKTfilecat                 ( char *targetFile, char *sourceFile );

#ifdef ps_win
#define _FAX_TMP_DIR		"\\TEMP"
#define _ACT_TMPFILE    "OUT_XXXXXX"
#else
#define _FAX_TMP_DIR		"/tmp"
#define _ACT_TMPFILE    "/tmp/OUT_XXXXXX"
#endif

char global_filename[128];

#define _HUNK_MAX			1024


/*--- TEXT ids for language independend text -------------------------------*/
#define AKTCOM_EDITOR				16
#define AKTCOM_EDITOR_HOST			17
#define AKTCOM_OUTFILE				18


/*============================================================================
 * Fax/Telex strategy: 
 *		all actions write to temporary default file FPout
 * 	- screen and printer output: this file is used 
 *		- fax/telex immediate: this file is used
 *		- fax/telex spooled:   this file is appended to the callnumber file 
 *                             whose name is given by action
 *============================================================================
 */


/*F************************************************************
 * Function:  AKTdeviceInit
 *            initialize struct with whatever is known from parameters
 * 
 * in:        device_id as given in options parameters
 * out:
 * return:    success code
 **************************************************************/
int AKTdeviceInit(int device, int spool)
{
	extern int DebugFlag;
	extern DEVICE_PORT	devicePort;
	extern FILE		*FPout;

	DEVICE_PORT	*pDev;
	char			*pFilename;
	char			tmpfilename[_RECORDLEN];
	int			status;

	/*--- general inits ------------*/
	pDev = &devicePort;
	pDev->type          = device; 
	pDev->direction     = _DEV_OUTPUT ;
	pDev->delay         = spool;
	pDev->recipient[0]  = '\0';	    		/* recipient  */
	pDev->faxnumber[0]  = '\0' ;
	pDev->callnumber[0] = '\0' ;
	pDev->command[0]    = '\0' ;
	pDev->command2[0]    = '\0' ;
	pDev->command3[0]    = '\0' ;
	pDev->command4[0]    = '\0' ;

	/*--- specific inits -----------*/
	status = MPOK;
	switch(device)
		{
		case _DEVPRINTER:
		case _DEVPRINTER2:
		case _DEVPRINTER3:
		case _DEVPRINTER4:
		case _DEVMODEM:
		case _DEVFILE:
		case _DEVFAX:	
		case _DEVTELEX:
		case _DEVSCREEN:
			(void)strcpy(tmpfilename, _ACT_TMPFILE);
			pFilename = mktemp(tmpfilename);
			if (pFilename == NULL)
				return(MPERROR);
#ifdef ps_win
			(void)sprintf(pDev->filename, "\\TEMP\\%s.txt", pFilename);
			(void)sprintf(pDev->unparsed_filename, "\\\\TEMP\\\\%s.txt", pFilename);
#else
			(void)strcpy(pDev->filename, pFilename);
			(void)strcpy(pDev->unparsed_filename, pFilename);
#endif
			FPout = fopen( pDev->filename, _P_WRITE_);
			if (FPout == NULL)
				{
				perror("Aktionsoutputdatei konnte nicht ge�ffnet werden");
				status = MPERROR;
				}

			/**** DEBUG *****/
			if (DebugFlag)
				(void)fprintf(stderr, "debug: Aktionen Outputfile: %s%s", pFilename, _P_EOL_);
			/**** DEBUG *****/
			break;

		default:
			pDev->filename[0] = '\0' ;
			FPout = stdout;
			break;
		}
	return(status);
}



/*F************************************************************
 * Function:  AKTdeviceOuput
 *            write the header of mail text 
 *
 **************************************************************/
int AKTdeviceOuput(void)
{
	int cret;
	cret = AKTdeviceOutput();
	return(cret);
}

int AKTdeviceOutput(void)
{
	extern DEVICE_PORT	devicePort;
	extern FILE		*FPout;
	extern char		guiHostname[] ;
	extern int		DebugFlag ;

	char		filename[_TEXTLEN], filenametemp[_TEXTLEN];
	char		callnr[_TEXTLEN]; 
	char     format[_RECORDLEN];
	char		cmd_buffer[_RECORDLEN];
	int		status, devtype, faxl;
	int		nbtext ;                             /* number of DB texts found */
	DEVICE_PORT	*pDev;

	int cretisguihost;
	char *isremotedisplay;


	/*--- inits ---------------------*/
	status = MPOK;
	pDev = &devicePort;
	devtype = pDev->type;
	*cmd_buffer = (char)NULL;

	/*--- Close general out file ----*/
	fclose(FPout);

	/*------------- OUTPUT is f(type) ---------------------------------------*/
	switch (devtype)
	{
		case _DEVFAX:         /*--- FAX --------------------------------------*/
			/*--- test if fax can be sent --------*/
			faxl = strlen (pDev->faxnumber);
			if (faxl < 1)
				AKTmsg(ACT_OSERROR, (int)_UNDEF, "Keine Fax Nummer vorhanden !");
				break; 

			/*--- create a file path -------------*/
			AKTcompactDigitString( pDev->faxnumber);
			strcpy( callnr, pDev->faxnumber);

			/*--- Spooled ------------------------*/
			if (pDev->delay == _AKT_AUTOSPOOL)
				{
				/*--- cat output file to fax file --*/
#ifdef ps_win
				(void)sprintf( filename, "%s\\FAX%s", _FAX_TMP_DIR, callnr);
#else
				(void)sprintf( filename, "%s/FAX%s", _FAX_TMP_DIR, callnr);
#endif
				status = AKTfilecat( filename, pDev->filename);
				if (status == MPERROR)
					{
					AKTmsg(ACT_OSERROR, (int)_UNDEF, "Fax/tlx Datei kann nicht geoeffnet werden");
					break; 
					}
				}
			else /*-- immediate ------------------*/
				{
				/*--- preponed ImmFax to standard file name -----*/
				(void)sprintf( filenametemp, "ImmFax%s", callnr);
#ifdef ps_win
				(void)sprintf( filename, "%s\\%s", _FAX_TMP_DIR, filenametemp);
#else
				(void)sprintf( filename, "%s/%s", _FAX_TMP_DIR, filenametemp);
#endif
				status = rename (pDev->filename, filename);       /*rename(old,new) */
				if (status == MPERROR)
					{
					AKTmsg(ACT_OSERROR, (int)_UNDEF, "Fax/tlx Datei kann nicht veraendert werden");
					break; 
					}
				status = PSSERCOM_fax(filename, callnr, devtype, (int)_FAX_NOW, 0);
				if (status != MPOK)
					AKTmsg(ACT_ERROR, (int)_UNDEF, "Fehler bei FAX/TLX uebermitteln");
				}
				strcpy( pDev->filename, filename);             /* to keep trace */
			break; 


		case _DEVTELEX:          /*--- Telex -------------------------------*/
			break;

		case _DEVMODEM:          /*--- Modem -------------------------------*/
			break;


		case _DEVFILE:           /*--- File --------------------------------*/
			break;


		case _DEVPRINTER:        /*--- Printer 1 ---------------------------*/
			if (*pDev->command == (char)NULL )
			{
				AKTmsg(ACT_OSERROR, (int)_UNDEF, "Kein Print Befehl vorhanden");
				break; 
			}
			(void)sprintf( cmd_buffer, "%s %s &", pDev->command, pDev->unparsed_filename);
			status = PSSYSexecute( cmd_buffer); 
			break;

		case _DEVPRINTER2:       /*--- Printer 2 ---------------------------*/
			if (*pDev->command2 == (char)NULL )
			{
				AKTmsg(ACT_OSERROR, (int)_UNDEF, "Kein Print Befehl 2 vorhanden");
				break; 
			}
			(void)sprintf( cmd_buffer, "%s %s &", pDev->command2, pDev->unparsed_filename);
			status = PSSYSexecute( cmd_buffer); 
			break;

		case _DEVPRINTER3:       /*--- Printer 3 ---------------------------*/
			if (*pDev->command3 == (char)NULL )
			{
				AKTmsg(ACT_OSERROR, (int)_UNDEF, "Kein Print Befehl 3 vorhanden");
				break; 
			}
			(void)sprintf( cmd_buffer, "%s %s &", pDev->command3, pDev->unparsed_filename);
			status = PSSYSexecute( cmd_buffer); 
			break;

		case _DEVPRINTER4:       /*--- Printer 4 ---------------------------*/
			if (*pDev->command4 == (char)NULL )
			{
				AKTmsg(ACT_OSERROR, (int)_UNDEF, "Kein Print Befehl 4 vorhanden");
				break; 
			}
			(void)sprintf( cmd_buffer, "%s %s &", pDev->command4, pDev->unparsed_filename);
			status = PSSYSexecute( cmd_buffer); 
			break;


		case _DEVSCREEN:        /*--- Screen on Host -----------------------*/
			/*--- Get editor name and command format for Host --*/
			cretisguihost = strlen(guiHostname);
			isremotedisplay = getenv( "MAPOREMOTEDISPLAY" );
			if (isremotedisplay != NULL)
				{
				nbtext = AKTobjtxt((int)_COMMON_TYP, (int)AKTCOM_EDITOR_HOST, format, NOMARGIN);
				if ( nbtext <= (int)0 )
					AKTmsg(ACT_OSERROR, (int)_UNDEF, "Device: Kein Editor Befehl vorhanden");
				else
					(void)sprintf( cmd_buffer, format, pDev->unparsed_filename, guiHostname );
				}
			else
				{
				nbtext = AKTobjtxt((int)_COMMON_TYP, (int)AKTCOM_EDITOR, format, NOMARGIN);
				if ( nbtext <= (int)0 )
					AKTmsg(ACT_OSERROR, (int)_UNDEF, "Device: Kein Editor Befehl vorhanden");
				else
					(void)sprintf( cmd_buffer, format, pDev->unparsed_filename );
				}
			/*--- EXECUTE --*/
			status = PSSYSexecute( cmd_buffer); 
			break;


		default:
			break;

	} 

	return(status);
}

/*F************************************************************
 * Function:  AKTdevicePrintCtrl
 *            Check the printer model from device and 
 *            Print the special Char
 * 
 * in:        FILE* FPoutbuf, special char define number
 * out:
 * return:    success code
 **************************************************************/
int AKTdevicePrintCtrl( FILE *FPoutbuf, int sequence )
{
	extern int DebugFlag;
	extern int GlobalPrinterMode;
	extern DEVICE_PORT	devicePort;
	extern FILE		*FPout;

	int			status;

	/*--- inits ---------------------*/
	status = MPOK;

#ifdef _NO_MORE_DEVICE_PRINTING
	switch ( GlobalPrinterMode )
	{
		case _DEV_EPSON_MODE:
			status = AKTdevicePrintCtrlWenger( FPoutbuf, sequence );
			break;
		case _DEV_LASERJET:
			status = AKTdevicePrintCtrlLaserJet( FPoutbuf, sequence );
			break;
	}
#endif
	return(status);
}


/*F************************************************************
 * Function:  AKTdevicePrintCtrlWenger
 *            Print the special Char in Wenger Epson-mode
 * 
 * in:        FILE* FPoutbuf, special char define number
 * out:
 * return:    success code
 **************************************************************/
static int AKTdevicePrintCtrlWenger( FILE *FPoutbuf, int sequence )
{
	extern int DebugFlag;
	extern DEVICE_PORT	devicePort;
	extern FILE		*FPout;

	int			status;

	/*--- inits ---------------------*/
	status = MPOK;

	switch(sequence)
	{
		case _DEV_RESET_PRINTER :
			fprintf( FPoutbuf, "%s", "\033@" );
			break;
		case _DEV_NORMAL_PITCH :
			fprintf( FPoutbuf, "%s", "\033P" );
			break;
		case _DEV_COMPRESSED_ON :
			fprintf( FPoutbuf, "%s", "\033\017" );
			break;
		case _DEV_COMPRESSED_OFF :
			fprintf( FPoutbuf, "%c", 0x12 );
			break;
		case _DEV_ENLARGED_ON :
			fprintf( FPoutbuf, "%s", "\033\016" );
			break;
		case _DEV_ENLARGED_OFF :
			fprintf( FPoutbuf, "%s", "\022" );
			break;
		case _DEV_PITCH_10 :
			fprintf( FPoutbuf, "%s", "\033P" );
			break;
		case _DEV_PITCH_12 :
			fprintf( FPoutbuf, "%s", "\033M" );
			break;
		case _DEV_ITALIC_ON :
			fprintf( FPoutbuf, "%s", "\0334" );
			break;
		case _DEV_ITALIC_OFF :
			fprintf( FPoutbuf, "%s", "\0335" );
			break;
		case _DEV_LETTER_ON :
			fprintf( FPoutbuf, "%s", "\033x\001" );
			break;
		case _DEV_LETTER_OFF :
			fprintf( FPoutbuf, "%s%c", "\033x", NULL );
			break;
		case _DEV_BOLD_ON :
			fprintf( FPoutbuf, "%s", "\033G" );
			break;
		case _DEV_BOLD_OFF :
			fprintf( FPoutbuf, "%s", "\033H" );
			break;
		case _DEV_UNDERLINE_ON :
			fprintf( FPoutbuf, "%s", "\033-\001" );
			break;
		case _DEV_UNDERLINE_OFF :
			fprintf( FPoutbuf, "%s%c", "\033-", NULL );
			break;
		case _DEV_DOUBLE_HIGH_ON :
			fprintf( FPoutbuf, "%s", "\033u" );
			break;
		case _DEV_DOUBLE_HIGH_OFF :
			fprintf( FPoutbuf, "%s", "\033v" );
			break;
		case _DEV_SUBSCRIPT_ON :
			fprintf( FPoutbuf, "%s", "\033S\001" );
			break;
		case _DEV_SUBSCRIPT_OFF :
			fprintf( FPoutbuf, "%s", "\033T" );
			break;
		case _DEV_SUPERSCRIPT_ON :
			fprintf( FPoutbuf, "%s%c", "\033S", NULL );
			break;
		case _DEV_SUPERSCRIPT_OFF :
			fprintf( FPoutbuf, "%s", "\033T" );
			break;
		case _DEV_LANDSCAPE :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_PORTRAIT :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_BELL :
			fprintf( FPoutbuf, "%s", "\007" );
			break;
		default:
			break;
	}
	return( status );	
}

/*F************************************************************
 * Function:  AKTdevicePrintCtrlLaserJet
 *            Print the special Char in LaserJet-mode
 * 
 * in:        FILE* FPoutbuf, special char define number
 * out:
 * return:    success code
 **************************************************************/
static int AKTdevicePrintCtrlLaserJet( FILE *FPoutbuf, int sequence )
{
	extern int DebugFlag;
	extern DEVICE_PORT	devicePort;
	extern FILE		*FPout;

	int			status;

	/*--- inits ---------------------*/
	status = MPOK;

	switch(sequence)
	{
		case _DEV_RESET_PRINTER :
			fprintf( FPoutbuf, "%s", "\033E" );
			break;
		case _DEV_NORMAL_PITCH :
			fprintf( FPoutbuf, "%s", "\033(s10H" );
			break;
		case _DEV_COMPRESSED_ON :
			fprintf( FPoutbuf, "%s", "\033&k2S" );
			break;
		case _DEV_COMPRESSED_OFF :
			fprintf( FPoutbuf, "%s", "\033&k0S" );
			break;
		case _DEV_ENLARGED_ON :
			fprintf( FPoutbuf, "%s", "\033&k3S" );
			break;
		case _DEV_ENLARGED_OFF :
			fprintf( FPoutbuf, "%s", "\033&k0S" );
			break;
		case _DEV_PITCH_10 :
			fprintf( FPoutbuf, "%s", "\033(s10H" );
			break;
		case _DEV_PITCH_12 :
			fprintf( FPoutbuf, "%s", "\033(s12H" );
			break;
		case _DEV_ITALIC_ON :
			fprintf( FPoutbuf, "%s", "\033(s1S" );
			break;
		case _DEV_ITALIC_OFF :
			fprintf( FPoutbuf, "%s", "\033(s0S" );
			break;
		case _DEV_LETTER_ON :
			fprintf( FPoutbuf, "%s", "\033(s2Q" );
			break;
		case _DEV_LETTER_OFF :
			fprintf( FPoutbuf, "%s", "\033(s0Q" );
			break;
		case _DEV_BOLD_ON :
			fprintf( FPoutbuf, "%s", "\033(s1B" );
			break;
		case _DEV_BOLD_OFF :
			fprintf( FPoutbuf, "%s", "\033(s0B" );
			break;
		case _DEV_UNDERLINE_ON :
			fprintf( FPoutbuf, "%s", "\033&d0D" );
			break;
		case _DEV_UNDERLINE_OFF :
			fprintf( FPoutbuf, "%s", "\033&d@" );
			break;
		case _DEV_DOUBLE_HIGH_ON :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_DOUBLE_HIGH_OFF :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_SUBSCRIPT_ON :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_SUBSCRIPT_OFF :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_SUPERSCRIPT_ON :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_SUPERSCRIPT_OFF :
			fprintf( FPoutbuf, "%s", "" );
			break;
		case _DEV_LANDSCAPE :
			fprintf( FPoutbuf, "%s", "\033&l1O" );
			break;
		case _DEV_PORTRAIT :
			fprintf( FPoutbuf, "%s", "\033&l0O" );
			break;
		case _DEV_BELL :
			fprintf( FPoutbuf, "%s", "\007" );
			break;
		default:
			break;
	}
	return( status );	
}



#ifdef COMPILE
/*F--------------------------------------------------------------------------
 *  Function: AKTfilecat ()
 *            low level i/o functions for BIG files 
 *            append the source file at end of target file 
 *            
 *  In:       -file names 
 *  out:      -
 *  Return:   -success code 
 *---------------------------------------------------------------------------
 */
static int  AKTfilecat( char *targetFile, char *sourceFile)
{
	int		FDtarget;
	int		FDsource;
	char		*bigbuf; 
	struct stat sourceStat; 
	size_t	hunk;                  /*nb of bytes for one transfer */
	size_t	left;                  /*nb of bytes left to transfer */
	int		nbsource, nbtarget;
	int		status = MPOK;

	/*--- Check source file -------------*/
	if (stat(sourceFile, &sourceStat) != 0 )
		return( MPERROR );                           /* >>>>> exit */            

	/*--- set hunk size -----------------*/
	left = hunk = sourceStat.st_size;       /* at start all is left */
	if (hunk > _HUNK_MAX) 
		hunk = _HUNK_MAX; 

	/*--- alloc a hunk ------------------*/
	if ((bigbuf = (char *)malloc(hunk)) == NULL)
		return( MPERROR );                           /* >>>>> exit */

	/*--- open files --------------------*/
	FDsource = open(sourceFile, O_RDONLY);
	if (FDsource == -1)
		return( MPERROR );                           /* >>>>> exit */
	FDtarget = open(targetFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (FDtarget == -1)
		return( MPERROR );                           /* >>>>> exit */

	/*--- concatenate -------------------*/
	while (left > 0)
		{
		nbsource = read( FDsource, bigbuf, hunk) ;
		if (nbsource != hunk)
			{
			close(FDsource);
			return( MPERROR );                           /* >>>>> exit */
			}
		nbtarget = write(FDtarget, bigbuf, hunk) ;
		if (nbtarget != hunk)
			{
			close(FDtarget);
			return( MPERROR );                           /* >>>>> exit */
			}
		left -= hunk;
		if (left < hunk) 
			hunk = left; 
		}

	if (close(FDsource) != 0) 
			return( MPERROR );                           /* >>>>> exit */
	if (close(FDtarget) != 0) 
			return( MPERROR );                           /* >>>>> exit */

	return( MPOK );
}
#endif


/*F--------------------------------------------------------------------------
 *  Function: AKTfilecat ()
 *            append the source file at end of target file 
 *            (trivial character based transfer) 
 *            
 *  In:       -file names 
 *  out:      -
 *  Return:   -success code 
 *---------------------------------------------------------------------------
 */
static int  AKTfilecat( char *targetFile, char *sourceFile)
{
	FILE		*FDtarget;
	FILE		*FDsource;
	char		bigbuf[1024]; 
	int		status = MPOK;

	/*--- Check source file -------------*/
	FDsource = fopen(sourceFile, _P_READ_);
	if (FDsource == NULL)
		return( MPERROR );                           /* >>>>> exit */
	FDtarget = fopen(targetFile, _P_APPEND_);
	if (FDtarget == NULL)
		return( MPERROR );                           /* >>>>> exit */

	/*--- concatenate -------------------*/
	while (fgets(bigbuf, 1024, FDsource))
		fputs(bigbuf, FDtarget);

	/*--- close -------------------------*/
	if (fclose(FDsource) != 0) 
			return( MPERROR );                           /* >>>>> exit */
	if (fclose(FDtarget) != 0) 
			return( MPERROR );                           /* >>>>> exit */

	return( MPOK );
}



/*F--------------------------------------------------------------------------
 *  Function: AKTcompactDigitString ()
 *            keep only digits, remove text in a string
 *            
 *  In:       -Ptr to string
 *  out:      -modified string
 *  Return:   -
 *---------------------------------------------------------------------------
 */
static void  AKTcompactDigitString(char *aString)
{
	int    i;
	char	*pS, *pD; 

	pS = pD = aString; 
	/*--- eliminate non digits ------------*/
	for ( i=0; (i < (int)strlen(aString)) ; i++, pS++ )
		{
		if (isdigit (*pS)) 
			*pD++ = *pS; 
		}
	/*--- terminate with null -------------*/
	*pD = '\0' ;
}

