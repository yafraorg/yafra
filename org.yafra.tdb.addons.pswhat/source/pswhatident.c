#include <stdio.h>

void main(int, char **);

void main(int argc, char **argv)
{
	if (argc < 2)
		{
		printf("usage: pswhat program or pswhat -i program\n");
		exit(-1);
		}
	if (strcmp(argv[1], "-i") == 0) {
		psidentMain(argc, argv);
	} else {
		pswhatMain(argc, argv);
	}
}
