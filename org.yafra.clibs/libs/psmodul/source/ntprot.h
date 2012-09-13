/*

	(c) Yafra.org, Switzerland

	MemoHASP Interface to protect Yafra.org products.

	int IsHaspAvailable(void)

	Checks if a HASP is connected to the PC. Returns 0 if none is found, otherwise 1,
	indicating success.

	int IsPsHASP(void)

	Assumes that a HASP is connected to the PC and checks to see that this is a HASP
	supplied by Yafra.org, i.e. that the passwords and internal seed codes are correct.
	Returns 0 if not a HASP, otherwise 1, indicating conformity.

	int CanApplRun(short int, char*, int *)

	The application id and version number (as a string, e,g, "v01r00") are supplied to the function
	in the first two parameters, respectively. The version number is extracted from positions two 
	and three of the supplied string. Using this information, the function checks if the given
	application is allowed to run with the HASP currently connected. The function returns
	1 (True) or 0 (False). If the function returns 0, then an error code (as a negative number) is 
	written to the third parameter supplied to the function. If the function returns 1
	then this error code is always 0. Warning: function does not first test whether a 
	HASP is connected - the above two functions verify this, and should be called first!

*/

/* Function prototypes... */

int IsHASPAvailable(void);
int IsPsHASP(void);
int CanApplRun(int aApplication, char* aVersion, int *aErrorCode);

/* Error code return values for CanApplRun... */

#define ILLEGAL_ADDRESS	-1
#define READ_FAIL		-2
#define NO_LICENSE		-3
#define BAD_VERSION		-4
#define INVALID_VERSION	-5
