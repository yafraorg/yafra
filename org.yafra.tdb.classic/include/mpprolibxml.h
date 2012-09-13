/*D***********************************************************
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
 *
 * modul:     API - mp xml utilities                           
 *
 * @author:   admin
 **************************************************************/

/* xml */
/* includes of libXML */
#include <libxml/encoding.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>

int MPXMLopen(void);
int MPXMLcreate(unsigned char *, int);
int MPXMLstartObject(char *);
int MPXMLaddElementString(const char *, const char *);
int MPXMLendObject(void);
int MPXMLsend(int, char *, int);
int MPXMLclose(void);

int MPXMLread(int);
int MPXMLgetElement(const char *elementname, char *content);
int MPXMLgetAttr(const char *elementname, const char *attrname, char *content);
int MPXMLgetObject(const char *elementname, const char *attrname, char *content, char *attr);
int MPXMLsetElement(const char *elementname, const char *content);
int MPXMLsetAttr(const char *elementname, const char *attrname, const char *content);
int MPXMLsetObject(const char *elementname, const char *attrname, const char *content, const char *attr);
xmlNodePtr MPXMLlookupElement(xmlNodePtr , const char *elementname);
int MPXMLreadEnd(void);
unsigned char *MPXMLencConv(const char *, const char *);
