#if !defined(AFX_FINISHTIME_H__638189E1_6D1D_11D4_93B6_0060087E363B__INCLUDED_)
#define AFX_FINISHTIME_H__638189E1_6D1D_11D4_93B6_0060087E363B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FinishTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinishTime window

class CFinishTime : public CWnd
{
// Construction
public:
	CFinishTime();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinishTime)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetShortFinishTime(int CurrentTask, int TotalTasks);
	CString GetFinishTime(int CurrentTask, int TotalTasks);
	virtual ~CFinishTime();

	// Generated message map functions
protected:
	CTime m_StartTime;
	//{{AFX_MSG(CFinishTime)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINISHTIME_H__638189E1_6D1D_11D4_93B6_0060087E363B__INCLUDED_)
