#
# MAKEFILE for library PSIPC - InterProcessCommunication
#
# copyright: yafra.org, Switzerland, 2004
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


CORENAME = psipc
VER_NAME = "Yafra.org - portable IPC library"
RELEASE  = $(YAFRAVER).$(YAFRAREL).0
SONAMEVER = $(YAFRAVER)

#
# path/flag declarations for release and develop
#
PBASE    = $(PSIPCLIB)
POBJ     = $(PSIPCLIBO)
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

#
# defines for the sourcecode
#
DEFINES   = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 3

#
# search path for includes and librarys
#
include $(YAFRATOOLS)/include/libflags.mak

ifeq ($(PS_OS),ps_mingw)
ADDON =-mno-cygwin
endif

ifeq ($(PS_OS),ps_osx)
endif

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_hpux)
ADDON = -Aa -D_HPUX_SOURCE +w1
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"C:/TEMP/vc.pch"
DLLADDONOBJS = wsock32.lib
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS = $(FCC) $(ADDON) $(DEFINES) \
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
# to do list
#
include $(YAFRATOOLS)/include/librules.mak

manpage:
	$(MANGEN) $(CMANFLAGS) $(PSRC)/client.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/read.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
