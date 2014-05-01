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
 *
 */

package org.yafra.modelhandler;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.cayenne.Cayenne;
import org.apache.cayenne.CayenneRuntimeException;
import org.apache.cayenne.DeleteDenyException;
import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.access.DataContext;
import org.apache.cayenne.query.SelectQuery;
import org.apache.cayenne.query.SortOrder;
import org.yafra.interfaces.IYafraMHYafraAudit;
import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraAuditTransform;
import org.yafra.model.MYafraUser;
import org.yafra.orm.YafraAudit;
import org.yafra.orm.YafraUser;
import org.yafra.utils.Logging;

/**
 * model handler person log</br>
 * 
 * @version $Id: MHPersonLog.java,v 1.2 2009-12-20 20:22:58 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHYafraAudit implements IYafraMHYafraAudit {
	private ObjectContext dbcontext = null;
	private Logging log = null;

	/**
	 * constructor with initializing the contexts
	 * 
	 * @param ctx
	 *            a cayenne database context which is already open/active
	 * @param l
	 *            a org.yafra.utils logging context which is already open/active
	 * @since 1.0
	 */
	public MHYafraAudit(ObjectContext ctx, Logging l) {
		dbcontext = ctx;
		log = l;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#insertYafraAudit(org.yafra.model.MYafraAudit)
	 */
	@Override
	public YafraAudit insertYafraAudit(MYafraAudit mya) {
		YafraAudit newya = null;
		try {
			newya = (YafraAudit) ((DataContext) dbcontext).newObject(YafraAudit.class);
			MYafraAuditTransform myat = new MYafraAuditTransform();
			myat.to(mya, newya);
			dbcontext.commitChanges();
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
		log.logDebug(" - inserted new audit entry");
		return newya;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#insertMYafraAudit(org.yafra.model.MYafraAudit)
	 */
	@Override
	public void insertMYafraAudit(MYafraAudit mya) {
		YafraAudit newya = insertYafraAudit(mya);
		mya.setDbPK(Cayenne.intPKForObject(newya));
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#updateYafraAudit(org.yafra.orm.YafraAudit)
	 */
	@Override
	public void updateYafraAudit(YafraAudit ya) {
		// simply commit as we expect the object did change already
		try {
			dbcontext.commitChanges();
		} catch (DeleteDenyException e) {
			log.logError("delete denied due to rule", e);
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#updateYafraAudit(org.yafra.model.MYafraAudit)
	 */
	@Override
	public void updateYafraAudit(MYafraAudit mya) {
		YafraAudit ya = this.selectYafraAudit(mya.getDbPK());
		MYafraAuditTransform myat = new MYafraAuditTransform();
		myat.to(mya, ya);
		this.updateYafraAudit(ya);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#deleteYafraAudit(org.yafra.orm.YafraAudit)
	 */
	@Override
	public void deleteYafraAudit(YafraAudit ya) {
		log.logDebug(" - delete yafra audit with name from db: " + ya.getAudittext());
		try {
			dbcontext.deleteObjects(ya);
			dbcontext.commitChanges();
		} catch (DeleteDenyException e) {
			log.logError("delete denied due to rule", e);
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#deleteYafraAudit(java.lang.Integer)
	 */
	@Override
	public void deleteYafraAudit(Integer id) {
		YafraAudit ya = this.selectYafraAudit(id);
		this.deleteYafraAudit(ya);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#selectYafraAudit(java.lang.Integer)
	 */
	@Override
	public YafraAudit selectYafraAudit(Integer id) {
		YafraAudit ya = Cayenne.objectForPK(dbcontext, YafraAudit.class, id);
		log.logDebug(" - query audit log with pk id: " + Integer.toString(id));
		return ya;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#selectMYafraAudit(java.lang.Integer)
	 */
	@Override
	public MYafraAudit selectMYafraAudit(Integer id) {
		MYafraAudit mya = new MYafraAudit();
		YafraAudit ya = this.selectYafraAudit(id);
		MYafraAuditTransform myat = new MYafraAuditTransform();
		mya = myat.from(ya);
		mya.setDbPK(Cayenne.intPKForObject(ya));
		return mya;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#getYafraAudits()
	 */
	@Override
	public List<YafraAudit> getYafraAudits() {
		SelectQuery select = new SelectQuery(YafraAudit.class);
		select.addOrdering("auditobject", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<YafraAudit> yalist = dbcontext.performQuery(select);
		log.logDebug(" - query all audit logs done");
		return yalist;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#getMYafraAudits()
	 */
	@Override
	public List<MYafraAudit> getMYafraAudits() {
		List<MYafraAudit> mya_list = new ArrayList<MYafraAudit>();
		List<YafraAudit> ya_list = this.getYafraAudits();
		Iterator<YafraAudit> it = ya_list.iterator();
		while (it.hasNext()) {
			YafraAudit ya = it.next();
			MYafraAuditTransform myat = new MYafraAuditTransform();
			MYafraAudit mya = null;
			mya = myat.from(ya);
			mya.setDbPK(Cayenne.intPKForObject(ya));
			mya_list.add(mya);
		}
		return mya_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#getYafraAudits(org.yafra.orm.YafraUser)
	 */
	@Override
	public List<YafraAudit> getYafraAudits(YafraUser yu) {
		return yu.getAuditArray();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#getMYafraAudits(org.yafra.model.MYafraUser)
	 */
	@Override
	public List<MYafraAudit> getMYafraAudits(MYafraUser myu) {
		MHYafraUser mhyu = new MHYafraUser(dbcontext, log);
		YafraUser yu = mhyu.selectUser(myu.getUserid());
		List<MYafraAudit> mya_list = new ArrayList<MYafraAudit>();
		List<YafraAudit> ya_list = this.getYafraAudits(yu);
		Iterator<YafraAudit> it = ya_list.iterator();
		while (it.hasNext()) {
			YafraAudit ya = it.next();
			MYafraAuditTransform myat = new MYafraAuditTransform();
			MYafraAudit mya = null;
			mya = myat.from(ya);
			mya.setDbPK(Cayenne.intPKForObject(ya));
			mya_list.add(mya);
		}
		return mya_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#setAuditUser(org.yafra.orm.YafraAudit, org.yafra.orm.YafraUser)
	 */
	@Override
	public void setAuditUser(YafraAudit ya, YafraUser yu) {
		ya.setToUser(yu);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHYafraAudit#setAuditUser(org.yafra.model.MYafraAudit, org.yafra.model.MYafraUser)
	 */
	@Override
	public void setAuditUser(MYafraAudit mya, MYafraUser myu) {
		YafraAudit ya = selectYafraAudit(mya.getDbPK());
		MHYafraUser mhyu = new MHYafraUser(dbcontext, log);
		YafraUser yu = mhyu.selectUser(myu.getUserid());
		this.setAuditUser(ya, yu);
	}
}
