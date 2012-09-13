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
package org.yafra.rcp;

import java.util.List;

import javax.naming.Context;

import org.eclipse.jface.action.IStatusLineManager;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;
import org.yafra.server.ejbRemote.YafraSessionRemote;
import org.yafra.utils.Logging;

/**
 * Global session data on client (singleton)
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: GlobalSettings.java,v 1.2 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class GlobalSettings
{
	// user session settings
	private Context ejbcontext = null;
	private YafraSessionRemote yafrases = null;
	private boolean YafraSessionConnected = false;
	private String user;
	private MYafraUser myu;
	private List<MYafraBusinessRole> mybrlist;
	private String server;
	private String language;
	// logging
	private Logging rcplog;
	private static final String dev = "stdout";
	// other GUI globals
	private IStatusLineManager statusline = null;

	// itself
   private static GlobalSettings ref;

	private GlobalSettings()
   {
   	YafraSessionConnected = false;
      user = "";
      server = "localhost";
      language = "en";
		rcplog = new Logging();
		rcplog.setDebugFlag(true);
		rcplog.YafraDebug("\norg.yafra.rcp - start rcp at singleton construction", dev);
		myu = null;
		mybrlist = null;
   }

   public static synchronized GlobalSettings getSingletonObject()
   {
     if (ref == null)
         // it's ok, we can call this constructor
         ref = new GlobalSettings();
     return ref;
   }

	public synchronized String getUser() {return user;}
	public synchronized void setUser(String user) {this.user = user;}
	
	public synchronized MYafraUser getUserModel() {return myu;}
	public synchronized void setUserModel(MYafraUser user) {this.myu = user;}
	
	public synchronized List<MYafraBusinessRole> getUserRoles() {return mybrlist;}
	public synchronized void setUserRoles(List<MYafraBusinessRole> rolelist) {this.mybrlist = rolelist;}

	public synchronized String getServer() {return server;}
	public synchronized void setServer(String server) {this.server = server;}

	public synchronized String getLanguage() {return language;}
	public synchronized void setLanguage(String language) {this.language = language;}

	public synchronized Context getEjbcontext() {return ejbcontext;}
	public synchronized void setEjbcontext(Context ejbcontext) {this.ejbcontext = ejbcontext;}

	public synchronized YafraSessionRemote getYafrases() {return yafrases;}
	public synchronized void setYafrases(YafraSessionRemote yafrases) {this.yafrases = yafrases;}

	public synchronized boolean isYafraSessionConnected() {return YafraSessionConnected;}
	public synchronized void setYafraSessionConnected(boolean yafraSessionConnected) {YafraSessionConnected = yafraSessionConnected;}

	public synchronized Logging getRcplog() {return rcplog;}
	public synchronized void setRcplog(Logging rcplog) {this.rcplog = rcplog;}

	public synchronized IStatusLineManager getStatusline() {return statusline;}
	public synchronized void setStatusline(IStatusLineManager statusline) {this.statusline = statusline;}
	
	public synchronized void setDebugmessage(String message) {rcplog.YafraDebug(message, dev);}
}
