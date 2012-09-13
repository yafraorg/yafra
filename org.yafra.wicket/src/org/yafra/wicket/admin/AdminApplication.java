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
package org.yafra.wicket.admin;

import org.apache.wicket.Application;
import org.apache.wicket.Page;
import org.apache.wicket.Session;
import org.apache.wicket.authroles.authentication.AbstractAuthenticatedWebSession;
import org.apache.wicket.authroles.authentication.AuthenticatedWebApplication;
import org.apache.wicket.markup.html.WebPage;
import org.apache.wicket.request.Request;
import org.apache.wicket.request.Response;
import org.yafra.utils.Logging;

/**
 * @author mwn
 * 
 */
/**
 * @author mwn
 * 
 */
public class AdminApplication extends AuthenticatedWebApplication
	{
	public static Logging yafralog = null;
	public static final String dev = "stdout";

	/**
	 * 
	 */
	public AdminApplication()
		{
		// TODO Auto-generated constructor stub
		}

	@Override
	protected void init()
		{
		super.init();
		// init values
		yafralog = new Logging();
		yafralog.setDebugFlag(true);
		yafralog.YafraDebug("org.yafra.internet - started wicket admin application", dev);
		yafralog.logInfo("org.yafra.internet - started wicket admin application");
		}

	@Override
	public Class<? extends Page> getHomePage()
		{
		// TODO Auto-generated method stub
		return Index.class;
		}

	/*
	 * generate a new session
	 */
	@Override
	public Session newSession(Request request, Response response)
		{
		AdminSession admsess = new AdminSession(request, yafralog);
		yafralog.logDebug("org.yafra.internet - new session started");
		return admsess;
		}

	public static AdminApplication get()
		{
		return (AdminApplication) Application.get();
		}

	public static Logging getLogging()
		{
		return yafralog;
		}

	/**
	 * @see org.apache.wicket.authroles.authentication.AuthenticatedWebApplication#getSignInPageClass()
	 */
	@Override
	protected Class<? extends WebPage> getSignInPageClass()
		{
		return AdminSignIn.class;
		}

	/**
	 * @see org.apache.wicket.authroles.authentication.AuthenticatedWebApplication#getWebSessionClass()
	 */
	@Override
	protected Class<? extends AbstractAuthenticatedWebSession> getWebSessionClass()
		{
		return AdminSession.class;
		}

	}
