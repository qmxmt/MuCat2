#pragma once


// CXrayRestartDialog dialog

class CXrayRestartDialog : public CDialog
{
	DECLARE_DYNAMIC(CXrayRestartDialog)

public:
	CXrayRestartDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CXrayRestartDialog();

// Dialog Data
	enum { IDD = IDD_XRAYRESTART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Shutdown;
	BOOL m_Wait45;
};
