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
import org.yafra.interfaces.IYafraMHYafraUser;
import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraAuditTransform;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraBusinessRoleTransform;
import org.yafra.model.MYafraUser;
import org.yafra.model.MYafraUserTransform;
import org.yafra.model.YafraReturnMessage;
import org.yafra.orm.YafraAudit;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraUser;
import org.yafra.utils.Logging;

/**
 * model handler YafraUser</br>
 * @version $Id: MHYafraUser.java,v 1.7 2009-12-20 20:22:58 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHYafraUser implements IYafraMHYafraUser
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
	public MHYafraUser(DataContext ctx, Logging l)
		{
		dbcontext = ctx;
		log = l;
		}
	
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#insertUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public YafraUser insertUser(MYafraUser myu)
		{
		YafraUser newyu = null;
		try
			{
			newyu = (YafraUser) dbcontext.newObject(YafraUser.class);
			MYafraUserTransform yut = new MYafraUserTransform();
			yut.to(myu, newyu);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - inserted new user: " + newyu.getUserid());
		return newyu;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#insertMUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void insertMUser(MYafraUser myu) {
		this.insertUser(myu);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#updateUser(org.yafra.orm.YafraUser)
	 */
	@Override
	public void updateUser(YafraUser u)
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
	 * @see org.yafra.interfaces.IYafraMHYafraUser#updateUser(org.yafra.model.MYafraUser)
	 */
	@Override
	public void updateUser(MYafraUser muser) {
		YafraUser yu = this.selectUser(muser.getUserid());
		MYafraUserTransform pt = new MYafraUserTransform();
		pt.to(muser, yu);
		this.updateUser(yu);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#deleteUser(org.yafra.orm.YafraUser)
	 */
	@Override
	public void deleteUser(YafraUser u)
		{
		log.logDebug(" - delete yafrauser with userid from db: " + u.getUserid());
		try
			{
			dbcontext.deleteObject(u);
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
	 * @see org.yafra.interfaces.IYafraMHYafraUser#deleteUser(java.lang.String)
	 */
	@Override
	public void deleteUser(String userid)
		{
		YafraUser yu = selectUser(userid);
		deleteUser(yu);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getUsers()
	 */
	@Override
	public List<YafraUser> getUsers()
		{
		SelectQuery select1 = new SelectQuery(YafraUser.class);
		select1.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraUser> yulist = dbcontext.performQuery(select1);
		log.logDebug(" - query all yafrausers done");
		return yulist;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getMUsers()
	 */
	@Override
	public List<MYafraUser> getMUsers() {
		List<MYafraUser> mp_list = new ArrayList<MYafraUser>();
		List<YafraUser> p_list = getUsers();
		Iterator<YafraUser> it = p_list.iterator();
		while (it.hasNext()) {
			YafraUser p = it.next();
			MYafraUserTransform pt = new MYafraUserTransform();
			MYafraUser mp = null;
			mp = pt.from(p);
			mp_list.add(mp);
		}
		return mp_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getUsers(java.lang.String)
	 */
	@Override
	public List<YafraUser> getUsers(String name)
		{
		Expression qual = Expression.fromString(String.format("name like \"%s\"", name));
		SelectQuery select1 = new SelectQuery(YafraUser.class, qual);
		select1.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraUser> yulist = dbcontext.performQuery(select1);
		log.logDebug(" - query all yafrausers done by name: " + name);
		return yulist;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getMUsers(java.lang.String)
	 */
	@Override
	public List<MYafraUser> getMUsers(String name) {
		List<MYafraUser> mp_list = new ArrayList<MYafraUser>();
		List<YafraUser> p_list = getUsers(name);
		Iterator<YafraUser> it = p_list.iterator();
		while (it.hasNext()) {
			YafraUser p = it.next();
			MYafraUserTransform pt = new MYafraUserTransform();
			MYafraUser mp = null;
			mp = pt.from(p);
			mp_list.add(mp);
		}
		return mp_list;
	}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getUsers(org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public List<YafraUser> getUsers(YafraBusinessRole ybr) {
		return ybr.getYUsers();
	}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getMUsers(org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public List<MYafraUser> getMUsers(MYafraBusinessRole mybr) {
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(dbcontext, log);
		YafraBusinessRole ybr = mhybr.selectBusinessRole(mybr.getName());
		List<MYafraUser> mp_list = new ArrayList<MYafraUser>();
		List<YafraUser> p_list = getUsers(ybr);
		Iterator<YafraUser> it = p_list.iterator();
		while (it.hasNext()) {
			YafraUser p = it.next();
			MYafraUserTransform pt = new MYafraUserTransform();
			MYafraUser mp = null;
			mp = pt.from(p);
			mp_list.add(mp);
		}
		return mp_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#selectUser(java.lang.String)
	 */
	@Override
	public YafraUser selectUser(String id)
		{
		Expression qual = Expression.fromString(String.format("userid = \"%s\"", id));
		SelectQuery select = new SelectQuery(YafraUser.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraUser> yulist = dbcontext.performQuery(select);
		YafraUser yu = (YafraUser) yulist.get(0);
		log.logDebug(" - query user with name: " + yu.getName());
		return yu;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#selectMUser(java.lang.String)
	 */
	@Override
	public MYafraUser selectMUser(String userid) {
		MYafraUser myu = new MYafraUser();
		YafraUser yu = this.selectUser(userid);
		MYafraUserTransform pt = new MYafraUserTransform();
		myu = pt.from(yu);
		return myu;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#selectUserByName(java.lang.String)
	 */
	@Override
	public YafraUser selectUserByName(String name)
		{
		Expression qual = Expression.fromString(String.format("name = \"%s\"", name));
		SelectQuery select = new SelectQuery(YafraUser.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<YafraUser> yulist = dbcontext.performQuery(select);
		YafraUser yu = (YafraUser) yulist.get(0);
		log.logDebug(" - query user with name: " + yu.getName());
		return yu;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#selectMUserByName(java.lang.String)
	 */
	@Override
	public MYafraUser selectMUserByName(String name) {
		MYafraUser myu = new MYafraUser();
		YafraUser yu = this.selectUserByName(name);
		MYafraUserTransform pt = new MYafraUserTransform();
		myu = pt.from(yu);
		return myu;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#addBusinessRole(org.yafra.orm.YafraUser, org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public void addBusinessRole(YafraUser u, YafraBusinessRole ybr)
		{
		try
			{
			u.addToYRoles(ybr);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - added business role " + ybr.getName() + " to user " + u.getName());
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#addMBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void addMBusinessRole(MYafraUser mu, MYafraBusinessRole mybr) {
		YafraUser yu = this.selectUser(mu.getUserid());
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(dbcontext, log);
		YafraBusinessRole ybr = mhybr.selectBusinessRole(mybr.getName());
		this.addBusinessRole(yu, ybr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#removeBusinessRole(org.yafra.orm.YafraUser, org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public void removeBusinessRole(YafraUser u, YafraBusinessRole ybr)
		{
		try
			{
			u.removeFromYRoles(ybr);
			dbcontext.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			log.logError("cayenne runtime exception", e);
			}
		log.logDebug(" - removed business role " + ybr.getName() + " to user " + u.getName());
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#removeMBusinessRole(org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public void removeMBusinessRole(MYafraUser mu, MYafraBusinessRole mybr) {
		YafraUser yu = this.selectUser(mu.getUserid());
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(dbcontext, log);
		YafraBusinessRole ybr = mhybr.selectBusinessRole(mybr.getName());
		this.removeBusinessRole(yu, ybr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#checkBusinessRole(java.lang.Boolean, org.yafra.orm.YafraUser, org.yafra.orm.YafraBusinessRole)
	 */
	@Override
	public YafraReturnMessage checkBusinessRole(Boolean add, YafraUser u, YafraBusinessRole ybr)
		{
		// this is a check of a business rule routine
		YafraReturnMessage ret = new YafraReturnMessage();
		ret.setMessage("OK");
		ret.setOK(true);

		// TODO check if noaccess is assigned (first delete else you can't add something)
		// TODO check if logged in user has enough rights
		// TODO check if admin is assinged (in this no other roles are allowed)
		// TODO check if role exists already and if so make exception
		List<YafraBusinessRole> assignedroles = u.getYRoles();
		if (assignedroles.contains(ybr))
			{
			// TODO error
			}
		
		return ret;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#checkMBusinessRole(java.lang.Boolean, org.yafra.model.MYafraUser, org.yafra.model.MYafraBusinessRole)
	 */
	@Override
	public YafraReturnMessage checkMBusinessRole(Boolean add, MYafraUser mu, MYafraBusinessRole mybr) {
		YafraUser yu = this.selectUser(mu.getUserid());
		MHYafraBusinessRole mhybr = new MHYafraBusinessRole(dbcontext, log);
		YafraBusinessRole ybr = mhybr.selectBusinessRole(mybr.getName());
		return this.checkBusinessRole(add, yu, ybr);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#checkUser(java.lang.Boolean, java.lang.Boolean, java.lang.Boolean, org.yafra.orm.YafraUser)
	 */
	@Override
	public YafraReturnMessage checkUser(Boolean upd, Boolean sel, Boolean add, YafraUser u)
		{
		// this is a check of a business rule routine
		YafraReturnMessage ret = new YafraReturnMessage();
		ret.setMessage("OK");
		ret.setOK(true);
		
		if (upd)
			{
			
			}
		if (sel)
			{
			
			}
		if (add)
			{
			
			}
		else
			{
			
			}
		return ret;
		}
	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#checkMUser(java.lang.Boolean, java.lang.Boolean, java.lang.Boolean, org.yafra.model.MYafraUser)
	 */
	@Override
	public YafraReturnMessage checkMUser(Boolean upd, Boolean sel, Boolean add,	MYafraUser mu) {
		YafraUser yu = this.selectUser(mu.getUserid());
		return this.checkUser(upd, sel, add, yu);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getRoles(org.yafra.orm.YafraUser)
	 */
	@Override
	public List<YafraBusinessRole> getRoles(YafraUser yu) {
		return yu.getYRoles();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getMRoles(org.yafra.model.MYafraUser)
	 */
	@Override
	public List<MYafraBusinessRole> getMRoles(MYafraUser myu) {
		YafraUser yu = this.selectUser(myu.getUserid());
		List<MYafraBusinessRole> mybr_list = new ArrayList<MYafraBusinessRole>();
		List<YafraBusinessRole>ybr_list = yu.getYRoles();
		Iterator<YafraBusinessRole> it = ybr_list.iterator();
		while (it.hasNext())
			{
			YafraBusinessRole ybr = it.next();
			MYafraBusinessRoleTransform mbrt = new MYafraBusinessRoleTransform();
			MYafraBusinessRole mbr = null;
			mbr = mbrt.from(ybr);
			mybr_list.add(mbr);
			}
		return mybr_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getUsersAudits(org.yafra.orm.YafraUser)
	 */
	@Override
	public List<YafraAudit> getUsersAudits(YafraUser yu) {
		return yu.getAuditArray();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraUser#getMUsersAudits(org.yafra.model.MYafraUser)
	 */
	@Override
	public List<MYafraAudit> getMUsersAudits(MYafraUser myu) {
		List<MYafraAudit> mya_list = new ArrayList<MYafraAudit>();
		YafraUser yu = this.selectUser(myu.getUserid());
		List<YafraAudit>ya_list = this.getUsersAudits(yu);
		Iterator<YafraAudit> it = ya_list.iterator();
		while (it.hasNext())
			{
			YafraAudit ya = it.next();
			MYafraAuditTransform myat = new MYafraAuditTransform();
			MYafraAudit mya = null;
			mya = myat.from(ya);
			mya_list.add(mya);
			}
		return mya_list;
	}
}
