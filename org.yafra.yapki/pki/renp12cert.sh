#!/bin/sh
#-------------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#
# (c) yafra.org, 2002, Switzerland
#
# function:	renew PKCS#12 certificate, your former private key remains the same
#
# argument: hex id of cert and start and end date
#
# CVS tag:   $Name:  $
# author:    $Author: mwn $
# revision:  $Revision: 16 $
#-------------------------------------------------------------------------------

# arguments are: 1: hex no of cert request to renew
#                2/3: start and end date 112233445566Z
if [ -z "$3" ]; then
        echo Please specify cert hex_id for renewal and start and stop date
	echo as YYMMDDHHMMSSZ where Z is Z and not to be replaced!
        exit
fi

# renew pem request from database (see index which to renew)
openssl ca -config openssl.cnf -in nissle/certs/cert-id$1.req -out newcert.pem -startdate $2 -enddate $3 -policy policy_anything 

# extract private key from p12 cert
openssl pkcs12 -in cert-id$1.p12 -out cert-id$1.key -nocerts

# export new cert to p12 with former private key
openssl pkcs12 -export -in newcert.pem -inkey cert-id$1.key -certfile nissle/cacert.pem -name "Martin Weber Nissle" -out newcert.p12
