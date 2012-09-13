/*D***********************************************************
 * modul:     SQL INTERFACE all DB access functions
 *
 * db:        HP/Allbase G.0.24
 *
 * copyright: yafra.org, Basel, Switzerland
 *************************************************************/
#if !defined(MPDBDUMMY)
#define MPDBDUMMY
#undef MPDBORACLE
#undef MPDBINGRES
#undef MPDBHPSQL
#undef MPDBODBC
#undef MPDBMSQL
#endif

#include <mpmain.h>     /* Includefile fuer MARCO-POLO */
#include <mpdb.h>       /* Includefile fuer die Relationalen Datenbanken */
#include <mpproapi.h>   /* Prototypes f�r ANSI-C */
#include <signal.h>
#include <sys/wait.h>
#include <version.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/dbdummy.sql,v 1.2 2008-11-02 19:55:48 mwn Exp $";

/* local prototyps */
static int MPAPIdb_checkstatus(void);

/* Include SQL headers */

/**************************************************************/
/* defines                                                    */
/**************************************************************/
#define		SQL_MESSAGE	132
#define		SQL_NAME	128
#define		SQL_MAX_COL	50
#define		SQL_MAX_ROW_LEN	512
#define		SQL_MAX_ROW	50
#define		SQL_MAX_BUF	SQL_MAX_ROW_LEN*SQL_MAX_ROW
#define		SQLMEMCHUNK  102400

/**************************************************************/
/* SQL declare section                                        */
/**************************************************************/
char	DBE_Name[128];		/* SQL_NAME + 1 */
char	SQLMessage[133];	/* SQL_MESSAGE + 1 */
char	DynamicCommand[2048];
int	Save_point;

/* include def_table struct */
#include <mpdbglob.h>


/**************************************************************/
/* SQL globals                                                */
/**************************************************************/
extern unsigned char logging_sql;
extern unsigned char logging_sqltm;

char		      DataBuffer[SQL_MAX_BUF];
char           logbuffer[_RECORDLEN];
time_t         starttime;
unsigned int   trxcount;


/**************************************************************/
/* Function:  open db                                         */
/*                                                            */
/* Parameter: db path and name                                */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_connect(char *dbe_name, char *user, char *password)
{
	extern unsigned int trxcount;
	int status=(int)MPSQL_OK;

	trxcount = 0;

	printf("debug: open DB with %s, %s, %s", dbe_name, user, password);
	
	if (logging_sql)
		{
		(void)sprintf(logbuffer, "OPEN DB %s", DBE_Name);
		MPlog(_LOGSQL, status, logbuffer, __FILE__);
		}

	return(status);
}

/**************************************************************/
/* Function:  release db and check sql state                  */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_release(void)
{
	extern unsigned int trxcount;
	int status=(int)MPSQL_OK;

	signal(SIGCLD, SIG_IGN);

	if (logging_sql)
		{
		(void)sprintf(logbuffer, "CLOSE DB %s - NUMBER OF TRX: %d", DBE_Name, trxcount);
		MPlog(_LOGSQL, status, logbuffer, __FILE__);
		}

	return(status);
}



/**************************************************************/
/* Function:  start a db transaction                          */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_begintrx(int isolationlevel, int priority)
{
	extern unsigned int trxcount;
	extern time_t starttime;
	int status=(int)MPSQL_OK;

	switch(isolationlevel)
		{
		case SQLISOLATION_RR:
			break;
		case SQLISOLATION_CS:
			break;
		case SQLISOLATION_RC:
			break;
		case SQLISOLATION_RU:
			break;
		}

	if (logging_sql)
		{
		trxcount++;
		starttime = time(NULL);
		MPlog(_LOGSQL, status, "BEGIN TRANSACTION", __FILE__);
		}

	return(status);
}


/**************************************************************/
/* Function:  set attributes of a db trx in progress          */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_settrx(int isolationlevel, int priority)
{
	int status=(int)MPSQL_OK;

	switch(isolationlevel)
		{
		case SQLISOLATION_RR:
			break;
		case SQLISOLATION_CS:
			break;
		case SQLISOLATION_RC:
			break;
		case SQLISOLATION_RU:
			break;
		}

	if (logging_sql)
		MPlog(_LOGSQL, status, "CHANGED TRANSACTION ISOLATIONLEVEL", __FILE__);

	return(status);
}


/**************************************************************/
/* Function:  write data to db and set savepoint              */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
void MPAPIdb_committrx(void)
{
	extern time_t starttime;
	int status=(int)MPSQL_OK;

	if (logging_sql)
		{
		char textbuf[_RECORDLEN];
		sprintf(textbuf, "END TRANSACTION - TRANSACTION TIME: %f SECONDS",
		        (difftime(time(NULL), starttime)));
		MPlog(_LOGSQL, status, textbuf, __FILE__);
		}

	return;
}

/**************************************************************/
/* Function:  rollback/cancel current transaction             */
/*            started by begin_transaction()                  */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
void MPAPIdb_rollbacktrx(void)
{
	extern time_t starttime;
	int status=(int)MPSQL_OK;

	if (logging_sql)
		{
		char textbuf[_RECORDLEN];
		sprintf(textbuf, "CANCEL/ROLLBACK TRANSACTION - TRANSACTION TIME: %f SECONDS",
		        (difftime(time(NULL), starttime)));
		MPlog(_LOGSQL, status, textbuf, __FILE__);
		}

	return;
}

/**************************************************************/
/* Function:  write data to db and set savepoint              */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_setsavepoint(int *save_point)
{
	int status=(int)MPSQL_OK;

	*save_point = Save_point;

	if (logging_sql)
		MPlog(_LOGSQL, status, "SAVEPOINT SET", __FILE__);

	return(status);
}

/**************************************************************/
/* Function:  delete work back to the next savepoint          */
/*                                                            */
/* Parameter: savepoint                                       */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_rollbacksavepoint(int *save_point )
{
	int status=(int)MPSQL_OK;

	Save_point = *save_point;
 	
	if (logging_sql)
		MPlog(_LOGSQL, status, "ROLLBACK", __FILE__);

	return(status);
}


/*F***********************************************************
 * Function:  commit a sql command to db and put the data     
 *            to the global memory
 *                                                            
 * Parameter: void                                            
 * Return:    ERROR / MPSQL_OK                                
 *************************************************************/
int MPAPIdb_sqlquery(int table_nr, char **ptr, char *query_string,
                   int *anzahl, unsigned long *datalen, unsigned long *alloclen)
{
	time_t aclock;
	int status=(int)MPSQL_OK;
	int current_offset, ret_status=MPSQL_OK;
	char logtext[_RECORDLEN];
	extern int DebugFlag;

	size_t fetchsize, datasize;

	*datalen = 0;

/*! pruefe auf memory ueberschreibung */
	strcpy(DynamicCommand, query_string);

/******* do uncomment this only for testing, else you got a lot of msgs ...
	if (DebugFlag)
		{
		(void)fprintf(stderr, "debug: %s\n\n", query_string);
		(void)fflush(stderr);
		}
*****************/

	(void)memset((void *)DataBuffer, NULL, (size_t)SQL_MAX_ROW_LEN);
	
	return(status);
}


/**************************************************************/
/* Function:  commit RDBMS command                            */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_sqlcommand(char *command_string, int *anzahl)
{
	time_t aclock;
	int status=(int)MPSQL_OK;
	char logtext[_RECORDLEN];

	if (logging_sql)
		aclock = time(NULL);

	/* init anzahl to zero */
	*anzahl = 0;

	/* copy SQLcommand to HOST variable */
	(void)strcpy(DynamicCommand, command_string);
	
	if (logging_sql)
		{
		sprintf(logtext, "COMMAND EXECUTION TIME IS %f SECONDS FOR %d OBJECTS",
			        (difftime(time(NULL), aclock)), *anzahl);
		MPlog(_LOGSQL, status, logtext, __FILE__);
		MPlog(_LOGSQL, status, command_string, __FILE__);
		}

	return(status);
}


/* local functions (static) */

/*SF***********************************************************/
/* Function:  check sql state                                 */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
static int MPAPIdb_checkstatus(void)
{
	int ret_status = (int)MPSQL_OK;

	return(ret_status);
}
