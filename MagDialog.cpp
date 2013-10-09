// MagDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "MagDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMagDialog dialog


CMagDialog::CMagDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMagDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMagDialog)
	m_MagFactor = 0.0;
	//}}AFX_DATA_INIT
}


void CMagDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMagDialog)
	DDX_Text(pDX, IDC_PARAMETERMAG, m_MagFactor);
	DDV_MinMaxDouble(pDX, m_MagFactor, 0.3, 2.5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMagDialog, CDialog)
	//{{AFX_MSG_MAP(CMagDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMagDialog message handlers
