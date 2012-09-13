#include <stdio.h>
#include <stdlib.h>
#include <psmodul.h>

void HASPtest(int aApp, char* aVerStr)
{
	int retVal;

	printf("App %d, version %s:\n", aApp, aVerStr);
	retVal = PSmodul(aApp, aVerStr, 0);
	printf("debug: return from call >%d<\n\n", retVal);
}

int main(int argc, char *argv[])
{
	HASPtest(0, "v01r01");
	HASPtest(-3, "v01r01");
	HASPtest(MPGUI, "v02r01");
	HASPtest(8, "v07r07");
	HASPtest(9, "hello!");

	printf("debug: test done and return 0\n");

	return (0);
}
