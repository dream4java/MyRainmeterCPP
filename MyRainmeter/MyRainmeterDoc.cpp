
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
	m_pCurRmCtrl=NULL;
	
}

CMyRainmeterDoc::~CMyRainmeterDoc()
{
	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		m_arrItems[i]->InternalRelease();
	}
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
	m_Text = "";

	CMainFrame* pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->AddStrLogToOutputWnd(_T("Create a new skin"));

	std::pair<CString, CString> pair(_T("Update"), _T("1000"));
	// Initialize Rainmeter Section
	//m_Rainmeter.insert(pair);
	//m_Rainmeter.insert(std::unordered_map::value_type(_T(""), _T("")));
	//m_Rainmeter.insert(_T("DynamicWindowSize"), _T("0"));
	//m_Rainmeter.insert(_T("DragMargins"), _T("0,0,0,0"));

	return TRUE;
}


BOOL CMyRainmeterDoc::OnOpenDocument( LPCTSTR lpszPathName )
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	InitDocument();	

	CMainFrame* pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->AddStrLogToOutputWnd(_T("Open skin:")+CString(lpszPathName));

	CStdioFile file(lpszPathName, CFile::modeRead);
	CString sTemp;
	bool isEof=FALSE;
	while (!isEof)
	{
		isEof = !file.ReadString(sTemp);
		m_Text += sTemp+L"\r\n";
		if (isEof)
		{
			break;
		}
	}
	file.Close();

	m_pConfigParser = new CConfigParser(lpszPathName);
	CString val1 = m_pConfigParser->GetValueString(_T("Rainmeter"),_T("Author"), _T("null"));
	MessageBox(NULL, val1, _T("Open a skin configuration "), 0);	

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
	m_SystemBgPath = wszWallpaper;

	//m_pConfigParser = new CConfigParser(_T("E:\\rainmeter\\Rainmeter\\Skins\\����\\ini.ini"));	

}


void CMyRainmeterDoc::SwitchViewCodeFrame()
{
	CFrameWnd *m_pTextViewFrame = NULL;

	// Check and set the TextViewFrame
	CMyRainmeterTextView* pTextView = GetTextView();
	if (pTextView != NULL)
	{
		m_pTextViewFrame = pTextView->GetParentFrame();
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
	pTextView = (CMyRainmeterTextView*)m_pTextViewFrame->GetActiveView();
	pTextView->SetText(m_Text);
}


// CMyRainmeterDoc ���л�

void CMyRainmeterDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		ar.Flush();		
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

void CMyRainmeterDoc::Add( CRmControl* pObj )
{
//	m_RmCtrls.AddTail(pObj);
//	pObj->m_pDocument = this;
	m_arrItems.Add(pObj);
	SetModifiedFlag();
}

void CMyRainmeterDoc::Remove( CRmControl* pObj )
{
	for (int i=0; i<m_arrItems.GetSize(); ++i)
	{
		CRmControl* pRmCtrl = m_arrItems[i];
		if (pRmCtrl == pObj)
		{
			m_arrItems.RemoveAt(i);
			pObj->InternalRelease();
			SetModifiedFlag();
		}
	}
	
}

void CMyRainmeterDoc::RemoveAt(int index)
{	
	CRmControl* pRmCtrl = m_arrItems[index];
//	pRmCtrl->m_pItem->InternalRelease();
	//delete pRmCtrl->m_pItem;
	m_arrItems.RemoveAt(index);
	pRmCtrl->InternalRelease();
//	delete pRmCtrl;
	SetModifiedFlag();
}

void CMyRainmeterDoc::Draw( CDC* pDC, CXTPTaskPanel* pTaskPanel )
{
	m_Text="";
	m_Text+=m_Rainmeter.ToString();
	m_Text+=m_MeterData.ToString();
	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		CRmControl* pRmCtrl = (CRmControl* )m_arrItems[i];
		
		CXTPTaskPanelGroupItem* pItem=pRmCtrl->m_pItem;;
		
		pRmCtrl->Draw(pDC, pTaskPanel);

		m_Text += pRmCtrl->ToString();
		/*CRect rcItem = pItem->GetItemRect();		

		CXTPImageManagerIcon* pImage = pTaskPanel->GetImageManager()->GetImage(pItem->GetIconIndex());
		pTaskPanel->GetPaintManager()->DrawGroupItemFrame(pDC, pItem, rcItem);
		if (pImage)
		{
			CPoint ptIcon((rcItem.right + rcItem.left - 16) / 2, (rcItem.top + rcItem.bottom - 16) / 2);
			pImage->Draw(pDC, ptIcon, pImage->GetIcon());
		}*/
	}

}


