/*D***********************************************************
 * modul:     SQL INTERFACE all DB access functions
 *
 * db:        INGRES RELEASE 6.4
 *
 * copyright: yafra.org, Basel, Switzerland
 *************************************************************/
#if !defined(MPDBINGRES)
#define MPDBINGRES
#undef MPDBHPSQL
#undef MPDBORACLE
#endif

#include <mpdb.h>      /* Includefile fuer die Relationalen Datenbanken */
#include <mpmain.h>    /* Includefile fuer MARCO-POLO */
#include <mpproapi.h>  /* Prototypes f�r ANSI-C */
#include <signal.h>
#include <sys/wait.h>
#include <version.h>

static char rcsid[]="$Header: /yafra/cvsroot/mapo/source/api/dbingres.sc,v 1.2 2008-11-02 19:55:48 mwn Exp $";

/* local prototyps */
static int MPAPIdb_checkstatus( void );
static int AllocateDescriptors ( void );
static int StructTest( void );

/****************************************
 * Include: kopiert die SQLCA and SQLDA
 ****************************************/
EXEC SQL INCLUDE sqlca;	 	/* Type definition for sqlca.____ */
EXEC SQL INCLUDE sqlda;	 	/* Type definition for sqlda.____ */

#define		SQL_MESSAGE	132
#define		SQL_NAME	128
#define		SQL_MAX_COL	50
#define		SQL_MAX_ROW_LEN	512
#define		SQL_MAX_ROW	50
#define		SQL_MAX_BUF	SQL_MAX_ROW_LEN*SQL_MAX_ROW
#define     SQLMEMCHUNK 102400

#define     STRIPHIGHBIT 0x7f
#define     LOC_NUM_ALLOC_DOUBLES   6333

				/* about 50K. Double is the most restrictive alignment */
#define		LOC_ALLOC_CHUNK  (LOC_NUM_ALLOC_DOUBLES * sizeof(double))

				/* Arbitrary value for allocating select list items    */
#define     LOC_ARBITRARY_SELECT_LIST_SIZE   512

#define err_ret printf

#define     MAX_USER_LENG 30
#define     MAX_STRING_LENG  16384

#define     MAX_WORK_BUF_LENG  64
#define     MAX_BUFFERSIZE 200

/* Beschreibung der SQL COMMUNICATION AREA */

EXEC SQL BEGIN DECLARE SECTION;

typedef struct {
	char arr[MAX_USER_LENG];
	int  len;
} VARCHAR1;

typedef struct {
	char arr[MAX_STRING_LENG];
	int  len;
} VARCHAR2;

/* Allgemeine Variablen der Datenbank */
VARCHAR2 dynamicCommand;   /* buffer for dynamic query was RECLENGTH+1 */
char     DBE_Name[128];           /* SQL_NAME + 1 */
char     errorMessageBuffer[2048];
char     IngresMSGbuffer[RECLENGTH];	/* Fehlermeldungen des Systems */
int      MessageNumber;	            /* Fehlernummer des Systems */

/********************************************************
 * Hostvariablen fuer den automatischen logon zu ingres
 ********************************************************/
VARCHAR1 user_name_string;  /* database name     */
VARCHAR1 dbname_string;     /* database name     */

int     Save_point;


EXEC SQL END DECLARE SECTION;

/* Declare pointers to bind and select descriptors **/
IISQLDA_TYPE(sqlda, SQLDAAA, 1);
typedef struct sqlda SQLDA;

SQLDA *selectDP = (SQLDA *)0;
SQLDA *bindDP = (SQLDA *)0;

/*******************************
 * Ingres forward declarations
 *******************************/
extern SQLDA *sqlald();
extern void   sqlprc();
extern void   sqlnul();

/*********************************
 * Globale Variablen fuer Ingres
 *********************************/
int    ingresPrecision;
int    ingresScale;
int    ingresNullOk;
short  ingresIndicator;


/* include def_table struct */
#include <mpdbglob.h>


/**************************************************************/
/* SQL globals                                                */
/**************************************************************/
extern unsigned char logging_sql;
extern unsigned char logging_sqltm;

char            logbuffer[RECLAENGE];
time_t          starttime;
unsigned int    trxcount;




