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
import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.exp.Expression;
import org.apache.cayenne.query.SelectQuery;
import org.apache.cayenne.query.SortOrder;
import org.yafra.interfaces.IYafraMHPerson;
import org.yafra.model.MPerson;
import org.yafra.model.MPersonLog;
import org.yafra.model.MPersonLogTransform;
import org.yafra.model.MPersonTransform;
import org.yafra.orm.Person;
import org.yafra.orm.PersonLog;
import org.yafra.utils.Logging;

/**
 * model handler person</br>
 * 
 * @version $Id: MHPerson.java,v 1.3 2009-12-20 20:22:58 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MHPerson implements IYafraMHPerson {
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
	public MHPerson(ObjectContext ctx, Logging l) {
		dbcontext = ctx;
		log = l;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#insertPerson(org.yafra.model.MPerson)
	 */
	@Override
	public Person insertPerson(MPerson p) {
		Person newp = null;
		try {
			newp = (Person) dbcontext.newObject(Person.class);
			MPersonTransform pt = new MPersonTransform();
			pt.to(p, newp);
			dbcontext.commitChanges();
		} catch (CayenneRuntimeException e) {
			log.logError("cayenne runtime exception", e);
		}
		log.logDebug(" - inserted new person: " + newp.getName());
		return newp;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#insertMPerson(org.yafra.model.MPerson)
	 */
	@Override
	public void insertMPerson(MPerson p) {
		this.insertPerson(p);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#updatePerson(org.yafra.orm.Person)
	 */
	@Override
	public void updatePerson(Person p) {
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
	 * @see org.yafra.interfaces.IYafraMHPerson#updatePerson(org.yafra.model.MPerson)
	 */
	@Override
	public void updatePerson(MPerson mp) {
		Person p = this.selectPerson(mp.getId());
		MPersonTransform pt = new MPersonTransform();
		pt.to(mp, p);
		this.updatePerson(p);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#deletePerson(org.yafra.orm.Person)
	 */
	@Override
	public void deletePerson(Person p) {
		log.logDebug(" - delete person with name from db: " + p.getName());
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
	 * @see org.yafra.interfaces.IYafraMHPerson#deletePerson(java.lang.Integer)
	 */
	@Override
	public void deletePerson(Integer id) {
		Person p = selectPerson(id);
		deletePerson(p);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getPersons()
	 */
	@Override
	public List<Person> getPersons() {
		SelectQuery select1 = new SelectQuery(Person.class);
		select1.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<Person> plist = dbcontext.performQuery(select1);
		log.logDebug(" - query all Person done");
		return plist;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getPersons(java.lang.String, java.lang.String, java.lang.String)
	 */
	@Override
	public List<Person> getPersons(String name, String type, String country) {
		Expression qual = Expression.fromString(String.format(
				"name like \"%s\"", name));
		SelectQuery select = new SelectQuery(Person.class, qual);
		select.addOrdering("name", SortOrder.ASCENDING);
		@SuppressWarnings("unchecked")
		List<Person> plist = dbcontext.performQuery(select);
		log.logDebug(" - query all Person done by name: " + name);
		return plist;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#selectPerson(java.lang.String)
	 */
	@Override
	public Person selectPerson(String name) {
		Expression qual = Expression.fromString(String.format("name = \"%s\"",
				name));
		SelectQuery select = new SelectQuery(Person.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<Person> plist = dbcontext.performQuery(select);
		Person p = (Person) plist.get(0);
		log.logDebug(" - query user with name: " + p.getName());
		return p;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#selectPerson(java.lang.Integer)
	 */
	@Override
	public Person selectPerson(Integer id) {
		Expression qual = Expression.fromString(String.format("id = %d", id));
		SelectQuery select = new SelectQuery(Person.class, qual);
		select.setDistinct(true);
		@SuppressWarnings("unchecked")
		List<Person> plist = dbcontext.performQuery(select);
		Person p = (Person) plist.get(0);
		log.logDebug(" - query user with name: " + p.getName());
		return p;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#selectMPerson(java.lang.String)
	 */
	@Override
	public MPerson selectMPerson(String name) {
		MPerson mp = new MPerson();
		Person p = this.selectPerson(name);
		MPersonTransform pt = new MPersonTransform();
		mp = pt.from(p);
		return mp;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#selectMPerson(java.lang.Integer)
	 */
	@Override
	public MPerson selectMPerson(Integer id) {
		MPerson mp = new MPerson();
		Person p = this.selectPerson(id);
		MPersonTransform pt = new MPersonTransform();
		mp = pt.from(p);
		return mp;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getMPersons()
	 */
	@Override
	public List<MPerson> getMPersons() {
		List<MPerson> mp_list = new ArrayList<MPerson>();
		List<Person> p_list = getPersons();
		Iterator<Person> it = p_list.iterator();
		while (it.hasNext()) {
			Person p = it.next();
			MPersonTransform pt = new MPersonTransform();
			MPerson mp = null;
			mp = pt.from(p);
			mp_list.add(mp);
		}
		return mp_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getMPersons(java.lang.String, java.lang.String, java.lang.String)
	 */
	@Override
	public List<MPerson> getMPersons(String name, String type, String country) {
		List<MPerson> mp_list = new ArrayList<MPerson>();
		List<Person> p_list = getPersons(name, type, country);
		Iterator<Person> it = p_list.iterator();
		while (it.hasNext()) {
			Person p = it.next();
			MPersonTransform pt = new MPersonTransform();
			MPerson mp = null;
			mp = pt.from(p);
			mp_list.add(mp);
		}
		return mp_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getLogs(org.yafra.orm.Person)
	 */
	@Override
	public List<PersonLog> getLogs(Person p) {
		return p.getLogArray();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getMLogs(java.lang.Integer)
	 */
	@Override
	public List<MPersonLog> getMLogs(Integer id) {
		Person p = selectPerson(id);
		List<PersonLog> pl_list = getLogs(p);
		List<MPersonLog> mpl_list = new ArrayList<MPersonLog>();
		Iterator<PersonLog> it = pl_list.iterator();
		while (it.hasNext()) {
			PersonLog pl = it.next();
			MPersonLogTransform plt = new MPersonLogTransform();
			MPersonLog mpl = null;
			mpl = plt.from(pl);
			mpl_list.add(mpl);
		}
		return mpl_list;
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#addLog(org.yafra.orm.Person, org.yafra.orm.PersonLog)
	 */
	@Override
	public void addLog(Person p, PersonLog plog) {
		p.addToLogArray(plog);
		dbcontext.commitChanges();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#removeLog(org.yafra.orm.Person, org.yafra.orm.PersonLog)
	 */
	@Override
	public void removeLog(Person p, PersonLog plog) {
		p.removeFromLogArray(plog);
		dbcontext.commitChanges();
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#addLog(org.yafra.model.MPerson, org.yafra.model.MPersonLog)
	 */
	@Override
	public void addLog(MPerson mp, MPersonLog mplog) {
		Person p = selectPerson(mp.getId());
		MHPersonLog mhpl = new MHPersonLog(dbcontext, log);
		PersonLog plog = mhpl.selectPersonLog(mplog.getDbPK());
		this.addLog(p, plog);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#removeLog(org.yafra.model.MPerson, org.yafra.model.MPersonLog)
	 */
	@Override
	public void removeLog(MPerson mp, MPersonLog mplog) {
		Person p = selectPerson(mp.getId());
		MHPersonLog mhpl = new MHPersonLog(dbcontext, log);
		PersonLog plog = mhpl.selectPersonLog(mplog.getDbPK());
		this.removeLog(p, plog);
	}

	/**
	 * @see org.yafra.interfaces.IYafraMHPerson#getLogs(java.lang.Integer)
	 */
	@Override
	public List<PersonLog> getLogs(Integer id) {
		// TODO Auto-generated method stub
		return null;
	}
}
