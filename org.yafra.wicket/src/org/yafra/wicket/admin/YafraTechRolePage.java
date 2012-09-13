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
package org.yafra.wicket.admin;

import java.util.List;

import org.apache.wicket.authroles.authorization.strategies.role.annotations.AuthorizeInstantiation;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.list.ListItem;
import org.apache.wicket.markup.html.list.PageableListView;
import org.apache.wicket.markup.html.navigation.paging.PagingNavigator;
import org.yafra.model.MYafraRole;
import org.yafra.modelhandler.MHYafraRole;
import org.yafra.utils.Logging;

/**
 * Index page</br>
 * 
 * @see org.yafra.interfaces.IYafraMPerson
 * @version $Id: MPerson.java,v 1.3 2009-12-09 22:40:15 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@AuthorizeInstantiation("ADMIN")
public class YafraTechRolePage extends AdminPage
	{
	private static final long serialVersionUID = 1L;

	public YafraTechRolePage()
		{
		PageableListView personslist = new PageableListView("yafrarole", getRoles(), 15)
			{
				private static final long serialVersionUID = 1L;

				@Override
				protected void populateItem(ListItem item)
					{
					MYafraRole role = (MYafraRole) item.getModelObject();
					item.add(new Label("name", role.getName()));
					item.add(new Label("rights", role.getRights()));
					item.add(new Label("description", role.getDescription()));
					}
			};
		add(personslist);
		add(new PagingNavigator("navigator", personslist));
		}

	private List<MYafraRole> getRoles()
		{
		AdminSession s = getAdminSession();
		Logging l = s.getLogging();
		l.logDebug("internet - get all roles");
		MHYafraRole mhyr = new MHYafraRole(s.getDataContext(), l);
		return mhyr.getMRoles();
		}

	}
