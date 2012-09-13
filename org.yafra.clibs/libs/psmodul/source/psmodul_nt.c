#ifdef ps_winnt

/*

	(c) Yafra.org, Switzerland

	MemoHASP Interface to protect Yafra.org products.

	For more information, refer to ntprot.h

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ntprot.h"

/* List of HASP services */
#define	IS_HASP	                        1
#define	GET_HASP_CODE                   2
#define	READ_MEMO                       3
#define	WRITE_MEMO                      4
#define	GET_HASP_STATUS                 5
#define	READ_MEMO_BLOCK                 50
#define	WRITE_MEMO_BLOCK                51

/* Memory size of the HASP key (= nr of cells) */
#define	HASP_MEMO_SIZE1                 112

/* License types for the application... */
#define FULL_LICENSE 1 
#define TEST_LICENSE 2

/* How much memory for each application? */
#define HASP_CELLS_PER_APP 1					/* Shouldn't be changed! */

/* passwords - same for all Ps HASPs! */
#define PASS1                           22079	/* 1st */
#define PASS2                           15123	/* 2nd */

/* seed requests and codes */
#define SRQ1      22079                         /* Request code */
#define SAN11        32                         /* 4 answer codes... */
#define SAN12     23905
#define SAN13     41184
#define SAN14     37285
#define SRQ2       9632                         /* Request code */
#define SAN21     11345                         /* 4 answer codes... */
#define SAN22      3656
#define SAN23      3116
#define SAN24     15360
#define SRQ3       2931                         /* Request code */
#define SAN31     15444                         /* 4 answer codes... */
#define SAN32      9232
#define SAN33     26907
#define SAN34     47164

/* Declare the function used to communicate with the HASP */
extern hasp (int,int,int,int,int,unsigned *,unsigned *,unsigned *,unsigned *);

int IsHASPAvailable()   
{
   int iP1,iP2,iP3,iP4;                     

   iP1 = iP2 = iP3 = iP4 = 0;          
   
   /* First, is the actual HASP attached to the port on the PC? */
   hasp(IS_HASP, 0, 0, PASS1, PASS2, &iP1, &iP2, &iP3, &iP4);
	
   return iP1;			/* 0 - HASP not found, 1 - HASP found */
}

int IsPsHASP()
{
	int iP1, iP2, iP3, iP4;
	int iQ1, iQ2, iQ3, iQ4;

	iP1 = iP2 = iP3 = iP4 = 0;
	iQ1 = iQ2 = iQ3 = iQ4 = 0;

	/* Check it's a HASP, with the correct seed codes... */                                                
	hasp(GET_HASP_CODE, SRQ1, 0, PASS1, PASS2, &iP1, &iP2, &iP3, &iP4);            
	hasp(GET_HASP_CODE, SRQ2, 0, PASS1, PASS2, &iQ1, &iQ2, &iQ3, &iQ4);            
                                                                     
	if((iP1 != SAN11) || (iP2 != SAN12) || (iP3 != SAN13) || (iP4 != SAN14) || 
	   (iQ1 != SAN21) || (iQ2 != SAN22) || (iQ3 != SAN23) || (iQ4 != SAN24))

		return 0;		/* Seed codes don't match! */

	else
		return 1;		/* Correct seed codes returned by HASP */
}

int CanApplRun(int aApplication, char* aVersionString, int *aErrorCode)
{
	int iP1, iP2, iP3, iP4;
	int retVal, iHASPLicenseType, iHASPVersionNumber;
	unsigned char haspBuffer[HASP_CELLS_PER_APP*2];
	long lVersionNumber;
	char *stopString;

	*aErrorCode = 0;		/* Initialise return variables... */
	retVal = 0;

	iP1 = aApplication * HASP_CELLS_PER_APP;	/* Which block to read? */

	if (iP1 > HASP_MEMO_SIZE1 || iP1 < 0)
		*aErrorCode = ILLEGAL_ADDRESS;			/* Illegal HASP memory location - wrong application Id? */
	else {
		
		iP2 = HASP_CELLS_PER_APP*2;				/* The number of bytes we want to get */
		iP4 = (int)haspBuffer;					/* Physical address of buffer to receive data */

		/* Read a block of memory from the HASP */
		hasp(READ_MEMO_BLOCK, 0, 0, PASS1, PASS2, &iP1, &iP2, &iP3, &iP4);

		if (iP3 != 0)
			*aErrorCode = READ_FAIL;			/* Serious problem - couldn't read HASP memory! */
		else {
			iHASPLicenseType = haspBuffer[0];

			if (iHASPLicenseType == FULL_LICENSE || iHASPLicenseType == TEST_LICENSE)
			
				if (iHASPLicenseType == FULL_LICENSE) {

					iHASPVersionNumber = haspBuffer[1];
					lVersionNumber = strtol(++aVersionString, &stopString, 10);	/* Get version number */

					if (strcmp(aVersionString, stopString) == 0)

						*aErrorCode = INVALID_VERSION;	/* This is an invalid version string! */

					else {

						if (iHASPVersionNumber >= lVersionNumber)
							retVal = 1;					/* Application has approval to run... */
						else
							*aErrorCode = BAD_VERSION;	/* Not able to run this particular version! */
						}
					}
				else
					retVal = 1;
			else
				*aErrorCode = NO_LICENSE;		/* No license - application not enabled! */
			}
		}

	return retVal;
}

#endif
