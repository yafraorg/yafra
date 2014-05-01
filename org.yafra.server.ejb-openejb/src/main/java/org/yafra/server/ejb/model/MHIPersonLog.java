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
package org.yafra.server.ejb.model;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Remote;
import javax.ejb.Stateless;

import org.yafra.model.MPerson;
import org.yafra.model.MPersonLog;
import org.yafra.modelhandler.MHPersonLog;
import org.yafra.server.ejbRemote.MHIPersonLogRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIPersonLog
 * @version $Id: MHIPersonLog.java,v 1.2 2009-12-12 21:57:14 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIPersonLogRemote.class)
public class MHIPersonLog implements MHIPersonLogRemote
{
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.interfaces.IYafraMHIPersonLog#insertPersonLog(java.lang.String, java.lang.String, java.lang.String, java.util.Date, java.lang.String)
	 */
	@Override
	public void insertPersonLog(MPersonLog mpl)
		{
		// create new database object
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhpl.insertMPersonLog(mpl);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIPersonLog#updatePersonLog(org.yafra.model.MPersonLog)
	 */
	@Override
	public void updatePersonLog(MPersonLog mpl)
		{
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhpl.updatePersonLog(mpl);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonLogRemote#deletePersonLog(java.lang.Integer)
	 */
	@Override
	public void deletePersonLog(Integer id)
		{
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhpl.deletePersonLog(id);
		}

	/**
	 * @see org.yafra.server.ejbRemote.MHIPersonLogRemote#selectPersonLog(java.lang.Integer)
	 */
	@Override
	public MPersonLog selectPersonLog(Integer PKid)
		{
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhpl.selectMPersonLog(PKid);
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIPersonLog#getPersonLogs()
	 */
	@Override
	public List<MPersonLog> getPersonLogs()
		{
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		return mhpl.getMPersonLogs();
		}

	/**
	 * @see org.yafra.interfaces.IYafraMHIPersonLog#getPersonLogs(org.yafra.model.MPerson)
	 */
	@Override
	public List<MPersonLog> getPersonLogs(MPerson mp)
		{
		yafraglobals.getLoggin().logDebug(" - get logs of a person " + mp.getName());
		MHPersonLog mhpl = new MHPersonLog(yafraglobals.getContext(), yafraglobals.getLoggin());
		List<MPersonLog>mpl_list = mhpl.getMPersonLogs();
		return mpl_list;
		}
}
