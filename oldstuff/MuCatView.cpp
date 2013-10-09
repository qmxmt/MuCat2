// MuCatView.cpp : implementation of the CMuCatView class
//

#include "stdafx.h"
#include "MuCat.h"

#include "MuCatDoc.h"
#include "MuCatView.h"
#include "ZoomDialog.h"
#include "StopDialog.h"
#include "FinishTime.h"
#include "PauseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLog Log;
/////////////////////////////////////////////////////////////////////////////
// CMuCatView

IMPLEMENT_DYNCREATE(CMuCatView, CScrollView)

BEGIN_MESSAGE_MAP(CMuCatView, CScrollView)
	//{{AFX_MSG_MAP(CMuCatView)
	ON_COMMAND(ID_STILL, OnStill)
	ON_WM_CANCELMODE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_VIEW_ZOOM, OnViewZoom)
	ON_COMMAND(ID_FOCUS, OnFocus)
	ON_COMMAND(ID_INITFOCUS, OnInitFocus)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_AUTOSCALE, OnAutoscale)
	ON_COMMAND(ID_BRIGHT_DOWN, OnBrightDown)
	ON_COMMAND(ID_BRIGHT_UP, OnBrightUp)
	ON_COMMAND(ID_CONTRAST_DOWN, OnContrastDown)
	ON_COMMAND(ID_CONTRAST_UP, OnContrastUp)
	ON_COMMAND(ID_RECORD, OnRecord)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_SCAN, OnScan)
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTONSHARPNESS, OnButtonsharpness)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

BOOL CMuCatView::m_Initialised = 0;
unsigned int CMuCatView::m_ScaleTable[41];

/////////////////////////////////////////////////////////////////////////////
// CMuCatView construction/destruction

CMuCatView::CMuCatView()
{
	// TODO: add construction code here
	if (!m_Initialised)
		Initialise();
	m_BitmapArray = NULL;
	m_BitmapBuffer = NULL;
	m_CCDBuffer = NULL;
	m_CCDPixel = NULL;
	m_XSize = m_YSize = 0;
	m_Zoom = 12;
	m_AutoScale = TRUE;
	m_ValidImage = FALSE;
	m_IsRecording = FALSE;
	m_IsDark = FALSE;
	m_CentreOffset = CENTRE_OFFSET;
	m_mmUnits = TRUE;
}

CMuCatView::~CMuCatView()
{
}

BOOL CMuCatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMuCatView drawing

void CMuCatView::OnDraw(CDC* pDC)
{
		// TODO: add draw code for native data here
	CMuCatDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_BitmapBuffer == NULL)
	{
		pDC->TextOut(0,0,"New",3);
		return;
	}
