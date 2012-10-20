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

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import jxl.CellView;
import jxl.JXLException;
import jxl.Workbook;
import jxl.write.Label;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;

import org.apache.wicket.authroles.authorization.strategies.role.annotations.AuthorizeInstantiation;
import org.apache.wicket.extensions.markup.html.repeater.data.grid.ICellPopulator;
import org.apache.wicket.extensions.markup.html.repeater.data.table.AbstractColumn;
import org.apache.wicket.extensions.markup.html.repeater.data.table.DefaultDataTable;
import org.apache.wicket.extensions.markup.html.repeater.data.table.IColumn;
import org.apache.wicket.extensions.markup.html.repeater.data.table.PropertyColumn;
import org.apache.wicket.markup.html.link.DownloadLink;
import org.apache.wicket.markup.html.link.Link;
import org.apache.wicket.markup.html.panel.Panel;
import org.apache.wicket.markup.repeater.Item;
import org.apache.wicket.model.AbstractReadOnlyModel;
import org.apache.wicket.model.IModel;
import org.apache.wicket.model.Model;
import org.apache.wicket.util.time.Duration;
import org.yafra.model.MYafraUser;

/**
 * description
 * 
 * @author mwn
 * @version
 * @since 1.0
 */
@AuthorizeInstantiation("ADMIN")
public class YafraUserPage extends AdminPage
	{
	private static final long serialVersionUID = 1L;
	private MYafraUser selected;

	/**
	 * constructor
	 */
	public YafraUserPage()
		{

        final YafraUserDP userProvider = new YafraUserDP();
        
		List<IColumn<MYafraUser, String>> columns = new ArrayList<IColumn<MYafraUser, String>>();
		columns.add(new AbstractColumn<MYafraUser, String>(new Model<String>("Actions"))
		{
			public void populateItem(Item<ICellPopulator<MYafraUser>> cellItem, String componentId,
				IModel<MYafraUser> model)
			{
				cellItem.add(new ActionPanel(componentId, model));
			}
		});
		columns.add(new PropertyColumn(new Model<String>("First Name"), "name", "name"));
		columns.add(new PropertyColumn(new Model<String>("User ID"), "id", "id"));
	    columns.add(new PropertyColumn(new Model("Picture"), "link", "link")
	    	{ 
	    	}); 
        
        DefaultDataTable table = new DefaultDataTable("datatable", columns, userProvider, 20);
        
        add(table);
        add(new DownloadLink("excelExport", new AbstractReadOnlyModel<File>()
        {
            private static final long serialVersionUID = 1L;

            @Override
            public File getObject()
            {
                File tempFile = null;
                try
                	{
                    tempFile = File.createTempFile("yafra", ".xls");
                	IModel<List<MYafraUser>> list = new YafraUserDM(); 
            		Iterator<MYafraUser> it = list.getObject().iterator();
            		//InputStream data;
            		WritableWorkbook w = Workbook.createWorkbook(tempFile);
            		WritableSheet s = w.createSheet("Demo", 0);
            		MYafraUser myu = null;
            		int i = 1;
            		CellView autoSizeCV = new CellView();
            		autoSizeCV.setAutosize(true);
            		s.setColumnView(0, autoSizeCV);
            		s.setColumnView(1, autoSizeCV);
            		s.setColumnView(2, autoSizeCV);
        			s.addCell(new Label(0, 0, "Name"));
        			s.addCell(new Label(1, 0, "User ID"));
        			s.addCell(new Label(2, 0, "Picture link"));
            		while (it.hasNext()) {
            			myu = it.next();
            			s.addCell(new Label(0, i, myu.getName()));
            			s.addCell(new Label(1, i, myu.getUserid()));
            			s.addCell(new Label(2, i, myu.getPicturelink()));
            			i++;
            		}
            		w.write();
         		   	w.close();
                	}
                catch (IOException e)
                	{
                    throw new RuntimeException(e);
                	}
				catch (JXLException e)
					{
					e.printStackTrace();
					}

                return tempFile;
            }
        }).setCacheDuration(Duration.NONE).setDeleteAfterDownload(true)); 		}
	
	/**
	 * 
	 */
	class ActionPanel extends Panel
	{
		/**
		 * @param id
		 *            component id
		 * @param model
		 *            model for contact
		 */
		public ActionPanel(String id, IModel<MYafraUser> model)
		{
			super(id, model);
			add(new Link("select")
			{
				@Override
				public void onClick()
				{
				selected = (MYafraUser)getParent().getDefaultModelObject();
	            setResponsePage(new YafraUserEdit(selected));
				}
			});
		}
	}

	}
