/*D***********************************************************
 * copyright: yafra.org, Switzerland, www.pisoag.com
 *
 * modul:     MARCO POLO TO Classic GTK/Gnome GUI
 *
 * CVS tag:   $Name:  $
 * author:    $Author: mwn $
 * revision:  $Revision: 1.8 $
 **************************************************************/
static char rcsid[]="$Id: main.c,v 1.8 2008-11-23 15:44:38 mwn Exp $";
static char tagid[]="$Name:  $"; /* tagid is only once in the main() needed */

#include "version.h"

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

#include <mpgtk.h>

/* travelDB API includes */
#include <mpvarlib.h>
#include <mpvarapi.h>
#include <mpvarwww.h>

/* dbinet global status fields */
int MPNETstate;
int aktuellesprache;
char   argbuffer[2*_RECORDLEN];
char   messageBuffer[8*_RECORDLEN];
unsigned char bm_obj;
PSmemobj outputmem;

/* end of global decl. */
int main(int, char *[]);
static int read_arguments(int , char** );

int main (int argc, char *argv[])
{
	/* external global variables */
	extern int DebugFlag;
	extern int ipcfd;
	extern int MPNETstate;

	/* GTK windows */
	GtkWidget *logon;

	/* local vars */
	int cret;

	/* init vars */
	DebugFlag = 0;
	MPNETstate = MPOK;

	/* check arguments */
	cret = read_arguments(argc, argv);
	if (DebugFlag)
		PSSYSdebug(MPGTK_DBGFILE, MPGTK_PRGNAME, "starting GTK environment - args read with code %d", cret);

	/* init GTK */
#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
	gtk_set_locale();
	gtk_init(&argc, &argv);
	// add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

	PSSYSsyslog(_PSLOG_OPEN, "travelDB XML", "");
	PSSYSsyslog(_PSLOG_INFO, "travelDB XML", "Started MPNET service");
	PSSYSsyslog(_PSLOG_CLOSE, "travelDB XML", "");
	(void)MPXMLopen();

	/* start login dialog */
	logon = create_tdb_login();
	gtk_widget_show (logon);
	gtk_main ();

	/* finish */
	MPGTKexit(MPOK);
	return 0;
}

static int read_arguments(int argc, char** argv)
{
	extern int	DebugFlag;

	int     i;

	/*-----  Command-line arguments check --------   */
	for (i=1;  i<argc;  i++)
		{
		if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0))
			{
			(void)printf( "\n%s\n",  PSIDENT);
			(void)printf( "\n%s", " -D           : debugging mode (all with *)  " );
			(void)printf( "\n%s", " -f filename  : file for global setup        " );
			(void)printf( "\n%s", " -o option    : set this option              " );
			(void)printf( "\n%s", "       0  DB log                            *" );
			(void)printf( "\n%s", "       1  User log                          *" );
			(void)printf( "\n%s", "       2  Automatic info                     " );
			(void)printf( "\n%s", " -v  or  -h   : print this text you read     " );
			(void)printf( "\n\n" );
			exit(0);                         /* >>>>>>>>>> exit here >>>>>>*/
			}

		if (strcmp(argv[i], "-D") == 0)		/* enable debugging mode  */
			{
			i++;
			/*-- set main debugging flag -----*/
			DebugFlag  = (int)TRUE;
			continue;
			}


		if (strcmp(argv[i], "-f") == 0)		/* file for glob setup */
			{
			i++;
			continue;
			}

		if (strcmp(argv[i], "-o") == 0)		/* Options can only be set */
			{
			i++;
			//j = sscanf(argv[i], "%d", &optionNr);
			//optionSelect[optionNr] = 1;
			continue;
			}

		}

	return(MPOK);
}
