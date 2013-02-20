
// MyRainmeterView.cpp : CMyRainmeterGraphView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "Meter.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRainmeterGraphView

IMPLEMENT_DYNCREATE(CMyRainmeterGraphView, CScrollView)

BEGIN_MESSAGE_MAP(CMyRainmeterGraphView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyRainmeterGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_CODE, &CMyRainmeterGraphView::OnViewCode)
END_MESSAGE_MAP()

// CMyRainmeterGraphView ����/����

CMyRainmeterGraphView::CMyRainmeterGraphView()
{
	// TODO: �ڴ˴���ӹ������
	
}

CMyRainmeterGraphView::~CMyRainmeterGraphView()
{
	
}

BOOL CMyRainmeterGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyRainmeterGraphView ����

void CMyRainmeterGraphView::OnDraw(CDC* pDC)
{
	CMyRainmeterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//���ñ���ͼƬ
	//CPaintDC dc(this);
	//CImage nImage;
	//nImage.Load(pDoc->systemBgPath);//����ͼƬ
	//HBITMAP hBitmap=nImage.Detach();//���ͼƬ�������ת��
	//CBitmap m_bmpBK;
	//m_bmpBK.DeleteObject();
	//m_bmpBK.Attach(hBitmap);//ת��ΪCBitmap����
	//CRect rect;
	//GetClientRect(&rect);//���Ŀ��ߴ磬�����ڿͻ�����������������
	//BITMAP bitMap;//λͼ�ṹ��
	//m_bmpBK.GetBitmap(&bitMap);//����ָ��
	//CDC dcMem;//Ŀ��DC
	//dcMem.CreateCompatibleDC(&dc);//������dc���ݵ��ڴ�DC
	//dcMem.SelectObject(&m_bmpBK);//��λͼ����m_bmpBK�����ڴ�DC
	//dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
	//pDC->SetStretchBltMode(STRETCH_HALFTONE); 
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);	

	//��ȡ��Ļ��С ����������
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	// ���ҽ���ͼƬδ����ʱ����
	if(backgroundImage.IsNull())
		backgroundImage.Load(pDoc->systemBgPath);
	if(!backgroundImage.IsNull())
		backgroundImage.Draw(pDC->m_hDC,0,0,cx, cy);
	else
		AfxMessageBox(_T("���汳������ʧ�ܣ����������ñ��������ԣ����������Ȼ���ڣ���������ϵ~~"));
	SetScrollSizes(MM_TEXT,CSize(cx, cy));    
	
	
	//AfxMessageBox(pDoc->systemBgPath);
}

// 
void CMyRainmeterGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetScrollSizes(MM_TEXT,CSize(cx, cy)); 
}


// CMyRainmeterGraphView ��ӡ


void CMyRainmeterGraphView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyRainmeterGraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyRainmeterGraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyRainmeterGraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMyRainmeterGraphView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyRainmeterGraphView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyRainmeterGraphView ���

#ifdef _DEBUG
void CMyRainmeterGraphView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRainmeterGraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRainmeterDoc* CMyRainmeterGraphView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRainmeterDoc)));
	return (CMyRainmeterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyRainmeterGraphView ��Ϣ�������



void CMyRainmeterGraphView::OnViewCode()
{
	// TODO: �ڴ���������������
	GetDocument()->SwitchViewCodeFrame();

	
}
