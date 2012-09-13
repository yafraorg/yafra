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
import java.util.Date;

/**
 * YafraBusinessRole database object</br>
 * Attributes:
 * <ul>
 * <li>dbPK - cayenne primary key as Integer
 * <li>eventAudit - String
 * <li>eventAuditReviewer - user who reviewed the audit log entry as String
 * <li>eventCreator - user who created the audit log entry as String
 * <li>eventDate - date of log creation as Date
 * <li>description - String
 * </ul>
 * @version $Id: IYafraMPersonLog.java,v 1.2 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @since 1.0
 */
public interface IYafraMPersonLog extends Serializable
{
public Integer getDbPK();
public void setDbPK(Integer pk);

public String getEventAudit();
public void setEventAudit(String eventAudit);

public String getEventAuditReviewer();
public void setEventAuditReviewer(String eventAuditReviewer);

public String getEventCreator();
public void setEventCreator(String eventCreator);

public Date getEventDate();
public void setEventDate(Date eventDate);

public String getEventDescription();
public void setEventDescription(String eventDescription);
}
