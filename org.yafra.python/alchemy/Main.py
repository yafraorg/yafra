#!/usr/bin/python
'''
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.

Created on 02.06.2012
Project yafra.org - org.yafra.padmin
Python administration tool based on SQLAlchemy
@author: mwn
'''

import sys

import pymysql
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
import model

print("start")

if len(sys.argv) > 1:
    server = sys.argv[1]
else:
    server = "localhost"

engine = create_engine('mysql+pymysql://yafraadmin:yafra@webdev/yafra', echo=True)
Session = sessionmaker(bind=engine)
session = Session()
for instance in session.query(model.Person).order_by(model.Person.name):
    print(instance.name)

print("stop")
#raw_input()
