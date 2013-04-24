#include "StdAfx.h"
#include "Rainmeter.h"
#include "RainmeterUtil.h"


CRainmeter::CRainmeter(void)
{
	m_Update=1000;
	m_DynamicWindowSize=L"0";
	m_DragMargins=L"0,0,0,0";
	m_OnRefreshAction=L"";
	m_OnUpdateAction=L"";
	m_OnCloseAction=L"";
	m_OnFocusAction=L"";
	m_OnUnfocusAction=L"";
	m_TransitionUpdate=100;
	m_ToolTipHidden=L"0";

	m_ImageCrop=L"";
	m_Greyscale=L"0";
	//m_ImageTint=L"255,255,255,255";
	m_ImageAlpha=255;
	//m_ImageFlip=L"None";
	m_ImageRotate=0.0;
	m_GradientAngle=0;
}


CRainmeter::~CRainmeter(void)
{
}

CString CRainmeter::ToString() const
{
	CString sTemp;
	sTemp.Append(_T(";这是由MyRainmeter程序生成的用于桌面美化工具Rainmeter的配置文件\r\n"));
	sTemp.Append(_T("\r\n"));
	sTemp.Append(_T(";Rainmeter\r\n"));
	// Section name
	sTemp.Append(_T("[Rainmeter]\r\n"));	
	// General options
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Update"), m_Update, _T("更新周期")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("DynamicWindowSize"), m_DynamicWindowSize, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("DragMargins"), m_DragMargins, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnRefreshAction"), m_OnRefreshAction, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnUpdateAction"), m_OnUpdateAction, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnCloseAction"), m_OnCloseAction, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnFocusAction"), m_OnFocusAction, _T("")));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("OnUnfocusAction"), m_OnUnfocusAction, _T("")));

	// General Image Options
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Greyscale"), m_Greyscale));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageTint"), m_ImageTint));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageAlpha"), m_ImageAlpha));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageFlip"), m_ImageFlip));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageRotate"), m_ImageRotate));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("ImageCrop"), m_ColorMatrix));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Background"), m_Background));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("BackgroundMode"), m_BackgroundMode));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("BackgroundMargins"), m_BackgroundMargins));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("SolidColor"), m_SolidColor));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("GradientAngle"), m_GradientAngle));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("BevelType"), m_BevelType));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("m_ContextTitle"), m_ContextTitle));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("m_ContextAction"), m_ContextAction));
	sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("Blur"), m_Blur));
	//sTemp.Append(CRainmeterUtil::OrgKeyValuePair(_T("m_BlurRegion"), m_BlurRegion));
	sTemp.Append(L"\r\n");
	return sTemp;
}

CMetadata::CMetadata()
{
	m_Name=L"MyRainmeter Skin";
	m_Author=L"MyRainmeter.exe";
	m_Version=L"1.0";
	m_Information=_T("This is a Rainmeter configuration file generated by MyRainmeter.exe");
}

CMetadata::~CMetadata()
{

}

CString CMetadata::ToString() const
{
	CString sTemp;		
	sTemp.Append(_T(";Metadata\r\n"));
	// Section name
	sTemp.Append(_T("[MetaData]\r\n"));
	sTemp += CRainmeterUtil::OrgKeyValuePair(L"Name", m_Name, L"");
	sTemp += CRainmeterUtil::OrgKeyValuePair(L"Author", m_Author, L"");
	sTemp += CRainmeterUtil::OrgKeyValuePair(L"Information", m_Information, L"");
	sTemp += CRainmeterUtil::OrgKeyValuePair(L"Version", m_Version, L"");
	sTemp += CRainmeterUtil::OrgKeyValuePair(L"License", m_License, L"");
	sTemp.Append(L"\r\n");
	return sTemp;
}
