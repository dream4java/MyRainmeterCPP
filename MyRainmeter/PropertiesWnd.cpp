
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MyRainmeter.h"
#include "MyRainmeterDoc.h"
#include "MyPropertyGridProterty.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar ��Ϣ�������

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ���������� \n");
		return -1;      // δ�ܴ���
	}

//	m_wndObjectCombo.AddString(_T("Ӧ�ó���"));
	m_wndObjectCombo.AddString(_T("���Դ���"));
	m_wndObjectCombo.SetCurSel(0);
//	m_wndPropList.SetListDelimiter(',');
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}
	isExpandAll = FALSE;
	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* ������*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* ����*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	isExpandAll = !isExpandAll;
	m_wndPropList.ExpandAll(isExpandAll);	
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
	
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: �ڴ˴���������������
	// ���Ե������
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
	
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: �ڴ˴���������������
	// �¼������磩�������
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: �ڴ˴����������� UI ����������
	
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();
	
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();	
	
	
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("����, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));
	
	pGroup2->AddSubItem(new CMyPropertyGridActionProterty(_T("testAction"), _T("Test action"))); 
	//ARGB
	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	pGroup2->AddSubItem(pColorProp);

	m_wndPropList.AddProperty(pGroup2); 

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250, _T("ָ�����ڵĸ߶�"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("���"), (_variant_t) 150, _T("ָ�����ڵĿ��"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);


	m_wndPropList.AddProperty(pSize);
	
	//LoadRainmeterSection();
	//LoadMeterDataSection();


	/*pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T("����"), _T("ָ�����ڱ���������ʾ���ı�")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250l, _T("ָ�����ڵĸ߶�"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("���"), (_variant_t) 150l, _T("ָ�����ڵĿ��"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));
	
	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("����, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("����"));
	pProp = new CMFCPropertyGridProperty(_T("(����)"), _T("Ӧ�ó���"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	pColorProp->EnableOtherButton(_T("����..."));
	pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("ͼ���ļ�(*.ico)|*.ico|�����ļ�(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("ָ������ͼ��")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ļ���"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("��νṹ"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("��һ���Ӽ�"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�ڶ����Ӽ�"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 1"), (_variant_t) _T("ֵ 1"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 2"), (_variant_t) _T("ֵ 2"), _T("��Ϊ˵��")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 3"), (_variant_t) _T("ֵ 3"), _T("��Ϊ˵��")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);*/

	
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::LoadRainmeterSection()
{
	// GetDocument 
	CMyRainmeterDoc* pDoc = GetDocument();
	if (pDoc==NULL)
	{
		return;
	}
	// Get Rainmeter section data
	CRainmeter* pRainmeter = &(pDoc->m_Rainmeter);
	CMFCPropertyGridProperty* pRainmeterGridProp = new CMFCPropertyGridProperty(_T("Rainmeter"));
	
	/************ General Options Area STart **************************/
	CMFCPropertyGridProperty* pRmGeneral = new CMFCPropertyGridProperty(_T("��ͨѡ��"));

	pRmGeneral->AddSubItem(new CMFCPropertyGridProperty(_T("Update"), (_variant_t) pRainmeter->m_Update, _T("Ϊmeter��measure�趨�˸�������,��λ�Ǻ���,Ĭ����1000����1��,�趨Ϊ-1�Ļ������Զ�����Ƥ��,ֻ����Ƥ�����ػ����ֶ�ˢ�µ�ʱ��Ż����")));
	pRmGeneral->AddSubItem(new CMFCPropertyGridProperty(_T("TransitionUpdate"), (_variant_t) pRainmeter->m_TransitionUpdate, _T("Defines the update time in milliseconds for meter transitions. While a transition is active the meter will update at this rate. Currently, only the Bitmap meter supports meter transitions")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("DynamicWindowSize"), pRainmeter->m_DynamicWindowSize, _T("�������Ϊ1�����ڻ���ÿ�θ��µ�ʱ���������ӦMeters"));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pRmGeneral->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("ToolTipHidden"), pRainmeter->m_ToolTipHidden, _T("�������Ϊ1�����е���ʾ���ᱻ����"));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pRmGeneral->AddSubItem(pProp);

	CMFCPropertyGridProperty* pDragMargin = new CMFCPropertyGridProperty(_T("DragMargins"), pRainmeter->m_DragMargins, _T("�����ڿ����϶���,�����趨����,�����ĸ�ֵ����ʹ��,��������˲����϶�������,�������ʹ�ø�ֵ������: DragMargins=0,-100,0,0"));
	pRmGeneral->AddSubItem(pDragMargin);
	
	static const TCHAR szFilter[] = _T("�����ļ�(*.*)|*.*||");

	CMFCPropertyGridProperty* pAction = new CMyPropertyGridActionProterty(_T("OnRefreshAction"), pRainmeter->m_OnRefreshAction, _T("Action to execute when the skin is loaded or refreshed."));		
	pRmGeneral->AddSubItem(pAction);

	pAction = new CMyPropertyGridActionProterty(_T("OnUpdateAction"), pRainmeter->m_OnUpdateAction, _T("Action to execute on each Update of the skin."));	
	pRmGeneral->AddSubItem(pAction);

	pAction = new CMyPropertyGridActionProterty(_T("OnCloseAction"), pRainmeter->m_OnCloseAction, _T("Action to execute when the skin is unloaded or when Rainmeter is closed."));	
	pRmGeneral->AddSubItem(pAction);	
	
	pAction = new CMyPropertyGridActionProterty(_T("OnFocusAction"), pRainmeter->m_OnFocusAction, _T("Action to execute when the skin recieves focus in Windows (set by clicking the mouse on the skin)."));	
	pRmGeneral->AddSubItem(pAction);	

	pAction = new CMyPropertyGridActionProterty(_T("OnUnfocusAction"), pRainmeter->m_OnUnfocusAction,  _T("Action to execute when the skin loses focus in Windows."));	
	pRmGeneral->AddSubItem(pAction);	

	pRainmeterGridProp->AddSubItem(pRmGeneral);
	/************ General Options Area End **************************/

	/************ BackGround Options Area Start **************************/
	CMFCPropertyGridProperty* pRmBackground = new CMFCPropertyGridProperty(_T("����ѡ��"));

	static const TCHAR imgFilter[] = _T("jpeg�ļ�(*.jpg)|*.jpg|png�ļ�(*.png)|*.png|bmp�ļ�(*.bmp)|*.bmp||");
	pProp  = new CMFCPropertyGridFileProperty(_T("Background"), TRUE, pRainmeter->m_Background, _T(""), 0, imgFilter, _T("Path of a background image file."));
	pRmBackground->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("BackgroundMode"), pRainmeter->m_BackgroundMode, _T("Defines the background mode for the skin"));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));	
	pProp->AddOption(_T("3"));	
	pProp->AddOption(_T("4"));	
	pProp->AllowEdit(FALSE);
	pRmBackground->AddSubItem(pProp);

	CMFCPropertyGridProperty* pBgMargin = new CMFCPropertyGridProperty(_T("DragMargins"), pRainmeter->m_DragMargins, _T("If BackgroundMode=3, defines margins of the Background image that are not scaled. The parameters are left,top,right,bottom. "));
	pRmBackground->AddSubItem(pBgMargin);

	CMFCPropertyGridProperty* pSolidColor = new CMFCPropertyGridProperty(_T("SolidColor"), pRainmeter->m_SolidColor, _T("This option will specify the background color when BackgroundMode=2. If SolidColor2 is also specified, the background is a gradient composed of SolidColor and SolidColor2."));
	pRmBackground->AddSubItem(pSolidColor);

	pRmBackground->AddSubItem(new CMFCPropertyGridProperty(_T("GradientAngle"), (_variant_t) pRainmeter->m_GradientAngle, _T("Angle of the gradient in degrees (for SolidColor and SolidColor2) when BackgroundMode=2.")));

	pProp = new CMFCPropertyGridProperty(_T("BevelType"), pRainmeter->m_BevelType, _T("If enabled, draws a bevel around the edges of the entire skin when BackgroundMode=2. Valid values are: {0: No bevel 1: Raised 2: Sunken}"));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AddOption(_T("2"));	
	pProp->AllowEdit(FALSE);
	pRmBackground->AddSubItem(pProp);

	pRainmeterGridProp->AddSubItem(pRmBackground);
	/************ BackGround Options Area End **************************/

	/************ Context Options Area Start **************************/
	CMFCPropertyGridProperty* pRmContext = new CMFCPropertyGridProperty(_T("������ѡ��"));
	pRmContext->AddSubItem(new CMFCPropertyGridProperty(_T("ContextTitle"), _T(""), _T("If not blank, adds an item to the skin's context menu under \"Custom skin actions\". ")));
	pRmContext->AddSubItem(new CMFCPropertyGridProperty(_T("ContextAction"), _T(""), _T("Action triggered by clicking the corresponding ContextTitleN item.")));
	pRainmeterGridProp->AddSubItem(pRmContext);
	/************ Context Options Area End ****************************/

	/************ Blur Options Area Start **************************/
	CMFCPropertyGridProperty* pRmBlur = new CMFCPropertyGridProperty(_T("ģ��ѡ��"));
	pProp = new CMFCPropertyGridProperty(_T("Blur"), pRainmeter->m_Blur, _T("Set to 1 to enable Aero Blur on Windows Vista or later operating systems. "));
	pProp->AddOption(_T("0"));	
	pProp->AddOption(_T("1"));	
	pProp->AllowEdit(FALSE);
	pRmBlur->AddSubItem(pProp);
	pRmBlur->AddSubItem(new CMFCPropertyGridProperty(_T("BlurRegion"), _T(""), _T("Defines areas and shapes of the one or more regions of the skin to be blurred. ")));
	pRainmeterGridProp->AddSubItem(pRmBlur);
	/************ Blur Options Area End ****************************/

	m_wndPropList.AddProperty(pRainmeterGridProp);
}


