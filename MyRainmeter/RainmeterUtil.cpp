#include "StdAfx.h"
#include "RainmeterUtil.h"


CRainmeterUtil::CRainmeterUtil(void)
{
}


CRainmeterUtil::~CRainmeterUtil(void)
{
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, CString strValue, CString strComment )
{	
	CString sTemp;
	if (strKey.IsEmpty()|| strValue.IsEmpty())
	{
		return L""; 
	}
	if (!strComment.IsEmpty())
	{
		sTemp.Append(L";"+strComment);		
		sTemp.Append(L"\r\n");
	}	
	sTemp.Append(strKey+L"="+strValue+"\r\n");
	return sTemp;
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, int intValue, CString strComment )
{
	CString intStr;
	intStr.Format(_T("%d"), intValue);
	return OrgKeyValuePair(strKey, intStr, strComment);
	/*if (strKey.IsEmpty())
	{
	return L""; 
	}
	if (!strComment.IsEmpty())
	{
	sTemp.Append(L";"+strComment);		
	sTemp.Append(L"\r\n");
	}	
	sTemp.Append(strKey+L"="+intStr+"\r\n");
	return sTemp;*/
}

CString CRainmeterUtil::OrgKeyValuePair( CString strKey, float floatValue, CString strComment )
{	
	CString floatStr;
	floatStr.Format(_T("%f"), floatValue);
	return OrgKeyValuePair(strKey, floatStr, strComment);	
}

//////////////////////////////////////////////////////////////////////////
/// ����Դ�ļ��м���ͼƬ
/// @param [in] pImage ͼƬָ��
/// @param [in] nResID ��Դ��
/// @param [in] lpTyp ��Դ����
//////////////////////////////////////////////////////////////////////////
bool CRainmeterUtil::LoadImageFromResource(IN CImage* pImage,
	IN UINT nResID, 
	IN LPCTSTR lpTyp)
{
	if ( pImage == NULL) return false;

	pImage->Destroy();

	// ������Դ
	HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
	if (hRsrc == NULL) return false;

	// ������Դ
	HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
	if (hImgData == NULL)
	{
		::FreeResource(hImgData);
		return false;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid    = ::LockResource(hImgData);

	LPSTREAM pStream = NULL;
	DWORD dwSize    = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
	HGLOBAL hNew    = ::GlobalAlloc(GHND, dwSize);
	LPBYTE lpByte    = (LPBYTE)::GlobalLock(hNew);
	::memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);

	// ��ָ���ڴ洴��������
	HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
	if ( ht != S_OK )
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);

		GlobalFree(hNew);
	}

	// �ͷ���Դ
	::FreeResource(hImgData);

	return true;
}