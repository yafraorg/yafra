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
package org.yafra.rcp.model;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

/**
 * @author mwn
 * 
 */
public class MGYafraBusRole implements PropertyChangeListener
	{
	private String name;
	private String description;
	private Boolean flag;
	private PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

	/**
	 * 
	 */
	public MGYafraBusRole() {
	// TODO Auto-generated constructor stub
	}

	public MGYafraBusRole(String name, String desc, Boolean active)
		{
		super();
		this.name = name;
		this.description = desc;
		this.flag = active;
		}

	/*
	 * (non-Javadoc)
	 * 
	 * @seejava.beans.PropertyChangeListener#propertyChange(java.beans.
	 * PropertyChangeEvent)
	 */
	@Override
	public void propertyChange(PropertyChangeEvent arg0)
		{
		// TODO Auto-generated method stub

		}

	public void addPropertyChangeListener(String propertyName, PropertyChangeListener listener)
		{
		propertyChangeSupport.addPropertyChangeListener(propertyName, listener);
		}

	public void removePropertyChangeListener(PropertyChangeListener listener)
		{
		propertyChangeSupport.removePropertyChangeListener(listener);
		}

	public String getDescription() {return description;	}
	public void setDescription(String desc)	{propertyChangeSupport.firePropertyChange("description",this.description, this.description = desc);	}

	public String getName()	{return name;}
	public void setName(String lastName) { propertyChangeSupport.firePropertyChange("name", this.name,this.name = lastName);}

	public Boolean getFlag(){return flag;}
	public void setFlag(boolean flag){propertyChangeSupport.firePropertyChange("flag", this.flag,this.flag = flag);	}

	@Override
	public String toString()
		{
		return name;
		}
	}
