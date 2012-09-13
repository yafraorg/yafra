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
 * modul:     API - utilities                           
 *
 * @author:    $Author: xy $
 **************************************************************/
static char rcsid[]="yafra.org testsuite psipc";
static char tagid[]="yafra.org"; /* tagid is only once in the main() needed */
#include <stdio.h>
#include <psipc.h>

int main(int argc, char *argv[]);
int DebugFlag;
char *PSIPCservicetitle = "PSIPC testserver";
char *PSIPCservicename = "test";
char *PSIPCprot = "tcp";
char *PSIPCservicedeps = "tcpip\0\0";
int (*PSclient)(int, char**, int);

int main(int argc, char *argv[])
{
	int cpid;

	printf("PSfork test\n");

	printf("start forking now\n");
	cpid = PSIPCfork();
	printf("PSfork return is %d\n", cpid);

	printf("exit now\n");
	exit(0);
}
