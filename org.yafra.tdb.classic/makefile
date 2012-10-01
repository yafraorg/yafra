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
# MAKEFILE for travelDB
#
# copyright: yafra.org
#
# external:
#

# ---- set RELEASE and VERSION ----------------------------
#
TDBVER = "$YAFRAVER"
TDBREL = "$YAFRAREL"
RELEASE = "$YAFRAVER.$YAFRAREL"
MAKE    = make
#NICE   = nice -15

#
# ---- General make tasks ----------------------------------
#

#
# default is info
#
default: info

#
# build a whole program with all libs, etc.
#
all: printver mplib mplibxml mplibcomm mpapi mpdbi mpactlib mpact mpnet mpgui

alllibs: pslibs mplib mplibxml mplibcomm mpapi mpactlib

alldbi: mplib mpapi mpdbi

allgui: mplib mpgui

allact: mplib mpapi mpactlib mpact

alltools: psfifo psedit

printver:
	@echo =========================
	@echo travelDB release $(RELEASE)
	@echo =========================

#
# single elements
#
mpgtk:
	$(NICE) $(MAKE) -f makefile.gtk version mpgtk install RELEASE="$(RELEASE)"

mpgui:
	$(NICE) $(MAKE) -f makefile.gui version mpgui install RELEASE="$(RELEASE)"

mpdbi:
	$(NICE) $(MAKE) -f makefile.dbi version mpdbi install RELEASE="$(RELEASE)"

mpnet:
	$(NICE) $(MAKE) -f makefile.dbinet version net install RELEASE="$(RELEASE)"

#
# Libraries
#
mplib:
	$(MAKE) -f makefile.lib version lib install.lib RELEASE="$(RELEASE)" MAPOVER="$(TDBVER)"

mplibxml:
	$(MAKE) -f makefile.libxml version lib install.lib RELEASE="$(RELEASE)" MAPOVER="$(TDBVER)"

mplibcomm:
	$(MAKE) -f makefile.libcomm version lib install.lib RELEASE="$(RELEASE)" MAPOVER="$(TDBVER)"

mpapi:
	$(MAKE) -f makefile.api sql version lib install.lib RELEASE="$(RELEASE)" MAPOVER="$(TDBVER)"

mpactlib:
	$(MAKE) -f makefile.actlib version lib install.lib RELEASE="$(RELEASE)" MAPOVER="$(TDBVER)"

#
# default Aktionen fuer Kunden
#
mpact: arrkom change kapa komm pricing req saisonclean stamm statdl statdlt statkont \
	mpstruct mptest

arrkom:
	$(MAKE) -f act/arrkom/makefile all RELEASE="$(RELEASE)"

change:
	$(MAKE) -f act/change/makefile all RELEASE="$(RELEASE)"

kapa:
	$(MAKE) -f act/kapaupdate/makefile all RELEASE="$(RELEASE)"

komm:
	$(MAKE) -f act/komm/makefile all RELEASE="$(RELEASE)"

maintdlt:
	$(MAKE) -f act/maintdlt/makefile all RELEASE="$(RELEASE)"

maintmsg:
	$(MAKE) -f act/maintmsg/makefile all RELEASE="$(RELEASE)"

mainttxt:
	$(MAKE) -f act/mainttxt/makefile all RELEASE="$(RELEASE)"

pricing:
	$(MAKE) -f act/pricing/makefile all RELEASE="$(RELEASE)"

req request:
	$(MAKE) -f act/request/makefile all RELEASE="$(RELEASE)"

saisonclean:
	$(MAKE) -f act/saisonclean/makefile all RELEASE="$(RELEASE)"

stamm:
	$(MAKE) -f act/stamm/makefile all RELEASE="$(RELEASE)"

statdl:
	$(MAKE) -f act/statdl/makefile all RELEASE="$(RELEASE)"

statdlt:
	$(MAKE) -f act/statdlt/makefile all RELEASE="$(RELEASE)"

statkont:
	$(MAKE) -f act/statkont/makefile all RELEASE="$(RELEASE)"

mpstruct:
	$(MAKE) -f act/structtest/makefile all RELEASE="$(RELEASE)"

mptest:
	$(MAKE) -f act/test/makefile all RELEASE="$(RELEASE)"

#
# externals prgs/libs
#
psfifo:
	$(MAKE) -f $(CMDSRV)/makefile all

psedit:
	$(MAKE) -f $(PSEDIT)/makefile all

pslibs:
	$(MAKE) -f $(YAFRALIBS)/makefile all

#
# deploy config files
#
deploy:
ifeq ($(PS_OS),ps_linux)
	$(TDBSETUP)/config/linux/install.sh all
endif

init:
	$(YAFRATOOLS)/scripts/profile-create-dirs.sh

#
# Call this to clean the objects and binaries
#
clean:
	$(MAKE) -f makefile.lib clean
	$(MAKE) -f makefile.libcomm clean
	$(MAKE) -f makefile.libxml clean
	$(MAKE) -f makefile.api clean
	$(MAKE) -f makefile.dbi clean
	$(MAKE) -f makefile.dbinet clean
	$(MAKE) -f makefile.gui clean
	$(MAKE) -f makefile.actlib clean

cleandbi:
	$(MAKE) -f makefile.dbi clean

cleanmpnet:
	$(MAKE) -f makefile.dbinet clean

cleanact:
	$(MAKE) -f makefile.actlib clean

cleanlib:
	$(MAKE) -f makefile.lib clean
	$(MAKE) -f makefile.libcomm clean
	$(MAKE) -f makefile.libxml clean

cleanapi:
	$(MAKE) -f makefile.api clean

cleangui:
	$(MAKE) -f makefile.gui clean

cleangtk:
	$(MAKE) -f makefile.gtk clean

cleanpslibs:
	$(MAKE) -f $(PISOLIBS)/makefile clean

cleantest:
	$(MAKE) -f act/test/makefile clean


#
# info of make commands
#
info index:
	@echo =========================
	@echo travelDB make commands
	@echo =========================
	@echo "all:            make full travelDB"
	@echo "mpdbi:          make travelDB DBI daemon"
	@echo "mpgui:          make travelDB GUI"
	@echo "mpact:          make travelDB actions"
	@echo "mpnet:          make travelDB net/dbi"
	@echo ""
	@echo "alllibs:        make all libs, including ps clibs"
	@echo "actions:        req kapa statdl statdlt statkont pricing"
	@echo "tools:          mainttxtbez maintmsg maintdlt"
	@echo "info:           this text"
	@echo "deploy:         create a config directory with all config files"
	@echo "init:           init needed directories to build"
	@echo "clean(XXX):     clean obj and binaries or only (XXX)"
	@echo "tar:            make a copy of the whole travelDB source"
