#if !defined(AFX_LOG_H__E4470AE3_EACE_11D3_93B6_0060087E363B__INCLUDED_)
#define AFX_LOG_H__E4470AE3_EACE_11D3_93B6_0060087E363B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Log.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLog window

class CLog : public CWnd
{
// Construction
public:
	CLog();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLog)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Clear();
	void Dump(CString FileName);
	void SetTime();
	void Write(CString Text,...);
	int Size();
	virtual ~CLog();

	// Generated message map functions
protected:
	CStringArray m_String;
	//{{AFX_MSG(CLog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG_H__E4470AE3_EACE_11D3_93B6_0060087E363B__INCLUDED_)
