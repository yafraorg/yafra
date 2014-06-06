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
 * @file psshared.h
 * @brief    header file for SHARED LIBRARIES AND DLLs
 */

#ifndef PSSHAREDDEFINED
#define PSSHAREDDEFINED

/* PS_SHAREDLIB is set to 1 if OSHARED is set */
/* PS_SHAREDLIB is set to 2 if OUSESHARED is set */
/* PS_SHAREDLIB is NOT set if either OSHARED nor OUSESHARED is set */

#if PS_SHAREDLIB == 1
# ifdef ps_win
#  define PS_DLLAPI __declspec(dllexport)
# else
#  define PS_DLLAPI
# endif
#elif PS_SHAREDLIB == 2
# ifdef ps_win
#  define PS_DLLAPI __declspec(dllimport)
# else
#  define PS_DLLAPI
# endif
#else
# define PS_DLLAPI
#endif

#endif
