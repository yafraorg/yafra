#include <stdio.h>
#include <pssys.h>

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
	int cpid;
	char astr[1024];
	char bstr[1024];
	char cstr[1024];

	printf("debug: PS character tests\n");

	printf("debug: start converting to upper case\n");
	strcpy(astr, "das ist alles lower Case");
	printf("debug: string before: %s\n", astr);
	PSSYSstrUpper(astr);
	printf("debug: string after PSSYSstrUpper: %s\n", astr);

	printf("debug: tests done - exit now\n");
	exit(0);
}
