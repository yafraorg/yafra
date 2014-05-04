package org.yafra.gwt.admin.server;

import java.util.List;

import javax.servlet.http.HttpSession;

import org.apache.cayenne.BaseContext;
import org.apache.cayenne.ObjectContext;
import org.apache.cayenne.access.DataContext;
import org.yafra.directclient.YafraDirectSession;
import org.yafra.gwt.admin.client.YafraAdminService;
import org.yafra.gwt.admin.shared.FieldVerifier;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraUser;
import org.yafra.orm.YafraUser;
import org.yafra.utils.Logging;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;


/**
 * The server side implementation of the RPC service.
 */
@SuppressWarnings("serial")
public class YafraAdminServiceImpl extends RemoteServiceServlet implements YafraAdminService {

	public String doLogin(String name, String pwd) throws IllegalArgumentException {
		HttpSession httpSession;
		httpSession = getThreadLocalRequest().getSession();
		
		// Verify that the input is valid. 
		if (!FieldVerifier.isValidName(name)) {
			// If the input is not valid, throw an IllegalArgumentException back to
			// the client.
			throw new IllegalArgumentException(
					"Name must be at least 4 characters long");
		}

		String serverInfo = getServletContext().getServerInfo();
		String userAgent = getThreadLocalRequest().getHeader("User-Agent");

		// Escape data from the client to avoid cross-site script vulnerabilities.
		name = escapeHtml(name);
		pwd = escapeHtml(pwd);
		userAgent = escapeHtml(userAgent);

		ObjectContext dbcontext = BaseContext.getThreadObjectContext();
		YafraDirectSession sess = null;
		Logging yafralog = null;
		String dev = "stdout";
		yafralog = new Logging();
		yafralog.setDebugFlag(true);
		yafralog.YafraDebug("org.yafra.internet - got cayenne context and init finished", dev);
		yafralog.logInfo("org.yafra.internet - got cayenne context and init finished");
		sess = new YafraDirectSession();
		sess.setContext(dbcontext);
		sess.setLogging(yafralog);
		sess.logMessage(" - simple servlet session started with id " + sess.getSessionId());
		sess.logMessage("\norg.yafra.tests - get person list");
		MHYafraUser mhp = new MHYafraUser(sess.getContext(), sess.getLogging());
		YafraUser yu = mhp.selectUser(name);
		sess.logMessage("- list done");
		sess.logMessage(" - end");
		name = "YAFRA: " + yu.getName() + yu.getUserid();

		return "Hello, " + name + ". I am running " + serverInfo
				+ ". You run on:" + userAgent;
	}

	public List<MYafraUser> getUserList(int location) throws IllegalArgumentException {
		HttpSession httpSession;
		httpSession = getThreadLocalRequest().getSession();
		ObjectContext dbcontext = BaseContext.getThreadObjectContext();
		YafraDirectSession sess = null;
		Logging yafralog = null;
		String dev = "stdout";
		yafralog = new Logging();
		yafralog.setDebugFlag(true);
		yafralog.YafraDebug("org.yafra.internet - got cayenne context and init finished", dev);
		yafralog.logInfo("org.yafra.internet - got cayenne context and init finished");
		sess = new YafraDirectSession();
		sess.setContext(dbcontext);
		sess.setLogging(yafralog);
		sess.logMessage(" - simple servlet session started with id " + sess.getSessionId());
		sess.logMessage("\norg.yafra.tests - get person list");
		MHYafraUser mhp = new MHYafraUser(sess.getContext(), sess.getLogging());
		List<MYafraUser> myul = mhp.getMUsers();
		sess.logMessage("- list done");
		sess.logMessage(" - end");
		return myul;
	}
	public MYafraUser getUser(String UserId) {
		return null;
	}
	public Integer changeUser(MYafraUser myu, int operation) {
		return 1;
	}

	/**
	 * Escape an html string. Escaping data received from the client helps to
	 * prevent cross-site script vulnerabilities.
	 * 
	 * @param html the html string to escape
	 * @return the escaped string
	 */
	private String escapeHtml(String html) {
		if (html == null) {
			return null;
		}
		return html.replaceAll("&", "&amp;").replaceAll("<", "&lt;")
				.replaceAll(">", "&gt;");
	}
}
