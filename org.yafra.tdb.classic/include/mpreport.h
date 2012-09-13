/************************************************************
                          * yafra.org *
			   tdb
			   -------------------
*****************************************************************************
 Beschreibung           : output definitions of tdb actions
*****************************************************************************

/*---- File Suffix --------------------------------------------------------*/
#define		SELECT_SUFFIX	".sel"
#define		FORMAT_SUFFIX	".for"
#define		TEXT_SUFFIX		".tex"

/*---- File Path ---------------------------------------------------------*/
#define		SELECT_PATH 	"/users/softech/data/chandris/"
#define		FORMAT_PATH 	"/users/softech/data/chandris/"
#define		TEXT_PATH 		"/users/softech/data/chandris/"

#define TRUE	1
#define FALSE	0

#define NonQueryFlag	FALSE		/* NonQuery Abfragen ja/nein */

/* NbrFmtRecords is number of columns expected in a dynamic SELECT. */
#define NbrFmtRecords   255
#define EndOF           100
#define MaxDataBuff     2500
#define MaxColSize      3996
#define	MaxStr		132
#define MAX_SELECT	3996

/*---- Structuren fuer Verknuepfte Listen --------------------------------*/

typedef struct int_list{
	int value;
	struct int_list *next;
}INT_LIST;

typedef struct char_list{
	char ch[MaxColSize];
	struct char_list *next ;
}CHAR_LIST;

typedef struct float_list{
	double value;
	struct float_list *next ;
}FLOAT_LIST;

typedef struct {
	char name[MaxColSize];
	int *pointer;
	int anz_elemente;
}CHAR_OUTPUT;

typedef struct {
	int name;
	int *pointer;
	int anz_elemente;
}INT_OUTPUT;

typedef struct {
	double name;
	int *pointer;
	int anz_elemente;
}FLOAT_OUTPUT;

typedef struct {
	union {
		int **ipointer;
		double **fpointer;
		char **cpointer;
	}POINTER;
	int anzahl;
	int type;
}OUTPUT;
