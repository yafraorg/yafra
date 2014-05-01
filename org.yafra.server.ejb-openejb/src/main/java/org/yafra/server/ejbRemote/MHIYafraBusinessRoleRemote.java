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
package org.yafra.server.ejbRemote;

import java.util.List;

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraRole;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole
 * @version $Id: MHIYafraBusinessRoleRemote.java,v 1.1 2009-12-12 21:41:32 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface MHIYafraBusinessRoleRemote
{
	/**
	 * Insert a new business role with attributes as arguments
	 * 
	 * @param name the unique name of the role
	 * @param desc description of the business role - free text
	 * @param active boolean to indicate if role is still active or not
	 * @return new yafra business role database object
	 * @since 1.0
	 */
	public void insertBusinessRole(MYafraBusinessRole mbr);

	/**
	 * Modify a business role with attributes as arguments
	 * 
	 * @param ybr yafra business role model whith modified data
	 * @since 1.0
	 */
	public void updateBusinessRole(MYafraBusinessRole ybr);

	/**
	 * Delete a business role
	 * 
	 * @param ybr yafra business role database object to be deleted
	 * @since 1.0
	 */
	public void deleteBusinessRole(MYafraBusinessRole ybr);

	/**
	 * Delete a business role
	 * 
	 * @param ybr yafra business role database object to be deleted
	 * @since 1.0
	 */
	public void deleteBusinessRole(String name);
	/**
	 * Select one business role by name
	 * 
	 * @param name
	 *           the name of the role (is a unique name)
	 * @return the model object of YafraBusinessRole
	 * @since 1.0
	 */
	public MYafraBusinessRole selectBusinessRole(String name);

	/**
	 * Get a list of all business roles in the database
	 * 
	 * @param onlyactive
	 *           true return only active roles / false returns all roles
	 * @return a list of model objects of YafraBusinessRole
	 * @since 1.0
	 */
	public List<MYafraBusinessRole> getBusinessRoles(Boolean onlyactive);

	/**
	 * add a technical role to a business role
	 * 
	 * @param mybr
	 *           the yafra business role
	 * @param myr
	 *           the yafra role (the technical one) to be assigned to the business role
	 * @since 1.0
	 */
	public void addRole(MYafraBusinessRole mybr, MYafraRole myr);

	/**
	 * remove a technical role from a business role
	 * 
	 * @param mybr
	 *           the yafra business role
	 * @param myr
	 *           the yafra role (the technical one) to be assigned to the business role
	 * @since 1.0
	 */
	public void removeRole(MYafraBusinessRole mybr, MYafraRole myr);

	/**
	 * Get all technical roles for a specific business role
	 * 
	 * @param ybr yafra business role model
	 * @return list of all technical roles (as model) for the provided business role
	 * @since 1.0
	 */
	public List<MYafraRole> getRoles(MYafraBusinessRole ybr);
}
