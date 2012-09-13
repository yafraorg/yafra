#include <stdio.h>
#include <stdlib.h>
#include <pssys.h>

#include <errno.h>

extern int errno;

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	char text[200];
	FILE *test;

	printf("\n\nPSSYSdebug test 1 on stdout\n");
	PSSYSdebug(stdout, argv[0], "test");

	printf("\n\nPSSYSdebug test 2 on stderr\n");
	strcpy(text, "Martin");
	PSSYSdebug(stderr, argv[0], "test mit variable %s", text);

	printf("\n\nPSSYSlog open\n");
	PSSYSlog(_PSLOG_OPEN, argv[0], "testlog.log", NULL);
	printf("PSSYSlog write\n");
	PSSYSlog(_PSLOG_ERROR, argv[0], "testlog.log", "test von %s", text);
	printf("PSSYSlog close\n");
	PSSYSlog(_PSLOG_CLOSE, argv[0], "testlog.log", NULL);

	printf("\n\nPSSYSsyslog open\n");
	PSSYSsyslog(_PSLOG_OPEN, argv[0], NULL);
	printf("PSSYSsyslog write\n");
	PSSYSsyslog(_PSLOG_ERROR, argv[0], "test von %s", text);
	printf("PSSYSsyslog close\n");
	PSSYSsyslog(_PSLOG_CLOSE, argv[0], NULL);

	printf("\n\nPSSYSerrorlog write\n");
	test = fopen("/home", "w");
	PSSYSerrorlog(errno, stderr, argv[0], "testfehler von %s", text);

	printf("debug: test done and exit 0\n");
	exit(0);
}
