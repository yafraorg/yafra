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
 * @version $Id: MHIYafraUserRemote.java,v 1.3 2009-12-09 22:41:11 mwn Exp $
 * @since 1.0
 *
 * org.yafra session SAME JVM
 * this session is intended for non EJB environment (batch, web apps without EJB, ...)
 * against the networked session we can host here all the logging stuff and context stuff
 *
 * EJB3 remote interface for db.YAFRAUSER
 */
package org.yafra.server.ejbRemote;

import java.util.List;

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraUser
 * @version $Id: MHIYafraUserRemote.java,v 1.3 2009-12-09 22:41:11 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface MHIYafraUserRemote
{
	/**
	 * Insert a new user into the database
	 * 
	 * @param user
	 *           the yafra user model object
	 * @since 1.0
	 */
	public void insertUser(MYafraUser u);

	/**
	 * Update a user on the database
	 * 
	 * @param user
	 *           the yafra user model object
	 * @since 1.0
	 */
	public void updateUser(MYafraUser u);

	/**
	 * Delete the selected user in the database
	 * 
	 * @param user
	 *           the yafra user model object
	 * @since 1.0
	 */
	public void deleteUser(String id);

	/**
	 * Select one user by name
	 * 
	 * @param name
	 *           the name of the user
	 * @return the first YafraUser model object found (could be more than one)
	 * @since 1.0
	 */
	public MYafraUser selectUserByName(String name);

	/**
	 * Select one user by userid
	 * 
	 * @param userid
	 *           the unique userid of the user
	 * @return YafraUser model object
	 * @since 1.0
	 */
	public MYafraUser selectUser(String id);

	/**
	 * get all users
	 * 
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getUsers();

	/**
	 * get all users filtered by a name
	 * 
	 * @param name
	 *           the name to be filtered on
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getUsers(String name);

	/**
	 * get all users filtered by a role
	 * 
	 * @param mybr
	 *           business role model object
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getUsers(MYafraBusinessRole mybr);

	/**
	 * get business roles for userid 
	 * 
	 * @param id
	 *           the userid of the user (is a unique name)
	 * @return list of business roles assigned to userid
	 * @since 1.0
	 */
   public List<MYafraBusinessRole> getRoles(String id);

	/**
	 * assing a business role to a user
	 * 
	 * @param myu
	 *           a yafra user model
	 * @param mybr
	 *           a yafra business role model to be assigned to the yafra user
	 * @since 1.0
	 */
   public void addBusinessRole(MYafraUser myu, MYafraBusinessRole mybr);

	/**
	 * remove a business role from a user
	 * 
	 * @param myu
	 *           a yafra user model
	 * @param mybr
	 *           a yafra business role model to be assigned to the yafra user
	 * @since 1.0
	 */
   public void removeBusinessRole(MYafraUser myu, MYafraBusinessRole mybr);
}