/*	SetDIBitsToDevice(pDC->GetSafeHdc(), 0,0, m_XSize,m_YSize, 0,0, 0,m_YSize,\
		m_BitmapBuffer, (BITMAPINFO*)&m_BitmapInfo,DIB_RGB_COLORS);*/
	StretchDIBits(pDC->GetSafeHdc(), 0,0,m_XSize*m_Zoom/12, m_YSize*m_Zoom/12, 0,0, m_XSize,\
		m_YSize, m_BitmapBuffer,(BITMAPINFO*)&m_BitmapInfo,DIB_RGB_COLORS,SRCCOPY);

	CPen Pen;
	Pen.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	pDC->SelectObject(&Pen);
	int Height = pDoc->GetHeader()->num_slices;
	int Y=(m_YSize/2-Height/2)*m_Zoom/12-1;
	int X=(m_XSize*m_Zoom/12)-1;
	pDC->MoveTo(0,Y);
	pDC->LineTo(X-1,Y);
	Y += Height*m_Zoom/12+1;
	pDC->MoveTo(0,Y);
	pDC->LineTo(X-1,Y);
	Y = m_YSize*m_Zoom/12-1;
	pDC->MoveTo(32*m_Zoom/12, 0);
	pDC->LineTo(32*m_Zoom/12, Y);
	pDC->MoveTo((m_XSize-33)*m_Zoom/12, 0);
	pDC->LineTo((m_XSize-33)*m_Zoom/12, Y);

	Y=(m_YSize/2)*m_Zoom/12-1;
	X=(m_XSize*m_Zoom/12)-1;
	CPen DotPen;
	DotPen.CreatePen(PS_DOT, 1, RGB(0,0,255));
	pDC->SelectObject(&DotPen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->MoveTo(0,Y);
	pDC->LineTo(X,Y);

	Height = pDoc->GetHeader()->slices_per_block;
	if (Height > pDoc->GetHeader()->num_slices)
		return;
	Y=(m_YSize/2-Height/2)*m_Zoom/12-1;
	X=(m_XSize*m_Zoom/12)-1;
	CPen DashPen;
	DashPen.CreatePen(PS_DASH, 1, RGB(0,255,0));
	pDC->SelectObject(&DashPen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->MoveTo(0,Y);
	pDC->LineTo(X,Y);
	Y += Height*m_Zoom/12+1;
	pDC->MoveTo(0,Y);
	pDC->LineTo(X,Y);
}

void CMuCatView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMuCatView printing

BOOL CMuCatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMuCatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMuCatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMuCatView diagnostics

#ifdef _DEBUG


void CMuCatView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMuCatView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMuCatDoc* CMuCatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMuCatDoc)));
	return (CMuCatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMuCatView message handlers

void CMuCatView::OnStill() 
{
	// TODO: Add your command handler code here
	int Bin;
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Bin = pDoc->GetBin();
	m_XSize = pDoc->GetNumCCDRows()/Bin;
	m_YSize = pDoc->GetNumCCDCols()/Bin;
	CreateBitmap();
	CreateCCDBuffer();
	Camera.Flush();
	Camera.Expose((float)(pDoc->GetStillExposure()*1000));
	Camera.Readout(m_CCDPixel, m_XSize, m_YSize, pDoc->GetBin());
	m_ValidImage = TRUE;
	if (m_AutoScale)
		AutoScale();
	CreateLookup();
	ExecuteLookup();
	Resize();
	Invalidate();
}

void CMuCatView::CreateBitmap()
{
	int XRoundupSize;
	if (m_XSize % 4)
		XRoundupSize = m_XSize + 4 - (m_XSize % 4);
	else
		XRoundupSize = m_XSize;
	if (m_BitmapArray != NULL)
		delete [] m_BitmapArray;
	if (m_BitmapBuffer != NULL)
		delete [] m_BitmapBuffer;
	m_BitmapBuffer = new unsigned char [m_YSize*XRoundupSize];
	m_BitmapArray = new unsigned char * [m_YSize];
	for (int a=0; a<m_YSize; ++a)
		m_BitmapArray[a] = &m_BitmapBuffer[a*XRoundupSize];

	for (a=0; a<m_YSize; ++a)
	{
		for (int b=0; b<XRoundupSize; ++b)
			m_BitmapArray[a][b] = b*256/XRoundupSize;
	}

	m_BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BitmapInfo.bmiHeader.biWidth = XRoundupSize;
	m_BitmapInfo.bmiHeader.biHeight = m_YSize;
	m_BitmapInfo.bmiHeader.biPlanes = 1;
	m_BitmapInfo.bmiHeader.biBitCount = 8;
	m_BitmapInfo.bmiHeader.biCompression = BI_RGB;
	m_BitmapInfo.bmiHeader.biSizeImage = 0;
	m_BitmapInfo.bmiHeader.biClrUsed = 256;
	m_BitmapInfo.bmiHeader.biClrImportant = 0;
	for (a=0; a<256; ++a)
	{
		m_BitmapInfo.bmiColors[a].rgbRed = a;
		m_BitmapInfo.bmiColors[a].rgbGreen = a;//a*9/10;
		m_BitmapInfo.bmiColors[a].rgbBlue = a;//a*2/3;
	}
}

void CMuCatView::Resize()
{
	RECT ChildRect,FrameRect;
	int Xmax,Ymax;
	BOOL OverSize = FALSE;
	GetParentFrame()->GetParentFrame()->GetClientRect(&FrameRect);
	Xmax = FrameRect.right;
	Ymax = FrameRect.bottom-50;
//	Ymax = 100;
	SIZE Size = {m_XSize*m_Zoom/12, m_YSize*m_Zoom/12};
	SetScrollSizes(MM_TEXT, Size);
	ResizeParentToFit(FALSE);
	SetScrollSizes(MM_TEXT, Size);
	ResizeParentToFit();
	GetParentFrame()->GetWindowRect(&ChildRect);
	if ((ChildRect.right - ChildRect.left) > Xmax)
		OverSize = TRUE;
	else
		Xmax = ChildRect.right - ChildRect.left;
	if ((ChildRect.bottom - ChildRect.top) > Ymax)
		OverSize = TRUE;
	else
		Ymax = ChildRect.bottom - ChildRect.top;
	if (OverSize)
	{
		GetParentFrame()->SetWindowPos(&wndTop, 0,0, Xmax, Ymax, SWP_NOMOVE);
		SetScrollSizes(MM_TEXT, Size);
	}
}


void CMuCatView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnPrepareDC(pDC, pInfo);
	pDC->SetMapMode(MM_TEXT);
}

