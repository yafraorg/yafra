/*D***********************************************************
 * descr:     Action - include               mpdefact.h 
 *            Definition and typedefs for actions 
 *            
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************/
/*R
 RCS Information:
 $Header: /yafra/cvsroot/mapo/source/include/mpdefact.h,v 1.2 2008-11-02 19:55:32 mwn Exp $
*/


/************************************************************
 * Section:  common definition for all actions 
 *************************************************************/

/*--- Error types in actions  ------------*/
#define MPOK                  0  /* alles soweit gut          */
#define MPERROR               1  /* allg. Error               */
#define MPMSG                 2  /* allg. Warning/Message     */
#define MPWARNING             2  /*         "                 */
#define MPINFO                3  /* allg. Info                */
#define MPDBERROR             4  /* allg. DB Error            */
#define MPEMERG               5  /* emergency error           */
#define MPDEBUG               6  /* debug information         */
#define MPNOP                 9  /* keine Operation ausgef.   */

/*--- type of error for acterror function */
#define ACT_OSERROR     (int)1
#define ACT_SQLERROR    (int)2
#define ACT_ERROR       (int)3
#define ACT_WARNING     (int)4
#define ACT_INFO        (int)5

/*--- Devices directions -----------------*/
#define _DEV_OUTPUT		(int)0
#define _DEV_INPUT		(int)1
#define _DEV_BIDIR		(int)2

/*--- Printermodes of the Devices --------*/
#define _DEV_EPSON_MODE	(int)0
#define _DEV_LASERJET   (int)1

/*--- Device special escape commands --------*/
#define _DEV_RESET_PRINTER		(int)0
#define _DEV_NORMAL_PITCH		(int)1
#define _DEV_COMPRESSED_ON 	(int)2
#define _DEV_COMPRESSED_OFF 	(int)3
#define _DEV_ENLARGED_ON   	(int)4
#define _DEV_ENLARGED_OFF   	(int)5
#define _DEV_PITCH_10   		(int)6
#define _DEV_PITCH_12   		(int)7
#define _DEV_ITALIC_ON  		(int)8
#define _DEV_ITALIC_OFF 		(int)9
#define _DEV_LETTER_ON  		(int)10
#define _DEV_LETTER_OFF  		(int)11
#define _DEV_BOLD_ON  	   	(int)12
#define _DEV_BOLD_OFF  	   	(int)13
#define _DEV_UNDERLINE_ON 	   (int)14
#define _DEV_UNDERLINE_OFF  	(int)15
#define _DEV_DOUBLE_HIGH_ON 	(int)16
#define _DEV_DOUBLE_HIGH_OFF  (int)17
#define _DEV_SUBSCRIPT_ON 		(int)18
#define _DEV_SUBSCRIPT_OFF  	(int)19
#define _DEV_SUPERSCRIPT_ON 	(int)20
#define _DEV_SUPERSCRIPT_OFF  (int)21
#define _DEV_LANDSCAPE        (int)22
#define _DEV_PORTRAIT         (int)23
#define _DEV_BELL    	   	(int)24

/*--- Select Variants (avoid multiple functions ---*/
#define VARIANT_0			(int)0
#define VARIANT_1			(int)1
#define VARIANT_2			(int)2

/*--- Options for sieve functions ------*/
#define MP_NOT_MATCHING		(int)0
#define MP_MATCHING			(int)1

/*--- margin defines for actions ---------*/
#define NOMARGIN			""
#define FORM_SEPAR		'@'      /* separator between text and format */

/*--- nb of lines for a form -------------*/
#define _NBLINES_NORMAL_		68
#define _NBLINES_COMPRESSED_  80

/*--- Recipient type ---------------------*/
#define REC_PRIV_SINGLE		(int)1
#define REC_FIRM_SINGLE		(int)2
#define REC_PRIV_GROUP		(int)3
#define REC_FIRM_GROUP		(int)4

/*--- Date/time/day formats -------0------*/
#define TODAY_VALUE			(time_t)0
#define DATE_DIGITFORM		(int)0
#define DATE_TEXTFORM		(int)1
#define MONTH            2592000
#define HOUR                3600
#define EUROPEEN            "europeen"
#define AMERICAN            "american"

/*--- definition of Commission types (kunden/Reisende) -------------*/
#define _ACT_COMMIS_KUNDE		 0
#define _ACT_COMMIS_REISENDER  1

/*--- Special Ordervalues for the *buchung Buffer ----------*/
#define BCH_ORDER_BY_KAT_ALL   	(int)0
#define BCH_ORDER_BY_KAT_KOL		(int)1


