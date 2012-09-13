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
 * YafraAudit database object Attributes:
 * <ul>
 * <li>audit object - String - what do you audit (user, role, etc)
 * <li>audit text - String - the audit log entry
 * <li>audit timestamp - Date - of event
 * </ul>
 * 
 * @version $Id: IYafraMYafraUser.java,v 1.3 2009-12-09 22:52:07 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMYafraAudit extends Serializable {
	public Integer getDbPK();
	public void setDbPK(Integer pk);

	public void setAuditobject(String auditobject);
	public String getAuditobject();

	public void setAudittext(String name);
	public String getAudittext();

	public void setTimestamp(Date timestamp);
	public Date getTimestamp();
}
