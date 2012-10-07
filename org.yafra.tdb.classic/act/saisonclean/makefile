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
# MAKEFILE for travelDB outputs
#
# P: PATH
# F: FLAG

#
# program and library names
#
CORENAME   = mpclean
VER_NAME   = "travelDB maintenance - clean up all data related to a season"

ifeq ($(PS_OSTYPE),ps_win)
PROGRAM    = $(CORENAME).exe
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
PREF      = $(TDBS)
PBASE     = $(PREF)
PSLIBINC  = $(YAFRAINC)
PSLIB     = $(YAFRALIBPATH)
PINC      = $(PBASE)/include
PSRC      = $(PBASE)/act/saisonclean
POBJ      = $(TDBO)
PEXE      = $(YAFRAEXE)

# GNU make
# set the vpath and suffixes
#
include $(YAFRATOOLS)/include/searchpath.mak

#
# link libraries
#
include $(TDBS)/makefile.dblib

ifeq ($(PS_OS),ps_winnt)
LIBS = @ntactlibs.txt
else
LIBS = -ltdbact -ltdbdb -ltdbcommon -ltdbact -ltdbdb -ltdbcommon -lpssercom -lpssys $(DBLIBS)
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
DEFINES    = -D$(PS_OS) -D$(PS_OSTYPE)
MANSECTION = 1

#
# search path for includes and libraries
#
include $(YAFRATOOLS)/include/prgflags.mak

ifeq ($(PS_OS),ps_linux)
ADDLIBS	=
ADDON		= $(DBDEFS)
endif

ifeq ($(PS_OS),ps_cygwin)
ADDLIBS	=
ADDON		= $(DBDEFS)
endif

ifeq ($(PS_OS),ps_mingw)
ADDLIBS	=
ADDON		= $(DBDEFS)
endif

ifeq ($(PS_OS),ps_hpux)
ADDON		= -Ae +w1 $(DBDEFS)
ADDLIBS	= -L$(YAFRALIBPATH)
#CC			= purify -best-effort cc
#LD			= purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDON		= $(DBDEFS) -W3 -Fp"$(PS_LOCALDRV)/temp/vc.pch"
#CC		= bcompile
#LD	= bclink
endif

ifeq ($(PS_OS),ps_winnt)
FINCSEARCH  = -I"$(PS_LOCALDRV)$(PINC)" \
 -I"$(PS_LOCALDRV)$(INCX11)" -I"$(PS_LOCALDRV)$(YAFRAINC)"
CFLAGS      = $(FCC) $(ADDON) $(DEFINES) \
 $(FINCSEARCH) -Fo"$(PS_LOCALDRV)$(POBJ)/"
LDFLAGS     = $(FLD)

else

LDFLAGS     = $(FLD) $(ADDLIBS) -L$(POBJ) -L$(PSLIB)
FINCSEARCH  = -I$(YAFRAINC) -I$(PINC)
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

