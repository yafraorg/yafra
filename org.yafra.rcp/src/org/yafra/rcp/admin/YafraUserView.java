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
package org.yafra.rcp.admin;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.core.databinding.observable.list.WritableList;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.GroupMarker;
import org.eclipse.jface.action.MenuManager;
import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.ScrolledComposite;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Menu;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.IWorkbenchActionConstants;
import org.eclipse.ui.forms.widgets.Form;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.ui.forms.widgets.TableWrapLayout;
import org.eclipse.ui.part.ViewPart;
import org.yafra.model.MYafraUser;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;

/**
 * User View
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraUserView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.YafraUserView";

	private GlobalSettings glob;

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());

	// Yafra User table
	private YafraUserTable yu_table;
	private TableViewer viewerUser;
	private Table tableUser;
	private WritableList inputUser;
	List<MGYafraUser> users = new ArrayList<MGYafraUser>();
	private MGYafraUser YafraUserElement;
	private MHIYafraUserRemote mhiuser = null;

	// Yafra BusinessRole table
	private YafraBusRoleTable ybr_table;
	private TableViewer viewerRoles;
	private Table tableRoles;
	private WritableList inputRoles;
	List<MGYafraBusRole> roles = new ArrayList<MGYafraBusRole>();
	private MGYafraBusRole YafraBusRoleElement = null;

	// Yafra User Logs table
	private TableViewer viewerLogs;
	private Table tableLogs;
	private WritableList inputLogs;

	// Form fields for Yafra User
	private Text txtUsername;

	private Text txtUserID;

	private Text txtHttpwwwyafraorgpicgif;


	/**
	 * Constructor
	 * get global settings and inits user elements
	 */
	public YafraUserView()
		{
		YafraUserElement = null;
		YafraBusRoleElement = null;
		glob = GlobalSettings.getSingletonObject();
		ybr_table = new YafraBusRoleTable();
		yu_table = new YafraUserTable();
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.ui.part.WorkbenchPart#createPartControl(org.eclipse.swt.widgets
	 * .Composite)
	 */
	@Override
	public void createPartControl(Composite parent)
		{
		// create view
		createViewer(parent);

		// MASTER User - fill up table
		// Get the content for the viewer, setInput will call getElements in the contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());

		// MASTER User - fill up table
		yu_table.loadTableData(viewerUser, inputUser);

		// DETAIL Roles - fill up table
		ybr_table.loadTableData(viewerRoles, inputRoles);
		}

	private void createViewer(Composite parent)
		{
		parent.setLayout(new GridLayout(1, false));

		// --- Form MASTER
		Group Fmaster = new Group(parent, SWT.NONE);
		GridData gridData_2 = new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1);
		gridData_2.heightHint = 161;
		Fmaster.setLayoutData(gridData_2);
		formToolkit.adapt(Fmaster);
		formToolkit.paintBordersFor(Fmaster);
		Fmaster.setLayout(new GridLayout(1, false));

		ScrolledComposite scrolledComposite = new ScrolledComposite(Fmaster, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		scrolledComposite.setExpandVertical(true);
		GridData gridData = new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1);
		gridData.heightHint = 131;
		gridData.widthHint = 658;
		scrolledComposite.setLayoutData(gridData);
		scrolledComposite.setExpandHorizontal(true);

		// user table viewer
		inputUser = new WritableList(users, MGYafraUser.class);
		viewerUser = new TableViewer(scrolledComposite, SWT.MULTI | SWT.FULL_SELECTION);
		yu_table.createTable(viewerUser, users);
		viewerUser.addSelectionChangedListener(new ISelectionChangedListener()
			{
				public void selectionChanged(SelectionChangedEvent event)
					{
					if (event.getSelection().isEmpty())
						{
						// if the selection is empty clear the labels
						glob.setDebugmessage(" - selection change is empty");
						YafraUserElement.setUserId("");
						YafraUserElement.setName("");
						YafraUserElement.setPicturelink("");
						return;
						}
					if (event.getSelection() instanceof IStructuredSelection)
						{
						IStructuredSelection selection = (IStructuredSelection) event.getSelection();
						YafraUserElement = (MGYafraUser) selection.getFirstElement();
						glob.setDebugmessage(" - selection changed on master table to " + YafraUserElement.getName());
						txtUsername.setText(YafraUserElement.getName());
						if (YafraUserElement.getUserId() != null) txtUserID.setText(YafraUserElement.getUserId());
						if (YafraUserElement.getPicturelink() != null) txtHttpwwwyafraorgpicgif.setText(YafraUserElement.getPicturelink());
						viewerUser.refresh();
						ybr_table.fillTable(roles);
						viewerRoles.refresh();
						}
					}
			});
		getSite().setSelectionProvider(viewerUser);

		MenuManager menuMgr = new MenuManager();
		menuMgr.add(new Action("Delete") {	public void run() { glob.setDebugmessage(" - delete action run now"); yu_table.deleteEntry(inputUser, getSite().getSelectionProvider().getSelection()); } });
		menuMgr.add(new GroupMarker(IWorkbenchActionConstants.MB_ADDITIONS));
		getSite().registerContextMenu(menuMgr, viewerUser);
		// getSite().registerContextMenu(menuMgr,getSite().getSelectionProvider());
		Control control = viewerUser.getControl();
		Menu menu = menuMgr.createContextMenu(control);
		control.setMenu(menu);
		tableUser = viewerUser.getTable();
		formToolkit.paintBordersFor(tableUser);
		scrolledComposite.setContent(tableUser);
		formToolkit.adapt(scrolledComposite, true, true);

		// --- Form DETAILS tabs
		TabFolder Fdetails = new TabFolder(parent, SWT.NONE);
		GridData gridData_1 = new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1);
		gridData_1.heightHint = 207;
		gridData_1.widthHint = 643;
		Fdetails.setLayoutData(gridData_1);

		// --- Form DETAILS tab USER DETAILS
		TabItem tbtmForm = new TabItem(Fdetails, SWT.NONE);
		tbtmForm.setText("User details");

		Form frmUser = formToolkit.createForm(Fdetails);
		tbtmForm.setControl(frmUser);
		formToolkit.paintBordersFor(frmUser);
		frmUser.setText("User");
		frmUser.getToolBarManager().add(new Action("New")
			{
			@Override
			public void run()
				{
				yu_table.getMHIUser();
				MYafraUser myu = new MYafraUser();
				myu.setName(txtUsername.getText());
				myu.setUserid(txtUserID.getText());
				myu.setPicturelink(txtHttpwwwyafraorgpicgif.getText());
				mhiuser.insertUser(myu);
				MGYafraUser NewYU = new MGYafraUser();
				NewYU.setName(txtUsername.getText());
				NewYU.setUserId(txtUserID.getText());
				NewYU.setPicturelink(txtHttpwwwyafraorgpicgif.getText());
				inputUser.add(NewYU);
				}
			});
		frmUser.getToolBarManager().add(new Action("Update")
			{
			@Override
			public void run()
				{
				if (YafraUserElement == null)
					{
					return;
					}
				yu_table.getMHIUser();
				MYafraUser myu = new MYafraUser();
				myu.setName(txtUsername.getText());
				myu.setUserid(txtUserID.getText());
				myu.setPicturelink(txtHttpwwwyafraorgpicgif.getText());
				mhiuser.updateUser(myu);
				YafraUserElement.setName(txtUsername.getText());
				YafraUserElement.setPicturelink(txtHttpwwwyafraorgpicgif.getText());
				viewerUser.update(YafraUserElement, null);
				viewerUser.refresh();
				// TODO refresh table with modified data
				}
			});
		frmUser.getToolBarManager().add(new Action("Clear")
			{
				@Override
				public void run()
					{
					txtUsername.setText("");
					txtUserID.setText("");
					txtHttpwwwyafraorgpicgif.setText("");
					}
			});
		frmUser.getToolBarManager().add(new Action("Export") { });
		frmUser.getToolBarManager().update(true);

		Label lblUsername = formToolkit.createLabel(frmUser.getBody(), "Username", SWT.NONE);
		lblUsername.setBounds(10, 25, 55, 15);
		txtUsername = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtUsername.setText("");
		txtUsername.setBounds(87, 22, 212, 21);

		Label lblUserId = formToolkit.createLabel(frmUser.getBody(), "User ID", SWT.NONE);
		lblUserId.setBounds(10, 49, 55, 15);
		txtUserID = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtUserID.setText("");
		txtUserID.setToolTipText("The user id is not modifiable");
		//txtUserID.setEditable(false);
		txtUserID.setBounds(87, 46, 212, 21);

		Label lblPictureLink = formToolkit.createLabel(frmUser.getBody(), "Picture link", SWT.NONE);
		lblPictureLink.setBounds(10, 73, 71, 15);
		txtHttpwwwyafraorgpicgif = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtHttpwwwyafraorgpicgif.setText("");
		txtHttpwwwyafraorgpicgif.setBounds(87, 73, 330, 21);

		// --- Form DETAILS tab ROLES per user
		TabItem tbtmJfaceTreeviewer = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTreeviewer.setText("Roles");

		Form frmAssignedRoles = formToolkit.createForm(Fdetails);
		tbtmJfaceTreeviewer.setControl(frmAssignedRoles);
		formToolkit.paintBordersFor(frmAssignedRoles);
		frmAssignedRoles.setText("Assigned roles");
		frmAssignedRoles.getToolBarManager().add(new Action("Assing new role")
			{
			@Override
			public void run()
				{
				// TODO check if noaccess is given - if so stop and provide message to delete this role first
				YafraUserAddBusRoleDialog addnew = new YafraUserAddBusRoleDialog(getSite().getShell());
				addnew.open();
				if (addnew.getReturnCode() == (int) addnew.OK)
					{
					List<MGYafraBusRole> rbrl = addnew.getSelection();
			      for(Iterator<MGYafraBusRole> iterator = rbrl.iterator(); iterator.hasNext();)
			      	{
			      	MGYafraBusRole mgybr = iterator.next();
			      	// TODO make this a real contains of the list - inputRoles.contains() does not work
			      	// check if already set - if so skip
			      	String name1 = inputRoles.toString();
			      	String name2 = mgybr.getName();
						if (name1.contains(name2))
							{
							return;
							}
						inputRoles.add(mgybr);
						ybr_table.addRole(mgybr, getSite().getSelectionProvider().getSelection(), mhiuser);
			      	}
			      	viewerRoles.refresh();
					}
				}
			});
		frmAssignedRoles.getToolBarManager().add(new Action("Delete selected role")
			{
			@Override
			public void run()
				{
				if (YafraBusRoleElement != null)
					{
					inputRoles.remove(YafraBusRoleElement);
					ybr_table.removeRole(YafraBusRoleElement, getSite().getSelectionProvider().getSelection(), mhiuser);
					viewerRoles.refresh();
					}
				}
			});
		frmAssignedRoles.getToolBarManager().add(new Action("Delete all roles") { });
		// TODO remove assignment MHI call to be implemented and for delete all loop over all and delete the assignments
		frmAssignedRoles.getToolBarManager().update(true);

		// role table viewer
		frmAssignedRoles.getBody().setLayout(new GridLayout(1, false));
		ScrolledComposite scrolledComposite_1 = new ScrolledComposite(frmAssignedRoles.getBody(), SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		scrolledComposite_1.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.adapt(scrolledComposite_1);
		formToolkit.paintBordersFor(scrolledComposite_1);
		scrolledComposite_1.setExpandHorizontal(true);
		scrolledComposite_1.setExpandVertical(true);
		viewerRoles = new TableViewer(scrolledComposite_1, SWT.MULTI | SWT.FULL_SELECTION);
		inputRoles = new WritableList(roles, MGYafraBusRole.class);
		ybr_table.createTable(viewerRoles, roles);
		viewerRoles.addSelectionChangedListener(new ISelectionChangedListener()
			{
				public void selectionChanged(SelectionChangedEvent event)
					{
					if (!event.getSelection().isEmpty() && event.getSelection() instanceof IStructuredSelection)
						{
						IStructuredSelection selection = (IStructuredSelection) event.getSelection();
						YafraBusRoleElement = (MGYafraBusRole) selection.getFirstElement();
						glob.setDebugmessage(" - selection on role table to " + YafraBusRoleElement.getName());
						}
					}
			});
		tableRoles = viewerRoles.getTable();
		formToolkit.paintBordersFor(tableRoles);
		formToolkit.adapt(tableRoles, true, true);
		scrolledComposite_1.setContent(tableRoles);
		scrolledComposite_1.setMinSize(tableRoles.computeSize(SWT.DEFAULT, SWT.DEFAULT));

		// --- Form DETAILS tab AUDITS per user
		TabItem tbtmJfaceTable = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTable.setText("Auditlog");

		Form frmAuditlog = formToolkit.createForm(Fdetails);
		tbtmJfaceTable.setControl(frmAuditlog);
		formToolkit.paintBordersFor(frmAuditlog);
		frmAuditlog.setText("Auditlog");
			{
			frmAuditlog.getBody().setLayout(new TableWrapLayout());
			}
		frmAuditlog.getToolBarManager().add(new Action("Clear log") { });
		frmAuditlog.getToolBarManager().add(new Action("Add log entry") { });
		frmAuditlog.getToolBarManager().update(true);

		//viewerLogs = new TableViewer(scrldfrmAuditlog.getBody(), SWT.MULTI | SWT.FULL_SELECTION);
		//tableAuditLog = formToolkit.createTable(scrldfrmAuditlog.getBody(), SWT.NONE);
		//tableAuditLog.setLayoutData(new TableWrapData(TableWrapData.FILL_GRAB, TableWrapData.FILL_GRAB, 1, 1));
		//formToolkit.paintBordersFor(tableAuditLog);
		//tableAuditLog.setHeaderVisible(true);
		//tableAuditLog.setLinesVisible(true);
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.ui.part.WorkbenchPart#setFocus()
	 */
	@Override
	public void setFocus()
		{
		viewerUser.getControl().setFocus();
		}

	public void dispose() {
   	}

}
