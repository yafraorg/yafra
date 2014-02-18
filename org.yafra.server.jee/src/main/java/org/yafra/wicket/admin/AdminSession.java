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

import java.util.Locale;

import org.apache.cayenne.BaseContext;
import org.apache.cayenne.access.DataContext;
import org.apache.wicket.Session;
import org.apache.wicket.authroles.authentication.AuthenticatedWebSession;
import org.apache.wicket.authroles.authorization.strategies.role.Roles;
import org.apache.wicket.request.Request;
import org.yafra.utils.Logging;

/*
 * Extends WiaSession instead of WebSession to make the 
 * cheesr application work within the examples.
 */
@SuppressWarnings("serial")
public class AdminSession extends AuthenticatedWebSession
{
	private String userid = null;

	public AdminSession(Request request)
		{
		super(request);
		setLocale(Locale.ENGLISH);
		AdminApplication.getLogging().logDebug(" - internet session started with id XXXX");
		}

	public AdminSession(Request request, Logging newlog)
		{
		super(request);
		setLocale(Locale.ENGLISH);
		newlog.logDebug(" - internet session started with id XXXX");
		}

	public static AdminSession get()
		{
		return (AdminSession) Session.get();
		}

	public synchronized String getUser()
		{
		return userid;
		}

	public synchronized boolean isAuthenticated()
		{
		return (userid != null);
		}

	public synchronized void setUser(String user)
		{
		this.userid = user;
		dirty();
		}

	public DataContext getDataContext()
		{
		return (DataContext)BaseContext.getThreadObjectContext();
		}

	public Logging getLogging()
		{
		return AdminApplication.getLogging();
		}

	/**
	 * @see org.apache.wicket.authentication.AuthenticatedWebSession#authenticate(java.lang.String,
	 *      java.lang.String)
	 */
	@Override
	public boolean authenticate(final String username, final String password)
	{
		final String WICKET = "wicket";

		// Check username and password
		return WICKET.equals(username) && WICKET.equals(password);
	}

	/**
	 * @see org.apache.wicket.authroles.authentication.AbstractAuthenticatedWebSession#getRoles()
	 */
	@Override
	public Roles getRoles()
		{
		if (isSignedIn())
		{
			// If the user is signed in, they have these roles
			return new Roles(Roles.ADMIN);
		}
		return null;
		}

}
