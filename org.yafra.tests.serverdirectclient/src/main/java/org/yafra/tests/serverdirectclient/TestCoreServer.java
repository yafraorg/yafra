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
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @version $$Id: TestCoreServer.java,v 1.3 2009-12-20 20:38:01 mwn Exp $$
 * @since 1.0
 * 
 * tests - test the server.core and server.directclient
 * it's a stand alone test without any network layer except if you have a database layer
 */
package org.yafra.tests.serverdirectclient;

import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.configuration.server.ServerRuntime;
import org.apache.cayenne.CayenneRuntimeException;
import org.apache.cayenne.DeleteDenyException;
import org.apache.cayenne.exp.Expression;
import org.apache.cayenne.query.NamedQuery;
import org.apache.cayenne.query.QueryChain;
import org.apache.cayenne.query.SelectQuery;
import org.apache.cayenne.query.SortOrder;
import org.yafra.directclient.YafraDirectSession;
import org.yafra.model.MPerson;
import org.yafra.modelhandler.MHPerson;
import org.yafra.orm.Person;
import org.yafra.orm.PersonLog;
import org.yafra.orm.YafraAudit;
import org.yafra.orm.YafraBusinessRole;
import org.yafra.orm.YafraRole;
import org.yafra.orm.YafraUser;
import org.yafra.utils.Logging;

/**
 * @author mwn
 * 
 */
public class TestCoreServer
{
	public static YafraDirectSession sess = null;

	/**
	 * @param args
	 */
	public static void main(String[] args)
		{
		// create logging and cayenne context
		ObjectContext dbcontext;
		Logging log;
		
		// start 1 session (could be n in parallel)
		try
			{
			ServerRuntime cayenneRuntime = new ServerRuntime("cayenne-org_yafra.xml");
			dbcontext = cayenneRuntime.getContext();
			log = new Logging();
			log.setDebugFlag(true);
			log.logInfo("org.yafra.tests.serverdirectclient - logging init done - getting session now");
			sess = new YafraDirectSession();
			sess.setLogging(log);
			sess.setContext(dbcontext);
			sess.logMessage(" - client starts now with session id " + sess.getSessionId());
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception during startup", e);
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception during startup", t);
			}

		DoqueryDeleteAll(sess.getContext());
		InsertPerson(sess.getContext());
		InsertYafra(sess.getContext());
		Doquery1(sess.getContext());
		Doquery2(sess.getContext());
		Doquery3(sess.getContext());
		Update1(sess.getContext());
		Delete1(sess.getContext());
		Delete2(sess.getContext());
		Delete2(sess.getContext()); // causes an exception
		TestHandlers(sess.getContext());
		}

	private static void InsertPerson(ObjectContext context)
		{
		Date today = new Date();
		sess.logMessage("\norg.yafra.tests - insert person plain cayenne");
		try
			{
			sess.logMessage(" - insert new person 1");
			Person inspers1 = (Person) context.newObject(Person.class);
			inspers1.setFirstname("Marius");
			inspers1.setName("Wenger");
			inspers1.setAddress("Hauptstrasse 12, 4152 Reinach");
			inspers1.setCountry("CH");
			inspers1.setType("dep");
			inspers1.setId(1);
			sess.logMessage(" - insert new person 2");
			Person inspers2 = (Person) context.newObject(Person.class);
			inspers2.setFirstname("Max");
			inspers2.setName("Knopf");
			inspers2.setAddress("Hauptstrasse 58, Zürich");
			inspers2.setCountry("CH");
			inspers2.setType("priv");
			inspers2.setId(2);
			sess.logMessage(" - insert new personlog for person 1");
			PersonLog insperslog1 = (PersonLog) context.newObject(PersonLog.class);
			insperslog1.setEventAudit("New person created approved");
			insperslog1.setEventAuditReviewer("Thomas Muster");
			insperslog1.setEventCreator("Max Mol");
			insperslog1.setEventDescription("Added new person");
			insperslog1.setEventDate(today);
			insperslog1.setToPerson(inspers1);

			for (int i = 3; i < 200; i++)
				{
				// sess.logMessage(String.format(" - insert new person %d", i));
				Person inspersA = (Person) context.newObject(Person.class);
				inspersA.setFirstname(String.format("Tom%d", i));
				inspersA.setName(String.format("Atkins%d", i));
				inspersA.setAddress("Main Street 58, Las Vegas, Nevada");
				inspersA.setCountry("US");
				inspersA.setType("dep");
				inspersA.setId(i);
				PersonLog logA = (PersonLog) context.newObject(PersonLog.class);
				logA.setEventAudit("New person created approved");
				logA.setEventAuditReviewer("HR North America - Tim Adams");
				logA.setEventCreator("Max Mosley");
				logA.setEventDescription("Added new person");
				logA.setEventDate(today);
				logA.setToPerson(inspersA);
				}
			sess.logMessage(" - inserted 200 new personlogs");

			context.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception", e);
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception", t);
			}
		sess.logMessage("\n - end");
		}

