/**************************************************************/
/* Modul:     XML handling                                    */
/*                                                            */
/* Copyright: yafra.org, Switzerland                          */
/**************************************************************/

/*
 * TDB XML message structure
 *
MPXMLopen()

MPXMLcreate()
<XML ....>
<TDB>

<HEADER>
<TRX>select</TRX>
<LANG>1</LANG>
</HEADER>

<BODY>
MPXMLstartObject()
<DATA>
MPXMLaddElementString()
<NAME>Muster</NAME>
MPXMLendObject()
</DATA>
MPXMLsend()
</BODY>

<FOOTER>
<STATUS>xxx</STATUS>
<MESSAGE>OK</MESSAGE>
</FOOTER>

</TDB>

MPXMLclose()
------------------------------------------------------------------------
mpgui login request with user pwd host dbschema port
mpdbi global data

mppgui trx
mpdbi result one item or list or result

mpgui logoff
mpdbi NO MSG - exit
-------------------------------------------------------------------------
table id (string) like country lang
obj id (int) like 1
bez and text always with string int

trx select land
<BODY>
<COUNTRY_ID>1</COUNTRY_ID>
<COUNTRY>Schweiz</COUNTRY>
*/

static char rcsid[]="$Header: 1.3$";
static char cvsrev[]="$Revision: 1.3 $";

#include <stdio.h>
#include <string.h>
#include <pssys.h>
#include <mpcomm.h>
#include <mpmsg.h>
#include <mpstrlen.h>
#include <mpdef.h>
#include <mpprolib.h>
#include <mpprolibxml.h>

/* includes of libXML */
#include <libxml/encoding.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>

#define XML_LOGNAME "xml"
#define XML_ENCODING "ISO-8859-1"
// #define XML_ENCODING "UTF-8"

/* global variables */
xmlTextWriterPtr xml_writer;
xmlBufferPtr xml_buf;
xmlDoc *xml_doc;
extern FILE *MP_DBIDEBUGFILE;
extern COMMOBJ comm;
extern int DebugFlag;
char xml_encoding[100];
static int found;


/**************************************************************
 * Function:  MPXMLopen - open XML, only call once - at the beginning
 *
 * Return:    error code
 **************************************************************/
int MPXMLopen()
{
	/* init libXML */
	LIBXML_TEST_VERSION
	xmlInitParser();
	(void)strcpy(xml_encoding, XML_ENCODING);
	return(MPOK);
}

/**************************************************************
 * Function:  MPXMLclose - close XML, only call once - at the end
 *
 * Return:    error code
 **************************************************************/
int MPXMLclose()
{
	xmlCleanupParser();
	xmlMemoryDump();
	return(MPOK);
}


/**************************************************************
 * Function:  MPXMLread - read received buffer from socket
 *            and start to read the XML file
 *
 * Return:    error code
 **************************************************************/
int MPXMLread(int memchunk)
{
	int cret = MPOK;
	char *Pbuf;
	char tmp[_CHAR256];
	/* init xml_doc, important that MPXMLreadEnd() was called before */
	xml_doc = NULL;

	/* READ setup information and make connect and read profile data */
	// parse login request feedback
	(void)MPcomm(RECV, (long)memchunk);
	Pbuf = comm.buffer;
	xml_doc = xmlParseMemory(Pbuf, comm.datalen);
	if (xml_doc == NULL)
		cret = MPERROR;
	if (cret == MPOK)
		cret = MPXMLgetElement("STATUS", &tmp);
	if (cret == MPOK)
		cret = atoi(&tmp); // get the xml status from the sender
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "status of read %d and received xml message is:\n%s", cret, Pbuf);
	return(cret);
}

/**************************************************************
 * Function:  MPXMLgetElement get content as string from one <ELEMENT>xx</ELEMENT>
 *
 * Parameter: doc      xml doc structure
 *            elementname XML element name as string
 *            content  content of element as string
 * Return:    return code
 **************************************************************/
int MPXMLgetElement(const char *elementname, char *content)
{
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;
	xmlChar *nodecnt;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(MPERROR);
	nodecnt = xmlNodeGetContent(work_node);
	(void)strcpy(content, nodecnt);
	xmlFree(nodecnt);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "got element %s with content %s", elementname, content);
	return(MPOK);
}

/**************************************************************
 * Function:  MPXMLgetAttr
 *
 * Parameter: doc     XML doc pointer
 *            elementname name of XML element
 *
 * Return:    return code
 **************************************************************/
int MPXMLgetAttr(const char *elementname, const char *attrname, char *content)
{
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;
	xmlChar *work_attr = NULL;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(MPERROR);
	work_attr = xmlGetProp(work_node, attrname);
	(void)strcpy(content, work_attr);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "got attribute %s %s with content %s", elementname, attrname, content);
	return(MPOK);
}

