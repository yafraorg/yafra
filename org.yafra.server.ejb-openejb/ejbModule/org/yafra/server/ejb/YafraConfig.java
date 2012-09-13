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
 * @version $Id: YafraConfig.java,v 1.1 2009-12-02 12:44:09 mwn Exp $
 * @since 1.0
 */
package org.yafra.server.ejb;

import static javax.ejb.LockType.WRITE;
import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;
import javax.ejb.Lock;
import javax.ejb.Singleton;
import javax.ejb.Startup;

import org.apache.cayenne.access.DataContext;
import org.yafra.server.ejbRemote.YafraConfigRemote;
import org.yafra.utils.Logging;

/**
 * @author mwn
 * 
 */
@Singleton
@Lock(WRITE)
@Startup
public class YafraConfig implements YafraConfigRemote {
	private DataContext yafracontext = null;
	private Logging ejblog = null;
	private static final String dev = "stdout";

	// The @Startup method ensures that this method is
	// called when the application starts up.
	@PostConstruct
	public void applicationStartup() {
		ejblog = new Logging();
		ejblog.setDebugFlag(true);
		yafracontext = DataContext.createDataContext();
		ejblog.YafraDebug(
				"\norg.yafra.ejb - EJB3 yafrasession init done - starting ...",
				dev);
		ejblog.logInfo("org.yafra.ejb - EJB3 yafrasession init done - starting sessionid ");
		logMessage(" - EJB3 singleton app started");
	}

	@PreDestroy
	public void applicationShutdown() {
		// TODO fill up
	}

	@Override
	public DataContext getContext() {
		return yafracontext;
	}

	@Override
	public void logMessage(String message) {
		ejblog.YafraDebug(message, dev);
	}

	@Override
	public Logging getLoggin() {
		return ejblog;
	}
}