/**************************************************************/
/* Function:  open db                                         */
/*                                                            */
/* Parameter: db path and name                                */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_connect(char *DBname, char *username, char *password)
{
	int  status = (int) NO_ERROR;

#ifdef DEBUG
	/*
	* rh erweitert 18.3.1994
	* Testet ob die def_table-Strukturen stimmen.
	*/
	status = StructTest();
#endif

/***************************************
	EXEC SQL CONNECT :DBname;
****************************************/

/*!!! for testing only */
	EXEC SQL CONNECT mapo;

	status = MPAPIdb_checkstatus();
	if (logging_sql)
		{
		(void)sprintf(logbuffer, "OPEN DB %s", DBE_Name);
		MPlog(_LOGSQL, status, logbuffer, __FILE__);
		}

	return( status );
}

/**************************************************************/
/* Function:  release db and check sql state                  */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_release(void)
{
	int status = (int) NO_ERROR;

	EXEC SQL COMMIT;
	EXEC SQL DISCONNECT;
	status = MPAPIdb_checkstatus();

	if (logging_sql)
	{
		(void)sprintf(logbuffer, "CLOSE DB %s - NUMBER OF TRX: %d",
		              DBE_Name, trxcount);
		MPlog(_LOGSQL, status, logbuffer, __FILE__);
	}

	return( status );
}


