// MuCat.h : main header file for the MUCAT application
//

#if !defined(AFX_MUCAT_H__BFC9FE25_EC06_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_MUCAT_H__BFC9FE25_EC06_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "log.h"

/////////////////////////////////////////////////////////////////////////////
// CMuCatApp:
// See MuCat.cpp for the implementation of this class
//

class CMuCatApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMuCatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuCatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMuCatApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMuCatApp theApp;
extern CLog Log;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUCAT_H__BFC9FE25_EC06_11D1_A406_0000010049AB__INCLUDED_)
