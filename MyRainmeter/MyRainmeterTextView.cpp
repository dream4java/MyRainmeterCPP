// MyRainmeterTextView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyRainmeter.h"
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
END_MESSAGE_MAP()


// CMyRainmeterTextView ��ͼ

void CMyRainmeterTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CMyRainmeterTextView ���

#ifdef _DEBUG
void CMyRainmeterTextView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyRainmeterTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyRainmeterTextView ��Ϣ�������
