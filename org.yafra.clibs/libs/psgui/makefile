#
# MAKEFILE for library PSGUI - generic GUI lib
#
# copyright: yafra.org, Switzerland
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER
#            PS_HOSTNAME
#            HARDWARE, PS_HW, PS_TARGET
#            PS_LOCALDRV, PS_SOFTECHDRV
#
#            BASENODE and path of corename or RELAREA
#            RELEASE   vXrX
#            FOPTIONS  debug or optimize
#
# revision system: CVS
#
# P: PATH
# F: FLAG


CORENAME = psgui
VER_NAME = "Yafra.org - portable small X11 GUI library"
RELEASE  = 1.0.0
SONAMEVER = 1

#
# path/flag declarations for release and develop
#
PBASE    = $(PSGUILIB)
POBJ     = $(PSGUILIBO)
PSLIBINC = $(YAFRAINC)
PSLIB    = $(YAFRALIBPATH)
PLIB     = $(YAFRALIBPATH)
PINC  = $(PBASE)/include
PSRC  = $(PBASE)/source
PMAN  = $(PBASE)/man


# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# set input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(PSRC)/lint.out
TAROUT   = /tmp/lib$(CORENAME).tar
TARIN    = $(PSRC)/* $(PBASE)/make* $(PINC)/*

#
# defines for the sourcecode
#
DEFINES   = -D$(PS_OS) -D$(PS_OSTYPE)

#
# search path for includes and librarys
#
include $(YAFRATOOLS)/include/libflags.mak

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_hpux)
ADDON = -Ae +w1
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"$(TEMP)/vc.pch"
endif

# set major flags
ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC) -I$(INCX11) -I$(INCMOTIF)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
endif


#
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# to do list
#
include $(YAFRATOOLS)/include/librules.mak

# DO NOT DELETE THIS LINE -- make depend depends on it.
