/*************************************************************/
/*                                                           */
/* File:        PShtmlutil.c                                 */
/*                                                           */
/* Modul:       HTML utilities                               */
/*                                                           */
/* Description: Utility functions to write HTML tags         */
/*                                                           */
/* Copyright: Yafra.org    */
/*                                                           */
/*************************************************************/

/* RCS static ID */
static char rcsid[]="$Header: /yafraorg/cvsroot/foundation/ansic/libs/pssys/source/html.c,v 1.1.1.1 2002-10-26 20:49:54 mwn Exp $";

#include <stdio.h>
#include <pssys.h>

void PSSYShtmlInitText(char *aTitle)
{
	/*------------------------------------------*/
	/* HtmlInitText - write HTML heading        */
	/* aTitle       - Title of the form         */
	/*------------------------------------------*/

	printf("Content-type: text/html%c%c",10,10);
	printf("<HTML>%c",10);
 	printf("<HEAD>%c",10);
 	printf("<TITLE>%s</TITLE>%c",aTitle,10);
	printf("</HEAD>%c",10);
 	printf("<BODY>%c",10);
	fflush(stdout);
}


void PSSYShtmlHeadingText(int aLevel, char *aHeading)
{
	/*------------------------------------------*/
	/* HtmlHeadingText - write a heading        */
	/* aLevel          - level of heading       */
	/* aHeading        - heading text           */
	/*------------------------------------------*/
	
	printf("<H%d>%s</H%d>",aLevel,aHeading,aLevel);
	
}


void PSSYShtmlParagraph(void)
{
	/*------------------------------------------*/
	/* HtmlParagraph - write a paragraph tag    */
	/*------------------------------------------*/
	
	printf("<P>%c",10);
	
}


void PSSYShtmlLinkRef(char *aHref, char *aText)
{
	/*------------------------------------------*/
	/* HtmlLink - write a Link                  */
	/* aHref    - File to load when link is     */ 
	/*            selected                      */
	/* aText    - Text that will be highlighted */
	/*------------------------------------------*/
	
	printf("<A HREF=\"%s\">%s</A>",aHref, aText);
	
}


void PSSYShtmlAnchor(char *anAnchor, char *aText)
{
	/*------------------------------------------*/
	/* HtmlAnchor - write an anchor             */
	/* anAnchor   - Anchor name to link to      */
	/* aText      - Text that will be at the    */
	/*              top of the screen           */
	/*------------------------------------------*/
	
	printf("<A NAME=\"%s\">%s</A>%c",anAnchor,aText,10);
	
}


void PSSYShtmlImage(char *aSrc)
{
	/*------------------------------------------*/
	/* HtmlImage - inserts an inline image into */
	/*             the document                 */
	/* aSrc      - filename of the image to     */
	/*             include                      */
	/*------------------------------------------*/
	
	printf("<IMG SRC=\"%s\">", aSrc);
	
}


void PSSYShtmlImageBottom(char *aSrc)
{
	/*------------------------------------------*/
	/* HtmlImage - inserts an inline image into */
	/*             the document                 */
	/* aSrc      - filename of the image to     */
	/*             include                      */
	/*------------------------------------------*/
	
	printf("<IMG SRC=\"%s\" ALIGN=BOTTOM>", aSrc);
	
}


void PSSYShtmlImageMiddle(char *aSrc)
{
	/*------------------------------------------*/
	/* HtmlImage - inserts an inline image into */
	/*             the document                 */
	/* aSrc      - filename of the image to     */
	/*             include                      */
	/*------------------------------------------*/
	
	printf("<IMG SRC=\"%s\" ALIGN=MIDDLE>", aSrc);
}


void PSSYShtmlImageTop(char *aSrc)
{
	/*------------------------------------------*/
	/* HtmlImage - inserts an inline image into */
	/*             the document                 */
	/* aSrc      - filename of the image to     */
	/*             include                      */
	/*------------------------------------------*/
	
	printf("<IMG SRC=\"%s\" ALIGN=TOP>", aSrc);
	
}