int MPXMLgetObject(const char *elementname, const char *attrname, char *content, char *attr)
{
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;
	xmlChar *work_attr = NULL;
	xmlChar *nodecnt;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(MPERROR);
	nodecnt = xmlNodeGetContent(work_node);
	(void)strcpy(content, nodecnt);
	xmlFree(nodecnt);
	work_attr = xmlGetProp(work_node, attrname);
	(void)strcpy(attr, work_attr);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "got element %s with content %s and attribute %s with content %s", elementname, content, attrname, attr);
	return(MPOK);
}

int MPXMLsetElement(const char *elementname, const char *content)
{
	int cret = MPOK;
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(-1);
	xmlNodeSetContent(work_node, content);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "created new element %s with content %s", elementname, content);
	return(cret);
}

int MPXMLsetAttr(const char *elementname, const char *attrname, const char *content)
{
	int cret = MPOK;
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;
	xmlAttrPtr work_attr = NULL;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(-1);
	work_attr = xmlSetProp(work_node, attrname, content);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "set attribute %s to element %s with content %s", attrname, elementname, content);
	return(cret);
}

int MPXMLsetObject(const char *elementname, const char *attrname, const char *content, const char *attr)
{
	int cret = MPOK;
	xmlNodePtr root_node = NULL;
	xmlNodePtr work_node = NULL;
	xmlAttrPtr work_attr = NULL;

	/*Get the root element node TRAVELDB */
	root_node = xmlDocGetRootElement(xml_doc);
	found = FALSE;
	work_node = MPXMLlookupElement(root_node, elementname);
	if (work_node == NULL || found == FALSE)
		return(-1);
	xmlNodeSetContent(work_node, content);
	work_attr = xmlSetProp(work_node, attrname, attr);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "set element %s with content %s and attribute %s with content %s", elementname, content, attrname, attr);
	return(cret);
}

xmlNode *MPXMLlookupElement(xmlNodePtr root_node, const char *elementname)
{
	xmlNodePtr cur_node = NULL;
	xmlNodePtr found_node = NULL;

	for (cur_node = root_node; cur_node; cur_node = cur_node->next)
		{
		if (cur_node->type == XML_ELEMENT_NODE && !(strcmp(cur_node->name, elementname)))
			{
			found = TRUE;
			return(cur_node);
			}
		if (found == FALSE)
			found_node = MPXMLlookupElement(cur_node->children, elementname);
		}
	return(found_node);
}

int MPXMLreadEnd()
{
	xmlFreeDoc(xml_doc);
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "end of read - freeing xml_doc");
	return(MPOK);
}

/**************************************************************
 * Function:  MPXMLcreate - create tdb xml message
 *
 * Parameter: mp_trxid    transcation code to be put into the header part
 *            language    language code - indicates the language of the message content
 *
 * Return:    return code
 **************************************************************/
int MPXMLcreate(unsigned char *mp_trxid, int language)
{
	int cret = MPOK;
	int rc;

	xmlChar *tmp;

	/* Create a new XML xml_buffer, to which the XML document will be written */
	xml_buf = xmlBufferCreate();
	if (xml_buf == NULL)
		cret = MPERROR;
	/* Create a new XmlWriter for memory, with no compression. */
	if (cret == MPOK)
		xml_writer = xmlNewTextWriterMemory(xml_buf, 0);
	if (xml_writer == NULL)
		cret=MPERROR;
	/* Start the document with some attributes */
	if (cret == MPOK)
		rc = xmlTextWriterStartDocument(xml_writer, NULL, xml_encoding, NULL);
	if (rc < 0)
		cret=MPERROR;

/* <TDB> */
	if (cret == MPOK)
		rc = xmlTextWriterStartElement(xml_writer, BAD_CAST "TDB");
	if (rc < 0)
		cret=MPERROR;
	/* Add an attribute with name "version" and value "1.0" */
	if (cret == MPOK)
		rc = xmlTextWriterWriteAttribute(xml_writer, BAD_CAST "version", BAD_CAST cvsrev);
	if (rc < 0)
		cret=MPERROR;
	/* Write a comment as child of TDB */
	// tmp = ConvertInput("<äöü>", MY_ENCODING);
	// rc = xmlTextWriterWriteFormatComment(xml_writer, "This is another comment with special chars: %s", tmp);
	// if (tmp != NULL) xmlFree(tmp);


/* <HEADER> */
	if (cret == MPOK)
		rc = xmlTextWriterStartElement(xml_writer, BAD_CAST "HEADER");
	if (rc < 0)
		cret=MPERROR;
	/* Write an element named "TRX" */
	if (cret == MPOK)
		rc = xmlTextWriterWriteFormatElement(xml_writer, BAD_CAST "TRX", "%s", mp_trxid);
	if (rc < 0)
		cret=MPERROR;
	/* Write an element named "LANG" */
	if (cret == MPOK)
		rc = xmlTextWriterWriteFormatElement(xml_writer, BAD_CAST "LANG", "%d", language);
	if (rc < 0)
		cret=MPERROR;
/* END <HEADER> */
	if (cret == MPOK)
		rc = xmlTextWriterEndElement(xml_writer);
	if (rc < 0)
		cret=MPERROR;

/* <BODY */
	// handle different trx -> select, selectone, delete, update, insert, ....
	if (cret == MPOK)
		rc = xmlTextWriterStartElement(xml_writer, BAD_CAST "BODY");
	if (rc < 0)
		cret=MPERROR;

	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "generated XML message up to BODY with status %d", cret);
	return(cret);
}

