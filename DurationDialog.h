#if !defined(AFX_DURATIONDIALOG_H__35133B63_B44D_11D2_A406_0060080C08D4__INCLUDED_)
#define AFX_DURATIONDIALOG_H__35133B63_B44D_11D2_A406_0060080C08D4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DurationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDurationDialog dialog

class CDurationDialog : public CDialog
{
// Construction
public:
	CDurationDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDurationDialog)
	enum { IDD = IDD_PARAMETER_DURATION };
	int		m_Duration;
	int		m_StillDuration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDurationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDurationDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DURATIONDIALOG_H__35133B63_B44D_11D2_A406_0060080C08D4__INCLUDED_)
