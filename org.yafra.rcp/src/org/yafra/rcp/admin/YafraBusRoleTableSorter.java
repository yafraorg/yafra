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
 * @version $Id: YafraBusRoleTableSorter.java,v 1.1 2009-12-13 20:02:54 mwn Exp $
 * @since 1.0
 */
package org.yafra.rcp.admin;

import org.eclipse.jface.viewers.Viewer;
import org.eclipse.jface.viewers.ViewerSorter;

/**
 * @author mwn
 * 
 */
public class YafraBusRoleTableSorter extends ViewerSorter
{
	private int propertyIndex;

	// private static final int ASCENDING = 0;
	private static final int DESCENDING = 1;

	private int direction = DESCENDING;

	public YafraBusRoleTableSorter()
		{
		this.propertyIndex = 0;
		direction = DESCENDING;
		}

	public void setColumn(int column)
		{
		if (column == this.propertyIndex)
			{
			// Same column as last sort; toggle the direction
			direction = 1 - direction;
			}
		else
			{
			// New column; do an ascending sort
			this.propertyIndex = column;
			direction = DESCENDING;
			}
		}

	@Override
	public int compare(Viewer viewer, Object e1, Object e2)
		{
		MGYafraBusRole p1 = (MGYafraBusRole) e1;
		MGYafraBusRole p2 = (MGYafraBusRole) e2;
		int rc = 0;
		switch (propertyIndex)
			{
			case 0:
				rc = p1.getName().compareTo(p2.getName());
				break;
			case 1:
				rc = p1.getFlag().compareTo(p2.getFlag());
				break;
			case 2:
				rc = p1.getDescription().compareTo(p2.getDescription());
				break;
			default:
				rc = 0;
			}
		// If descending order, flip the direction
		if (direction == DESCENDING)
			{
			rc = -rc;
			}
		return rc;
		}
}
