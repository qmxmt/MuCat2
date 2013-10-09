// MuCatDoc.cpp : implementation of the CMuCatDoc class
//

#include "stdafx.h"
#include "MuCat.h"
#include "MuCatDoc.h"
#include "BinDialog.h"
#include "DimDialog.h"
#include "SpecDialog.h"
#include "XrayDialog.h"
#include "PositionDialog.h"
#include "MainFrm.h"
#include "GainDialog.h"
#include "MagDialog.h"
#include "DurationDialog.h"
#include "Geometry.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMuCatDoc

IMPLEMENT_DYNCREATE(CMuCatDoc, CDocument)

BEGIN_MESSAGE_MAP(CMuCatDoc, CDocument)
	//{{AFX_MSG_MAP(CMuCatDoc)
	ON_COMMAND(ID_PARAMETER_BIN, OnParameterBin)
	ON_COMMAND(IDD_PARAMETER_GAIN, OnParameterGain)
	ON_COMMAND(ID_POSITION, OnPosition)
	ON_COMMAND(ID_PARAMETER_MAG, OnParameterMag)
	ON_COMMAND(ID_PARAMETER_EXP, OnParameterExp)
	ON_COMMAND(ID_EDIT_SPEC, OnEditSpec)
	ON_COMMAND(ID_EDIT_XRAY, OnEditXray)
	ON_COMMAND(ID_PARAMETER_DIM, OnParameterDim)
	ON_COMMAND(ID_EDIT_GEOMETRY, OnEditGeometry)
	ON_COMMAND(ID_BUTTONDIM, OnButtondim)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMuCatDoc construction/destruction

CMuCatDoc::CMuCatDoc():m_Turntable(2,ROTATIONAL_DIRECT),m_Slide(1,LINEAR_DIRECT),
	m_Elevator(3,LINEAR_GEARED)
{
	// TODO: add one-time construction code here
	CFile HeaderFile;
	m_NumActiveCols = 10000; // Inhibit initial height adjustment.
	if (HeaderFile.Open("header.bin",CFile::modeRead))
	{
		HeaderFile.Read(&m_Header, 512);
		SetBin(m_Header.bin);
	}
	else
	{
		SetBin(2);
		m_Header.gain = 0;
		m_Header.speed = 3;
	}
	m_StillExposure = 1;
}

CMuCatDoc::~CMuCatDoc()
{
	m_Header.bin = m_Bin;
	CFile HeaderFile("header.bin", CFile::modeWrite | CFile::modeCreate);
	HeaderFile.Write(&m_Header,512);
}

BOOL CMuCatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMuCatDoc serialization

void CMuCatDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		ar.Read(&m_Header, 512);
		SetBin(m_Header.bin);
		m_Theta = m_Header.theta/1000.0;
		m_Elevation = m_Header.z;
		m_Turntable.Move(-m_Header.theta);
		m_Elevator.Move(m_Elevation*(-30));
		GetCCDSize();
		SetGain();
		SetMaxHeight();
	// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMuCatDoc diagnostics

#ifdef _DEBUG
void CMuCatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMuCatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMuCatDoc commands

void CMuCatDoc::OnParameterBin() 
{
	// TODO: Add your command handler code here
	CBinDialog aDlg;
	aDlg.m_Bin = m_Bin;
	if (aDlg.DoModal() == IDOK)
		SetBin(aDlg.m_Bin);
}

int CMuCatDoc::GetBin()
{
	return m_Bin;
}

void CMuCatDoc::OnEditSpec() 
{
	// TODO: Add your command handler code here
	CSpecDialog aDlg;
	aDlg.m_Comment = m_Header.scan;
	aDlg.m_Description = m_Header.specimen;
	aDlg.m_Owner = m_Header.owner;
	aDlg.m_User = m_Header.user;
	if (aDlg.DoModal() == IDOK)
	{
		strcpy(m_Header.scan, aDlg.m_Comment);
		strcpy(m_Header.specimen, aDlg.m_Description);
		strcpy(m_Header.owner, aDlg.m_Owner);
		strcpy(m_Header.user, aDlg.m_User);
	}
}


