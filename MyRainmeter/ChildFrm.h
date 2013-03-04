
// ChildFrm.h : CChildFrame ��Ľӿ�
//

#pragma once
#include "Ruler.h"

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// ����
public:

private:
	CRulerSplitterWnd m_Rulers;

// ����
public:
	void ShowRulers(BOOL bShow);
	void UpdateRulersInfo(stRULER_INFO stRulerInfo);

// ��д
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// ʵ��
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnClose();
};
