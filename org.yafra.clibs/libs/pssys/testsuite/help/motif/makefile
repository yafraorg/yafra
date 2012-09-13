#
#
# MAKEFILE for MarcoPolo graphical user interface (xUI/xGR)
#
# copyright: Yafra.org
#
# shell env: OSVERSION 7 or 8 for HP-UX Version
#            PS_HW  HPUX400, HPUX700, PCUNIX, IBMAIX, IMBRT, DEC, SUNOS
#            SERVERNAME Name of the server (Mips, T400, Turbo, Tech)
#            BASENODE  /users/softech
#            RELEASE vXrX
#            FOPTIONS debug or optimize
#
#
# revision system: RCS
#
# P: PATH
# F: FLAG

#
# program and library names
#
CORENAME   = tsthelp
VER_NAME   = "PISO Testsuite X11 OSF/Motif"

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif

#
# path/flag declarations for release or development basis(BASE) 
# the reference(REF) is used to find the RCS repository
#
PREF    = $(PSSYSLIB)/testsuite/help/motif
PSLIBINC = $(PISOINC)
PSLIB    = $(PISOTESTLIBPATH)
PBASE     = $(PREF)
PINC      = $(PBASE)
PSRC      = $(PBASE)
POBJ	   = $(PSSYSLIBO)
PEXE = /work/bin

# GNU make
# set the vpath and suffixes
#
include $(PISOTOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = -lpssys -lXm -lXt -lX11
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -lpssys -lXm -lXpm -lXt -lXext -lX11
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS = -lpssys -lXm -lXpm -lXt -lXext -lX11
endif

ifeq ($(PS_OS),ps_mingw)
LIBS = -lpssys -lXm -lXpm -lXt -lXext -lX11
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = @ntlibs.txt
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
include $(PISOTOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_cygwin)
endif

ifeq ($(PS_OS),ps_mingw)
ADDON = -mno-cygwin
endif

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1
ADDLIBS	= -L$(PISOTESTLIBPATH) -L$(PISOLIBPATH)
#CC			= purify -best-effort cc
#LD			= purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDON		= -W3 -Fp"$(PS_LOCALDRV)/temp/vc.pch"
endif

ifeq ($(PS_OS),ps_winnt)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" \
 -I"$(PS_LOCALDRV)$(INCX11)" -I"$(PS_SOFTECHDRV)$(PISOINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)

else

LDFLAGS     = $(FLD) $(ADDLIBS) -L$(LIBMOTIF) -L$(LIBX11) -L$(PSLIB)
FINCSEARCH  = -I$(PINC) -I$(INCMOTIF) -I$(INCX11)  -I$(PSLIBINC)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
endif

#
# dependencies
#
include $(PISOTOOLS)/include/objects.mak

#
# to do list
#
include $(PISOTOOLS)/include/prgrules.mak

$(CORENAME): all

# DO NOT DELETE THIS LINE -- make depend depends on it.
