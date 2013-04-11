
// MyRainmeterDoc.h : CMyRainmeterDoc ��Ľӿ�
//

#pragma once

#include "ConfigParser.h"
#include "Rainmeter.h"

class CMyRainmeterGraphView;
class CMyRainmeterTextView;

class CString_Hash{
public:
	size_t operator()(const CString& str) const
	{
		unsigned long __h = 0;
		for (size_t i = 0 ; i < str.GetLength() ; i ++)
			__h = 5*__h + str[i];
		return size_t(__h);
	}
};

class CMyRainmeterDoc : public CDocument
{
protected: // �������л�����
	CMyRainmeterDoc();
	DECLARE_DYNCREATE(CMyRainmeterDoc)

// ����
public:
	CString m_SystemBgPath;	//����ͼƬ��ַ
	CRainmeter m_Rainmeter;
	CMetadata m_MeterData;
	CString m_Text;
	CConfigParser *m_pConfigParser;
	/// Items 
	CRmCtrlList m_arrItems;
	CRmControl* m_pCurRmCtrl;
	
	//unordered_map<CString, CString, CString_Hash> m_MeterData;
	//unordered_map<CString, CString, CString_Hash> m_Variables;

protected:
	

// ����
public:	
	void SwitchViewCodeFrame();
//	CRmCtrlList* GetRmCtrls(){return &m_RmCtrls;}
	
	void Draw(CDC* pDC, CXTPTaskPanel* pTaskPanel);
	void RemoveAt(int index);
	
	void Add(CRmControl* pObj);
	void Remove(CRmControl* pObj);
	CMyRainmeterTextView* GetTextView();
	virtual void UpdateAllViews(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
	virtual BOOL DoSave(LPCTSTR pszPathName, BOOL bReplace = TRUE);

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