void CMuCatDoc::OnEditXray() 
{
	// TODO: Add your command handler code here
	CXrayDialog aDlg;
	aDlg.m_Current = m_Header.current;
	aDlg.m_Filter  = m_Header.thickness;
	aDlg.m_Voltage = m_Header.voltage;
	aDlg.m_PepperThreshold = m_Header.pepper;
	aDlg.m_Issue = m_Header.issue;
	if (Camera.GetPepper())
		aDlg.m_PepperCheck = TRUE;
	if (aDlg.DoModal() == IDOK)
	{
		m_Header.current = aDlg.m_Current;
		m_Header.thickness = aDlg.m_Filter;
		m_Header.voltage = aDlg.m_Voltage;
		m_Header.pepper = aDlg.m_PepperThreshold;
		m_Header.issue = aDlg.m_Issue;
		if (aDlg.m_PepperCheck)
			Camera.SetPepper(aDlg.m_PepperThreshold);
		else
			Camera.SetPepper(0);
	}
}

/*void CMuCatDoc::WriteStatus(int Pane, LPCTSTR Text, int Value1, int Value2)
{
	CString String;
	String.Format(Text,Value1,Value2);
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->GetStatus()->SetPaneText(Pane, String);
}*/

void CMuCatDoc::WriteStatus(int Pane, LPCTSTR Text, ...)
{
	CString String;
	double *Arg = (double*)((&Text)+1);
	String.Format(Text,Arg[0],Arg[1],Arg[2],Arg[3]);
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->GetStatus()->SetPaneText(Pane, String);
}

void CMuCatDoc::GetCCDSize()
{
	Camera.GetCCDSize(&m_NumCCDCols, &m_NumCCDRows);
	m_NumActiveCols = Camera.GetNumActiveColumns();
}

int CMuCatDoc::GetNumCCDCols()
{
	return m_NumCCDCols;
}

int CMuCatDoc::GetNumCCDRows()
{
	return m_NumCCDRows;
}

void CMuCatDoc::SetBin(int Bin)
{
	m_Bin = Bin;
	WriteStatus(1,"Bin: %1d",m_Bin);
	m_CCDBinnedHeight = m_NumActiveCols / m_Bin;
	if (m_Header.num_slices > m_CCDBinnedHeight)
		m_Header.num_slices = m_CCDBinnedHeight;
}

void CMuCatDoc::OnParameterGain() 
{
	// TODO: Add your command handler code here
	CGainDialog aDlg;
	aDlg.m_Gain = m_Header.gain;
	aDlg.m_Speed = m_Header.speed;
	if (aDlg.DoModal() == IDOK)
	{
		m_Header.gain = aDlg.m_Gain;
		m_Header.speed = aDlg.m_Speed;
		SetGain();
	}
}


void CMuCatDoc::SetGain()
{
	Camera.SetGain(m_Header.gain, m_Header.speed);
}

void CMuCatDoc::OnPosition() 
{
	// TODO: Add your command handler code here
	CPositionDialog aDlg;
	aDlg.m_StepSize = CCD_PIXEL_SIZE*m_Bin/m_Header.mag_factor;
	aDlg.m_Rotation = m_Theta;
	aDlg.m_Elevation = m_Elevation;
	aDlg.m_pTurntable = &m_Turntable;
	aDlg.m_pSlide = &m_Slide;
	aDlg.m_pElevator = &m_Elevator;
	aDlg.m_Translation = (int)(m_Slide.GetPosition()/aDlg.m_StepSize);
	if (aDlg.DoModal()== IDOK)
	{
		m_Theta = aDlg.m_Rotation;
		m_Elevation = aDlg.m_Elevation;
		if (aDlg.m_Translation < -aDlg.m_MaxTranslation)
			aDlg.m_Translation = -aDlg.m_MaxTranslation;
		if (aDlg.m_Translation > aDlg.m_MaxTranslation)
			aDlg.m_Translation = aDlg.m_MaxTranslation;
	}
	m_Turntable.Move(-(m_Header.theta=(long)m_Theta*1000));
	m_Slide.Move((int)(aDlg.m_StepSize*aDlg.m_Translation));
	m_Elevator.Move(aDlg.m_Elevation*(-30));
	m_Header.z = (long)aDlg.m_Elevation;
}

