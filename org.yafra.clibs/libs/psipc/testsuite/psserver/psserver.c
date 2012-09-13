/*D***********************************************************
 *  Copyright 2002 yafra.org
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * modul:     API - testsuite full ipc server                           
 *
 * @author:    mw
 **************************************************************/
static char rcsid[]="yafra.org";
static char tagid[]="yafra.org"; /* tagid is only once in the main() needed */

/* PROTOKOLL DEFINITION **************************************
Client sends:
0ascii-string\0
or
1\0 (which means exit)

---------------------------------------------------------------

Client receives:
OK\0 (if not exit)
***********************************************************/

#include <stdio.h>
#include <psipc.h>
#include <psserver.h>
#include "version.h"

/* end of global decl. */
int main(int, char *[]);
int PStst(int, char *[], int);

int DebugFlag;
char *PSIPCservicetitle = "PSIPC testserver";
char *PSIPCservicename = PSTST_SERVICE;
char *PSIPCprot = "tcp";
char *PSIPCservicedeps = "tcpip\0\0";
int (*PSclient)(int, char**, int);

int main(int argc, char *argv[])
{
	int cret = 0;

	PSclient = PStst;
	cret = PSIPCserver(argc, argv);

	if (cret != IPCOK)
		{
		(void)printf("\n PSserver exit with error code %d\n", cret);
		exit(1);
		}
	else
		{
		exit(0);
		}
}

int PStst(int argc, char *argv[], int fd)
{
	char infolen[PSTST_INFOLEN];
	char inbuffer[50000];
	int len;

	if (DebugFlag)
		printf("debug: this is client custom func with socket %d\n", fd);

	for (;;)
		{
		if (DebugFlag)
			printf("debug: read from socket\n");
		(void)memset(infolen, (int)NULL, PSTST_INFOLEN);

		PSIPCread(fd, infolen, PSTST_INFOLEN);

		if (DebugFlag)
			printf("debug: len is %s\n", infolen);
		len = atoi(infolen);

		if (len > 0)
			{
			(void)memset(inbuffer, (int)NULL, 50000);
			PSIPCread(fd, inbuffer, (size_t)len);
			}
		else
			{
			if (DebugFlag)
				printf("debug: no data received - server main/client function now returning\n");
			return(0);
			}


		if (DebugFlag)
			printf("debug: buffer is %s\n", inbuffer);
		if (*inbuffer == '1')
			{
			if (DebugFlag)
				printf("debug: server main/client function now returning\n");
			return(0);
			}
		}
}
