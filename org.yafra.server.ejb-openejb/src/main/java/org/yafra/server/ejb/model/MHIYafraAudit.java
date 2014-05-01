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
 */

package org.yafra.server.ejb.model;

import java.util.List;

import javax.ejb.EJB;
import javax.ejb.Remote;
import javax.ejb.Stateless;

import org.yafra.model.MYafraAudit;
import org.yafra.model.MYafraUser;
import org.yafra.modelhandler.MHYafraAudit;
import org.yafra.modelhandler.MHYafraUser;
import org.yafra.server.ejbRemote.MHIYafraAuditRemote;
import org.yafra.server.ejbRemote.YafraConfigRemote;

/**
 * model handler remote implementation</br>
 * @see org.yafra.interfaces.IYafraMHIYafraAudit
 * @version $Id: MHIYafraBusinessRole.java,v 1.3 2009-12-24 08:18:23 mwn Exp $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
@Stateless
@Remote(MHIYafraAuditRemote.class)
public class MHIYafraAudit implements MHIYafraAuditRemote {
	@EJB private YafraConfigRemote yafraglobals;	

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraAuditRemote#insertYafraAudit(org.yafra.model.MYafraAudit, org.yafra.model.MYafraUser)
	 */
	@Override
	public void insertYafraAudit(MYafraAudit mya, MYafraUser myu) {
		// create new database object
		MHYafraAudit mhya = new MHYafraAudit(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhya.insertMYafraAudit(mya);
		mhya.setAuditUser(mya, myu);
	}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraAuditRemote#deleteYafraAudit(java.lang.Integer)
	 */
	@Override
	public void deleteYafraAudit(Integer id) {
		MHYafraAudit mhya = new MHYafraAudit(yafraglobals.getContext(), yafraglobals.getLoggin());
		mhya.deleteYafraAudit(id);
	}

	/**
	 * @see org.yafra.server.ejbRemote.MHIYafraAuditRemote#getYafraAudit(org.yafra.model.MYafraUser)
	 */
	@Override
	public List<MYafraAudit> getYafraAudit(MYafraUser myu) {
		MHYafraAudit mhya = new MHYafraAudit(yafraglobals.getContext(), yafraglobals.getLoggin());
		if (myu != null)
			{
			MHYafraUser mhyu = new MHYafraUser(yafraglobals.getContext(), yafraglobals.getLoggin());
			return mhyu.getMUsersAudits(myu);
			}
		return mhya.getMYafraAudits();
	}
}
