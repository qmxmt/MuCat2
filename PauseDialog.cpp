// PauseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "PauseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPauseDialog dialog


CPauseDialog::CPauseDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPauseDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPauseDialog)
	m_Pause = FALSE;
	m_KillTheta = FALSE;
	m_KillZ = FALSE;
	//}}AFX_DATA_INIT
}


void CPauseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPauseDialog)
	DDX_Check(pDX, IDC_CHECKPAUSE, m_Pause);
	DDX_Check(pDX, IDC_KILLTHETA, m_KillTheta);
	DDX_Check(pDX, IDC_KILLZ, m_KillZ);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPauseDialog, CDialog)
	//{{AFX_MSG_MAP(CPauseDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPauseDialog message handlers
