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
 *  
 */
package org.yafra.tests.serverejb3;

import java.util.Iterator;
import java.util.List;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;

import org.yafra.model.MYafraUser;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;
import org.yafra.server.ejbRemote.YafraSessionRemote;
import org.yafra.utils.Logging;
import org.yafra.utils.WhichUser;

/**
 * tests - test the server.core and server.ejb3
 * it's a stand alone test against the EJB3 server components
 * 
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @version $$Id: TestEJB.java,v 1.3 2009-12-24 08:47:17 mwn Exp $$
 * @since 1.0
 * 
 */
public class TestEJB
{
	private static Logging tstlog = null;
	private static final String dev = "stdout";

	/**
	 * @param args
	 */
	public static void main(String[] args)
		{
		YafraSessionRemote yafrases = null;
		InitialContext context = null;
		tstlog = new Logging();
		tstlog.setDebugFlag(true);
		tstlog.YafraDebug("\norg.yafra.tests - start off with getting session", dev);
		
		// get servername from args
		if (args.length < 1)
			{
			tstlog.YafraDebug("\norg.yafra.tests - missing arguments (1:servername), exit", dev);
			return;
			}
		String servername = args[0];
		// for the provider URL see as examples http://openejb.apache.org/clients.html
		// openejb in tomee http://127.0.0.1:8080/tomee/ejb
		// openejb standalone ejbd ejbd://localhost:4201
		String ejbname = "http://" + servername + ":8080/tomee/ejb";

		// get login name from system
		String username = null;
		WhichUser UserID = new WhichUser();
		username = UserID.getUser();
		tstlog.YafraDebug(" - username = " + username, dev);
		try {
			Properties prop=new Properties();
			prop.put("java.naming.factory.initial", "org.apache.openejb.client.RemoteInitialContextFactory");
			prop.put("java.naming.provider.url", ejbname);
			context = new InitialContext(prop);
			tstlog.YafraDebug(" - got context", dev);
			yafrases = (YafraSessionRemote)context.lookup("YafraSessionRemote");
			tstlog.YafraDebug(" - got remote session class", dev);
			}
		catch (javax.naming.NamingException ne)
			{
			ne.printStackTrace();
			}
		yafrases.init();
		tstlog.YafraDebug(" - got remote session init", dev);
		if (yafrases.Login(username, ""))
			tstlog.YafraDebug(" - login OK", dev);
		else
			{
			tstlog.YafraDebug(" - login NOT OK - EXIT NOW", dev);
			return;
			}
		tstlog.YafraDebug(" - version got from server: " + yafrases.getVersion(),dev);
		tstlog.YafraDebug(" - sessionid got from server: " + yafrases.getSessionId(),dev);

		tstlog.YafraDebug(" - do query 1 - get all users", dev);
		doQuery1(context);
		
		tstlog.YafraDebug("\norg.yafra.tests - logout session and exit client", dev);
		yafrases.Logout();
		}

	public static void doQuery1(Context context)
		{
		MHIYafraUserRemote user = null;
		tstlog.YafraDebug(" - Get EJB user list", dev);
		try {
			user = (MHIYafraUserRemote)context.lookup("MHIYafraUserRemote");
			}
		catch (javax.naming.NamingException ne)
			{
			ne.printStackTrace();
			}
		List<MYafraUser> userlist = user.getUsers();
		Iterator<MYafraUser> it = userlist.iterator();
		while (it.hasNext())
			{
			MYafraUser a = it.next();
			tstlog.YafraDebug(String.format(" Person: ID %s, Name %s, Picturelink %s", a.getUserid(), a.getName(), a.getPicturelink()), dev);
			}
		}

}
