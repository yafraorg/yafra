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
# MAKEFILE for travelDB testsuite
#
# P: PATH
# F: FLAG

#
# program and library names
#
CORENAME   = mpstruct
VER_NAME   = "MARCO POLO struct test"

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
else
PROGRAM    = $(CORENAME)
endif

#
# path/flag declarations for release or development basis(BASE) 
# the reference(REF) is used to find the RCS repository
#
PBASE   = $(TDBS)
POBJ    = $(TDBO)
PSLIBINC = $(YAFRAINC)
PSLIB   = $(YAFRALIBPATH)
PINC    = $(PBASE)/include
PLIB    = $(POBJ)
PEXE    = $(YAFRAEXE)
PSRC    = $(PBASE)/act/structtest
PMAN    = $(PBASE)/man

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
include $(TDBS)/makefile.dblib

ifeq ($(PS_OS),ps_hpux)
LIBS = -ltdbact -ltdbdb -ltdbact -ltdbdb -ltdbcommon -lpssys $(DBLIBS) -lportnls -lcl
endif

ifeq ($(PS_OS),ps_linux)
LIBS = -ltdbact -ltdbdb -ltdbcommon -lpssys $(DBLIBS)
endif

ifeq ($(PS_OS),ps_winnt)
LIBS = @ntactlibs.txt
endif

#
# set input/output files
#
MAKEFILE   = makefile
LINTOUT    = $(SOURCEPATH)/lint.out

#
# defines for the sourcecode
#
NOLOCKING  = -DNOACTLOCK
DBDEFS     = -D$(TDBDEF)
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE) -D$(PS_HW) $(DBDEFS)
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_linux)
ADDLIBS	=
ADDON		=
endif

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1
ADDLIBS	=
#CC			= purify -best-effort cc
#LD			= purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDLIBS	=
ADDON		= -W3 -Fp"$(TEMP)/vc.pch"
#CC		= bcompile
#LD	= bclink
endif

ifeq ($(PS_COMPTYPE),ps_win)
FINCSEARCH  = -I"$(PS_LOCALDRV)$(PINC)" -I"$(PS_LOCALDRV)$(PSLIBINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)
else
LDFLAGS     = $(FLD) $(ADDLIBS) -L$(PLIB) -L$(PSLIB)
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
include $(YAFRATOOLS)/include/prgrules.mak

$(CORENAME): all

# DO NOT DELETE THIS LINE -- make depend depends on it.
