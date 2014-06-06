/*
 *  Copyright 2002 yafra.org
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*!
 * @file psmodul.h
 * @brief    global include for the security/modul library
 * handles a module to deal with license keys / tongles. PSmodul Interface to protect Yafra.org products
 */

#ifndef _PSMODUL_H
#define _PSMODUL_H


/* Application code values for PSmodul (integer in range 0 to 55)... */

#define PSCMDSRV		1		/*!< Program command server */

#define MPDBI			10		/* tdb */
#define MPGUI			11
#define MPNET			12

#define NETCAD			20		/* cad */
#define NETCALC			21
#define MATCALC			22
#define PAXCALC			23
#define LINPLAN			24

/* return values */
#define PSMODUL_NOTALLOWED  0
#define PSMODUL_ALLOWED     1
#define PSMODUL_ERROR       2

/*! @brief check on the allowance if this program/module can be executed as a valid license is given */
int PSmodul(int, char *, int);

#endif
