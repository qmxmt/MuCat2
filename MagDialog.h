#if !defined(AFX_MAGDIALOG_H__6D4BBF60_B20F_11D2_A406_0060080C08D4__INCLUDED_)
#define AFX_MAGDIALOG_H__6D4BBF60_B20F_11D2_A406_0060080C08D4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MagDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMagDialog dialog

class CMagDialog : public CDialog
{
// Construction
public:
	CMagDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMagDialog)
	enum { IDD = IDD_MAGDIALOG };
	float	m_MagFactor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMagDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMagDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAGDIALOG_H__6D4BBF60_B20F_11D2_A406_0060080C08D4__INCLUDED_)
