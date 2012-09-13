/*
 * Copyright(c) 1992 Bell Communications Research, Inc. (Bellcore)
 *                        All rights reserved
 * Permission to use, copy, modify and distribute this material for
 * any purpose and without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies, and that the name of Bellcore not be used in advertising
 * or publicity pertaining to this material without the specific,
 * prior written permission of an authorized representative of
 * Bellcore.
 *
 * BELLCORE MAKES NO REPRESENTATIONS AND EXTENDS NO WARRANTIES, EX-
 * PRESS OR IMPLIED, WITH RESPECT TO THE SOFTWARE, INCLUDING, BUT
 * NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR ANY PARTICULAR PURPOSE, AND THE WARRANTY AGAINST IN-
 * FRINGEMENT OF PATENTS OR OTHER INTELLECTUAL PROPERTY RIGHTS.  THE
 * SOFTWARE IS PROVIDED "AS IS", AND IN NO EVENT SHALL BELLCORE OR
 * ANY OF ITS AFFILIATES BE LIABLE FOR ANY DAMAGES, INCLUDING ANY
 * LOST PROFITS OR OTHER INCIDENTAL OR CONSEQUENTIAL DAMAGES RELAT-
 * ING TO THE SOFTWARE.
 *
 */

#ifndef _Xbae_Converters_h
#define _Xbae_Converters_h

/*
 * Converters.h created by Andrew Lister (6 August, 1995)
 */

#include <Xm/Xm.h>
#include <Xbae/Macros.h>
/*
 * Type converters
 */
Boolean CvtStringToStringArray P(( Display *dpy, XrmValuePtr args,
				   Cardinal *num_args, XrmValuePtr from,
				   XrmValuePtr to, XtPointer *data ));
void StringArrayDestructor P(( XtAppContext app, XrmValuePtr to,
			       XtPointer converter_data,
			       XrmValuePtr args, Cardinal *num_args ));
Boolean CvtStringToWidthArray P(( Display *dpy, XrmValuePtr args,
				  Cardinal *num_args, XrmValuePtr from,
				  XrmValuePtr to, XtPointer *data ));
void WidthArrayDestructor  P(( XtAppContext app, XrmValuePtr to,
			       XtPointer converter_data,
			       XrmValuePtr args, Cardinal *num_args ));
Boolean CvtStringToMaxLengthArray P(( Display *dpy, XrmValuePtr args,
				      Cardinal *num_args,
				      XrmValuePtr from,
				      XrmValuePtr to,
				      XtPointer *data ));
void MaxLengthArrayDestructor P(( XtAppContext app, XrmValuePtr to,
				  XtPointer converter_data,
				  XrmValuePtr args,
				  Cardinal *num_args ));

Boolean CvtStringToAlignmentArray P(( Display *dpy, XrmValuePtr args,
				      Cardinal *num_args,
				      XrmValuePtr from,
				      XrmValuePtr to,
				      XtPointer *data ));
void AlignmentArrayDestructor P(( XtAppContext app, XrmValuePtr to,
				  XtPointer converter_data,
				  XrmValuePtr args,
				  Cardinal *num_args ));
Boolean CvtStringToGridType P(( Display *dpy, XrmValuePtr args,
				Cardinal *num_args, XrmValuePtr from,
				XrmValuePtr to, XtPointer *data ));

#endif
