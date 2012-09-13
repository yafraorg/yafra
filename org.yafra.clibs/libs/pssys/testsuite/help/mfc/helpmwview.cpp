// helpmwView.cpp : implementation of the CHelpmwView class
//

#include "stdafx.h"
#include "helpmw.h"

#include "helpmwDoc.h"
#include "helpmwView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView

IMPLEMENT_DYNCREATE(CHelpmwView, CView)

BEGIN_MESSAGE_MAP(CHelpmwView, CView)
	//{{AFX_MSG_MAP(CHelpmwView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView construction/destruction

CHelpmwView::CHelpmwView()
{
	// TODO: add construction code here

}

CHelpmwView::~CHelpmwView()
{
}

BOOL CHelpmwView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView drawing

void CHelpmwView::OnDraw(CDC* pDC)
{
	CHelpmwDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView printing

BOOL CHelpmwView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHelpmwView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHelpmwView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView diagnostics

#ifdef _DEBUG
void CHelpmwView::AssertValid() const
{
	CView::AssertValid();
}

void CHelpmwView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelpmwDoc* CHelpmwView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelpmwDoc)));
	return (CHelpmwDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHelpmwView message handlers
