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
# MAKEFILE for all yafra.org ansi c libraries
#
# responsible/autor: Administrator
#


# ---- general tasks for all ----------------------------
#

MAKE = make

default: info

all: libipc libmodul libgui libmatrix libsys libsercom libmume

clean: cleanipc cleanmodul cleanmume cleanmatrix \
  cleansys cleansercom cleangui

install:
	@echo "this needs to be executed with root access!"
	cp -P $(YAFRALIBPATH)/*so* /usr/lib
	@echo "libs installed in $(YAFRALIBPATH) done"


#--------------------------- sys ------------------------------------
libsys:
	(cd $(PSSYSLIB); $(MAKE) all)

cleansys:
	(cd $(PSSYSLIB); $(MAKE) clean)

#--------------------------- ipc ------------------------------------
libipc:
	(cd $(PSIPCLIB); $(MAKE) all)

cleanipc:
	(cd $(PSIPCLIB); $(MAKE) clean)

#--------------------------- Modul ------------------------------------
libmodul:
	(cd $(PSMODULLIB); $(MAKE) all)

cleanmodul:
	(cd $(PSMODULLIB); $(MAKE) clean)

#--------------------------- Mume ------------------------------------
libmume:
	(cd $(PSMUMELIB); $(MAKE) all)

cleanmume:
	(cd $(PSMUMELIB); $(MAKE) clean)

#--------------------------- Matrix ------------------------------------
libmatrix:
	(cd $(PSMATRIXLIB); $(MAKE) all)

cleanmatrix:
	(cd $(PSMATRIXLIB); $(MAKE) clean)

#--------------------------- SerCom ------------------------------------
libsercom:
	(cd $(PSSERCOMLIB); $(MAKE) all)

cleansercom:
	(cd $(PSSERCOMLIB); $(MAKE) clean)

#--------------------------- Gui ------------------------------------
libgui:
	(cd $(PSGUILIB); $(MAKE) all)

cleangui:
	(cd $(PSGUILIB); $(MAKE) clean)

#
# info of make commands
#
info index:
	@echo =========================
	@echo Yafra.org ansi c libs
	@echo =========================
	@echo "all:         make all libraries"
	@echo ""
	@echo "libsys:      make the YAFRA transparent system library"
	@echo "libipc:      make the IPC / Berkeley Sockets library"
	@echo "libmodul:    make the license modul library"
	@echo "libmume:     make the multimedia lib (audio, image, video)"
	@echo "libsercom:   make the serialcommunication library"
	@echo "libmatrix:   make the matrix library (X11/Motif)"
	@echo "libgui:      make the small independent GUI library (Motif/MFC)"
	@echo ""
	@echo "install:         install all available libraries to /usr/lib - needs root! - use for shared libraries"
	@echo "man:         make all manfiles"
	@echo "cleanxx:     clean binaries and objects of xx library"
	@echo "clean:       clean all binaries and objects of all libraries"
