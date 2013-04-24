
// MyRainmeter.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MyRainmeter.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MyRainmeterDoc.h"
#include "MyRainmeterGraphView.h"
#include "MyRainmeterTextView.h"


#include <AFXPRIV.H>
#include "RainmeterUtil.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyRainmeterApp

BEGIN_MESSAGE_MAP(CMyRainmeterApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMyRainmeterApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	//�½������ļ�
	ON_COMMAND(ID_FILE_NEW_CONFIG, &CMyRainmeterApp::OnFileNewConfig)
	//�½�Ƥ��
	ON_COMMAND(ID_FILE_NEW_SKIN, &CMyRainmeterApp::OnFileNewSkin)
	// ��Ƥ��	
	ON_COMMAND(ID_FILE_OPEN_SKIN, &CMyRainmeterApp::OnFileOpenSkin)
	// �������ļ�
	ON_COMMAND(ID_FILE_OPEN_CONFIG, &CMyRainmeterApp::OnFileOpenConfig)
END_MESSAGE_MAP()


// CMyRainmeterApp ����

CMyRainmeterApp::CMyRainmeterApp()
{
	// Startup GDI+
	GdiplusStartupInput input;  
	GdiplusStartup(&m_gdiplusToken, &input, NULL); 

	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MyRainmeter.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// ��������
CMyRainmeterApp::~CMyRainmeterApp()
{
	// Shutdown GDI+
	GdiplusShutdown(m_gdiplusToken);  
}


// Ψһ��һ�� CMyRainmeterApp ����

CMyRainmeterApp theApp;


// CMyRainmeterApp ��ʼ��

BOOL CMyRainmeterApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("�ҵ����Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MyRainmeterTYPE,
		RUNTIME_CLASS(CMyRainmeterDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CMyRainmeterGraphView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	m_pTemplateTxt = new CMultiDocTemplate(IDR_MyRainmeterTYPE,
		RUNTIME_CLASS(CMyRainmeterDoc),
		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
		RUNTIME_CLASS(CMyRainmeterTextView));
	if (!m_pTemplateTxt)
		return FALSE;
	
	// ������ MDI ��ܴ���
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	// Dispatch commands specified on the command line
	
	ParseCommandLine(cmdInfo);
	
	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// �������ѳ�ʼ���������ʾ����������и���
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


int CMyRainmeterApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMyRainmeterApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMyRainmeterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMyRainmeterApp �Զ������/���淽��

void CMyRainmeterApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);	
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_GRAPH);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMyRainmeterApp::LoadCustomState()
{
}

void CMyRainmeterApp::SaveCustomState()
{
}

// CMyRainmeterApp ��Ϣ�������


void CMyRainmeterApp::OnFileOpenSkin()
{
	// TODO: �ڴ���������������
	CString folder;
	if(CRainmeterUtil::ChooseFolder(m_pMainWnd->m_hWnd, _T("ѡ���ļ���"), folder))
	{
		m_SkinFolder = folder;		
		CMainFrame* pMainFrame = (CMainFrame* )AfxGetMainWnd();
		CFileView* pFileView = pMainFrame->GetFileView();
		pFileView->OnRefresh();
		pMainFrame=NULL;
		pFileView=NULL;
	}
}

void CMyRainmeterApp::OnFileOpenConfig()
{
	// TODO: �ڴ���������������
	CWinAppEx::OnFileOpen();
}


void CMyRainmeterApp::OnFileNewConfig()
{
	// TODO: �ڴ���������������
	POSITION tFirstDocTemplatePos = theApp.m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate* pBitmapViewDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tFirstDocTemplatePos);
	pBitmapViewDocTemplate->OpenDocumentFile(NULL);
	
	//CWinAppEx::OnFileNew();
}


void CMyRainmeterApp::OnFileNewSkin()
{
	// TODO: �ڴ���������������
	CString folder;
	if(CRainmeterUtil::ChooseFolder(m_pMainWnd->m_hWnd, _T("ѡ���ļ���"), folder))
	{
		//m_SkinFolder += L"\\MyRainmeterSkin";		
		PathCombine(m_SkinFolder.GetBuffer(MAX_FILENAME_LENGTH), folder, L"MyRainmeterSkin");
		
		if(PathIsDirectory(m_SkinFolder))  
		{
			AfxMessageBox(_T("MyRainmeterSkinĿ¼�Ѵ��ڣ���ѡ������Ŀ¼"));
		}
		else	
		{
			if (CreateDirectory(m_SkinFolder, NULL))	
			{
				CString resFolder, fontFolder, imgFolder,cursorFolder;
				
				// Create resources folder
				PathCombine(resFolder.GetBuffer(MAX_FILENAME_LENGTH), m_SkinFolder, L"@Resources");				
				CreateDirectory(resFolder, NULL);

				// Create font folder
				PathCombine(fontFolder.GetBuffer(MAX_FILENAME_LENGTH), resFolder, L"font");
				CreateDirectory(fontFolder, NULL);

				// Create image folder
				PathCombine(imgFolder.GetBuffer(MAX_FILENAME_LENGTH), resFolder, L"image");
				CreateDirectory(imgFolder, NULL);

				// Create cursor folder
				PathCombine(cursorFolder.GetBuffer(MAX_FILENAME_LENGTH), resFolder, L"cursor");
				CreateDirectory(cursorFolder, NULL);
				
				CMainFrame* pMainFrame = (CMainFrame* )AfxGetMainWnd();
				CFileView* pFileView = pMainFrame->GetFileView();
				pFileView->OnRefresh();
				pMainFrame=NULL;
				pFileView=NULL;
			}
			else
			{
				AfxMessageBox(_T("�ܱ�Ǹ������Ŀ¼ʧ�ܣ������ԣ�"));
			}
		}
		//AfxMessageBox(m_SkinFolder);
	}
	
}


//void CMyRainmeterApp::OnFileNew()
//{
//	// TODO: �ڴ���������������
//	//for(POSITION tPos = theApp.m_pDocManager->GetFirstDocTemplatePosition();tPos!=NULL;)
//	//{
//	//	//get pointer to the CdocTemplates.
//	//	CDocTemplate * ptempDocTemplate = 
//	//		theApp.m_pDocManager->GetNextDocTemplate (tPos);
//	//	//this will make the view visible.
//	//	ptempDocTemplate->OpenDocumentFile(NULL);
//	//}	
//	POSITION tFirstDocTemplatePos = theApp.m_pDocManager->GetFirstDocTemplatePosition();
//	CDocTemplate* pBitmapViewDocTemplate = theApp.m_pDocManager->GetNextDocTemplate(tFirstDocTemplatePos);
//	pBitmapViewDocTemplate->OpenDocumentFile(NULL);
//}



//void CAboutDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: �ڴ˴������Ϣ����������
//	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
//}







