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

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;

/**
 * @author mwn
 * 
 */
public class MGYafraUser implements PropertyChangeListener
{
	private String name;

	private String picturelink;

	private String id;

	private PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

	/**
	 * 
	 */
	public MGYafraUser()
		{
		// TODO Auto-generated constructor stub
		}

	public MGYafraUser(String name, String id, String piclink)
		{
		super();
		this.name = name;
		this.id = id;
		this.picturelink = piclink;
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

	public String getPicturelink()
		{
		return picturelink;
		}

	public String getName()
		{
		return name;
		}

	public void setPicturelink(String picturelink)
		{
		propertyChangeSupport.firePropertyChange("picturelink", this.picturelink, this.picturelink = picturelink);
		}

	public void setName(String lastName)
		{
		propertyChangeSupport.firePropertyChange("name", this.name, this.name = lastName);
		}

	public String getUserId()
		{
		return id;
		}

	public void setUserId(String guiid)
		{
		propertyChangeSupport.firePropertyChange("id", this.id, this.id = guiid);
		}

	@Override
	public String toString()
		{
		return name;
		}
}
