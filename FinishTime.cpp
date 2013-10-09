// FinishTime.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "FinishTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinishTime

CFinishTime::CFinishTime()
{
}

CFinishTime::~CFinishTime()
{
}


BEGIN_MESSAGE_MAP(CFinishTime, CWnd)
	//{{AFX_MSG_MAP(CFinishTime)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFinishTime message handlers

CString CFinishTime::GetFinishTime(int CurrentTask, int TotalTasks)
{
	CString FinishTime;
	if (CurrentTask == 0)
	{
		m_StartTime = CTime::GetCurrentTime();
		FinishTime.Format("Not known.");
		return FinishTime;
	}
	CTime CurrentTime = CTime::GetCurrentTime();
	CTimeSpan Duration = CurrentTime - m_StartTime;
	double Seconds = (double)Duration.GetTotalSeconds();
	Seconds = Seconds*TotalTasks/CurrentTask;
	CTimeSpan TotalTimeEstimate((time_t) Seconds);
	CTime EndTime = m_StartTime+TotalTimeEstimate;
	FinishTime = EndTime.Format("%#c");
	return FinishTime;
}

CString CFinishTime::GetShortFinishTime(int CurrentTask, int TotalTasks)
{
	CString FinishTime;
	if (CurrentTask == 0)
	{
		m_StartTime = CTime::GetCurrentTime();
		FinishTime.Format("Not known.");
		return FinishTime;
	}
	CTime CurrentTime = CTime::GetCurrentTime();
	CTimeSpan Duration = CurrentTime - m_StartTime;
	double Seconds = (double)Duration.GetTotalSeconds();
	Seconds = Seconds*TotalTasks/CurrentTask;
	CTimeSpan TotalTimeEstimate((time_t) Seconds);
	CTime EndTime = m_StartTime+TotalTimeEstimate;
	FinishTime = EndTime.Format("Fin: %a %H:%M");
	return FinishTime;
}
