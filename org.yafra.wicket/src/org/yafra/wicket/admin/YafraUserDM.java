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
 */

package org.yafra.wicket.admin;

import java.util.List;

import org.apache.cayenne.BaseContext;
import org.apache.cayenne.access.DataContext;
import org.apache.wicket.model.LoadableDetachableModel;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraUser;

/**
 * description
 *
 * @author mwn
 * @version 
 * @since 1.0
 */
public class YafraUserDM extends LoadableDetachableModel<List <MYafraUser>>
	{

	/**
	 * 
	 */
	private static final long serialVersionUID = 3724988370581514193L;

	/**
	 * @see org.apache.wicket.model.LoadableDetachableModel#load()
	 */
	@Override
	protected List<MYafraUser> load()
		{
		try {
			AdminApplication.getLogging().logInfo("internet - query users as loadable detachable model");
			MHYafraUser mhyu = new MHYafraUser((DataContext)BaseContext.getThreadObjectContext(), AdminApplication.getLogging());
			return mhyu.getMUsers();
			}
		catch (IndexOutOfBoundsException e)
			{
			AdminApplication.getLogging().logError("no entries found - returning null", e);
			return null;
			}
		}
	
	}
