// Meter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyRainmeter.h"
#include "Meter.h"


// CMeter

IMPLEMENT_DYNAMIC(CMeter, CRmControl)

CMeter::CMeter()
{
	m_X = m_Y = 0;
//	m_W = m_H = 0;
	m_Hidden = 0;
	

}

CMeter::~CMeter()
{
}


BEGIN_MESSAGE_MAP(CMeter, CRmControl)
END_MESSAGE_MAP()



// CMeter ��Ϣ�������


