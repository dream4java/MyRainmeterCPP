
// MyRainmeterView.h : CMyRainmeterView ��Ľӿ�
//

#pragma once


class CMyRainmeterView : public CScrollView
{
protected: // �������л�����
	CMyRainmeterView();
	DECLARE_DYNCREATE(CMyRainmeterView)

// ����
public:
	CMyRainmeterDoc* GetDocument() const;
private:
	CImage backgroundImage;
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMyRainmeterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewCode();
};

#ifndef _DEBUG  // MyRainmeterView.cpp �еĵ��԰汾
inline CMyRainmeterDoc* CMyRainmeterView::GetDocument() const
   { return reinterpret_cast<CMyRainmeterDoc*>(m_pDocument); }
#endif

