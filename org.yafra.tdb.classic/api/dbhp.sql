/*D***********************************************************
 * modul:     SQL INTERFACE all DB access functions
 *
 * db:        HP/Allbase G.0.24
 *
 * copyright: yafra.org, Basel, Switzerland
 *************************************************************/
#if !defined(MPDBHPSQL)
#define MPDBHPSQL
#undef MPDBORACLE
#undef MPDBINGRES
#endif

#include <mpmain.h>     /* Includefile fuer MARCO-POLO */
#include <mpdb.h>       /* Includefile fuer die Relationalen Datenbanken */
#include <mpproapi.h>   /* Prototypes f�r ANSI-C */
#include <signal.h>
#include <sys/wait.h>
#include "version.h"

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/dbhp.sql,v 1.2 2008-11-02 19:55:48 mwn Exp $";

/* local prototyps */
static int MPAPIdb_checkstatus(void);

/* Include SQL headers */
EXEC SQL INCLUDE SQLCA;
EXEC SQL INCLUDE SQLDA;

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
EXEC SQL BEGIN DECLARE SECTION;
char	DBE_Name[128];		/* SQL_NAME + 1 */
char	SQLMessage[133];	/* SQL_MESSAGE + 1 */
char	DynamicCommand[2048];
int	Save_point;
EXEC SQL END DECLARE SECTION;


/* include def_table struct */
#include <mpdbglob.h>


/**************************************************************/
/* SQL globals                                                */
/**************************************************************/
extern unsigned char logging_sql;
extern unsigned char logging_sqltm;

sqlformat_type sqlfmts[SQL_MAX_COL];	/* Formatbuffer fuer Dynamic Query */
char		      DataBuffer[SQL_MAX_BUF];
char           logbuffer[_RECORDLEN];
time_t         starttime;
unsigned int   trxcount;


/**************************************************************/
/* Function:  open db                                         */
/*            user and password is not used under HP/Allbase  */
/*                                                            */
/* Parameter: db path and name                                */
/* Return:    ERROR / MPSQL_OK                                */
/**************************************************************/
int MPAPIdb_connect(char *aDBname, char *aUsername, char *aPassword)
{
	extern unsigned int trxcount;
	int status=(int)MPSQL_OK;

	trxcount = 0;

	if (aDBname == NULL)
		return(MPERROR);
	(void)strcpy(DBE_Name, aDBname);
	
	EXEC SQL CONNECT TO :DBE_Name;
	status=MPAPIdb_checkstatus();
	if (logging_sql)
		{
		(void)sprintf(logbuffer, "OPEN DB %s", DBE_Name);
		MPlog(_LOGSQL, status, logbuffer, __FILE__);
		}

	if (status == MPSQL_OK)
		{
		EXEC SQL SET USER TIMEOUT 30 SECONDS;
		status=MPAPIdb_checkstatus();
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

	EXEC SQL RELEASE;
	status=MPAPIdb_checkstatus();

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
			EXEC SQL BEGIN WORK RR;
			break;
		case SQLISOLATION_CS:
			EXEC SQL BEGIN WORK CS;
			break;
		case SQLISOLATION_RC:
			EXEC SQL BEGIN WORK RC;
			break;
		case SQLISOLATION_RU:
			EXEC SQL BEGIN WORK RU;
			break;
		default:
			EXEC SQL BEGIN WORK;
			break;
		}

	status=MPAPIdb_checkstatus();
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
			EXEC SQL SET TRANSACTION ISOLATION LEVEL RR;
			break;
		case SQLISOLATION_CS:
			EXEC SQL SET TRANSACTION ISOLATION LEVEL CS;
			break;
		case SQLISOLATION_RC:
			EXEC SQL SET TRANSACTION ISOLATION LEVEL RC;
			break;
		case SQLISOLATION_RU:
			EXEC SQL SET TRANSACTION ISOLATION LEVEL RU;
			break;
		default:
			EXEC SQL SET TRANSACTION ISOLATION LEVEL RU;
			break;
		}

	status=MPAPIdb_checkstatus();
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

	EXEC SQL COMMIT WORK;

	status=MPAPIdb_checkstatus();
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

	EXEC SQL ROLLBACK WORK;

	status=MPAPIdb_checkstatus();
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

	EXEC SQL SAVEPOINT :Save_point;

	status=MPAPIdb_checkstatus();
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
 	
	EXEC SQL ROLLBACK WORK TO :Save_point;

	status=MPAPIdb_checkstatus();
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

	if (logging_sql)
		aclock = time(NULL);

/*! pruefe auf memory ueberschreibung */
	if (query_string == NULL)
		return(MPERROR);
	strcpy(DynamicCommand, query_string);

