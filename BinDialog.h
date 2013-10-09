#if !defined(AFX_BINDIALOG_H__6F1A6321_EE36_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_BINDIALOG_H__6F1A6321_EE36_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBinDialog dialog

class CBinDialog : public CDialog
{
// Construction
public:
	CBinDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBinDialog)
	enum { IDD = IDD_BINDIALOG };
	int		m_Bin;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBinDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BINDIALOG_H__6F1A6321_EE36_11D1_A406_0000010049AB__INCLUDED_)
