/*D************************************************************/
/* project:   MARCO POLO TO                                   */
/* client:    DEMONSTRATION                                   */
/*                                                            */
/* DBMS:      ORACLE                                          */
/*            create users environment                        */
/*                                                            */
/* copyright: yafra.org, Switzerland                   */
/**************************************************************/
/* RCS Information: */
/* $Header: /yafra/cvsroot/mapo/db/oracle/Old/dbe_drop_users.sql,v 1.1 2004-03-28 22:32:26 mwn Exp $ */

/* drop everything first (including the existing MARCO POLO DB) */

drop user root cascade;
drop role mpadmin;
drop role mpuser;
drop role mpbooker;
drop role mpreadonly;
drop profile mapoprof cascade;
commit work;
