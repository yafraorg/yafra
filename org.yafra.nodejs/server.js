#!/bin/env node
/*
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
'use strict';

//	OpenShift sample Node application
var mongoose = require('mongoose');
var express = require("express");
var yafrarest = require('./yafrarest.js');

/**
 *	Define the sample application.
 */
var YafraApp = function() {

	//	Scope.
	var self = this;
    var app;


	/*	================================================================  */
	/*	Helper functions.												  */
	/*	================================================================  */

	/**
	 *	Set up server IP address and port # using env variables/defaults.
	 */
	self.setupVariables = function() {
		//	Set the environment variables we need.
		self.ipaddress = process.env.OPENSHIFT_NODEJS_IP;
		self.port	   = process.env.OPENSHIFT_NODEJS_PORT || 8080;

		if (typeof self.ipaddress === "undefined") {
			//	Log errors on OpenShift but continue w/ 127.0.0.1 - this
			//	allows us to run/test the app locally.
			console.warn('No OPENSHIFT_NODEJS_IP var, using 127.0.0.1');
			self.ipaddress = "127.0.0.1";
            self.port = 8081;
		};
	};

	/**
	 *	terminator === the termination handler
	 *	Terminate server on receipt of the specified signal.
	 *	@param {string} sig	 Signal to terminate on.
	 */
	self.terminator = function(sig){
		if (typeof sig === "string") {
			console.log('%s: Received %s - terminating sample app ...', Date(Date.now()), sig);
			process.exit(1);
			}
		console.log('%s: Node server stopped.', Date(Date.now()) );
	};


	/**
	 *	Setup termination handlers (for exit and a list of signals).
	 */
	self.setupTerminationHandlers = function(){
		//	Process on exit and signals.
		process.on('exit', function() { self.terminator(); });

		// Removed 'SIGPIPE' from the list - bugz 852598.
		['SIGHUP', 'SIGINT', 'SIGQUIT', 'SIGILL', 'SIGTRAP', 'SIGABRT',
		 'SIGBUS', 'SIGFPE', 'SIGUSR1', 'SIGSEGV', 'SIGUSR2', 'SIGTERM'
		].forEach(function(element, index, array) {
			process.on(element, function() { self.terminator(element); });
		});
	};


	/**
	 *	Initializes the sample application.
	 */
	self.initialize = function() {
        console.log('yafra - %s: Node server start.', Date(Date.now()) );
		self.setupVariables();
        console.log('yafra - setup var done' );
		self.setupTerminationHandlers();
        console.log('yafra - setup terminate handlers done' );

		// Create the express server and routes.
        self.app  = express();
        console.log('yafra - express init done' );

        //This uses the Connect frameworks body parser to parse the body of the post request
        /*self.app.configure(function () {
            self.app.use(express.bodyParser());
            self.app.use(express.methodOverride());
            self.app.use(express.errorHandler({ dumpExceptions: true, showStack: true }));
        });
*/

        //define all the url mappings
        yafrarest.init();
        console.log('yafra - yafrarest init done' );
        self.app.get('/yafra', yafrarest.showindex);
        console.log('yafra - express /yafra get done' );
        self.app.get('/', function(req, res){
            res.send('Hello World');
        });
        console.log('yafra - express / done' );
    };


	/**
	 *	Start the server (starts up the sample application).
	 */
	self.start = function() {
		//	Start the app on the specific interface (and port).
        console.log('yafra - start' );
		self.app.listen(self.port ,self.ipaddress, function(){
			console.log('%s listening at %s ', self.app.name , self.app.url);
			});
	};

};	 /*	 Sample Application.  */



/**
 *	main():	 Main code.
 */
var yafraapp = new YafraApp();
yafraapp.initialize();
yafraapp.start();
