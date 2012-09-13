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

package org.yafra.wicket.admin;

import org.apache.wicket.request.mapper.parameter.PageParameters;
import org.apache.wicket.authroles.authentication.panel.SignInPanel;

/**
 * description
 *
 * @author mwn
 * @version 
 * @since 1.0
 */
public class AdminSignIn extends AdminPage
	{
	private static final long serialVersionUID = 3707541115826459016L;

	/**
	 * Construct
	 */
	public AdminSignIn()
	{
		this(null);
	}

	/**
	 * Constructor
	 * 
	 * @param parameters
	 *            The page parameters
	 */
	public AdminSignIn(final PageParameters parameters)
		{
		// That is all you need to add a logon panel to your application with rememberMe
		// functionality based on Cookies. Meaning username and password are persisted in a Cookie.
		// Please see ISecuritySettings#getAuthenticationStrategy() for details.
		add(new SignInPanel("signInPanel"));
		}

	}
