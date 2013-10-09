#if !defined(AFX_POSITIONDIALOG_H__548A5F80_AFBD_11D2_A406_0060080C08D4__INCLUDED_)
#define AFX_POSITIONDIALOG_H__548A5F80_AFBD_11D2_A406_0060080C08D4__INCLUDED_

#include "843.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PositionDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPositionDialog dialog

class CPositionDialog : public CDialog
{
// Construction
public:
	C843 *m_pSlide;
	C843 *m_pTurntable;
	C843 *m_pElevator;
	C843* m_pMagnificationSlide;
	int m_MaxTranslation;
	int m_OldTranslation;
	float m_SourceToCamera;
	CPositionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPositionDialog)
	enum { IDD = IDD_POSITIONDIALOG };
	double	m_Rotation;
	int		m_Translation;
	double m_StepSize;
	long	m_Elevation;
	long m_PosDistance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPositionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPositionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposRotationspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeRotation();
	afx_msg void OnDeltaposTranslationspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeElevation();
	afx_msg void OnDeltaposElevationspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposPosdistancespin(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	float m_DistanceOffset;
	float m_CameraPixelSize;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSITIONDIALOG_H__548A5F80_AFBD_11D2_A406_0060080C08D4__INCLUDED_)
