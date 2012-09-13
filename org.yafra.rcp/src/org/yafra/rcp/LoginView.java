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

import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.commands.Command;
import org.eclipse.core.commands.ParameterizedCommand;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Label;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.commands.ICommandService;
import org.eclipse.ui.forms.events.ExpansionAdapter;
import org.eclipse.ui.forms.events.ExpansionEvent;
import org.eclipse.ui.forms.events.HyperlinkAdapter;
import org.eclipse.ui.forms.events.HyperlinkEvent;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.ui.forms.widgets.Hyperlink;
import org.eclipse.ui.forms.widgets.ScrolledForm;
import org.eclipse.ui.forms.widgets.Section;
import org.eclipse.ui.forms.widgets.TableWrapData;
import org.eclipse.ui.forms.widgets.TableWrapLayout;
import org.eclipse.ui.handlers.IHandlerService;
import org.eclipse.ui.part.ViewPart;
import org.eclipse.ui.statushandlers.StatusManager;
import org.yafra.utils.WhichOS;

/**
 * Login View
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: LoginView.java,v 1.2 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class LoginView extends ViewPart
	{
	public LoginView()
		{}

	public static final String ID = "org.yafra.rcp.LoginView";

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());
	private ScrolledForm scrldfrmLogin;

	private String version = "";
	private String sessionid = "";
	private String username = "";
	private String picturelink = "http://www.yafra.org/";

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.ui.part.WorkbenchPart#createPartControl(org.eclipse.swt.widgets .Composite)
	 */
	@SuppressWarnings("static-access")
	@Override
	public void createPartControl(Composite parent)
		{
		String connectmessage;
		GlobalSettings glob = GlobalSettings.getSingletonObject();
		glob.setDebugmessage(" - create view " + ID);
		IActionBars bars = getViewSite().getActionBars();
		glob.setStatusline(bars.getStatusLineManager());
		if (glob.isYafraSessionConnected())
			{
			sessionid = glob.getYafrases().getSessionId();
			version = glob.getYafrases().getVersion();
			connectmessage = "Logged in - session established with server";
			username = glob.getUserModel().getName();
			picturelink = glob.getUserModel().getPicturelink();
			}
		else
			{
			connectmessage = "Not logged in - please connect again";
			}

		glob.getStatusline().setMessage(connectmessage);

		parent.setLayout(new GridLayout(1, false));

		scrldfrmLogin = formToolkit.createScrolledForm(parent);
		scrldfrmLogin.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.paintBordersFor(scrldfrmLogin);
		scrldfrmLogin.setText("Login");
			{
			TableWrapLayout tableWrapLayout = new TableWrapLayout();
			tableWrapLayout.numColumns = 3;
			scrldfrmLogin.getBody().setLayout(tableWrapLayout);
			}

		Label lblLogin = formToolkit.createLabel(scrldfrmLogin.getBody(), "Login status", SWT.NONE);
		if (glob.isYafraSessionConnected())
			connectmessage = "Logged in - session established with server";
		else connectmessage = "Not logged in - please connect again";

		Label lblLoginValue = formToolkit.createLabel(scrldfrmLogin.getBody(), connectmessage, SWT.NONE);
		new Label(scrldfrmLogin.getBody(), SWT.NONE);

		Label lblName = formToolkit.createLabel(scrldfrmLogin.getBody(), "Name", SWT.NONE);
		Label lblNameValue = formToolkit.createLabel(scrldfrmLogin.getBody(), username, SWT.NONE);

		Label lblDocumentation = formToolkit.createLabel(scrldfrmLogin.getBody(), "Documentation", SWT.NONE);

		Label lblUserId = formToolkit.createLabel(scrldfrmLogin.getBody(), "User ID", SWT.NONE);
		Label lblUserIdValue = formToolkit.createLabel(scrldfrmLogin.getBody(), glob.getUser(), SWT.NONE);
		Hyperlink hprlnkYafraorg = formToolkit.createHyperlink(scrldfrmLogin.getBody(), "yafra.org", SWT.NONE);
		hprlnkYafraorg.addHyperlinkListener(new HyperlinkAdapter()
			{
				public void linkActivated(HyperlinkEvent e)
					{
					ICommandService cS = (ICommandService) getSite().getService(ICommandService.class);
					IHandlerService hS = (IHandlerService) getSite().getService(IHandlerService.class);
					Command openView = cS.getCommand("org.yafra.rcp.commands.Browse");
					Map<String, String> params = new HashMap<String, String>();
					params.put("org.yafra.rcp.commands.Browse.url", "http://www.yafra.org");
					ParameterizedCommand pC = ParameterizedCommand.generateCommand(openView, params);
					try
						{
						hS.executeCommand(pC, null);
						}
					catch (Exception ex)
						{
						ex.printStackTrace();
						Status status = new Status(IStatus.ERROR, "My Plug-in ID", 0, "Hyperlink activation error", ex);
						StatusManager.getManager().handle(status, StatusManager.SHOW);
						}
					;
					}
			});

		formToolkit.paintBordersFor(hprlnkYafraorg);

		Label lblPicture = formToolkit.createLabel(scrldfrmLogin.getBody(), "Picture", SWT.NONE);
		Hyperlink imageUser = formToolkit.createHyperlink(scrldfrmLogin.getBody(), "picture.link", SWT.NONE);
		imageUser.addHyperlinkListener(new HyperlinkAdapter()
			{
				public void linkActivated(HyperlinkEvent e)
					{
					ICommandService cS = (ICommandService) getSite().getService(ICommandService.class);
					IHandlerService hS = (IHandlerService) getSite().getService(IHandlerService.class);
					Command openView = cS.getCommand("org.yafra.rcp.commands.Browse");
					Map<String, String> params = new HashMap<String, String>();
					params.put("org.yafra.rcp.commands.Browse.url", picturelink);
					ParameterizedCommand pC = ParameterizedCommand.generateCommand(openView, params);
					try
						{
						hS.executeCommand(pC, null);
						}
					catch (Exception ex)
						{
						ex.printStackTrace();
						Status status = new Status(IStatus.ERROR, "My Plug-in ID", 0, "Hyperlink activation error", ex);
						StatusManager.getManager().handle(status, StatusManager.SHOW);
						}
					;
					}
			});

		formToolkit.paintBordersFor(imageUser);
		imageUser.setText("picture link");
		new Label(scrldfrmLogin.getBody(), SWT.NONE);

		// SERVER section
		Section sctnServerVersion = formToolkit.createSection(scrldfrmLogin.getBody(), Section.TWISTIE | Section.TITLE_BAR | Section.EXPANDED | Section.DESCRIPTION);
		sctnServerVersion.setDescription("Here is some information from your connected server");
		formToolkit.paintBordersFor(sctnServerVersion);
		sctnServerVersion.setText("Server information");
		TableWrapData td = new TableWrapData(TableWrapData.LEFT);
		td.valign = TableWrapData.FILL;
		td.colspan = 2;
		sctnServerVersion.setLayoutData(td);
		sctnServerVersion.addExpansionListener(new ExpansionAdapter()
			{
				public void expansionStateChanged(ExpansionEvent e)
					{
					scrldfrmLogin.reflow(true);
					}
			});
		Composite sectionClient = formToolkit.createComposite(sctnServerVersion);
		GridLayout gridLayout = new GridLayout();
		gridLayout.numColumns = 2;
		sectionClient.setLayout(gridLayout);
		Label lblServer = formToolkit.createLabel(sectionClient, "Server Name is", SWT.NONE);
		Label lblServerValue = formToolkit.createLabel(sectionClient, glob.getServer(), SWT.NONE);

		Label lblSessionId = formToolkit.createLabel(sectionClient, "Session ID", SWT.NONE);
		Label lblSessionValue = formToolkit.createLabel(sectionClient, sessionid, SWT.NONE);

		Label lblVersion = formToolkit.createLabel(sectionClient, "Version", SWT.NONE);
		Label lblVersionValue = formToolkit.createLabel(sectionClient, version, SWT.NONE);
		lblVersionValue.setLayoutData(new GridData(SWT.LEFT, SWT.TOP, false, false, 1, 1));
		sctnServerVersion.setClient(sectionClient);

		// CLIENT section
		Section sctnClientInformation = formToolkit.createSection(scrldfrmLogin.getBody(), Section.DESCRIPTION | Section.TWISTIE | Section.TITLE_BAR);
		sctnClientInformation.setDescription("Here is some information from your client");
		formToolkit.paintBordersFor(sctnClientInformation);
		sctnClientInformation.setText("Client information");
		Composite composite = formToolkit.createComposite(sctnClientInformation, SWT.NONE);
		formToolkit.paintBordersFor(composite);
		sctnClientInformation.setClient(composite);
		composite.setLayout(new GridLayout(2, false));
		Label lblClientVersion = formToolkit.createLabel(composite, "Version", SWT.NONE);
		Label lblClientVersionValue = formToolkit.createLabel(composite, "1.0", SWT.NONE);

		Label lblOs = formToolkit.createLabel(composite, "OS", SWT.NONE);
		WhichOS os = new WhichOS();
		Label lblOsValue = formToolkit.createLabel(composite, os.getOsName(), SWT.NONE);
		sctnClientInformation.setExpanded(true);
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.ui.part.WorkbenchPart#setFocus()
	 */
	@Override
	public void setFocus()
		{
		// TODO Auto-generated method stub

		}
	}
