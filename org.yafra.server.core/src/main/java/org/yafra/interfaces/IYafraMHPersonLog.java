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

import org.yafra.model.MPersonLog;
import org.yafra.orm.PersonLog;

/**
 * Interface model handler person log - associations see person handler
 * @version $Id: IYafraMHPersonLog.java,v 1.3 2009-12-12 18:49:20 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHPersonLog
{

	/**
	 * Insert a new log entry into the database
	 * 
	 * @param MPersonLog model object as input
	 * @return the new database object
	 * @since 1.0
	 */
	public PersonLog insertPersonLog(MPersonLog mpl);
	/**
	 * Insert a new log entry into the database without any return - used within DTO
	 * 
	 * @param MPersonLog model object as input
	 * @since 1.0
	 */
	public void insertMPersonLog(MPersonLog mpl);
	/**
	 * Update person log entry in the database
	 * 
	 * @param personlog database object as input
	 * @since 1.0
	 */
	public void updatePersonLog(PersonLog pl);
	/**
	 * Update person in the database, makes a lookup first - used within DTO
	 * 
	 * @param MPerson model object as input
	 * @since 1.0
	 */
	public void updatePersonLog(MPersonLog mpl);
	/**
	 * Delete directly a person log entry in the database
	 * 
	 * @param personlog cayenne database object as input
	 * @since 1.0
	 */
	public void deletePersonLog(PersonLog pl);
	/**
	 * Delete directly a person log entry in the database
	 * 
	 * @param ID the log entry ID as integer
	 * @since 1.0
	 */
	public void deletePersonLog(Integer id);

	/**
	 * Select a person log entry by its ID
	 * 
	 * @param ID ID of log entry as selection criteria
	 * @return 1 database object
	 * @since 1.0
	 */
	public PersonLog selectPersonLog(Integer id);
	/**
	 * Select a person log entry by its ID
	 * 
	 * @param ID ID of log entry as selection criteria
	 * @return 1 model object
	 * @since 1.0
	 */
	public MPersonLog selectMPersonLog(Integer id);

	/**
	 * Select all person log entries
	 * 
	 * @return 0-n database object
	 * @since 1.0
	 */
	public List<PersonLog> getPersonLogs();
	/**
	 * Select all person log entries
	 * 
	 * @return 0-n model object
	 * @since 1.0
	 */
	public List<MPersonLog> getMPersonLogs();
}
