#
# MAKEFILE for program psfifo - command server
#
# copyright: yafra.org, 2004
#
#            BASENODE path of corename
#            RELEASE  vXrX
#            ODEBUG   debug or optimize
#
# revision system: GitHub.com
#
# P: PATH
# F: FLAG

CORENAME   = psfifo
VER_NAME   = "psfifo"
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

PBASE   = $(CMDSRV)
POBJ    = $(CMDSRVO)
PSLIBINC = $(YAFRAINC)
PSLIB   = $(YAFRALIBPATH)
PINC    = $(PBASE)
PLIB    = $(YAFRALIBPATH)
PEXE    = $(YAFRAEXE)
PSRC    = $(PBASE)/source
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

ifeq ($(PS_OS),ps_cygwin)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_mingw)
LIBS = -lpsipc -lpssys
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

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"$(TEMP)/vc.pch"
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
