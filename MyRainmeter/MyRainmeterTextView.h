#pragma once


// CMyRainmeterTextView ��ͼ

class CMyRainmeterTextView : public CEditView
{
	DECLARE_DYNCREATE(CMyRainmeterTextView)

protected:
	CMyRainmeterTextView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyRainmeterTextView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


