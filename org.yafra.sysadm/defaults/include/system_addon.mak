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
# system addons - OPTIONAL
#
# (c) yafra.org, 2004
#
# mostly this is defined in the makefile, but you can
# delete these entries there and make an include of this
# makefile
#
ifeq ($(PS_OS),linux)
ADDON =
endif

ifeq ($(PS_OS),sco)
ADDON =
endif

ifeq ($(PS_OS),ultrix)
ADDON = -YSYSTEM_FIVE
endif

ifeq ($(PS_OS),hpux)
WARNLEVEL=+w1
ADDON	= -Aa -D_HPUX_SOURCE $(WARNLEVEL)
endif

