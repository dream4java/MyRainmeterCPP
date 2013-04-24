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
		pStream->Release();
	}

	// �ͷ���Դ
	::FreeResource(hImgData);

	return true;
}

bool CRainmeterUtil::LoadImageFromResource( IN Gdiplus::Image* & pImage, IN UINT nResID, IN LPCTSTR lpTyp/*=_T("PNG")*/ )
{
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
		pImage = Gdiplus::Image::FromStream(pStream);		
		GlobalFree(hNew);
		pStream->Release();
	}

	// �ͷ���Դ
	::FreeResource(hImgData);

	return true;
}

COLORREF CRainmeterUtil::ParseColor2RGBA( CString colorStr )
{
	int nA = 0,nR = 0, nG = 0, nB = 0; 
	_stscanf_s(colorStr, _T("%3d,%3d,%3d,%3d"), &nR, &nG, &nB, &nA);
	if(nA == 0 && (nR !=0 || nG != 0 || nB !=  0))
		nA = 0xFF;
	return RGBA(nR, nG, nB, nA);
}

COLORREF CRainmeterUtil::ParseColor2RGB( CString colorStr )
{
	int nA = 0,nR = 0, nG = 0, nB = 0;
	_stscanf_s(colorStr, _T("%3d,%3d,%3d,%3d"), &nR, &nG, &nB, &nA);
	
	return RGB(nR, nG, nB);
}

bool CRainmeterUtil::ChooseFolder( HWND hParent, const CString& title, CString& folder )
{
	bool success = false;

	BROWSEINFO bi;
	::ZeroMemory(&bi, sizeof(bi));
	LPTSTR pBuffer = folder.GetBuffer(MAX_PATH);

	bi.hwndOwner = hParent;
	bi.pszDisplayName = pBuffer;
	bi.lpszTitle = title;
	bi.pidlRoot = 0;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | 
		BIF_NEWDIALOGSTYLE;

	LPITEMIDLIST pItem = ::SHBrowseForFolder(&bi);
	if (pItem != NULL)
	{
		::SHGetPathFromIDList(pItem, pBuffer);
		success = true;

		CComPtr<IMalloc> pMalloc;
		if (SUCCEEDED(::SHGetMalloc(&pMalloc)))
			pMalloc->Free(pItem);
	}

	folder.ReleaseBuffer();
	return success;
}

//
//void CRainmeterUtil::GreyscaleImage( IN Gdiplus::Image* & pImage, OUT Gdiplus::Image* pGrayImage )
//{	
//	Gdiplus::Image *img = pImage->Clone();
//	ImageAttributes imageAttributes;
//	ColorMatrix colorMatrix ={
//		0.299f, 0.299f, 0.299f, 0, 0,
//		0.588f, 0.588f, 0.588f, 0, 0,
//		0.111f, 0.111f, 0.111f, 0, 0,
//		0, 0, 0, 1, 0 ,
//		0, 0, 0, 0, 1
//	};
//	imageAttributes.SetColorMatrix(
//		&colorMatrix, 
//		ColorMatrixFlagsDefault,
//		ColorAdjustTypeBitmap);
//	Graphics g(img);
//	g.DrawImage(
//		pImage, 
//		Rect(0,0,pImage->GetWidth(), pImage->GetHeight()), 
//		0, 0, 
//		pImage->GetWidth(), 
//		pImage->GetHeight(), 
//		UnitPixel, 
//		&imageAttributes
//	);
//}
//
