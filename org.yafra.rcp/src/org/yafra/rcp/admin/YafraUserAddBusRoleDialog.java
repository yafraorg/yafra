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

import javax.naming.NamingException;

import org.eclipse.core.databinding.observable.list.WritableList;
import org.eclipse.jface.databinding.viewers.ObservableListContentProvider;
import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.jface.dialogs.IDialogConstants;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.jface.viewers.ListViewer;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.swt.SWT;
import org.eclipse.swt.custom.ScrolledComposite;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.yafra.model.MYafraBusinessRole;
import org.yafra.rcp.GlobalSettings;
import org.yafra.server.ejbRemote.MHIYafraBusinessRoleRemote;

public class YafraUserAddBusRoleDialog extends Dialog
{
private ListViewer viewerRoles;
private List<MGYafraBusRole> roles = new ArrayList<MGYafraBusRole>();
private WritableList inputRoles;
private GlobalSettings glob;
private List<MGYafraBusRole> selectedroles = new ArrayList<MGYafraBusRole>();


	/**
	 * Create the dialog.
	 * @param parentShell
	 */
	public YafraUserAddBusRoleDialog(Shell parentShell)
		{
		super(parentShell);
		glob = GlobalSettings.getSingletonObject();
		}

	/**
	 * Create contents of the dialog.
	 * @param parent
	 */
	@Override
	protected Control createDialogArea(Composite parent)
		{
		Composite container = (Composite) super.createDialogArea(parent);
		
		Label lblAddNewBusRole = new Label(container, SWT.NONE);
		lblAddNewBusRole.setText("Add new business role - select one or more roles below");
		
		ScrolledComposite scrolledComposite = new ScrolledComposite(container, SWT.BORDER | SWT.H_SCROLL | SWT.V_SCROLL);
		GridData gridData = new GridData(SWT.FILL, SWT.FILL, true, true, 1, 1);
		gridData.heightHint = 95;
		scrolledComposite.setLayoutData(gridData);
		scrolledComposite.setExpandHorizontal(true);
		scrolledComposite.setExpandVertical(true);
		
		fillList();
		inputRoles = new WritableList(roles, MGYafraBusRole.class);
		viewerRoles = new ListViewer(scrolledComposite, SWT.BORDER | SWT.MULTI);
		viewerRoles.setContentProvider(new ObservableListContentProvider());
		viewerRoles.setLabelProvider(new LabelProvider() {
      	public String getText(Object element) {
      		MGYafraBusRole user = (MGYafraBusRole) element;
      		return (user.getName() + " - " + user.getDescription());
      		}
		});
		viewerRoles.addSelectionChangedListener(new ISelectionChangedListener()
			{
				public void selectionChanged(SelectionChangedEvent event)
					{
					if (event.getSelection().isEmpty())
						{
						// if the selection is empty clear list
						selectedroles.clear();
						glob.setDebugmessage(" - selection change is empty");
						return;
						}
					if (event.getSelection() instanceof IStructuredSelection)
						{
						IStructuredSelection selection = (IStructuredSelection) event.getSelection();
						glob.setDebugmessage(" - selection on dialog business roles no of selections: " + selection.size());
				      for(Iterator<MGYafraBusRole> iterator = selection.iterator(); iterator.hasNext();)
				      	{
				      	selectedroles.add(iterator.next());
				      	}
						}
					}
			});
		viewerRoles.setInput(inputRoles);
		
		scrolledComposite.setContent(viewerRoles.getList());
		scrolledComposite.setMinSize(viewerRoles.getList().computeSize(SWT.DEFAULT, SWT.DEFAULT));
		
		return container;
		}

	/**
	 * Create contents of the button bar.
	 * @param parent
	 */
	@Override
	protected void createButtonsForButtonBar(Composite parent)
		{
		Button okbutton = createButton(parent, IDialogConstants.OK_ID, IDialogConstants.OK_LABEL, true);
	   okbutton.addSelectionListener(new SelectionAdapter() {
	      public void widgetSelected(SelectionEvent event) {
	        // check if selection list is empty - if so error message to user to use cancel or to do selection
	      	if (selectedroles.isEmpty())
	      		{
	      		MessageDialog.openInformation(getShell(), "Information", "You did not select an item");
	      		}
	      }
	    });
		createButton(parent, IDialogConstants.CANCEL_ID, IDialogConstants.CANCEL_LABEL, false);
		}

	/**
	 * Return the initial size of the dialog.
	 */
	@Override
	protected Point getInitialSize()
		{
		return new Point(602, 375);
		}
	
	public List<MGYafraBusRole> getSelection()
	{
		return selectedroles;
	}

	private void fillList()
		{
		MHIYafraBusinessRoleRemote mhibrole = null;
		List<MYafraBusinessRole> perslist;
		roles.clear(); // clear any existing list as this list will be rebuild by every new user selection
		selectedroles.clear();
		try
			{
			mhibrole = (MHIYafraBusinessRoleRemote) glob.getEjbcontext().lookup("MHIYafraBusinessRoleRemote");
			}
		catch (NamingException e)
			{
			glob.setDebugmessage(" - error with ejb context");
			e.printStackTrace();
			}
		perslist = (List<MYafraBusinessRole>) mhibrole.getBusinessRoles(true);
		Iterator<MYafraBusinessRole> it = perslist.iterator();
		while (it.hasNext())
			{
			MYafraBusinessRole dbrole = it.next();
			MGYafraBusRole r = new MGYafraBusRole();
			r.setName(dbrole.getName());
			r.setDescription(dbrole.getDescription());
			r.setFlag(dbrole.isFlag());
			roles.add(r);
			}

		}
}
