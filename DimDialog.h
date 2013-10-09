#if !defined(AFX_DIMDIALOG_H__224EB6E0_B136_11D2_A406_0060080C08D4__INCLUDED_)
#define AFX_DIMDIALOG_H__224EB6E0_B136_11D2_A406_0060080C08D4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DimDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDimDialog dialog

class CDimDialog : public CDialog
{
// Construction
public:
	void Paint();
	float m_Distance;
	int m_MaxHeight;
	CDimDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDimDialog)
	enum { IDD = IDD_DIMDIALOG };
	int		m_Height;
	int		m_ScanLength;
	int		m_NumProj;
	int		m_NumBlocks;
	int		m_Shift;
	BOOL	m_RoundCheck;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDimDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDimDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeDimheight();
	afx_msg void OnChangeDimlength();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_NumFrames;
	afx_msg void OnBnClickedRoundcheck();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIMDIALOG_H__224EB6E0_B136_11D2_A406_0060080C08D4__INCLUDED_)