void PSSYShtmlBeginOList()
{
	/*------------------------------------------*/
	/* HtmlBeginOList - begin ordered list      */
	/*------------------------------------------*/
	
	printf("<OL>%c",10);
	
}


void PSSYShtmlEndOList()
{
	/*------------------------------------------*/
	/* HtmlEndOList - end of ordered list       */
	/*------------------------------------------*/
	
	printf("</OL>%c",10);
	
}


void PSSYShtmlBeginUList()
{
	/*------------------------------------------*/
	/* HtmlBeginUList - begin unordered list    */
	/*------------------------------------------*/
	
	printf("<UL>%c",10);
	
} /* HtmlBeginUlist */


void PSSYShtmlEndUList()
{
	/*------------------------------------------*/
	/* HtmlEndUList - end of unordered list     */
	/*------------------------------------------*/
	
	printf("</UL>%c",10);
	
} /* HtmlEndUList */


void PSSYShtmlBeginMenuList()
{
	/*------------------------------------------*/
	/* HtmlBeginMenuList - begin menu list      */
	/*------------------------------------------*/
	
	printf("<MENU>%c",10);
	
} /* HtmlBeginMenulist */


void PSSYShtmlEndMenuList()
{
	/*------------------------------------------*/
	/* HtmlEndMenuList - end of menu list       */
	/*------------------------------------------*/
	
	printf("</MENU>%c",10);
	
} /* HtmlEndMenuList */


void PSSYShtmlBeginDirList()
{
	/*------------------------------------------*/
	/* HtmlBeginDirList - begin directory list  */
	/*------------------------------------------*/
	
	printf("<DIR>%c",10);
	
} /* HtmlBeginDirlist */


void PSSYShtmlEndDirList()
{
	/*------------------------------------------*/
	/* HtmlEndDirList - end of directory list   */
	/*------------------------------------------*/
	
	printf("</DIR>%c",10);
	
} /* HtmlEndDirList */


void PSSYShtmlListItemTag()
{
	/*------------------------------------------*/
	/* HtmlListItemTag - put the LI tag	for use */
	/*                   with <OL>, <UL>,       */
	/*                   <MENU> and <DIR>       */
	/*------------------------------------------*/
	
	printf("<LI>");
	
} /* HtmlListItemTag */

	
void PSSYShtmlListItem(char *aItem)
{
	/*------------------------------------------*/
	/* HtmlListItem - write a List Item         */
	/*------------------------------------------*/
	
	PSSYShtmlListItemTag();
	printf("%s%c",aItem,10);

} /* HtmlListItem */


void PSSYShtmlBeginGlossList()
{
	/*------------------------------------------*/
	/* HtmlBeginGlossList - begin glossary list */
	/*------------------------------------------*/
	
	printf("<DL>%c",10);
	
} /* HtmlBeginGlossList */


void PSSYShtmlDefTerm(char *aTerm)
{
	/*------------------------------------------*/
	/* HtmlDefTerm - a definition term, as part */
	/*               of a definition list       */
	/* aTerm         term text                  */
	/*------------------------------------------*/
	
	printf("<DT>%s",aTerm);

} /* HtmlDefTerm */


void PSSYShtmlDefinition(char *aDefin)
{
	/*------------------------------------------*/
	/* HtmlDefTerm - a terms definition, as     */
	/*               part of a definition list  */
	/* aTerm         term text                  */
	/*------------------------------------------*/
	
	printf("<DD>%s%c",aDefin,10);

} /* HtmlDefinition */


void PSSYShtmlEndGlossList()
{
	/*------------------------------------------*/
	/* HtmlEndGlossList - end of glossary list  */
	/*------------------------------------------*/
	
	printf("</DL>%c",10);
	
} /* HtmlEndGlossList */


