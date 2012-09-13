/*IH***********************************************************
 * File:          Portability                        portable.h
 *
 * Description:   Definitions and Prototypes (ANSI C)
 *                for portable objects
 *                
 *
 * Copyright: Yafra.org
 **************************************************************
 *
 RCS Information:
 $Header: /yafraorg/cvsroot/foundation/ansic/include/psportable.h,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $
 */


/*T------------------------ FILE HANDLING -----------------------------------*/
#ifndef ps_unix
	#define   PS_FILENAMELEN  256
	#define   _P_READ_         "rb"
	#define   _P_READUPDATE_   "rb+"
	#define   _P_WRITE_        "wb"
	#define   _P_WRITEUPDATE_  "wb+"
	#define   _P_APPEND_       "ab"
	#define   _P_APPENDUPDATE_ "ab+"
	#define   _P_PATH_SEP      '\\'
#else
	#define   PS_FILENAMELEN  256
	#define   _P_READ_         "r"
	#define   _P_READUPDATE_   "r+"
	#define   _P_WRITE_        "w"
	#define   _P_WRITEUPDATE_  "w+"
	#define   _P_APPEND_       "a"
	#define   _P_APPENDUPDATE_ "a+"
	#define   _P_PATH_SEP	   '/'
#endif

/*P------------------------ TOKENS ------------------------------------------*/
#ifndef ps_unix
	#define _P_EOL_  "\r\n"  
#else
	#define _P_EOL_  "\n"  
#endif

