#
# MAKEFILE for all C# foundations
#
# copyright: yafra.org, 2004
# responsible/autor: administrator
#
# P: PATH
# F: FLAG


#--------------------------- declarations ----------------------
RELEASE = $(YAFRAVER)$(YAFRAREL)
PBASE = $(BASENODE)/org.yafra.tdb.csharp/common
PTESTS = $(PBASE)/testsuite
POBJ = $(PBASE)/bin
PBINR = $(POBJ)/Release
PBIND = $(POBJ)/Debug
POBJTEST = $(PTESTS)/bin

CMDDEBMONO=mdtool build
CMDOPTMONO=mdtool build
CMDDEBVS=msbuild.exe foundation.sln /p:Configuration=Debug /p:Platform=Win32
CMDOPTVS=msbuild.exe foundation.sln /p:Configuration=Optimize /p:Platform=Win32
CMDMONO = $(CMDDEBMONO)
CMDVS = $(CMDDEBVS)

#--------------------- general tasks for all --------------------
default: info

all: found

found:
ifeq ($(PS_OSTYPE),ps_win)
	$(CMDVS)
else
ifeq ($(PS_OS),ps_cygwin)
	$(CMDVS)
else
	$(CMDMONO)
endif
endif

run:
	mono $(POBJTEST)/Debug/ConsoleApplication1.exe

clean:
	@rm -f $(POBJ)
	@rm -f $(POBJTEST)

#--------------------------- info ------------------------------------
info index:
	@echo =====================
	@echo org.swyn.foundation
	@echo =====================
	@echo "all:         make dll and run tests"
	@echo ""
	@echo "found:       make the org.swyn.foundation library"
	@echo "run:          run tests"
	@echo "clean:       clean all binaries and objects of all libraries"
