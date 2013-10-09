// ZoomDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "ZoomDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog


CZoomDialog::CZoomDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CZoomDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDialog, CDialog)
	//{{AFX_MSG_MAP(CZoomDialog)
	ON_BN_CLICKED(IDC_ZOOM25, OnZoom25)
	ON_BN_CLICKED(IDC_ZOOM33, OnZoom33)
	ON_BN_CLICKED(IDC_ZOOM50, OnZoom50)
	ON_BN_CLICKED(IDC_ZOOM100, OnZoom100)
	ON_BN_CLICKED(IDC_ZOOM200, OnZoom200)
	ON_BN_CLICKED(IDC_ZOOM300, OnZoom300)
	ON_BN_CLICKED(IDC_ZOOM400, OnZoom400)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog message handlers

BOOL CZoomDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(m_Zoom)
	{
		case 3:
			CheckDlgButton(IDC_ZOOM25, 1);
			break;
		case 4:
			CheckDlgButton(IDC_ZOOM33, 1);
			break;
		case 6:
			CheckDlgButton(IDC_ZOOM50, 1);
			break;
		case 12:
			CheckDlgButton(IDC_ZOOM100, 1);
			break;
		case 24:
			CheckDlgButton(IDC_ZOOM200, 1);
			break;
		case 36:
			CheckDlgButton(IDC_ZOOM300, 1);
			break;
		case 48:
			CheckDlgButton(IDC_ZOOM400, 1);
			break;
		default:
			CheckDlgButton(IDC_ZOOM100, 1);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZoomDialog::OnZoom25() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 3;
}

void CZoomDialog::OnZoom33() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 4;
}

void CZoomDialog::OnZoom50() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 6;
}

void CZoomDialog::OnZoom100() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 12;
}

void CZoomDialog::OnZoom200() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 24;
}

void CZoomDialog::OnZoom300() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 36;
}

void CZoomDialog::OnZoom400() 
{
	// TODO: Add your control notification handler code here
	m_Zoom = 48;
}
