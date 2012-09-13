/*HP*************************************************************** 
 * Header:    Definition of client/server message         cmdmsg.h
 *                                                                
 * Copyright: Yafra.org, Ansi C Module     
 *            Switzerland                                          
 *                                                              
 ******************************************************************/

/*--- General definitions --------------------*/
#define IPCOK						0
#define _errorFree_				0
#define _errorDataLength_		1
#define _errorSystem_			2


/*--- Fifo definitions -----------------------*/
#ifdef ps_unix
#define FIFO1	"/tmp/CMDfifo.1"
#define FIFO2	"/tmp/CMDfifo.2"
#else
#define FIFO1	"\\TEMP\\CMDfifo.1"
#define FIFO2	"\\TEMP\\CMDfifo.2"
#endif

#define PERMS       S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define UID_SEPAR   ';'

/* length of mesg_len and mesg_typ */
#define MESGHDRSIZE		(sizeof(Mesg) - MAXMESGDATA)
#define MAXMESGDATA		(4096-16)
 

typedef struct {
	int	mesg_len;                 /* #bytes in mesg_data, can be 0 or >0  */
	long	mesg_type;                /* message type, must be > 0            */
	char	mesg_data[MAXMESGDATA];   /* message text                         */ 
} Mesg; 
