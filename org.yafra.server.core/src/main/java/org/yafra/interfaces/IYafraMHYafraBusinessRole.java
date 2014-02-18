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
 * Interface model handler yafra business role
 * @version $Id: IYafraMHYafraBusinessRole.java,v 1.7 2009-12-18 17:07:31 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHYafraBusinessRole
{
	/**
	 * Insert a new user into the database
	 * 
	 * @param MYafraBusinessRole	model object - name is primary key
	 * @return the new database object
	 * @since 1.0
	 */
	public YafraBusinessRole insertBusinessRole(MYafraBusinessRole mybr);
	/**
	 * Insert a new user into the database
	 * 
	 * @param MYafraBusinessRole	model object - name is primary key
	 * @since 1.0
	 */
	public void insertMBusinessRole(MYafraBusinessRole mybr);

	/**
	 * update a business role
	 * 
	 * @param businessrole
	 *           database object to be updated
	 * @since 1.0
	 */
	public void updateBusinessRole(YafraBusinessRole ybr);
	/**
	 * update a business role
	 * 
	 * @param businessrole
	 *           model object to be updated
	 * @since 1.0
	 */
	public void updateBusinessRole(MYafraBusinessRole mybr);


	/**
	 * delete a business role
	 * 
	 * @param businessrole
	 *           database object to be deleted
	 * @since 1.0
	 */
	public void deleteBusinessRole(YafraBusinessRole ybr);

	/**
	 * delete a business role by its name - first retrieve the database object
	 * and then delete it within the database
	 * 
	 * @param name
	 *           name of the business role to be deleted
	 * @since 1.0
	 */
	public void deleteBusinessRole(String name);

	/**
	 * retrieve one business role by its name
	 * 
	 * @param name
	 *           the name of the role (is a unique name)
	 * @return the retrieved database object
	 * @since 1.0
	 */
	public YafraBusinessRole selectBusinessRole(String name);
	/**
	 * retrieve one business role by its name
	 * 
	 * @param name
	 *           the name of the role (is a unique name)
	 * @return the retrieved model object
	 * @since 1.0
	 */
	public MYafraBusinessRole selectMBusinessRole(String name);

	/**
	 * retrieve all business roles
	 * 
	 * @return 0-n retrieved database objects as a list
	 * @since 1.0
	 */
	public List<YafraBusinessRole> getBusinessRoles();
	/**
	 * retrieve all business roles
	 * 
	 * @return 0-n retrieved model objects as a list
	 * @since 1.0
	 */
	public List<MYafraBusinessRole> getMBusinessRoles();

	/**
	 * retrieve all ACTIVE business roles
	 * 
	 * @return 0-n retrieved database objects as a list
	 * @since 1.0
	 */
	public List<YafraBusinessRole> getActiveBusinessRoles();
	/**
	 * retrieve all ACTIVE business roles
	 * 
	 * @return 0-n retrieved model objects as a list
	 * @since 1.0
	 */
	public List<MYafraBusinessRole> getActiveMBusinessRoles();

	/**
	 * add a role to a business role
	 * 
	 * @param ybr
	 *           the yafra business role to be added to an user
	 * @param yr
	 *           the yafra role
	 * @since 1.0
	 */
	public void addRole(YafraBusinessRole ybr, YafraRole yr);
	/**
	 * add a model role to a model business role
	 * 
	 * @param mybr
	 *           the yafra business role to be added to an user
	 * @param myr
	 *           the yafra role
	 * @since 1.0
	 */
	public void addRole(MYafraBusinessRole mybr, MYafraRole myr);

	/**
	 * remove a business role from a role
	 * 
	 * @param ybr
	 *           the yafra business role to be added to an user
	 * @param yr
	 *           the yafra role
	 * @since 1.0
	 */
	public void removeRole(YafraBusinessRole ybr, YafraRole yr);
	/**
	 * remove a model business role from a model role
	 * 
	 * @param ybr
	 *           the yafra business role to be added to an user
	 * @param yr
	 *           the yafra role
	 * @since 1.0
	 */
	public void removeRole(MYafraBusinessRole mybr, MYafraRole myr);

	/**
	 * retrieve all technical roles for one business role
	 * 
	 * @param ybr
	 *           the yafra business role
	 * @return the retrieved technical roles for the business role
	 * @since 1.0
	 */
	public List<YafraRole> getRoles(YafraBusinessRole ybr);
	/**
	 * retrieve all technical roles for one business role
	 * 
	 * @param ybr
	 *           the yafra business role
	 * @return the retrieved technical model roles for the business role
	 * @since 1.0
	 */
	public List<MYafraRole> getMRoles(YafraBusinessRole ybr);
}
