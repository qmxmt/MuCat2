; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPauseDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MuCat.h"
LastPage=0

ClassCount=20
Class1=CMuCatApp
Class2=CMuCatDoc
Class3=CMuCatView
Class4=CMainFrame

ResourceCount=30
Resource1=IDD_XRAY_DIALOG (English (U.K.))
Resource2=IDD_GEOMETRYDIALOG
Resource3=IDD_MAGDIALOG
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_DIMDIALOG
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDD_PAUSEDIALOG (English (U.S.))
Class7=CBinDialog
Resource7=IDD_VIEWZOOM (English (U.K.))
Class8=CSpecDialog
Resource8=IDD_STOPDIALOG
Class9=CXrayDialog
Resource9=IDD_GAINDIALOG
Class10=CZoomDialog
Resource10=IDD_BINDIALOG
Class11=CStopDialog
Resource11=IDD_XRAY_DIALOG
Class12=CGainDialog
Class13=CSplashWnd
Resource12=IDD_VIEWZOOM
Class14=CPositionDialog
Resource13=IDD_ABOUTBOX (English (U.S.))
Class15=CDimDialog
Resource14=IDD_POSITIONDIALOG
Resource15=IDD_GAINDIALOG (English (U.K.))
Class16=CMagDialog
Class17=CDurationDialog
Resource16=IDR_MUCATTYPE (English (U.S.))
Resource17=IDD_SPECDIALOG (English (U.K.))
Resource18=IDD_ABOUTBOX
Resource19=IDD_MAGDIALOG (English (U.K.))
Resource20=IDD_GEOMETRYDIALOG (English (U.S.))
Resource21=IDD_DIMDIALOG (English (U.K.))
Resource22=IDR_MUCATTYPE
Resource23=IDD_PAUSEDIALOG
Resource24=IDD_PARAMETER_DURATION
Resource25=IDR_MAINFRAME
Resource26=IDD_BINDIALOG (English (U.K.))
Class18=CGeometry
Resource27=IDD_SPECDIALOG
Class19=CFinishTime
Resource28=IDD_PARAMETER_DURATION (English (U.K.))
Class20=CPauseDialog
Resource29=IDD_STOPDIALOG (English (U.K.))
Resource30=IDD_POSITIONDIALOG (English (U.K.))

[CLS:CMuCatApp]
Type=0
HeaderFile=MuCat.h
ImplementationFile=MuCat.cpp
Filter=N

[CLS:CMuCatDoc]
Type=0
HeaderFile=MuCatDoc.h
ImplementationFile=MuCatDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CMuCatDoc

[CLS:CMuCatView]
Type=0
HeaderFile=MuCatView.h
ImplementationFile=MuCatView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CMuCatView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_POSITION


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=MuCat.cpp
ImplementationFile=MuCat.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_COPY
Command4=ID_FILE_PRINT
Command5=ID_SCAN
Command6=ID_INITFOCUS
Command7=ID_STILL
Command8=ID_RECORD
Command9=ID_AUTOSCALE
Command10=ID_BRIGHT_DOWN
Command11=ID_BRIGHT_UP
Command12=ID_CONTRAST_DOWN
Command13=ID_CONTRAST_UP
Command14=ID_POSITION
Command15=ID_BUTTONDIM
Command16=ID_BUTTONSHARPNESS
Command17=ID_APP_ABOUT
CommandCount=17

