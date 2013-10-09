// Geometry.cpp : implementation file
//

#include "stdafx.h"
#include "MuCat.h"
#include "Geometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeometry dialog


CGeometry::CGeometry(CWnd* pParent /*=NULL*/)
	: CDialog(CGeometry::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeometry)
	m_Distance = 0.0f;
	m_PixelSize = 0.0f;
	m_Gradient = 0.0f;
	//}}AFX_DATA_INIT
}


void CGeometry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeometry)
	DDX_Text(pDX, IDC_GEOMETRYDISTANCE, m_Distance);
	DDV_MinMaxFloat(pDX, m_Distance, 0.1f, 100.f);
	DDX_Text(pDX, IDC_GEOMETRYPIXELSIZE, m_PixelSize);
	DDV_MinMaxFloat(pDX, m_PixelSize, 3.f, 1000.f);
	DDX_Text(pDX, IDC_GEOMETRYGRADIENT, m_Gradient);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeometry, CDialog)
	//{{AFX_MSG_MAP(CGeometry)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeometry message handlers
