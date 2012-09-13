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

package org.yafra.rcp.templates;

import org.eclipse.jface.action.Action;
import org.eclipse.jface.layout.TableColumnLayout;
import org.eclipse.jface.viewers.ColumnPixelData;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.jface.viewers.TableViewerColumn;
import org.eclipse.nebula.widgets.calendarcombo.CalendarCombo;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.ScrolledComposite;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.forms.widgets.ExpandableComposite;
import org.eclipse.ui.forms.widgets.Form;
import org.eclipse.ui.forms.widgets.FormText;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.ui.forms.widgets.ImageHyperlink;
import org.eclipse.ui.forms.widgets.Section;
import org.eclipse.ui.forms.widgets.TableWrapData;
import org.eclipse.ui.forms.widgets.TableWrapLayout;
import org.eclipse.ui.menus.CommandContributionItem;
import org.eclipse.ui.menus.CommandContributionItemParameter;
import org.eclipse.ui.part.ViewPart;

/**
 * @author mwn
 * 
 */
public class MasterDetailView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.MasterDetailView";
	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());
	private Table table;
	private Text text;

	/**
	 * 
	 */
	public MasterDetailView()
		{
		// TODO Auto-generated constructor stub
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
		parent.setLayout(new GridLayout(1, false));
		
		Group group = new Group(parent, SWT.NONE);
		group.setLayoutData(new GridData(SWT.FILL, SWT.TOP, false, false, 1, 1));
		
		Label label = new Label(group, SWT.NONE);
		label.setBounds(0, 10, 55, 15);
		formToolkit.adapt(label, true, true);
		label.setText("New Label");
		
		Button button = new Button(group, SWT.NONE);
		button.setBounds(61, 10, 75, 25);
		formToolkit.adapt(button, true, true);
		button.setText("New Button");
		
		Button button_1 = new Button(group, SWT.CHECK);
		button_1.setBounds(142, 10, 93, 16);
		formToolkit.adapt(button_1, true, true);
		button_1.setText("Check Button");
		
		Combo combo = new Combo(group, SWT.NONE);
		combo.setBounds(250, 12, 91, 23);
		formToolkit.adapt(combo);
		formToolkit.paintBordersFor(combo);
		
		Group group_1 = new Group(parent, SWT.NONE);
		GridData gridData = new GridData(SWT.FILL, SWT.CENTER, false, false, 1, 1);
		gridData.heightHint = 128;
		group_1.setLayoutData(gridData);
		
		ScrolledComposite scrolledComposite = new ScrolledComposite(group_1, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		scrolledComposite.setBounds(10, 10, 564, 126);
		formToolkit.adapt(scrolledComposite);
		formToolkit.paintBordersFor(scrolledComposite);
		scrolledComposite.setExpandHorizontal(true);
		scrolledComposite.setExpandVertical(true);
		
		Composite composite = new Composite(scrolledComposite, SWT.NONE);
		formToolkit.adapt(composite);
		formToolkit.paintBordersFor(composite);
		TableColumnLayout tableColumnLayout = new TableColumnLayout();
		composite.setLayout(tableColumnLayout);
		
		TableViewer tableViewer_1 = new TableViewer(composite, SWT.BORDER | SWT.FULL_SELECTION);
		table = tableViewer_1.getTable();
		table.setHeaderVisible(true);
		table.setLinesVisible(true);
		formToolkit.paintBordersFor(table);
		
		TableViewerColumn tableViewerColumn = new TableViewerColumn(tableViewer_1, SWT.NONE);
		TableColumn tableColumn = tableViewerColumn.getColumn();
		tableColumnLayout.setColumnData(tableColumn, new ColumnPixelData(150, true, true));
		tableColumn.setText("New Column");
		
		TableViewerColumn tableViewerColumn_1 = new TableViewerColumn(tableViewer_1, SWT.NONE);
		TableColumn tableColumn_1 = tableViewerColumn_1.getColumn();
		tableColumnLayout.setColumnData(tableColumn_1, new ColumnPixelData(150, true, true));
		tableColumn_1.setText("New Column");
		
		TableViewerColumn tableViewerColumn_2 = new TableViewerColumn(tableViewer_1, SWT.NONE);
		TableColumn tableColumn_2 = tableViewerColumn_2.getColumn();
		tableColumnLayout.setColumnData(tableColumn_2, new ColumnPixelData(150, true, true));
		tableColumn_2.setText("New Column");
		scrolledComposite.setContent(composite);
		scrolledComposite.setMinSize(composite.computeSize(SWT.DEFAULT, SWT.DEFAULT));
		
		Form frmDetails = formToolkit.createForm(parent);
		frmDetails.setToolTipText("Detail form");
		frmDetails.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1));
		formToolkit.paintBordersFor(frmDetails);
		frmDetails.setText("Details");
			{
			TableWrapLayout tableWrapLayout = new TableWrapLayout();
			tableWrapLayout.numColumns = 3;
			frmDetails.getBody().setLayout(tableWrapLayout);
			}
		CommandContributionItemParameter itempara = new CommandContributionItemParameter(getSite().getWorkbenchWindow(), "template.md", "org.yafra.rcp.commands.TemplateCommand", 0);
		CommandContributionItem item = new CommandContributionItem(itempara);
		frmDetails.getMenuManager().add(new Action("This is the form menu") { });
		frmDetails.getToolBarManager().add(new Action("This is the 1") { });
		frmDetails.getToolBarManager().add(item);
		frmDetails.getToolBarManager().add(new Action("This is the 3") { });
		frmDetails.getToolBarManager().update(true);

		
		Label lblId = formToolkit.createLabel(frmDetails.getBody(), "ID", SWT.NONE);
		
		Label label_2 = formToolkit.createLabel(frmDetails.getBody(), "New Label", SWT.NONE);
		new Label(frmDetails.getBody(), SWT.NONE);
		
		Label lblName = formToolkit.createLabel(frmDetails.getBody(), "Name", SWT.NONE);
		
		ImageHyperlink imageHyperlink = formToolkit.createImageHyperlink(frmDetails.getBody(), SWT.NONE);
		formToolkit.paintBordersFor(imageHyperlink);
		imageHyperlink.setText("New ImageHyperlink");
		new Label(frmDetails.getBody(), SWT.NONE);
		
		ExpandableComposite expandableComposite = formToolkit.createExpandableComposite(frmDetails.getBody(), ExpandableComposite.TWISTIE);
		expandableComposite.setLayoutData(new TableWrapData(TableWrapData.FILL_GRAB, TableWrapData.TOP, 1, 3));
		expandableComposite.setSize(166, 15);
		formToolkit.paintBordersFor(expandableComposite);
		expandableComposite.setText("New ExpandableComposite");
		
		Composite composite_2 = formToolkit.createComposite(expandableComposite, SWT.NONE);
		formToolkit.paintBordersFor(composite_2);
		expandableComposite.setClient(composite_2);
		composite_2.setLayout(new GridLayout(2, false));
		
		Label label_4 = formToolkit.createLabel(composite_2, "New Label", SWT.NONE);
		
		text = formToolkit.createText(composite_2, "New Text", SWT.NONE);
		
		Label label_5 = formToolkit.createLabel(composite_2, "New Label", SWT.NONE);
		
		FormText formText = formToolkit.createFormText(composite_2, false);
		formToolkit.paintBordersFor(formText);
		formText.setText("New FormText", false, false);
		
		Label label_6 = formToolkit.createLabel(composite_2, "New Label", SWT.NONE);
		
		Combo combo_1 = new Combo(composite_2, SWT.NONE);
		formToolkit.adapt(combo_1);
		formToolkit.paintBordersFor(combo_1);
		
		Label label_7 = formToolkit.createLabel(composite_2, "New Label", SWT.NONE);
		
		CalendarCombo calendarCombo = new CalendarCombo(composite_2, SWT.NONE);
		calendarCombo.setSize(91, 23);
		formToolkit.adapt(calendarCombo);
		formToolkit.paintBordersFor(calendarCombo);
		expandableComposite.setExpanded(true);
		
		Section sctnActions = formToolkit.createSection(frmDetails.getBody(), Section.TWISTIE | Section.TITLE_BAR);
		sctnActions.setLayoutData(new TableWrapData(TableWrapData.FILL, TableWrapData.BOTTOM, 1, 3));
		formToolkit.paintBordersFor(sctnActions);
		sctnActions.setText("Actions");
		
		Composite composite_1 = formToolkit.createComposite(sctnActions, SWT.NONE);
		formToolkit.paintBordersFor(composite_1);
		sctnActions.setClient(composite_1);
		{
			TableWrapLayout tableWrapLayout = new TableWrapLayout();
			tableWrapLayout.numColumns = 4;
			composite_1.setLayout(tableWrapLayout);
		}
		
		Button btnNewEntry = formToolkit.createButton(composite_1, "New entry", SWT.NONE);
		btnNewEntry.addSelectionListener(new SelectionAdapter() {
			@Override
			public void widgetSelected(SelectionEvent e) {
			}
		});
		
		Button btnUpdate = formToolkit.createButton(composite_1, "Update", SWT.NONE);
		
		Button btnClearForm = formToolkit.createButton(composite_1, "Clear form", SWT.NONE);
		
		Button btnExport = formToolkit.createButton(composite_1, "Export", SWT.NONE);
		sctnActions.setExpanded(true);
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