void CMuCatView::OnCancelMode() 
{
	CScrollView::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CMuCatView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	int XPrintSize, YPrintSize, XScale, YScale, Scale;
	if (m_BitmapBuffer == NULL)
		return;
	XPrintSize = pDC->GetDeviceCaps(HORZRES);
	YPrintSize = pDC->GetDeviceCaps(VERTRES);
	XScale = XPrintSize/m_XSize;
	YScale = YPrintSize/m_YSize;
	if (XScale < YScale)
		Scale = XScale;
	else
		Scale = YScale;
	StretchDIBits(pDC->GetSafeHdc(), 0,0,m_XSize*Scale, m_YSize*Scale, 0,0, m_XSize,\
		m_YSize, m_BitmapBuffer,(BITMAPINFO*)&m_BitmapInfo,DIB_RGB_COLORS,SRCCOPY);
}


void CMuCatView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CClientDC ClientDC(this);
	CBitmap Image;	
	Image.CreateCompatibleBitmap(&ClientDC, m_XSize, m_YSize);
	SetDIBits(ClientDC.GetSafeHdc()
		,HBITMAP(Image),0,m_YSize,m_BitmapBuffer,(BITMAPINFO*)&m_BitmapInfo,DIB_RGB_COLORS);
/*	CDC MemDC;
	MemDC.CreateCompatibleDC(&ClientDC);
	MemDC.SelectObject(&Image);*/
	if (!OpenClipboard())
		return;
	::EmptyClipboard();
	::SetClipboardData(CF_BITMAP, Image.m_hObject);
	Image.Detach();
	::CloseClipboard();
}

void CMuCatView::OnViewZoom() 
{
	// TODO: Add your command handler code here
	CZoomDialog aDlg;
	aDlg.m_Zoom = m_Zoom;
	if (aDlg.DoModal() == IDOK)
		m_Zoom = aDlg.m_Zoom;
	Resize();
	Invalidate();
}

void CMuCatView::OnInitFocus() 
{
	// TODO: Add your command handler code here
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_Stop = FALSE;
	Camera.Flush();
	do
	{
		OnFocus();
	} while (!(GetQueueStatus(QS_INPUT)&4) && !m_Stop);
//	aDlg.DestroyWindow();
}

void CMuCatView::OnFocus() 
{
	// TODO: Add your command handler code here
	int Max;
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_XSize = pDoc->GetNumCCDRows()/2;
	m_YSize = pDoc->GetNumCCDCols()/2;
	CreateBitmap();
	Camera.Expose((float)(pDoc->GetStillExposure()*1000));
	Max = Camera.ReadoutRegion(m_BitmapArray, m_XSize/2, m_YSize/2, m_XSize, m_YSize, 1);
	Resize();
//	Invalidate();
	OnDraw(GetDC());
	pDoc->WriteStatus(7,"Max %d",Max);
}


void CMuCatView::OnStop() 
{
	// TODO: Add your command handler code here
	m_Stop = TRUE;
}

