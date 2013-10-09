// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__A4CCC249_2D5C_11D3_BC29_00500406DD97__INCLUDED_)
#define AFX_CAMERA_H__A4CCC249_2D5C_11D3_BC29_00500406DD97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include <windows.h>
#include "StdAfx.h"
#include "843.h"

void Texit(char *Message);
#define CCDPIXELSIZE 30
#define VERTICAL_MAGNIFICATION 1.0

#define PORT1OFFSET   80
#define PORT2OFFSET   50

#define ROW_READ_TIME	1.70455		//fastest we can read a row in mS - experimentally determined on 04/11/2010
class CSI800Camera  
{
public:
	int AbortReadout();
	int EEpromWrite();
	int EEpromRead();
	int CoolerOff();
	int CoolerOn();
	int ImageTdi();
	int ImageExposeandRead();
	int ImageExpose();
	int ImageTest();
	int DmaStatus();
	int EndAcquisition();
	CSI800Camera();
	virtual ~CSI800Camera();
	int CharactersAvailable();
	char GetCharacter();
	void SendCharacter(char cChar);
	void ClearBuffer();

	int InitializeCamera(int index = 0, int baud = 19200);
	int OpenShutter();
	int CloseShutter();
	int LoadReadoutParameters();
	int LoadConfigurationParameters();
	int SendConfigurationParameters();
	int SendReadoutParameters();
	int SendOneReadoutParameter(int offset, DWORD value);
	int SendOneConfigurationParameter(int offset, DWORD value);
	int GetStatus();
	int PrepareAcquisition (WORD row,WORD col,LPWORD lpImage,LPSTR lpszFileName,WORD wDInterlace,WORD wSave,LPSTR lpszFitsHeader);

	struct PARAMETER
	{
		DWORD	SerialOrigin;				// Serial origin
		DWORD	SerialReadLength;			// Serial readout length
		DWORD	SerialBinningFactor;		// Serial binning factor
		DWORD	SerialPostscan;				// Serial postscan
		DWORD	ParallelOrigin;				// Parallel origin
		DWORD	ParallelReadLength;			// Parallel readout lenth
		DWORD	ParallelBinningFactor;		// Parallel binning factor
		DWORD	ParallelPostscan;			// Parallel postscan
		DWORD	ExposureTime;				// Exposure time
		DWORD	ContinousClearDisable;		// Continous clear disable (0 = enable; 1 = disable)
		DWORD	DSISampleTime;				// DSI sample time
		DWORD	AnalogAttenuation;			// Analog attenuation
		DWORD	Port1Offset;				// Port 1 offset
		DWORD	Port2Offset;				// Port 2 offset
		DWORD	Port3Offset;				// Port 3 offset
		DWORD	Port4Offset;				// Port 4 offset
		DWORD	TDIDelayTime;				// TDI delay time
		DWORD	Spare15;					// spare
		DWORD	Spare14;					// spare
		DWORD	Spare13;					// spare
		DWORD	Spare12;					// spare
		DWORD	Spare11;					// spare
		DWORD	Spare10;					// spare
		DWORD	TDICommand;					// 26 = internally paced TDI, 4 = normal readout,
		DWORD	Spare8;						// spare
		DWORD	TDIShutter;					// Bit 1 = 0 for shutter open, 1 for shutter closed
		DWORD	Spare6;						// spare
		DWORD	Spare5;						// spare
		DWORD	Spare4;						// spare
		DWORD	Spare3;						// spare
		DWORD	Spare2;						// spare
		DWORD	Spare1;						// spare
	};
	PARAMETER * lpParameter;

	struct CONFIGURATION
	{
		DWORD	InstrumentModel;			// Instrument model/type
		DWORD	InstrumentSerialNumber;		// Instrument serial number
		DWORD	HardwareRevision;			// Hardware revision number
		DWORD	SerialRegisterPhasing;		// Sets shift direction for serial register
		DWORD	SerialRegisterSplit;		// For multiport cameras only (0 = common; 1 = split)
		DWORD	SerialRegisterSize;			// Physical size of serial register
		DWORD	ParallelRegisterPhasing;	// Sets shift direction for parallel register
		DWORD	ParallelRegisterSplit;		// For multiport cameras only (0 = common; 1 = split)
		DWORD	ParallelRegisterSize;		// Physical size of parallel register
		DWORD	ParallelShiftDelay;			// Delay between shift states (in 100ns units)
		DWORD	NumberOfPorts;				// For multiport cameras only. Number of ports in use
		DWORD	ShutterCloseDelay;			// Delay between shutter close and start of readout (1 ms units)
		DWORD	CCDTemperatureOffset;		// Value subtracted from CCD temperature reading for single point correction
		DWORD	BackplateTemperatureOffset;	// Value subtracted from backplate temperature reading for single point correction
		DWORD	CCDTemperatureSetpoint;		// CCD temperature the system will attempt to achieve (in 1/10 Kelvin units)
		DWORD	DataWordSize;				// Data word size
		DWORD	MPPModeDisable;				// Disables MPP mode (0 = enable; 1 = disable)
		DWORD	Spare15;					// spare
		DWORD	Spare14;					// spare
		DWORD	Spare13;					// spare
		DWORD	Spare12;					// spare
		DWORD	Spare11;					// spare
		DWORD	Spare10;					// spare
		DWORD	Spare9;						// spare
		DWORD	Spare8;						// spare
		DWORD	Spare7;						// spare
		DWORD	Spare6;						// spare
		DWORD	Spare5;						// spare
		DWORD	Spare4;						// spare
		DWORD	Spare3;						// spare
		DWORD	Spare2;						// spare
		DWORD	Spare1;						// spare
	};
	CONFIGURATION * lpConfiguration;

