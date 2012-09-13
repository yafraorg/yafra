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

// String[] titles = { "Name", "Description", "Rights" }; - see YafrTechRoleView

/**
 * @author mwn
 * 
 */
public class YafraTechRoleLabelProvider extends LabelProvider implements ITableLabelProvider
{
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
		MGYafraTechRole user = (MGYafraTechRole) element;
		switch (columnIndex)
			{
			case 0:
				return user.getName();
			case 1:
				return user.getDescription();
			case 2:
				return user.getRights();
			default:
				throw new RuntimeException(" - ERROR out of range on table label provider");
			}

		}

	@Override
	public Image getColumnImage(Object element, int columnIndex)
		{
		// TODO Auto-generated method stub
		return null;
		}

}
