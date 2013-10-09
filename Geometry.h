#if !defined(AFX_GEOMETRY_H__CA5C26F5_66C2_11D4_9DEF_005004F94BC9__INCLUDED_)
#define AFX_GEOMETRY_H__CA5C26F5_66C2_11D4_9DEF_005004F94BC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Geometry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeometry dialog

class CGeometry : public CDialog
{
// Construction
public:
	CGeometry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeometry)
	enum { IDD = IDD_GEOMETRYDIALOG };
	float	m_Distance;
	float	m_PixelSize;
	float	m_Gradient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeometry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeometry)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEOMETRY_H__CA5C26F5_66C2_11D4_9DEF_005004F94BC9__INCLUDED_)
