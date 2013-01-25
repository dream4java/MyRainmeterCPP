
// MyRainmeterView.cpp : CMyRainmeterView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MyRainmeterView.h"
#include "Meter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRainmeterView

IMPLEMENT_DYNCREATE(CMyRainmeterView, CScrollView)

BEGIN_MESSAGE_MAP(CMyRainmeterView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyRainmeterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_CODE, &CMyRainmeterView::OnViewCode)
END_MESSAGE_MAP()

// CMyRainmeterView ����/����

CMyRainmeterView::CMyRainmeterView()
{
	// TODO: �ڴ˴���ӹ������
	
}

CMyRainmeterView::~CMyRainmeterView()
{
	
}

BOOL CMyRainmeterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyRainmeterView ����

void CMyRainmeterView::OnDraw(CDC* pDC)
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
void CMyRainmeterView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	SetScrollSizes(MM_TEXT,CSize(cx, cy)); 
}


// CMyRainmeterView ��ӡ


void CMyRainmeterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyRainmeterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyRainmeterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyRainmeterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMyRainmeterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyRainmeterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyRainmeterView ���

#ifdef _DEBUG
void CMyRainmeterView::AssertValid() const
{
	CView::AssertValid();
}

void CMyRainmeterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyRainmeterDoc* CMyRainmeterView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyRainmeterDoc)));
	return (CMyRainmeterDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyRainmeterView ��Ϣ�������


void CMyRainmeterView::OnViewCode()
{
	// TODO: �ڴ���������������
	
	POSITION tDocTemplatePos = theApp.m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate* pDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tDocTemplatePos);
	pDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tDocTemplatePos);
	if (pDocTemplate!=NULL)
	{
		pDocTemplate->OpenDocumentFile(NULL);
	}
		
}