[MNU:IDR_MUCATTYPE]
Type=1
Class=CMuCatView
Command1=ID_FILE_CLOSE
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_SPEC
Command11=ID_EDIT_XRAY
Command12=ID_EDIT_GEOMETRY
Command13=ID_EDIT_COPY
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VIEW_ZOOM
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_PARAMETER_BIN
Command22=ID_PARAMETER_DIM
Command23=ID_PARAMETER_EXP
Command24=ID_PARAMETER_MAG
Command25=IDD_PARAMETER_GAIN
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_STOP
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_SAVE
Command3=ID_EDIT_COPY
Command4=ID_FILE_PRINT
Command5=ID_SCAN
Command6=ID_INITFOCUS
Command7=ID_STILL
Command8=ID_RECORD
Command9=ID_AUTOSCALE
Command10=ID_BRIGHT_DOWN
Command11=ID_BRIGHT_UP
Command12=ID_CONTRAST_DOWN
Command13=ID_CONTRAST_UP
Command14=ID_POSITION
Command15=ID_BUTTONDIM
Command16=ID_BUTTONSHARPNESS
Command17=ID_APP_ABOUT
CommandCount=17

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MUCATTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_CLOSE
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_FILE_PRINT
Command5=ID_FILE_PRINT_PREVIEW
Command6=ID_FILE_PRINT_SETUP
Command7=ID_FILE_MRU_FILE1
Command8=ID_APP_EXIT
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_SPEC
Command11=ID_EDIT_XRAY
Command12=ID_EDIT_GEOMETRY
Command13=ID_EDIT_COPY
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VIEW_ZOOM
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_PARAMETER_BIN
Command22=ID_PARAMETER_DIM
Command23=ID_PARAMETER_EXP
Command24=ID_PARAMETER_MAG
Command25=IDD_PARAMETER_GAIN
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_STOP
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_BINDIALOG]
Type=1
Class=CBinDialog
ControlCount=4
Control1=IDC_BINEDIT,edit,1350631552
Control2=IDC_BINSPIN,msctls_updown32,1342177314
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CBinDialog]
Type=0
HeaderFile=BinDialog.h
ImplementationFile=BinDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CBinDialog
VirtualFilter=dWC

[CLS:CSpecDialog]
Type=0
HeaderFile=SpecDialog.h
ImplementationFile=SpecDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_COMMENT
VirtualFilter=dWC

[DLG:IDD_SPECDIALOG]
Type=1
Class=CSpecDialog
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_USER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OWNER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DESCRIPTION,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMMENT,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816

[DLG:IDD_XRAY_DIALOG]
Type=1
Class=CXrayDialog
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_VOLTAGE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CURRENT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FILTER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ISSUE,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDITPEPPER,edit,1350631552
Control11=IDC_PEPPERCHECK,button,1342242819
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816

[CLS:CXrayDialog]
Type=0
HeaderFile=XrayDialog.h
ImplementationFile=XrayDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CXrayDialog

[DLG:IDD_VIEWZOOM]
Type=1
Class=CZoomDialog
ControlCount=9
Control1=IDC_ZOOM25,button,1342177289
Control2=IDC_ZOOM33,button,1342177289
Control3=IDC_ZOOM50,button,1342177289
Control4=IDC_ZOOM100,button,1342177289
Control5=IDC_ZOOM200,button,1342177289
Control6=IDC_ZOOM300,button,1342177289
Control7=IDC_ZOOM400,button,1342177289
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[CLS:CZoomDialog]
Type=0
HeaderFile=ZoomDialog.h
ImplementationFile=ZoomDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CZoomDialog
VirtualFilter=dWC

[DLG:IDD_STOPDIALOG]
Type=1
Class=CStopDialog
ControlCount=1
Control1=IDOK,button,1342259201

[CLS:CStopDialog]
Type=0
HeaderFile=StopDialog.h
ImplementationFile=StopDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CStopDialog
VirtualFilter=dWC

[DLG:IDD_GAINDIALOG]
Type=1
Class=CGainDialog
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GAINSPEED,edit,1350631552
Control5=IDC_GAINSPEEDSPIN,msctls_updown32,1342177314
Control6=IDC_STATIC,static,1342308352
Control7=IDC_GAINGAIN,edit,1350631552
Control8=IDC_GAINGAINSPIN,msctls_updown32,1342177314
Control9=IDC_GAINELECTRON,static,1342308352

[CLS:CGainDialog]
Type=0
HeaderFile=GainDialog.h
ImplementationFile=GainDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_GAINGAIN

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
LastObject=CSplashWnd
Filter=W

