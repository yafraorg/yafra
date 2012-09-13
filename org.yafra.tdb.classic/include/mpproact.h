/*DH***************************************************************
 * Header:    mpproact.h 
 *            prototypes for MarcoPolo actions                    
 *                                                                
 * Copyright: yafra.org, Dornacherweg 104 Basel     
 *            Switzerland                                         
 ******************************************************************/

#define MAXREDUKT	(int)20

/*--- base action prototypes --------------------------------------------*/
void	AKTmsg							(int, int, char *);
void	AKTmsghandler					(int, char *);
int	AKTmsginit						(void);
void	AKTmsgget						(int, char *);
int	AKTmsgfree						(void);

void	AKTarrgtMemobjInit			( );
void	AKTarrgtMemobjFree			( );
int	AKTarrgtGetAll					( int aProgid );
void	AKTarrDlViewMemobjInit		( );
void	AKTarrDlViewMemobjFree		( );
int	AKTarrDlView					( int aArrid );
void	AKTarrDlgdlgMemobjInit		( );
void	AKTarrDlgdlgMemobjFree		( );
int	AKTarrGiveAllDlgFor			( int aDlgid );

void	AKTbchdlnMemobjectInit		();
void	AKTbchdlnMemobjectFree		();
int	AKTbchFindAll					(MEMOBJ *mem, int *anzBch, int bchid, int kolid, int dlgid, int kunid);
int	AKTdlnFindAll					(MEMOBJ *mem, int *anzDln, int bchid, int kolid);
int   AKTbchOrderByDltKat        ( int aTdlid, int OrderBy );

void	AKTdlgdlgMemobjInit			( );
void	AKTdlgdlgMemobjFree			( );
int	AKTdlgdlgFindAll				( int aDlid );

void	AKTrecipient					(BUCHUNG *pBch, BCH_DLN *dlnview, int anzDlnv, int currentDln );
void	AKTrecipientSetType			(BUCHUNG *pBch);
void	AKTrecipientGetText			(BUCHUNG *pBch, int aDlnid, RECIPIENT *pRecip); 
void	AKTrecipientWriteOut			(RECIPIENT *pRecip );
int   AKTrecipientGiveKundenType ( BUCHUNG *pBch );

void	AKTparticipantTitle			(int aKolid );
void	AKTparticipantSingle			(int aDlnid, char* margin );
void	AKTparticipantAll				(BCH_DLN *dlnview, int anzDlnv, char* margin);
void	AKTgroupName					(int aKolid );

void	AKTresViewMemobjInit			( );
void	AKTresViewMemobjFree			( );
int	AKTresViewStatus				( int aBid, int aDlid, int aSourcesta, int aTargetsta );
int	AKTresViewDl_variant			( int aDlid, int aVariant);

void	AKTreservatMemobjInit		();
void	AKTreservatMemobjFree		();
int 	AKTreservatFindDl				( int aDlid );
int	AKTreservatFindAll			(int aBid, int aPersid );
int   AKTreservatFindCat         ( int aDlgid, int aDlnid, char *CatTxt );
int	AKTreservatBidDlgid			(int aBid, int aDlid );
int	AKTreservatStatus				(int aBid, int aDlid, int sourcesta, int targetsta );
void	AKTreservatSortService		();
void	AKTreservatSortLeader		();
void	AKTreservatGetStartDate		(time_t *startDate);
void	AKTreservatCopyDate			();
void	AKTreservatCopySortDate		();
void	AKTreservatCheckActionType	();
void	AKTreservatPriceSingle		();
int	AKTreservatPartsExpand		();
int	AKTreservatReplaceDl			();
int   AKTreservatCheckFirstLeg   ( int aBid, int aTdlid );
void	AKTreservatChangeZusatzbett( int aDlgId, int aZusatzid );
int AKTreservatGetStrechFrom		( int aPersId, int aTeil, char *aFrom, char *aTo );

int	AKTactionDetailFind			(int aBchid, int aPersid, int aDlgid, int anAkttid);

void	AKTpriceMemobjInit			();
void	AKTpriceMemobjFree			();
int	AKTpriceFindAll				( int, int);
int	AKTpriceVerify					( RESERVATION *, int);
void	AKTpriceGetAll					( double *);
int	AKTpriceCountValid			( );
int	AKTpriceMatrixPrepare		( int, int, int);
void	AKTpriceMatrixGetSum			( double *, int);
void	AKTpriceMatrixGetAESum		( double *, double *, int);
int   AKTpriceTrialDebitor       ( void );
int   AKTpriceWriteDebitor       ( PRICERESULT *pPrice,  BUCHUNG *pBch, int akt_nr, double reduktion, double kommission );

void	AKTcommisMemobjInit			();
void	AKTcommisMemobjFree			();
int	AKTcommisFindAll				(int aBid, int aDlnid, int aKunid, int aKolid);
int	AKTcommisPrepare				( PRICERESULT *pPr, int aKunid, int aKolid );  
int	AKTcommisKunPrepare			( int aKunid);
int	AKTcommisVerify				( PRICERESULT *pPr );
int	AKTcommisComputeResult		( int nbDiscount, double brutVal,	double *comVal );  
int   AKTcommisPrintAllValid     ( );
int	AKTcommisDeleteItemWhen 	( int matchingOrNot, char *aString );
int	AKTcommisGetIndexWhen 		( char *aString );
int	AKTcommisCompute				( PRICERESULT *pPr, double *brutVal, double *minorVal, double *netVal );
int	AKTcommisPrint					( PRICERESULT *pPr, double brutVal );
int	AKTcommisMatrixBuild			( );
int	AKTcommisMatrixPrint			( );
int	AKTcommisCountValid			( );
int   AKTcommisMWStPrepare       ( int aDlgid );
int   AKTcommisPrintAllValid     ( );


