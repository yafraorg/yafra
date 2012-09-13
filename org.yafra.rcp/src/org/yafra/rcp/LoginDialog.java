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
package org.yafra.rcp;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.jface.dialogs.IDialogConstants;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Point;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.yafra.utils.WhichUser;

/**
 * Login dialog - takes parameters to log into server
 * 
 * @author $Author: mwn $
 * @version $Id: LoginDialog.java,v 1.3 2009-12-24 08:29:53 mwn Exp $
 */
public class LoginDialog extends Dialog
{
	private Text Ipassword;

	private String userid;

	private String pwd;

	private String server;

	private Combo combo;

	/**
	 * Create the dialog
	 * 
	 * @param parentShell
	 */
	public LoginDialog(Shell parentShell)
		{
		super(parentShell);
		}

	/**
	 * Create contents of the dialog
	 * 
	 * @param parent
	 */
	@Override
	protected Control createDialogArea(Composite parent)
		{
		// TODO get properties from file to save settings
		Composite container = (Composite) super.createDialogArea(parent);
		final GridLayout gridLayout = new GridLayout();
		gridLayout.numColumns = 2;
		container.setLayout(gridLayout);

		final Label pleaseLoginToLabel = new Label(container, SWT.NONE);
		final GridData gridData = new GridData(SWT.LEFT, SWT.FILL, false, false);
		gridData.heightHint = 34;
		pleaseLoginToLabel.setLayoutData(gridData);
		pleaseLoginToLabel.setText("Please login to your yafra server:");
		new Label(container, SWT.NONE);

		final Label usernameLabel = new Label(container, SWT.NONE);
		usernameLabel.setText("Username:");
		WhichUser UserID = new WhichUser();
		userid = UserID.getUser();
		final Label useridLabel = new Label(container, SWT.NONE);
		useridLabel.setText(userid);
		// TODO handle exception if not identical to environment

		final Label passwordLabel = new Label(container, SWT.NONE);
		passwordLabel.setText("Password:");
		Ipassword = new Text(container, SWT.BORDER);
		Ipassword.setEchoChar('*');
		Ipassword.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false));

		final Label servernameLabel = new Label(container, SWT.NONE);
		servernameLabel.setText("Servername:");

		combo = new Combo(container, SWT.NONE);
		// TODO take hosts from preferences - initial preference should be localhost only but can be added in a list with own
		combo.add("localhost");
		combo.add("vmjboss");
		combo.add("webdevelop");
		combo.select(0);
		combo.setLayoutData(new GridData(SWT.FILL, SWT.CENTER, true, false, 1, 1));
		return container;
		}

	/**
	 * Create contents of the button bar
	 * 
	 * @param parent
	 */
	@Override
	protected void createButtonsForButtonBar(Composite parent)
		{
		createButton(parent, IDialogConstants.OK_ID, IDialogConstants.OK_LABEL, true);
		createButton(parent, IDialogConstants.CANCEL_ID, IDialogConstants.CANCEL_LABEL, false);
		}

	/**
	 * Return the initial size of the dialog
	 */
	@Override
	protected Point getInitialSize()
		{
		return new Point(518, 204);
		}

	@Override
	protected void configureShell(Shell newShell)
		{
		super.configureShell(newShell);
		newShell.setText("Login dialog");
		}

	@Override
	protected void okPressed()
		{

		if (combo.getItem(combo.getSelectionIndex()).length() != 0) server = combo.getItem(combo.getSelectionIndex());
		else server = new String("localhost"); // fallback to localhost
		pwd = Ipassword.getText();
		if (pwd.equals(""))
			{
			MessageDialog.openError(getShell(), "Invalid password", "Password field must not be blank.");
			return;
			}
		if (server.equals(""))
			{
			MessageDialog.openError(getShell(), "Invalid Server", "Server field must not be blank.");
			return;
			}
		super.okPressed();
		}

	public String getUserid()
		{
		return this.userid;
		}

	public String getPwd()
		{
		return this.pwd;
		}

	public String getServer()
		{
		return this.server;
		}
}
