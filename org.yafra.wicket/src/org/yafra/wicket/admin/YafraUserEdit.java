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

import org.apache.wicket.feedback.IFeedback;
import org.apache.wicket.markup.html.basic.Label;
import org.apache.wicket.markup.html.form.Button;
import org.apache.wicket.markup.html.form.Form;
import org.apache.wicket.markup.html.form.TextField;
import org.apache.wicket.markup.html.panel.FeedbackPanel;
import org.apache.wicket.model.CompoundPropertyModel;
import org.apache.wicket.model.Model;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraUser;

/**
 * description
 * 
 * @author mwn
 * @version
 * @since 1.0
 */
public class YafraUserEdit extends AdminPage
	{

	/**
	 * 
	 */
	private static final long serialVersionUID = -7673548977411668987L;
	private FeedbackPanel feedbackPanel;
	private boolean updateflag;

	public YafraUserEdit()
		{
		this.CreateForm(null);
		}

	public YafraUserEdit(MYafraUser inputmyu)
		{
		this.CreateForm(inputmyu);
		}
	
	private void CreateForm(MYafraUser updmyu)
		{
		feedbackPanel = new FeedbackPanel("feedbackPanel");
		add(feedbackPanel);
		if (updmyu != null)
			{
			updateflag = true;
			add(new YafraUserForm("personForm", updmyu, updateflag));
			add(new Label("lFormops", "Update/Delete existing user"));
			}
		else
			{
			updateflag=false;
			MYafraUser newmyu = new MYafraUser();
			add(new YafraUserForm("personForm", newmyu, updateflag));
			add(new Label("lFormops", "New user"));
			}
		}

	class YafraUserForm extends Form
		{
		private String ID;
		public YafraUserForm(String s, MYafraUser myu, boolean uflag)
			{
			super(s, new CompoundPropertyModel(myu));
			if (uflag == true)
				{
				ID = myu.getUserid();
				}
			add(new Label("lName", "User name:"));
			add(new TextField("name").setRequired(true));
			add(new Label("lId", "User ID:"));
			add(new TextField("id").setRequired(true));
			add(new Label("lLink", "Link to picture:"));
			add(new TextField("link").setRequired(false));
			Button delete = new Button("bDelete"){
				public void onSubmit() {
					AdminApplication.getLogging().logInfo("internet - delete user: " + ID);
					MHYafraUser mhyu = new MHYafraUser(getAdminSession().getDataContext(), getAdminSession().getLogging());
					mhyu.deleteUser(ID);
					setResponsePage(new YafraUserPage());
				}
			};
			delete.setVisible(uflag);
			delete.setDefaultFormProcessing(false);
			add(delete);
			add(new Button("bSave"));
			}

		public void onSubmit()
			{
			MYafraUser myu = (MYafraUser) getDefaultModelObject();
			MHYafraUser mhyu = new MHYafraUser(getAdminSession().getDataContext(), getAdminSession().getLogging());
			if (updateflag == true)
				{
				AdminApplication.getLogging().logInfo("internet - update user: " + myu.getName());
				mhyu.updateUser(myu);
				}
			else
				{
				AdminApplication.getLogging().logInfo("internet - insert new user: " + myu.getName());
				mhyu.insertMUser(myu);
				}
			setResponsePage(new YafraUserPage());
			}
		}

	}
