#
# MAKEFILE for psedit command
#
# copyright: yafra.org, 2004
#
# shell env: PS_OS
#            BASENODE   path to git repo
#            RELEASE    vXrX
#            FOPTIONS   debug or optimize
#
#

CORENAME = psedit
VER_NAME = "network editor version"
RELEASE  = "1.0.0"

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM  = $(CORENAME).exe
else
ifeq ($(PS_OS),ps_cygwin)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif
endif

PBASE      = $(PSEDIT)
PLIB       = $(YAFRALIBPATH)
PEXE       = $(YAFRAEXE)
PSRC       = $(PBASE)
POBJ       = $(PSEDITO)
PRCS       = $(PSRC)/RCS

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_linux)
LIBS = -lXm -lXpm -lXt -lX11 -lXext
endif

ifeq ($(PS_OS),ps_hpux)
LIBS =  -lXm -lXt -lX11
endif

ifeq ($(PS_OS),ps_mingw)
LIBS = -L/usr/X11R6/lib -lXm -lXpm -lXt -lX11 -lXext -lSM -lICE
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS = -L/usr/X11R6/lib -lXm -lXpm -lXt -lX11 -lXext -lSM -lICE
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = /NODEFAULTLIB Xm.lib Xt.lib sm.lib ice.lib X11.lib cnts.lib socket.lib
endif

#
# set input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(PSRC)/lint.out

#
# defines for the sourcecode
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_hpux)
ADDON    = -Aa -D_HPUX_SOURCE
#LD         = purify -best-effort cc
#LD         = purecov -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
FINCSEARCH  = -I"$(PS_LOCALDRV)$(YAFRAINC)" -I"$(PS_LOCALDRV)$(INCX11)"
FLIBSEARCH  = 
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD) -entry:mainCRTStartup -subsystem:windows $(FLIBSEARCH)
else
FINCSEARCH  = -I$(YAFRAINC) -I$(INCX11) -I$(INCMOTIF)
FLIBSEARCH  = -L$(YAFRATESTLIBPATH) -L$(YAFRALIBPATH)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
LDFLAGS     = $(FLD) $(FLIBSEARCH)
endif

#
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# rules
#
include $(YAFRATOOLS)/include/prgrules.mak
