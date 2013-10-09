// MuCatDoc.h : interface of the CMuCatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUCATDOC_H__BFC9FE2D_EC06_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_MUCATDOC_H__BFC9FE2D_EC06_11D1_A406_0000010049AB__INCLUDED_

#include "Camera.h"	// Added by ClassView
#include "842.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#define CCD_PIXEL_SIZE 22.5

struct thead
  {
    short xsize,ysize,zsize,lmarg,rmarg,tmarg,bmarg,tzmarg,bzmarg,\
     num_samples,num_proj,num_blocks,num_slices,bin,gain,speed,pepper,issue,spare_int[14];
    float scale,offset,voltage,current,thickness,pixel_size,distance,exposure,\
     mag_factor,gradient,spare_float[3];
	long slices_per_block,z,theta;
    char time[26],duration[12],owner[21],user[5],specimen[32],scan[32],\
     comment[64],spare_char[192];
  };

class CMuCatDoc : public CDocument
{
protected: // create from serialization only
	CMuCatDoc();
	DECLARE_DYNCREATE(CMuCatDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMuCatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetElevation();
	void SetElevation(int Elevation);
	C842* GetElevator();
	double GetTheta();
	void SetTheta(double Theta);
	C842* GetTurntable();
	C842* GetSlide();
	int GetStillExposure();
	struct thead* GetHeader();
	void SetMaxHeight();
	void SetGain();
	void SetBin(int Bin);
	int GetNumCCDRows();
	int GetNumCCDCols();
	void GetCCDSize();
	void WriteStatus(int Pane, LPCTSTR Text, ...);
//	void WriteStatus(int Pane, LPCTSTR Text, int Value1 = 0, int Value2 = 0);
	int GetBin();
	virtual ~CMuCatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnEditSpec();
	afx_msg void OnEditXray();
	afx_msg void OnParameterDim();
	afx_msg void OnEditGeometry();
protected:

// Generated message map functions
protected:
	int m_Elevation;
	int m_NumActiveCols;
	int m_CCDBinnedHeight;
	double m_Theta;
	int m_NumCCDRows;
	int m_NumCCDCols;
	int m_StillExposure;
	int m_Bin;
	C842 m_Slide;
	C842 m_Elevator;
	C842 m_Turntable;
	struct thead m_Header;
	//{{AFX_MSG(CMuCatDoc)
	afx_msg void OnParameterBin();
	afx_msg void OnParameterGain();
	afx_msg void OnPosition();
	afx_msg void OnParameterMag();
	afx_msg void OnParameterExp();
	afx_msg void OnButtondim();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUCATDOC_H__BFC9FE2D_EC06_11D1_A406_0000010049AB__INCLUDED_)
