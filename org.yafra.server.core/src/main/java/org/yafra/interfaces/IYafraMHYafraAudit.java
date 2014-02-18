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

import java.util.List;

import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraUser;
import org.yafra.orm.YafraAudit;
import org.yafra.orm.YafraUser;

/**
 * Interface model handler person log - associations see person handler
 * @version $Id: IYafraMHPersonLog.java,v 1.3 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHYafraAudit
{

	/**
	 * Insert a new audit entry into the database
	 * 
	 * @param MPersonLog model object as input
	 * @return the new database object
	 * @since 1.0
	 */
	public YafraAudit insertYafraAudit(MYafraAudit mya);
	/**
	 * Insert a new audit entry into the database without any return - used within DTO
	 * 
	 * @param MPersonLog model object as input
	 * @since 1.0
	 */
	public void insertMYafraAudit(MYafraAudit mya);
	/**
	 * Update audit entry in the database
	 * 
	 * @param personlog database object as input
	 * @since 1.0
	 */
	public void updateYafraAudit(YafraAudit ya);
	/**
	 * Update audit in the database, makes a lookup first - used within DTO
	 * 
	 * @param MPerson model object as input
	 * @since 1.0
	 */
	public void updateYafraAudit(MYafraAudit mya);
	/**
	 * Delete directly an audit entry in the database
	 * 
	 * @param personlog cayenne database object as input
	 * @since 1.0
	 */
	public void deleteYafraAudit(YafraAudit ya);
	/**
	 * Delete directly an audit entry in the database
	 * 
	 * @param ID the audit entry ID as integer
	 * @since 1.0
	 */
	public void deleteYafraAudit(Integer id);

	/**
	 * Select an audit entry by its ID
	 * 
	 * @param ID ID of audit entry as selection criteria
	 * @return 1 database object
	 * @since 1.0
	 */
	public YafraAudit selectYafraAudit(Integer id);
	/**
	 * Select an audit entry by its ID
	 * 
	 * @param ID ID of audit entry as selection criteria
	 * @return 1 model object
	 * @since 1.0
	 */
	public MYafraAudit selectMYafraAudit(Integer id);

	/**
	 * Select all audit entries
	 * 
	 * @return 0-n database object
	 * @since 1.0
	 */
	public List<YafraAudit> getYafraAudits();
	/**
	 * Select all audit entries
	 * 
	 * @return 0-n model object
	 * @since 1.0
	 */
	public List<MYafraAudit> getMYafraAudits();

	/**
	 * get all audit entries for a user
	 * 
	 * @param user as selection criteria
	 * @return 0-n database object
	 * @since 1.0
	 */
	public List<YafraAudit> getYafraAudits(YafraUser yu);
	/**
	 * get all audit entries for user
	 * 
	 * @return 0-n model object
	 * @since 1.0
	 */
	public List<MYafraAudit> getMYafraAudits(MYafraUser myu);

	/**
	 * make relationship to user
	 * @param audit yafra audit entry
	 * @param user yafra user who is doing this audit entry
	 * @since 1.0
	 */
	public void setAuditUser(YafraAudit ya, YafraUser yu);
	/**
	 * make relationship to user
	 * @param audit yafra model audit entry
	 * @param user yafra model user who is doing this audit entry
	 * @since 1.0
	 */
	public void setAuditUser(MYafraAudit mya, MYafraUser myu);
}
