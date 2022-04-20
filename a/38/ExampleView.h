// ExampleView.h : interface of the CExampleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLEVIEW_H__F10F716D_2B31_11D4_90AE_0010B53C9D0C__INCLUDED_)
#define AFX_EXAMPLEVIEW_H__F10F716D_2B31_11D4_90AE_0010B53C9D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExampleView : public CView
{
protected: // create from serialization only
	CExampleView();
	DECLARE_DYNCREATE(CExampleView)

// Attributes
public:
	CExampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExampleView)
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
	virtual ~CExampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	GLUquadricObj* m_qObj;
	CDC* pDC;
	HGLRC m_hglrc;
};

#ifndef _DEBUG  // debug version in ExampleView.cpp
inline CExampleDoc* CExampleView::GetDocument()
   { return (CExampleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLEVIEW_H__F10F716D_2B31_11D4_90AE_0010B53C9D0C__INCLUDED_)
