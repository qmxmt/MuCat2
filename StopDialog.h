#if !defined(AFX_STOPDIALOG_H__02660521_FB9E_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_STOPDIALOG_H__02660521_FB9E_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StopDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStopDialog dialog

class CStopDialog : public CDialog
{
// Construction
public:
	BOOL m_Stopped;
	CStopDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStopDialog)
	enum { IDD = IDD_STOPDIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStopDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStopDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOPDIALOG_H__02660521_FB9E_11D1_A406_0000010049AB__INCLUDED_)
