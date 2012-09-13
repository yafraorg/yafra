/************************************************************** 
 * header:    global PSCMD system() server include
 *                                                            
 * copyright: yafra.org      
 **************************************************************/

/* define DEBUG information output medium */
#define MESSAGELOG stderr
#define PRGNAME "psfifo:"

#ifdef ps_unix
#define CMDLOGNAME "/tmp/CMDlog"
#else
#define CMDLOGNAME "\\TEMP\\CMDlog.txt"
#endif

/* prototypes */
int	CMDserverDaemon(int  argc, char **argv );	
void	CMDserver(int, int);
void	CMDlogOpen(void);
void	CMDlogWrite(char *);
void	CMDlogClose(void);
