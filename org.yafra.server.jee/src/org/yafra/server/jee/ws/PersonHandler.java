package org.yafra.server.jee.ws;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.annotation.Resource;
import javax.jws.WebService;
import javax.servlet.http.HttpSession;
import javax.xml.ws.WebServiceContext;
import javax.xml.ws.WebServiceException;
import javax.xml.ws.handler.MessageContext;

import org.apache.cayenne.access.DataContext;
import org.apache.cayenne.conf.ServletUtil;
import org.yafra.directclient.YafraDirectSession;
import org.yafra.modelhandler.MHPerson;
import org.yafra.orm.Person;
import org.yafra.server.jee.xmlobjects.WSPerson;
import org.yafra.utils.Logging;

@WebService
public class PersonHandler implements PersonSEI {
	@Resource
	private WebServiceContext context;

	private Logging log;
	private YafraDirectSession sess;

	@Override
	public List<String> getPersons() {
		// TODO replace with getting persons from cayenne db
		MessageContext mc = context.getMessageContext();    // Step 3
	    HttpSession session = ((javax.servlet.http.HttpServletRequest)mc.get(MessageContext.SERVLET_REQUEST)).getSession();
	    if (session == null)
	         throw new WebServiceException("No HTTP Session found");
		DataContext dbcontext = ServletUtil.getSessionContext(session);
		log = new Logging();
		log.setDebugFlag(true);
		log.logInfo("org.yafra.tests.serverdirectclient - logging init done - getting session now");
		sess = new YafraDirectSession();
		sess.setLogging(log);
		sess.setContext(dbcontext);
		sess.logMessage(" - client starts now with session id " + sess.getSessionId());

		MHPerson mhp = new MHPerson(dbcontext, log);
		List<Person> pl = mhp.getPersons();
		List<String> a = new ArrayList<String>();
		Iterator<Person> it = pl.iterator();
		while (it.hasNext())
			{
			Person i = (Person) it.next();
			a.add(i.getName());
			}
		return a;
	}

	@Override
	public void insertPerson(WSPerson person) {
		// TODO insert a new person into the db
	}

}
