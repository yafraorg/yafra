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
# Purpose:      Environment setup for UNIX
#-------------------------------------------------------------------------------

#export DISPLAY=vmubuntu:0.0

# work environment stuff
# global umask rw rw r (002)
#umask 002
#export PATH=$PATH:/opt/insight/bin:/opt/eclipse:/opt/oracle/instantclient_11_1
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/apache2/lib:/opt/oracle/instantclient_11_1
#export DISPLAY=:0.0

# set standard language to english iso not to C, but date remains on C
#export LANG=C.iso88591
#export LC_ALL=C.iso88591
#export LC_MESSAGES=C.iso88591

# JAVA stuff
#export MOZILLA_HOME=/opt/mozilla
#export JAVA_HOME=/usr/lib/java
#export CLASSPATH=.:/usr/lib/java/lib/classes.zip:/work/java

# some more ls aliases
set -o vi
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

#
# import generic profile here
#