void PSSYShtmlEmphText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlEmphText - write emphasized text     */
	/*                (usually italic)          */
	/* aText        - text to write             */
	/*------------------------------------------*/

	printf("<EM>%s</EM>",aText);
	
} /* HtmlEmphText */


void PSSYShtmlStrongText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlStrongText - write strongly          */
	/*                  emphasized text         */
	/*                  (usually bold)          */
	/* aText          - text to write           */
	/*------------------------------------------*/

	printf("<STRONG>%s</STRONG>",aText);
	
} /* HtmlStrongText */


void PSSYShtmlSampleText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlSampleText - write example text      */
	/* aText          - text to write           */
	/*------------------------------------------*/

	printf("<SAMP>%s</SAMP>",aText);
	
} /* HtmlSampleText */


void PSSYShtmlCodeText(char *CodeText)
{
	/*------------------------------------------*/
	/* HtmlCodeText - write code sample text    */
	/*                (usually Courier)         */
	/* CodeText     - code text to write        */
	/*------------------------------------------*/
	
	printf("<CODE>%s</CODE>",CodeText);
	
} /* HtmlCodeText */


void PSSYShtmlKbdText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlKbdText - write text to be typed     */
	/*               (usually Courier)          */
	/* aText       - text to write              */
	/*------------------------------------------*/

	printf("<KBD>%s</KBD>",aText);
	
} /* HtmlKbdText */


void PSSYShtmlVarText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlVarText - write the name of a        */
	/*               variable, or some entity   */
	/*               to be replaced with an     */
	/*               value.                     */
	/*               (often italic or underline)*/
	/* aText       - text to write              */
	/*------------------------------------------*/

	printf("<VAR>%s</VAR>",aText);
	
} /* HtmlVarText */


void PSSYShtmlDfnText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlDfnText - highlight text that is     */
	/*               to be defined              */
	/* aText       - text to write              */
	/*------------------------------------------*/

	printf("<DFN>%s</DFN>",aText);
	
} /* HtmlDfnText */


void PSSYShtmlCiteText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlCiteText - write a citation          */
	/* aText        - text to write             */
	/*------------------------------------------*/

	printf("<CITE>%s</CITE>",aText);
	
} /* HtmlCiteText */


void PSSYShtmlBoldText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlBoldText - write boldface text       */
	/* aText        - text to write             */
	/*------------------------------------------*/

	printf("<B>%s</B>",aText);
	
} /* HtmlBoldText */


void PSSYShtmlItalicText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlItalicText - write italic text       */
	/* aText          - text to write           */
	/*------------------------------------------*/

	printf("<I>%s</I>",aText);
	
} /* HtmlItalicText */


void PSSYShtmlTypeText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlTypeText - write monospaced          */
	/*                typewriter font text      */
	/* aText        - text to write             */
	/*------------------------------------------*/

	printf("<TT>%s</TT>",aText);
	
} /* HtmlTypeText */


void PSSYShtmlPreText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlPreText - write preformatted text    */
	/* aText       - text to write              */
	/*------------------------------------------*/

	printf("<PRE>%s</PRE>",aText);
	
} /* HtmlPreText */


void PSSYShtmlBeginAddress()
{
	/*------------------------------------------*/
	/* HtmlBeginAddress - write address tag     */
	/*------------------------------------------*/
	
	printf("<ADDRESS>%c",10);
	
} /* HtmlBeginAddress */


void PSSYShtmlEndAddress()
{
	/*------------------------------------------*/
	/* HtmlEndAddress - write end address tag   */
	/*------------------------------------------*/
	
	printf("</ADDRESS>%c",10);
	
} /* HtmlEndAddress */


void PSSYShtmlAddressText(char *aText)
{
	/*------------------------------------------*/
	/* HtmlAddressText - write address in html  */
	/*                   format                 */
	/*------------------------------------------*/
	
	printf("<ADDRESS>%c%s</ADDRESS>",10,aText);

} /* HtmlAddressText */


