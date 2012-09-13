#
#       X b a e   M a t r i x
#
# matrix OSF/Motif widget set library
#
# Autor:  Bellcore
# (c):    1992 Bell Communications Research, Inc. (Bellcore), USA
#
# Input Parameters: 
# Standard Output:  pbmlib program
#
# External shell variables
#
# PSMATRIXLIB:  where is matrix lacated

CORENAME = psmatrix
VER_NAME = "MATRIX library (c) Bellcore Xbae"
RELEASE  = 1.0.0
SONAMEVER = 1

#
# Path definitions (P....)
#
PBASE    = $(PSMATRIXLIB)
POBJ     = $(PSMATRIXLIBO)
PSLIBINC = $(YAFRAINC)
PSLIB    = $(YAFRALIBPATH)
PLIB     = $(YAFRALIBPATH)
PINC  = $(PBASE)/include
PSRC  = $(PBASE)/source
PMAN  = $(PBASE)/man

# GNU make
# searchpatch only for GNU Make
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# set input/output files
#
MAKEFILE = makefile
LINTOUT  = $(PSRC)/lint.out
TARIN    = $(PBASE)/source/* $(PBASE)/make*
TAROUT   = /tmp/lib$(CORENAME).tar

#
# defines for the sourcecode
#
DEFINES = -D$(PS_OS) -D$(PS_OSTYPE) -DSYSV
MANSECTION = 3

#
# serach path and flags for cc/ar/ld
#
include $(YAFRATOOLS)/include/libflags.mak

ifeq ($(PS_OS),ps_linux)
ADDON =
endif

ifeq ($(PS_OS),ps_hpux)
#ADDON = -Wp,-H900 -D__hpux -Dhpux -DSYSV -DMERGE -DTDUX -Dhp9000s300
ADDON =  -Aa -D_HPUX_SOURCE +w1
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"$(TEMP)/vc.pch"
DLLADDONOBJS =
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PINC)" -I"$(PS_SOFTECHDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC) -I$(INCX11) -I$(INCMOTIF)
CFLAGS   = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH) 
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
	$(MANGEN) $(CMANFLAGS) $(PSRC)/matrix.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
