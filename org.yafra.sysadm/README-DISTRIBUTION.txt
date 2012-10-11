LICENSE

Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.


DISTRIBUTION

http://www.yafra.org/
https://github.com/yafraorg/yafra/   GET YOUR LOGIN AND FORK ME NOW!

Version 1.0-B1

Beta 1

* Before you start:
you find up to date information on:
https://github.com/yafraorg/yafra/wiki

install the following components on your local PC
- java runtime edition 6.x
- apache tomee webprofile 1.0.0 into /work or c:\work
- apache cxf 2.6.1 into /work or c:\work
- apache cayenne 3.0.2 into /work or c:\work
follow the installation guides on those products to get them running (except cayenne, see later).
Make sure they are installed correctly and are running before you continue.
Make sure you have enabled some users in tomee under conf/tomcat-users.xml


* Database generation

Releases for the full yafra applications and demonstrations are available as MySQL builds. The Java Yafra part
can be available as derby standalone version. An installation script will create the databases and users in order
to run the samples or tests.


* Steps to get ready

Execute the install.sh scripts on linux or cygwin in order to install the build. A windows install.bat will install
windows specific parts.