void PSSYShtmlHorizRule()
{
	/*------------------------------------------*/
	/* HtmlHorizRule - A horizontal rule line   */
	/*------------------------------------------*/
	
	printf("<HR>%c",10);
	
} /* HtmlHorizRule */


void PSSYShtmlLineBreak()
{
	/*------------------------------------------*/
	/* HtmlLineBreak - A line break             */
	/*------------------------------------------*/
	
	printf("<BR>%c",10);
	
} /* HtmlHorizRule */


void PSSYShtmlBeginPostForm(char *anAction)
{
	/*------------------------------------------*/
	/* HtmlBeginPostForm - Begins a form with   */
	/*                     post method          */
	/* anAction     - Action to do when submit  */
	/*                button is selected        */
	/*------------------------------------------*/
	
	printf("<FORM METHOD=POST ACTION=\"%s\">%c",anAction,10);
	
} /* HtmlBeginPostForm */


void PSSYShtmlEndForm()
{
	/*------------------------------------------*/
	/* HtmlEndText - End of a form              */
	/*------------------------------------------*/

	printf("</FORM>%c",10);
	
} /* HtmlEndForm */


void PSSYShtmlSubmitInput(char *aValue)
{
	/*------------------------------------------*/
	/* HtmlSubmitInput - Creates a button to    */
	/*            submit the form to the script */
	/*            which process the input.      */
	/* aValue   - label of the button           */
	/*------------------------------------------*/
	
	printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"%s\">",aValue);

} /* HtmlSubmitInput */


void PSSYShtmlResetInput(char *aValue)
{
	/*------------------------------------------*/
	/* HtmlResetInput - Creates a button which  */
	/*            resets the default values of  */
	/*            the form, if any.             */
	/* aValue   - label of the button           */
	/*------------------------------------------*/
	
	printf("<INPUT TYPE=\"RESET\" VALUE=\"%s\">",aValue);

} /* HtmlResetInput */


void PSSYShtmlTextInput(char *aName, char *aValue, char *aSize, char *aMaxLength)
{
	/*------------------------------------------*/
	/* HtmlTextInput - Creates a single-line    */
	/*                 text field               */
	/* aName         - Name of the variable     */
	/*                 which holds the eventual */
	/*                 value of this element    */
	/* aValue        - default value            */
	/* aSize         - Size of the text field   */
	/* aMaxlength    - Maximum number of        */
	/*                 characters this text     */
	/*                 field will accept.       */
	/*------------------------------------------*/
	
	if (aValue!=NULL)
		{
		printf("<INPUT TYPE=\"TEXT\" NAME=\"%s\" VALUE=\"%s\" SIZE=%s MAXLENGTH=%s>%c",aName, aValue, aSize,aMaxLength,10);
		}
	else
		{
		printf("<INPUT TYPE=\"TEXT\" NAME=\"%s\" SIZE=%s MAXLENGTH=%s>%c",aName, aSize,aMaxLength,10);
		}
		
} /* HtmlTextInput */


void PSSYShtmlHiddenText(char *aName, char *aValue)
{
	/*------------------------------------------*/
	/* HtmlTextInput - Creates a hidden         */
	/*                 text field               */
	/* aName         - Name of the variable     */
	/*                 which holds the value    */
	/*                 of this element          */
	/* aValue        - value of this element    */
	/*------------------------------------------*/
	
	printf("<INPUT TYPE=\"HIDDEN\" NAME=\"%s\" VALUE=\"%s\">%c",aName, aValue, 10);
	
} /* HtmlHiddenText */


void PSSYShtmlEndText()
{
	/*------------------------------------------*/
	/* HtmlEndText - write HTML closing tags    */
	/*------------------------------------------*/

 	printf("</BODY>%c",10);
 	printf("</HTML>%c",10);

} /* HtmlEndText */	

