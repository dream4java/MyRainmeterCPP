
// MyRainmeterGraphView.cpp : CMyRainmeterGraphView ���ʵ��
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


#define ZOOM_MAX            2
#define ZOOM_MIN            0.25
#define ZOOM_NORMAL         1


// CMyRainmeterGraphView

IMPLEMENT_DYNCREATE(CMyRainmeterGraphView, CScrollView)

BEGIN_MESSAGE_MAP(CMyRainmeterGraphView, CScrollView)
	//{{AFX_MSG_MAP(CDemoView)
	//ON_COMMAND(ID_DEMO_TOGGLERULERS, OnRulersTogglerulers)
	//ON_UPDATE_COMMAND_UI(ID_DEMO_TOGGLERULERS, OnUpdateRulersTogglerulers)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyRainmeterGraphView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_VIEW_CODE, &CMyRainmeterGraphView::OnViewCode)
	ON_WM_MOUSEMOVE()
//	ON_WM_PAINT()
	ON_WM_PAINT()
//	ON_WM_PAINT()
ON_WM_PAINT()
END_MESSAGE_MAP()

// CMyRainmeterGraphView ����/����

CMyRainmeterGraphView::CMyRainmeterGraphView()
{
	// TODO: �ڴ˴���ӹ������
	m_pParent           = NULL;
	m_BrushBackGround.CreateHatchBrush(HS_DIAGCROSS, RGB(191, 191, 191));
	m_bShowRulers       = TRUE;
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	m_DesktopSize = CSize(cx, cy);

	m_imageManager.SetIcons(IDB_TRASH, 0, 0, CSize(48, 48));
		
}

CMyRainmeterGraphView::~CMyRainmeterGraphView()
{
	//m_BackgroundImage.Destroy();
	m_BrushBackGround.DeleteObject();
	for (int i = 0; i < GetDocument()->m_arrItems.GetSize(); i++)
	{
		GetDocument()->m_arrItems[i]->InternalRelease();
	}
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

	CDC dc;
	CDC* pDrawDC = pDC;
	CBitmap bitmap;
	CBitmap* pOldBitmap = 0;

	// only paint the rect that needs repainting
	CRect client;
	pDC->GetClipBox(client);
	CRect rect = client;
	//DocToClient(rect);

	//if (!pDC->IsPrinting())
	//{
	//	// draw to offscreen bitmap for fast looking repaints
	//	if (dc.CreateCompatibleDC(pDC))
	//	{
	//		if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
	//		{
	//			OnPrepareDC(&dc, NULL);
	//			pDrawDC = &dc;

	//			// offset origin more because bitmap is just piece of the whole drawing
	//			dc.OffsetViewportOrg(-rect.left, -rect.top);
	//			pOldBitmap = dc.SelectObject(&bitmap);
	//			dc.SetBrushOrg(rect.left % 8, rect.top % 8);

	//			// might as well clip to the same rectangle
	//			dc.IntersectClipRect(client);
	//		}
	//	}
	//}

	// paint background

	if (!pDC->IsPrinting())
		DrawBackground(pDC);

	pDoc->Draw(pDrawDC, this);

	if (pDrawDC != pDC)
	{
		pDC->SetViewportOrg(0, 0);
		pDC->SetWindowOrg(0,0);
		pDC->SetMapMode(MM_TEXT);
		dc.SetViewportOrg(0, 0);
		dc.SetWindowOrg(0,0);
		dc.SetMapMode(MM_TEXT);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
		dc.SelectObject(pOldBitmap);
	}
	
}

void CMyRainmeterGraphView::DrawBackground( CDC* pDC )
{
	CMyRainmeterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// ���ҽ���ͼƬδ����ʱ����
	if(m_BackgroundImage.IsNull())
		m_BackgroundImage.Load(pDoc->systemBgPath);
	if(!m_BackgroundImage.IsNull())
	{
	//	m_BackgroundImage.Draw(pDC->m_hDC,0,0, m_DesktopSize.cx, m_DesktopSize.cy);
		HBITMAP hBitmap=m_BackgroundImage.Detach();//���ͼƬ�������ת��
		CBitmap m_bmpBK;
		m_bmpBK.DeleteObject();
		m_bmpBK.Attach(hBitmap);//ת��ΪCBitmap����
		CRect rect;
		GetClientRect(&rect);//���Ŀ��ߴ磬�����ڿͻ�����������������
		BITMAP bitMap;//λͼ�ṹ��
		m_bmpBK.GetBitmap(&bitMap);//����ָ��
		CDC dcMem;//Ŀ��DC
		dcMem.CreateCompatibleDC(pDC);//������dc���ݵ��ڴ�DC
		dcMem.SelectObject(&m_bmpBK);//��λͼ����m_bmpBK�����ڴ�DC
		//dcMem.SetStretchBltMode(STRETCH_HALFTONE); 
		//dcMem.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,m_DesktopSize.cx,m_DesktopSize.cy,SRCCOPY);
		
		pDC->SetStretchBltMode(STRETCH_HALFTONE); 
		CPoint point = GetScrollPosition();
		pDC->StretchBlt(0,0,m_DesktopSize.cx,m_DesktopSize.cy,&dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
		//pDC->BitBlt(point.x,point.y,rect.Width(),rect.Height(),&dcMem, point.x,point.y,SRCCOPY);	
		m_bmpBK.DeleteObject();
		dcMem.DeleteDC();
		
	}
	else
		AfxMessageBox(_T("���汳������ʧ�ܣ����������ñ��������ԣ����������Ȼ���ڣ���������ϵ~~"));	
}

// 
void CMyRainmeterGraphView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	m_wndDragTarget.Register(this);

	SetScrollSizes(MM_TEXT, m_DesktopSize);  
	m_pParent = ((CChildFrame*)GetParentFrame());
	m_pParent->ShowRulers(TRUE);
	OnUpdate(NULL, 0, NULL);
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


void CMyRainmeterGraphView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	SetScrollSizes(MM_TEXT, m_DesktopSize);   
	UpdateRulersInfo(RW_POSITION, GetScrollPosition());
	Invalidate();	
}

