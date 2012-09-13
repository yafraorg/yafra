/*D***********************************************************
 * Module:		telfax.c
 * 				telex, telefax transmission
 *                                                            
 * Functions:	ACTtelfax()                                                            
 *                                                            
 *                                                            
 * Copyright: Yafra.org     
 *************************************************************/
/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/fax_uniplex.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#ifdef UNIPLEX_NIEMEHR

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>

/*--- Public interface with library -------------*/
#include <pssercom.h>

#define IFDEBUG  if (debug>0)


/*G--------------------- GLOBALS -----------------------------------------*/
FAXCONFIG  faxconfig;

/*F**************************************************************************
 *  Function:	faxUniplex ()
 *					fax utility program for Boll + Reich Uniplex soft
 *					build fax command
 *					send file to queue and delete it					
 *					
 *  In:			-filename, fax/tlxNr, device, delay , debug
 *  out:			-
 *  Return:		-completion code 
 ***************************************************************************-
 */
int fax_Uniplex(char *filename, char *phoneNr, int device, int delay, int debug)
{
	int		status,  res;
	char		command[_stringMax_];
	char		cmd[_stringMax_];
	char		faxOrder[_stringMax_];
	char		host[_stringMax_];
	uid_t		userid;							/* user id handling */
	struct	passwd *userpasswd;
	char		*faxUser;


	/*--- Ignore signal -------*/
/*	signal(SIGCLD, SIG_IGN); */

	/*-------------------- prepare fax command -----------------------------*/
	userid = getuid();
	userpasswd	= getpwuid(userid);
	faxUser		= userpasswd->pw_name ;			/* used for mail */	
 
	/*--- Telefax or telex ---*/
	if ( device == _DEVFAX )
		(void)sprintf(faxOrder, "%s/bin/ufax", faxconfig.path ); 
	if ( device == _DEVTELEX )
		(void)sprintf(faxOrder, "%s/bin/utelex", faxconfig.path ); 

	/*--- check cur host vs. fax host (case sensitive) ----*/
	gethostname ( host, _stringMax_); 
	res = strncmp(host, faxconfig.node, strlen(host) ); 
/*	IFDEBUG printf("faxUniplex> host, compare: %s   %d \n", host, res);    */
	if (res == 0 )
	{
		/*--- Local execution print or send --------------------------*/
		if (debug > 0)  
			(void)sprintf(command, "sh %s -u%s +x %s",
											faxOrder, faxUser,  filename );	/*Print*/	
		else
			(void)sprintf(command, "sh %s -u%s +x%s %s",
											faxOrder, faxUser, phoneNr, filename );	
		/*--- execute fax command -----*/
		status = system(command);
		if (status == -1 )
         {
            if (errno == ECHILD )
 					/*--- reset status ------*/
					status = _noError_;
				else
					printf("System Error %d: %s \n", errno, strerror(errno) ); 
			}
		if (status != _noError_)
			return (_error_); 
	}
	else
	{
		/*--- Remote copy and execution -------------------------------*/
		(void)sprintf(cmd, "rcp %s %s:%s", filename, faxconfig.node, filename );	
IFDEBUG printf("faxUniplex> %s \n", cmd);         
		status = system(cmd);
		if (status == -1 )
         {
            if (errno == ECHILD )
 					/*--- reset status ------*/
					status = _noError_;
				else
					printf("System Error %d: %s \n", errno, strerror(errno) ); 
			}
		if (status != _noError_)
			return (_error_); 
		/*--- remote execution --------------*/
		if (debug > 0)  
			(void)sprintf(command, "remsh %s %s -u%s +x %s",
									faxconfig.node, faxOrder, faxUser, filename ); /*Print ! */
		else
			(void)sprintf(command, "remsh %s %s -u%s +x%s %s",
								faxconfig.node, faxOrder, faxUser, phoneNr, filename );	
		/*--- execute fax command -----*/
		status = system(command);
		if (status == -1 )
         {
            if (errno == ECHILD )
 					/* reset status */
					status = _noError_;
				else
					printf("System Error %d: %s \n", errno, strerror(errno) ); 
			}
		if (status != _noError_)
			return (_error_); 
	}

/* IFDEBUG fprintf(stderr, "faxUniplex> %s \n", command);   */

#ifdef COMPILE
	/*--- remove local file -----------------*/
	(void)sprintf(cmd, "rm %s", filename );	
	status = system(cmd);
	IFDEBUG printf("faxUniplex> %s \n", cmd); 
#endif

	return(status);
}

#endif