void CPropertiesWnd::LoadMeterDataSection()
{
	CMyRainmeterDoc* pDoc = GetDocument();
	if (pDoc==NULL)
	{
		return;
	}
	CMetadata* pMeterData = &(pDoc->m_MeterData);
	CMFCPropertyGridProperty* pMeterDataGridProp = new CMFCPropertyGridProperty(_T("MeterData"));
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Name"), pMeterData->m_Name, _T("The name of the skin."));
	pMeterDataGridProp->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Author"), pMeterData->m_Author, _T("The author of the skin."));
	pMeterDataGridProp->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Information"), pMeterData->m_Information, _T("A description of the skin, setup and usage instructions, credits, or other documentation elements. Use | for line breaks."));
	pMeterDataGridProp->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("Version"), pMeterData->m_Version, _T("The version of the skin."));
	pMeterDataGridProp->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("License"), pMeterData->m_License, _T("The name of a standard license or explicit permissions and conditions for ports, mods and derivative works."));
	pMeterDataGridProp->AddSubItem(pProp);

	m_wndPropList.AddProperty(pMeterDataGridProp);
}

// Set the current object's properties
void CPropertiesWnd::SetCurObjProperties( CRmControl* pRmCtrl )
{
	if (pRmCtrl == NULL)
	{			
		m_wndPropList.RemoveAll();
		LoadRainmeterSection();
		LoadMeterDataSection();
	}
	else
	{		
		m_wndPropList.RemoveAll();		
		pRmCtrl->InitProperties(&m_wndPropList);
	}
	
}

LRESULT CPropertiesWnd::OnPropertyChanged( WPARAM,LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	
	CMyRainmeterDoc* pDoc = GetDocument();
	if(pDoc==NULL)return NULL;

	CRmControl* pCurRmCtrl = pDoc->m_pCurRmCtrl;
	if(pCurRmCtrl != NULL)
		pCurRmCtrl->PropertyChanged(pProp);
	
	return 0;
}

// Get the Active Document
CMyRainmeterDoc* CPropertiesWnd::GetDocument()
{
	CMDIChildWnd * pChild =
		((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

	if ( !pChild )
		return NULL;

	CDocument * pDoc = pChild->GetActiveDocument();

	if ( !pDoc )
		return NULL;

	// Fail if doc is of wrong kind
	if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CMyRainmeterDoc) ) )
		return NULL;
	return (CMyRainmeterDoc*)pDoc;
}


