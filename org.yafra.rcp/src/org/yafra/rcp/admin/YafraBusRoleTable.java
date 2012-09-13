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

import java.util.Iterator;
import java.util.List;

import javax.naming.NamingException;

import org.eclipse.core.databinding.observable.list.WritableList;
import org.eclipse.jface.databinding.viewers.ObservableListContentProvider;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.jface.viewers.TableViewerColumn;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.model.MYafraUser;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote;
import org.yafra.server.ejbRemote.MHIYafraUserRemote;

/**
 * Manage JFace Table of Yafra Business Role to be used within a group
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraBusRoleTable
	{
	private GlobalSettings glob;
	private YafraBusRoleTableSorter tableSorterBRoles;
	public MHIYafraBusinessRoleRemote mhibrole = null;

	public YafraBusRoleTable() {
	glob = GlobalSettings.getSingletonObject();
	}

	public void loadTableData(TableViewer viewerBRoles, WritableList inputBRoles)
		{
		// Get the content for the viewer, setInput will call getElements in the
		// contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());
		viewerBRoles.setInput(inputBRoles);
		tableSorterBRoles = new YafraBusRoleTableSorter();
		viewerBRoles.setSorter(tableSorterBRoles);

		}

	/**
	 * @wbp.parser.entryPoint
	 */
	public void createTable(TableViewer viewerBRoles, List<MGYafraBusRole> broles)
		{
		// business role table viewer
		this.fillTable(broles);
		this.tableCreateCols(viewerBRoles);
		viewerBRoles.setContentProvider(new ObservableListContentProvider());
		// viewerUser.setContentProvider(new YafraUserContentProvider());
		viewerBRoles.setLabelProvider(new YafraBusRoleLabelProvider());
		}

	private void tableCreateCols(final TableViewer viewer)
		{
		String[] titles = { "Name", "Description", "Active" };
		int[] bounds = { 200, 500, 100 };

		for (int i = 0; i < titles.length; i++) {
			final int index = i;
			final TableViewerColumn viewerColumn = new TableViewerColumn(
					viewer, SWT.NONE);
			viewerColumn.getColumn().setText(titles[i]);
			viewerColumn.getColumn().setWidth(bounds[i]);
			viewerColumn.getColumn().setResizable(true);
			viewerColumn.getColumn().setMoveable(true);
			// Setting the right sorter
			viewerColumn.getColumn().addSelectionListener(
					new SelectionAdapter() {
						@Override
						public void widgetSelected(SelectionEvent e)
							{
							YafraBusRoleTableSorter tableSorterBusRoles;
							tableSorterBusRoles = (YafraBusRoleTableSorter) viewer
									.getSorter();
							tableSorterBusRoles.setColumn(index);
							int dir = viewer.getTable().getSortDirection();
							if (viewer.getTable().getSortColumn() == viewerColumn
									.getColumn()) {
								dir = dir == SWT.UP ? SWT.DOWN : SWT.UP;
							} else {
								dir = SWT.DOWN;
							}
							viewer.getTable().setSortDirection(dir);
							viewer.getTable().setSortColumn(
									viewerColumn.getColumn());
							viewer.refresh();
							}
					});
		}
		GridData gridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 1,
				1);
		viewer.getTable().setLayoutData(gridData);
		viewer.getTable().setHeaderVisible(true);
		viewer.getTable().setLinesVisible(true);
		}

	protected void fillTable(List<MGYafraBusRole> broles)
		{
		getMHIBusRoles();
		List<MYafraBusinessRole> brlist = (List<MYafraBusinessRole>) mhibrole
				.getBusinessRoles(false);
		Iterator<MYafraBusinessRole> it = brlist.iterator();
		while (it.hasNext()) {
			MYafraBusinessRole dbbr = it.next();
			MGYafraBusRole mgbr = new MGYafraBusRole();
			mgbr.setName(dbbr.getName());
			mgbr.setDescription(dbbr.getDescription());
			mgbr.setFlag(dbbr.isFlag());
			broles.add(mgbr);
		}
		}

	public void deleteEntry(WritableList inputBRoles, ISelection selection)
		{
		glob.setDebugmessage(" - start deleteEntry");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraBusRole YafraBusRoleElement = (MGYafraBusRole) sel
				.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of "
				+ YafraBusRoleElement.getName());
		// TODO potential multiple selection delete - not wished at this moment
		getMHIBusRoles();
		mhibrole.deleteBusinessRole(YafraBusRoleElement.getName());
		inputBRoles.remove(YafraBusRoleElement);
		}

	public MHIYafraBusinessRoleRemote getMHIBusRoles()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhibrole != null)
			return mhibrole;
		try {
			mhibrole = (MHIYafraBusinessRoleRemote) glob.getEjbcontext()
					.lookup("MHIYafraBusinessRoleRemote");
		} catch (NamingException e) {
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
		}
		return mhibrole;
		}

	/*
	 * add / remove role to / from user
	 */
	public void addRole(MGYafraBusRole mgbr, ISelection selection, MHIYafraUserRemote mhiuser)
		{
		glob.setDebugmessage(" - start add new business role");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraUser YafraUserElement = (MGYafraUser) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of " + YafraUserElement.getName());
		getMHIBusRoles();
		MYafraUser myu = mhiuser.selectUser(YafraUserElement.getUserId());
		MYafraBusinessRole mybr = mhibrole.selectBusinessRole(mgbr.getName());
		mhiuser.addBusinessRole(myu, mybr);
		}
	public void removeRole(MGYafraBusRole mgbr, ISelection selection, MHIYafraUserRemote mhiuser)
		{
		glob.setDebugmessage(" - start remove business role");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraUser YafraUserElement = (MGYafraUser) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of " + YafraUserElement.getName());
		getMHIBusRoles();
		MYafraUser myu = mhiuser.selectUser(YafraUserElement.getUserId());
		MYafraBusinessRole mybr = mhibrole.selectBusinessRole(mgbr.getName());
		mhiuser.removeBusinessRole(myu, mybr);
		}

	}
