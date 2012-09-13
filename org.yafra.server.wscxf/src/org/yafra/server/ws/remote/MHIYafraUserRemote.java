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
package org.yafra.server.ws.remote;

import java.util.List;

import javax.jws.WebParam;
import javax.jws.WebService;

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;

/**
 * YafraBusinessRole database object</br>
 * Attributes:
 * <ul>
 * <li>name (unique) - String
 * <li>description - String
 * <li>flag - access flags as String
 * </ul>
 * @version $Id: $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@WebService
public interface MHIYafraUserRemote
{
	public void insertUser(@WebParam(name="yafrauserobj")MYafraUser u);

	public void updateUser(@WebParam(name="yafrauserobj")MYafraUser u);

	public void deleteUser(@WebParam(name="userid")String id);

	public MYafraUser selectUserByName(@WebParam(name="username")String name);

	public String getNameFromId(@WebParam(name="userid")String id);

	public MYafraUser selectUser(@WebParam(name="userid")String id);

	public List<MYafraUser> getUsersFromName(@WebParam(name="username")String name);

	public List<MYafraBusinessRole> getRoles(@WebParam(name="userid")String id);
	
	public void addBusinessRole(@WebParam(name="yafrauser")MYafraUser myu, @WebParam(name="yafrabusinessrole")MYafraBusinessRole mybr);
	
	public void removeBusinessRole(@WebParam(name="yafrauser")MYafraUser myu, @WebParam(name="yafrabusinessrole")MYafraBusinessRole mybr);
}
