#include <stdio.h>
#include <pssys.h>
#include <locale.h>
#include "version.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	int cpid;
	char astr[1024];
	char bstr[1024];
	char cstr[1024];


#ifdef ps_unix
	setlocale(LC_ALL, "en_US.utf8");
#endif

	printf("\ndebug: c type size test - %s\n", PSIDENT);
	printf("debug: test sizeof of standard types (char, short, int, long, etc)\n");
	printf("sizeof char: %2d\n", sizeof(char));
	printf("sizeof short: %2d\n", sizeof(short));
	printf("sizeof int: %2d\n", sizeof(int));
	printf("sizeof long: %2d\n", sizeof(long));
	printf("sizeof long long: %2d\n", sizeof(long long));
	printf("sizeof float: %2d\n", sizeof(float));
	printf("sizeof double: %2d\n", sizeof(double));
	printf("sizeof void *: %2d\n", sizeof(void *));
	printf("sizeof size_t: %2d\n", sizeof(size_t));
	printf("sizeof time_t: %2d\n", sizeof(time_t));

	printf("\ndebug: PS character tests\n");
	printf("debug: test with locale using umlaute: äöüéàè€\n");
	printf("debug: start converting to upper case\n");
	strcpy(astr, "das ist alles lower Case");
	printf("debug: string before: %s\n", astr);
	PSSYSstrUpper(astr);
	printf("debug: string after PSSYSstrUpper: %s\n", astr);

	printf("debug: tests done - exit now\n");
	exit(0);
}