/**************************************************************/
/* Function:  start a db transaction                          */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_begintrx(int isolationlevel, int priority)
{
	int status = (int) NO_ERROR;
	extern unsigned int trxcount;
	extern time_t starttime;


	status = MPAPIdb_checkstatus();
	if (logging_sql)
	{
		trxcount++;
		starttime = time(NULL);
		MPlog(_LOGSQL, status, "BEGIN TRANSACTION", __FILE__);
	}

	return( status );
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
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
void MPAPIdb_committrx(void)
{
	int status = (int) NO_ERROR;

	EXEC SQL COMMIT WORK;
	status = MPAPIdb_checkstatus();
	if (logging_sql)
	{
		char textbuf[_RECORDLEN];
		sprintf (textbuf, "END TRANSACTION - TRANSACTION TIME: %f SECONDS",
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
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
void MPAPIdb_rollbacktrx(void)
{
	extern time_t starttime;
	int status=(int)MPSQL_OK;

	EXEC SQL ROLLBACK WORK;

	status = MPAPIdb_checkstatus();
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
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_setsavepoint(int *save_point)
{
	/*******************
	* Local variables
	*******************/

	int status = (int) NO_ERROR;

	EXEC SQL SAVEPOINT Save_point;
	status = MPAPIdb_checkstatus();
	*save_point = Save_point;

	if (logging_sql)
	{
		MPlog(_LOGSQL, status, "SAVEPOINT SET", __FILE__);
	}

	return( status );
}


/**************************************************************/
/* Function:  delete work back to the next savepoint          */
/*                                                            */
/* Parameter: savepoint                                       */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_rollbacksavepoint(int *save_point )
{
	int status = (int) NO_ERROR;

	Save_point = *save_point;
	EXEC SQL ROLLBACK WORK TO Save_point;
	status = MPAPIdb_checkstatus();

	if (logging_sql)
	{
		MPlog(_LOGSQL, status, "ROLLBACK", __FILE__);
	}

	return( status );
}


/*F***********************************************************
 * Function:  commit a sql command to db and put the data     
 *            to the global memory
 *                                                            
 * Parameter: void                                            
 * Return:    ERROR / NO_ERROR                                
 *************************************************************/
int MPAPIdb_sqlquery(int table_nr, char **dataTargetPtr, char *queryString,
       int  *queryCount, unsigned long *datalen, unsigned long *alloclen )
{
	unsigned int querySize = 0;

	int    sqlStatus     = (int) NO_ERROR;
	int 	 currentOffset = (int)0;		/* Offset into output buffer */
	int 	 fetchCount    = (int)0;		/* Loop counter for copying data */
	size_t fetchSize     = (size_t)0;	/* size of data retrieved */
	size_t dataSize      = (size_t)0;	/* total size of converted data */
	size_t allocsize     = (size_t)0;   /* memory to allocate */

	short  tempShort  = (short)0;
	int    tempInt    = (int)0;
	long   tempLong   = (long)0L;
	double tempDouble = (double)0.0;
	float  tempFloat  = (float)0.0;
	long   longa = (long)0L, longb = (long)0L;	/* used for swapping doubles. */

#ifdef DEBUG
/*###################### debug begin ######*/
int aaa, aai;
for (aai = aaa = 0; aai < def_table[table_nr].sqln; aai++)
	aaa += def_table[table_nr].elements[aai].leng;
if (def_table[table_nr].sqlrowlen != aaa)
	{
	printf("table=[%s], sqlrowlen=%d, sum=%d",def_table[table_nr].name,
	       def_table[table_nr].sqlrowlen,aaa);
	printf("  ungleich !!\n");
	}
/* printf("tablenr: %d sqlstring: %s\n\n", table_nr, queryString); */
/*###################### debug end ######*/
#endif

	/*****************************************
	* If dataTargetPtr = (char **)0, then this
	* is not a query, this is a major bug.
	*****************************************/
	if ( dataTargetPtr == (char **) 0 )
		return(-1);

	/*****************************************************************
	* Copy the query string to the dynamicCommand VARCHAR structure
	*****************************************************************/
	querySize = strlen( queryString );
	if ( queryString[querySize - 1] == ';' )
		{		
		queryString[querySize - 1] = '\0';
		querySize--;
		}

	(void)memset( dynamicCommand.arr, 0x00, MAX_STRING_LENG );
	(void)memcpy( (char *) dynamicCommand.arr, (char *)queryString, querySize );
	dynamicCommand.len = querySize;

	/********************************
	* Allocate the bind descriptor
	********************************/
	if ( AllocateDescriptors() == -1 )
		return( -1 );
	bindDP->sqln = def_table[table_nr].sqln;

	/*************************
	* Prepare the sql query.
	*************************/
	EXEC SQL PREPARE SQL_QUERY FROM :dynamicCommand.arr;
	sqlStatus = MPAPIdb_checkstatus();
	if ( sqlStatus != (int) NO_ERROR )
		return( sqlStatus );

	/******************************
	* Declare a dynamic cursor.
	* This may not be necessary.
	******************************/
	EXEC SQL DECLARE dynam_cursor CURSOR FOR SQL_QUERY;
	sqlStatus = MPAPIdb_checkstatus();
	if ( sqlStatus != (int) NO_ERROR )
		return( sqlStatus );

	EXEC SQL DESCRIBE SQL_QUERY INTO selectDP;
	sqlStatus = MPAPIdb_checkstatus();
	if ( sqlStatus != (int) NO_ERROR )
		return( sqlStatus );

	/*********************************************************
	* If bindDP->sqld < 0, then there is a mismatch between
	* the requested and actual SLI's.
	*********************************************************/
	if ( bindDP->sqld < 0 )
		{
		sprintf( errorMessageBuffer,
		         "Too many bind variables: bindDP->sqld = %d, sqlcode = %d\n",
		         bindDP->sqld, sqlca.sqlcode );
		(void) MPAPIdb_checkstatus();
		return( sqlca.sqlcode );
		}

	/**************************************
	* Reset bindDP->sqln to bindDP->sqld
	**************************************/
	bindDP->sqln = bindDP->sqld;

	/********************
	* Open the cursor.
	********************/
	EXEC SQL OPEN dynam_cursor USING DESCRIPTOR bindDP;
	sqlStatus = MPAPIdb_checkstatus();
	if ( sqlStatus != (int) NO_ERROR )
		return( sqlStatus );

	/*************************************
	* Init queryCount and datalen to zero
	**************************************/
	*queryCount = (int)0;
	*datalen = 0;

	/*****************************
	* Describe the select list.
	*****************************/
	EXEC SQL DESCRIBE SQL_QUERY INTO selectDP;
	sqlStatus = MPAPIdb_checkstatus();
	if ( sqlStatus != (int) NO_ERROR )
		return( sqlStatus );

	/******************************************
	* If selectDP->sqld < 0, then there are
	* more select list items than asked for.
	******************************************/
	if ( selectDP->sqld < 0 )
		{
		sprintf( errorMessageBuffer,
		         "Too many select-list items. selectDP->sqld: %d, sqlcode: %d\n", 
		         selectDP->sqld, sqlca.sqlcode );
		(void) MPAPIdb_checkstatus();
		return( sqlca.sqlcode );
		}

	/*****************************************************
	* Reset requested to actual # of select list items.
	*****************************************************/
  	selectDP->sqln = selectDP->sqld;

	/******************
	* start for loop
	******************/
	for (fetchCount = 0; fetchCount < selectDP->sqld; fetchCount++)
		{
		/*********************************************************
		* The switch sets the length of the data type.
		* selectDP->sqltype is a pointer to an array of shorts.
		*********************************************************/
		switch( abs(selectDP->sqlvar[fetchCount].sqltype) )
			{
			/*************
			* Char Type
			*************/
			case IngresCharType:
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_CHA_TYPE);
				break;

			/****************
			* VarChar Type
			****************/
			case IngresVarCharType:
				/* Konvertiert von Varchar zu Char */
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_CHA_TYPE);
				break;

			/************
			* Int Type
			************/
			case IngresIntType:
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_INT_TYPE);
				selectDP->sqlvar[fetchCount].sqllen = (short)sizeof(int);
				break;

			/*************
			* Date Type
			*************/
			case IngresDateType:
				/* Konvertiert von Date zu Char */
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_CHA_TYPE);
				selectDP->sqlvar[fetchCount].sqllen = (short)IISQ_DTE_LEN;
				break;

			/**************
			* Float Type
			**************/
			case IngresFloatType:
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_FLT_TYPE);
				break;

			/**************
			* Money Type
			**************/
			case IngresMoneyType:
				/* Konvertiert von Money zu Double */
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_FLT_TYPE);
				selectDP->sqlvar[fetchCount].sqllen = (short)sizeof(double);
				break;

			/*******************
			* Tablefield Type
			*******************/
			case IngresTableType:
				selectDP->sqlvar[fetchCount].sqltype = abs(IISQ_CHA_TYPE);
				break;

			/***********************************
			* defualt = unbekannter DatenType
			***********************************/
			default:
				err_ret("Bad value %d for data type detected (bind descriptor).\n\
				Data descriptor element %d value %d\n",
				selectDP->sqlvar[fetchCount].sqltype & STRIPHIGHBIT,
				fetchCount, def_table[table_nr].elements[fetchCount].typ );
				return( -1 );
				break;
			} /* end switch */
		} /* end for loop */

	/*****************************************
	* Now, fetch the data. This loop breaks
	* when sqlca.sqlcode = MPSQL_END_OF_TABLE is reached.
	*****************************************/
	while(sqlca.sqlcode != MPSQL_END_OF_TABLE)
		{
		EXEC SQL FETCH dynam_cursor USING DESCRIPTOR selectDP;
		sqlStatus = MPAPIdb_checkstatus();
		if ( sqlStatus != (int) NO_ERROR )
			{
			if ( sqlStatus == (int)NO_DATA_FOUND )
				{
				sqlStatus = (int)0;
				break;
				}
			else
				return( sqlStatus );
			}
		else if ( sqlca.sqlcode == (int) MPSQL_END_OF_TABLE )
			break;

		/* if there are no columns go to the next fetch */
		if (selectDP->sqld <= (int)0) /* selectDP->sqld is number of columns */
			continue;

		/**************************************************
		* Process select list values. 
		* Calculate the fetched size, allocate memory,
		* and copy data into the buffer. This assumes
		* the columns are specified in the same order as
		* the goal structure in the calling function.
		**************************************************/

		/**********************************************
		* Increment the number of records retrieved.
		**********************************************/
		(*queryCount)++;

		/**********************************
		* Allocate more space if needed.
		**********************************/
		allocsize = (size_t)(*queryCount) * (size_t)def_table[table_nr].sqlrowlen;
		if (allocsize > (size_t)*alloclen)
			*dataTargetPtr = (char *)MPalloc((void *)*dataTargetPtr, alloclen,
			          SQLMEMCHUNK, allocsize, sizeof(char));

		/************************************************
		* Working column by column,
		* sum the lengths of the fetched data, and
		* copy the data. Note that Ingres seems
		* to present everything as a character string.
		*
		* make loop over def_table.sqln instead of
		* selectDP->sqld ! In Ingres def_table.sqln HAS
		* NOT TO BE THE SAME AS selectDP->sqld, because
		* of the NULLIND fields !
		************************************************/
		for (fetchCount = 0; fetchCount < def_table[table_nr].sqln; fetchCount++)
			{
			ingresIndicator = *selectDP->sqlvar[fetchCount].sqlind;
			switch( def_table[table_nr].elements[fetchCount].typ )
				{
				case DB_CHAR:
					/***************************************************************
					* The length is the size in selectDP->sqlvar[fetchCount].sqldata
					****************************************************************/
					fetchSize = (size_t) ((selectDP->sqlvar[fetchCount].sqllen <
					            def_table[table_nr].elements[fetchCount].leng) ?
					            selectDP->sqlvar[fetchCount].sqllen :
					            def_table[table_nr].elements[fetchCount].leng );

					/**************************************************
					* dataSize should always be incremented by
					* the size specified in the dataMap, so that
					* the structure expected by the calling function
					* is properly set up.
					**************************************************/
					dataSize += def_table[table_nr].elements[fetchCount].leng;
					if ( ingresIndicator != SQLNULL )
						{
						(void)memcpy((void *) (*dataTargetPtr + currentOffset ),
						               (void *) selectDP->sqlvar[fetchCount].sqldata,
						               fetchSize );
						(*dataTargetPtr)[currentOffset +
						                selectDP->sqlvar[fetchCount].sqllen] = '\0';
						}
					else
						{
						(void)memset((void *)(*dataTargetPtr + currentOffset),
						            NULL, fetchSize);
						}

					/*******************************************
					* Current Offset should be incremented by
					* the amound specified in the dataMap.
					*******************************************/
					currentOffset += def_table[table_nr].elements[fetchCount].leng;
					break;

				case DB_SHORT:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;
					if ( ingresIndicator != SQLNULL )
						{
						(void)memcpy( (void *)&tempShort,
						        selectDP->sqlvar[fetchCount].sqldata,
						        selectDP->sqlvar[fetchCount].sqllen );

						(void)memcpy( (void *) (*dataTargetPtr + currentOffset ),
						               (void *) &tempShort, sizeof(short) );
						}
					else
						{
						(void)memset( (void *) (*dataTargetPtr + currentOffset ),
						               0x00, fetchSize );
						}

					currentOffset += (int) fetchSize;
					break;

				case DB_INT:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;
					if ( ingresIndicator != SQLNULL )
						{
						(void)memcpy((void *)&tempInt,selectDP->sqlvar[fetchCount].sqldata,
						      selectDP->sqlvar[fetchCount].sqllen);
						(void)memcpy((void *)(*dataTargetPtr + currentOffset),
						      (void *)&tempInt, sizeof(int));
						}
					else
						{
						(void)memset((void *)(*dataTargetPtr + currentOffset), 0x00, fetchSize);
						}
					currentOffset += (int) fetchSize;
					break;

				case DB_LONG:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;
					if ( *selectDP->sqlvar[fetchCount].sqlind == SQLNULL )
						tempLong = 0L;
					else
						{
						(void)memcpy((void *)&tempLong,selectDP->sqlvar[fetchCount].sqldata,
						       selectDP->sqlvar[fetchCount].sqllen );
						} 
					(void) memcpy( (void *) (*dataTargetPtr + currentOffset ),
					               (void *) &tempLong, sizeof(long) );

					currentOffset += (int) fetchSize;
					break;

				case DB_DOUBLE:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;

					if ( *selectDP->sqlvar[fetchCount].sqlind == SQLNULL )
						tempDouble = 0L;
					else
						{
						(void)memcpy( (void *)&tempDouble,
						        selectDP->sqlvar[fetchCount].sqldata,
						        selectDP->sqlvar[fetchCount].sqllen );
						}
					(void) memcpy( (void *) (*dataTargetPtr + currentOffset ),
					               (void *) &tempDouble, sizeof(double) );
					currentOffset += (int) fetchSize;
					break;

				case DB_FLOAT:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;

					if ( *selectDP->sqlvar[fetchCount].sqlind == SQLNULL )
						tempFloat = 0L;
					else
						{
						(void)memcpy( (void *)&tempFloat,
						        selectDP->sqlvar[fetchCount].sqldata,
						        selectDP->sqlvar[fetchCount].sqllen );
						}

					(void) memcpy( (void *) (*dataTargetPtr + currentOffset ),
					               (void *) &tempFloat, sizeof(float) );

					currentOffset += (int) fetchSize;
					break;

				/************************************************************
				* bull shit ! NULL fields don't have a extra information in
            * the returning buffer of the fetch ! So, we init the memory
            * region to NULL. I need this because of HP/Allbase and I
            * think of ORACLE.
				*************************************************************/
				case DB_NULLIND:
					fetchSize=(size_t)def_table[table_nr].elements[fetchCount].leng;
					dataSize += fetchSize;
					(void)memset((void *)(*dataTargetPtr + currentOffset), NULL, fetchSize);
					currentOffset += (int)fetchSize;
					break;

				/*****************
				* date dataType IS NOT SUPPORTED YET !!
				*****************/
				case DB_DATE:
					sprintf( errorMessageBuffer, "%s\t",
					         selectDP->sqlvar[fetchCount].sqldata );
					break;

				default:
					err_ret("Bad value %d for data type detected(select descriptor).\n",
					        def_table[table_nr].elements[fetchCount].typ);
					return( -1 );
					break;
				}	/* end switch type of column */
			} /* end of columns for loop */
      
		if (sqlStatus != MPSQL_OK)
			*queryCount = (int) 0;
		} /* end of fetch while loop */

	/*****************************************
	* Note that memory is never free'd, but
	* reused next time around, to prevent
	* breaking it up into unusable chunks.
	*****************************************/

	/**************************
	* Close cursor and exit.
	**************************/
	EXEC SQL CLOSE dynam_cursor;

	*datalen = (unsigned long)dataSize;

	return(sqlStatus);
}


