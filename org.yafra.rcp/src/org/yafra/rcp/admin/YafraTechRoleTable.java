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
import org.yafra.model.MYafraRole;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote;
import org.yafra.server.ejbRemote.MHIYafraRoleRemote;

/**
 * Manage JFace Table of Yafra Business Role to be used within a group
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraTechRoleTable
	{
	private GlobalSettings glob;
	private YafraTechRoleTableSorter tableSorterTRoles;
	public MHIYafraRoleRemote mhitrole = null;
	private MHIYafraBusinessRoleRemote mhibrole = null;

	public YafraTechRoleTable() {
	glob = GlobalSettings.getSingletonObject();
	}

	public void loadTableData(TableViewer viewerRoles, WritableList inputRoles)
		{
		// Get the content for the viewer, setInput will call getElements in the
		// contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());
		viewerRoles.setInput(inputRoles);
		tableSorterTRoles = new YafraTechRoleTableSorter();
		viewerRoles.setSorter(tableSorterTRoles);

		}

	/**
	 * @wbp.parser.entryPoint
	 */
	public void createTable(TableViewer viewerRoles, List<MGYafraTechRole> troles)
		{
		// business role table viewer
		this.fillTable(troles, null);
		tableCreateCols(viewerRoles);
		viewerRoles.setContentProvider(new ObservableListContentProvider());
		viewerRoles.setLabelProvider(new YafraTechRoleLabelProvider());
		}

	private void tableCreateCols(final TableViewer viewer)
		{
		String[] titles = { "Name", "Description", "Rights" };
		int[] bounds = { 100, 500, 100 };

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
							tableSorterBusRoles = (YafraBusRoleTableSorter) viewer.getSorter();
							tableSorterBusRoles.setColumn(index);
							int dir = viewer.getTable().getSortDirection();
							if (viewer.getTable().getSortColumn() == viewerColumn.getColumn()) {
								dir = dir == SWT.UP ? SWT.DOWN : SWT.UP;
							} else {
								dir = SWT.DOWN;
							}
							viewer.getTable().setSortDirection(dir);
							viewer.getTable().setSortColumn(viewerColumn.getColumn());
							viewer.refresh();
							}
					});
		}
		GridData gridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 1,	1);
		viewer.getTable().setLayoutData(gridData);
		viewer.getTable().setHeaderVisible(true);
		viewer.getTable().setLinesVisible(true);
		}

	protected void fillTable(List<MGYafraTechRole> troles, MGYafraBusRole mgybr)
		{
		List<MYafraRole> perslist;
		getMHITechRoles();
		getMHIBusRoles();
		troles.clear(); // clear any existing list as this list will be rebuild by every new user selection
		if (mgybr == null)
			{
			perslist = (List<MYafraRole>) mhitrole.getRoles();
			}
		else
			{
			MYafraBusinessRole mybr = new MYafraBusinessRole();
			mybr.setName(mgybr.getName());
			mybr.setFlag(mgybr.getFlag());
			mybr.setDescription(mgybr.getDescription());
			perslist = (List<MYafraRole>) mhibrole.getRoles(mybr);
			}
		if (perslist == null) return;
		Iterator<MYafraRole> it = perslist.iterator();
		while (it.hasNext())
			{
			MYafraRole dbbr = it.next();
			MGYafraTechRole mgbr = new MGYafraTechRole();
			mgbr.setName(dbbr.getName());
			mgbr.setDescription(dbbr.getDescription());
			mgbr.setRights(dbbr.getRights());
			troles.add(mgbr);
			}
		}

	public void deleteEntry(WritableList inputBRoles, ISelection selection)
		{
		glob.setDebugmessage(" - start deleteEntry");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraTechRole YafraTechRoleElement = (MGYafraTechRole) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of "	+ YafraTechRoleElement.getName());
		// TODO potential multiple selection delete - not wished at this moment
		getMHITechRoles();
		mhitrole.deleteRole(YafraTechRoleElement.getName());
		inputBRoles.remove(YafraTechRoleElement);
		}

	public MHIYafraRoleRemote getMHITechRoles()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhitrole != null)
			return mhitrole;
		try {
			mhitrole = (MHIYafraRoleRemote) glob.getEjbcontext().lookup("MHIYafraRoleRemote");
		} catch (NamingException e) {
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
		}
		return mhitrole;
		}

	private void getMHIBusRoles()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhibrole != null)
			return;
		try {
			mhibrole = (MHIYafraBusinessRoleRemote) glob.getEjbcontext().lookup("MHIYafraBusinessRoleRemote");
		} catch (NamingException e) {
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
		}
		return;
		}


	/*
	 * add / remove technical role to / from business role
	 */
	public void addRole(MGYafraTechRole YafraRoleElement, MHIYafraBusinessRoleRemote mhibrole)
		{
		glob.setDebugmessage(" - start add new role");
		getMHITechRoles();
		MYafraBusinessRole mybr = mhitrole.selectBusinessRole(YafraRoleElement.getName());
		MYafraRole myr = mhitrole.selectRole(YafraRoleElement.getName());
		glob.setDebugmessage(" -  adding role " + myr.getName() + " to business role " + mybr.getName());
		mhibrole.addRole(mybr, myr);
		}
	public void removeRole(ISelection selection, MHIYafraBusinessRoleRemote mhibrole)
		{
		glob.setDebugmessage(" - start removal of role");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraTechRole YafraRoleElement = (MGYafraTechRole) sel.getFirstElement();
		getMHITechRoles();
		MYafraBusinessRole mybr = mhitrole.selectBusinessRole(YafraRoleElement.getName());
		MYafraRole myr = mhitrole.selectRole(YafraRoleElement.getName());
		glob.setDebugmessage(" -  removing role " + myr.getName() + " from business role " + mybr.getName());
		mhibrole.removeRole(mybr, myr);
		}

}
