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
# flags include for main program MAKEFILE
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


ifeq ($(PS_OS),ps_hpux)
MAKE = gmake
TAR  = gtar cvf --exclude='*,v' --exclude='RCS'
TARCMD = gtar
TARNEW  = $(TARCMD) --exclude='*,v' --exclude='RCS' -c -v -f
TARADD  = $(TARCMD) --exclude='*,v' --exclude='RCS' -r -v -f
else
MAKE = make
TAR  = tar cvf
TARCMD = tar
TARNEW  = $(TARCMD) cvf
TARADD  = $(TARCMD) rvf
endif

CC       = cc
LD       = cc
LINT     = lint
RANLIB   = ranlib
MANGEN   = c2man
GET      = co

ifdef RELAREA
FRELEASE = -DPSLICENSE
endif

#
# LINUX
#
ifeq ($(PS_OS),ps_linux)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall -fno-strength-reduce
	FLD = -g
else
	FDEBUG = -O -fno-strength-reduce
	FLD = -O
endif
FCC       = $(FDEBUG) $(FRELEASE)
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
endif

#
# SCO Unix
#
ifeq ($(PS_OS),ps_sco)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG
	FLD = -g
else
	FDEBUG = -O t -Za
	FLD = -O
endif
FCC   = $(FDEBUG) $(FRELEASE) -Fo$@
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
endif

#
# Ultrix
#
ifeq ($(PS_OS),ps_ultrix)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG
	FLD = -g
else
	FDEBUG = -O
	FLD = -O
endif
FCC   = $(FDEBUG) $(FRELEASE)
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
endif

#
# HP-UX
#
ifeq ($(PS_OS),ps_hpux)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG
	FLD = -g
else
	FDEBUG = -O
	FLD = -O
endif
ifdef OSHARED
	FSHARED = +Z -DOSHARED
else
	FSHARED =
endif

FCC       = $(FDEBUG) $(FSHARED) $(FRELEASE)
CMANFLAGS = -P "cc -E -C -Aa -D_HPUX_SOURCE +e" \
-I$(PINC) -V -o$(PMAN) -S$(MANSECTION)
endif

#
# Windows mit CYGNUS SUPPORT (GNU TOOLS)
#
ifeq ($(PS_OS),ps_cygwin)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall
	FLD = -g
else
	FDEBUG = -O
	FLD = -O
endif
CC        = gcc -I/usr/gnu/include
LD        = gcc -L/usr/gnu/lib
FCC       = $(FDEBUG) $(FRELEASE)
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
endif

#
# Windows mit MinGW pure win32 SUPPORT (GNU TOOLS)
#
ifeq ($(PS_OS),ps_mingw)
ifdef ODEBUG
	FDEBUG = -g -DDEBUG -Wall
	FLD = -g
else
	FDEBUG = -O
	FLD = -O
endif
CC        = gcc -mno-cygwin
LD        = gcc -mno-cygwin
FCC       = $(FDEBUG) $(FRELEASE)
CMANFLAGS = -P "cc -E -C" -I$(PINC) -V -i$(INCLUDE) -o$(PMAN) -S$(MANSECTION)
endif

#
# Microsoft Windows Visual C
#
ifeq ($(PS_COMPTYPE),ps_win)
ifdef ODEBUG
	FDEBUG = -Od -Zi -DDEBUG -D_DEBUG
	LDDBG = -debug
else
	FDEBUG =
	LDDBG = 
endif
ifdef OUSESHARED
	FSHARED = -DPS_SHAREDLIB=2
else
	FSHARED =
endif
CC        = cl
LD        = link
FLD       = -nologo -incremental:yes $(LDDBG) -machine:I386
FCC       = -nologo $(FDEBUG) $(FSHARED) $(FRELEASE) -DWIN32 -D_WINDOWS
MAKE      = make
endif
