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
 * @version $Id: IYafraMHPerson.java,v 1.2 2009-12-05 22:25:03 mwn Exp $
 * @since 1.0
 */
package org.yafra.tests.utils;

import org.yafra.utils.Logging;
import org.yafra.utils.WhichUser;

/**
 * Test class for org.yafra.utils
 * 
 * @author mwn
 */
public class TestUtils
{
	// vars for Logging facility
	private static Logging tstlog = null;
	private static final String dev = "stdout";

	public static void main(String[] args)
		{
		// test logging
		tstlog = new Logging();
		tstlog.setDebugFlag(true);
		tstlog.YafraDebug("\norg.yafra.tests - start off with first debug message", dev);
		tstlog.logInfo("test utils - log info record");
		tstlog.logDebug("test utils - log debug record");
		tstlog.logError("test utils - log error record with exception null", null);

		// test which user logged in on current system
		tstlog.YafraDebug("\n\norg.yafra.tests - test user logged in", dev);
		WhichUser UserID = new WhichUser();
		String username = UserID.getEnvUser();
		tstlog.YafraDebug("username from property = " + username, dev);
		username = UserID.getUser();
		tstlog.YafraDebug("username from NT/UNIX auth = " + username, dev);
		if (UserID.isIdentical())
			tstlog.YafraDebug("username is IDENTICAL", dev);
		else
			tstlog.YafraDebug("username is NOT identical ! CRITICAL", dev);
		
		// test which operating system
		tstlog.YafraDebug("\n\norg.yafra.tests - test current os", dev);
		String osname = System.getProperty("os.name");
		tstlog.YafraDebug("osname = " + osname, dev);
		if (org.yafra.utils.WhichOS.isWindows() == true)
			{
			tstlog.YafraDebug("is Windows", dev);
			}
		if (org.yafra.utils.WhichOS.isUnix() == true)
			{
			tstlog.YafraDebug("is Unix", dev);
			}

		// TODO selection of objects for selection/combos
		tstlog.YafraDebug("\n\norg.yafra.tests - test objselection", dev);

		// TODO unix timestamp
		tstlog.YafraDebug("\n\norg.yafra.tests - test unix timestamp conversion", dev);

		tstlog.YafraDebug("\n\norg.yafra.tests - ======== END =========", dev);
		}
}