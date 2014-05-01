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
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @version $$Id: YafraSession.java,v 1.2 2009-12-02 20:48:51 mwn Exp $$
 * @since 1.0
 *
 * org.yafra session SAME JVM
 * this session is intended for non EJB environment (batch, web apps without EJB, ...)
 * against the networked session we can host here all the logging stuff and context stuff
 *
 * EJB session per client
 */
package org.yafra.server.ejb;

import java.util.Random;

import javax.ejb.EJB;
import javax.ejb.Remote;
import javax.ejb.Remove;
import javax.ejb.Stateful;

import org.apache.cayenne.ObjectContext;
import org.yafra.model.MYafraUser;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;
import org.yafra.server.ejbRemote.YafraSessionRemote;
import org.yafra.utils.Logging;

/**
 * @author mwn
 * Session Bean implementation class YafraSession
 */
@Stateful
@Remote(YafraSessionRemote.class)
public class YafraSession implements YafraSessionRemote
{
	@EJB private YafraConfigRemote yafraglobals;	
	@EJB private MHIYafraUserRemote mhyu;	

	private ObjectContext yafracontext = null;
	private Logging ejblog = null;
	private Long sessionid = -1L;
	
	/**
	 * Default constructor.
	 */
	public YafraSession(){	}


	/**
	 * custom constructor initialize method
	 */
	public void init()
		{
		// set all global variables
		// TODO user singleton in EJB 3.1 (geronimo 2.2)
		Random r = new Random();
		sessionid = r.nextLong();
		ejblog = yafraglobals.getLoggin();
		yafracontext = yafraglobals.getContext();
		yafraglobals.logMessage(" - initialized context and log through singleton with new session id: " + sessionid.toString());
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#Login(java.lang.String, java.lang.String)
	 */
	@Override
	public boolean Login(String User, String Pwd)
		{
		// TODO set default values for user (lang etc)
		MYafraUser user = null;
		user = mhyu.selectUser(User);
		if (user != null)
			{
			if (user.getUserid().equals(User))
				{
				ejblog.logInfo(String.format("ejb session - user from login %s and user from db %s", User, user.getUserid()));
				return true;
				}
			}
		ejblog.logError(String.format("ejb session - LOGIN FAILED - user from login %s - NO such user in database", User), null);
		return false;
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getVersion()
	 */
	@Override
	public String getVersion()
		{
		return ("$Id: YafraSession.java,v 1.2 2009-12-02 20:48:51 mwn Exp $");
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#Logout()
	 */
	@Remove
	public void Logout()
		{
		yafraglobals.logMessage("\norg.yafra.ejb - logout of session");
		ejblog.logInfo("logout of session");
		// TODO clean up and finalize logging and auditing
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getLicense()
	 */
	@Override
	public String getLicense()
		{
		return "Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getMessageOfToday()
	 */
	@Override
	public String getMessageOfToday()
		{
		// TODO get message from database
		return "No news";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getSessionId()
	 */
	@Override
	public String getSessionId()
		{
		return sessionid.toString();
		}
}
