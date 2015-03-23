#-------------------------------------------------------------------------------
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
#-------------------------------------------------------------------------------
#
# Author:       Administrator
#
# Purpose:      Generic environment setup independend of system
#-------------------------------------------------------------------------------

#
# setup general paths
#
export BASENODE=/work/repos/git
export JAVANODE=$BASENODE/yafra-java
export TDBNODE=$BASENODE/yafra-tdb-c
export YAFRADB=$BASENODE/yafra-database
export WORKNODE=/work/yafra-runtime
export SYSADM=$BASENODE/yafra/org.yafra.sysadm
export YAFRATOOLS=$SYSADM/defaults
export YAFRABIN=$SYSADM/defaults/scripts
export YAFRADOC=$WORKNODE/doc
export YAFRAMAN=$WORKNODE/man
export YAFRAEXE=$WORKNODE/bin
    
export PATH=$PATH:$YAFRABIN:$YAFRAEXE


#
# setup system
#
export PS_TARGET=`$YAFRABIN/gettarget`
export PS_OSTYPE=`$YAFRABIN/getostype`
export PS_OS=`$YAFRABIN/getos`
export PS_OSVER=`$YAFRABIN/getosver`
export PS_COMPTYPE=$PS_OSTYPE
export PS_HW=`$YAFRABIN/gethardware`
export PS_HOSTNAME=`$YAFRABIN/getserver`
export HARDWARE=$PS_HW