	private static void InsertYafra(ObjectContext context)
		{
		Date today = new Date();
		sess.logMessage("\norg.yafra.tests - insert yafra users plain cayenne");
		try
			{
			YafraUser insuser1 = (YafraUser) context.newObject(YafraUser.class);
			insuser1.setName("Marius Wenger");
			insuser1.setUserid("mwn");
			insuser1.setPicturelink("http://www.yafra.org/");
			sess.logMessage(" - inserted new user 1");
			YafraUser insuser2 = (YafraUser) context.newObject(YafraUser.class);
			insuser2.setName("web user");
			insuser2.setUserid("www");
			sess.logMessage(" - inserted new user 2");
			YafraUser insuser3 = (YafraUser) context.newObject(YafraUser.class);
			insuser3.setName("Max Müller");
			insuser3.setUserid("mm");
			sess.logMessage(" - inserted new user 3");
			YafraUser insuser4 = (YafraUser) context.newObject(YafraUser.class);
			insuser4.setName("Martin Meier");
			insuser4.setUserid("mmeier2");
			sess.logMessage(" - inserted new user 4");
			for (int i = 5; i < 200; i++)
				{
				// sess.logMessage(String.format(" - insert new user %d", i));
				YafraUser insuserA = (YafraUser) context.newObject(YafraUser.class);
				insuserA.setName(String.format("Jon%d Doe%d", i, i));
				insuserA.setUserid(String.format("jd%d", i));
				}
			sess.logMessage(" - insert 200 new users");

			for (int i = 5; i < 2000; i++)
				{
				YafraAudit insaudit1 = (YafraAudit) context.newObject(YafraAudit.class);
				insaudit1.setAuditobject("User");
				insaudit1.setAudittext(String.format("test audit log number %d",i));
				insaudit1.setTimestamp(today);
				insaudit1.setToUser(insuser1);
				}
			sess.logMessage(" - inserted 2000 new audit entries");
			
			sess.logMessage(" - insert new businessrole 1");
			YafraBusinessRole insbrole1 = (YafraBusinessRole) context.newObject(YafraBusinessRole.class);
			insbrole1.setName("admin");
			insbrole1.setDescription("administrator - * / ALL access");
			insbrole1.setFlag(true);
			sess.logMessage(" - insert new businessrole 2");
			YafraBusinessRole insbrole2 = (YafraBusinessRole) context.newObject(YafraBusinessRole.class);
			insbrole2.setName("noaccess");
			insbrole2.setDescription("no access - valid user without any access");
			insbrole2.setFlag(true);
			sess.logMessage(" - insert new businessrole 3");
			YafraBusinessRole insbrole3 = (YafraBusinessRole) context.newObject(YafraBusinessRole.class);
			insbrole3.setName("personaladmin");
			insbrole3.setDescription("H2R - personal admin");
			insbrole3.setFlag(true);
			sess.logMessage(" - insert new businessrole 4 - normal user");
			YafraBusinessRole insbrole4 = (YafraBusinessRole) context.newObject(YafraBusinessRole.class);
			insbrole4.setName("standarduser");
			insbrole4.setDescription("Default role for standard user");
			insbrole4.setFlag(true);
			sess.logMessage(" - insert new businessrole 5 - inactive role");
			YafraBusinessRole insbrole5 = (YafraBusinessRole) context.newObject(YafraBusinessRole.class);
			insbrole5.setName("olduserrole");
			insbrole5.setDescription("Inactive role for test");
			insbrole5.setFlag(false);

			sess.logMessage(" - insert new role 1");
			YafraRole insrole1 = (YafraRole) context.newObject(YafraRole.class);
			insrole1.setName("admin");
			insrole1.setDescription("administrator - * / ALL access");
			insrole1.setRights("*");
			insrole1.setToYafraBusinessRole(insbrole1);
			sess.logMessage(" - insert new role 2");
			YafraRole insrole2 = (YafraRole) context.newObject(YafraRole.class);
			insrole2.setName("noaccess");
			insrole2.setDescription("no access");
			insrole2.setRights("null");
			insrole2.setToYafraBusinessRole(insbrole2);
			sess.logMessage(" - insert new role 3");
			YafraRole insrole3 = (YafraRole) context.newObject(YafraRole.class);
			insrole3.setName("web");
			insrole3.setDescription("web user");
			insrole3.setRights("web");
			insrole3.setToYafraBusinessRole(insbrole1);
			sess.logMessage(" - insert new role 4");
			YafraRole insrole4 = (YafraRole) context.newObject(YafraRole.class);
			insrole4.setName("persadmin");
			insrole4.setDescription("personal adminisrator - can change all persons and logs");
			insrole4.setRights("rw");

			// assign users and business roles
			sess.logMessage(" - create many to many");
			// insbrole1.addToUsers(insuser1);
			insuser1.addToYRoles(insbrole1);
			insuser2.addToYRoles(insbrole1);
			insuser3.addToYRoles(insbrole2);
			
			// assign roles to business roles
			insbrole1.addToTechnicalRolesArray(insrole1);
			insrole1.setToYafraBusinessRole(insbrole1);
			insrole2.setToYafraBusinessRole(insbrole1);
			insrole3.setToYafraBusinessRole(insbrole1);
			insrole1.setToYafraBusinessRole(insbrole2);
			insrole4.setToYafraBusinessRole(insbrole1);

			context.commitChanges();
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception", e);
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception", t);
			}
		sess.logMessage(" - end");
		}