int	AKTcompareDlnRes		(int aBid, BCH_DLN *dlnview, int anzDlnv, int *compstat );
int	AKTcompareResDate		(RESERVATION *resA, RESERVATION *resB );

int	AKTcntrl					(int, AKT_DETAIL *, int);
int   AKTcntrlGiveActionNumber ( int aAktionsTyp, int aBuchungsId, int aDlnId, int aDlgId, int flag );

int	AKTdeviceInit			(int, int);
int	AKTdeviceOuput		(void);
int   AKTdevicePrintCtrl   ( FILE *FPoutbuf, int sequence );

int	AKTmailHeader			(void);
void	AKTmailDevice			(char	*clientname, char *callnr);
void	AKTmailStatusWrong	( int aBid, int aStatus );
void	AKTmailArrangement	( int aArrid );
int	AKTmailDetail			(int bch_id, int dl_id, int tdl_id, int dla_id, int dlt_id);
int	AKTmailPriceProblem	(int aBid, int aDlid );
void	AKTmailFoot				(int status);

int	AKTdatetimeday			(int sek, char *date, char *zeit, char *day, char *lang );
void	AKTdateTextLang		(int sek, char *date, char *zeit, char *day, char *lang, int textform);
int	AKTdateConvertToAge	( char *dateStr );

void	AKTlanguage					(int, int, int, int);
int	AKTlanguageCount			( );
int	AKTlanguageDepText		(int textid, int typ, int spr, int s_id, char *buffer);
int	LanguageDependentBez		(int, int, int, int, char *);
int	LanguageDependentText	(int, int, int, int, char *);
int	AKTobjbez					(int, int, char *);
int	AKTobjtxt					(int, int, char *, char *);
int	AKTobjtxtFormat			(int typ, int textid, char *buffer, char *format);

int 	UtilSetAKTlock				(void);
int 	UtilUnsetAKTlock			(void);

int	AKTiobufferInit			(void);
int	AKTiobufferClose			(void);


void	AKTlayoutInit				(void);
int	AKTlayoutGetPages			(void);
int	AKTlayoutPageEndReached	(void);
void	AKTlayoutFormFeedPrint	(FILE *aFPoutbuf);
void  AKTlayoutLinesAdd			( int aNumber );
int	AKTlayoutGetLines			(void);
int	AKTlayoutGetFreeLines	(void);
void	AKTlayoutNewLinePrint	(FILE *aFPoutbuf);
void	AKTlayoutNewLine			(void);
void	AKTlayoutPrintManyNewLines( FILE *aFPoutbuf, int aNumber);


/*--- Interface to Command server daemon which executes system(command) */
int	CMDclientSystem		(char *command);





/*--------------------------------------------------------------------------*/
/* OLD functions  DON'T USE THESE ANY MORE OR YOU WILL GET TROUBLES WITH mw */
/*--------------------------------------------------------------------------*/
int OutputCtrl(int, AKT_DETAIL *, int, int, int, int, FILE *);
int IntNr(char *data , int anzahl , int table , int typ , int id , int *start , int *end );
int GiveAktNrFrom( int AktionsTyp, int BuchungsId, int DlgId, FILE *fpMail );
void MinPriceCalc(PREIS*, int*, double*, int*, double*, int, int, int, int, int, int, int);
int OrderBidByKat( RESERVATION *reservation, int anzres, BUCHUNG *buchung, int anzbch );
double PriceCalc ( int		dlg_id,
						int		bid,
						int		uid,
						int		kid,
						int		kar,
						int		res_start,
						int		res_end,	
						int		akt_start,
						int		akt_end,
						int		*redpreisnr,
						int		*kommpreisnr,
						int		*redkostenart,
						int		*kommkostenart,
						int		*anzred,
						int		*anzkomm,
						double	*kommab,
						double	*kommabproz,
						double	*kommnewprice,
						double	*redab,
						double	*redabproz,
						double	*rednewprice,
						char 		redukabk[MAXREDUKT][_CHAR30+1],
						char		reduktxt[MAXREDUKT][_CHAR30+1],
						char		kommabk[MAXREDUKT][_CHAR30+1],
						char		kommtxt[MAXREDUKT][_CHAR30+1],
						double	*totalvpr );
int SuchePreis(PREIS *, PREIS *, int, int, int, int);
int LookForOne(PREIS *, PREIS *, int, int);
int buchdat(int, int *, int *, int *, int *, int *,
            int *, int *, int *, FILE *);
char *convdate(time_t, char *, char *, char *);
int cruisedlt(int *, char *, char *, char *, char *, int);
int cruiseplatz(int, int *, int *, char *, char *, char *, char *);
int cruisecab(int, int, char *, char *, char *, char *);
int kommabzug (
						int komm_id,
						PREIS *preis,
						int round,
						int *preis_nr,
						double *newpreis,
						int *kostenart,
						double *abzug,
						double *proz,
						char *abztxt,
						char *abzabk
					);
void suchkunde(int, int *, int *, int *, int *, int *);
int groupref(KOLLEKTIV *, char *, char *);
int datetimeday(int, char *, char *, char *, char *);
