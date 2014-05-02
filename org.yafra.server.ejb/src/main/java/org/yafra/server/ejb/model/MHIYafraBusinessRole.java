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
import org.yafra.model.MYafraRole;
import org.yafra.modelhandler.MHYafraBusinessRole;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole
 * @version $Id: MHIYafraBusinessRole.java,v 1.3 2009-12-24 08:18:23 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIYafraBusinessRoleRemote.class)
public class MHIYafraBusinessRole implements MHIYafraBusinessRoleRemote
{
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote#insertBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void insertBusinessRole(MYafraBusinessRole mbr)
		{
		// create new database object
		MHYafraBusinessRole mhbr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhbr.insertBusinessRole(mbr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#updateBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void updateBusinessRole(MYafraBusinessRole mybr)
		{
		MHYafraBusinessRole mhbr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhbr.updateBusinessRole(mybr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#deleteBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void deleteBusinessRole(MYafraBusinessRole mybr)
		{
		MHYafraBusinessRole mhbr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhbr.deleteBusinessRole(mybr.getName());
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#deleteBusinessRole(java.lang.String)
	 */
	@Override
	public void deleteBusinessRole(String arg0)
		{
		MHYafraBusinessRole mhbr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhbr.deleteBusinessRole(arg0);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#getBusinessRoles()
	 */
	@Override
	public List<MYafraBusinessRole> getBusinessRoles(Boolean onlyactive)
		{
		yafraglobals.getLoggin().logDebug(" - get business roles - pass to MHYafraBusinessRole");
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		if (onlyactive)
			return mhybr.getActiveMBusinessRoles();
		else
			return mhybr.getMBusinessRoles();
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#selectBusinessRole(java.lang.String)
	 */
	@Override
	public MYafraBusinessRole selectBusinessRole(String name)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhybr.selectMBusinessRole(name);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraBusinessRole#getRoles(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public List<MYafraRole> getRoles(MYafraBusinessRole mybr)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		YafraBusinessRole ybr = mhybr.selectBusinessRole(mybr.getName());
		return mhybr.getMRoles(ybr);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote#addRole(org.yafra.model.MYafraBusinessRole, org.yafra.model.MYafraRole)
	 */
	@Override
	public void addRole(MYafraBusinessRole mybr, MYafraRole myr)
		{
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhybr.addRole(mybr, myr);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote#removeRole(org.yafra.model.MYafraBusinessRole, org.yafra.model.MYafraRole)
	 */
	@Override
	public void removeRole(MYafraBusinessRole mybr, MYafraRole myr)
		{
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhybr.removeRole(mybr, myr);
		}

}
