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

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraRole;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraRole;

/**
 * Interface model handler yafra role
 * @version $Id: IYafraMHYafraRole.java,v 1.6 2009-12-18 17:07:31 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHYafraRole {
	/**
	 * Insert a new user into the database
	 * 
	 * @param MYafraRole
	 *            model object - name of role is primary key
	 * @return the new database object
	 * @since 1.0
	 */
	public YafraRole insertRole(MYafraRole myr);
	/**
	 * Insert a new user into the database
	 * 
	 * @param MYafraRole
	 *            model object - name of role is primary key
	 * @since 1.0
	 */
	public void insertMRole(MYafraRole myr);

	/**
	 * update a role
	 * 
	 * @param role
	 *            database object to be updated
	 * @since 1.0
	 */
	public void updateRole(YafraRole yr);
	/**
	 * update a role
	 * 
	 * @param role
	 *            model object to be updated
	 * @since 1.0
	 */
	public void updateRole(MYafraRole myr);

	/**
	 * delete a role
	 * 
	 * @param role
	 *            database object to be deleted
	 * @since 1.0
	 */
	public void deleteRole(YafraRole yr);

	/**
	 * delete a role by its name - first retrieve the database object and then
	 * delete it within the database
	 * 
	 * @param name
	 *            name of the role to be deleted
	 * @since 1.0
	 */
	public void deleteRole(String name);

	/**
	 * retrieve one role by its name
	 * 
	 * @param name
	 *            the name of the role (is a unique name)
	 * @return the retrieved database object
	 * @since 1.0
	 */
	public YafraRole selectRole(String name);
	/**
	 * retrieve one role by its name
	 * 
	 * @param name
	 *            the name of the role (is a unique name)
	 * @return the retrieved model object
	 * @since 1.0
	 */
	public MYafraRole selectMRole(String name);

	/**
	 * retrieve all roles
	 * 
	 * @return the retrieved database objects as a list
	 * @since 1.0
	 */
	public List<YafraRole> getRoles();
	/**
	 * retrieve all roles
	 * 
	 * @return the retrieved model objects as a list
	 * @since 1.0
	 */
	public List<MYafraRole> getMRoles();

	/**
	 * Get business role for a role
	 * 
	 * @param yafra role
	 *            the role database object
	 * @return the assigned business role
	 * @since 1.0
	 */
	public YafraBusinessRole getBusinessRole(YafraRole yr);
	/**
	 * Get model business role for a role
	 * 
	 * @param yafra role
	 *            the role database object
	 * @return the assigned model business role
	 * @since 1.0
	 */
	public MYafraBusinessRole getMBusinessRole(YafraRole yr);
}
