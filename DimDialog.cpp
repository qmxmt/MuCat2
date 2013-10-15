// DimDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "DimDialog.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDimDialog dialog


CDimDialog::CDimDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDimDialog::IDD, pParent)
	, m_NumFrames(0)
{
	//{{AFX_DATA_INIT(CDimDialog)
	m_Height = 0;
	m_ScanLength = 0;
	m_NumProj = 0;
	m_NumBlocks = 0;
	m_Shift = 0;
	//}}AFX_DATA_INIT
}


void CDimDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDimDialog)
	DDX_Text(pDX, IDC_DIMHEIGHT, m_Height);
	DDV_MinMaxInt(pDX, m_Height, 10, m_MaxHeight);
	DDX_Text(pDX, IDC_DIMLENGTH, m_ScanLength);
	DDV_MinMaxInt(pDX, m_ScanLength, 32, 7000);
	DDX_Text(pDX, IDC_DIMPROJ, m_NumProj);
	DDV_MinMaxInt(pDX, m_NumProj, 1, 32000);
	DDX_Text(pDX, IDC_DIMBLOCKS, m_NumBlocks);
	DDV_MinMaxInt(pDX, m_NumBlocks, 1, 2000);
	DDX_Text(pDX, IDC_DIMAV, m_NumFrames);
	DDV_MinMaxInt(pDX, m_NumFrames, 1, 100);
	DDX_Text(pDX, IDC_DIMSHIFT, m_Shift);
	DDV_MinMaxInt(pDX, m_Shift, 0, 200000);
	DDX_Check(pDX, IDC_ROUNDCHECK, m_RoundCheck);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDimDialog, CDialog)
	//{{AFX_MSG_MAP(CDimDialog)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_DIMHEIGHT, OnChangeDimheight)
	ON_EN_CHANGE(IDC_DIMLENGTH, OnChangeDimlength)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ROUNDCHECK, &CDimDialog::OnBnClickedRoundcheck)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDimDialog message handlers

BOOL CDimDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	CSpinButtonCtrl *pSpin;
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMHEIGHTSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMHEIGHT));
	pSpin->SetRange(10, m_MaxHeight);
	
	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMLENGTHSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMLENGTH));
	pSpin->SetRange(32, 7000);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMPROJSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMPROJ));
	pSpin->SetRange(1, 32000);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMBLOCKSSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMBLOCKS));
	pSpin->SetRange(1, 2000);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMAVSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMAV));
	pSpin->SetRange(1, 100);

	pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_DIMSHIFTSPIN);
	pSpin->SetBuddy(GetDlgItem(IDC_DIMSHIFT));
//	pSpin->SetRange(1, 200000);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDimDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CWnd* pWnd = GetDlgItem(IDC_DIMMAXSLICES);
	CDC* pDC = pWnd->GetDC();
	double Phi;
	int MaxSlices;
	int Length, Height;
	CString Text;
	Length=GetDlgItemInt(IDC_DIMLENGTH);
	Height=GetDlgItemInt(IDC_DIMHEIGHT);
	if (m_Distance < 0.1)
		Text.Format("Geometry is not set!");
	else
	{
		Phi=atan2(Length/2, m_Distance);
		MaxSlices = int((1.0-sin(Phi))*Height);
		MaxSlices = (MaxSlices/2)*2;
		Text.Format("Maximum slices per block = %d",MaxSlices);
	}
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,0,0));
	pDC->TextOut(0,0,Text);
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDimDialog::OnChangeDimheight() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Paint();	
}

void CDimDialog::OnChangeDimlength() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Paint();
}

void CDimDialog::Paint()
{
	CWnd* pWnd = GetDlgItem(IDC_DIMMAXSLICES);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	OnPaint();
}





void CDimDialog::OnBnClickedRoundcheck()
{
	// TODO: Add your control notification handler code here
}
