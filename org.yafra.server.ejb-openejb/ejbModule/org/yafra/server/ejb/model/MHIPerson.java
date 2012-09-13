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
 *  
 * @author <a href="mailto:yafra@yafra.org">yafra</a>
 * @version $Id: MHIPerson.java,v 1.3 2009-12-09 22:40:57 mwn Exp $
 * @since 1.0
 *
 * org.yafra session SAME JVM
 * this session is intended for non EJB environment (batch, web apps without EJB, ...)
 * against the networked session we can host here all the logging stuff and context stuff
 *
 * EJB session per client
 *
 * Model for db.PERSON
 */
package org.yafra.server.ejb.model;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Remote;
import javax.ejb.Stateless;

import org.yafra.model.MPerson;
import org.yafra.model.MPersonLog;
import org.yafra.modelhandler.MHPerson;
import org.yafra.server.ejbRemote.MHIPersonRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIPerson
 * @version $Id: MHIPerson.java,v 1.3 2009-12-09 22:40:57 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIPersonRemote.class)
public class MHIPerson implements MHIPersonRemote
{
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#insertPerson(org.yafra.model.MPerson)
	 */
	@Override
	public void insertPerson(MPerson mp)
		{
		// create new database object
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhp.insertPerson(mp);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#updatePerson(org.yafra.model.MPerson)
	 */
	@Override
	public void updatePerson(MPerson mp)
		{
		// get database object first and then change with input and update
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhp.updatePerson(mp);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#deletePerson(java.lang.Integer)
	 */
	@Override
	public void deletePerson(Integer id)
		{
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhp.deletePerson(id);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#selectPerson(java.lang.Integer)
	 */
	@Override
	public MPerson selectPerson(Integer id)
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		MPerson mp = mhp.selectMPerson(id);
		yafraglobals.getLoggin().logDebug(" - get users DONE");
		return mp;
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#selectPerson(java.lang.String)
	 */
	@Override
	public MPerson selectPerson(String name)
		{
		yafraglobals.getLoggin().logDebug(" - get a person by name");
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		MPerson mp = mhp.selectMPerson(name);
		yafraglobals.getLoggin().logDebug(" - get a person by name DONE");
		return mp;
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#getPersons()
	 */
	@Override
	public List<MPerson> getPersons()
		{
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		List<MPerson>mp_list = mhp.getMPersons();
		return mp_list;
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#getPersons(java.lang.String, java.lang.String, java.lang.String)
	 */
	@Override
	public List<MPerson> getPersons(String name, String type, String country)
		{
		// TODO replace this by a query on one or all of the parameters in order to reduce the amount of entries coming back
		// TODO create first a corresponding model handler in the core server
		yafraglobals.getLoggin().logDebug(" - get users - pass to MHYafraUser");
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		List<MPerson>mp_list = mhp.getMPersons();
		return mp_list;
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonRemote#getLogs(java.lang.Integer)
	 */
	@Override
	public List<MPersonLog> getLogs(Integer personid)
		{
		MHPerson mhp = new MHPerson(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhp.getMLogs(personid);
		}
}
