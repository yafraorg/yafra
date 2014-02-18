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
package org.yafra.interfaces;

/**
 * interface of a session logout will close session but is not part of
 * interface because of EJB3 usage with annotations
 * @version $Id: IYafraSession.java,v 1.3 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraSession
{
	/**
	 * special constructor used in J2EE environments - not used in directclient sessions (uses the standard one)
	 * 
	 * @since 1.0
	 */
	public void init();

	/**
	 * do a login within the session, first method to be executed else you will not be allowed to read further on.
	 * sets a global flag (in a singleton) to check on further calls on the server side (and on the client side if
	 * directclient is used)
	 * 
	 * @param username
	 *           user name from system
	 * @param password
	 *           the name of the role (is a unique name)
	 * @return success in login <code>true</code> or <code>false</code>
	 * @since 1.0
	 */
	public boolean Login(String User, String Pwd);

	/**
	 * do a logout within the session, opportunity to clean up environment and to flush any data
	 * 
	 * @since 1.0
	 */
	public void Logout();

	/**
	 * get the version of the server
	 * 
	 * @return version of the server as a String
	 * @since 1.0
	 */
	public String getVersion();


	/**
	 * get the message of today
	 * 
	 * @return message of today as a String
	 * @since 1.0
	 */
	public String getMessageOfToday();


	/**
	 * get the license of the server
	 * 
	 * @return license of the server as a String
	 * @since 1.0
	 */
	public String getLicense();


	/**
	 * get the session id from the server
	 * 
	 * @return session id from the server as a String
	 * @since 1.0
	 */
	public String getSessionId();
}
