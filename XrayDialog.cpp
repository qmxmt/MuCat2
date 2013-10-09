// XrayDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "XrayDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXrayDialog dialog


CXrayDialog::CXrayDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CXrayDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXrayDialog)
	m_Current = 0.0f;
	m_Filter = 0.0f;
	m_Voltage = 0.0f;
	m_PepperCheck = FALSE;
	m_PepperThreshold = 0;
	m_Issue = 0;
	//}}AFX_DATA_INIT
}


void CXrayDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXrayDialog)
	DDX_Text(pDX, IDC_CURRENT, m_Current);
	DDV_MinMaxFloat(pDX, m_Current, 0.f, 100.f);
	DDX_Text(pDX, IDC_FILTER, m_Filter);
	DDV_MinMaxFloat(pDX, m_Filter, 0.f, 100.f);
	DDX_Text(pDX, IDC_VOLTAGE, m_Voltage);
	DDV_MinMaxFloat(pDX, m_Voltage, 0.f, 1000.f);
	DDX_Check(pDX, IDC_PEPPERCHECK, m_PepperCheck);
	DDX_Text(pDX, IDC_EDITPEPPER, m_PepperThreshold);
	DDV_MinMaxInt(pDX, m_PepperThreshold, 0, 32767);
	DDX_Text(pDX, IDC_ISSUE, m_Issue);
	DDV_MinMaxInt(pDX, m_Issue, 0, 32767);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXrayDialog, CDialog)
	//{{AFX_MSG_MAP(CXrayDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXrayDialog message handlers


