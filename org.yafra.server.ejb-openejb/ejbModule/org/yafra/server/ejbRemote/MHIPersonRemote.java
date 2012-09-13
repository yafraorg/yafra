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
 * 
 * @see org.yafra.interfaces.IYafraMHIPerson
 * @version $Id: MHIPersonRemote.java,v 1.3 2009-12-09 22:41:11 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface MHIPersonRemote {
	/**
	 * select a person by its name
	 * @param name the name of a person as criteria
	 * @return one model object as found person
	 */
	public MPerson selectPerson(String name);

	/**
	 * select a person by its id
	 * @param id of a person as criteria
	 * @return one model object as found person
	 */
	public MPerson selectPerson(Integer id);

	// TODO create a get all with pages and not all entries in one
	
	/**
	 * get all persons in the database
	 * @return 0-n model objects
	 */
	public List<MPerson> getPersons();

	/**
	 * get all persons in the database which meet either a name, a type or a country
	 * @param name the name of a person as criteria
	 * @param type the type of a person as criteria
	 * @param country the country of a person as criteria
	 * @return 0-n model objects
	 */
	public List<MPerson> getPersons(String name, String type, String country);

	/**
	 * insert a person
	 * @param person model object to be inserted
	 */
	public void insertPerson(MPerson p);

	/**
	 * update a person
	 * @param person model object to be inserted
	 */
	public void updatePerson(MPerson p);

	/**
	 * delete person with ID
	 * @param id person id to be deleted
	 */
	public void deletePerson(Integer id);

	/**
	 * get all logs for a person
	 * @param id person id to get all logs of
	 * @return 0-n model objects
	 */
	public List<MPersonLog> getLogs(Integer id);
}
