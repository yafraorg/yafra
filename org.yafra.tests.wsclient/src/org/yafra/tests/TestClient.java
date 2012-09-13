/*****************************************************************
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
package org.yafra.tests;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import javax.xml.ws.soap.SOAPBinding;

import org.yafra.model.MYafraUser;
import org.yafra.server.ws.remote.MHIYafraUserRemote;
import org.yafra.server.ws.remote.YafraSessionRemote;
import org.yafra.utils.Logging;
import org.yafra.utils.WhichUser;

/**
 * Test of web services</br>
 * @version $Id: $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public final class TestClient
{
	private static Logging tstlog = null;
	private static final String dev = "stdout";
  	public Service service_ys = null;
	protected static Service service_yuser = null;
	protected static Service service_ysession = null;

	/**
	 * startup application - main entrypoint
	 */
	public static void main(String[] args)
		{
		YafraSessionRemote yafrases = null;
		MHIYafraUserRemote user = null;
		
		tstlog = new Logging();
		tstlog.setDebugFlag(true);
		tstlog.YafraDebug("\norg.yafra.tests - start off with getting session", dev);

		// get login name from system
		String username = null;
		WhichUser UserID = new WhichUser();
		username = UserID.getUser();
		tstlog.YafraDebug(" - username = " + username, dev);

		// get web service yafrasession
		set_ysession("http://remote.ws.server.yafra.org/", "YafraSessionRemote", "http://localhost:9000/yafraSession");
     	yafrases = service_ysession.getPort(YafraSessionRemote.class);

     	// TODO add exception handling here
		tstlog.YafraDebug(" - got remote session class", dev);
		yafrases.init();
		tstlog.YafraDebug(" - got remote session init", dev);
		tstlog.YafraDebug(" - version got from server: " + yafrases.getVersion(),dev);
		tstlog.YafraDebug(" - sessionid got from server: " + yafrases.getSessionId(),dev);
		if (yafrases.Login(username, ""))
			tstlog.YafraDebug(" - login OK", dev);
		else
			{
			tstlog.YafraDebug(" - login NOT OK - EXIT NOW", dev);
			yafrases.Logout();
			return;
			}

		tstlog.YafraDebug(" - do query 1 - Select one user object", dev);

		set_yuser("http://remote.ws.server.yafra.org/", "MHIYafraUserRemote", "http://localhost:9000/yafraUser");
		user = service_yuser.getPort(MHIYafraUserRemote.class);

		// TODO implement data binding for MYafraUser
		//MYafraUser oneuser = user.selectUserByName("Test");
	   //tstlog.YafraDebug(oneuser.toString(), dev);
	   tstlog.YafraDebug(user.getNameFromId("jd10"), dev);
		tstlog.YafraDebug("\norg.yafra.tests - logout session and exit client", dev);
		yafrases.Logout();
    	System.exit(0);
		}

	protected static void set_ysession(String qnameurl, String qnameclass, String endpoint) {
		QName SERVICE_NAME = new QName(qnameurl, qnameclass);
		QName PORT_NAME = new QName(qnameurl, qnameclass+"Port");
		service_ysession = Service.create(SERVICE_NAME);
		service_ysession.addPort(PORT_NAME, SOAPBinding.SOAP11HTTP_BINDING, endpoint);
	}

	protected static void set_yuser(String qnameurl, String qnameclass, String endpoint) {
		QName SERVICE_NAME = new QName(qnameurl, qnameclass);
		QName PORT_NAME = new QName(qnameurl, qnameclass+"Port");
		service_yuser = Service.create(SERVICE_NAME);
		service_yuser.addPort(PORT_NAME, SOAPBinding.SOAP11HTTP_BINDING, endpoint);
	}

}
