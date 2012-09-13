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
 * 
 * @see org.yafra.interfaces.IYafraMHIYafraRole
 * @version $Id: MHIYafraRoleRemote.java,v 1.1 2009-12-12 21:41:32 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface MHIYafraRoleRemote {
	/**
	 * insert a new role
	 * @param name name of the role
	 * @return 1 model object
	 */
	public MYafraRole selectRole(String name);

	/**
	 * get all roles
	 * @return 0-1 roles
	 */
	public List<MYafraRole> getRoles();

	/**
	 * get roles selected by business role
	 * @param name of the business role of which we get the roles as return
	 * @return 0-n roles
	 */
	public List<MYafraRole> getRoles(String name);

	/**
	 * insert a new role
	 * @param myr role to be inserted
	 */
	public void insertRole(MYafraRole myr);

	/**
	 * update a role
	 * @param myr role to be update
	 */
	public void updateRole(MYafraRole myr);

	/**
	 * delete a role
	 * @param id name of the role to be deleted
	 */
	public void deleteRole(String id);

	/**
	 * get business roles from role
	 * @param name of the role of which we get the business role as return
	 * @return business role
	 */
	public MYafraBusinessRole selectBusinessRole(String rolename);

}
