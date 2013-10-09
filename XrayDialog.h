#if !defined(AFX_XRAYDIALOG_H__20297863_F0C4_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_XRAYDIALOG_H__20297863_F0C4_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// XrayDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXrayDialog dialog

class CXrayDialog : public CDialog
{
// Construction
public:
	CXrayDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXrayDialog)
	enum { IDD = IDD_XRAY_DIALOG };
	float	m_Current;
	float	m_Filter;
	float	m_Voltage;
	BOOL	m_PepperCheck;
	int		m_PepperThreshold;
	short	m_Issue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXrayDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXrayDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRAYDIALOG_H__20297863_F0C4_11D1_A406_0000010049AB__INCLUDED_)
