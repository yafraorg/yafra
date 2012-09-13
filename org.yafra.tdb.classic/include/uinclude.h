/*IH***********************************************************
 * Header:        User Interface
 *
 * Description:   X-Window Module Prototypes (ANSI C)
 *                for xUI modules
 *                -nested includes for X11, Xm 
 *                - Callback functions, Actions functions 
 *                - Definitions 
 *                - Resources and defaults (DEF values)
 *
 * Copyright: yafra.org, Basel, Switzerland
 **************************************************************
 */

/*---------------------- INCLUDE GROUPING -----------------------------------*/

#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <X11/cursorfont.h>

#include <Xm/Xm.h>

#ifdef ps_win31              /* filenames on WIN 3.1 are only 8 plus 2 */
#include <Xm/Protoco.h>
#include <Xm/BulletB.h>
#include <Xm/RowColu.h>
#include <Xm/MessagB.h>
#include <Xm/CascaB.h>
#include <Xm/TogglBG.h>
#include <Xm/Separat.h>
#include <Xm/SeparaG.h>
#include <Xm/ScrollW.h>
#include <Xm/SelectB.h>
#include <Xm/DrawinA.h>
#include <Xm/ScrollB.h>
#else
#include <Xm/Protocols.h>
#include <Xm/BulletinB.h>
#include <Xm/RowColumn.h>
#include <Xm/MessageB.h>
#include <Xm/CascadeB.h>
#include <Xm/ToggleBG.h>
#include <Xm/Separator.h>
#include <Xm/SeparatoG.h>
#include <Xm/ScrolledW.h>
#include <Xm/SelectioB.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrollBar.h>
#endif

#include <Xm/AtomMgr.h>
#include <Xm/MwmUtil.h>
#include <Xm/MainW.h>
#include <Xm/DialogS.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/ToggleB.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>
#include <Xm/List.h>
#include <Xm/FileSB.h>

#include <mpmain.h>
#include <mpprolib.h>
#include <ulabels.h>
#include <uwgclass.h>
#include <uappdefs.h>
#include <binclude.h>
#include <ucselect.h>
#include <uctwin.h>
#include <utypes.h>
#include <uproto.h>
#include <udefs.h>

