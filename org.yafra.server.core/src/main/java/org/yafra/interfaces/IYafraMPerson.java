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
package org.yafra.interfaces;

import java.io.Serializable;

/**
 * Person database object</br>
 * Attributes:
 * <ul>
 * <li>id (unique) - Integer
 * <li>name - String
 * <li>firstname - String
 * <li>address - String
 * <li>country - String
 * <li>googleid - URL to the google profile of the person as String
 * <li>type - type of person as String
 * </ul>
 * @version $Id: IYafraMPerson.java,v 1.4 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMPerson extends Serializable
{
	public void setAddress(String address);
   public String getAddress();
   public void setCountry(String country);
   public String getCountry();
   public void setFirstname(String firstname);
   public String getFirstname();
   public void setGoogleId(String googleId);
   public String getGoogleId();
   public void setId(Integer id);
   public Integer getId();
   public void setName(String name);
   public String getName();
   public void setType(String type);
   public String getType();
}
