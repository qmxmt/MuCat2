// XrayRestartDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "XrayRestartDialog.h"


// CXrayRestartDialog dialog

IMPLEMENT_DYNAMIC(CXrayRestartDialog, CDialog)
CXrayRestartDialog::CXrayRestartDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CXrayRestartDialog::IDD, pParent)
	, m_Shutdown(FALSE)
	, m_Wait45(FALSE)
{
}

CXrayRestartDialog::~CXrayRestartDialog()
{
}

void CXrayRestartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_XRAYRESTART, m_Shutdown);
	DDX_Check(pDX, IDC_WAIT45, m_Wait45);
}


BEGIN_MESSAGE_MAP(CXrayRestartDialog, CDialog)
END_MESSAGE_MAP()


// CXrayRestartDialog message handlers
