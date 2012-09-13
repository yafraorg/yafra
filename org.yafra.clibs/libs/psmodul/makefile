#
# MAKEFILE for library MODUL
#
# copyright: yafra.org
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER, PS_HW
#            PS_HOSTNAME
#            PS_LOCALDRV, PS_SOFTECHDRV
#            RELAREA
#
#            BASENODE and path of corename or RELAREA
#            RELEASE  vXrX
#            ODEBUG   debug or optimize
#
# revision system: CVS
# tokens:
# P   PATH
# F   FLAG
#

CORENAME = psmodul
VER_NAME = "Yafra.org - portable LICENSE MODULE library"
RELEASE  = 1.0.0
SONAMEVER = 1

#
#--- Path definitions 
#
PBASE    = $(PSMODULLIB)
POBJ     = $(PSMODULLIBO)
PSLIBINC = $(YAFRAINC)
PSLIB    = $(YAFRALIBPATH)
PLIB     = $(YAFRALIBPATH)
PINC  = $(PBASE)/include
PSRC  = $(PBASE)/source
PMAN  = $(PBASE)/man

# GNU make
# searchpath
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# input/output files
#
MAKEFILE	= makefile
LINTOUT	= $(PSRC)/lint.out
TAROUT   = /tmp/lib$(CORENAME).tar
TARIN    = $(PBASE)/source/ $(PBASE)/make*


#
# defines for sourcecode/manual
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 3

#
# search path and flags for cc/ar/ld
#
include $(YAFRATOOLS)/include/libflags.mak

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_hpux)
ADDON = -Aa -D_HPUX_SOURCE +w1
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"$(TEMP)/vc.pch"
DLLDEFS = $(PS_SOFTECHDRV)$(PSRC)/hasp32b.obj $(PS_SOFTECHDRV)$(PSRC)/haspms32.obj
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC)
CFLAGS  = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
endif

#------------------------------------------------------------------------
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# rules
#
include $(YAFRATOOLS)/include/librules.mak

manpage:
	$(MANGEN) $(CMANFLAGS) $(PSRC)/psmodul.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
