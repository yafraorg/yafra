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

import org.apache.wicket.markup.html.WebPage;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.panel.Panel;

/**
 * description
 *
 * @author mwn
 * @version 
 * @since 1.0
 */
public class AdminHeader extends Panel
	{
	private static final long serialVersionUID = 7773306672468301120L;

	/**
	 * @param id
	 * @param model
	 */
	public AdminHeader(String id, String title, WebPage page)
		{
		super(id);

		//add(new DebugBar("debug"));
		add(new Label("Title", title));
		//BookmarkablePageLink<Void> link = new BookmarkablePageLink<Void>("sources",SourcesPage.class, SourcesPage.generatePageParameters(page));
		//add(link);

		//PopupSettings settings = new PopupSettings("sources", PopupSettings.RESIZABLE);
		//settings.setWidth(800);
		//settings.setHeight(600);
		//link.setPopupSettings(settings);
		}

	}
