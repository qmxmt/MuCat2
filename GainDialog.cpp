// GainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "GainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGainDialog dialog



CGainDialog::CGainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGainDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGainDialog)
	m_Gain = 0;
	//}}AFX_DATA_INIT
}


void CGainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGainDialog)
	DDX_Text(pDX, IDC_GAINGAIN, m_Gain);
	DDV_MinMaxUInt(pDX, m_Gain, 0, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGainDialog, CDialog)
	//{{AFX_MSG_MAP(CGainDialog)
	ON_EN_CHANGE(IDC_GAINGAIN, OnChangeGaingain)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGainDialog message handlers

BOOL CGainDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSpinButtonCtrl *pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_GAINGAINSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_GAINGAIN));
	pSpin->SetRange(0, 3);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*void CGainDialog::OnPaint() 
{
	CWnd* pWnd = GetDlgItem(IDC_GAINELECTRON);
	CDC* pDC = pWnd->GetDC();
	int IGain,ISpeed;
	float Gain;
	CString Text;
	IGain=GetDlgItemInt(IDC_GAINGAIN);
	ISpeed=GetDlgItemInt(IDC_GAINSPEED);
	Gain = Camera.GetGain(IGain,ISpeed);
	Text.Format("%4.1f electrons/level",Gain);
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(0,0,Text);

}*/



void CGainDialog::OnChangeGaingain() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
//	Paint();
}




/*void CGainDialog::OnChangeGainspeed() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_CHANGE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
//	Paint();
}*/


/*void CGainDialog::Paint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CWnd* pWnd = GetDlgItem(IDC_GAINELECTRON);
	pWnd->Invalidate();
	pWnd->UpdateWindow();
//	OnPaint();
	
	// Do not call CDialog::OnPaint() for painting messages
}*/