void CMuCatView::CreateCCDBuffer()
{
	int a;
	if (m_CCDBuffer)
		delete m_CCDBuffer;
	if (m_CCDPixel)
		delete m_CCDPixel;
	m_CCDBuffer = new unsigned short[m_XSize*m_YSize];
	m_CCDPixel = new unsigned short*[m_YSize];
	for (a=0; a<m_YSize; ++a)
		m_CCDPixel[a] = &m_CCDBuffer[a*m_XSize];
}

void CMuCatView::OnAutoscale() 
{
	// TODO: Add your command handler code here
	if (!m_ValidImage)
		return;
	m_AutoScale = TRUE;
	AutoScale();
	CreateLookup();
	ExecuteLookup();
	Invalidate();
}

void CMuCatView::OnBrightUp() 
{
	// TODO: Add your command handler code here
	if (!m_ValidImage)
		return;
	m_AutoScale = FALSE;
	if (m_Brightness > 0)
		m_Brightness -= 16;
	else
		m_Brightness -= 48;
	m_Brightness = m_Brightness/32*32;
	CreateLookup();
	ExecuteLookup();
	Invalidate();
}

void CMuCatView::OnBrightDown() 
{
	// TODO: Add your command handler code here
	if (!m_ValidImage)
		return;
	m_AutoScale = FALSE;
	if (m_Brightness >= 0)
		m_Brightness += 48;
	else
		m_Brightness += 16;
	m_Brightness = (m_Brightness)/32*32;
	CreateLookup();
	ExecuteLookup();
	Invalidate();
}

void CMuCatView::OnContrastDown() 
{
	// TODO: Add your command handler code here
	if (!m_ValidImage)
		return;
	if (m_Contrast > 0)
		--m_Contrast;
	CreateLookup();
	ExecuteLookup();
	Invalidate();
}

void CMuCatView::OnContrastUp() 
{
	// TODO: Add your command handler code here
	if (!m_ValidImage)
		return;
	if (m_Contrast < 40)
		++m_Contrast;
	CreateLookup();
	ExecuteLookup();
	Invalidate();
}

void CMuCatView::Initialise()
{
	m_Initialised = TRUE;
	double Factor = pow(2.0,0.2);
	double Scale = 256;
	for (int a=0; a<41; ++a)
	{
		m_ScaleTable[a] = (unsigned int)(Scale+0.5);
		Scale *= Factor;
	}
}

void CMuCatView::CreateLookup()
{
	int Start,End,Scale,a;
	Scale = m_ScaleTable[m_Contrast];
	Start = 65536*m_Brightness/Scale;
	End = 65536*(m_Brightness+255)/Scale;
	if (Start < 0)
		Start = 0;
	if (End > 65535)
		End = 65535;
	for (a=0; a<=Start; ++a)
		m_Lookup[a] = 0;
	for (; a<End; ++a)
		m_Lookup[a] = ((Scale*a)>>16) - m_Brightness;
	for (; a<65535; ++a)
		m_Lookup[a] = 255;
}

void CMuCatView::AutoScale()
{
	unsigned short Min, Max, *line;
	int a, b, Scale, EndX, EndY, Avg;
	double FScale,Sum;
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Min = 65535;
	Max = 0;
	Sum = 0;
	EndY = m_YSize - 4;
	EndX = m_XSize - 4;
	for (a=0; a<EndY; a += 4)
	{
		line = m_CCDPixel[a];
		for (b=0; b<EndX; ++b)
		{
  			if (line[b] > Max)
				Max = line[b];
			else
			{
				if (line[b] < Min)
					Min = line[b];
			}
			Sum += line[b];
		}
	}
	Avg = (int)(Sum/(EndX*EndY)*4);
	FScale = 65535.0 * 255.99 / (Max - Min);
	a=0;
	while (m_ScaleTable[a] < FScale && a < 41)
		++a;
	m_Contrast = a-1;
	Scale = m_ScaleTable[a-1];
	m_Brightness = Min * Scale/65536;
	Log.Write("Max: %d",Max);
	pDoc->WriteStatus(7,"Int. %d/%d",Max,Avg);
}

