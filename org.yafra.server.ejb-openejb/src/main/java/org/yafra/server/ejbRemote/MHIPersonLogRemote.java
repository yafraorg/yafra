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
package org.yafra.server.ejbRemote;

import java.util.List;

import org.yafra.model.MPerson;
import org.yafra.model.MPersonLog;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIPersonLog
 * @version $Id: MHIPersonLogRemote.java,v 1.1 2009-12-12 21:41:32 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface MHIPersonLogRemote
{
	/**
	 * select the log entry for log PK ID
	 * @param id integer PK id of log entry
	 * @return log entry object
	 */
	public MPersonLog selectPersonLog(Integer id);
	/**
	 * get all log entries
	 * @return all model person log entries
	 */
	public List<MPersonLog> getPersonLogs();
	/**
	 * get all log entries of a given person
	 * @param mpl model person which serves as selection criteria
	 * @return all model person log entries of the person given as parameter
	 */
	public List<MPersonLog> getPersonLogs(MPerson mpl);
	/**
	 * insert a new log entry
	 * @param mpl the data to be inserted
	 */
	public void insertPersonLog(MPersonLog mpl);
	/**
	 * update the person log entry
	 * @param mpl model object to be updated
	 */
	public void updatePersonLog(MPersonLog mpl);
	/**
	 * delete a log entry
	 * @param id as integer id (or primary key) of log entry
	 */
	public void deletePersonLog(Integer id);
}
