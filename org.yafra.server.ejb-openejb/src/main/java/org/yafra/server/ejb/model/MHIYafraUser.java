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
package org.yafra.server.ejb.model;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Remote;
import javax.ejb.Stateless;

import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraUser;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraUser
 * @version $Id: MHIYafraUser.java,v 1.5 2009-12-24 08:18:23 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIYafraUserRemote.class)
public class MHIYafraUser implements MHIYafraUserRemote
{
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#insertUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void insertUser(MYafraUser u)
		{
		// create new database object
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.insertUser(u);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#updateUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void updateUser(MYafraUser u)
		{
		// get database object first and then change with input and update
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.updateUser(u);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#deleteUser(java.lang.String)
	 */
	@Override
	public void deleteUser(String id)
		{
		yafraglobals.getLoggin().logDebug(" - delete users - " + id);
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.deleteUser(id);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#getUsers()
	 */
	@Override
	public List<MYafraUser> getUsers()
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyu.getMUsers();
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#getUsers(java.lang.String)
	 */
	@Override
	public List<MYafraUser> getUsers(String name)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyu.getMUsers(name);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#getUsers(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public List<MYafraUser> getUsers(MYafraBusinessRole mybr) {
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyu.getMUsers(mybr);
	}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#selectUserByName(java.lang.String)
	 */
	@Override
	public MYafraUser selectUserByName(String name)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyu.selectMUserByName(name);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#selectUser(java.lang.String)
	 */
	@Override
	public MYafraUser selectUser(String id)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyu.selectMUser(id);
		}
	
	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#getRoles(java.lang.String)
	 */
	@Override
	public List<MYafraBusinessRole> getRoles(String id)
		{
		yafraglobals.getLoggin().logDebug(" - get roles of user - pass to MHYafraUser");
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		MYafraUser myu = mhyu.selectMUser(id);
		return mhyu.getMRoles(myu);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#addBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void addBusinessRole(MYafraUser myu, MYafraBusinessRole mybr)
		{
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.addMBusinessRole(myu, mybr);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraUserRemote#removeBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void removeBusinessRole(MYafraUser myu, MYafraBusinessRole mybr)
		{
		MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyu.removeMBusinessRole(myu, mybr);
		}

}