void CMuCatView::ExecuteLookup()
{
	unsigned short *CCDLine;
	unsigned char *BitmapLine;
	int a,b;
	for (a=0; a<m_YSize; ++a)
	{
		CCDLine = m_CCDPixel[a];
		BitmapLine = m_BitmapArray[a];
		for (b=0; b<m_XSize; ++b)
			BitmapLine[b] = m_Lookup[CCDLine[b]];
	}
}

void CMuCatView::OnScan() 
{
	// TODO: Add your command handler code here
	int Bin;
	long ScanStart, ScanEnd;
	struct thead *pHeader;
	double PixelStep;
	double FirstBreak;
	CTime StartTime = CTime::GetCurrentTime();
	CMuCatDoc* pDoc = GetDocument();
//m_CentreOffset = (int)(210.94*(pDoc->GetHeader()->distance) - 1645); // increase to move object image to right
m_CentreOffset = (int)(394.375*(pDoc->GetHeader()->distance) - 3410); // increase to move object image to right
//m_CentreOffset = 0;
	ASSERT_VALID(pDoc);
	m_VerticalPosition = pDoc->GetElevation();
	Bin = pDoc->GetBin();
	m_XSize = pDoc->GetHeader()->num_samples+64;
	m_YSize = pDoc->GetNumCCDCols()/Bin;
	if (!m_IsRecording)
	{
		CreateBitmap();
		CreateCCDBuffer();
	}
	pHeader = pDoc->GetHeader();
	PixelStep = CCD_PIXEL_SIZE / pHeader->mag_factor;
	ScanStart = (long)-(100 + PixelStep*(m_XSize*pDoc->GetBin() + pDoc->GetNumCCDRows() +4))/2;
	ScanEnd = -ScanStart;
	ScanStart += m_CentreOffset;
	if (ScanStart < -99500)
		return;
	ScanEnd += m_CentreOffset;
	if (ScanEnd > 99500)
		return;
	FirstBreak = (double)ScanStart + 100.0;
	pDoc->GetSlide()->SetVelocityFraction(1);
	pDoc->GetSlide()->Move(ScanStart);
//	Camera.Flush();
	pDoc->GetSlide()->WaitForStop();
	pDoc->GetSlide()->SetVelocity((int)(pDoc->GetNumCCDRows()*PixelStep*1000 / pDoc->GetHeader()->exposure));
	if (!m_IsDark)				//Open shutter unless recording "dark" image
		Camera.OpenShutter();
	Camera.TDIReadout(pDoc->GetSlide(),m_CCDPixel, m_XSize, m_YSize, pDoc->GetBin(), FirstBreak, ScanEnd, PixelStep);
	Camera.CloseShutter();
	m_ValidImage = TRUE;
	if (m_AutoScale)
		AutoScale();
	CreateLookup();
	ExecuteLookup();
	if (!m_IsRecording)
		Resize();
	Invalidate();
	pDoc->WriteStatus(3,"T = %5.1f C",Camera.GetTemperature());
	if (Camera.GetPepper())
		pDoc->WriteStatus(5,"Pepper %d",Camera.GetPepperCount());
	else
		pDoc->WriteStatus(5,"Pepper Off");
	CTimeSpan Duration = CTime::GetCurrentTime() - StartTime;
	pDoc->WriteStatus(6,"%4d s",Duration.GetTotalSeconds());
}

