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
# search path include for main MAKEFILE (library and prg)
#
# copyright: yafra.org, 2004
#
# revision system: CVS
# P   PATH
# F   FLAG
#
# you have to use PSRC PINC POBJ PRCS !!!
#

# GNU make
# Suffixes and search paths
#
.SUFFIXES:
.SUFFIXES: .c,v .c .h .o
vpath
vpath %.c $(PSRC)
vpath %.h $(PINC)
vpath %.o $(POBJ)
vpath %.c,v $(PRCS)