	private static void TestHandlers(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - test model handlers from core server");
		// TODO test model handler methods here
		MHPerson mhp = new MHPerson(context, sess.getLogging());
		MPerson mp = new MPerson();
		mp.setId(120202);
		mp.setAddress("Hallostrasse 12 Berlin Deutschland");
		mp.setCountry("Deutschland");
		mp.setName("Hallo");
		mp.setFirstname("Gunter");
		mp.setType("priv");
		mhp.insertMPerson(mp);
		sess.logMessage(" - inserted mperson " + mp.getName());
		Person phallo = null;
		phallo = mhp.selectPerson(120202);
		sess.logMessage(" - select person " + phallo.getName());
		mp.setName("Halloupdated");
		mhp.updatePerson(mp);
		sess.logMessage(" - updated mperson " + mp.getName());
		phallo = mhp.selectPerson(120202);
		sess.logMessage(" - select person (after update) " + phallo.getName());

		sess.logMessage(" - end");
		}
	
	private static void Doquery1(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - get person list");
		// test with pre def where clause
		SelectQuery select1 = new SelectQuery(Person.class);
		// add ordering by BEZ:
		select1.addOrdering("name", SortOrder.ASCENDING);
		List<Person> bez1 = context.performQuery(select1);
		Iterator<Person> it = bez1.iterator();
		Person a = (Person) it.next();
		sess.logMessage(String.format(" Person: ID %d, Name %s %s, Land %s", a.getId(), a.getFirstname(), a.getName(), a.getCountry()));
		a = (Person) it.next();
		sess.logMessage(String.format(" Person: ID %d, Name %s %s, Land %s", a.getId(), a.getFirstname(), a.getName(), a.getCountry()));
		a = (Person) it.next();
		sess.logMessage(String.format(" Person: ID %d, Name %s %s, Land %s", a.getId(), a.getFirstname(), a.getName(), a.getCountry()));
		sess.logMessage("- list done - reported only the 3 first out of 200");
		sess.logMessage(" - end");
		}

	private static void Doquery2(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - get one person");
		sess.logMessage(" - get one entry by Id (1)");
		Integer id = 1;
		Expression qual = Expression.fromString("id = " + id);
		SelectQuery select2 = new SelectQuery(Person.class, qual);
		select2.setDistinct(true);
		List<Person> plist = context.performQuery(select2);
		sess.logMessage(String.format("Persons returned: %d", plist.size()));
		Person p = (Person) plist.get(0);
		sess.logMessage(String.format("Person: ID %d, Name %s %s, Land %s", p.getId(), p.getFirstname(), p.getName(), p.getCountry()));
		sess.logMessage("\n - end");
		}