void CMuCatView::OnRecord() 
{
	// TODO: Add your command handler code here
	BOOL Pause = FALSE;
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CFile DataFile;
	char FileName[256];
	double Theta,ThetaStep;
	int Block,Proj;
	CFinishTime Finish;
	m_AutoScale = TRUE;
	Camera.SetPepper(pDoc->GetHeader()->pepper);
	pDoc->OnEditSpec();
	pDoc->OnParameterDim();
	pDoc->OnEditXray();
	pDoc->OnEditGeometry();
	CPauseDialog aDlg;
	if (aDlg.DoModal() == IDOK)
		Pause = aDlg.m_Pause;
	int NumBlocks = pDoc->GetHeader()->num_blocks;
	int ZShift = (int)(pDoc->GetHeader()->slices_per_block * pDoc->GetHeader()->pixel_size *(-30.0));
	if (aDlg.m_KillZ)
		ZShift = 0;
	int NumProj = pDoc->GetHeader()->num_proj;
	if (NumProj != 1 && !aDlg.m_KillTheta)
		ThetaStep = 360.0/NumProj;
	else
		ThetaStep = 0;
	CFileDialog FD(FALSE, "mcd", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, \
		"MuCat data files (*.mcd)|*.mcd|All files (*.*)|*.*||");
	if (FD.DoModal() != IDOK)
		return;
	CTime ScanStartTime;
	ScanStartTime = CTime::GetCurrentTime();
	strcpy(pDoc->GetHeader()->time, (LPCTSTR)ScanStartTime.Format("%c"));
	strcpy(FileName,(LPCTSTR)FD.GetPathName());
	pDoc->SetTitle(FileName);
	GetParent()->UpdateWindow();
//	CFile DataFile(FileName,CFile::modeWrite|CFile::modeCreate);
	DataFile.Open(FileName,CFile::modeWrite|CFile::modeCreate);
	DataFile.Write(pDoc->GetHeader(),512);

	if (Pause)
		MessageBox("Remove Specimen and Switch X-rays on.","Waiting for user action.",MB_ICONEXCLAMATION);
	else
		pDoc->GetElevator()->MoveToEnd();
	m_IsDark = TRUE;
	OnScan();
	GetParent()->GetParent()->UpdateWindow();
	UpdateWindow();
	SaveProjection(DataFile);
	pDoc->GetElevator()->WaitForStop();
	m_IsDark = FALSE;
	OnScan();
	GetParent()->GetParent()->UpdateWindow();
	UpdateWindow();
//	pDoc->GetElevator()->Move((pDoc->GetElevation() + (NumBlocks-1)*ZShift));
	SaveProjection(DataFile);
	pDoc->GetElevator()->WaitForStop();
	DataFile.Close();
	if (Pause)
		MessageBox("Replace Specimen and Switch X-rays on.","Waiting for user action.",MB_ICONEXCLAMATION);
	Log.Clear();
	Log.Write("File: %s",(LPCTSTR)FileName);


	for (Block=0; Block<NumBlocks; ++Block)
	{
//		CFile DataFile(FileName,CFile::modeReadWrite);
		DataFile.Open(FileName,CFile::modeReadWrite);
		DataFile.SeekToEnd();
		Theta = pDoc->GetTheta();
		pDoc->GetElevator()->Move((pDoc->GetElevation()*(-30) + (NumBlocks-1-Block)*ZShift));
		pDoc->GetElevator()->WaitForStop();
		Camera.Flush();
		for (Proj=0; Proj < NumProj; ++Proj)
		{
			pDoc->WriteStatus(2,"Projection %d:%d",Block+1,Proj+1);
			Log.Write("Projection: %d:%d",Block+1,Proj+1);
			pDoc->GetTurntable()->Move(-(long)(Theta*1000.0));
			Log.Write("Angle: = %6.2lf",Theta);
			Log.Write("Finish: "+Finish.GetFinishTime(NumProj*Block+Proj,NumProj*NumBlocks));
			pDoc->WriteStatus(8,(LPCTSTR)Finish.GetShortFinishTime(NumProj*Block+Proj,NumProj*NumBlocks));
			Theta -= ThetaStep;
			pDoc->GetTurntable()->WaitForStop();
			OnScan();
			m_IsRecording = TRUE; // Update after first projection
			GetParent()->GetParent()->UpdateWindow();
			UpdateWindow();
			SaveProjection(DataFile);
			Log.Dump("MuCat.mon");

//			DataFile.Flush();
		}
		DataFile.Close();
	}
	m_IsRecording = FALSE;
	pDoc->GetTurntable()->Move(-(long)(pDoc->GetTheta()*1000.0));
	Log.Write("File: %s",(LPCTSTR)FileName);
	Log.Write("FINISHED!!!!");
	Log.Dump("MuCat.mon");
	CTimeSpan Duration = CTime::GetCurrentTime() - ScanStartTime;
	strcpy(pDoc->GetHeader()->duration, (LPCTSTR)Duration.Format("%D:%H:%M:%S"));
	DataFile.Open(FileName,CFile::modeReadWrite);
	DataFile.Write(pDoc->GetHeader(),512);
	DataFile.Close();
	pDoc->WriteStatus(2,"Finished!");
}

