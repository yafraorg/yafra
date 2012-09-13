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
package org.yafra.model;

import org.yafra.orm.YafraRole;

/**
 * Transform to/from database object to model object</br>
 * model object from database object from(database)
 * @version $Id: MYafraRoleTransform.java,v 1.1 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MYafraRoleTransform
{
	/**
	 * copy from cayenne object to model object
	 * 
	 * @param YafraRole	a cayenne database object
	 * @return			a model object
	 * @since			1.0
	 */
	public MYafraRole from(YafraRole from)
		{
		MYafraRole to = new MYafraRole();
		to.setName(from.getName());
		to.setDescription(from.getDescription());
		to.setRights(from.getRights());
		return to;
		}
	
	/**
	 * copy from model object to cayenne object
	 * 
	 * @param MYafraRole	a model object
	 * @param YafraRole		a cayenne database object
	 * @since				1.0
	 */
	public void to(MYafraRole from, YafraRole to)
		{
		to.setName(from.getName());
		to.setDescription(from.getDescription());
		to.setRights(from.getRights());
		}
}
