#
# MAKEFILE for program psserver
#
# copyright: yafra.org, Switzerland, 2004
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER, PS_HW, PS_TARGET
#            PS_HOSTNAME
#            PS_LOCALDRV, PS_SOFTECHDRV
#
#            BASENODE and path of corename or RELAREA
#            RELEASE  vXrX
#            ODEBUG   debug or optimize
#
#            PSLIBREL      release number of current PISO global libs and incs
#            PSLIBPATH     path to released binaries of PISO global libs
#            PSLIBINCPATH  path to released PISO global includes
#
# revision system: CVS
#
# P: PATH
# F: FLAG

CORENAME   = psserver
VER_NAME   = "psserver"
RELEASE    = 1.0.1

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
else
ifeq ($(PS_OS),ps_cygwin)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif
endif

#
# This is where we are storing the project files
#
PBASE   = $(PSIPCLIB)/testsuite/psserver
POBJ    = $(PSSYSLIBO)
PSLIBINC = $(YAFRAINC)
PSLIB   = $(YAFRALIBPATH)
PINC    = $(PBASE)
PLIB    = $(YAFRLIBPATH)
PEXE    = $(YAFRAEXE)
PSRC    = $(PBASE)
PMAN    = $(PBASE)/man

# GNU make
# Set the vpath for source dependecies
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_solaris)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_aix)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_osx)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS = -lpsipc -lpssys
endif

# mingw with posix threads for mingw
ifeq ($(PS_OS),ps_mingw)
LIBS = -lpsipc -lpssys -lwsock32 -ladvapi32
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = @ntlibs.txt
endif

#
# input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(PSRC)/lint.out

#
# defines for source/manuals
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_hpux)
ADDON    = -Ae +w1
#CC      = purify -best-effort cc
#LD      = purify -best-effort cc
endif

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_cygwin)
ADDON  = 
endif

ifeq ($(PS_OS),ps_mingw)
ADDON  = -mno-cygwin
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"C:/TEMP/vc.pch"
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
FLIBSEARCH  = 
LDFLAGS     = $(FLD) $(FLIBSAERCH) $(ADDLIBS)

else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
FLIBSEARCH  = -L$(PSLIB)
LDFLAGS     = $(FLD) $(FLIBSEARCH) $(ADDLIBS)
endif

#
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# to do list
#
include $(YAFRATOOLS)/include/prgrules.mak

$(CORENAME): all

# DO NOT DELETE THIS LINE -- make depend depends on it.
