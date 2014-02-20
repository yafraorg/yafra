package org.yafra.server.jee.servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Iterator;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.cayenne.access.DataContext;
import org.apache.cayenne.BaseContext;
import org.apache.cayenne.ObjectContext;
import org.yafra.directclient.YafraDirectSession;
import org.yafra.modelhandler.MHPerson;
import org.yafra.orm.Person;
import org.yafra.utils.Logging;

/**
 * Servlet implementation class PersonServlet
 */
@WebServlet(description = "List all persons", urlPatterns = { "/PersonServlet" })
public class PersonServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public PersonServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO simple servlet - use more advanced logging and sharing between servlets
		HttpSession session = request.getSession(true);
		//DataContext dbcontext = ServletUtil.getSessionContext(session);
		ObjectContext dbcontext = BaseContext.getThreadObjectContext();
		PrintWriter out = response.getWriter();
		YafraDirectSession sess = null;
		Logging yafralog = null;
		String dev = "stdout";
		yafralog = new Logging();
		yafralog.setDebugFlag(true);
		yafralog.YafraDebug("org.yafra.internet - got cayenne context and init finished", dev);
		yafralog.logInfo("org.yafra.internet - got cayenne context and init finished");
		sess = new YafraDirectSession();
		//sess.setContext(dbcontext);
		sess.setLogging(yafralog);
		sess.logMessage(" - simple servlet session started with id " + sess.getSessionId());
		sess.logMessage("\norg.yafra.tests - get person list");
		MHPerson mhp = new MHPerson(sess.getContext(), sess.getLogging());
		List<Person> pl = mhp.getPersons();
		Iterator<Person> it = pl.iterator();
		while (it.hasNext())
			{
			Person i = (Person) it.next();
			out.printf("%s %s\n", i.getName(), i.getFirstname());
			}
		sess.logMessage("- list done");
		sess.logMessage(" - end");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO doPost not used and empty
	}

}
