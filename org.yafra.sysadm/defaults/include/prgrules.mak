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
# rules include for main program MAKEFILE
#
# copyright: yafra.org, 2004
#
# revision system: CVS
# P   PATH
# F   FLAG
#
# standard vars:
# PSRC = source path
# PRCS = RCS source path
# PLIB = library path (binary)
# PEXE = binary path (where to install)
# CFLAGS = compile flags
# PROGRAM = name of exe
# LIBS = libraries to link
# RELEASE = release string for makeversion
#

#
# Rules
#
all: version prog install

.c,v.c:
	$(GET) $(PSRC)/$@ $(PRCS)/$^ 

ifeq ($(PS_COMPTYPE),ps_win)

$(POBJ)/%.obj: $(PSRC)/%.c
	$(CC) $(CFLAGS) -c "$(PS_LOCALDRV)$<"

prog: $(OBJS)
	@echo making $(PROGRAM) ...
	$(LD) $(LDFLAGS) $(LIBOBJS) $(LIBS) -out:$(PS_LOCALDRV)$(POBJ)/$(PROGRAM)
	@echo done

$(POBJ)/$(PROGRAM): prog
else
$(OBJS): $(POBJ)/%.o: $(PSRC)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

prog $(POBJ)/$(PROGRAM): $(OBJS)
	@echo making $(PROGRAM) ...
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(POBJ)/$(PROGRAM)
	@echo done
endif

rel-prepare:
	@echo
	@echo ====== Preparing release for $(CORENAME) -------------------
	$(YAFRABIN)/relmakedir  $(RELAREA)
	$(YAFRABIN)/relmakedir  $(PBASE)
	$(YAFRABIN)/relmakedir  $(POBJ)
	$(YAFRABIN)/relmakedir  $(PEXE)
	$(YAFRABIN)/relmakedir  $(PSRC)
	$(YAFRABIN)/relmakedir  $(PMAN)
	$(YAFRABIN)/relcontrol  $(PREFSRC)
	$(YAFRABIN)/relthread   $(PREFSRC)  $(PSRC)
ifdef PINC
	$(YAFRABIN)/relmakedir  $(PINC)
	$(YAFRABIN)/relcontrol  $(PREFINC)
	$(YAFRABIN)/relthread   $(PREFINC)  $(PINC)
endif
ifdef PLIB
	$(YAFRABIN)/relmakedir  $(PLIB)
endif

rel-co:		
	@echo
	@echo ====== Building release for $(CORENAME) ----------------------------
	$(YAFRABIN)/relco  $(PREFSRC)  $(PSRC)
ifdef PINC
	$(YAFRABIN)/relco  $(PREFINC)  $(PINC)
endif

rel-target:		
	@echo
	@echo ====== making dirs for target $(PS_TARGET) -------------------
	$(YAFRABIN)/relmakedir  $(POBJ)
	$(YAFRABIN)/relmakedir  $(PEXE)
ifdef PLIB
	$(YAFRABIN)/relmakedir  $(PLIB)
endif

rel-cleanobj:
	@echo
	@echo ====== Cleaning objects for $(CORENAME) ----------------------------
	rm $(POBJ)/*

rel-cleansrc:
	@echo
	@echo ====== Cleaning source for $(CORENAME) ----------------------------
ifdef RELAREA
		rm $(PSRC)/*.c
		rm $(PSRC)/*.h
ifdef PINC
		rm $(PINC)/*.h
endif
endif

rel-clean:
	@echo
	@echo ====== Cleaning whole release $(RELEASE) for $(CORENAME) --------
ifdef RELAREA
		rm -rf $(RELAREA)
endif

#========================= TOOLS ====================================
version:
	$(YAFRABIN)/makeversion $(VER_NAME) $(RELEASE) > $(PSRC)/version.h

clean:
	@rm -f $(OBJS) $(POBJ)/$(PROGRAM) $(LINTOUT)

clean.obj:
	@rm -f $(OBJS)

dos:
	$(MKDOS) $(CORENAME)

install:
ifeq ($(POBJ),$(PEXE))
	@echo "already installed"
else
	@cp -f $(POBJ)/$(PROGRAM) $(PEXE)
	@echo "installing $(PROGRAM) to $(PEXE)"
endif

makedep:
	@makedepend -o.o -p'$(POBJ)' $(DEFINES) $(FINCSEARCH) $(PSRC)/*.c


#
# manpage is not in this include - see main makefile
#

install.man:
	@cp -f $(PMAN)/*.$(MANSECTION) $(PISOMAN)/man$(MANSECTION)/.

tar:
	$(TAR) $(FTAR) $(TAROUT) $(TARIN)
	@echo "$(TAR) done"
