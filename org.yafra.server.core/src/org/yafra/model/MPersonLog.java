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
import java.util.Date;

import org.yafra.interfaces.IYafraMPersonLog;

/**
 * Object</br>
 * @see org.yafra.interfaces.IYafraMPersonLog
 * @version $Id: MPersonLog.java,v 1.4 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MPersonLog implements IYafraMPersonLog, Serializable
{
	/**
	 * DTO Model
	 */
	private static final long serialVersionUID = 1L;
	private Integer pk;
	private String eventAudit;
	private String eventAuditReviewer;
	private String eventCreator;
	private Date eventDate;
	private String eventDescription;
	
	public MPersonLog() {	}

	public Integer getDbPK() {return pk;}
	public void setDbPK(Integer pk) {this.pk = pk;}

	public String getEventAudit()	{return eventAudit;}
	public void setEventAudit(String eventAudit)	{this.eventAudit = eventAudit;}

	public String getEventAuditReviewer() {return eventAuditReviewer;}
	public void setEventAuditReviewer(String eventAuditReviewer) {this.eventAuditReviewer = eventAuditReviewer;}

	public String getEventCreator() {return eventCreator;}
	public void setEventCreator(String eventCreator) {this.eventCreator = eventCreator;}

	public Date getEventDate(){return eventDate;}
	public void setEventDate(Date eventDate) {this.eventDate = eventDate;}

	public String getEventDescription()	{return eventDescription;}
	public void setEventDescription(String eventDescription) {this.eventDescription = eventDescription;}
}
