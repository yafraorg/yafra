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
PBINA = $(PADMIN)/bin

#--------------------- general tasks for all --------------------
default: info

all: admin

version:
	$(PISOBIN)/makeversioncs $(VER_NAME) $(RELEASE) $(NAMESPACE) > $(NAMESPACE)/version.cs

#--------------------------- db ------------------------------------
admin:
ifeq ($(PS_OSTYPE),ps_win)
	devenv tdbadmin.sln /build Debug
else
	mdtool build
endif

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
