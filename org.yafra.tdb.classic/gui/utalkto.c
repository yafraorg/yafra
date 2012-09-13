/*D************************************************************ 
 * Modul:		GUI - Dialog						utalkto.c
 *                                                           
 *					talk to database daemon
 *					buffer and len are only in SEND needed !!
 *                                                           
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
#include <uinclude.h>
#include <ginclude.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/gui/utalkto.c,v 1.2 2008-11-02 19:55:46 mwn Exp $";


/*F---------------------------------------------------------------------
 *	Function:	xUItalkto 
 *					-Communication with DB 
 *					-Optimized version with glas-window cache and cursor
 *					-
 *	In:			-type Receive or Send, the buffer to send, length 
 *					-
 *-----------------------------------------------------------------------
 */
long xUItalkto( int typ, char *buffer, long len)
{
	extern Display *display;
	extern long		maxentries;
	extern char		*entries;
	extern char		databasenotok;
	extern ApplicationData app_data;
	extern int		ipcfd;

	static int	status = SEND;		/* synchronization       */
	static int	first = 0;			/* error message cut-off */
	static int	nbWidgets; 			/* remember for receive  */

	int			laenge;
	int			cret;
	Widget		aktwidget;
	Widget		wid[ANZ_MENU + 20];
	unsigned long readno;

	/*----- check database -----------*/
	if (databasenotok)
		{
		COMMSTAT = MESSAGEOK;
		if (first == 0)
			{
			xUIfehler(XUINOCOMM, 0);
			first=1;
			}
		return(0);
		}
	/*!! XFlush(display); */


	/*------------------- RECEIVE -----------------------------------*/
	if (typ == RECV)
		{
		COMMSTAT   = NULL;
		COMMTYP    = NULL;
		ACTIONTYP  = NULL;
		MENUNR     = NULL;
		FELDNR     = NULL;
		comm.datalen = 0;
		(void)MPcomm(RECV, (long)app_data.maxdatain);
		entries = comm.buffer;
		laenge = (int)comm.datalen;

		/*--- remove waiting symbol --*/
		/*!! XFlush(display);      */
		xUItalkingModalityOff( nbWidgets);
		/*!! XFlush(display); */

		status = SEND;
		}

	/*------------------- SENDING -----------------------------------*/
	else /* SEND Status */
		{
		if (status != SEND)  /* synchron. error in communication */
			{
			xUIfehler(XUINOSENDPOSSIBLE, 0);
			return(0);
			}

		laenge = (long)0;

		/*--- Prevent user from touching windows ---*/
		/*!! XFlush(display);     */
		nbWidgets = xUIwidgets(wid);
		xUItalkingModalityOn( wid, nbWidgets);
		/*!! XFlush(display); */

		/*--- create comm.buffer if possible */
		if (len > 0)
			{
			if (len+1 > comm.alloclen)
				comm.buffer = (char *)MPalloc(comm.buffer, &comm.alloclen,
				      (long)app_data.maxdatain, len, sizeof(char));
			(void)memcpy((void *)comm.buffer, (void *)buffer, len);
			}

		comm.datalen = len;
		(void)MPcomm(SEND, (long)app_data.maxdatain);
		status = RECV;
		}

	return((long)laenge);
}
