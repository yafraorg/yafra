#
#
# MAKEFILE for TESTSUITE logging
#
# copyright: Yafra.org, Switzerland
#
# revision system: RCS
#
# P: PATH
# F: FLAG

#
# program and library names
#
CORENAME   = tsthasp
VER_NAME   = "PISO Testsuite tsthasp"

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif


#
# path/flag declarations for release or development basis(BASE) 
# the reference(REF) is used to find the RCS repository
#
PREF    = $(PISOTESTS)/tsthasp
ifdef RELAREA
	PBASE     = $(RELAREA)
	PINC      = $(PBASE)/include
	PSRC      = $(PBASE)/$(CORENAME)
	POBJ      = $(MAPOO)
	FINCPISO  = -I$(RELAREA)/pisoinc
	FLIBPISO  = -L$(RELAREA)/pisobin/$(PS_HW)  -L$(POBJ)
else
	PBASE     = $(PREF)
	PINC      = $(PBASE)
	PSRC      = $(PBASE)
	POBJ      = $(TESTSUITEO)
	FINCPISO  = -I$(PISOINC)
	FLIBPISO  = -L$(PISOLIBPATH) -L$(PISOTESTLIBPATH)
endif
PRCS = $(PSRC)/RCS
PEXE = /work/bin

# GNU make
# set the vpath and suffixes
#
include $(PISOTOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -lpssys
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = @ntlibs.txt
endif

#
# set input/output files
#
MAKEFILE   = makefile.gui
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

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1
ADDLIBS	= -L$(PISOTESTLIBPATH) -L$(PISOLIBPATH)
#CC			= purify -best-effort cc
#LD			= purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDON		= -W3 -Fp"$(PS_LOCALDRV)/temp/vc.pch"
#CC		= bcompile
#LD	= bclink
endif

ifeq ($(PS_OS),ps_winnt)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PISOINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)

else

LDFLAGS     = $(FLD) $(ADDLIBS) -L$(PISOTESTLIBPATH) -L$(PISOLIBPATH)
FINCSEARCH  = -I$(PINC) -I$(INCMOTIF) -I$(INCX11) $(FINCPISO)
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