[CLS:CPositionDialog]
Type=0
HeaderFile=PositionDialog.h
ImplementationFile=PositionDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPositionDialog

[DLG:IDD_POSITIONDIALOG]
Type=1
Class=CPositionDialog
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ROTATION,edit,1350631552
Control3=IDC_ROTATIONSPIN,msctls_updown32,1342177442
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ELEVATION,edit,1350631552
Control6=IDC_ELEVATIONSPIN,msctls_updown32,1342177442
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TRANSLATION,edit,1350631552
Control9=IDC_TRANSLATIONSPIN,msctls_updown32,1342177442
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[DLG:IDD_DIMDIALOG]
Type=1
Class=CDimDialog
ControlCount=18
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DIMHEIGHT,edit,1350631552
Control3=IDC_DIMHEIGHTSPIN,msctls_updown32,1342177442
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DIMLENGTH,edit,1350631552
Control6=IDC_DIMLENGTHSPIN,msctls_updown32,1342177442
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DIMPROJ,edit,1350631552
Control9=IDC_DIMPROJSPIN,msctls_updown32,1342177442
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DIMBLOCKS,edit,1350631552
Control12=IDC_DIMBLOCKSSPIN,msctls_updown32,1342177442
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DIMSHIFT,edit,1350631552
Control15=IDC_DIMSHIFTSPIN,msctls_updown32,1342177314
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_DIMMAXSLICES,static,1342308352

[CLS:CDimDialog]
Type=0
HeaderFile=DimDialog.h
ImplementationFile=DimDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DIMLENGTH

[DLG:IDD_MAGDIALOG]
Type=1
Class=CMagDialog
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PARAMETERMAG,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CMagDialog]
Type=0
HeaderFile=MagDialog.h
ImplementationFile=MagDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMagDialog
VirtualFilter=dWC

[DLG:IDD_PARAMETER_DURATION]
Type=1
Class=CDurationDialog
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PARAMETER_DURATION,edit,1350631552
Control3=IDC_PARAMETERDURATIONSPIN,msctls_updown32,1342177314
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PARAMETERSTILL,edit,1350631552
Control6=IDC_PARAMETERSTILLSPIN,msctls_updown32,1342177314
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CDurationDialog]
Type=0
HeaderFile=DurationDialog.h
ImplementationFile=DurationDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDurationDialog
VirtualFilter=dWC

[DLG:IDD_POSITIONDIALOG (English (U.K.))]
Type=1
Class=CPositionDialog
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ROTATION,edit,1350631552
Control3=IDC_ROTATIONSPIN,msctls_updown32,1342177442
Control4=IDC_STATIC,static,1342308352
Control5=IDC_ELEVATION,edit,1350631552
Control6=IDC_ELEVATIONSPIN,msctls_updown32,1342177442
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TRANSLATION,edit,1350631552
Control9=IDC_TRANSLATIONSPIN,msctls_updown32,1342177442
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[DLG:IDD_BINDIALOG (English (U.K.))]
Type=1
Class=CBinDialog
ControlCount=4
Control1=IDC_BINEDIT,edit,1350631552
Control2=IDC_BINSPIN,msctls_updown32,1342177314
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_SPECDIALOG (English (U.K.))]
Type=1
Class=CSpecDialog
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_USER,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OWNER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DESCRIPTION,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMMENT,edit,1350631552
Control9=IDOK,button,1342242817
Control10=IDCANCEL,button,1342242816

[DLG:IDD_XRAY_DIALOG (English (U.K.))]
Type=1
Class=CXrayDialog
ControlCount=13
Control1=IDC_STATIC,static,1342308352
Control2=IDC_VOLTAGE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CURRENT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_FILTER,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ISSUE,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDITPEPPER,edit,1350631552
Control11=IDC_PEPPERCHECK,button,1342242819
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816

