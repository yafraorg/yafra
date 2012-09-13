/*************************************************************
 * header:    header file for SHARED LIBRARIES AND DLLs
 *
 * copyright: Yafra.org
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafraorg/cvsroot/foundation/ansic/include/psshared.h,v 1.2 2003-05-11 12:13:27 mwn Exp $
*/

#ifndef PSSHAREDDEFINED
#define PSSHAREDDEFINED

/* PS_SHAREDLIB is set to 1 if OSHARED is set */
/* PS_SHAREDLIB is set to 2 if OUSESHARED is set */
/* PS_SHAREDLIB is NOT set if either OSHARED nor OUSESHARED is set */

#if PS_SHAREDLIB == 1
# ifdef ps_win
#  define PS_DLLAPI __declspec(dllexport)
# else
#  define PS_DLLAPI
# endif
#elif PS_SHAREDLIB == 2
# ifdef ps_win
#  define PS_DLLAPI __declspec(dllimport)
# else
#  define PS_DLLAPI
# endif
#else
# define PS_DLLAPI
#endif

#endif
