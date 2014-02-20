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
package org.yafra.directclient;

import java.util.Random;

import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.access.DataContext;
import org.yafra.interfaces.IYafraSession;
import org.yafra.utils.Logging;

/**
 * YafraSession direct session</br> Implementation of a yafra session for the
 * direct client. org.yafra session SAME JVM this session is intended for non
 * EJB environment (batch, web apps without EJB, ...) against the networked
 * session we can host here all the logging stuff and context stuff
 * 
 * @version $Id: YafraDirectSession.java,v 1.3 2009-12-10 08:38:22 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class YafraDirectSession implements IYafraSession
{
	private ObjectContext yafracontext;

	private Logging log = null;

	private final String dev = "stdout";

	private Long sessionid;

	/**
	 * Default constructor. Initializes the session id
	 */
	public YafraDirectSession()
		{
		Random r = new Random();
		sessionid = r.nextLong();
		}

	@Override
	public void init()
		{
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#Login(java.lang.String,
	 *      java.lang.String)
	 */
	@Override
	public boolean Login(String User, String Pwd)
		{
		// TODO init session - get profil first and set user class
		// TODO get user from login and search if user exists in database
		logMessage(" -DS session login called");
		return true;
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getLicense()
	 */
	@Override
	public String getLicense()
		{
		logMessage(" -DS session getLicense called");
		return "Apache License 2.0 - http://www.apache.org/licenses/LICENSE-2.0";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getMessageOfToday()
	 */
	@Override
	public String getMessageOfToday()
		{
		// TODO get message from database
		logMessage(" -DS session getMessageOfToday called");
		return "No news";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getSessionId()
	 */
	@Override
	public String getSessionId()
		{
		logMessage(" -DS session getSessionId called");
		return sessionid.toString();
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#getVersion()
	 */
	@Override
	public String getVersion()
		{
		// TODO send version of database and CVS of this file
		logMessage(" -DS session getVersion called");
		return "$Id: YafraDirectSession.java,v 1.3 2009-12-10 08:38:22 mwn Exp $";
		}

	/**
	 * @see org.yafra.interfaces.IYafraSession#Logout()
	 */
	@Override
	public void Logout()
		{
		// TODO clean up and finalize logging and auditing
		logMessage(" -DS session logout called");
		}

	/**
	 * dedicated functions to direct clients - EJB version needs different
	 * approach (EJB 3.1 singleton)
	 */
	public ObjectContext getContext()
		{
		return yafracontext;
		}

	public void setContext(ObjectContext context)
		{
		yafracontext = context;
		return;
		}

	public Logging getLogging()
		{
		return log;
		}

	public void setLogging(Logging logarg)
		{
		log = logarg;
		log.YafraDebug("\norg.yafra.server.directclient - session logging started", dev);
		log.logInfo("org.yafra.server.directclient - session logging started");
		return;
		}

	public void logMessage(String message)
		{
		log.YafraDebug(message, dev);
		}
}