/**************************************************************/
/* Function:  commit RDBMS command                            */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
int MPAPIdb_sqlcommand(char *command_string, int *anzahl)
{
	/*******************
	* Local variables
	*******************/

	int SqlStatus = MPSQL_OK;
	time_t aclock;
	int status=(int)MPSQL_OK;
	int querySize = 0;
	char logtext[_RECORDLEN];

	/* init anzahl to zero */
	*anzahl = 0;

	if (logging_sql)
	{
		aclock = time(NULL);
	}

	querySize = strlen(command_string);
	if ( command_string[querySize - 1] == ';' )
	{
		command_string[querySize - 1] = '\0';
		querySize--;
	}

	(void)memset( dynamicCommand.arr, 0x00, 16384 );
	(void)memcpy( (char *) dynamicCommand.arr, (char *)command_string, querySize );
	dynamicCommand.len = querySize;

	/*SqlStatus = dCOeDynamicSqlQuery( (DataDescriptorPtr)0, (char **)0,
	                                   command_string, (int *)0 );*/

	EXEC SQL EXECUTE IMMEDIATE :dynamicCommand.arr;

	status = MPAPIdb_checkstatus();
	if (status == (int)MPSQL_OK)
	{
		/*
		* This field holds the number of rows processed
		* by the most recently executed SQL statement.
		*/

		*anzahl = (int)sqlca.sqlerrd[2];
	}

	if (logging_sql)
	{
		sprintf(logtext, "COMMAND EXECUTION TIME IS %f SECONDS",
		        (difftime(time(NULL), aclock)));
		MPlog(_LOGSQL, status, logtext, __FILE__);
		MPlog(_LOGSQL, status, command_string, __FILE__);
	}

	return( SqlStatus );
}

