[DLG:IDD_VIEWZOOM (English (U.K.))]
Type=1
Class=CZoomDialog
ControlCount=9
Control1=IDC_ZOOM25,button,1342177289
Control2=IDC_ZOOM33,button,1342177289
Control3=IDC_ZOOM50,button,1342177289
Control4=IDC_ZOOM100,button,1342177289
Control5=IDC_ZOOM200,button,1342177289
Control6=IDC_ZOOM300,button,1342177289
Control7=IDC_ZOOM400,button,1342177289
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816

[DLG:IDD_STOPDIALOG (English (U.K.))]
Type=1
Class=CStopDialog
ControlCount=1
Control1=IDOK,button,1342259201

[DLG:IDD_GAINDIALOG (English (U.K.))]
Type=1
Class=CGainDialog
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GAINSPEED,edit,1350631552
Control5=IDC_GAINSPEEDSPIN,msctls_updown32,1342177314
Control6=IDC_STATIC,static,1342308352
Control7=IDC_GAINGAIN,edit,1350631552
Control8=IDC_GAINGAINSPIN,msctls_updown32,1342177314
Control9=IDC_GAINELECTRON,static,1342308352

[DLG:IDD_DIMDIALOG (English (U.K.))]
Type=1
Class=CDimDialog
ControlCount=18
Control1=IDC_STATIC,static,1342308352
Control2=IDC_DIMHEIGHT,edit,1350631552
Control3=IDC_DIMHEIGHTSPIN,msctls_updown32,1342177442
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DIMLENGTH,edit,1350631552
Control6=IDC_DIMLENGTHSPIN,msctls_updown32,1342177442
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DIMPROJ,edit,1350631552
Control9=IDC_DIMPROJSPIN,msctls_updown32,1342177442
Control10=IDC_STATIC,static,1342308352
Control11=IDC_DIMBLOCKS,edit,1350631552
Control12=IDC_DIMBLOCKSSPIN,msctls_updown32,1342177442
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DIMSHIFT,edit,1350631552
Control15=IDC_DIMSHIFTSPIN,msctls_updown32,1342177314
Control16=IDOK,button,1342242817
Control17=IDCANCEL,button,1342242816
Control18=IDC_DIMMAXSLICES,static,1342308352

[DLG:IDD_MAGDIALOG (English (U.K.))]
Type=1
Class=CMagDialog
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PARAMETERMAG,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_PARAMETER_DURATION (English (U.K.))]
Type=1
Class=CDurationDialog
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PARAMETER_DURATION,edit,1350631552
Control3=IDC_PARAMETERDURATIONSPIN,msctls_updown32,1342177314
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PARAMETERSTILL,edit,1350631552
Control6=IDC_PARAMETERSTILLSPIN,msctls_updown32,1342177314
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[DLG:IDD_GEOMETRYDIALOG]
Type=1
Class=CGeometry
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GEOMETRYPIXELSIZE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GEOMETRYDISTANCE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GEOMETRYGRADIENT,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CGeometry]
Type=0
HeaderFile=Geometry.h
ImplementationFile=Geometry.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_GEOMETRYGRADIENT

[DLG:IDD_GEOMETRYDIALOG (English (U.S.))]
Type=1
Class=CGeometry
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_GEOMETRYPIXELSIZE,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_GEOMETRYDISTANCE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_GEOMETRYGRADIENT,edit,1350631552
Control7=IDOK,button,1342242817
Control8=IDCANCEL,button,1342242816

[CLS:CFinishTime]
Type=0
HeaderFile=FinishTime.h
ImplementationFile=FinishTime.cpp
BaseClass=generic CWnd
Filter=W

[DLG:IDD_PAUSEDIALOG]
Type=1
Class=CPauseDialog
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECKPAUSE,button,1342242819
Control4=IDC_KILLTHETA,button,1342242819
Control5=IDC_KILLZ,button,1342242819

[CLS:CPauseDialog]
Type=0
HeaderFile=PauseDialog.h
ImplementationFile=PauseDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_KILLTHETA

[DLG:IDD_PAUSEDIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECKPAUSE,button,1342242819

