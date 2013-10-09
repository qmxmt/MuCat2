#if !defined(AFX_GAINDIALOG_H__51805361_006F_11D2_A406_0000010049AB__INCLUDED_)
#define AFX_GAINDIALOG_H__51805361_006F_11D2_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "SI800Camera.h"
// GainDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGainDialog dialog

class CGainDialog : public CDialog
{
// Construction
public:
//	void Paint();
	CGainDialog(CSI800Camera* pCamera, CWnd* pParent = NULL); 
	CGainDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGainDialog)
	enum { IDD = IDD_GAINDIALOG };
	UINT	m_Gain;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGainDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGainDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeGaingain();
//	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAINDIALOG_H__51805361_006F_11D2_A406_0000010049AB__INCLUDED_)
