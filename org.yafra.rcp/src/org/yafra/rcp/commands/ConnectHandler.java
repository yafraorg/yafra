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
package org.yafra.rcp.commands;

import java.lang.reflect.InvocationTargetException;
import java.util.Properties;

import javax.naming.InitialContext;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.jface.dialogs.ErrorDialog;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.dialogs.ProgressMonitorDialog;
import org.eclipse.jface.operation.IRunnableWithProgress;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.IViewReference;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.handlers.HandlerUtil;
import org.yafra.rcp.GlobalSettings;
import org.yafra.rcp.LoginDialog;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;
import org.yafra.server.ejbRemote.YafraSessionRemote;

/**
 * connect handler
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: ConnectHandler.java,v 1.2 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class ConnectHandler extends AbstractHandler
{
	private static final String Lloginstartmon = "Log on in progress ...";

	private IWorkbenchWindow preferredWindow = null;

	private LoginDialog login = null;
	private GlobalSettings glob;

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.core.commands.IHandler#execute(org.eclipse.core.commands.
	 * ExecutionEvent)
	 */
	@SuppressWarnings("static-access")
	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException
		{
		glob = GlobalSettings.getSingletonObject();
		glob.setDebugmessage(" - start command connect and login");
		preferredWindow = HandlerUtil.getActiveWorkbenchWindow(event);
		if (glob.isYafraSessionConnected())
			{
			MessageDialog.openInformation(preferredWindow.getShell(), "Info", "You are already logged in - logoff first");
			return null;
			}
		login = new LoginDialog(preferredWindow.getShell());
		login.open();
		if (login.getReturnCode() == (int) login.OK)
			{
			ProgressMonitorDialog progressDialog = new ProgressMonitorDialog(preferredWindow.getShell());
			IRunnableWithProgress runnable = new IRunnableWithProgress()
				{
					public void run(IProgressMonitor progressMonitor) throws InterruptedException
						{
						progressMonitor.beginTask(Lloginstartmon, IProgressMonitor.UNKNOWN);
						try
							{
							// for the provider URL see as examples http://openejb.apache.org/clients.html
							// openejb in tomee http://127.0.0.1:8080/tomee/ejb
							// openejb standalone ejbd ejbd://localhost:4201
							String ServerURL = new String(String.format("http://%s:8080/tomee/ejb", login.getServer()));
							Properties prop = new Properties();
							prop.put(glob.getEjbcontext().INITIAL_CONTEXT_FACTORY, "org.apache.openejb.client.RemoteInitialContextFactory");
							prop.put("java.naming.provider.url", ServerURL);
							glob.setEjbcontext(new InitialContext(prop));
							progressMonitor.worked(1);
							glob.setDebugmessage(" - got context");
							glob.setYafrases((YafraSessionRemote) glob.getEjbcontext().lookup("YafraSessionRemote"));
							glob.setDebugmessage(" - got remote session class");
							glob.getYafrases().init();
							progressMonitor.worked(2);
							glob.setDebugmessage(" - got remote init");
							if (glob.getYafrases().Login(login.getUserid(), login.getPwd()))
								{
								glob.setYafraSessionConnected(true);
								glob.getStatusline().setMessage(null, "Ready - logged in");
								glob.setDebugmessage(" - login OK");
								GlobalSettings glob = GlobalSettings.getSingletonObject();
								glob.setServer(login.getServer());
								glob.setUser(login.getUserid());
								MHIYafraUserRemote mhiuser = (MHIYafraUserRemote) glob.getEjbcontext().lookup("MHIYafraUserRemote");
								glob.setUserModel(mhiuser.selectUser(login.getUserid()));
								glob.setUserRoles(mhiuser.getRoles(login.getUserid()));
								}
							else
								{
								glob.setDebugmessage(" - login NOT OK - EXIT NOW");
								glob.getStatusline().setMessage(null, "Ready - not logged in - ERROR with login - try again");
								glob.setYafraSessionConnected(false);
								return;
								}
							glob.setDebugmessage(" - version got from server: " + glob.getYafrases().getVersion());

							// TODO check why not returning
							progressMonitor.done();
							}
						catch (Exception e)
							{
							glob.setYafraSessionConnected(false);
							progressMonitor.done();
							Status status = new Status(IStatus.ERROR, "My Plug-in ID", 0, "EJB3 connection error", e);
							ErrorDialog.openError(Display.getCurrent().getActiveShell(), "EJB3 connection error", e.toString(), status);
							e.printStackTrace();
							}
						};
				};
			try
				{
				progressDialog.open();
				runnable.run(progressDialog.getProgressMonitor());
				}
			catch (InvocationTargetException e)
				{
				// TODO Auto-generated catch block
				e.printStackTrace();
				}
			catch (InterruptedException e)
				{
				// TODO Auto-generated catch block
				e.printStackTrace();
				}
			progressDialog.close();
			try
				{
				IViewReference ref = preferredWindow.getActivePage().findViewReference("org.yafra.rcp.LoginView");
				preferredWindow.getActivePage().hideView(ref);
				preferredWindow.getActivePage().showView("org.yafra.rcp.LoginView");
				}
			catch (PartInitException e)
				{
				// TODO Auto-generated catch block
				e.printStackTrace();
				}

			}

		return null;
		}

}
