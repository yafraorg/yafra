/**************************************************************
 * modul:     manage /etc/password functions
 *            get a userid or get a user string from an id
 *            and so on
 *
 *
 * copyright: Yafra.org
 **************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/password.c,v 1.2 2004-02-05 18:47:29 mwn Exp $";

/* system includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef ps_win
#else
#include <pwd.h>
#include <unistd.h>
#endif

/* piso includes */
#include <pssys.h>

/************************************************************
 * get the current password entry of this process
 *
 * get uid/gid from the passwd file. On msdos/mswin we don't have
 * this, so we do nothing
 *
 * returns     int as an error code
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSgetUser(int *aUserId,    /* the real user ID number as return */
                 char *aUser      /* the real user string as return */)
{
	int cret = PSOK;

	/* init */
	*aUserId = 0;
	*aUser = (char)NULL;

#ifdef ps_unix
	{
	uid_t userid;
	struct passwd *userpasswd;

	/* get the user id of this process */
	userid = getuid();
	userpasswd = (struct passwd *)getpwuid(userid);

	/* set output data */
	*aUserId = userid;
	(void)strcpy((char *)aUser, (char *)userpasswd->pw_name);
	}
#endif
	return(cret);
}


/************************************************************
 * set the current password entry of this process
 *
 * set uid/gid from the passwd file. On msdos/mswin we don't have
 * this, so we do nothing
 *
 * returns     int as an error code
 *
 * library:    libpssys.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSSYSsetUser(int *aUserId,    /* the real user ID number as return */
                           char *aUser      /* the real user string as return */)
{
	int cret = 0;

#ifndef ps_mingw
#ifndef ps_winnt
	struct passwd *Passwd_ptr;

	/* get UID and check it with UNIX UID */
	Passwd_ptr = getpwnam(aUser);
	if (Passwd_ptr == NULL)
		cret = -1;
	else
		{
		/* set process user ID */
		cret = setgid(Passwd_ptr->pw_gid);
		if (cret == 0)
			{
			cret = setuid(Passwd_ptr->pw_uid);
			if (cret != 0)
				perror("\nPSSYS setgid error:");
			}
		else
			perror("\nPSSYS setuid error:");
		}
#endif
#endif

	return(cret);
}