void CMyRainmeterGraphView::OnRulersTogglerulers() 
{
	m_bShowRulers = !m_bShowRulers;
	m_pParent->ShowRulers(m_bShowRulers);
}

void CMyRainmeterGraphView::OnUpdateRulersTogglerulers(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bShowRulers);
}

void CMyRainmeterGraphView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// Update the ruler mark
	UpdateRulersInfo(RW_POSITION, GetScrollPosition(), point);

	CScrollView::OnMouseMove(nFlags, point);
}



BOOL CMyRainmeterGraphView::OnEraseBkgnd( CDC* pDC )
{
	FillOutsideRect(pDC, &m_BrushBackGround);
	return TRUE;
	return FALSE; 
}

void CMyRainmeterGraphView::OnLButtonDown( UINT nFlags, CPoint point )
{
	// TODO:
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMyRainmeterGraphView::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	UpdateRulersInfo(RW_VSCROLL, GetScrollPosition());
	Invalidate(FALSE);

	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyRainmeterGraphView::OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar )
{
	UpdateRulersInfo(RW_HSCROLL, GetScrollPosition());
	Invalidate(FALSE);

	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMyRainmeterGraphView::UpdateRulersInfo( int nMessage, CPoint ScrollPos, CPoint Pos /*= CPoint(0, 0)*/ )
{
	if (!m_pParent)
		return;
	stRULER_INFO pRulerInfo;
	pRulerInfo.uMessage    = nMessage;
	pRulerInfo.ScrollPos   = ScrollPos;
	pRulerInfo.Pos         = Pos;
	pRulerInfo.DocSize     = m_DesktopSize;
	pRulerInfo.fZoomFactor = 1;

	m_pParent->UpdateRulersInfo(pRulerInfo);
}





DROPEFFECT CMyRainmeterGraphView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!pDataObject || !pDataObject->IsDataAvailable(CXTPTaskPanel::GetClipboardFormat()))
		return DROPEFFECT_NONE;
	return DROPEFFECT_COPY;
//	return CScrollView::OnDragOver(pDataObject, dwKeyState, point);
}


BOOL CMyRainmeterGraphView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	CXTPTaskPanelGroupItem* pItemDrop = (CXTPTaskPanelGroupItem*)CXTPTaskPanelItem::CreateFromOleData(pDataObject);

	if (!pItemDrop)
		return FALSE;

	ASSERT_KINDOF(CXTPTaskPanelGroupItem, pItemDrop);

	GetDocument()->m_arrItems.Add(pItemDrop);
	CPoint ScrollPos = this->GetScrollPosition();
	pItemDrop->SetItemRect(CRect(point.x + ScrollPos.x - 14, point.y + ScrollPos.y - 14, point.x +ScrollPos.x + 14, point.y + ScrollPos.y + 14));

	Invalidate(FALSE);

	return TRUE;
//	return CScrollView::OnDrop(pDataObject, dropEffect, point);
}



BOOL CMyRainmeterGraphView::PtInTrash(CPoint point)
{
	CXTPClientRect rc(this);
	CRect rcTrash(rc.right - 72, rc.bottom - 72, rc.right - 12, rc.bottom - 12);

	return rcTrash.PtInRect(point);
}

CXTPTaskPanel* CMyRainmeterGraphView::GetTaskPanel()
{
	//CWnd* pSplitterWnd = GetParentFrame()->GetDlgItem(IDS_KIT_VIEW);
	CMainFrame* pMainWnd = (CMainFrame *)AfxGetMainWnd();
	CKitView* pKitViewPane = pMainWnd->GetKitVew();
	
	ASSERT_KINDOF(CKitView, pKitViewPane);

	return (CXTPTaskPanel*)pKitViewPane->GetTaskPanel();
}




