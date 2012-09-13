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


import javax.xml.ws.Endpoint;

import org.yafra.server.ws.handlers.MHIYafraUser;

/**
 * Yafra standalone web service server</br>
 * @version $Id: $
 * @author <a href="mailto:yafra@yafra.org">Martin Weber</a>
 * @since 1.0
 */
public class YafraWSServer
{
	protected YafraWSServer() throws Exception {
		YafraWSConfig yafraglobal = YafraWSConfig.getInstance();
		Endpoint.publish("http://localhost:9000/yafraSession", new YafraSession());
		Endpoint.publish("http://localhost:9000/yafraUser", new MHIYafraUser());
	}

	public static void main(String args[]) throws Exception {
		System.out.println("Starting Server");
		new YafraWSServer();
		System.out.println("Server ready...");
	   while(true) {
	      try {
	      	Thread.sleep(5 * 60 * 1000);
	      	}
	      catch(InterruptedException e) {
	      	}
	    	}
		//System.out.println("Server exiting");
		//System.exit(0);
	}
}