	private static void Doquery3(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - get one user");
		List<YafraUser> yulist;
		try
			{
			Expression qual = Expression.fromString("userid = \"mwn\"");
			SelectQuery select = new SelectQuery(YafraUser.class, qual);
			select.setDistinct(true);
			sess.logMessage(" - query build done");
			yulist = context.performQuery(select);
			sess.logMessage(" - query executed");
			// should not be the case but it could
			if (yulist == null)
				{
				sess.logMessage(" - user list null");
				return;
				}
			// list is empty if nothing found - but list created
			if (yulist.isEmpty())
				{
				sess.logMessage(" - no user list returned (list empty)");
				return;
				}
			YafraUser yu = (YafraUser) yulist.get(0);
			sess.logMessage(String.format("Person: ID %s, Name %s", yu.getUserid(), yu.getName()));
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception", t);
			}
		sess.logMessage("\n - end");
		}

	private static void Update1(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - update a user");
		// TODO change role (relation) change content (userid)
		try
			{
			Expression qual = Expression.fromString("id = 89");
			SelectQuery select2 = new SelectQuery(Person.class, qual);
			select2.setDistinct(true);
			List<Person> plist = context.performQuery(select2);
			// list is empty if nothing found
			if (plist.isEmpty())
				{
				sess.logMessage(" - no user list returned (list empty) - NO UPDATE POSSIBLE");
				return;
				}
			Person p = (Person) plist.get(0);
			sess.logMessage(" - update person with name " + p.getName());
			p.setFirstname("Barack");
			p.setName("Obama");
			context.commitChanges();
			}
		catch (IndexOutOfBoundsException e)
			{
			sess.getLogging().logError("entry not found", e);
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception", e);
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception", t);
			}
		sess.logMessage(" - end update done");
		}

	private static void Delete1(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - delete a person");
		try
			{
			Expression qual = Expression.fromString("id = 88");
			SelectQuery select2 = new SelectQuery(Person.class, qual);
			select2.setDistinct(true);
			List<Person> plist = context.performQuery(select2);
			Person p = (Person) plist.get(0);
			sess.logMessage(" - delete person with name " + p.getName());
			context.deleteObject(p);
			context.commitChanges();
			}
		catch (DeleteDenyException e)
			{
			sess.getLogging().logError("delete denied due to rule", e);
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception", e);
			}
		sess.logMessage(" - end");
		}

	private static void Delete2(ObjectContext context)
		{
		String userid = new String("\"jd77\"");
		sess.logMessage("\norg.yafra.tests - delete a user with id " + userid);
		try
			{
			Expression qual = Expression.fromString("userid = " + userid);
			SelectQuery select2 = new SelectQuery(YafraUser.class, qual);
			select2.setDistinct(true);
			List<YafraUser> plist = context.performQuery(select2);
			YafraUser p = (YafraUser) plist.get(0);
			sess.logMessage(" - delete YafraUser with id " + p.getUserid());
			context.deleteObject(p);
			context.commitChanges();
			}
		catch (IndexOutOfBoundsException e)
			{
			sess.getLogging().logError("entry to delete not found", e);
			}
		catch (DeleteDenyException e)
			{
			sess.getLogging().logError("delete denied due to rule", e);
			}
		catch (CayenneRuntimeException e)
			{
			sess.getLogging().logError("cayenne runtime exception", e);
			}
		catch (Throwable t)
			{
			sess.getLogging().logError("generic catch all exception", t);
			}
		sess.logMessage(" - end");
		}

	private static void DoqueryDeleteAll(ObjectContext context)
		{
		sess.logMessage("\norg.yafra.tests - delete all entries");
		QueryChain chain = new QueryChain();
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "PersonLog")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "Person")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "YafraUserRole")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "YafraRole")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "YafraAudit")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "YafraUser")));
		chain.addQuery(new NamedQuery("DeleteAll", Collections.singletonMap("table", "YafraBusinessRole")));
		context.performGenericQuery(chain);
		}
}
