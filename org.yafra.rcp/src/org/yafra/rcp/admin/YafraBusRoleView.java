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
import org.eclipse.swt.widgets.Button;
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
import org.yafra.model.MYafraBusinessRole;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote;


/**
 * User View
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraBusRoleView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.admin.YafraBusRoleView";

	private GlobalSettings glob;

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());

	// Yafra BusinessRole table
	private YafraBusRoleTable ybr_table;
	private TableViewer viewerBRoles;
	private Table tableBRoles;
	private WritableList inputBRoles;
	private MGYafraBusRole YafraBusRoleElement = null;
	private MHIYafraBusinessRoleRemote mhibrole = null;
	private List<MGYafraBusRole> broles = new ArrayList<MGYafraBusRole>();

	// Yafra Role table (technical roles associated to business role)
	private YafraTechRoleTable ytr_table;
	private TableViewer viewerRoles;
	private Table tableRoles;
	private WritableList inputRoles;
	private MGYafraTechRole YafraRoleElement;
	List<MGYafraTechRole> roles = new ArrayList<MGYafraTechRole>();

	// Yafra User table (which user has this business role)
	private YafraUserTable yu_table;
	private TableViewer viewerUsers;
	private Table tableUsers;
	private WritableList inputUser;
	List<MGYafraUser> users = new ArrayList<MGYafraUser>();
	private MGYafraUser YafraUserElement;

	// Form fields for Yafra Business Role
	private String txtId;
	private Text txtName;
	private Boolean checkbFlag;
	Button btnCheckButton;
	private Text txtDesc;

	/**
	 * Constructor
	 * get global settings and inits user elements
	 */
	public YafraBusRoleView()
		{
		YafraBusRoleElement = null;
		YafraRoleElement = null;
		glob = GlobalSettings.getSingletonObject();
		ybr_table = new YafraBusRoleTable();
		ytr_table = new YafraTechRoleTable();
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
		ybr_table.loadTableData(viewerBRoles, inputBRoles);

		// DETAIL Roles - fill up table
		ytr_table.loadTableData(viewerRoles, inputRoles);
		// DETAIL Users - fill up table
		yu_table.loadTableData(viewerUsers, inputUser);
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

		// business role table viewer
		viewerBRoles = new TableViewer(scrolledComposite, SWT.MULTI | SWT.FULL_SELECTION);
		inputBRoles = new WritableList(broles, MGYafraBusRole.class);
		ybr_table.createTable(viewerBRoles, broles);
		viewerBRoles.addSelectionChangedListener(new ISelectionChangedListener()
			{
			public void selectionChanged(SelectionChangedEvent event)
				{
				if (event.getSelection().isEmpty())
					{
					// if the selection is empty clear the labels
					glob.setDebugmessage(" - selection change is empty");
					if (YafraBusRoleElement == null) {	return; }
					YafraBusRoleElement.setName("");
					YafraBusRoleElement.setDescription("");
					YafraBusRoleElement.setFlag(false);
					return;
					}
				if (event.getSelection() instanceof IStructuredSelection)
					{
					IStructuredSelection selection = (IStructuredSelection) event.getSelection();
					YafraBusRoleElement = (MGYafraBusRole) selection.getFirstElement();
					if (YafraBusRoleElement.getName() != null) txtName.setText(YafraBusRoleElement.getName());
					if (YafraBusRoleElement.getDescription() != null) txtDesc.setText(YafraBusRoleElement.getDescription());
					if (YafraBusRoleElement.getFlag() != null) {checkbFlag = YafraBusRoleElement.getFlag(); btnCheckButton.setSelection(checkbFlag);}
					viewerBRoles.refresh();
					ytr_table.fillTable(roles, YafraBusRoleElement);
					viewerRoles.refresh();
					glob.setDebugmessage(" - selection changed on master table to " + YafraBusRoleElement.getName());
					}
				}
			});
		getSite().setSelectionProvider(viewerBRoles);

		MenuManager menuMgr = new MenuManager();
		menuMgr.add(new Action("Delete") {	public void run() { glob.setDebugmessage(" - delete action run now"); ybr_table.deleteEntry(inputBRoles, getSite().getSelectionProvider().getSelection()); } });
		menuMgr.add(new GroupMarker(IWorkbenchActionConstants.MB_ADDITIONS));
		getSite().registerContextMenu(menuMgr, viewerBRoles);
		// getSite().registerContextMenu(menuMgr,getSite().getSelectionProvider());
		Control control = viewerBRoles.getControl();
		Menu menu = menuMgr.createContextMenu(control);
		control.setMenu(menu);
		tableBRoles = viewerBRoles.getTable();
		formToolkit.paintBordersFor(tableBRoles);
		scrolledComposite.setContent(tableBRoles);
		formToolkit.adapt(scrolledComposite, true, true);

		// --- Form DETAILS tabs
		TabFolder Fdetails = new TabFolder(parent, SWT.NONE);
		GridData gridData_1 = new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1);
		gridData_1.widthHint = 643;
		Fdetails.setLayoutData(gridData_1);

		// --- Form DETAILS tab BUS ROLE DETAILS
		TabItem tbtmForm = new TabItem(Fdetails, SWT.NONE);
		tbtmForm.setText("Role details");

		Form frmUser = formToolkit.createForm(Fdetails);
		tbtmForm.setControl(frmUser);
		formToolkit.paintBordersFor(frmUser);
		frmUser.setText("Role");
		frmUser.getToolBarManager().add(new Action("New")
			{
			@Override
			public void run()
				{
				mhibrole = ybr_table.getMHIBusRoles();
				MYafraBusinessRole mybr = new MYafraBusinessRole();
				mybr.setName(txtName.getText());
				mybr.setDescription(txtDesc.getText());
				mybr.setFlag(checkbFlag);
				mhibrole.insertBusinessRole(mybr);
				MGYafraBusRole NewYBR = new MGYafraBusRole();
				NewYBR.setName(txtName.getText());
				NewYBR.setDescription(txtDesc.getText());
				NewYBR.setFlag(checkbFlag);
				inputBRoles.add(NewYBR);
				}
			});
		frmUser.getToolBarManager().add(new Action("Update")
			{
			@Override
			public void run()
				{
				if (YafraBusRoleElement == null) {	return; }
				mhibrole = ybr_table.getMHIBusRoles();
				MYafraBusinessRole mybr = new MYafraBusinessRole();
				mybr.setName(txtName.getText());
				mybr.setDescription(txtDesc.getText());
				mybr.setFlag(checkbFlag);
				mhibrole.updateBusinessRole(mybr);
				YafraBusRoleElement.setName(txtName.getText());
				YafraBusRoleElement.setDescription(txtDesc.getText());
				YafraBusRoleElement.setFlag(checkbFlag);
				viewerBRoles.update(YafraBusRoleElement, null);
				viewerBRoles.refresh();
				// TODO refresh table with modified data
				}
			});
		frmUser.getToolBarManager().add(new Action("Clear")
			{
			@Override
			public void run()
				{
				txtName.setText("");
				txtId = "";
				txtDesc.setText("");
				checkbFlag = false;
				}
			});
		frmUser.getToolBarManager().add(new Action("Export") { });
		frmUser.getToolBarManager().update(true);
		
		Label lblId = formToolkit.createLabel(frmUser.getBody(), "ID", SWT.NONE);
		lblId.setBounds(10, 23, 55, 15);
		Label lblIdFill = formToolkit.createLabel(frmUser.getBody(), txtId, SWT.NONE);
		lblIdFill.setBounds(87, 23, 55, 15);

		Label lblName = formToolkit.createLabel(frmUser.getBody(), "Name", SWT.NONE);
		lblName.setBounds(10, 48, 55, 15);
		txtName = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtName.setText("");
		txtName.setBounds(87, 45, 402, 21);

		Label lblFlag = formToolkit.createLabel(frmUser.getBody(), "Active ?", SWT.NONE);
		lblFlag.setBounds(10, 73, 55, 15);
		btnCheckButton = new Button(frmUser.getBody(), SWT.CHECK);
		btnCheckButton.setBounds(87, 72, 93, 16);
		formToolkit.adapt(btnCheckButton, true, true);
		checkbFlag = false;
		btnCheckButton.setEnabled(true);

		Label lblNotes = formToolkit.createLabel(frmUser.getBody(), "Description", SWT.NONE);
		lblNotes.setBounds(10, 100, 71, 15);
		
		txtDesc = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtDesc.setBounds(87, 100, 583, 93);


		// --- Form DETAILS tab TECHNICAL ROLES per business role
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
				YafraBusRoleAddRoleDialog addnew = new YafraBusRoleAddRoleDialog(getSite().getShell());
				addnew.open();
				if (addnew.getReturnCode() == (int) addnew.OK)
				{
					List<MGYafraTechRole> rbrl = addnew.getSelection();
					for(Iterator<MGYafraTechRole> iterator = rbrl.iterator(); iterator.hasNext();)
					{
						MGYafraTechRole mgyr = iterator.next();
						// TODO make this a real contains of the list - inputRoles.contains() does not work
						// check if already set - if so skip
						String name1 = inputRoles.toString();
						String name2 = mgyr.getName();
						if (name1.contains(name2))
						{
							return;
						}
						inputRoles.add(mgyr);
						ytr_table.addRole(mgyr, mhibrole);
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
				if (YafraRoleElement != null)
				{
					inputRoles.remove(YafraRoleElement);
					ytr_table.removeRole(getSite().getSelectionProvider().getSelection(), mhibrole);
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
		inputRoles = new WritableList(roles, MGYafraTechRole.class);
		ytr_table.createTable(viewerRoles, roles);
		viewerRoles.addSelectionChangedListener(new ISelectionChangedListener()
		{
			public void selectionChanged(SelectionChangedEvent event)
			{
				if (!event.getSelection().isEmpty() && event.getSelection() instanceof IStructuredSelection)
				{
					IStructuredSelection selection = (IStructuredSelection) event.getSelection();
					YafraRoleElement = (MGYafraTechRole) selection.getFirstElement();
					glob.setDebugmessage(" - selection on role table to " + YafraRoleElement.getName());
				}
			}
		});
		tableRoles = viewerRoles.getTable();
		formToolkit.paintBordersFor(tableRoles);
		formToolkit.adapt(tableRoles, true, true);
		scrolledComposite_1.setContent(tableRoles);
		scrolledComposite_1.setMinSize(tableRoles.computeSize(SWT.DEFAULT, SWT.DEFAULT));

		// --- Form DETAILS tab USERS having the selected business role
		TabItem tbtmJfaceTable = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTable.setText("Users");

		Form frmUsers = formToolkit.createForm(Fdetails);
		tbtmJfaceTable.setControl(frmUsers);
		formToolkit.paintBordersFor(frmUsers);
		frmUsers.setText("Assigned users");
		{
			frmUsers.getBody().setLayout(new TableWrapLayout());
		}
		frmUsers.getToolBarManager().add(new Action("Clear log") { });
		frmUsers.getToolBarManager().add(new Action("Add log entry") { });
		frmUsers.getToolBarManager().update(true);

		// user table viewer
		frmUsers.getBody().setLayout(new GridLayout(1, false));
		ScrolledComposite scrolledComposite_2 = new ScrolledComposite(frmUsers.getBody(), SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		scrolledComposite_2.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.adapt(scrolledComposite_2);
		formToolkit.paintBordersFor(scrolledComposite_2);
		scrolledComposite_2.setExpandHorizontal(true);
		scrolledComposite_2.setExpandVertical(true);
		viewerUsers = new TableViewer(scrolledComposite_2, SWT.MULTI | SWT.FULL_SELECTION);
		inputUser = new WritableList(users, MGYafraUser.class);
		yu_table.createTable(viewerUsers, users);
		viewerUsers.addSelectionChangedListener(new ISelectionChangedListener()
		{
			public void selectionChanged(SelectionChangedEvent event)
			{
				if (!event.getSelection().isEmpty() && event.getSelection() instanceof IStructuredSelection)
				{
					IStructuredSelection selection = (IStructuredSelection) event.getSelection();
					YafraUserElement = (MGYafraUser) selection.getFirstElement();
					glob.setDebugmessage(" - selection on user table to " + YafraUserElement.getName());
				}
			}
		});
		tableUsers = viewerUsers.getTable();
		formToolkit.paintBordersFor(tableUsers);
		formToolkit.adapt(tableUsers, true, true);
		scrolledComposite_1.setContent(tableUsers);
		scrolledComposite_1.setMinSize(tableUsers.computeSize(SWT.DEFAULT, SWT.DEFAULT));
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.ui.part.WorkbenchPart#setFocus()
	 */
	@Override
	public void setFocus() {
		viewerBRoles.getControl().setFocus();
		}

	public void dispose() {
		}
}
