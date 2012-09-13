// helpmwDoc.cpp : implementation of the CHelpmwDoc class
//

#include "stdafx.h"
#include "helpmw.h"

#include "helpmwDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpmwDoc

IMPLEMENT_DYNCREATE(CHelpmwDoc, CDocument)

BEGIN_MESSAGE_MAP(CHelpmwDoc, CDocument)
	//{{AFX_MSG_MAP(CHelpmwDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpmwDoc construction/destruction

CHelpmwDoc::CHelpmwDoc()
{
	// TODO: add one-time construction code here

}

CHelpmwDoc::~CHelpmwDoc()
{
}

BOOL CHelpmwDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CHelpmwDoc serialization

void CHelpmwDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHelpmwDoc diagnostics

#ifdef _DEBUG
void CHelpmwDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHelpmwDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpmwDoc commands
