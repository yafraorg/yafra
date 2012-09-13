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
package org.yafra.modelhandler;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.cayenne.CayenneRuntimeException;
import org.apache.cayenne.DeleteDenyException;
import org.apache.cayenne.access.DataContext;
import org.apache.cayenne.exp.Expression;
import org.apache.cayenne.query.SelectQuery;
import org.apache.cayenne.query.SortOrder;
import org.yafra.interfaces.IYafraMHYafraRole;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraBusinessRoleTransform;
import org.yafra.model.MYafraRole;
import org.yafra.model.MYafraRoleTransform;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraRole;
import org.yafra.utils.Logging;

/**
 * model handler YafraRole</br>
 * @version $Id: MHYafraRole.java,v 1.4 2009-12-20 20:22:57 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHYafraRole implements IYafraMHYafraRole
	{
	private DataContext dbcontext = null;
	private Logging log = null;
	
	/**
	 * constructor with initializing the contexts
	 * 
	 * @param ctx
	 *           a cayenne database context which is already open/active
	 * @param l
	 *           a org.yafra.utils logging context which is already open/active
	 * @since 1.0
	 */
	public MHYafraRole(DataContext ctx, Logging l)
		{
		dbcontext = ctx;
		log = l;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#insertRole(org.yafra.model.MYafraRole)
	 */
	@Override
	public YafraRole insertRole(MYafraRole myr)
		{
		YafraRole newybr = null;
		try
			{
			newybr = (YafraRole) dbcontext.newObject(YafraRole.class);
			MYafraRoleTransform yrt = new MYafraRoleTransform();
			yrt.to(myr, newybr);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - inserted new business role: " + newybr.getName());
		return newybr;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#insertMRole(org.yafra.model.MYafraRole)
	 */
	@Override
	public void insertMRole(MYafraRole myr) {
		insertRole(myr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#updateRole(org.yafra.orm.YafraRole)
	 */
	@Override
	public void updateRole(YafraRole yr)
		{
		// simply commit as we expect the object did change already
		try
			{
			dbcontext.commitChanges();
			}
		catch (DeleteDenyException e)
			{
			log.logError("delete denied due to rule", e);
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#updateRole(org.yafra.model.MYafraRole)
	 */
	@Override
	public void updateRole(MYafraRole myr) {
		YafraRole yr = selectRole(myr.getName());
		MYafraRoleTransform yrt = new MYafraRoleTransform();
		yrt.to(myr, yr);
		updateRole(yr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#deleteRole(org.yafra.orm.YafraRole)
	 */
	@Override
	public void deleteRole(YafraRole yr)
		{
		log.logDebug(" - delete yafrarole from db with name: " + yr.getName());
		try
			{
			dbcontext.deleteObject(yr);
			dbcontext.commitChanges();
			}
		catch (DeleteDenyException e)
			{
			log.logError("delete denied due to rule", e);
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#deleteRole(java.lang.String)
	 */
	@Override
	public void deleteRole(String name)
		{
		YafraRole yr = selectRole(name);
		deleteRole(yr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#getRoles()
	 */
	@Override
	public List<YafraRole> getRoles()
		{
		SelectQuery select = new SelectQuery(YafraRole.class);
		select.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraRole> yrlist = dbcontext.performQuery(select);
		log.logDebug(" - query all yafraroles done");
		return yrlist;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#getMRoles()
	 */
	@Override
	public List<MYafraRole> getMRoles() {
		List<MYafraRole> myr_list = new ArrayList<MYafraRole>();
		List<YafraRole> yr_list = this.getRoles();
		Iterator<YafraRole> it = yr_list.iterator();
		while (it.hasNext()) {
			YafraRole yr = it.next();
			MYafraRoleTransform myrt = new MYafraRoleTransform();
			MYafraRole myr = null;
			myr = myrt.from(yr);
			myr_list.add(myr);
		}
		return myr_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#selectRole(java.lang.String)
	 */
	@Override
	public YafraRole selectRole(String name)
		{
		Expression qual = Expression.fromString(String.format("name = \"%s\"", name));
		SelectQuery select = new SelectQuery(YafraRole.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraRole> yrlist = dbcontext.performQuery(select);
		YafraRole yr = (YafraRole) yrlist.get(0);
		log.logDebug(" - query user with name: " + yr.getName());
		return yr;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#getBusinessRole(org.yafra.orm.YafraRole)
	 */
	@Override
	public YafraBusinessRole getBusinessRole(YafraRole yr)
		{
		return yr.getToYafraBusinessRole();
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#selectMRole(java.lang.String)
	 */
	@Override
	public MYafraRole selectMRole(String name) {
		MYafraRole myr = new MYafraRole();
		YafraRole yr = this.selectRole(name);
		MYafraRoleTransform myrt = new MYafraRoleTransform();
		myr = myrt.from(yr);
		return myr;
	}


	/**
	 * @see org.yafra.interfaces.IYafraMHYafraRole#getMBusinessRole(org.yafra.orm.YafraRole)
	 */
	@Override
	public MYafraBusinessRole getMBusinessRole(YafraRole yr) {
		YafraBusinessRole ybr = this.getBusinessRole(yr);
		MYafraBusinessRoleTransform mybrt = new MYafraBusinessRoleTransform();
		return mybrt.from(ybr);
	}
}
