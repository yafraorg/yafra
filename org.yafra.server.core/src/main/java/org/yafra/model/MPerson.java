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

import java.io.Serializable;

import org.yafra.interfaces.IYafraMPerson;

/**
 * Object</br>
 * @see org.yafra.interfaces.IYafraMPerson
 * @version $Id: MPerson.java,v 1.3 2009-12-09 22:40:15 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MPerson implements IYafraMPerson, Serializable
{
	/**
	 * DTO Model
	 */
	private static final long serialVersionUID = 1L;
	private String address;
	private String country;
	private String firstname;
	private String name;
	private String googleid;
	private Integer id;
	private String type;

	public MPerson() {	}

	public void setAddress(String address) { this.address = address;	}
	public String getAddress() { return this.address; }

	public void setCountry(String country) { this.country = country;	}
	public String getCountry(){ return this.country; }

	public void setFirstname(String firstname) { this.firstname = firstname;	}
	public String getFirstname(){ return this.firstname; }

	public void setGoogleId(String googleId) { this.googleid = googleId;	}
	public String getGoogleId(){ return this.googleid; }

	public void setId(Integer id) { this.id = id;	}
	public Integer getId(){ return this.id; }

	public void setName(String name) { this.name = name;	}
	public String getName(){ return this.name; }

	public void setType(String type) { this.type = type;	}
	public String getType(){ return this.type; }
}
