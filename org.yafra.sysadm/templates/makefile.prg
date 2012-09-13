#
#  Copyright 2002 yafra.org
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# MAKEFILE for your_project
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER, PS_HW, PS_TARGET
#            PS_HOSTNAME
#            PS_LOCALDRV, PS_SOFTECHDRV
#
#            BASENODE and path of corename or RELAREA
#            RELEASE  vXrX
#            ODEBUG   debug or optimize
#
# revision system: RCS
#
# P: PATH
# F: FLAG


##
## ATTENTION !!!
## REMOVE ALL COMMENTARIES BEHIND A STATEMENT
## like CORENAME = xy  # thats the main name
## else there are white spaces in the string which makes difficulties
##

CORENAME   = xy  # thats the main name
VER_NAME   = "xy"
RELEASE    = v01r00t          # add 't' for testing, for release let 't' away

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif

#
# This is where we are storing the project files
#
PBASE   = $(xy)             # use shell var like $(VTX),$(MAPO) not CORENAME
POBJ    = $(xyO)
PSLIBINC = $(YAFRAINC)       # here are the PISO global includes for the libs
PSLIB   = $(PSLIBPATH)      # or set it to PISOLIBPATH resp. PISOTESTLIBPATH
PINC    = $(PSLIBINCPATH)   # or set it to PISOINC
PLIB    = $(POBJ)           # here are the project specific libs
PEXE    = /work/bin
PSRC    = $(PBASE)/source
PRCS    = $(PSRC)/RCS
PMAN    = $(PBASE)/man

# GNU make
# Set the vpath for source dependecies
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
ifeq ($(PS_OS),ps_hpux)
LIBS =
endif

ifeq ($(PS_OS),ps_solaris)
LIBS =
endif

ifeq ($(PS_OS),ps_aix)
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
# input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(PSRC)/lint.out

#
# defines for source/manuals
#
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_hpux)
ADDON    = -Ae +w1
ADDLIBS  =
#CC      = purify -best-effort cc
#LD      = purify -best-effort cc
endif

ifeq ($(PS_OS),ps_linux)
ADDLIBS  =
endif

ifeq ($(PS_OS),ps_cygwin)
ADDLIBS  =
endif

ifeq ($(PS_OS),ps_mingw)
ADDLIBS  =
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"$(TEMP)/vc.pch"
ADDLIBS  =
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_LOCALDRV)$(PINC)" -I"$(PS_LOCALDRV)$(PSLIBINC)" \
 -I"$(PS_LOCALDRV)$(INCX11)" -I"$(PS_LOCALDRV)$(INCMOTIF)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"

FLIBSEARCH  = -libpath:"$(PS_LOCALDRV)$(PSLIB)"
LDFLAGS     = $(FLD) $(FLIBSAERCH) $(ADDLIBS)

else

FINCSEARCH  = -I$(PINC) -I$(PSLIBINC) -I$(INCMOTIF) -I$(INCX11)
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

# DO NOT DELETE THIS LINE -- make depend depends on it.
