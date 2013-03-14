
// MyRainmeterDoc.h : CMyRainmeterDoc ��Ľӿ�
//

#pragma once

#include "ConfigParser.h"

class CMyRainmeterGraphView;

class CMyRainmeterDoc : public CDocument
{
protected: // �������л�����
	CMyRainmeterDoc();
	DECLARE_DYNCREATE(CMyRainmeterDoc)

// ����
public:
	CString systemBgPath;	//����ͼƬ��ַ
	CConfigParser *pConfigParser;
//	CRmCtrlList m_RmCtrls;
	/// Items 
	CArray<CXTPTaskPanelGroupItem*, CXTPTaskPanelGroupItem*> m_arrItems;

// ����
public:
	void SwitchViewCodeFrame();
//	CRmCtrlList* GetRmCtrls(){return &m_RmCtrls;}
	void Draw(CDC* pDC, CMyRainmeterGraphView* pView);
	CRmControl* RmCtrlAt(const CPoint& point);
	// ------ Draw called for live icon and Win7 taskbar thumbnails
	void Draw (CDC* pDC);
	void FixUpRmCtrlPositions();
	void Add(CRmControl* pObj);
	void Remove(CRmControl* pObj);

private:
	void InitDocument();

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMyRainmeterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
