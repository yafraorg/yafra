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

import org.yafra.interfaces.IYafraMYafraUser;

/**
 * Object</br>
 * @see org.yafra.interfaces.IYafraMYafraUser
 * @version $Id: MYafraUser.java,v 1.3 2009-12-09 22:40:15 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MYafraUser implements IYafraMYafraUser
{
	/**
	 * DTO Model
	 */
	private static final long serialVersionUID = 1L;
	private String id;
	private String name;
	private String link;

	public MYafraUser() {	}

	public void setUserid(String id) { this.id = id;	}
	public String getUserid() { return this.id; }

	public void setName(String name) {this.name = name; }
	public String getName() {return this.name; }

	public void setPicturelink(String link) {this.link = link; }
	public String getPicturelink() { return this.link; }
}
