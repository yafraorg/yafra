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
package org.yafra.rcp.person;

import java.util.ArrayList;
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
import org.eclipse.swt.widgets.Combo;
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
import org.eclipse.ui.part.ViewPart;
import org.yafra.model.MPerson;
import org.yafra.rcp.GlobalSettings;
import org.yafra.rcp.admin.MGYafraUser;
import org.yafra.server.ejbRemote.MHIPersonRemote;


/**
 * Person View
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class PersonView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.PersonView";

	private GlobalSettings glob;

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());
	
	// Person table
	private PersonTable p_table;
	private TableViewer viewerPerson;
	private Table tablePerson;
	private WritableList inputPerson;
	List<MGPerson> persons = new ArrayList<MGPerson>();
	private MGPerson PersonElement;
	private MHIPersonRemote mhiperson = null;

	// Person Logs
	// private PersonLogTable pl_table;

	// Form fields for Person
	private Text txtName;
	private Text txtFirstname;
	private Text txtAddress;
	private Text txtType;
	private Text txtID;

	/**
	 * constructor of view
	 */
	public PersonView()
		{
		PersonElement = null;
		glob = GlobalSettings.getSingletonObject();
		p_table = new PersonTable();
		//pl_table = new PersonLogTable();
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

		// MASTER Person - fill up table
		p_table.loadTableData(viewerPerson, inputPerson);

		// DETAIL Logs - fill up table
		// TODO add person log table
		//pl_table.loadTableData(viewerLogs, inputLogs);
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

		// person table viewer
		inputPerson = new WritableList(persons, MGYafraUser.class);
		viewerPerson = new TableViewer(scrolledComposite, SWT.MULTI | SWT.FULL_SELECTION);
		p_table.createTable(viewerPerson, persons);
		viewerPerson.addSelectionChangedListener(new ISelectionChangedListener()
			{
				public void selectionChanged(SelectionChangedEvent event)
					{
					if (event.getSelection().isEmpty())
						{
						// if the selection is empty clear the labels
						glob.setDebugmessage(" - selection change is empty");
						PersonElement.setId(0);
						PersonElement.setAddress("");
						PersonElement.setName("");
						PersonElement.setFirstname("");
						PersonElement.setType("");
						return;
						}
					if (event.getSelection() instanceof IStructuredSelection)
						{
						IStructuredSelection selection = (IStructuredSelection) event.getSelection();
						PersonElement = (MGPerson) selection.getFirstElement();
						glob.setDebugmessage(" - selection changed on master table to " + PersonElement.getName());
						txtName.setText(PersonElement.getName());
						if (PersonElement.getFirstname() != null) txtFirstname.setText(PersonElement.getFirstname());
						if (PersonElement.getAddress() != null) txtAddress.setText(PersonElement.getAddress());
						if (PersonElement.getId() != null) txtID.setText(Integer.toString(PersonElement.getId()));
						if (PersonElement.getType() != null) txtType.setText(PersonElement.getType());
						viewerPerson.refresh();
						// ybr_table.fillTable(roles);
						// viewerRoles.refresh();
						}
					}
			});
		getSite().setSelectionProvider(viewerPerson);

		MenuManager menuMgr = new MenuManager();
		menuMgr.add(new Action("Delete") {	public void run() { glob.setDebugmessage(" - delete action run now"); p_table.deleteEntry(inputPerson, getSite().getSelectionProvider().getSelection()); } });
		menuMgr.add(new GroupMarker(IWorkbenchActionConstants.MB_ADDITIONS));
		getSite().registerContextMenu(menuMgr, viewerPerson);
		// getSite().registerContextMenu(menuMgr,getSite().getSelectionProvider());
		Control control = viewerPerson.getControl();
		Menu menu = menuMgr.createContextMenu(control);
		control.setMenu(menu);
		tablePerson = viewerPerson.getTable();
		formToolkit.paintBordersFor(tablePerson);
		scrolledComposite.setContent(tablePerson);
		formToolkit.adapt(scrolledComposite, true, true);

		// --- Form DETAILS tabs
		TabFolder Fdetails = new TabFolder(parent, SWT.NONE);
		GridData gridData_1 = new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1);
		gridData_1.heightHint = 207;
		gridData_1.widthHint = 643;
		Fdetails.setLayoutData(gridData_1);

		// --- Form DETAILS tab person DETAILS
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
				p_table.getMHI();
				MPerson mp = new MPerson();
				mp.setName(txtName.getText());
				mp.setId(Integer.valueOf(txtID.getText()));
				mp.setFirstname(txtFirstname.getText());
				mp.setType(txtType.getText());
				mp.setAddress(txtAddress.getText());
				mhiperson.insertPerson(mp);
				MGPerson NewP = new MGPerson();
				NewP.setName(txtName.getText());
				NewP.setId(Integer.valueOf(txtID.getText()));
				NewP.setFirstname(txtFirstname.getText());
				NewP.setAddress(txtAddress.getText());
				NewP.setType(txtType.getText());
				inputPerson.add(NewP);
				}
			});
		frmUser.getToolBarManager().add(new Action("Update")
			{
			@Override
			public void run()
				{
				if (PersonElement == null)
					{
					return;
					}
				p_table.getMHI();
				MPerson mp = new MPerson();
				mp.setName(txtName.getText());
				mp.setId(Integer.valueOf(txtID.getText()));
				mp.setFirstname(txtFirstname.getText());
				mp.setType(txtType.getText());
				mp.setAddress(txtAddress.getText());
				mhiperson.updatePerson(mp);
				PersonElement.setName(txtName.getText());
				PersonElement.setId(Integer.valueOf(txtID.getText()));
				PersonElement.setFirstname(txtFirstname.getText());
				PersonElement.setAddress(txtAddress.getText());
				PersonElement.setType(txtType.getText());
				viewerPerson.update(PersonElement, null);
				viewerPerson.refresh();
				// TODO refresh table with modified data
				}
			});
		frmUser.getToolBarManager().add(new Action("Clear")
			{
				@Override
				public void run()
					{
					txtName.setText("");
					txtID.setText("");
					txtFirstname.setText("");
					txtAddress.setText("");
					txtType.setText("");
					}
			});
		frmUser.getToolBarManager().add(new Action("Export") { });
		frmUser.getToolBarManager().update(true);

		Label lblName = formToolkit.createLabel(frmUser.getBody(), "Name", SWT.NONE);
		lblName.setBounds(10, 44, 55, 15);
		txtName = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtName.setText("");
		txtName.setBounds(87, 41, 212, 21);

		Label lblId = formToolkit.createLabel(frmUser.getBody(), "ID", SWT.NONE);
		lblId.setBounds(10, 19, 55, 15);
		txtID = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtID.setText("");
		txtID.setToolTipText("The person id is not modifiable");
		//txtUserID.setEditable(false);
		txtID.setBounds(87, 16, 120, 21);

		Label lblFirstname = formToolkit.createLabel(frmUser.getBody(), "First name", SWT.NONE);
		lblFirstname.setBounds(305, 44, 71, 15);
		txtFirstname = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtFirstname.setText("");
		txtFirstname.setBounds(382, 41, 212, 21);
		
		Label lblAddress = formToolkit.createLabel(frmUser.getBody(), "Address", SWT.NONE);
		lblAddress.setBounds(10, 109, 55, 15);
		txtAddress = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtAddress.setBounds(87, 81, 507, 73);
		
		Label lblType = formToolkit.createLabel(frmUser.getBody(), "Type", SWT.NONE);
		lblType.setBounds(10, 172, 55, 15);
		txtType = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtType.setBounds(87, 172, 120, 21);

		// --- Form DETAILS tab logs per person
		TabItem tbtmJfaceTreeviewer = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTreeviewer.setText("Log entries");

		Form frmAssignedRoles = formToolkit.createForm(Fdetails);
		tbtmJfaceTreeviewer.setControl(frmAssignedRoles);
		formToolkit.paintBordersFor(frmAssignedRoles);
		frmAssignedRoles.setText("Assigned logs");
		frmAssignedRoles.getToolBarManager().add(new Action("Create new log")
			{
			});
		frmAssignedRoles.getToolBarManager().add(new Action("Delete selected log")
			{
			});
		frmAssignedRoles.getToolBarManager().add(new Action("Delete all logs") { });
		frmAssignedRoles.getToolBarManager().update(true);
		// TODO add table logs
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
