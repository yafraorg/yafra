/*D***********************************************************
 * header:    global vars for OUTput programs       mpvaract.h
 *
 * copyright: yafra.org, Basel, Switzerland     
 *************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpvaract.h,v 1.2 2008-11-02 19:55:33 mwn Exp $
*/


/*--- SQL-Memory im DBI */
MEMOBJ			sqlmem;
char sqlquery[_QUERYLEN]; /* global SQL query buffer */

/*--- some globals only for actions -----------*/
int globalflag = 0;
int FatalError;		/* Fataler Fehler beim Aufstarten */


/*--- mailing defines -------------------------*/
FILE *FPmail;                /* Mailfile */
char mailstring[RECLAENGE];  /* Mailstring */

/*--- Device parameters -----------------------*/
FILE		*FPoutbuf;
char		OutBuffer[15*STARTMEMCHUNK];    /* this is the tmp-buffer for FPoutbuf */
FILE		*FPout;
char		FPoutname[_FILELEN+1];
DEVICE_PORT	devicePort;
int GlobalPrinterMode;                  /* define the Printmode for this Output */

/*--- global language fields ------------------*/
int	aktuellesprache;         /* current      */
char	language[_CHAR20+1];     /* sprache bez  */
int	NbSupportedLang;         /* supported languages in DB */

int	recipientType;           /* firm/private combined with single/group */


/*--- faktura stuff ---------------------------*/
double     brutTotalVal;
double     minorTotalVal;
double     netTotalVal;
double     netnetVal;
double     breakTotalVal;
double     MWstTotalVal;

/*--- layout and forms ------------------------*/
int		LayLines;
int		LayPages;
int		LayLinesMax;
int		LayBottomMargin;
int	BottomMargin;          /* for compatibility only, obsolete */

/*--- Memory  ---------------------------------*/

	/*--- error messages read from DB to memory for access at every point */
int		akt_maxmessage;               /* count of action messages          */
char		**akt_message;                /* system messages in memory from DB */
MEMOBJ	msgmem;


	/*--- Arrangement dl view -*/
MEMOBJ		arrgtmem; 
ARRANGEMENT	*arrangement ;
int			anzArrgt;
	/*--- Arrangement dl view -*/
MEMOBJ		arrdlvmem, *pArrdlvmem; 
ARRDL_VIEW	*arrdlview ;
int			anzArrdl;
	/*--- buchung -------------*/
MEMOBJ		bchmem, *pBchmem; 
BUCHUNG		*buchung	;
int			anzBch;
	/*--- bchdln --------------*/
MEMOBJ		dlnmem, *pDlnmem;
BCH_DLN		*bchdln;
int			anzBd;
	/*--- reservation ---------*/
MEMOBJ		resmem, *pResmem;
RESERVATION	*reservation ;
int			anzRes;
	/*--- reservation view ----*/
MEMOBJ		resvmem, *pResvmem; 
RES_DL_VIEW	*resview ;
int			anzResv;
	/*--- aktion detail -------*/
MEMOBJ		aktdetmem, *pAktdetmem;
AKT_DETAIL	*aktdetail ;
int			anzAktdet;
	/*--- dlgdlg Dl + Tdl -----*/
MEMOBJ		dlgdlgmem, *pDlgdlgmem; 
DLG_DLG		*dlgdlg ;
int			anzDlgdlg;
	/*--- preis ---------------*/
MEMOBJ		preismem, *pPreismem;
PREIS			*preis ;
int			anzPreis;
int         LWlandid;
int         LWwhrid;
	/*--- price matrix --------------*/
MEMOBJ		matrixmem ;
PRICERESULT	*priceMatrix ;
int			anzMatrix;
	/*--- commission ----------------*/
MEMOBJ		commismem, *pCommismem;
KOMMISSION	*commis ;
int			anzCommis;
int			CommisTyp;
	/*--- price matrix --------------*/
MEMOBJ			comatrixmem ;
COMMISRESULT	*commisMatrix ;
int				anzComatrix;



/****************************************************************
 *  AKTIONEN     *  F L A G S  *
 ****************************************************************/
/* -A */ int dlaid;				/* DIENST_ANGEBOT */
/* -a */ int arrid;				/* ARRANGEMENT */
/* -b */ int bchid;				/* BUCHUNG */
/* -C */ int ActionNumber;    /* an individual Action Number */
/* -c */ int dlgid, tdlid;		/* DLGPART id */
/* -D */ /* see mpvarlib.h */	/* debug flag */
/* -d */ char DBname[_RECORDLEN];	/* Datenbankname */
/* -E */ int abdate, time_start;		/* Abfahrtsdatum und Zeit */
/* -e */ int time_end;			/* anfangs- und end- Zeit/Datum */
/* -f */ int specificflag;		/*interpreted by each action */
/* -g */ int kolid;				/* KOLLEKTIV */
/* -H */ char guiHostname[_FILELEN+1] = "\0" ;
/* -h */ int dltid;				/* DIENST_TRAEGER */
/* -J */ int debitorflag;	   /* Debitoren Journal */
/* -k */ int kunid;				/* KUNDEN */
/* -K */ int katid;				/* KATEGORIE */
/* -L */ int dialogsprache;	/* can overwrite user language */
/* -l */ int outputsprache;	/* can overwrite receiver language */
/* -M */
/* -m */ int device_id;			/* Ausgabemedium ID */
/* -N */ int hostkontid;      /* HOST_KONT */
/* -n */ int kontid;          /* KONTINGENT */
/* -R */ int reinitflag;		/* reinit of akt_detail */
/* -S */ int exectyp;			/* Execution Typ */
/* -s */ int dlid;				/* DIENSTLEISTUNG */
/* -t */ int akttid;				/* AKTIONSTYP */
/* -u */ int dlnid;				/* REISENDER */
/* -X */ int LockAction;      /* locking of an action */
/* -y */ int kuntypid;			/* KUNDEN_TYP id */
/* -Z */ int sourcesta;			/* source reservation state */
/* -z */ int targetsta;			/* Target reservation state */

