/**************************************************************
 * File:      what.c
 * Modul:     print out version infos of binaries and libs
 *
 * Copyright: yafra.org
 **************************************************************/
static char rcsid[]="$Header: see github.com yafra $";

#include "version.h"
#include <stdio.h>
#include <psportable.h>

/*
 * Copyright (c) 1980, 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
static char copyright[] =
"@(#) Parts of sourcee copyright (c) 1980, 1988, 1993 The Regents of the University of California. Rest www.yafra.org";

void pswhatMain(int, char **);
void search(void);

/*
 * what
 */
void pswhatMain(int argc, char **argv)
{
	if (!*++argv) 
		search();
	else
		{
		do
			{
			if (!freopen(*argv, _P_READ_, stdin))
				{
				perror(*argv);
				exit(1);
				}
			printf("%s\n", *argv);
			search();
			} while(*++argv);
		}

	exit(0);
}

void search(void)
{
	register int c;

	while ((c = getchar()) != EOF)
		{
loop:	if (c != '@')
			continue;

		if ((c = getchar()) != '(')
			goto loop;

		if ((c = getchar()) != '#')
			goto loop;

		if ((c = getchar()) != ')')
			goto loop;

		putchar('\t');

		while ((c = getchar()) != EOF && c && c != '"' && c != '>' && c != '\n')
			putchar(c);

		putchar('\n');
		}

	return;
}