BOOL CMyRainmeterDoc::DoSave( LPCTSTR pszPathName, BOOL bReplace /*= TRUE*/ )
{
	CMainFrame* pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->AddStrLogToOutputWnd(_T("Saving skin..."));

	CString newName = pszPathName;
	BOOL bModified = IsModified();
	BOOL bSaveAs = FALSE;
	CConfigParser* pConfigParser = m_pConfigParser;

	// First save
	if (newName.IsEmpty())
		bSaveAs = TRUE;
	
	POSITION pos = GetFirstViewPosition();
	GetNextView(pos)->GetParentFrame()->RecalcLayout();

	if (bSaveAs)
	{
		newName = m_strPathName;
		if (bReplace && newName.IsEmpty())
		{
			newName = m_strTitle;
		}
		if (!AfxGetApp()->DoPromptFileName(newName,
			bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, this->GetDocTemplate()))
		{
			pMainFrame->AddStrLogToOutputWnd(_T("Saving canceled."));
			return FALSE;
		}
		pConfigParser = new CConfigParser(newName);
	}
	BeginWaitCursor();

	OnSaveDocument(newName);	

	
	CStdioFile file(newName, CFile::modeWrite | CFile::typeBinary );
	file.Write("\377\376", 2);
	file.WriteString(m_Text);
	file.Flush();
	file.Close();
	//for (unordered_map<CString, CString>::iterator iter = m_Rainmeter.begin(); iter != m_Rainmeter.end(); ++iter)
	//{
	//	pConfigParser->SetValueString(_T("Rainmeter"), iter->first, iter->second);
	//}
	//
	////m_pConfigParser->
	//
	//// iterate the items, write data to the configuration file
	//CRmControl* pRmCtrl;
	//for (int i=0; i<m_arrItems.GetSize(); ++i)
	//{
	//	pRmCtrl = (CRmControl* )m_arrItems[i];
	//	pRmCtrl->WriteToFile(pConfigParser);
	//}

	m_pConfigParser = pConfigParser;
	// Set the path, otherwise the program would show the save file dialog every time.
	SetPathName(newName);
	ASSERT(m_strPathName == newName);       // must be set

	pMainFrame->AddStrLogToOutputWnd(_T("Skin has been saved."));
	
	EndWaitCursor();
	return TRUE;
}

void CMyRainmeterDoc::UpdateAllViews( CView* pSender, LPARAM lHint /* = 0L */, CObject* pHint /* = NULL */ )
{
	m_Text="";
	m_Text+=m_Rainmeter.ToString();
	m_Text+=m_MeterData.ToString();
	for (int i = 0; i < m_arrItems.GetSize(); i++)
	{
		CRmControl* pRmCtrl = (CRmControl* )m_arrItems[i];
		m_Text += pRmCtrl->ToString();		
	}
	CMyRainmeterTextView* pTextView = GetTextView();
	if (pTextView)
	{
		pTextView->SetText(m_Text);
	}	
	__super::UpdateAllViews(pSender, lHint, pHint);	
}


CMyRainmeterTextView* CMyRainmeterDoc::GetTextView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView( pos );
		if (pView->IsKindOf(RUNTIME_CLASS(CMyRainmeterTextView)))
		{
			return (CMyRainmeterTextView* )pView;			
		}
	}
	return NULL;
}


#endif //_DEBUG


// CMyRainmeterDoc ����
