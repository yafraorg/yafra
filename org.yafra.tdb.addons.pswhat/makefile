#
# MAKEFILE for what/ident command
#
# copyright: yafra.org
#
# shell env: PS_OS, PS_OSTYPE, PS_OSVER, PS_HW, PS_TARGET
#            RELEASE    vXrX
#            ODEBUG     debug or optimize
#
# revision system: GIT
#

CORENAME = pswhat
VER_NAME = "yafra.org - what version"
RELEASE  = 1.0.0

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM  = $(CORENAME).exe
else
ifeq ($(PS_OS),ps_cygwin)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif
endif

PBASE      = $(PSWHAT)
POBJ       = $(PSWHATO)
PSLIB      = $(YAFRALIBPATH)
PSLIBINC   = $(YAFRAINC)
PEXE       = $(YAFRAEXE)
PSRC  = $(PBASE)/source
PMAN  = $(PBASE)/man

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = 
endif

ifeq ($(PS_OS),ps_linux)
LIBS =
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS =
endif

ifeq ($(PS_OS),ps_mingw)
LIBS =
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = 
endif

#
# set input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(PSRC)/lint.out
TAROUT     = /tmp/$(PROGRAM).tar
TARIN      = $(PSRC)/* $(PBASE)/make*

#
# defines for the sourcecode
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_hpux)
ADDON    = -Ae +w1
#LD      = purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"C:/TEMP/vc.pch"
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_LOCALDRV)$(PSLIBINC)"
FLIBSEARCH  = 
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD) -subsystem:console $(FLIBSEARCH)
else
FINCSEARCH  = -I$(PSLIBINC)
FLIBSEARCH  = -L$(PSLIB)
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

$(CORENAME): all

# DO NOT DELETE THIS LINE -- make depend depends on it.
