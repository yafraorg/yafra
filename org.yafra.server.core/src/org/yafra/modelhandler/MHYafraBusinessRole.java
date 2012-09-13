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
import org.yafra.interfaces.IYafraMHYafraBusinessRole;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraBusinessRoleTransform;
import org.yafra.model.MYafraRole;
import org.yafra.model.MYafraRoleTransform;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraRole;
import org.yafra.utils.Logging;

/**
 * model handler</br>
 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole
 * @version $Id: MHYafraBusinessRole.java,v 1.5 2009-12-20 20:22:57 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHYafraBusinessRole implements IYafraMHYafraBusinessRole
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
	public MHYafraBusinessRole(DataContext ctx, Logging l)
		{
		dbcontext = ctx;
		log = l;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#insertBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public YafraBusinessRole insertBusinessRole(MYafraBusinessRole mybr)
		{
		YafraBusinessRole newybr = null;
		try
			{
			newybr = (YafraBusinessRole) dbcontext.newObject(YafraBusinessRole.class);
			MYafraBusinessRoleTransform brt = new MYafraBusinessRoleTransform();
			brt.to(mybr, newybr);
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
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#insertMBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void insertMBusinessRole(MYafraBusinessRole mybr) {
		this.insertBusinessRole(mybr);
	}


	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#updateBusinessRole(org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public void updateBusinessRole(YafraBusinessRole ybr)
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
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#updateBusinessRole(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void updateBusinessRole(MYafraBusinessRole mybr) {
		YafraBusinessRole ybr = this.selectBusinessRole(mybr.getName());
		MYafraBusinessRoleTransform ybrt = new MYafraBusinessRoleTransform();
		ybrt.to(mybr, ybr);
		this.updateBusinessRole(ybr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#deleteBusinessRole(org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public void deleteBusinessRole(YafraBusinessRole ybr)
		{
		log.logDebug(" - delete yafrarole from db with name: " + ybr.getName());
		try
			{
			dbcontext.deleteObject(ybr);
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
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#deleteBusinessRole(java.lang.String)
	 */
	@Override
	public void deleteBusinessRole(String name)
		{
		YafraBusinessRole ybr = this.selectBusinessRole(name);
		this.deleteBusinessRole(ybr);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getBusinessRoles()
	 */
	@Override
	public List<YafraBusinessRole> getBusinessRoles()
		{
		SelectQuery select = new SelectQuery(YafraBusinessRole.class);
		select.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraBusinessRole> ybrlist = dbcontext.performQuery(select);
		log.logDebug(" - query all yafrausers done");
		return ybrlist;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getMBusinessRoles()
	 */
	@Override
	public List<MYafraBusinessRole> getMBusinessRoles() {
		List<MYafraBusinessRole> mybr_list = new ArrayList<MYafraBusinessRole>();
		List<YafraBusinessRole> p_list = this.getBusinessRoles();
		Iterator<YafraBusinessRole> it = p_list.iterator();
		while (it.hasNext()) {
			YafraBusinessRole ybr = it.next();
			MYafraBusinessRoleTransform pt = new MYafraBusinessRoleTransform();
			MYafraBusinessRole mybr = null;
			mybr = pt.from(ybr);
			mybr_list.add(mybr);
		}
		return mybr_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getActiveBusinessRoles()
	 */
	@Override
	public List<YafraBusinessRole> getActiveBusinessRoles()
		{
		Expression qual = Expression.fromString("flag = true");
		SelectQuery select = new SelectQuery(YafraBusinessRole.class, qual);
		select.setDistinct(true);
		select.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraBusinessRole> ybrlist = dbcontext.performQuery(select);
		log.logDebug(" - query all yafrausers done");
		return ybrlist;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getActiveMBusinessRoles()
	 */
	@Override
	public List<MYafraBusinessRole> getActiveMBusinessRoles() {
		List<MYafraBusinessRole> mybr_list = new ArrayList<MYafraBusinessRole>();
		List<YafraBusinessRole> p_list = this.getActiveBusinessRoles();
		Iterator<YafraBusinessRole> it = p_list.iterator();
		while (it.hasNext()) {
			YafraBusinessRole ybr = it.next();
			MYafraBusinessRoleTransform pt = new MYafraBusinessRoleTransform();
			MYafraBusinessRole mybr = null;
			mybr = pt.from(ybr);
			mybr_list.add(mybr);
		}
		return mybr_list;
	}


	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#selectBusinessRole(java.lang.String)
	 */
	@Override
	public YafraBusinessRole selectBusinessRole(String name)
		{
		Expression qual = Expression.fromString(String.format("name = \"%s\"", name));
		SelectQuery select = new SelectQuery(YafraBusinessRole.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraBusinessRole> ybrlist = dbcontext.performQuery(select);
		YafraBusinessRole ybr = (YafraBusinessRole) ybrlist.get(0);
		log.logDebug(" - query business role with name: " + ybr.getName());
		return ybr;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#selectMBusinessRole(java.lang.String)
	 */
	@Override
	public MYafraBusinessRole selectMBusinessRole(String name) {
		MYafraBusinessRole mybr = new MYafraBusinessRole();
		YafraBusinessRole ybr = this.selectBusinessRole(name);
		MYafraBusinessRoleTransform pt = new MYafraBusinessRoleTransform();
		mybr = pt.from(ybr);
		return mybr;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#addRole(org.yafra.orm.YafraBusinessRole,
	 *      org.yafra.orm.YafraRole)
	 */
	@Override
	public void addRole(YafraBusinessRole ybr, YafraRole yr)
		{
		try
			{
			ybr.addToTechnicalRolesArray(yr);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - added business role to technical role");
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#addRole(org.yafra.model.MYafraBusinessRole, org.yafra.model.MYafraRole)
	 */
	@Override
	public void addRole(MYafraBusinessRole mybr, MYafraRole myr) {
		Expression qual = Expression.fromString(String.format("name = \"%s\"", myr.getName()));
		SelectQuery select = new SelectQuery(YafraRole.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraRole> yrlist = dbcontext.performQuery(select);
		YafraRole yr = (YafraRole) yrlist.get(0);
		log.logDebug(" - query user with name: " + yr.getName());
		YafraBusinessRole ybr = this.selectBusinessRole(mybr.getName());
		this.addRole(ybr, yr);
		log.logDebug(" - added roles: " + yr.getName() + " to " + ybr.getName());
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#removeRole(org.yafra.orm.YafraBusinessRole, org.yafra.orm.YafraRole)
	 */
	@Override
	public void removeRole(YafraBusinessRole ybr, YafraRole yr)
		{
		try
			{
			ybr.removeFromTechnicalRolesArray(yr);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - removed business role from technical role");
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#removeRole(org.yafra.model.MYafraBusinessRole, org.yafra.model.MYafraRole)
	 */
	@Override
	public void removeRole(MYafraBusinessRole mybr, MYafraRole myr) {
		Expression qual = Expression.fromString(String.format("name = \"%s\"", myr.getName()));
		SelectQuery select = new SelectQuery(YafraRole.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraRole> yrlist = dbcontext.performQuery(select);
		YafraRole yr = (YafraRole) yrlist.get(0);
		log.logDebug(" - query user with name: " + yr.getName());
		YafraBusinessRole ybr = this.selectBusinessRole(mybr.getName());
		this.removeRole(ybr, yr);
		log.logDebug(" - removed roles " + yr.getName() + " from " + ybr.getName());
	}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getRoles(org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public List<YafraRole> getRoles(YafraBusinessRole ybr)
		{
		return ybr.getTechnicalRolesArray();
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraBusinessRole#getMRoles(org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public List<MYafraRole> getMRoles(YafraBusinessRole ybr) {
		List<MYafraRole> myr_list = new ArrayList<MYafraRole>();
		List<YafraRole> yr_list = this.getRoles(ybr);
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

}
