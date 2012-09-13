// helpmwView.h : interface of the CHelpmwView class
//
/////////////////////////////////////////////////////////////////////////////

class CHelpmwView : public CView
{
protected: // create from serialization only
	CHelpmwView();
	DECLARE_DYNCREATE(CHelpmwView)

// Attributes
public:
	CHelpmwDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpmwView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHelpmwView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHelpmwView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in helpmwView.cpp
inline CHelpmwDoc* CHelpmwView::GetDocument()
   { return (CHelpmwDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
