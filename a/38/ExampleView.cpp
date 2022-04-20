// ExampleView.cpp : implementation of the CExampleView class
//

#include "stdafx.h"
#include "Example.h"

#include "ExampleDoc.h"
#include "ExampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExampleView

IMPLEMENT_DYNCREATE(CExampleView, CView)

BEGIN_MESSAGE_MAP(CExampleView, CView)
	//{{AFX_MSG_MAP(CExampleView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExampleView construction/destruction

CExampleView::CExampleView()
{
	// TODO: add construction code here
	m_qObj = gluNewQuadric();
}

CExampleView::~CExampleView()
{
	gluDeleteQuadric(m_qObj);
}

BOOL CExampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CS_OWNDC;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView drawing

void CExampleView::OnDraw(CDC* pDC)
{
    CExampleDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0.0f, 0.5f, 0.5f);
	gluSphere(m_qObj, 1.0f, 10, 10);

	SwapBuffers(pDC->m_hDC);
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView printing

BOOL CExampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExampleView diagnostics

#ifdef _DEBUG
void CExampleView::AssertValid() const
{
	CView::AssertValid();
}

void CExampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExampleDoc* CExampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExampleDoc)));
	return (CExampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExampleView message handlers

int CExampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormat;

    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO: Add your specialized creation code here
    pDC = GetDC();
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 16;
    iPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
    SetPixelFormat(pDC->m_hDC, iPixelFormat, &pfd);
    m_hglrc = wglCreateContext(pDC->m_hDC);
    wglMakeCurrent(pDC->m_hDC, m_hglrc);

	glClearColor (0.5, 0.5, 0.75, 1.0);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_COLOR_MATERIAL);

    return 0;
}

void CExampleView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
    wglMakeCurrent(NULL, NULL);	
	wglDeleteContext(m_hglrc);
    ReleaseDC(pDC);
}

void CExampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;

	GetClientRect(&rect);

	glViewport(0, 0, rect.right, rect.bottom);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glFrustum (-1, 1, -1, 1, 4, 10);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -8.0);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(70.0f, 0.0f, 1.0f, 0.0f);
}
