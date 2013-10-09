// StopDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "StopDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStopDialog dialog


CStopDialog::CStopDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStopDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStopDialog)
	//}}AFX_DATA_INIT
	m_Stopped = FALSE;
	Create(IDD_STOPDIALOG,AfxGetMainWnd());
}


void CStopDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStopDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStopDialog, CDialog)
	//{{AFX_MSG_MAP(CStopDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStopDialog message handlers

void CStopDialog::OnOK() 
{
	// TODO: Add extra validation here
	m_Stopped = TRUE;
	CDialog::OnOK();
}

