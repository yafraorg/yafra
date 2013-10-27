#
# MAKEFILE for cgi-bin example
#
# copyright: yafra.org, Switzerland
#
# shell env: PS_OSVER for operating system version
#            PS_HW  HPUX400, HPUX700, LINUXINTEL
#            PS_OS name of the os (ps_hpux, ps_linux, ps_winnt)
#            PS_OSTYPE type of the os (ps_unix, ps_win)
#            BASENODE  /users/softech
#            RELEASE vXrX
#            ODEBUG debug or optimize
#            OSHARED shared lib or not
#
# revision system: RCS
#
# P: PATH
# F: FLAG

#
# program and library names
#
CORENAME   = mwncgi
VER_NAME   = "yafra.org date/time Y2000 test"

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
# path/flag declarations for release or development basis(BASE) 
# the reference(REF) is used to find the RCS repository
#
PBASE	= $(PSSYSLIB)/testsuite/cgi
PSLIB    = $(YAFRALIBPATH)
PSLIBINC = $(YAFRAINC)
PLIB	= $(YAFRALIBPATH)
PSRC    = $(PBASE)
PMAN    = $(PBASE)
PINC	= $(PBASE)
POBJ	= $(PSSYSLIBO)
PEXE    = $(YAFRAEXE)

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_osx)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_mingw)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = e:\work\libs\pssys.lib
endif

#
# set input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(SOURCEPATH)/lint.out

#
# defines for the sourcecode
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_linux)
ADDLIBS	=
ADDON	=
endif

ifeq ($(PS_OS),ps_cygwin)
ADDLIBS	=
ADDON	=
endif

ifeq ($(PS_OS),ps_mingw)
ADDLIBS	=
ADDON	= -mno-cygwin
endif

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1
ADDLIBS	=
#CC			= purify -best-effort cc
#LD			= purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDLIBS	=
ADDON		= -W3 -Fp"C:/TEMP/vc.pch"
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)
else
LDFLAGS     = $(FLD) $(ADDLIBS) -L$(PLIB) -L$(PSLIB)
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
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
