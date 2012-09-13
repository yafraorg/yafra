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
 * @version $Id: YafraConfigRemote.java,v 1.1 2009-12-02 12:44:09 mwn Exp $
 * @since 1.0
 *
 * org.yafra session SAME JVM
 * this session is intended for non EJB environment (batch, web apps without EJB, ...)
 * against the networked session we can host here all the logging stuff and context stuff
 *
 * EJB3 remote interface for session
 */
package org.yafra.server.ejbRemote;

import org.apache.cayenne.access.DataContext;
import org.yafra.utils.Logging;

/**
 * @author mwn
 *
 */
public interface YafraConfigRemote {
	public DataContext getContext();
	public Logging getLoggin();
	public void logMessage(String message);
}
