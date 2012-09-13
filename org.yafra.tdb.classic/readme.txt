travel database classic client/server
=====================================


release v05r50
compiled release under ubuntu 8. setup done under eclipse.

release v05r51
update makefile and added "deploy" task.
updated mysql database to innodb instead of myisam

release v05r52
fixed mysql issue with out of sync and added longlong type as LONG - could be an issue on memory, did not check

release v05r53
add configuration files and xml to this project

release v05r54
changelog:
xml.c added XML tdb message - added new create / send function and embedded MPcomm into it
mpdef.h change memchunk def to (int) from long
mpnet.c add new XML functions

release v05r60
changelog:
fixed issues with DLT selection and GRA support
set A_ZEIT and E_ZEIT in mp_profil to -1 instead of 0
XML works within MPNET/MPGTK to login - nothing more

release v05r61
fixed memory issues due to new strlen's
checked usage and even made booking

open issues
============
- oracle structure
- password in file
- config not XML
- not working - texte, message, help, history, akt_detail (small issue), aktionspara (issue with structure on linux/mysql - check)
- issue with date - no date should be zero but is in some cases -1 (UNDEF)
