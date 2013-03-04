
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"

#include "Corner.h"
#include "VRuler.h"
#include "HRuler.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame ��Ϣ�������


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pContext->m_pNewViewClass->m_lpszClassName == "CMyRainmeterTextView")
	{
		return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
	}
	if (!m_Rulers.CreateRulers(this, pContext)) {
		TRACE("Error creation of rulers\n");
		return CMDIChildWnd::OnCreateClient(lpcs, pContext);
	}

	return TRUE;
	//return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


void CChildFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CMDIChildWndEx::OnClose();
}

void CChildFrame::ShowRulers( BOOL bShow )
{
	m_Rulers.ShowRulers(bShow);
}

void CChildFrame::UpdateRulersInfo(stRULER_INFO stRulerInfo)
{
	m_Rulers.UpdateRulersInfo(stRulerInfo);
}
	