	struct CAMSTATUS
	{
		DWORD	CCDTemperature;
		DWORD	BackplateTemperature;
		DWORD	HeadPressure;
		DWORD	ADCSpare4;
		DWORD	ADCSpare5;
		DWORD	ADCSpare6;
		DWORD	ADCSpare7;
		DWORD	ADCSpare8;
		DWORD	ShutterStatus;
		DWORD	XIRQStatus;
		DWORD	Spare1;
		DWORD	Spare2;
		DWORD	Spare3;
		DWORD	Spare4;
		DWORD	Spare5;
		DWORD	Spare6;
	};
	CAMSTATUS * lpCamStatus;

	// type definition for DLL function calls
	typedef DWORD (*INSTALL_ISR)(WORD device_id,WORD vendor_id,WORD index);
	typedef void (*REMOVE_ISR)(void);
	typedef void (*INIT_DMA)(WORD row, WORD col, WORD *array);
	typedef void (*INIT_DMA_SYNC)(WORD row, WORD col, WORD *array, LPSTR lpszFileName, WORD wDInterlace, WORD wSave, LPSTR lpszFitsHeader);
	typedef void (*START_DMA)(BYTE);
	typedef BYTE (*DMA_DONE)(void);
	typedef void (*END_DMA)(void);
	typedef void (*INIT_COM)(DWORD baud,WORD parity,WORD bits,WORD stop_bits,WORD buffersize);
	typedef void (*SEND_BREAK)(DWORD);
	typedef void (*SEND_CHAR)(BYTE);
	typedef BYTE (*GET_CHAR)(void);
	typedef void (*SEND_STRING)(LPBYTE,int);
	typedef BYTE (*GET_STRING)(WORD,BYTE,CHAR *);
	typedef DWORD (*CHARS_AVAIL)(VOID);
	typedef DWORD (*CHARS_TO_SEND)(VOID);
	typedef void (*CLEAR_BUFF)(VOID);
	typedef BYTE (*SENDFILE)(DWORD, char *);
	typedef BYTE (*CHECK_FRAME_COMPLETE)(VOID);
	typedef void (*RESET_FRAME_COMPLETE)(VOID);
	typedef DWORD (*GET_FRAME_COUNT)(VOID);

//void __declspec(dllexport) init_dma_sync(WORD	row,						// pixels in a row
//										 WORD	col,						// number of columns
//										 WORD	*array,						// pointer to image array
//										 LPSTR	lpszFileName,				// file name of flat field image
//										 WORD	wDInterlace,				// flag for de-interlace
//										 WORD	wSave,						// flag for saving
//										 LPSTR	lpszFitsHeader)				// header for FITS file

	struct CAMDLL
	{
		INSTALL_ISR				lpInstallIsr;
		REMOVE_ISR				lpRemoveIsr;
		INIT_DMA				lpInitDma;
		INIT_DMA_SYNC			lpInitDmaSync;
		START_DMA				lpStartDma;
		DMA_DONE				lpDmaDone;
		END_DMA					lpEndDma;
		INIT_COM				lpInitCom;
		SEND_BREAK				lpSendBreak;
		SEND_CHAR				lpSendChar;
		GET_CHAR				lpGetChar;
		SEND_STRING				lpSendString;
		GET_STRING				lpGetString;
		CHARS_AVAIL				lpCharsAvail;
		CHARS_TO_SEND			lpCharsToSend;
		CLEAR_BUFF				lpClearBuff;
		SENDFILE				lpSendfile;
		CHECK_FRAME_COMPLETE	lpCheckFrameComplete;
		RESET_FRAME_COMPLETE	lpResetFrameComplete;
		GET_FRAME_COUNT			lpGetFrameCount;
	};
	CAMDLL * lpCamDLL;

protected:
	int MapDll();
	int SendCommand(char cCommand);
	int ReceiveCharacter(char* cCharacter, int iTimeout);
	int ExpectYN();
	int ReceiveDWord(LPDWORD lpValue);
	int SendDWord(DWORD dwValue);



private:
	int		m_IsrActive;				// flag for active interrupt service routine
	int		m_DmaActive;				// flag for active DMA
	int		m_CameraInitialized;		// flag for camera ready
	char	szLastErrorMessage[256];	// string holds last error
	char	szLastErrorSource[256];		// string holds last error



public:
	int GetPepperCount(void);
	void SetPepper(int PepperLevel);
	int GetPepper(void);
	float GetTemperature(void);
	int GetNumActiveColumns(void);
	int TDIReadout(C843 *pSlide, unsigned long ** image, int XSize, int YSize, int Bin, double FirstStop, long FinalPosition, double StepSize, bool IsDark, bool ShutterOpen, int FrameNum, int NumFrames, unsigned int TDIDelay);
	void SetGain(int Gain, int Speed);
	float GetGain(int Gain, int Speed);
	void ExposeandReadoutRegion(float exposure, unsigned long ** image, int X, int Y, int XSize, int YSize, int Bin);
	void StillImage(float exposure, unsigned long ** image, int XSize, int YSize, int Bin);
protected:
	int m_PepperCount;
	int m_Pepper;
public:
	void GetCCDSize(int * NumCols, int * NumRows);
private:
	int m_NumRows;
	int m_NumColumns;
public:
	void CExit(char * Message);
	void GetTempPressure(float *Temperature, float *Pressure);
	void Restart(void);
protected:
	int ImageInternalTDI(void);
};

// error definitions
#define E_TIMEOUT			1
#define E_DATA_ERROR		2
#define E_COM_ERROR			3
#define E_DMA_ACTIVE		4
#define E_DMA_NOT_ACTIVE	5

extern CSI800Camera Camera;


#endif // !defined(AFX_CAMERA_H__A4CCC249_2D5C_11D3_BC29_00500406DD97__INCLUDED_)
