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
# GENERIC system environment
#

# some more ls aliases
set -o vi
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# global umask rw rw r (002)
#umask 002

# display with ssh should be empty or set to :0.0
#export DISPLAY=:0.0

# set standard language only if you want the system default overwritten
#export LANG=C.iso88591
#export LC_ALL=C.iso88591
#export LC_MESSAGES=C.iso88591

# JAVA stuff
export JDK_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_60.jdk/Contents/Home
export JAVA_HOME=$JDK_HOME

# ANDROID stuff
export ADK_HOME=/work/android/android-sdk-macosx

#export PATH=$PATH:$ADK_HOME/tools:$ADK_HOME/platform-tools

#
# setup general yafra.org paths
#
export BASENODE=/work/repos
export JAVANODE=$BASENODE/yafra-java
export TDBNODE=$BASENODE/yafra-tdb-c
export YAFRADB=$BASENODE/yafra-database
export WORKNODE=/work/yafra-runtime
export SYSADM=$BASENODE/yafra/org.yafra.sysadm
export YAFRATOOLS=$SYSADM/defaults/shellscripts
export YAFRABIN=$SYSADM/defaults/scripts
export YAFRADOC=$WORKNODE/doc
export YAFRAMAN=$WORKNODE/man
export YAFRAEXE=$WORKNODE/bin
    
export PATH=$PATH:$YAFRABIN:$YAFRAEXE:$YAFRATOOLS


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
