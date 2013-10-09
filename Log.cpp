// Log.cpp : implementation file
//

#include "stdafx.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLog

CLog::CLog()
{
}

CLog::~CLog()
{
}


BEGIN_MESSAGE_MAP(CLog, CWnd)
	//{{AFX_MSG_MAP(CLog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLog message handlers

int CLog::Size()
{
	return m_String.GetSize();
}

void CLog::Write(CString Text, ...)
{
	CString ID = Text.SpanExcluding(":");
	double *Arg = (double*)((&Text)+1);
	CString String;
	String.Format(Text,Arg[0],Arg[1],Arg[2],Arg[3]);
	int a;
	int n=Size();
	for (a=0; a<n; ++a)
		if (ID == m_String[a].SpanExcluding(":"))
			break;
	if (a == n)
		m_String.Add(String);
	else
		m_String[a] = String;
}

void CLog::SetTime()
{
	CTime Time;
	Write((Time.GetCurrentTime()).Format("MuCat Scanner: %#c"));
}

void CLog::Dump(CString FileName)
{
//	return;//              $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Temporarily remove this
	CTime Time;
	CFile File(FileName, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone);
	int n=Size();
	CString String;
	Write((Time.GetCurrentTime()).Format("MuCat 2 Scanner: %#c\n\n"));
	for (int a=0; a<n; ++a)
	{
		String = m_String[a]+"\n";
		File.Write(String,String.GetLength());
	}
}

void CLog::Clear()
{
	m_String.RemoveAll();
}