/*--- message id's ----------------------*/
#define MPA_OK               0  /* ok message                         */
#define MPA_ERRORHEADER      1  /* header message for error msg       */
#define MPA_OSERRORHEADER    2  /* header message for os error msg    */
#define MPA_SQLERRORHEADER   3  /* header message for sql error msg   */
#define MPA_SUPPORT          4  /* support information                */
#define MPA_MAILHEADER1      5  /* mailing header 1                   */
#define MPA_MAILHEADER2      6  /* mailing header 2                   */
#define MPA_OBJECTDL         7  /* dl info                            */
#define MPA_OBJECTDLT        8  /* dlt info                           */
#define MPA_FAXTLXTO         9  /* adress of fax/tlx send             */
#define MPA_PAGES           10  /* no of pages printed/filed          */
#define MPA_OUTPUTTYP       11  /* typ of output (printer/file/fax/...) */
#define MPA_CONFIRMMSG      12  /* confirmation message of action exec  */
#define MPA_EXECTYP         13  /* automatic immediately execution    */
#define MPA_NOSTART         14  /* action could not be started        */
#define MPA_SELECTERROR     15  /* error in select                    */
#define MPA_INVALIDARGS     16  /* wrong parameters/arguments         */
#define MPA_FILENAME        17  /* filename if output is a file       */
#define MPA_ALREADYSTARTED  18  /* action is already started          */
#define MPA_ALREADYOK       19  /* action is already done/ok          */
#define MPA_SOURCESTAWRONG  20  /* source res_sta is wrong            */
#define MPA_FATALERRORSTATE 21  /* action is on fatal error state     */
#define MPA_CNTRLDBERROR    22  /* sql/db error                       */
#define MPA_SETTOERROR      23  /* action is set to error state       */
#define MPA_SETTOFATAL      24  /* action is set to fatal error state */
#define MPA_NOCONFIRM       25  /* action could not be confirmed      */
#define MPA_DBERROR         26  /* general DB/SQL error               */
#define MPA_OBJECTDLA       27  /* dl angebot info                    */
#define MPA_OBJECTDLID      28  /* dl-d Teil dienstleistung info      */
#define MPA_OBJECTBCH       29  /* Buchung info                       */
#define MPA_DEVICEERROR     30  /* error in device handling           */
#define MPA_TICKETWARNING   31  /* missing ticket part, not complete  */
#define MPA_PRICEERROR      32  /* no price or problem with a price   */
#define MPA_SRCRSTA         33  /* source reservation status          */
#define MPA_TARGETRSTA      34  /* target reservation status          */
#define MPA_OUTBUFERROR     35  /* error in temp io buffer handling   */
#define MPA_OBJECTARR       36  /* arrangement info                   */
#define MPA_INCOMPATIBLE    37  /* Incompatible actions parameters    */
#define MPA_KOMMERROR       38  /* Zuviel kommissionen  definiert     */
#define MPA_NOKOMMERROR     39  /* Keine  kommission definiert        */
#define MPA_PRICEDESCRIPT   40  /* Preisbeschreibung bei Problemen    */
#define MPA_PRICECOUNTER    41  /* Preisauswertung bei Problemen      */
#define MPA_OBJECTHKON      42  /* hkon info                          */



/************************************************************
 * Section:  Typedefs  
 *************************************************************/

/* --- Device structure -------------------*/
typedef struct {
	int	type;								/* type of device                     */
	int	direction;						/* direction input or output or both  */
	int	delay;							/* delay for execution                */
	char	recipient[_TEXTLEN];			/* recipient                          */
	char	faxnumber[_TEXTLEN];			/* for fax                            */
	char	callnumber[_TEXTLEN];		/* for telex, modem, network...       */
	char	filename[_TEXTLEN];			/* filename                           */
	char	unparsed_filename[_TEXTLEN];	/* filename unparsed for Windows   */
	char	command[_TEXTLEN] ;			/* command for printer 1              */
	char	command2[_TEXTLEN] ;			/* command for printer 2              */
	char	command3[_TEXTLEN] ;			/* command for printer 3              */
	char	command4[_TEXTLEN] ;			/* command for printer 4              */
} DEVICE_PORT;


/* --- price result structure -------------------*/
typedef struct {
	int		preid;						/* Preis id                           */
	int		bid;							/* Buchung id                         */
	int		dlnid;						/* Dienstleistungs nehmer             */
	int		karid;						/* kosten art                         */
	int		dlttid;						/* Dienstleistung Traeger Typ         */
	int		katid;						/* Kategorie                          */
	int		rkrid;						/* Reisendertyp                       */
	int		dlaid;						/* Dienstleistungs Angebot            */
	int		tdlid;						/* Host Teildienstleistung            */
	int		dlgid;						/* Dienstleistung                     */
	int		teil;							/* Teilstueck nummer                  */
	int		kontid;						/* Kontigent                          */
	int		resflag;						/* reservation flag static or dyn...  */
	int		azeit;						/* Dl Anfangszeit                     */
	int		ezeit;						/* Dl Endzeit                         */
	double	ankaufVal;					/*      */
	double	einstandVal;				/*      */
	double	verkaufVal;					/*      */
} PRICERESULT;


/* --- commission_reduction result structure -----*/
typedef struct {
	int		komid;                  /* identification       */
	char		bez[_CHAR30+1];         /* bezeichnung          */
	int		satzart;                /* kind of com_reduc    */
	double	satzVal;                /* value                */
	double	commVal;                /* computed commission  */
} COMMISRESULT;



/*?????????------ will be replaced later by view */
typedef struct {
	int	id;
	char	anschrift[_CHAR30+1];
	char	name[_CHAR30+1];
	char	vor[_CHAR30+1];
	char	adr1[_CHAR30+1];
	char	adr2[_CHAR30+1];
	char	adr3[_CHAR30+1];
	char	plz[_CHAR10+1];
	char	ort[_CHAR30+1];
	char	land[_CHAR30+1] ;
	int	versand;
	char	tel[_CHAR30+1] ;
	char	fax[_CHAR30+1] ;
} RECIPIENT;
