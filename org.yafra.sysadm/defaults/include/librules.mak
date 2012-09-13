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
# librules.mak
#
# rules include for main library MAKEFILE
#
# copyright: yafra.org, 2004
#
# revision system: CVS
#
# standard vars:
# PSRC = source path
# PLIB = library path (binary)
# CFLAGS = compile flags
# LIBRARY = name of library
#

#
# Rules
#
all: version lib install.lib

.c,v.c:
	$(GET) $(PSRC)/$@ $(PRCS)/$^ 

ifeq ($(PS_COMPTYPE),ps_win)

$(POBJ)/%.obj: $(PSRC)/%.c
	$(CC) $(CFLAGS) -c $(PS_LOCALDRV)$<

lib: $(OBJS)
	@echo making $(LIBRARY) ...
	$(AR) -OUT:"$(PS_LOCALDRV)$(POBJ)/$(LIBRARY)" $(DLLDEFS) $(LIBOBJS)
	@echo done

$(POBJ)/$(LIBRARY): lib

else

$(OBJS): $(POBJ)/%.o: $(PSRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

lib $(POBJ)/$(LIBRARY): $(OBJS)
	@echo making $(LIBRARY) ...
ifdef OSHARED
	$(AR) $(POBJ)/$(LIBRARY) $(OBJS)
else
	$(AR) $(POBJ)/$(LIBRARY) $(OBJS)
endif
	@echo done

endif

#========================= TOOLS ====================================
version:
	$(YAFRABIN)/makeversion $(VER_NAME) $(RELEASE) > $(PSRC)/version.h

clean:
	@rm -f $(OBJS) $(POBJ)/$(LIBRARY) $(PLIB)/$(LIBRARY) $(LINTOUT)
ifdef OSHARED
	@rm -f $(POBJ)/$(LIBRARY).$(SONAMEVER)
	@rm -f $(POBJ)/$(LIBRARY).$(RELEASE)
endif

clean.obj:
	@rm -f $(OBJS)

install.lib:
ifeq ($(POBJ),$(PLIB))
	@echo "already installed"
else
ifdef OSHARED
	@$(LINKCMD) $(POBJ)/$(LIBRARY) $(POBJ)/$(LIBRARY).$(SONAMEVER)
	@$(LINKCMD) $(POBJ)/$(LIBRARY) $(POBJ)/$(LIBRARY).$(RELEASE)
endif
	@cp -f $(POBJ)/$(LIBRARY) $(PLIB)
ifdef OSHARED
	@$(LINKCMD) $(PLIB)/$(LIBRARY) $(PLIB)/$(LIBRARY).$(SONAMEVER)
	@$(LINKCMD) $(PLIB)/$(LIBRARY) $(PLIB)/$(LIBRARY).$(RELEASE)
endif
	@echo "installing $(LIBRARY) to $(PLIB)"
endif

makedep:
	@makedepend -o.o -p'$(POBJ)' $(DEFINES) $(FINCSEARCH) $(PSRC)/*.c

#
# manpage is not in this include - see main makefile
#

install.man:
	@cp -f $(PMAN)/*.$(MANSECTION) $(YAFRAMAN)/man$(MANSECTION)/.

tar:
	$(TAR) $(FTAR) $(TAROUT) $(TARIN)
	@echo "$(TAR) done"
