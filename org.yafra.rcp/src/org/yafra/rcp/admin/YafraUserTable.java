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
import org.yafra.server.ejbRemote.MHIYafraUserRemote;

/**
 * Manage JFace Table of Yafra Business Role to be used within a group
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraUserTable
	{
	private GlobalSettings glob;
	private YafraUserTableSorter tableSorterUser;
	public MHIYafraUserRemote mhiuser = null;

	public YafraUserTable()
		{
		glob = GlobalSettings.getSingletonObject();
		}

	public void loadTableData(TableViewer viewerUsers, WritableList inputUser)
		{
		// Get the content for the viewer, setInput will call getElements in the
		// contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());
		viewerUsers.setInput(inputUser);
		tableSorterUser = new YafraUserTableSorter();
		viewerUsers.setSorter(tableSorterUser);
		}

	/**
	 * @wbp.parser.entryPoint
	 */
	public void createTable(TableViewer viewerUsers, List<MGYafraUser> users)
		{
		// business role table viewer
		this.fillTable(users, null);
		tableCreateCols(viewerUsers);
		viewerUsers.setContentProvider(new ObservableListContentProvider());
		// viewerUser.setContentProvider(new YafraUserContentProvider());
		viewerUsers.setLabelProvider(new YafraUserLabelProvider());
		}

	public void tableCreateCols(final TableViewer viewer)
		{
		String[] titles =
			{ "User name", "User ID", "Picture" };
		int[] bounds =
			{ 200, 100, 500 };

		for (int i = 0; i < titles.length; i++)
			{
			final int index = i;
			final TableViewerColumn viewerColumn = new TableViewerColumn(viewer, SWT.NONE);
			viewerColumn.getColumn().setText(titles[i]);
			viewerColumn.getColumn().setWidth(bounds[i]);
			viewerColumn.getColumn().setResizable(true);
			viewerColumn.getColumn().setMoveable(true);
			// Setting the right sorter
			viewerColumn.getColumn().addSelectionListener(new SelectionAdapter()
				{
					@Override
					public void widgetSelected(SelectionEvent e)
						{
						YafraUserTableSorter tableSorterUser = (YafraUserTableSorter) viewer.getSorter();
						tableSorterUser.setColumn(index);
						int dir = viewer.getTable().getSortDirection();
						if (viewer.getTable().getSortColumn() == viewerColumn.getColumn())
							{
							dir = dir == SWT.UP ? SWT.DOWN : SWT.UP;
							}
						else
							{

							dir = SWT.DOWN;
							}
						viewer.getTable().setSortDirection(dir);
						viewer.getTable().setSortColumn(viewerColumn.getColumn());
						viewer.refresh();
						}
				});
			}
		GridData gridData = new GridData(SWT.LEFT, SWT.CENTER, true, false, 1, 1);
		viewer.getTable().setLayoutData(gridData);
		viewer.getTable().setHeaderVisible(true);
		viewer.getTable().setLinesVisible(true);
		}

	public void fillTable(List<MGYafraUser> users, MGYafraBusRole mgybr)
		{
		getMHIUser();
		users.clear();
		List<MYafraUser> perslist = null;
		if (mgybr == null)
			{
			perslist = (List<MYafraUser>) mhiuser.getUsers();
			}
		else
			{
			MYafraBusinessRole mybr = new MYafraBusinessRole();
			mybr.setName(mgybr.getName());
			mybr.setFlag(mgybr.getFlag());
			mybr.setDescription(mgybr.getDescription());
			perslist = (List<MYafraUser>) mhiuser.getUsers(mybr);
			}
		Iterator<MYafraUser> it = perslist.iterator();
		while (it.hasNext())
			{
			MYafraUser dbuser = it.next();
			MGYafraUser u = new MGYafraUser();
			u.setName(dbuser.getName());
			u.setUserId(dbuser.getUserid());
			u.setPicturelink(dbuser.getPicturelink());
			users.add(u);
			}
		}

	public void deleteEntry(WritableList inputUser, ISelection selection)
		{
		glob.setDebugmessage(" - start deleteEntry");
		if (selection == null || !(selection instanceof IStructuredSelection)) return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraUser YafraUserElement = (MGYafraUser) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of " + YafraUserElement.getName());
		// TODO potential multiple selection delete - not wished at this moment
		getMHIUser();
		mhiuser.deleteUser(YafraUserElement.getUserId());
		inputUser.remove(YafraUserElement);
		}

	public void getMHIUser()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhiuser != null) return;
		try
			{
			mhiuser = (MHIYafraUserRemote) glob.getEjbcontext().lookup("MHIYafraUserRemote");
			}
		catch (NamingException e)
			{
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
			}
		}
	}
