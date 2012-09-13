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

import org.eclipse.jface.layout.TableColumnLayout;
import org.eclipse.jface.layout.TreeColumnLayout;
import org.eclipse.jface.viewers.ListViewer;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.jface.viewers.TreeViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.browser.Browser;
import org.eclipse.swt.custom.ScrolledComposite;
import org.eclipse.swt.custom.StyledText;
import org.eclipse.swt.custom.TableCursor;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.CoolBar;
import org.eclipse.swt.widgets.CoolItem;
import org.eclipse.swt.widgets.DateTime;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Group;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.List;
import org.eclipse.swt.widgets.Spinner;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;
import org.eclipse.ui.forms.widgets.Form;
import org.eclipse.ui.forms.widgets.FormText;
import org.eclipse.ui.forms.widgets.FormToolkit;
import org.eclipse.ui.forms.widgets.Hyperlink;
import org.eclipse.ui.forms.widgets.ImageHyperlink;
import org.eclipse.ui.forms.widgets.Section;
import org.eclipse.ui.part.ViewPart;

/**
 * @author mwn
 * 
 */
public class MasterDetailsView extends ViewPart
{
	public static final String ID = "org.yafra.rcp.MasterDetailsView";

	private final FormToolkit formToolkit = new FormToolkit(Display.getDefault());

	private Text text;

	private Table table;

	private Table table_1;

	private Table table_2;

	/**
	 * 
	 */
	public MasterDetailsView()
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

		Group Fheader = new Group(parent, SWT.NONE);
		Fheader.setLayoutData(new GridData(SWT.FILL, SWT.TOP, false, false, 1, 1));
		formToolkit.adapt(Fheader);
		formToolkit.paintBordersFor(Fheader);
		Fheader.setLayout(new GridLayout(4, false));

		Label label = new Label(Fheader, SWT.NONE);
		label.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
		formToolkit.adapt(label, true, true);
		label.setText("New Label");

		Combo combo_1 = new Combo(Fheader, SWT.NONE);
		formToolkit.adapt(combo_1);
		formToolkit.paintBordersFor(combo_1);

		DateTime dateTime_1 = new DateTime(Fheader, SWT.BORDER);
		formToolkit.adapt(dateTime_1);
		formToolkit.paintBordersFor(dateTime_1);

		Button button_3 = new Button(Fheader, SWT.NONE);
		formToolkit.adapt(button_3, true, true);
		button_3.setText("New Button");

		Group Fmaster = new Group(parent, SWT.NONE);
		Fmaster.setLayoutData(new GridData(SWT.FILL, SWT.FILL, true, false, 1, 1));
		formToolkit.adapt(Fmaster);
		formToolkit.paintBordersFor(Fmaster);
		Fmaster.setLayout(new GridLayout(2, false));

		ScrolledComposite scrolledComposite = new ScrolledComposite(Fmaster, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		GridData gridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 1, 1);
		gridData.widthHint = 566;
		scrolledComposite.setLayoutData(gridData);
		scrolledComposite.setExpandHorizontal(true);
		scrolledComposite.setExpandVertical(true);

		ListViewer listViewer = new ListViewer(scrolledComposite, SWT.BORDER);
		List list = listViewer.getList();
		scrolledComposite.setContent(list);
		scrolledComposite.setMinSize(list.computeSize(SWT.DEFAULT, SWT.DEFAULT));
						
								Group Factions = new Group(Fmaster, SWT.NONE);
								Factions.setLayoutData(new GridData(SWT.RIGHT, SWT.FILL, false, false, 1, 1));
								formToolkit.adapt(Factions);
								formToolkit.paintBordersFor(Factions);
								Factions.setLayout(new GridLayout(1, false));
										
												Label label_2 = new Label(Factions, SWT.NONE);
												label_2.setLayoutData(new GridData(SWT.RIGHT, SWT.CENTER, false, false, 1, 1));
												formToolkit.adapt(label_2, true, true);
												label_2.setText("New Label");
								
										Button button_5 = new Button(Factions, SWT.NONE);
										formToolkit.adapt(button_5, true, true);
										button_5.setText("New Button");

