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

// external dependencies (modules)
var mongoose = require('mongoose');

// module variables
var Message;
var db;
var Schema;

// init function - opens the db
var	init = function() {
	var connectionstring = 'mongodb://' + process.env.OPENSHIFT_MONGODB_DB_HOST + ':' + process.env.OPENSHIFT_MONGODB_DB_PORT;
	db = mongoose.connect(connectionstring);
	Schema = mongoose.Schema;
	// Create a schema for our data
	var MessageSchema = new Schema({
		message: String,
		date: Date
		});
	// Use the schema to register a model with MongoDb
	mongoose.model('Message', MessageSchema); 
	return;
	};
exports.init = init;
	
// REST GET all users
var restGetMsgs = function(req, res, next) {
	// Resitify currently has a bug which doesn't allow you to set default headers
	// This headers comply with CORS and allow us to server our response to any origin
	res.header("Access-Control-Allow-Origin", "*"); 
	res.header("Access-Control-Allow-Headers", "X-Requested-With");
	// .find() without any arguments, will return all results
	// the `-1` in .sort() means descending order
	Message = mongoose.model('Message'); 
	Message.find().sort('date', -1).execFind(function (arr,data) {
		res.send(data);
		});
		return;
	};
exports.restGetMsgs = restGetMsgs;

// REST POST new message
var restPostMsg = function(req, res, next) {
	res.header("Access-Control-Allow-Origin", "*");
	res.header("Access-Control-Allow-Headers", "X-Requested-With");
	// Create a new message model, fill it up and save it to Mongodb
	var message = new Message();
	message.message = req.params.message;
	message.date = new Date();
	message.save(function () {
		res.send(req.body);
		});
	return;
	};
exports.restPostMsg = restPostMsg;
