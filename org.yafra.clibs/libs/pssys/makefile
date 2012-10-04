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
# MAKEFILE for system command substitution library
#
# copyright: yafra.org, Switzerland
#
# shell env: PS_OSTYPE, PS_OS, PS_OSVER, PS_HW
#            PS_HOSTNAME
#            PS_LOCALDRV
#
#            BASENODE and path of corename or RELAREA
#            RELEASE  vXrX
#            ODEBUG   debug or optimize
#
# revision system: CVS
# P   PATH
# F   FLAG
#

CORENAME    = pssys
VER_NAME    = "Yafra.org - portable SYS library"
RELEASE  = $(YAFRAVER).$(YAFRAREL).0
SONAMEVER = $(YAFRAVER)

#
#--- Path definitions 
#
PBASE		= $(PSSYSLIB)
POBJ	   = $(PSSYSLIBO)
PSLIBINC = $(YAFRAINC)
PSLIB    = $(YAFRALIBPATH)
PLIB		= $(YAFRALIBPATH)
PINC  = $(PBASE)/include
PSRC	= $(PBASE)/source
PMAN	= $(PBASE)/man

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

ifeq ($(PS_OS),ps_mingw)
ADDON =-mno-cygwin
endif

ifeq ($(PS_OS),ps_cygwin)
ADDON =
endif

ifeq ($(PS_OS),ps_hpux)
ADDON	= -Aa -D_HPUX_SOURCE +w1
#CC      = purify -best-effort cc
endif

ifeq ($(PS_OS),ps_winnt)
ADDON = -W3 -Fp"C:/temp/vc.pch" -Dps_winplain
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
	$(MANGEN) $(CMANFLAGS) $(PSRC)/alloc.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/cmd_clnt.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/date.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/free.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/help.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/log.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/password.c
	$(MANGEN) $(CMANFLAGS) $(PSRC)/signal.c

# DO NOT DELETE THIS LINE -- make depend depends on it.
