
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
https://github.com/yafraorg/yafra/

Version 1.0-B1

Beta 1

* Before you start:
up to date information is always on:
https://sourceforge.net/apps/trac/yafra/wiki/FrameworkRelease

install the following components on your local PC
- java runtime edition 6.x
- apache openejb-3.1.2
- apache tomcat-7.0.x
- apache derby-10.x
follow the installation guides on those products to get them running (except cayenne, see later).
Make sure they are installed correctly and are running before you continue.
Make sure you have enabled some users in tomcat /conf/tomcat-users.xml

* Database generation

You have two options to generate the database. One with the pre defined script (recommended) or
doing it the developer way using Apache Cayenne Modeler (description is on the sourceforge trac wiki page).

Installation with the script:
Make sure the database server is up and running. Start the derby net server (startNetworkServer).
Start in the derby/bin directory the ij and execute:
connect 'jdbc:derby://localhost:1527/yafra;user=yafra;create=true';
copy past now the content of the yafra-db-creation.sql (in the root directoy of this distribution) into
the open ij shell, this will create the database schema.


* Steps to get ready

Start the derby net server (startNetworkServer).
Open a dos / unix shell and go to testclients/.
Run: java -jar test-coreserver.jar
Ignore the final exception but this creates the database with test data, check the output for more information

Deploy the ear file to openejb-3.1.2/apps and start the server.
Deploy the war file to tomcat through its console.

Run the other test clients.
Run the Eclipse RCP fat client.
Run the Internet application, connect to your tomcat and select the deployed war url (org.yafra.internet).

* Web Services

The web services example is based on Apache CXF 2.x and is only available as source within Eclipse, however you can export
test client and the web service server to run as standalone applications (java -jar xxxx.jar). To test drive the web services check out the
source to your eclipse.
