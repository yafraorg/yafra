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
# set current version info
#
export YAFRAVER="1.0"
export YAFRAREL="B1"

#
# setup general paths
#
export BASENODE=/work/repos/git/YafraLocalGit
export JAVANODE=/work/repos/git/YafraLocalGit
export WORKNODE=/work/yafra-runtime
export SYSADM=$BASENODE/org.yafra.sysadm
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

#
# setup include/lib path
#
export YAFRAINC=$BASENODE/org.yafra.clibs/include
export YAFRALIBS=$BASENODE/org.yafra.clibs/libs
export YAFRALIBPATH=$WORKNODE/libs
export INCX11=`$YAFRABIN/getx11inc`
export INCMOTIF=`$YAFRABIN/getmotifinc`
export LIBX11=`$YAFRABIN/getx11lib`
export LIBMOTIF=`$YAFRABIN/getmotiflib`

#
# setup control flags
#
export OMANUAL=
export OSHARED=1
export ODEBUG=1

#
# setup foundation LIBS
#
export PSSYSLIB=$YAFRALIBS/pssys
export PSMUMELIB=$YAFRALIBS/psmume
export PSIPCLIB=$YAFRALIBS/psipc
export PSSERCOMLIB=$YAFRALIBS/pssercom
export PSGUILIB=$YAFRALIBS/psgui
export PSMATRIXLIB=$YAFRALIBS/matrix
export PSMODULLIB=$YAFRALIBS/psmodul

export YAFRALIBSO=$WORKNODE/obj/libs
export PSSYSLIBO=$YAFRALIBSO
export PSIPCLIBO=$YAFRALIBSO
export PSMUMELIBO=$YAFRALIBSO
export PSSERCOMLIBO=$YAFRALIBSO
export PSMODULLIBO=$YAFRALIBSO
export PSGUILIBO=$YAFRALIBSO
export PSMATRIXLIBO=$YAFRALIBSO

#
# section: travelDB
#
#travelDB
export TDB=$BASENODE/org.yafra.tdb.classic
export TDBCS=$TDB/csharp
export TDBS=$TDB
export TDBI=$MAPOS/include
export TDBSETUP=$BASENODE/org.yafra.tdb.setup
export TDBDB=$TDBSETUP/db
export TDBO=$WORKNODE/obj/tdb

#set which database to use
export TDBMYSQL=1
#export TDBMSSQL=1
#export TDBORACLE=1
#export TDBORACLECLASSIC=1
#export TDBODBC=1

#
# add on's
#
export YAFRAADDONS=$BASENODE
export CMDSRV=$BASENODE/org.yafra.tdb.addons.cmdsrv
export PSWHAT=$BASENODE/org.yafra.tdb.addons.pswhat
export PSEDIT=$BASENODE/org.yafra.tdb.addons.psedit
export CMDSRVO=$WORKNODE/obj/addons
export PSWHATO=$WORKNODE/obj/addons
export PSEDITO=$WORKNODE/obj/addons
export TESTSUITEO=$WORKNODE/obj/testsuite

#
# depreciated
#
export MPDBMYSQL=$TDBMYSQL