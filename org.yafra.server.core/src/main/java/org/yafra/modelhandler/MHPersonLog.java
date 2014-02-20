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
import org.apache.cayenne.DataObjectUtils;
import org.apache.cayenne.DeleteDenyException;
import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.query.SelectQuery;
import org.apache.cayenne.query.SortOrder;
import org.yafra.interfaces.IYafraMHPersonLog;
import org.yafra.model.MPersonLog;
import org.yafra.model.MPersonLogTransform;
import org.yafra.orm.PersonLog;
import org.yafra.utils.Logging;

/**
 * model handler person log</br>
 * 
 * @version $Id: MHPersonLog.java,v 1.2 2009-12-20 20:22:58 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHPersonLog implements IYafraMHPersonLog
{
	private ObjectContext dbcontext = null;

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
	public MHPersonLog(ObjectContext ctx, Logging l)
		{
		dbcontext = ctx;
		log = l;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#insertPersonLog(org.yafra.model.MPersonLog)
	 */
	@Override
	public PersonLog insertPersonLog(MPersonLog mpl) {
		PersonLog newpl = null;
		try {
			newpl = (PersonLog) dbcontext.newObject(PersonLog.class);
			MPersonLogTransform pt = new MPersonLogTransform();
			pt.to(mpl, newpl);
			dbcontext.commitChanges();
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
		log.logDebug(" - inserted new person: " + newpl.getEventDescription());
		return newpl;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#insertMPersonLog(org.yafra.model.MPersonLog)
	 */
	@Override
	public void insertMPersonLog(MPersonLog mpl) {
		PersonLog pl = this.insertPersonLog(mpl);
		mpl.setDbPK(DataObjectUtils.intPKForObject(pl));
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#updatePersonLog(org.yafra.orm.PersonLog)
	 */
	@Override
	public void updatePersonLog(PersonLog p)
		{
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
	 * @see org.yafra.interfaces.IYafraMHPersonLog#updatePersonLog(org.yafra.model.MPersonLog)
	 */
	@Override
	public void updatePersonLog(MPersonLog mpl) {
		PersonLog pl = this.selectPersonLog(mpl.getDbPK());
		MPersonLogTransform pt = new MPersonLogTransform();
		pt.to(mpl, pl);
		this.updatePersonLog(pl);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#deletePersonLog(org.yafra.orm.PersonLog)
	 */
	@Override
	public void deletePersonLog(PersonLog p)
		{
		log.logDebug(" - delete person with name from db: " + p.getEventDescription());
		try {
			dbcontext.deleteObject(p);
			dbcontext.commitChanges();
		} catch (DeleteDenyException e) {
			log.logError("delete denied due to rule", e);
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#deletePersonLog(java.lang.Integer)
	 */
	@Override
	public void deletePersonLog(Integer id)
		{
		PersonLog p = this.selectPersonLog(id);
		deletePersonLog(p);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#getPersonLogs()
	 */
	@Override
	public List<PersonLog> getPersonLogs()
		{
		SelectQuery select = new SelectQuery(PersonLog.class);
		select.addOrdering("eventAudit", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<PersonLog> plist = dbcontext.performQuery(select);
		log.logDebug(" - query all Person done");
		return plist;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#getMPersonLogs()
	 */
	@Override
	public List<MPersonLog> getMPersonLogs() {
		List<MPersonLog> mpl_list = new ArrayList<MPersonLog>();
		List<PersonLog> p_list = getPersonLogs();
		Iterator<PersonLog> it = p_list.iterator();
		while (it.hasNext()) {
			PersonLog pl = it.next();
			MPersonLogTransform mplt = new MPersonLogTransform();
			MPersonLog mpl = null;
			mpl = mplt.from(pl);
			mpl.setDbPK(DataObjectUtils.intPKForObject(pl));
			mpl_list.add(mpl);
		}
		return mpl_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#selectPersonLog(java.lang.Integer)
	 */
	@Override
	public PersonLog selectPersonLog(Integer id)
		{
		PersonLog pl = DataObjectUtils.objectForPK(dbcontext, PersonLog.class, id);
		log.logDebug(" - query user with name: " + Integer.toString(id));
		return pl;
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHPersonLog#selectMPersonLog(java.lang.Integer)
	 */
	@Override
	public MPersonLog selectMPersonLog(Integer id) {
		MPersonLog mpl = new MPersonLog();
		PersonLog pl = this.selectPersonLog(id);
		MPersonLogTransform pt = new MPersonLogTransform();
		mpl = pt.from(pl);
		mpl.setDbPK(DataObjectUtils.intPKForObject(pl));
		return mpl;
	}

}
