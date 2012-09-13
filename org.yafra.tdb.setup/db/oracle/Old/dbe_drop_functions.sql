set echo off;
rem /*******************************************************************/
rem /*                                                                 */
rem /* dbe_drop_functions.sql                                          */
rem /*                                                                 */
rem /*                                                                 */
rem /* This script clear all functions from root schema                */
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

  FOR rec IN (SELECT OBJECT_NAME, OBJECT_TYPE FROM SYS.ALL_OBJECTS
   WHERE OBJECT_TYPE LIKE 'FUNCTION' 
    AND OWNER = 'ROOT' ORDER BY 2 ) LOOP
     BEGIN
	 stmt := 'DROP ' || rec.OBJECT_TYPE || ' "' || rec.OBJECT_NAME || '"';
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
