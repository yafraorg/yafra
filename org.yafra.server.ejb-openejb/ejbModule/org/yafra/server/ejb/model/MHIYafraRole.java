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
import org.yafra.modelhandler.MHYafraRole;
import org.yafra.server.ejbRemote.MHIYafraRoleRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraRole
 * @version $Id: MHIYafraRole.java,v 1.2 2009-12-24 08:18:23 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIYafraRoleRemote.class)
public class MHIYafraRole implements MHIYafraRoleRemote
{
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#insertRole(org.yafra.model.MYafraRole)
	 */
	@Override
	public void insertRole(MYafraRole myr)
		{
		// create new database object
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyr.insertMRole(myr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#updateRole(org.yafra.model.MYafraRole)
	 */
	@Override
	public void updateRole(MYafraRole myr)
		{
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyr.updateRole(myr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#deleteRole(java.lang.String)
	 */
	@Override
	public void deleteRole(String name)
		{
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhyr.deleteRole(name);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#getRoles()
	 */
	@Override
	public List<MYafraRole> getRoles()
		{
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyr.getMRoles();
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#getRoles(java.lang.String)
	 */
	@Override
	public List<MYafraRole> getRoles(String busrolename)
		{
		MHYafraBusinessRole mhyr = new MHYafraBusinessRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyr.getMRoles(mhyr.selectBusinessRole(busrolename));
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#selectRole(java.lang.String)
	 */
	@Override
	public MYafraRole selectRole(String arg0)
		{
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyr.selectMRole(arg0);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIYafraRole#getBusinessRole(java.lang.String)
	 */
	@Override
	public MYafraBusinessRole selectBusinessRole(String rolename)
		{
		MHYafraRole mhyr = new MHYafraRole(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhyr.getMBusinessRole(mhyr.selectRole(rolename));
		}

}