void CMuCatDoc::OnParameterDim() 
{
	// TODO: Add your command handler code here
	CDimDialog aDlg;
	aDlg.m_Height = m_Header.num_slices;
	aDlg.m_MaxHeight = m_CCDBinnedHeight;
	aDlg.m_ScanLength = m_Header.num_samples;
	aDlg.m_NumProj = m_Header.num_proj;
	aDlg.m_NumBlocks = m_Header.num_blocks;
	aDlg.m_Shift = m_Header.slices_per_block;
	if (m_Header.distance < 0.1 || m_Header.pixel_size < 0.1)
		aDlg.m_Distance = 0;
	else
		aDlg.m_Distance = m_Header.distance * 10000 / m_Header.pixel_size;
	if (aDlg.DoModal() == IDOK)
	{
		m_Header.num_slices = aDlg.m_Height;
		m_Header.num_samples = aDlg.m_ScanLength;
		m_Header.num_proj = aDlg.m_NumProj;
		m_Header.slices_per_block = aDlg.m_Shift;
		m_Header.num_blocks = aDlg.m_NumBlocks;
	}
	UpdateAllViews(NULL);
}

void CMuCatDoc::SetMaxHeight()
{
	m_CCDBinnedHeight = m_NumActiveCols/m_Bin;
}

void CMuCatDoc::OnParameterMag() 
{
	// TODO: Add your command handler code here
	CMagDialog aDlg;
	aDlg.m_MagFactor = m_Header.mag_factor;
	if (aDlg.DoModal() == IDOK)
		m_Header.mag_factor = aDlg.m_MagFactor;
}

struct thead* CMuCatDoc::GetHeader()
{
	return &m_Header;
}


void CMuCatDoc::OnParameterExp() 
{
	// TODO: Add your command handler code here
	CDurationDialog aDlg;
	aDlg.m_Duration = (int)(m_Header.exposure/1000.0);
	aDlg.m_StillDuration = m_StillExposure;
	if (aDlg.DoModal() == IDOK)
	{
		m_Header.exposure = (float)(aDlg.m_Duration*1000.0);
		m_StillExposure = aDlg.m_StillDuration;
	}
}

int CMuCatDoc::GetStillExposure()
{
	return m_StillExposure;
}

C842* CMuCatDoc::GetSlide()
{
	return &m_Slide;
}

C842* CMuCatDoc::GetTurntable()
{
	return &m_Turntable;
}

void CMuCatDoc::SetTheta(double Theta)
{
	m_Theta = Theta;
}

double CMuCatDoc::GetTheta()
{
	return m_Theta;
}

C842* CMuCatDoc::GetElevator()
{
	return &m_Elevator;
}

void CMuCatDoc::SetElevation(int Elevation)
{
	m_Elevation = Elevation;
}

int CMuCatDoc::GetElevation()
{
	return m_Elevation;
}

void CMuCatDoc::OnEditGeometry() 
{
	// TODO: Add your command handler code here
	CGeometry aDlg;
	aDlg.m_Distance = m_Header.distance;
	aDlg.m_PixelSize = m_Header.pixel_size;
	aDlg.m_Gradient = m_Header.gradient;
	if (aDlg.DoModal() == IDOK)
	{
		m_Header.distance = aDlg.m_Distance;
		m_Header.pixel_size = aDlg.m_PixelSize;
		m_Header.gradient = aDlg.m_Gradient;
	}
}

void CMuCatDoc::OnButtondim() 
{
	// TODO: Add your command handler code here
	OnParameterDim();
}
