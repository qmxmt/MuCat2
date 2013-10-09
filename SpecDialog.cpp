// SpecDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "SpecDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpecDialog dialog


CSpecDialog::CSpecDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecDialog)
	m_Comment = _T("");
	m_Description = _T("");
	m_Owner = _T("");
	m_User = _T("");
	//}}AFX_DATA_INIT
}


void CSpecDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecDialog)
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	DDV_MaxChars(pDX, m_Comment, 31);
	DDX_Text(pDX, IDC_DESCRIPTION, m_Description);
	DDV_MaxChars(pDX, m_Description, 31);
	DDX_Text(pDX, IDC_OWNER, m_Owner);
	DDV_MaxChars(pDX, m_Owner, 20);
	DDX_Text(pDX, IDC_USER, m_User);
	DDV_MaxChars(pDX, m_User, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpecDialog, CDialog)
	//{{AFX_MSG_MAP(CSpecDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecDialog message handlers