/******* do uncomment this only for testing, else you got a lot of msgs ...
	if (DebugFlag)
		{
		(void)fprintf(stderr, "debug: %s\n\n", query_string);
		(void)fflush(stderr);
		}
*****************/


	sqlda.sqln	= def_table[table_nr].sqln;
	sqlda.sqlfmtarr	= sqlfmts;

	(void)memset((void *)DataBuffer, NULL, (size_t)SQL_MAX_ROW_LEN);
	
	EXEC SQL PREPARE SQL_QUERY FROM :DynamicCommand;

	status=MPAPIdb_checkstatus();
	ret_status=(abs(status) > abs(ret_status)) ? status : ret_status;
	if (status == (int)MPSQL_OK)
		{
		
		EXEC SQL DESCRIBE SQL_QUERY INTO sqlda;

		status=MPAPIdb_checkstatus();
		ret_status=(abs(status) > abs(ret_status)) ? status : ret_status;
		if (status == (int)MPSQL_OK && sqlda.sqld > 0)
			{
			EXEC SQL DECLARE DYNAM_CURSOR CURSOR FOR SQL_QUERY;

			if (logging_sql && logging_sqltm)
				{
				sprintf(logtext, "TIME AFTER DECLARE CURSOR IS %f SECONDS",
				        (difftime(time(NULL), aclock)));
				MPlog(_LOGSQL, status, logtext, __FILE__);
				}
			status=MPAPIdb_checkstatus();
			ret_status=(abs(status) > abs(ret_status)) ? status : ret_status;
			if (status == (int)MPSQL_OK)
				{
				sqlda.sqlbuflen	= sizeof(DataBuffer);
				sqlda.sqlnrow	= ((sqlda.sqlbuflen) / (sqlda.sqlrowlen));
				sqlda.sqlrowbuf	= (int)DataBuffer;
				*anzahl=0;
				
				EXEC SQL OPEN DYNAM_CURSOR;

				if (logging_sql && logging_sqltm)
					{
					sprintf(logtext, "TIME AFTER OPEN CURSOR IS %f SECONDS",
					        (difftime(time(NULL), aclock)));
					MPlog(_LOGSQL, status, logtext, __FILE__);
					}
				status=MPAPIdb_checkstatus();
				ret_status=(abs(status)>abs(ret_status)) ? status : ret_status;

				if (status == (int)MPSQL_OK)
					{
					current_offset = 0;
					do {
						EXEC SQL FETCH DYNAM_CURSOR USING DESCRIPTOR SQLDA;

						status=MPAPIdb_checkstatus();
						ret_status=(abs(status)>abs(ret_status)) ? status : ret_status;
						if (status != (int)MPSQL_OK)
							break;

						if (sqlda.sqlrrow > (int)0)
							{
							*anzahl += sqlda.sqlrrow;
							fetchsize = (size_t)sqlda.sqlrrow * (size_t)sqlda.sqlrowlen;
							datasize=(size_t)(*anzahl) * (size_t)sqlda.sqlrowlen;
							if (datasize > (size_t)*alloclen)
								*ptr = (char *)MPalloc((void *)*ptr, alloclen,
			                           SQLMEMCHUNK, datasize, sizeof(char));
							(void)memcpy((void *)(*ptr + current_offset),
											(void *)DataBuffer, fetchsize);
							current_offset += (int)fetchsize;
							}
						} while (sqlca.sqlcode != MPSQL_END_OF_TABLE &&
						         sqlda.sqlrrow == sqlda.sqlnrow);
					
					EXEC SQL CLOSE DYNAM_CURSOR;

					*datalen = (unsigned long)datasize;

					if (logging_sql && logging_sqltm)
						{
						sprintf(logtext, "TIME AFTER CLOSE CURSOR IS %f SECONDS",
						        (difftime(time(NULL), aclock)));
						MPlog(_LOGSQL, status, logtext, __FILE__);
						}
					status=MPAPIdb_checkstatus();
					ret_status=(abs(status)>abs(ret_status)) ? status : ret_status;
					if (ret_status != MPSQL_OK)
						{
						*datalen = (unsigned long)0;
						*anzahl = (int)0;
						}
					}
				}
			}
		}
		if (logging_sql)
			{
			sprintf(logtext, "QUERY EXECUTION TIME IS %f SECONDS",
				        (difftime(time(NULL), aclock)));
			MPlog(_LOGSQL, status, logtext, __FILE__);
			MPlog(_LOGSQL, status, query_string, __FILE__);
			}
		return(ret_status);
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
	
	EXEC SQL EXECUTE IMMEDIATE :DynamicCommand;

	/* if status is MPSQL_OK then get anzahl if possible (DELETE,UPDATE,INSERT) */
	status = MPAPIdb_checkstatus();
	if (status == (int)MPSQL_OK)
		*anzahl = sqlca.sqlerrd[2];

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
	int status = (int)MPSQL_OK;
	int ret_status = (int)MPSQL_OK;

	if (sqlca.sqlcode != MPSQL_OK && sqlca.sqlcode != MPSQL_END_OF_TABLE)
		{
		status=sqlca.sqlcode;
		do
			{

			EXEC SQL SQLEXPLAIN :SQLMessage;

			UtilMsgWrite(SQLMessage);
			} while (sqlca.sqlcode != MPSQL_OK);
		}

	ret_status=(abs(status) > abs(ret_status)) ? status : ret_status;

	return(ret_status);
}
