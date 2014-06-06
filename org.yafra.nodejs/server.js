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
var restify = require('restify');
var mongoose = require('mongoose');
var yafrarest = require('./yafrarest.js');

/**
 *	Define the sample application.
 */
var SampleApp = function() {

	//	Scope.
	var self = this;


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
	 *	Initialize the server (express) and create the routes and register
	 *	the handlers.
	 */
	self.initializeServer = function() {
		self.app = restify.createServer({
			name : "myapp"
			});
	};


	/**
	 *	Initializes the sample application.
	 */
	self.initialize = function() {
		self.setupVariables();
		self.setupTerminationHandlers();

		// Create the express server and routes.
		self.initializeServer();

		self.app.use(restify.queryParser());
		self.app.use(restify.bodyParser());
		self.app.use(restify.CORS());

		self.app.get(/.*/, restify.serveStatic({
			'directory': 'static/',
			'default': 'index.html'
			}));
		yafrarest.init();
		self.app.get('/messages', yafrarest.restGetMsgs);
	};


	/**
	 *	Start the server (starts up the sample application).
	 */
	self.start = function() {
		//	Start the app on the specific interface (and port).
		self.app.listen(self.port ,self.ipaddress, function(){
			console.log('%s listening at %s ', self.app.name , self.app.url);
			});
	};

};	 /*	 Sample Application.  */



/**
 *	main():	 Main code.
 */
var yafraapp = new SampleApp();
yafraapp.initialize();
yafraapp.start();
