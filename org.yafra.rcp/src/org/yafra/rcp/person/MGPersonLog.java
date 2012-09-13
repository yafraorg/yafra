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

package org.yafra.rcp.person;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.Date;

/**
 * @author mwn
 * 
 */
public class MGPersonLog implements PropertyChangeListener
{
	private Integer pk;
	private String eventAudit;
	private String eventAuditReviewer;
	private String eventCreator;
	private Date eventDate;
	private String eventDescription;

	private PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

	/**
	 * 
	 */
	public MGPersonLog()
		{
		// TODO Auto-generated constructor stub
		}

	public MGPersonLog(Integer pk, String eventAudit, String eventAuditReviewer, String eventCreator, Date eventDate, String eventDescription)
		{
		super();
		this.eventAudit = eventAudit;
		this.pk = pk;
		this.eventAuditReviewer = eventAuditReviewer;
		this.eventCreator = eventCreator;
		this.eventDate = eventDate;
		this.eventDescription = eventDescription;
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

	public String getEventAudit() {return eventAudit;	}
	public void setEventAudit(String eventAudit)	{propertyChangeSupport.firePropertyChange("eventAudit", this.eventAudit, this.eventAudit = eventAudit);}

	@Override
	public String toString()
		{
		return eventDescription + ": " + eventAudit;
		}
}
