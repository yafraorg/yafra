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
package org.yafra.server.ws.handlers;

import java.util.List;

import javax.jws.WebService;

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;
import org.yafra.model.MYafraUserTransform;
import org.yafra.modelhandler.MHYafraUser;
import org.yafra.orm.YafraUser;
import org.yafra.server.ws.YafraWSConfig;
import org.yafra.server.ws.remote.MHIYafraUserRemote;

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
@WebService(endpointInterface = "org.yafra.server.ws.remote.MHIYafraUserRemote",
         serviceName = "MHIYafraUserRemote")
public class MHIYafraUser implements MHIYafraUserRemote
{
	private YafraWSConfig yafraglobals = YafraWSConfig.getInstance();

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#insertUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void insertUser(MYafraUser u)
		{
		// TODO Auto-generated method stub

		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#updateUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void updateUser(MYafraUser u)
		{
		// TODO Auto-generated method stub

		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#deleteUser(java.lang.String)
	 */
	@Override
	public void deleteUser(String id)
		{
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.deleteUser(id);
		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#selectUserByName(java.lang.String)
	 */
	@Override
	public MYafraUser selectUserByName(String name)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		YafraUser yu = mhyu.selectUserByName(name);
		MYafraUserTransform ut = new MYafraUserTransform();
		MYafraUser u = null;
		u = ut.from(yu);
		yafraglobals.getLoggin().logDebug(" - get users DONE");
		return u;
		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#selectUser(java.lang.String)
	 */
	@Override
	public MYafraUser selectUser(String id)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		YafraUser yu = mhyu.selectUser(id);
		MYafraUserTransform ut = new MYafraUserTransform();
		MYafraUser u = null;
		u = ut.from(yu);
		yafraglobals.getLoggin().logDebug(" - get users DONE");
		return u;
		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#getUsersFromName(java.lang.String)
	 */
	@Override
	public List<MYafraUser> getUsersFromName(String name)
		{
		// TODO Auto-generated method stub
		return null;
		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#getRoles(java.lang.String)
	 */
	@Override
	public List<MYafraBusinessRole> getRoles(String id)
		{
		// TODO Auto-generated method stub
		return null;
		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#addBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void addBusinessRole(MYafraUser myu, MYafraBusinessRole mybr)
		{
		// TODO Auto-generated method stub

		}

	/**
	 * @see org.yafra.server.ws.remote.MHIYafraUserRemote#removeBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void removeBusinessRole(MYafraUser myu, MYafraBusinessRole mybr)
		{
		// TODO Auto-generated method stub

		}

	@Override
	public String getNameFromId(String id)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		YafraUser yu = mhyu.selectUser(id);
		yafraglobals.getLoggin().logDebug(" - got users with name " + yu.getName());
		return yu.getName();
		}

}
