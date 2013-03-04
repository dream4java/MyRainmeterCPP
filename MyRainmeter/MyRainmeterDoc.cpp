
// MyRainmeterDoc.cpp : CMyRainmeterDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyRainmeter.h"
#endif

#include "MyRainmeterDoc.h"
#include "MainFrm.h"

#include "MyRainmeterTextView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyRainmeterDoc

IMPLEMENT_DYNCREATE(CMyRainmeterDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyRainmeterDoc, CDocument)
END_MESSAGE_MAP()


// CMyRainmeterDoc ����/����

CMyRainmeterDoc::CMyRainmeterDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyRainmeterDoc::~CMyRainmeterDoc()
{
	
//	delete systemBgPath;
//	delete pConfigParser;
}

BOOL CMyRainmeterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	InitDocument();

	return TRUE;
}


BOOL CMyRainmeterDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	InitDocument();
	return TRUE;
}


void CMyRainmeterDoc::InitDocument()
{
	///��ȡ���汳��ͼƬ��ַ
	HRESULT hr;//���ڱ��淵��ֵ
	IActiveDesktop* pIAD;//����ӿ�ʵ��
	hr=CoCreateInstance(CLSID_ActiveDesktop, NULL,CLSCTX_INPROC_SERVER,IID_IActiveDesktop,(void**)&pIAD);//��ʼ��
	WCHAR wszWallpaper[MAX_PATH];//���ڱ��汳��ͼƬ·��
	hr=pIAD->GetWallpaper(wszWallpaper,MAX_PATH,0);//��ȡ����ͼƬ·��
	systemBgPath = wszWallpaper;

	pConfigParser = new CConfigParser(_T("E:\\rainmeter\\Rainmeter\\Skins\\����\\ini.ini"));
	wstring val1 = pConfigParser->GetValueString(_T("Rainmeter"),_T("Author"), _T("null"));
	MessageBox(NULL, val1.c_str(), _T("aaa"), 0);
	CMainFrame* pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->AddStrLogToOutputWnd(val1.c_str());
	
}


void CMyRainmeterDoc::SwitchViewCodeFrame()
{
	CFrameWnd *m_pTextViewFrame = NULL;

	// Check and set the TextViewFrame
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView( pos );
		if (pView->IsKindOf(RUNTIME_CLASS(CMyRainmeterTextView)))
		{
			m_pTextViewFrame = pView->GetParentFrame();
			break;
		}
	}
		
	// if TextViewFrame doesn't exist (NULL), initialize and display it.
	if(m_pTextViewFrame == NULL)
	{
		// Create TextView frame
		CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
		CMDIChildWnd* pActiveChild = pMainFrame->MDIGetActive();

		if (pActiveChild == NULL )
		{
			TRACE0("Warning: No active document for WindowNew command\n");
			AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
			return ;     // command failed
		}
		CDocTemplate* pTemplate = theApp.m_pTemplateTxt;
		ASSERT_VALID(pTemplate);

		m_pTextViewFrame = pTemplate->CreateNewFrame(this, pActiveChild);
		if (m_pTextViewFrame == NULL)
		{
			TRACE0("Warning: failed to create new frame\n");
			AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
			return ;     // command failed
		}
		pTemplate->InitialUpdateFrame(m_pTextViewFrame, this);
	}
	else	// TextViewFrame exists, just switch to show it
	{		
		CDocTemplate* pTemplate = theApp.m_pTemplateTxt;
		pTemplate->InitialUpdateFrame(m_pTextViewFrame, this);
	}
}


// CMyRainmeterDoc ���л�

void CMyRainmeterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMyRainmeterDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMyRainmeterDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMyRainmeterDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyRainmeterDoc ���

#ifdef _DEBUG
void CMyRainmeterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyRainmeterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}


#endif //_DEBUG


// CMyRainmeterDoc ����
