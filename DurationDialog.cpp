// DurationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "DurationDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDurationDialog dialog


CDurationDialog::CDurationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDurationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDurationDialog)
	m_Duration = 0;
	m_StillDuration = 0;
	//}}AFX_DATA_INIT
}


void CDurationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDurationDialog)
	DDX_Text(pDX, IDC_PARAMETER_DURATION, m_Duration);
	DDV_MinMaxInt(pDX, m_Duration, 3, 360);//Change back to 5$$$
	DDX_Text(pDX, IDC_PARAMETERSTILL, m_StillDuration);
	DDV_MinMaxInt(pDX, m_StillDuration, 1, 360);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDurationDialog, CDialog)
	//{{AFX_MSG_MAP(CDurationDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDurationDialog message handlers

BOOL CDurationDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSpinButtonCtrl *pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PARAMETERDURATIONSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_PARAMETER_DURATION));
	pSpin->SetRange(3, 360);//Change back to 5$$$
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_PARAMETERSTILLSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_PARAMETERSTILL));
	pSpin->SetRange(1, 360);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
