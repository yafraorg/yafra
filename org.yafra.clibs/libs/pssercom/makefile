#
# MAKEFILE for serial communication library
#
# copyright: yafra.org, Switzerland, 2004
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
# P   PATH
# F   FLAG
#

CORENAME    = pssercom
VER_NAME    = "Yafra.org - portable serial communication library"
RELEASE  = 1.0.0
SONAMEVER = 1
OSHARED=

#
#--- Path definitions 
#
PBASE    = $(PSSERCOMLIB)
POBJ     = $(PSSERCOMLIBO)
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
ADDON =
endif

ifeq ($(PS_OS),ps_hpux)
ADDON	= -Aa -D_HPUX_SOURCE
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"C:/TEMP/vc.pch"
DLLADDONOBJS =
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
endif

#
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# Rules
#
include $(YAFRATOOLS)/include/librules.mak

manpage:
	$(MANGEN) $(CMANFLAGS) $(PSRC)/fax.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/mdm_io.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/mdm_lock.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/mdm_port.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
