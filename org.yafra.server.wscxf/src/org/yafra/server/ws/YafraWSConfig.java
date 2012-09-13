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
package org.yafra.server.ws;

import org.apache.cayenne.access.DataContext;
import org.yafra.utils.Logging;

/**
 * YafraBusinessRole database object</br>
 * Attributes:
 * <ul>
 * <li>name (unique) - String
 * <li>description - String
 * <li>flag - access flags as String
 * </ul>
 * @version $Id: $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class YafraWSConfig
{
    private static YafraWSConfig instance = new YafraWSConfig();
    private DataContext yafracontext;
    private Logging log = null;
    private final String dev = "stdout";

    /**
     * Default-Konstruktor, der nicht au�erhalb dieser Klasse
     * aufgerufen werden kann
     */
    private YafraWSConfig() {
	  	log = new Logging();
	 	log.setDebugFlag(true);
		yafracontext = DataContext.createDataContext();
		log.YafraDebug("\norg.yafra.ejb - CXF yafrasession init done - starting ...", dev);
		log.logInfo("org.yafra.ejb - CXF yafrasession init done - starting sessionid ");
		logMessage(" - CXF singleton app started");
    }

    /**
     * Statische Methode, liefert die einzige Instanz dieser
     * Klasse zur�ck
     */

	public static YafraWSConfig getInstance() {
    	return instance;
    }

	public DataContext getContext()
    	{
    	return yafracontext;
    	}

	public Logging getLoggin()
 		{
 		return log;
 		} 

	public void logMessage(String message)
		{
		log.YafraDebug(message, dev);
		}
}
