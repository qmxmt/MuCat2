#if !defined(AFX_PAUSEDIALOG_H__C540DD88_E15E_11D4_9DFD_005004F94BC9__INCLUDED_)
#define AFX_PAUSEDIALOG_H__C540DD88_E15E_11D4_9DFD_005004F94BC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PauseDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPauseDialog dialog

class CPauseDialog : public CDialog
{
// Construction
public:
	BOOL m_KillZ;
	BOOL m_KillTheta;
	CPauseDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPauseDialog)
	enum { IDD = IDD_PAUSEDIALOG };
	BOOL	m_Pause;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPauseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPauseDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAUSEDIALOG_H__C540DD88_E15E_11D4_9DFD_005004F94BC9__INCLUDED_)
