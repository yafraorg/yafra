set echo off;
rem /*******************************************************************/
rem /*                                                                 */
rem /* drop.sql                                                        */
rem /*                                                                 */
rem /* This script clear ALL tables, views, indexes, grants,           */
rem /*  sequences, functions from root schema                          */
rem /*                                                                 */
rem /* The only thing that are NOT affected are roles and users.       */
rem /*                                                                 */
rem /*                                                                 */
rem /*                                                                 */
rem /*******************************************************************/


DECLARE
  stmt VARCHAR2(255);
  cur Integer;
  ret Integer;
  ErrCnt Integer;
BEGIN
  ErrCnt := 0;
  cur := dbms_sql.open_cursor;
  FOR rec IN (SELECT OWNER, SYNONYM_NAME FROM SYS.ALL_SYNONYMS 
   WHERE TABLE_OWNER = 'ROOT'
   AND OWNER = 'PUBLIC' AND DB_LINK IS NULL)  LOOP
     stmt := 'DROP PUBLIC SYNONYM "' || rec.SYNONYM_NAME || '"';
     BEGIN
       dbms_sql.parse( cur, stmt, dbms_sql.NATIVE);
       ret := dbms_sql.execute(cur);
     EXCEPTION
       WHEN OTHERS THEN
         ErrCnt := ErrCnt + 1;
     END;
  END LOOP;

  FOR rec IN (SELECT OBJECT_NAME, OBJECT_TYPE FROM SYS.ALL_OBJECTS
   WHERE OBJECT_TYPE != 'INDEX' AND OBJECT_TYPE != 'TRIGGER'
    AND OBJECT_TYPE != 'PACKAGE BODY'
    AND OBJECT_TYPE != 'TYPE' AND OBJECT_TYPE != 'TYPE BODY'
    AND OWNER = 'ROOT' ORDER BY 2 ) LOOP
     BEGIN
		   stmt := 'DROP ' || rec.OBJECT_TYPE || ' "' || rec.OBJECT_NAME || '"';
       IF rec.OBJECT_TYPE = 'TABLE' THEN
         stmt := stmt || ' CASCADE CONSTRAINTS';
       END IF;
       dbms_sql.parse( cur, stmt, dbms_sql.NATIVE);
       ret := dbms_sql.execute(cur);
     EXCEPTION
       WHEN OTHERS THEN
         ErrCnt := ErrCnt + 1;
     END;
  END LOOP;
  FOR rec IN (SELECT OBJECT_NAME, OBJECT_TYPE FROM SYS.ALL_OBJECTS
   WHERE OBJECT_TYPE = 'TYPE'
    AND OWNER = 'ROOT' ORDER BY 2 ) LOOP
     BEGIN
		   stmt := 'DROP TYPE "' || rec.OBJECT_NAME || '" FORCE';
       dbms_sql.parse( cur, stmt, dbms_sql.NATIVE);
       ret := dbms_sql.execute(cur);
     EXCEPTION
       WHEN OTHERS THEN
         ErrCnt := ErrCnt + 1;
     END;
  END LOOP;
  FOR rec IN (SELECT JOB FROM SYS.USER_JOBS) LOOP 
     stmt := 'begin dbms_job.remove( ' || rec.Job || '); end;';
     BEGIN
       dbms_sql.parse( cur, stmt, dbms_sql.NATIVE);
       ret := dbms_sql.execute(cur);
     EXCEPTION
       WHEN OTHERS THEN
         ErrCnt := ErrCnt + 1;
     END;
  END LOOP;

  dbms_sql.close_cursor( cur);
  IF ErrCnt > 0 THEN
    raise_application_error( -20000, TO_CHAR(ErrCnt) ||
      ' Objects could not be dropped.' ||
      ' Please check your privileges.');
   END IF;
END;
/
