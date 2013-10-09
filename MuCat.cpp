// MuCat.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MuCat.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "MuCatDoc.h"
#include "MuCatView.h"
#include "843.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMuCatApp

BEGIN_MESSAGE_MAP(CMuCatApp, CWinApp)
	//{{AFX_MSG_MAP(CMuCatApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMuCatApp construction

void Texit(char *Message)
{
	::MessageBox(NULL,Message,"Error",MB_OK|MB_ICONHAND);
	exit(1);
}

CMuCatApp::CMuCatApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMuCatApp object

CMuCatApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMuCatApp initialization

BOOL CMuCatApp::InitInstance()
{
	C843::Reset();
	::MessageBox(NULL, "Remove specimen and holder!\n\nCheck slide paths are clear!", "Caution", MB_OK|MB_ICONWARNING);
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

/*#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif*/

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.


	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MUCATTYPE,
		RUNTIME_CLASS(CMuCatDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMuCatView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	POSITION PDoc = pDocTemplate->GetFirstDocPosition();
	CMuCatDoc* pDoc = (CMuCatDoc*)(pDocTemplate->GetNextDoc(PDoc));
	ASSERT_VALID(pDoc);

	if (Camera.InitializeCamera())
		Texit("Camera initialisation error");;
	pDoc->GetCCDSize();
	pDoc->SetGain();
	pDoc->SetMaxHeight();
	pDoc->GetSlide()->SetAcceleration(400000);
	pDoc->GetMagSlide()->SetAcceleration(400000);
//	pDoc->GetMagSlide()->SetTopSpeed(50000);
	pDoc->GetTurntable()->FindHome();
	pDoc->GetSlide()->FindHome();
	pDoc->GetMagSlide()->FindHome();
	pDoc->GetMagSlide()->Move(170000);
	pDoc->GetMagSlide()->WaitForStop();
	pDoc->GetElevator()->FindHome();
	pDoc->GetElevator()->Move(280000);
	pDoc->GetElevator()->WaitForStop();
//	pDoc->GetSlide()->SetAcceleration(100000);
	pDoc->SetTheta(pDoc->GetHeader()->theta/1000.0);
	pDoc->SetElevation(pDoc->GetHeader()->z);
	pDoc->OnPosition();
	pDoc->GetTurntable()->Move(-pDoc->GetHeader()->theta);
	pDoc->GetElevator()->Move(pDoc->GetElevation()*(-2));
	pDoc->GetElevator()->WaitForStop();
	pDoc->GetMagSlide()->Move(pDoc->GetHeader()->posdistance*2);

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMuCatApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMuCatApp commands

BOOL CMuCatApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}