void CMuCatView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int XPos, YPos;
	CMuCatDoc* pDoc = GetDocument();
	CClientDC aDC(this);
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	XPos = point.x*12/m_Zoom - m_XSize/2;
	YPos = m_YSize/2 - point.y*12/m_Zoom;
	if (m_mmUnits)
	{
		float X = (float)(XPos*pDoc->GetHeader()->pixel_size/1000.0);
		float Y = (float)(-YPos*pDoc->GetHeader()->pixel_size/1000.0 + m_VerticalPosition/1000.0);
		pDoc->WriteStatus(4,"X=%7.3f Y=%7.3f",(float)X,Y);
	}
	else
	{
		pDoc->WriteStatus(4,"X=%d Y=%d",XPos,(int)(-YPos+m_VerticalPosition/pDoc->GetHeader()->pixel_size));
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CMuCatView::SaveProjection(CFile &DataFile)
{
	CMuCatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int Height = pDoc->GetHeader()->num_slices;
	DataFile.Write(m_CCDPixel[m_YSize/2-Height/2],m_XSize*Height*2);
}

void CMuCatView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnLButtonDblClk(nFlags, point);
	m_mmUnits = !m_mmUnits;
}

void CMuCatView::OnButtonsharpness() 
{
	// TODO: Add your command handler code here
	CMuCatDoc* pDoc = GetDocument();
	float Min,Max,Mid,Sharpness,Value,Left75,Left25,Right25,Right75;
	int x,y,IMin,LeftMid,RightMid,LeftMin,RightMin;
	unsigned short *Pixel;
	Sharpness = 0;
	for (y=0; y<m_YSize; ++y)
	{
		Pixel = m_CCDPixel[y];
		Max = 0;
		for (x=0; x<32; ++x)
			Max += Pixel[x] + Pixel[m_XSize-1-x];
		Max /= 64;
		IMin = 65535;
		for (x=0; x<m_XSize; ++x)
		{
			if (Pixel[x] < IMin)
				IMin = Pixel[x];
		}
		Mid = (IMin + Max)/2;
		for (LeftMid = 0; LeftMid < m_XSize; ++LeftMid)
		{
			if (Pixel[LeftMid] < Mid)
				break;
		}
		for (RightMid = m_XSize-1; RightMid > LeftMid; --RightMid)
		{
			if (Pixel[RightMid] < Mid)
				break;
		}
		LeftMin = (LeftMid*3 + RightMid)/4;
		RightMin = (LeftMid + RightMid*3)/4;
		Min = 0;
		for (x = LeftMid; x<= RightMid; ++x)
			Min += Pixel[x];
		Min /= (RightMid - LeftMid + 1);

		Value = (Max*3 + Min) / 4;
		x=0;
		while (Pixel[x] > Value)
			++x;
		Left75 = ((Value - Pixel[x])*(x - 1) + (Pixel[x-1] - Value)*x) / (Pixel[x-1] - Pixel[x]);

		Value = (Max + Min*3) / 4;
		while (Pixel[x] > Value)
			++x;
		Left25 = ((Value - Pixel[x])*(x - 1) + (Pixel[x-1] - Value)*x) / (Pixel[x-1] - Pixel[x]);

		x = (LeftMid + RightMid)/2;

		while (Pixel[x] < Value)
			++x;
		Right25 = ((Pixel[x] - Value)*(x-1) + (Value - Pixel[x-1])*x) / (Pixel[x] - Pixel[x-1]);

		Value = (Max*3 + Min) / 4;
		while (Pixel[x] < Value)
			++x;
		Right75 = ((Pixel[x] - Value)*(x-1) + (Value - Pixel[x-1])*x) / (Pixel[x] - Pixel[x-1]);

		Sharpness += Right75 - Right25 + Left25 - Left75;
	}
	Sharpness /= (m_YSize*2);
	pDoc->WriteStatus(2, "Sharp = %6.2f",Sharpness);
}




