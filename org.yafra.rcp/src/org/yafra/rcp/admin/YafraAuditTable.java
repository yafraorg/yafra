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
import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraUser;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraAuditRemote;

/**
 * Manage JFace Table of Yafra Business Role to be used within a group
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class YafraAuditTable
	{
	private GlobalSettings glob;
	private YafraAuditTableSorter tableSorterAudit;
	public MHIYafraAuditRemote mhiaudit = null;

	public YafraAuditTable() {
	glob = GlobalSettings.getSingletonObject();
	}

	public void loadTableData(TableViewer viewerAudits, WritableList inputAudits)
		{
		// Get the content for the viewer, setInput will call getElements in the
		// contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());
		viewerAudits.setInput(inputAudits);
		tableSorterAudit = new YafraAuditTableSorter();
		viewerAudits.setSorter(tableSorterAudit);

		}

	/**
	 * @wbp.parser.entryPoint
	 */
	public void createTable(TableViewer viewerAudits, List<MGYafraAudit> audits)
		{
		// business role table viewer
		this.fillTable(audits, null);
		tableCreateCols(viewerAudits);
		viewerAudits.setContentProvider(new ObservableListContentProvider());
		viewerAudits.setLabelProvider(new YafraAuditLabelProvider());
		}

	private void tableCreateCols(final TableViewer viewer)
		{
		String[] titles = { "Object", "Text", "Timestamp" };
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
							YafraAuditTableSorter tableSorterAudit;
							tableSorterAudit = (YafraAuditTableSorter) viewer.getSorter();
							tableSorterAudit.setColumn(index);
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

	protected void fillTable(List<MGYafraAudit> audits, MGYafraUser mgyu)
		{
		List<MYafraAudit> ya_list;
		getMHIaudit();
		audits.clear(); // clear any existing list as this list will be rebuild by every new user selection
		if (mgyu == null)
		{
			// TODO null as user would mean all logs - check ejb impl.
			ya_list = (List<MYafraAudit>) mhiaudit.getYafraAudit(null);
		}
		else
			{
			MYafraUser myu = new MYafraUser();
			myu.setName(mgyu.getName());
			myu.setPicturelink(mgyu.getPicturelink());
			myu.setUserid(mgyu.getUserId());
			ya_list = (List<MYafraAudit>) mhiaudit.getYafraAudit(myu);
			}
		if (ya_list == null) return;
		Iterator<MYafraAudit> it = ya_list.iterator();
		while (it.hasNext())
			{
			MYafraAudit mya = it.next();
			MGYafraAudit mgya = new MGYafraAudit();
			mgya.setAuditobject(mya.getAuditobject());
			mgya.setAudittext(mya.getAudittext());
			mgya.setTimestamp(mya.getTimestamp());
			audits.add(mgya);
			}
		}

	public void deleteEntry(WritableList inputBRoles, ISelection selection)
		{
		glob.setDebugmessage(" - start deleteEntry");
		if (selection == null || !(selection instanceof IStructuredSelection))
			return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGYafraAudit YafraAuditElement = (MGYafraAudit) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of "	+ YafraAuditElement.getDbPK());
		// TODO potential multiple selection delete - not wished at this moment
		getMHIaudit();
		mhiaudit.deleteYafraAudit(YafraAuditElement.getDbPK());
		inputBRoles.remove(YafraAuditElement);
		}

	public MHIYafraAuditRemote getMHIaudit()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhiaudit != null)
			return mhiaudit;
		try {
			mhiaudit = (MHIYafraAuditRemote) glob.getEjbcontext().lookup("MHIYafraAuditRemote");
		} catch (NamingException e) {
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
		}
		return mhiaudit;
		}
}
