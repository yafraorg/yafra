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
 *  
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @version $Id: Activator.java,v 1.1 2009-12-03 23:07:00 mwn Exp $
 * @since 1.0
 */

package org.yafra.rcp;

import javax.naming.Context;

import org.eclipse.jface.action.IStatusLineManager;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.ui.plugin.AbstractUIPlugin;
import org.osgi.framework.BundleContext;
import org.yafra.server.ejbRemote.YafraSessionRemote;
import org.yafra.utils.Logging;

/**
 * The activator class controls the plug-in life cycle
 */
public class Activator extends AbstractUIPlugin
{

	// The plug-in ID
	public static final String PLUGIN_ID = "org.yafra.rcp";

	// The shared instance
	private static Activator plugin;

	/**
	 * The constructor
	 */
	public Activator()
		{
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.ui.plugin.AbstractUIPlugin#start(org.osgi.framework.BundleContext
	 * )
	 */
	public void start(BundleContext context) throws Exception
		{
		super.start(context);
		plugin = this;
		// TODO init of application / logging
		GlobalSettings glob = GlobalSettings.getSingletonObject();
		glob.getRcplog().logInfo("start rcp");
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.ui.plugin.AbstractUIPlugin#stop(org.osgi.framework.BundleContext
	 * )
	 */
	public void stop(BundleContext context) throws Exception
		{
		plugin = null;
		super.stop(context);
		GlobalSettings glob = GlobalSettings.getSingletonObject();
		if (glob.isYafraSessionConnected() == true)
			{
			glob.getRcplog().logInfo("- shutdown but still logged in - do logout now");
			glob.getYafrases().Logout();
			}
		glob.setDebugmessage("\norg.yafra.rcp - stop rcp at activator");
		glob.getRcplog().logInfo("org.yafra.rcp - stop rcp");
		}

	/**
	 * Returns the shared instance
	 * 
	 * @return the shared instance
	 */
	public static Activator getDefault()
		{
		return plugin;
		}

	/**
	 * Returns an image descriptor for the image file at the given plug-in
	 * relative path
	 * 
	 * @param path
	 *           the path
	 * @return the image descriptor
	 */
	public static ImageDescriptor getImageDescriptor(String path)
		{
		return imageDescriptorFromPlugin(PLUGIN_ID, path);
		}
}
