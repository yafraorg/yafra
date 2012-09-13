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

package org.yafra.rcp.commands;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.handlers.HandlerUtil;
import org.yafra.rcp.GlobalSettings;

/**
 * @author mwn
 * 
 */
public class YafraBusRoleHandler extends AbstractHandler
{
	private IWorkbenchWindow preferredWindow = null;

	/*
	 * (non-Javadoc)
	 * 
	 * @seeorg.eclipse.core.commands.IHandler#execute(org.eclipse.core.commands.
	 * ExecutionEvent)
	 */
	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException
		{
		GlobalSettings glob = GlobalSettings.getSingletonObject();
		glob.setDebugmessage(" - start YafraBusRole command");
		preferredWindow = HandlerUtil.getActiveWorkbenchWindow(event);
		if (glob.isYafraSessionConnected() == false)
			{
			MessageDialog.openInformation(preferredWindow.getShell(), "Info", "Login first");
			return null;
			}
		try
			{
			preferredWindow.getActivePage().showView("org.yafra.rcp.admin.YafraBusRoleView");
			}
		catch (PartInitException e)
			{
			// TODO Auto-generated catch block
			e.printStackTrace();
			}

		return null;
		}

}
