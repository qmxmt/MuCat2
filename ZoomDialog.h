#if !defined(AFX_ZOOMDIALOG_H__F02169E1_F4B3_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_ZOOMDIALOG_H__F02169E1_F4B3_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ZoomDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDialog dialog

class CZoomDialog : public CDialog
{
// Construction
public:
	int m_Zoom;
	CZoomDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomDialog)
	enum { IDD = IDD_VIEWZOOM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnZoom25();
	afx_msg void OnZoom33();
	afx_msg void OnZoom50();
	afx_msg void OnZoom100();
	afx_msg void OnZoom200();
	afx_msg void OnZoom300();
	afx_msg void OnZoom400();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDIALOG_H__F02169E1_F4B3_11D1_A406_0000010049AB__INCLUDED_)
