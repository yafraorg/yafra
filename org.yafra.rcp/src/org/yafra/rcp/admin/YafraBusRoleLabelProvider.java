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

import org.eclipse.jface.viewers.ITableLabelProvider;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.graphics.Image;
import org.yafra.rcp.Activator;

// String[] titles = { "Name", "Description", "Active" }; - see YafrBusRoleView

/**
 * @author mwn
 * 
 */
public class YafraBusRoleLabelProvider extends LabelProvider implements ITableLabelProvider
{
	private static final Image CHECKED = Activator.getImageDescriptor("icons/checked.gif").createImage();
	private static final Image UNCHECKED = Activator.getImageDescriptor("icons/unchecked.gif").createImage();

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.jface.viewers.ITableLabelProvider#getColumnImage(java.lang
	 * .Object, int)
	 */
	@Override
	public Image getColumnImage(Object element, int columnIndex)
		{
		if (columnIndex == 2)
			{
			if (((MGYafraBusRole) element).getFlag())
				{
				return CHECKED;
				}
			else
				{
				return UNCHECKED;
				}
			}
		return null;
		}
	
	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.eclipse.jface.viewers.ITableLabelProvider#getColumnText(java.lang.
	 * Object, int)
	 */
	@Override
	public String getColumnText(Object element, int columnIndex)
		{
		MGYafraBusRole user = (MGYafraBusRole) element;
		switch (columnIndex)
			{
			case 0:
				return user.getName();
			case 1:
				return user.getDescription();
			case 2:
				return String.valueOf(user.getFlag());
			default:
				throw new RuntimeException(" - ERROR out of range on table label provider");
			}

		}

}
