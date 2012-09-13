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

import java.util.List;

import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;
import org.yafra.model.YafraReturnMessage;
import org.yafra.orm.YafraAudit;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraUser;

/**
 * interface model handler yafra user</br>
 * @version $Id: IYafraMHYafraUser.java,v 1.8 2009-12-20 20:22:57 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHYafraUser
{
	/**
	 * Insert a new user into the database
	 * 
	 * @param myu
	 *           a model object containing all new data to be inserted
	 * @return the new database object
	 * @since 1.0
	 */
	public YafraUser insertUser(MYafraUser myu);
	/**
	 * Insert a new user into the database
	 * 
	 * @param myu
	 *           a model object containing all new data to be inserted
	 * @since 1.0
	 */
	public void insertMUser(MYafraUser myu);

	/**
	 * update a user
	 * 
	 * @param user
	 *           database object to be updated
	 * @since 1.0
	 */
	public void updateUser(YafraUser user);
	/**
	 * update a user
	 * 
	 * @param user
	 *           model object to be updated
	 * @since 1.0
	 */
	public void updateUser(MYafraUser muser);

	/**
	 * Delete a user
	 * 
	 * @param user
	 *           database object to be deleted
	 * @since 1.0
	 */
	public void deleteUser(YafraUser user);

	/**
	 * Delete a user by name
	 * 
	 * @param userid
	 *           unique userid
	 * @since 1.0
	 */
	public void deleteUser(String userid);

	/**
	 * Select one user by name
	 * 
	 * @param name
	 *           the name of the user
	 * @return the first YafraUser database object found (could be more than one)
	 * @since 1.0
	 */
	public YafraUser selectUserByName(String name);
	/**
	 * Select one user by name
	 * 
	 * @param name
	 *           the name of the user
	 * @return the first model YafraUser object found (could be more than one)
	 * @since 1.0
	 */
	public MYafraUser selectMUserByName(String name);

	/**
	 * Select one user by id
	 * 
	 * @param userid
	 *           the id of the user
	 * @return YafraUser database object
	 * @since 1.0
	 */
	public YafraUser selectUser(String userid);
	/**
	 * Select one user by id
	 * 
	 * @param userid
	 *           the id of the user
	 * @return YafraUser database object
	 * @since 1.0
	 */
	public MYafraUser selectMUser(String userid);

	/**
	 * get all users
	 * 
	 * @return a list of YafraUser database objects
	 * @since 1.0
	 */
	public List<YafraUser> getUsers();
	/**
	 * get all users
	 * 
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getMUsers();

	/**
	 * get all users with a similar name
	 * 
	 * @param name
	 *           name to be filtered
	 * @return a list of YafraUser database objects
	 * @since 1.0
	 */
	public List<YafraUser> getUsers(String name);
	/**
	 * get all users with a similar name
	 * 
	 * @param name
	 *           name to be filtered
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getMUsers(String name);

	/**
	 * get all users with a role
	 * 
	 * @param ybr
	 *           business role database object
	 * @return a list of YafraUser database objects
	 * @since 1.0
	 */
	public List<YafraUser> getUsers(YafraBusinessRole ybr);
	/**
	 * get all users with a role
	 * 
	 * @param mybr
	 *           business role model object
	 * @return a list of YafraUser model objects
	 * @since 1.0
	 */
	public List<MYafraUser> getMUsers(MYafraBusinessRole mybr);

	/**
	 * assign a business role to a user
	 * 
	 * @param user
	 *           a yafra user database object
	 * @param businessrole
	 *           a yafra business role database object to be assigned to the yafra user
	 * @since 1.0
	 */
	public void addBusinessRole(YafraUser u, YafraBusinessRole ybr);
	/**
	 * assign a business role to a user
	 * 
	 * @param muser
	 *           a yafra user model object
	 * @param mbusinessrole
	 *           a yafra business role model object to be assigned to the yafra user
	 * @since 1.0
	 */
	public void addMBusinessRole(MYafraUser mu, MYafraBusinessRole mybr);

	/**
	 * remove a business role from a user
	 * 
	 * @param user
	 *           a yafra user database object
	 * @param businessrole
	 *           a yafra business role database object to be assigned to the yafra user
	 * @since 1.0
	 */
	public void removeBusinessRole(YafraUser u, YafraBusinessRole ybr);
	/**
	 * remove a business role from a user
	 * 
	 * @param muser
	 *           a yafra user model object
	 * @param mbusinessrole
	 *           a yafra business role model object to be assigned to the yafra user
	 * @since 1.0
	 */
	public void removeMBusinessRole(MYafraUser mu, MYafraBusinessRole mybr);

	/**
	 * check the business role assignment - business rule
	 * 
	 * @param user
	 *           a yafra user database object
	 * @param businessrole
	 *           a yafra business role database object to be assigned to the yafra user
	 * @return YafraReturnMessage with more information
	 * @since 1.0
	 */
	public YafraReturnMessage checkBusinessRole(Boolean add, YafraUser u, YafraBusinessRole ybr);
	/**
	 * check the business role assignment - business rule
	 * 
	 * @param muser
	 *           a yafra user model object
	 * @param mbusinessrole
	 *           a yafra business role model object to be assigned to the yafra user
	 * @return YafraReturnMessage with more information
	 * @since 1.0
	 */
	public YafraReturnMessage checkMBusinessRole(Boolean add, MYafraUser mu, MYafraBusinessRole mybr);

	/**
	 * check user handling - business rule
	 * 
	 * @param upd
	 *           true if you want to check update handling
	 * @param sel
	 *           true if you want to check selection access
	 * @param add
	 *           true if you want to check insert, false if you want to check delete
	 * @param user
	 *           a yafra user database object
	 * @return YafraReturnMessage with more information
	 * @since 1.0
	 */
	public YafraReturnMessage checkUser(Boolean upd, Boolean sel, Boolean add, YafraUser u);
	/**
	 * check user handling - business rule
	 * 
	 * @param upd
	 *           true if you want to check update handling
	 * @param sel
	 *           true if you want to check selection access
	 * @param add
	 *           true if you want to check insert, false if you want to check delete
	 * @param muser
	 *           a yafra user model object
	 * @return YafraReturnMessage with more information
	 * @since 1.0
	 */
	public YafraReturnMessage checkMUser(Boolean upd, Boolean sel, Boolean add, MYafraUser mu);
	
	/**
	 * get all business roles of a user
	 * 
	 * @param user database object of user
	 * @return 0-n business roles as database objects
	 */
	public List<YafraBusinessRole> getRoles(YafraUser yu);
	/**
	 * get all business roles of a user
	 * 
	 * @param user model object of user
	 * @return 0-n business roles as model objects
	 */
	public List<MYafraBusinessRole> getMRoles(MYafraUser myu);
	
	/**
	 * get all audits of a user
	 * 
	 * @param user database object of user
	 * @return 0-n audits as database objects
	 */
	public List<YafraAudit> getUsersAudits(YafraUser yu);
	/**
	 * get all audits of a user
	 * 
	 * @param user model object of user
	 * @return 0-n audits as model objects
	 */
	public List<MYafraAudit> getMUsersAudits(MYafraUser myu);
}
