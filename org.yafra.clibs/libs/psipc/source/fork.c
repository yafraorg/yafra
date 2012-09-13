/**************************************************************/
/* Modul:     make a new process                              */
/*                                                            */
/* Copyright: Yafra.org     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/psipc/source/fork.c,v 1.3 2004-02-05 18:26:43 mwn Exp $";

#include <stdio.h>

#include <psipc.h>

#ifndef ps_winnt
#include <unistd.h>
#endif

/************************************************************
 * make a new process
 *
 * make a new process
 *
 * returns     int as an error code
 *
 * library:    libpsipc.a
 *
 * copyright:  Yafra.org, Switzerland, 1994
 *
 * author:     Administrator
 **************************************************************/
PS_DLLAPI int PSIPCfork(void)
{
	/* --- locals --- */
	int retpid = 0;

#ifdef ps_unix
	pid_t pid;

	pid = fork();
	retpid = (int)pid;
#endif

	return(retpid);
}