		TabFolder Fdetails = new TabFolder(parent, SWT.NONE);
		GridData gridData_1 = new GridData(SWT.FILL, SWT.FILL, false, true, 1, 1);
		gridData_1.widthHint = 643;
		Fdetails.setLayoutData(gridData_1);

		TabItem tbtmJfaceTable = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTable.setText("JFace Table");

		Composite composite_2 = new Composite(Fdetails, SWT.NONE);
		tbtmJfaceTable.setControl(composite_2);
		formToolkit.paintBordersFor(composite_2);
		composite_2.setLayout(new TableColumnLayout());

		TableViewer tableViewer = new TableViewer(composite_2, SWT.BORDER | SWT.FULL_SELECTION);
		table_1 = tableViewer.getTable();
		table_1.setHeaderVisible(true);
		table_1.setLinesVisible(true);
		formToolkit.paintBordersFor(table_1);

		TabItem tbtmJfaceTreeviewer = new TabItem(Fdetails, SWT.NONE);
		tbtmJfaceTreeviewer.setText("JFace TreeViewer");

		Composite composite_1 = new Composite(Fdetails, SWT.NONE);
		tbtmJfaceTreeviewer.setControl(composite_1);
		formToolkit.paintBordersFor(composite_1);
		composite_1.setLayout(new TreeColumnLayout());

		TreeViewer treeViewer = new TreeViewer(composite_1, SWT.BORDER);
		Tree tree_1 = treeViewer.getTree();
		tree_1.setHeaderVisible(true);
		tree_1.setLinesVisible(true);
		formToolkit.paintBordersFor(tree_1);

		TabItem tbtmPalette = new TabItem(Fdetails, SWT.NONE);
		tbtmPalette.setText("Palette");

		Group group = new Group(Fdetails, SWT.NONE);
		tbtmPalette.setControl(group);
		formToolkit.paintBordersFor(group);
		group.setLayout(new GridLayout(14, false));

		Combo combo = new Combo(group, SWT.NONE);
		combo.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(combo);
		formToolkit.paintBordersFor(combo);

		Label label_1 = new Label(group, SWT.NONE);
		formToolkit.adapt(label_1, true, true);
		label_1.setText("New Label");

		text = new Text(group, SWT.BORDER);
		text.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(text, true, true);

		Button button = new Button(group, SWT.NONE);
		formToolkit.adapt(button, true, true);
		button.setText("New Button");

		Button button_1 = new Button(group, SWT.CHECK);
		formToolkit.adapt(button_1, true, true);
		button_1.setText("Check Button");

		Spinner spinner = new Spinner(group, SWT.BORDER);
		spinner.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(spinner);
		formToolkit.paintBordersFor(spinner);

		DateTime dateTime = new DateTime(group, SWT.BORDER);
		dateTime.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(dateTime);
		formToolkit.paintBordersFor(dateTime);

