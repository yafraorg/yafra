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
package org.yafra.server.ws;

import java.util.Random;

import javax.annotation.Resource;
import javax.jws.WebService;
import javax.xml.ws.WebServiceContext;

import org.yafra.server.ws.remote.YafraSessionRemote;

/**
 * YafraBusinessRole database object</br>
 * Attributes:
 * <ul>
 * <li>name (unique) - String
 * <li>description - String
 * <li>flag - access flags as String
 * </ul>
 * @version $Id: $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@WebService(endpointInterface = "org.yafra.server.ws.remote.YafraSessionRemote",
         serviceName = "YafraSessionRemote")
public class YafraSession implements YafraSessionRemote
{
	//webServiceContext is injected by the JAXWS API
	//@Resource private WebServiceContext wsContext;
	private Long sessionid;
	public YafraWSConfig yafraglobal = YafraWSConfig.getInstance();

	/**
	 * @see org.yafra.interfaces.IYafraSession#Login(java.lang.String, java.lang.String)
	 */
	@Override
	public boolean Login(String user, String password)
		{
		// TODO verify user within the database
		yafraglobal.logMessage("got login as " + user);
		return true;
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#Logout()
	 */
	@Override
	public void Logout()
		{
		// TODO clean up session and close

		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getLicense()
	 */
	@Override
	public String getLicense()
		{
		yafraglobal.logMessage("got license call");
		return "Version 1.0";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getMessageOfToday()
	 */
	@Override
	public String getMessageOfToday()
		{
		return "Version 1.0";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getSessionId()
	 */
	@Override
	public String getSessionId()
		{
		yafraglobal.logMessage("got sessionid call");
		return sessionid.toString();
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getVersion()
	 */
	@Override
	public String getVersion()
		{
		return "1.0";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#init()
	 */
	@Override
	public void init()
		{
		// TODO get apache cayenne context from singelton
		Random r = new Random();
		sessionid = r.nextLong();
		}

}
