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

import java.util.Date;

import org.yafra.interfaces.IYafraMYafraAudit;

/**
 * Object</br>
 * @see org.yafra.interfaces.IYafraMYafraRole
 * @version $Id: MYafraRole.java,v 1.2 2009-12-09 22:40:15 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class MYafraAudit implements IYafraMYafraAudit
{
	/**
	 * DTO Model
	 */
	private static final long serialVersionUID = 1L;
	private Integer pk;
	private String auditobject;
	private String audittext;
	private Date timestamp;
	
	public MYafraAudit() {	}

	public Integer getDbPK() {return pk;}
	public void setDbPK(Integer p_pk) {this.pk = p_pk;}

	public void setAuditobject(String p_auditobject) { this.auditobject = p_auditobject;	}
	public String getAuditobject() { return this.auditobject; }

	public void setAudittext(String p_audittext) { this.audittext = p_audittext;	}
	public String getAudittext(){ return this.audittext; }
   
	public void setTimestamp(Date p_timestamp) { this.timestamp = p_timestamp;	}
	public Date getTimestamp(){ return this.timestamp; }
}
