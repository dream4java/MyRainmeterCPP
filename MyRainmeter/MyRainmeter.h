
// MyRainmeter.h : MyRainmeter Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyRainmeterApp:
// �йش����ʵ�֣������ MyRainmeter.cpp
//

class CMyRainmeterApp : public CWinAppEx
{
public:
	CMyRainmeterApp();
	~CMyRainmeterApp();

public:
	CMultiDocTemplate* m_pTemplateTxt;
	CString m_SkinFolder;

protected:
	ULONG_PTR m_gdiplusToken;  

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();	
	afx_msg void OnFileNewConfig();
	afx_msg void OnFileNewSkin();
	afx_msg void OnFileOpenSkin();
	afx_msg void OnFileOpenConfig();

	DECLARE_MESSAGE_MAP()
};

extern CMyRainmeterApp theApp;
