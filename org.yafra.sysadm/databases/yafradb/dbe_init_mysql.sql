/* drop any old database first */
DROP SCHEMA if exists yafra;

/* use the newly created database now */
/* create database root DEFAULT CHARACTER SET utf8; for UTF8 support */
create database yafra;
use yafra;
commit;

/* create root user */
CREATE USER 'yafraadmin'@'localhost' IDENTIFIED BY  'yafra';
GRANT ALL PRIVILEGES ON * . * TO  'yafraadmin'@'localhost' IDENTIFIED BY  'yafra' WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;
GRANT ALL PRIVILEGES ON  `yafraadmin\_%` . * TO  'yafraadmin'@'localhost';

commit;

/* create roles */

/* add members to the roles */
