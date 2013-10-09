// BinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "BinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinDialog dialog


CBinDialog::CBinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBinDialog)
	m_Bin = 0;
	//}}AFX_DATA_INIT
}


void CBinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBinDialog)
	DDX_Text(pDX, IDC_BINEDIT, m_Bin);
	DDV_MinMaxInt(pDX, m_Bin, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBinDialog, CDialog)
	//{{AFX_MSG_MAP(CBinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBinDialog message handlers

BOOL CBinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSpinButtonCtrl *pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_BINSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_BINEDIT));
	pSpin->SetRange(1, 10);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
