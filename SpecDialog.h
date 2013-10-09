#if !defined(AFX_SPECDIALOG_H__8AFB17C1_F001_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_SPECDIALOG_H__8AFB17C1_F001_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SpecDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpecDialog dialog

class CSpecDialog : public CDialog
{
// Construction
public:
	CSpecDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpecDialog)
	enum { IDD = IDD_SPECDIALOG };
	CString	m_Comment;
	CString	m_Description;
	CString	m_Owner;
	CString	m_User;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpecDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpecDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECDIALOG_H__8AFB17C1_F001_11D1_A406_0000010049AB__INCLUDED_)
