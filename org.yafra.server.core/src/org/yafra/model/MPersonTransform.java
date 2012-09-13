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

import org.yafra.orm.Person;

/**
 * Transform to/from database object to model object</br>
 * model object from database object from(database)
 * @version $Id: MPersonTransform.java,v 1.3 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MPersonTransform
{
	/**
	 * copy from cayenne object to model object
	 * 
	 * @param Person	a cayenne database object
	 * @return			a model object
	 * @since			1.0
	 */
	public MPerson from(Person from)
		{
		MPerson to = new MPerson();
		to.setAddress(from.getAddress());
		to.setName(from.getName());
		to.setFirstname(from.getFirstname());
		to.setId(from.getId());
		to.setType(from.getType());
		to.setCountry(from.getCountry());
		to.setGoogleId(from.getGoogleId());
		return to;
		}
	
	/**
	 * copy from model object to cayenne object
	 * 
	 * @param MPerson	a model object
	 * @param Person	a cayenne database object
	 * @since			1.0
	 */
	public void to(MPerson from, Person to)
		{
		to.setAddress(from.getAddress());
		to.setName(from.getName());
		to.setFirstname(from.getFirstname());
		to.setId(from.getId());
		to.setType(from.getType());
		to.setCountry(from.getCountry());
		to.setGoogleId(from.getGoogleId());
		}
}