/**************************************************************
 * Function:  MPXMLstartObject - start xml element
 *
 * Parameter: object  name of the element as string
 *
 * Return:    return code
 **************************************************************/
int MPXMLstartObject(char *object)
{
	int cret = MPOK;
	cret = xmlTextWriterStartElement(xml_writer, BAD_CAST object);
	if (cret < 0)
		cret = MPERROR;
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "start xml element (startObject) %s with cret %d", object, cret);
	return (cret);
}

/**************************************************************
 * Function:  MPXMLaddElementString - add a variable as xml element
 *
 * Parameter: element  name of element as string
 *            code     content of element as string
 *
 * Return:    return code
 **************************************************************/
int MPXMLaddElementString(const char *element, const char *code)
{
	int cret = 0;
	cret = xmlTextWriterWriteFormatElement(xml_writer, BAD_CAST element, "%s", code);
	if (cret < 0)
		cret = MPERROR;
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "add xml element (addElementString) %s with content %s and with cret %d", element, code, cret);
	return (cret);
}

/**************************************************************
 * Function:  MPXMLendObject - end xml element
 *
 * Return:    return code
 **************************************************************/
int MPXMLendObject()
{
	int cret = MPOK;
	int rc;
	rc = xmlTextWriterEndElement(xml_writer);
	if (rc < 0)
		cret = MPERROR;
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "end xml element with cret %d", cret);
	return (cret);
}

/**************************************************************
 * Function:  MPXMLsend - send tdb xml message
 *
 * Parameter: status      status to be submitted with the message
 *
 * Return:    return code
 **************************************************************/
int MPXMLsend(int status, char *message, int memchunk)
{
	int cret = MPOK;
	int rc = 0;
/* END <BODY */
	rc = xmlTextWriterEndElement(xml_writer);
	if (rc < 0)
		cret = MPERROR;

/* <FOOTER> */
	if (cret == MPOK)
		rc = xmlTextWriterStartElement(xml_writer, BAD_CAST "FOOTER");
	if (rc < 0)
		cret = MPERROR;
	/* Set status to return */
	if (cret == MPOK)
		rc = xmlTextWriterWriteFormatElement(xml_writer,	BAD_CAST "STATUS", "%d", status);
	if (rc < 0)
		cret = MPERROR;
	/* Set status message to return */
	if (cret == MPOK)
		rc = xmlTextWriterWriteFormatElement(xml_writer,	BAD_CAST "MESSAGE", "%s", message);
	if (rc < 0)
		cret = MPERROR;
/* END <FOOTER> */
	if (cret == MPOK)
		rc = xmlTextWriterEndElement(xml_writer);
	if (rc < 0)
		cret = MPERROR;


	/* Here we could close the elements but we simply call xmlTextWriterEndDocument,
	* which will do all the work. */
	if (cret == MPOK)
		rc = xmlTextWriterEndDocument(xml_writer);
	if (rc < 0)
		cret = MPERROR;
	xmlFreeTextWriter(xml_writer);


	/* send XML message and free up XML buf */
	(void)memcpy((void *)comm.buffer, (void *)xml_buf->content, xml_buf->use);
	comm.datalen = xml_buf->use;
	xmlBufferFree(xml_buf);
	COMMSTAT = MESSAGEOK;
	(void)MPcomm(SEND, (long)memchunk);

	/* log xml_buffer if in debug mode */
	if (DebugFlag)
		PSSYSdebug(NULL, XML_LOGNAME, "send with status %d and xml message:\n%s", cret, comm.buffer);

	return MPOK;
}


/**************************************************************
 * Function:  MPXMLencConv
 *
 * Parameter: text     string text to convert
 *            encoding language encoding to convert to
 * Return:    converted string text or NULL in case of an error
 **************************************************************/
unsigned char *MPXMLencConv(const char *in, const char *encoding)
{
	xmlChar *out;
	int ret;
	int size;
	int out_size;
	int temp;
	xmlCharEncodingHandlerPtr handler;

	if (in == NULL)
		return NULL;

	handler = xmlFindCharEncodingHandler(encoding);
	if (!handler)
		return NULL;

	size = (int) strlen(in) + 1;
	out_size = size * 2 - 1;
	out = (unsigned char *) xmlMalloc((size_t) out_size);
	if (out != NULL)
		{
		temp = size - 1;
		ret = handler->input(out, &out_size, (const xmlChar *) in, &temp);
		if (ret || temp - size + 1)
			{
			xmlFree(out);
			out = NULL;
			}
		else
			{
			out = (unsigned char *) xmlRealloc(out, out_size + 1);
			out[out_size] = (xmlChar)NULL;
			}
		}

	return((unsigned char *)out);
}
