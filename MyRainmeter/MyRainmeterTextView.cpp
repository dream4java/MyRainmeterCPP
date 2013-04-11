// MyRainmeterTextView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterTextView.h"


// CMyRainmeterTextView

IMPLEMENT_DYNCREATE(CMyRainmeterTextView, CEditView)

CMyRainmeterTextView::CMyRainmeterTextView()
{
	
}

CMyRainmeterTextView::~CMyRainmeterTextView()
{
}

BEGIN_MESSAGE_MAP(CMyRainmeterTextView, CEditView)
	ON_EN_CHANGE(AFX_IDW_PANE_FIRST, OnEditChange)
END_MESSAGE_MAP()


// CMyRainmeterTextView ���

#ifdef _DEBUG
void CMyRainmeterTextView::AssertValid() const
{
	CEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyRainmeterTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}


#endif
#endif //_DEBUG

void CMyRainmeterTextView::SetText( CString sText )
{
	SetWindowText(sText);
}

CString CMyRainmeterTextView::GetText()
{
	CString sTemp;	
	GetWindowText(sTemp);
	return sTemp;
}

// CMyRainmeterTextView ��Ϣ�������


void CMyRainmeterTextView::OnEditChange()
{
	CMyRainmeterDoc* pDoc = (CMyRainmeterDoc*)GetDocument();
	pDoc->m_Text = GetText();
}

BOOL CMyRainmeterTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	//cs.style |= ES_READONLY;
	return CEditView::PreCreateWindow(cs);
}