/*SF***********************************************************/
/* Function:  check sql state                                 */
/*                                                            */
/* Parameter: void                                            */
/* Return:    ERROR / NO_ERROR                                */
/**************************************************************/
static int check_sql_error(void);
static int MPAPIdb_checkstatus(void)
{
	int status = (int) NO_ERROR;
	int ret_status = (int) NO_ERROR;

	status = check_sql_error();
	ret_status = ( abs( status ) > abs( ret_status ) ) ? status : ret_status;

	return( ret_status );
}
static int check_sql_error( void )
{
	int  status = (int) NO_ERROR;
	char WorkBuf[MAX_WORK_BUF_LENG];
	int  MessageLength = (int)0;
	int  i = (int)0;
	char Buffer[RECLENGTH];

	if ( sqlca.sqlcode != MPSQL_OK && sqlca.sqlcode != MPSQL_END_OF_TABLE )
	{   
		EXEC SQL INQUIRE_SQL (:IngresMSGbuffer = ERRORTEXT);
		EXEC SQL INQUIRE_SQL (:MessageNumber = ERRORNO);

		MessageLength = strlen(IngresMSGbuffer);
		sqlca.sqlerrm.sqlerrmc[sqlca.sqlerrm.sqlerrml] = '\0';
		IngresMSGbuffer[MessageLength-1] = '\0';

		/*****************************************
		* Nimmt am Schluss das Tagesdatum weg !
		*****************************************/

		for ( i = MessageLength; i > 0; i-- )
		{
			if ( IngresMSGbuffer[i] == '\012' || IngresMSGbuffer[i] == '\n' )
			{
				IngresMSGbuffer[i+1] = '\0';
				break;
			}
		}

		sprintf(Buffer, "%d - %s", MessageNumber, IngresMSGbuffer);
		sprintf(sqlca.sqlerrm.sqlerrmc, "%s", Buffer);
		printf("\n%s\n", Buffer);

		return( sqlca.sqlcode );
	}

	return( status );
}


