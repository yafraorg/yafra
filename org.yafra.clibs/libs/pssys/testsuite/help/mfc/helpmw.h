// helpmw.h : main header file for the HELPMW application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelpmwApp:
// See helpmw.cpp for the implementation of this class
//

class CHelpmwApp : public CWinApp
{
public:
	CHelpmwApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpmwApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHelpmwApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateHelp(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void SBVWWWhelp(char *);

/////////////////////////////////////////////////////////////////////////////
