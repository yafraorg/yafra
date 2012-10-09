#
# MAKEFILE for all C# traveldb projects
#
# copyright: yafra.org, 2004
# responsible/autor: yafra
#
# P: PATH
# F: FLAG


#--------------------------- declarations ----------------------
VER_NAME = "travelDB tdbadmin"
RELEASE = $(YAFRAVER)$(YAFRAREL)
NAMESPACE = tdbadmin
PBASE = $(BASENODE)/org.yafra.tdb.csharp

PADMIN = $(PBASE)/tdbadmin
PBINA = $(PADMIN)/tdbadmin/bin

#--------------------- general tasks for all --------------------
default: info

all: admin install

version:
	$(YAFRABIN)/makeversioncs $(VER_NAME) $(RELEASE) $(NAMESPACE) > $(NAMESPACE)/version.cs

#--------------------------- db ------------------------------------
admin:
ifeq ($(PS_OSTYPE),ps_win)
	msbuild tdbadmin.sln /p:Configuration=Debug /p:Platform=Win32
else
	mdtool build
endif

install:
	test -d $(WORKNODE)/apps/tdbmono || mkdir $(WORKNODE)/apps/tdbmono
	@cp $(PBINA)/Debug/*.exe $(WORKNODE)/apps/tdbmono
	@cp $(PBINA)/Debug/*.dll $(WORKNODE)/apps/tdbmono
	@cp $(PADMIN)/testsuite/bin/Debug/tdbtest.exe $(WORKNODE)/apps/tdbmono

clean:
	@rm -f $(POBJA)
	@rm -f $(PBINA)

#--------------------------- info ------------------------------------
info index:
	@echo =====================
	@echo org.yafra.tdb.csharp.tdbadmin
	@echo =====================
	@echo "all:         make all travelDB"
	@echo ""
	@echo "admin:       make the admin client"
	@echo "clean:       clean all binaries and objects"
