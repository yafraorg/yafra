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

import org.yafra.model.MPerson;
import org.yafra.model.MPersonLog;
import org.yafra.orm.Person;
import org.yafra.orm.PersonLog;

/**
 * Interface model handler person
 * @version $Id: IYafraMHPerson.java,v 1.4 2009-12-20 20:22:57 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public interface IYafraMHPerson
{

	/**
	 * Insert a new user into the database
	 * 
	 * @param MPerson model object as input
	 * @return the new database object
	 * @since 1.0
	 */
	public Person insertPerson(MPerson p);
	/**
	 * Insert a new user into the database without any return - used within DTO
	 * 
	 * @param MPerson model object as input
	 * @since 1.0
	 */
	public void insertMPerson(MPerson p);

	/**
	 * Update directly a person object in the database
	 * 
	 * @param Person cayenne database object as input
	 * @since 1.0
	 */
	public void updatePerson(Person p);
	/**
	 * Update person in the database, makes a lookup first - used within DTO
	 * 
	 * @param MPerson model object as input
	 * @since 1.0
	 */
	public void updatePerson(MPerson p);

	/**
	 * Delete directly a person in the database
	 * 
	 * @param Person cayenne database object as input
	 * @since 1.0
	 */
	public void deletePerson(Person p);
	/**
	 * Delete a person in the database, makes a lookup first - used within DTO
	 * 
	 * @param ID integer id as input
	 * @since 1.0
	 */
	public void deletePerson(Integer id);

	/**
	 * Select one person
	 * 
	 * @param Name String as input
	 * @return one database object
	 * @since 1.0
	 */
	public Person selectPerson(String name);
	/**
	 * Select one person
	 * 
	 * @param ID integer id as input
	 * @return one database object
	 * @since 1.0
	 */
	public Person selectPerson(Integer id);
	/**
	 * Select one person
	 * 
	 * @param Name String as input
	 * @return one model object
	 * @since 1.0
	 */
	public MPerson selectMPerson(String name);
	/**
	 * Select one person
	 * 
	 * @param ID integer id as input
	 * @return one model object
	 * @since 1.0
	 */
	public MPerson selectMPerson(Integer id);
	/**
	 * Select all persons
	 * 
	 * @return 0-n database objects
	 * @since 1.0
	 */
	public List<Person> getPersons();
	/**
	 * Select all persons
	 * 
	 * @param name selection criteria name
	 * @param typ selection criteria person type
	 * @param country selection criteria country code
	 * @return 0-n database objects
	 * @since 1.0
	 */
	public List<Person> getPersons(String name, String type, String country);
	/**
	 * Select all persons
	 * 
	 * @return 0-n model objects
	 * @since 1.0
	 */
	public List<MPerson> getMPersons();
	/**
	 * Select all persons
	 * 
	 * @param name selection criteria name
	 * @param typ selection criteria person type
	 * @param country selection criteria country code
	 * @return 0-n model objects
	 * @since 1.0
	 */
	public List<MPerson> getMPersons(String name, String type, String country);
	
	/**
	 * Select all log entries for a person identified by its ID
	 * 
	 * @param ID integer ID of person
	 * @return 0-n model objects (the logs)
	 * @since 1.0
	 */
	public List<MPersonLog> getMLogs(Integer id);
	/**
	 * Select all log entries for a person identified by an ID
	 * 
	 * @param ID integer ID of person
	 * @return 0-n database objects (the logs) of the person given
	 * @since 1.0
	 */
	public List<PersonLog> getLogs(Integer id);
	/**
	 * Select all log entries for a person identified by a person db object
	 * 
	 * @param person database object of a person
	 * @return 0-n database objects (the logs) of the person given
	 * @since 1.0
	 */
	public List<PersonLog> getLogs(Person p);
	
	/**
	 * Add a log entry for a person - the log entry must be created before
	 * 
	 * @param person a valid person
	 * @param personlog a valid personlog which will be associated to the person
	 * @since 1.0
	 */
	public void addLog(Person p, PersonLog plog);
	/**
	 * Add a log entry for a person - the log entry must be created before
	 * 
	 * @param person a valid person
	 * @param personlog a valid personlog which will be associated to the person
	 * @since 1.0
	 */
	public void addLog(MPerson mp, MPersonLog mplog);
	/**
	 * Remove a log entry for a person - the log entry must be selected before
	 * 
	 * @param person a valid person
	 * @param personlog a valid personlog which will be removed - the log entry itself will not be removed - please delete it afterwards or leave it orphan
	 * @since 1.0
	 */
	public void removeLog(Person p, PersonLog plog);
	/**
	 * Remove a log entry for a person - the log entry must be selected before
	 * 
	 * @param person a valid person
	 * @param personlog a valid personlog which will be removed - the log entry itself will not be removed - please delete it afterwards or leave it orphan
	 * @since 1.0
	 */
	public void removeLog(MPerson mp, MPersonLog mplog);
}
