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
import java.util.Date;

/**
 * @author mwn
 * 
 */
public class MGYafraAudit implements PropertyChangeListener
{
	private Integer pk;
	private String auditobject;
	private String audittext;
	private Date timestamp;
	private PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

	/**
	 * 
	 */
	public MGYafraAudit()
		{
		// TODO Auto-generated constructor stub
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

	public Integer getDbPK() {return pk;}
	public void setDbPK(Integer p_pk) { propertyChangeSupport.firePropertyChange("pk", this.pk, this.pk = p_pk);}

	public void setAuditobject(String p_auditobject) { propertyChangeSupport.firePropertyChange("auditobject", this.auditobject, this.auditobject = p_auditobject);}
	public String getAuditobject() { return this.auditobject; }

	public void setAudittext(String p_audittext) { propertyChangeSupport.firePropertyChange("audittext", this.audittext, this.audittext = p_audittext);}
	public String getAudittext(){ return this.audittext; }
   
	public void setTimestamp(Date p_timestamp) { propertyChangeSupport.firePropertyChange("timestamp", this.timestamp, this.timestamp = p_timestamp); }
	public Date getTimestamp(){ return this.timestamp; }
	

	@Override
	public String toString()
		{
		return audittext;
		}
}
