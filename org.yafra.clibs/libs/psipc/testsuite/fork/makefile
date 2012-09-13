#
#
# MAKEFILE for TESTSUITE fork
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
CORENAME   = psfork
VER_NAME   = "yafra testsuite fork"
RELEASE = 1.0.0

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM  = $(CORENAME).exe
else
ifeq ($(PS_OS),ps_cygwin)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif
endif


#
# path/flag declarations for release or development basis(BASE) 
# the reference(REF) is used to find the RCS repository
#
PBASE     = $(PSIPCLIB)/testsuite/fork
POBJ    = $(PSSYSLIBO)
PSLIBINC = $(YAFRAINC)
PSLIB   = $(YAFRALIBPATH)
PINC    = $(PBASE)/../pserver
PLIB    = $(YAFRALIBPATH)
PEXE    = $(YAFRAEXE)
PSRC    = $(PBASE)
PMAN    = $(PBASE)/man

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_solaris)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_aix)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_cygwin)
LIBS = -lpsipc -lpssys
endif

ifeq ($(PS_OS),ps_mingw)
LIBS = -lpsipc -lpssys
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
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE) -D_POSIX_
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_linux)
endif

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1
endif

ifeq ($(PS_OS),ps_cygwin)
endif

ifeq ($(PS_OS),ps_mingw)
ADDON  = -mno-cygwin
endif

ifeq ($(PS_OS),ps_winnt)
ADDON	= -W3 -Fp"$(TEMP)/vc.pch"
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_SOFTECHDRV)$(PISOINC)" 
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)
else
FINCSEARCH  = -I$(PINC) -I$(PSLIBINC)
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) $(FINCSEARCH)
FLIBSEARCH  = -L$(PSLIB)
LDFLAGS     = $(FLD) $(FLIBSEARCH) $(ADDLIBS)
endif

#
# dependencies
#
include $(YAFRATOOLS)/include/objects.mak

#
# to do list
#
include $(YAFRATOOLS)/include/prgrules.mak

$(CORENAME): all
