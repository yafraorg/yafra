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
 * @version $Id: MGPerson.java,v 1.1 2009-12-03 23:07:02 mwn Exp $
 * @since 1.0
 */
package org.yafra.rcp.person;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

/**
 * @author mwn
 * 
 */
public class MGPerson implements PropertyChangeListener
{

	private String firstName;

	private String name;

	private String type;

	private Integer id;

	private String address;

	private PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

	@Override
	public void propertyChange(PropertyChangeEvent arg0)
		{
		// TODO Auto-generated method stub

		}

	public MGPerson()
		{
		}

	public void addPropertyChangeListener(String propertyName, PropertyChangeListener listener)
		{
		propertyChangeSupport.addPropertyChangeListener(propertyName, listener);
		}

	public void removePropertyChangeListener(PropertyChangeListener listener)
		{
		propertyChangeSupport.removePropertyChangeListener(listener);
		}

	public String getFirstname()
		{
		return firstName;
		}

	public String getType()
		{
		return type;
		}

	public String getName()
		{
		return name;
		}

	public void setFirstname(String firstName)
		{
		propertyChangeSupport.firePropertyChange("firstName", this.firstName, this.firstName = firstName);
		}

	public void setType(String type)
		{
		propertyChangeSupport.firePropertyChange("type", this.type, this.type = type);
		}

	public void setName(String lastName)
		{
		propertyChangeSupport.firePropertyChange("name", this.name, this.name = lastName);
		}

	public Integer getId()
		{
		return id;
		}

	public void setId(Integer guiid)
		{
		propertyChangeSupport.firePropertyChange("id", this.id, this.id = guiid);
		}

	public String getAddress()
		{
		return address;
		}

	public void setAddress(String guiaddress)
		{
		propertyChangeSupport.firePropertyChange("address", this.address, this.address = guiaddress);
		}

	@Override
	public String toString()
		{
		return name + " " + firstName;
		}

	/*
	 * @Override public void propertyChange(PropertyChangeEvent event) {
	 * propertyChangeSupport.firePropertyChange("address", null, address); }
	 */
}