		Button button_2 = new Button(group, SWT.RADIO);
		button_2.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 3, 1));
		formToolkit.adapt(button_2, true, true);
		button_2.setText("Radio Button");

		List list_1 = new List(group, SWT.BORDER);
		formToolkit.adapt(list_1, true, true);

		Tree tree = new Tree(group, SWT.BORDER);
		tree.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 3, 1));
		formToolkit.adapt(tree);
		formToolkit.paintBordersFor(tree);

		TreeItem treeItem = new TreeItem(tree, SWT.NONE);
		treeItem.setText("New TreeItem");

		TreeItem treeItem_1 = new TreeItem(tree, SWT.NONE);
		treeItem_1.setText("New TreeItem");

		TreeItem treeItem_2 = new TreeItem(tree, SWT.NONE);
		treeItem_2.setText("New TreeItem");

		TreeItem treeItem_3 = new TreeItem(tree, SWT.NONE);
		treeItem_3.setText("New TreeItem");

		table = new Table(group, SWT.BORDER | SWT.FULL_SELECTION);
		table.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 4, 1));
		formToolkit.adapt(table);
		formToolkit.paintBordersFor(table);
		table.setHeaderVisible(true);
		table.setLinesVisible(true);

		TableColumn tableColumn = new TableColumn(table, SWT.NONE);
		tableColumn.setWidth(100);
		tableColumn.setText("New Column");

		TableColumn tableColumn_1 = new TableColumn(table, SWT.NONE);
		tableColumn_1.setWidth(100);
		tableColumn_1.setText("New Column");

		TableItem tableItem = new TableItem(table, SWT.NONE);
		tableItem.setText("New Item");

		TableItem tableItem_1 = new TableItem(table, SWT.NONE);
		tableItem_1.setText("New Item");

		TableCursor tableCursor = new TableCursor(table, SWT.NONE);
		formToolkit.adapt(tableCursor);
		formToolkit.paintBordersFor(tableCursor);

		Canvas canvas = new Canvas(group, SWT.NONE);
		canvas.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(canvas);
		formToolkit.paintBordersFor(canvas);

		Browser browser = new Browser(group, SWT.NONE);
		browser.setLayoutData(new GridData(SWT.LEFT, SWT.CENTER, false, false, 2, 1));
		formToolkit.adapt(browser);
		formToolkit.paintBordersFor(browser);

		StyledText styledText = new StyledText(group, SWT.BORDER);
		formToolkit.adapt(styledText);
		formToolkit.paintBordersFor(styledText);
		
		CoolBar coolBar = new CoolBar(group, SWT.NONE);
		formToolkit.adapt(coolBar);
		formToolkit.paintBordersFor(coolBar);
		
		CoolItem coolItem = new CoolItem(coolBar, SWT.NONE);

		TabItem tbtmForm = new TabItem(Fdetails, SWT.NONE);
		tbtmForm.setText("Form");

		Form form = formToolkit.createForm(Fdetails);
		tbtmForm.setControl(form);
		formToolkit.paintBordersFor(form);
		form.setText("New Form");

		Section section = formToolkit.createSection(form.getBody(), Section.TWISTIE | Section.TITLE_BAR);
		section.setBounds(10, 10, 98, 21);
		formToolkit.paintBordersFor(section);
		section.setText("New Section");

		FormText formText = formToolkit.createFormText(form.getBody(), false);
		formText.setBounds(10, 37, 79, 15);
		formToolkit.paintBordersFor(formText);
		formText.setText("New FormText", false, false);

		ImageHyperlink imageHyperlink = formToolkit.createImageHyperlink(form.getBody(), SWT.NONE);
		imageHyperlink.setBounds(115, 33, 115, 19);
		formToolkit.paintBordersFor(imageHyperlink);
		imageHyperlink.setText("New ImageHyperlink");

		Button button_4 = formToolkit.createButton(form.getBody(), "New Button", SWT.NONE);
		button_4.setBounds(10, 58, 75, 25);

		Label label_3 = formToolkit.createLabel(form.getBody(), "New Label", SWT.NONE);
		label_3.setBounds(125, 58, 55, 15);

		Hyperlink hyperlink = formToolkit.createHyperlink(form.getBody(), "New Hyperlink", SWT.NONE);
		hyperlink.setBounds(115, 86, 80, 17);
		formToolkit.paintBordersFor(hyperlink);

		Composite composite = formToolkit.createComposite(form.getBody(), SWT.NONE);
		composite.setBounds(240, 10, 64, 64);
		formToolkit.paintBordersFor(composite);

		table_2 = formToolkit.createTable(form.getBody(), SWT.NONE);
		table_2.setBounds(338, 10, 85, 45);
		formToolkit.paintBordersFor(table_2);
		table_2.setHeaderVisible(true);
		table_2.setLinesVisible(true);

		Tree tree_2 = formToolkit.createTree(form.getBody(), SWT.NONE);
		tree_2.setBounds(447, 10, 85, 85);
		formToolkit.paintBordersFor(tree_2);

		Canvas canvas_1 = new Canvas(form.getBody(), SWT.NONE);
		canvas_1.setBounds(348, 76, 64, 64);
		formToolkit.adapt(canvas_1);
		formToolkit.paintBordersFor(canvas_1);
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
