#
# MAKEFILE for library PSMUME - multimedia extensions
#
# copyright: yafra.org, Switzerland
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER
#            PS_HOSTNAME
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


CORENAME = psmume
VER_NAME = "Yafra.org - portable multimedia library"
RELEASE  = $(YAFRAVER).$(YAFRAREL).0
SONAMEVER = $(YAFRAVER)

#
# path/flag declarations for release and develop
#
PBASE    = $(PSMUMELIB)
POBJ     = $(PSMUMELIBO)
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
MAKEFILE = makefile
LINTOUT  = $(PSRC)/lint.out

#
# defines for the sourcecode
#
DEFINES  = -D$(PS_OS) -D$(PS_OSTYPE) -DSYSV

#
# search path for includes and librarys
#
include $(YAFRATOOLS)/include/libflags.mak

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_hpux)
AINC = -I/opt/audio/include
ADDON = -Ae +w1 $(AINC)
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
