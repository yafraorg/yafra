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

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
//import java.util.function.Function;
//import java.util.function.ToDoubleFunction;
//import java.util.function.ToIntFunction;
//import java.util.function.ToLongFunction;

import org.apache.cayenne.access.DataContext;
import org.apache.wicket.extensions.markup.html.repeater.data.sort.SortOrder;
import org.apache.wicket.extensions.markup.html.repeater.util.SortableDataProvider;
import org.apache.wicket.model.AbstractReadOnlyModel;
import org.apache.wicket.model.IModel;
import org.apache.wicket.model.PropertyModel;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraUser;
import org.yafra.utils.Logging;

/**
 * description
 * 
 * @author mwn
 * @version
 * @since 1.0
 */
public class YafraUserDP extends SortableDataProvider<MYafraUser, String>
	{
	class SortableDataProviderComparator implements Comparator<MYafraUser>, Serializable
	{
	public int compare(final MYafraUser o1, final MYafraUser o2)
		{
		PropertyModel<Comparable> model1 = new PropertyModel<Comparable>(o1, (String) getSort().getProperty());
		PropertyModel<Comparable> model2 = new PropertyModel<Comparable>(o2, (String) getSort().getProperty());

		int result = model1.getObject().compareTo(model2.getObject());

		if (!getSort().isAscending())
			{
			result = -result;
			}

		return result;
		}

	}
	private SortableDataProviderComparator comparator = new SortableDataProviderComparator();

	private IModel<List<MYafraUser>> list;

	public YafraUserDP()
		{
		// The default sorting
		this.setSort("name", SortOrder.ASCENDING);
		// load data
		list = new YafraUserDM(); 
		}

	public Iterator<MYafraUser> iterator(final int first, final int count)
		{
		// In this example the whole list gets copied, sorted and sliced; in real applications typically your database would deliver a sorted and limited list

		// Get the data
		List<MYafraUser> newList = new ArrayList<MYafraUser>(list.getObject());

		// Sort the data
		// JAVA8 support: Collections.sort(newList, (MYafraUser a1, MYafraUser a2 ) -> ( a1.compareTo( a2 ) ));
		Collections.sort(newList, comparator);

		// Return the data for the current page - this can be determined only after sorting
		return newList.subList(first, first + count).iterator();
		}

	public long size()
		{
		return list.getObject().size();
		}

	/**
	 * @see org.apache.wicket.markup.repeater.data.IDataProvider#model(java.lang.Object)
	 */
	@Override
	public IModel<MYafraUser> model(final MYafraUser mu)
		{
		return new AbstractReadOnlyModel<MYafraUser>()
			{
				@Override
				public MYafraUser getObject()
					{
					return (MYafraUser) mu;
					}
			};
		}

	@Override
	public Iterator iterator(long arg0, long arg1)
		{
		// TODO Auto-generated method stub
		return null;
		}

	}
