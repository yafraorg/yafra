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
import org.yafra.interfaces.IYafraMPerson;
import org.yafra.model.MPerson;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIPersonRemote;

/**
 * Manage JFace Table of Person to be used within a group
 * 
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @version $Id: YafraUserView.java,v 1.8 2009-12-19 20:40:33 mwn Exp $
 * @since 1.0
 */
public class PersonTable
	{
	private GlobalSettings glob;
	private PersonTableSorter tableSorterPerson;
	public MHIPersonRemote mhiperson = null;

	public PersonTable()
		{
		glob = GlobalSettings.getSingletonObject();
		}

	public void loadTableData(TableViewer viewerPersons, WritableList inputPerson)
		{
		// Get the content for the viewer, setInput will call getElements in the
		// contentProvider
		// viewerUser.setInput(YafraUserDataProvider.getInstance().getPersons());
		viewerPersons.setInput(inputPerson);
		tableSorterPerson = new PersonTableSorter();
		viewerPersons.setSorter(tableSorterPerson);
		}

	/**
	 * @wbp.parser.entryPoint
	 */
	public void createTable(TableViewer viewerPersons, List<MGPerson> persons)
		{
		// business role table viewer
		this.fillTable(persons, null);
		tableCreateCols(viewerPersons);
		viewerPersons.setContentProvider(new ObservableListContentProvider());
		// viewerUser.setContentProvider(new YafraUserContentProvider());
		viewerPersons.setLabelProvider(new PersonLabelProvider());
		}

	public void tableCreateCols(final TableViewer viewer)
		{
		String[] titles =
			{ "ID", "Name", "First name", "Address", "Type" };
		int[] bounds =
			{ 50, 100, 100, 500, 50 };

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
						PersonTableSorter tableSorterUser = (PersonTableSorter) viewer.getSorter();
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

	public void fillTable(List<MGPerson> persons, MGPersonLog mgybr)
		{
		this.getMHI();
		persons.clear();
		List<MPerson> perslist = null;
		if (mgybr == null)
			{
			perslist = (List<MPerson>) mhiperson.getPersons();
			}
		else
			{
			perslist = (List<MPerson>) mhiperson.getPersons();
			}
		Iterator<MPerson> it = perslist.iterator();
		while (it.hasNext())
			{
			IYafraMPerson dbperson = it.next();
			MGPerson p = new MGPerson();
			p.setAddress(dbperson.getAddress());
			p.setName(dbperson.getName());
			p.setFirstname(dbperson.getFirstname());
			p.setId(dbperson.getId());
			p.setType(dbperson.getType());
			// p.setCountry(dbperson.getCountry());
			// p.setGoogleId(dbperson.getGoogleId());
			persons.add(p);
			}
		}

	public void deleteEntry(WritableList inputUser, ISelection selection)
		{
		glob.setDebugmessage(" - start deleteEntry");
		if (selection == null || !(selection instanceof IStructuredSelection)) return;
		IStructuredSelection sel = (IStructuredSelection) selection;
		MGPerson PersonElement = (MGPerson) sel.getFirstElement();
		glob.setDebugmessage(" - selection on master table on deletion of " + PersonElement.getName());
		// TODO potential multiple selection delete - not wished at this moment
		getMHI();
		mhiperson.deletePerson(PersonElement.getId());
		inputUser.remove(PersonElement);
		}

	public void getMHI()
		{
		glob.setDebugmessage(" - get ejb handler implementation");
		if (mhiperson != null) return;
		try
			{
			mhiperson = (MHIPersonRemote) glob.getEjbcontext().lookup("MHIPersonRemote");
			}
		catch (NamingException e)
			{
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
			}
		}
	}
