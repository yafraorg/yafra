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
# libflags.mak
#
# flags include for main library MAKEFILE
#
# copyright: yafra.org, 2004
#
# revision system: CVS
# P   PATH
# F   FLAG
#

#
# flags and program definition system independent
#
MAKE = make
TARCMD = tar
TAR  = $(TARCMD) cvf
TARNEW  = $(TARCMD) cvf
TARADD  = $(TARCMD) rvf
LINT     = lint
MANGEN   = c2man
GET      = git clone
LINKCMD = ln -sf

ifdef RELAREA
FRELEASE = -DPSLICENSE
endif

#
# library name
#
ifdef OSHARED
   LIBRARY    = lib$(CORENAME).so
else
   LIBRARY    = lib$(CORENAME).a
endif

#
# LINUX
#
ifeq ($(PS_OS),ps_linux)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall -fno-strength-reduce
else
	FDEBUG = -O -fno-strength-reduce
endif
ifdef OSHARED
	FSHARED  = -fPIC -DPS_SHAREDLIB=1
	AR = gcc -shared -Wl,-soname,$(LIBRARY).$(SONAMEVER) -o
else
	AR        = ar crus
endif
FCC       = $(FDEBUG) $(FSHARED) $(FRELEASE)
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
MAKE      = make
endif

#
# SCO Unix / OpenServer
#
ifeq ($(PS_OS),ps_sco)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG
else
	FDEBUG = -O t -Za
endif
FCC   = $(FDEBUG) $(FRELEASE) -Fo$@
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
AR    = ar crus
endif

#
# HP-UX
#
ifeq ($(PS_OS),ps_hpux)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG
else
	FDEBUG = -O
endif
ifdef OSHARED
	FSHARED = +Z -DPS_SHAREDLIB=1
	AR       = ld -b -o
else
	FSHARED =
	AR       = ar crus
endif
FCC       = $(FDEBUG) $(FSHARED) $(FRELEASE)
CMANFLAGS = -P "cc -E -C -Aa -D_HPUX_SOURCE +e" \
-I$(PINC) -V -o$(PMAN) -S$(MANSECTION)
endif

#
# Windows CYGNUS GNU TOOLS
#
ifeq ($(PS_OS),ps_cygwin)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall
else
	FDEBUG = -O
endif
ifdef OSHARED
	FSHARED = -fpic -DPS_SHAREDLIB=1
	AR       = ld -b -o
else
	FSHARED =
	AR       = ar crus
endif
CC        = gcc
FCC       = $(FDEBUG) $(FSHARED) $(FRELEASE)
CMANFLAGS = -P "cc -E -C -Aa -D_HPUX_SOURCE +e" \
-I$(PINC) -V -o$(PMAN) -S$(MANSECTION)
endif


#
# Windows MinGW pure win32 GNU TOOLS
#
ifeq ($(PS_OS),ps_mingw)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall
else
	FDEBUG = -O
endif
ifdef OSHARED
	FSHARED = -fpic -DPS_SHAREDLIB=1
	AR       = ld -b -o
else
	FSHARED =
	AR       = ar crus
endif
CC        = gcc -mno-cygwin
FCC       = $(FDEBUG) $(FSHARED) $(FRELEASE)
CMANFLAGS = -P "cc -E -C -Aa -D_HPUX_SOURCE +e" \
-I$(PINC) -V -o$(PMAN) -S$(MANSECTION)
endif


#
# Microsoft Windows NT/95 Visual C
#
ifeq ($(PS_COMPTYPE),ps_win)
ifdef ODEBUG
	FDEBUG = -Od -Zi -Ge -DDEBUG -D_DEBUG
else
	FDEBUG =
endif
ifdef OSHARED
	FSHARED  = -DPS_SHAREDLIB=1
	LIBRARY  = $(CORENAME).dll
	AR       = link $(DLLADDONOBJS) -nologo -subsystem:windows -debug -dll -machine:I386
	DLLDEFS  = -implib:"$(PS_LOCALDRV)$(PLIB)/$(CORENAME).lib"
else
ifdef OUSESHARED
	FSHARED  = -DPS_SHAREDLIB=2
endif
	LIBRARY    = $(CORENAME).lib
	AR       = lib -nologo
endif
CC        = cl
FCC       = -nologo $(FDEBUG) $(FSHARED) $(FRELEASE) -DWIN32 -D_WINDOWS
MAKE      = make
LINKCMD = cp
endif