/*SF******************************************************************
 * AllocateDescriptors allocates the bind and select descriptors.
 * The values should not be hardcoded!
 ******************************************************************/
static int AllocateDescriptors ( void )
{
	/*******************
	* Local variables
	*******************/

	static long   bindFvalue   = 0L;
	static long   selectFvalue = 0L;
	int           status       = (int) NO_ERROR;
	short        *workPtr      = (short *)0;
	char         *VworkPtr     = (char *)0;
	int           i            = 0;

	if ( bindDP == (SQLDA *)0 )
	{
		bindDP = (SQLDA *)calloc((size_t)LOC_ARBITRARY_SELECT_LIST_SIZE,
		                         (size_t)IISQDA_HEAD_SIZE+(10 * IISQDA_VAR_SIZE));
		if ( bindDP == (SQLDA *)0 )
		{
			return( -1 );
		}
		bindFvalue = bindDP->sqld;
	}

	bindDP->sqln = LOC_ARBITRARY_SELECT_LIST_SIZE;
	bindDP->sqld = bindFvalue;

	if ( selectDP == (SQLDA *)0 )
	{
		selectDP = (SQLDA *)calloc((size_t)LOC_ARBITRARY_SELECT_LIST_SIZE,
		                           (size_t)IISQDA_HEAD_SIZE+(10*IISQDA_VAR_SIZE));
		if ( selectDP == (SQLDA *)0 )
		{
			return( -1 );
		}
		selectFvalue = selectDP->sqld;
		selectDP->sqln = LOC_ARBITRARY_SELECT_LIST_SIZE;

		/***************************************
		* Alloziert Platz fuer die Datenwerte
		* und die Indikatorenwerte.
		***************************************/
      
		workPtr = (short *)calloc( selectDP->sqln, sizeof( short ) );
		VworkPtr = (char *)calloc(selectDP->sqln, LOC_ARBITRARY_SELECT_LIST_SIZE);
		for ( i = 0; i < selectDP->sqln; i++ )
		{
			selectDP->sqlvar[i].sqlind = workPtr;
			workPtr += sizeof( short );
			selectDP->sqlvar[i].sqldata = VworkPtr;
			VworkPtr += LOC_ARBITRARY_SELECT_LIST_SIZE;
		}
	}

	selectDP->sqln = 100;
	selectDP->sqld = selectFvalue;

	return( status );
}


/* DEBUG: Testfunction only */
static int StructTest()
{
	FILE *fp;
	int status = (int)NO_ERROR;
	int table, elem, elemleng = 0;

	if ( (fp = fopen("/tmp/table.struct", "w")) == NULL )
		return(1);

	for (table = 0; table < (int)_GRA_VIEW; table++)
		{
		/* there are some empty fields, which we don't need to process */
		if (&def_table[table] == NULL)
			continue;
		if (def_table[table].sqln == 0)
			continue;

		elemleng = (int)0;
		for (elem = 0; def_table[table].elements[elem].leng > (int)0; elem++ )
			elemleng += def_table[table].elements[elem].leng;

		if ( def_table[table].sqlrowlen != elemleng )
			{
			status = (int)ERROR;
			fprintf(fp,"TABELLE = %-20.20s SIZEOF LENG = %4d ELEMENT LENG = %4d\n",
			        def_table[table].name, def_table[table].sqlrowlen,elemleng);
			}
		else
			{
			fprintf(fp,"TABELLE = %-20.20s SIZEOF = %4d | %4d\n",
			        def_table[table].name, def_table[table].sqlrowlen,elemleng);
			}
		}

	fclose(fp);

	return(status);
}
