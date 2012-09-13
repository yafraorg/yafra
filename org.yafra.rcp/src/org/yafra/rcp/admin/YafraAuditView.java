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
import java.util.List;

import org.eclipse.core.databinding.observable.list.WritableList;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.GroupMarker;
import org.eclipse.jface.action.MenuManager;
import org.eclipse.jface.viewers.ComboViewer;
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
import org.yafra.model.MYafraAudit;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraAuditRemote;

/**
 * @author mwn
 * 
 */
public class YafraAuditView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.YafraAuditView";

	private GlobalSettings glob;

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());

	// Yafra Role table (technical roles associated to business role)
	private YafraAuditTable ya_table;
	private TableViewer viewerAudits;
	private Table tableAudits;
	private WritableList inputAudits;
	private MGYafraAudit YafraAuditElement;
	private MHIYafraAuditRemote mhiaudit = null;
	List<MGYafraAudit> audits = new ArrayList<MGYafraAudit>();

	// Form fields for Yafra Business Role
	private String txtId;
	private Text txtName;
	private Text txtDesc;
	private Text txtRights;
	private Label lblIdFill;

	/**
	 * 
	 */
	public YafraAuditView()
		{
		YafraAuditElement = null;
		glob = GlobalSettings.getSingletonObject();
		ya_table = new YafraAuditTable();
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

		// MASTER Roles - fill up table
		ya_table.loadTableData(viewerAudits, inputAudits);
		}


	private void createViewer(Composite parent)
		{
		// TODO handle timestamp and PK id
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
		viewerAudits = new TableViewer(scrolledComposite, SWT.MULTI | SWT.FULL_SELECTION);
		inputAudits = new WritableList(audits, MGYafraBusRole.class);
		ya_table.createTable(viewerAudits, audits);
		viewerAudits.addSelectionChangedListener(new ISelectionChangedListener()
			{
			public void selectionChanged(SelectionChangedEvent event)
				{
				if (event.getSelection().isEmpty())
					{
					// if the selection is empty clear the labels
					glob.setDebugmessage(" - selection change is empty");
					if (YafraAuditElement == null) {	return; }
					YafraAuditElement.setAuditobject("");
					YafraAuditElement.setAudittext("");
					YafraAuditElement.setTimestamp(null);
					YafraAuditElement.setDbPK(0);
					return;
					}
				if (event.getSelection() instanceof IStructuredSelection)
					{
					IStructuredSelection selection = (IStructuredSelection) event.getSelection();
					YafraAuditElement = (MGYafraAudit) selection.getFirstElement();
					if (YafraAuditElement.getAuditobject() != null) txtName.setText(YafraAuditElement.getAuditobject());
					if (YafraAuditElement.getAudittext() != null) txtDesc.setText(YafraAuditElement.getAudittext());
					viewerAudits.refresh();
					glob.setDebugmessage(" - selection changed on master table to " + YafraAuditElement.getDbPK());
					}
				}
			});
		getSite().setSelectionProvider(viewerAudits);

		MenuManager menuMgr = new MenuManager();
		menuMgr.add(new Action("Delete") {	public void run() { glob.setDebugmessage(" - delete action run now"); ya_table.deleteEntry(inputAudits, getSite().getSelectionProvider().getSelection()); } });
		menuMgr.add(new GroupMarker(IWorkbenchActionConstants.MB_ADDITIONS));
		getSite().registerContextMenu(menuMgr, viewerAudits);
		Control control = viewerAudits.getControl();
		Menu menu = menuMgr.createContextMenu(control);
		control.setMenu(menu);
		tableAudits = viewerAudits.getTable();
		formToolkit.paintBordersFor(tableAudits);
		scrolledComposite.setContent(tableAudits);
		formToolkit.adapt(scrolledComposite, true, true);

		// --- Form DETAILS tabs
		TabFolder Fdetails = new TabFolder(parent, SWT.NONE);
		GridData gridData_1 = new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1);
		gridData_1.widthHint = 643;
		Fdetails.setLayoutData(gridData_1);

		// --- Form DETAILS tab ROLE DETAILS
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
				mhiaudit = ya_table.getMHIaudit();
				MYafraAudit mya = new MYafraAudit();
				mya.setAuditobject(txtName.getText());
				mya.setAudittext(txtDesc.getText());
				// TODO get the user in order to insert a log
				mhiaudit.insertYafraAudit(mya, null);
				MGYafraAudit NewYBR = new MGYafraAudit();
				NewYBR.setAuditobject(txtName.getText());
				NewYBR.setAudittext(txtDesc.getText());
				inputAudits.add(NewYBR);
				}
			});
		frmUser.getToolBarManager().add(new Action("Update")
			{
			@Override
			public void run()
				{
				if (YafraAuditElement == null) {	return; }
				mhiaudit = ya_table.getMHIaudit();
				MYafraAudit mya = new MYafraAudit();
				mya.setAuditobject(txtName.getText());
				mya.setAudittext(txtDesc.getText());
				// TODO implement the update method for Yafra Audit
				mhiaudit.deleteYafraAudit(0);
				YafraAuditElement.setAuditobject(txtName.getText());
				YafraAuditElement.setAudittext(txtDesc.getText());
				viewerAudits.update(YafraAuditElement, null);
				viewerAudits.refresh();
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
				txtRights.setText("");
				}
			});
		frmUser.getToolBarManager().add(new Action("Export") { });
		frmUser.getToolBarManager().update(true);
		
		Label lblId = formToolkit.createLabel(frmUser.getBody(), "ID", SWT.NONE);
		lblId.setBounds(10, 23, 55, 15);
		lblIdFill = formToolkit.createLabel(frmUser.getBody(), txtId, SWT.NONE);
		lblIdFill.setBounds(104, 23, 88, 15);

		Label lblName = formToolkit.createLabel(frmUser.getBody(), "Name", SWT.NONE);
		lblName.setBounds(10, 48, 55, 15);
		txtName = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtName.setText("");
		txtName.setBounds(104, 44, 402, 21);

		Label lblNotes = formToolkit.createLabel(frmUser.getBody(), "Description", SWT.NONE);
		lblNotes.setBounds(10, 160, 71, 15);
		txtDesc = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtDesc.setBounds(104, 131, 526, 93);
		txtDesc.setText("");
		
		Label lblBusinessRole = formToolkit.createLabel(frmUser.getBody(), "Business role", SWT.NONE);
		lblBusinessRole.setBounds(10, 76, 88, 15);
		ComboViewer comboViewer = new ComboViewer(frmUser.getBody(), SWT.NONE);
		Combo comboBusRole = comboViewer.getCombo();
		comboBusRole.setBounds(104, 71, 187, 23);
		formToolkit.paintBordersFor(comboBusRole);
		
		Label lblRights = formToolkit.createLabel(frmUser.getBody(), "Rights", SWT.NONE);
		lblRights.setBounds(10, 103, 55, 15);
		txtRights = formToolkit.createText(frmUser.getBody(), "New Text", SWT.NONE);
		txtRights.setBounds(104, 100, 402, 21);
		txtRights.setText("");
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.eclipse.ui.part.WorkbenchPart#setFocus()
	 */
	@Override
	public void setFocus()
		{
		}
}
