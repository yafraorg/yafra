/**************************************************************/
/* Modul:     lock the communication port                     */
/*                                                            */
/* Copyright: Yafra.org     */
/* Autor:     Administrator, Yafra.org                     */
/**************************************************************/
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssercom/source/mdm_lock.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#ifdef ps_unix

/* Includes */
#include <pssercom.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#ifdef SVR4
#include <sys/sysmacros.h>
#include <sys/mkdev.h>
#endif

#define PATHSIZE 200
#define LockDir "/usr/spool/uucp"
 
static char	lockname[PATHSIZE];	/* Name of lock file */
static int	lockfile;		/* File descriptor of lock file */

extern int errno;

int mdm_lock(char *name)
{
  int pid;
  char buf[40];
  unsigned old_umask;


#if defined(SVR4)
  struct stat st_buf;

  stat (name, &st_buf);
  /* In System V R4 the lockfile seem's to contain major and minor number
   * of the device that is to lock.
   * I don't know the meaning of the first number '000' seem's to work :-)
   */
  sprintf (lockname, "%s/LK.000.%03u.%03u", LockDir, 
	   major(st_buf.st_rdev),
	   minor(st_buf.st_rdev));
#else
  char *name_frac;

  name_frac = strrchr (name, '/');
  if (name_frac == NULL) name_frac = name;
  else name_frac++;

  sprintf (lockname, "%s/LCK..%s", LockDir, name_frac);
#endif

  debugf ("Lockfile: %s\n", lockname);

  old_umask = umask(0);

  lockfile = open(lockname, O_RDWR|O_CREAT|O_EXCL, 0444);
  if (lockfile == -1) {
    debugf ("Can't create lock file %s\n", lockname);
    lockname[0] = '\0';	/* We don't hold a lock */
    return -1;
  }
  
  pid = getpid();
  sprintf (buf, "%10lu\n", pid);
  if (write(lockfile, buf, strlen(buf)) != strlen(buf)) {
    debugf ("Write of pid to %s failed\n", lockname);
    (void) close(lockfile);
    (void) mdm_unlock();
    return -1;
  }
  umask (old_umask);
  return 0;
}

int mdm_unlock(void)
{
  if (lockname[0] == '\0') return 0;
  
  if (lockfile != -1 && close(lockfile) != 0) {
    debugf ("Lock file close failed\n");
  }
  lockfile = -1;
  if (remove(lockname) != 0) {
    debugf ("Removing lock file %s failed", lockname);
    debugf (" with errno %d\n", errno);
    lockname[0] = '\0';
    return -1;
  }
  lockname[0] = '\0';
}

#endif
