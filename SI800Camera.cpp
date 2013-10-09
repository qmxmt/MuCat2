// Camera.cpp: implementation of the CSI800Camera class.
//
//////////////////////////////////////////////////////////////////////
#define CAMERABINFILE "x3968C+3_1uS.bin"	//latest DSP file as of 2009-11-06, for self paced TDI


#include <stdio.h>
#include "SI800Camera.h"
#include "MuCat.h"
#include "C843Profile.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSI800Camera Camera;

CSI800Camera::CSI800Camera()
: m_PepperCount(0)
, m_Pepper(0)
, m_CameraInitialized(0)
, m_NumRows(0)
, m_NumColumns(0)
{
	lpParameter = new(PARAMETER);
	lpConfiguration = new(CONFIGURATION);
	lpCamDLL = new(CAMDLL);
	lpCamStatus = new(CAMSTATUS);
	m_IsrActive = FALSE;
	m_DmaActive = FALSE;

}

CSI800Camera::~CSI800Camera()
{
	CoolerOff();
	if (m_DmaActive) (lpCamDLL->lpEndDma)();			// end DMA if it is still active
	if (m_IsrActive) (lpCamDLL->lpRemoveIsr)();			// remove interrupt service routine if still present
	delete lpParameter;
	delete lpConfiguration;
	delete lpCamStatus;
	delete lpCamDLL;
}

///////////////////////////////////////////////////////////////////////////////
// high level functions
//		high level functions are called from outside and provide
//		the class' functionality
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// InitializeCamera
//	downloads the camera code defined in the SiSettings.ini file
//
//	Parameters:
//		none
//
//	Return:
//		none
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::InitializeCamera(int index, int baud)
{
	int		error;
	BYTE		send_error;

	error = 0;							// assume success - be positive

	error = MapDll();
	if (error) return error;

	error = (lpCamDLL->lpInstallIsr)(0x80B6,0x10E8,index);	// start the interface

	m_IsrActive = TRUE;
	(lpCamDLL->lpInitCom)(baud,0,8,1,9000);					// setp UART
	Restart();
//	C843::Pause(5000);
//	(lpCamDLL->lpSendBreak)(200);
//	C843::Pause(5000);

	//if (send_error) return send_error;

	m_CameraInitialized = TRUE;
	//Restart();
	CoolerOn();
	CloseShutter();

	return 0;// No error
//	return error;

}

///////////////////////////////////////////////////////////////////////////////
// OpenShutter
//	opens the shutter
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::OpenShutter()
{
	int	error;

	error =  SendCommand('A');
	if (error) return error;
	error = ExpectYN();
	
	return error;

}

///////////////////////////////////////////////////////////////////////////////
// CloseShutter
//	closes the shutter
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::CloseShutter()
{
	int error;

	error = SendCommand('B');
	if (error) return error;
	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// GetStatus
//	receives status from camers
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::GetStatus()
{
	int error;
	int i;
	error = SendCommand('I');							// command to receive status
	if (error) Texit("Error getting camera status");

	for (i=0; i<16; i++)								// receive 16 DWORDs
	{
		error = ReceiveDWord((LPDWORD)lpCamStatus + i);
		if (error) Texit("Error getting camera status");
	}

	error = ExpectYN();
	if (error) Texit("Error getting camera status");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// LoadReadoutParameters
//	receives the readout parameters from camera and fills in the structure
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::LoadReadoutParameters()
{
	int error;
	int i;

	error = SendCommand('H');							// command to receive the readout parameters
	if (error) return error;

	for (i=0; i<32; i++)								// receive 32 DWORDs
	{
		error = ReceiveDWord((LPDWORD)lpParameter + i);
		if (error) return error;
	}

	error = ExpectYN();

	return error;
}

///////////////////////////////////////////////////////////////////////////////
// SendReadoutParameters
//	sends the readout parameters to camera
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendReadoutParameters()
{
	int error;
	int i;

	error = SendCommand('F');							// command to send the Readout parameters
	if (error) return error;

	for (i=0; i<32; i++)								// receive 32 DWORDs
	{
		error = SendDWord(*((LPDWORD)lpParameter + i));
		if (error) return error;
	}

	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// SendOneReadoutParameter
//	sends one readout parameters to camera
//
//	Parameters:
//		offset, value
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendOneReadoutParameter(int offset, DWORD value)
{
	int error;

	error = SendCommand('G');							// command to send one Readout parameters
	if (error) return error;
	*((LPDWORD)lpParameter + offset) = value;
	error = SendDWord(offset);							// send offset down
	error = SendDWord(*((LPDWORD)lpParameter + offset));	// send parameter

	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// LoadConfigurationParameters
//	receives the configuration parameters from camera and fills in the structure
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::LoadConfigurationParameters()
{
	int error;
	int i;

	error = SendCommand('L');							// command to receive the configuration parameters
	if (error) return error;

	for (i=0; i<32; i++)								// receive 32 DWORDs
	{
		error = ReceiveDWord((LPDWORD)lpConfiguration + i);
		if (error) return error;
	}

	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// SendConfigurationParameters
//	sends the configuration parameters to camera
//
//	Parameters:
//		none
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendConfigurationParameters()
{
	int error;
	int i;

	error = SendCommand('J');							// command to send the configuration parameters
	if (error) return error;

	for (i=0; i<32; i++)								// receive 32 DWORDs
	{
		error = SendDWord(*((LPDWORD)lpConfiguration + i));
		if (error) return error;
	}

	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// SendOneConfigurationParameter
//	sends one configuration parameter to camera
//
//	Parameters:
//		offset, value
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendOneConfigurationParameter(int offset, DWORD value)
{
	int error;

	error = SendCommand('K');							// command to send one Configuration parameters
	if (error) return error;
	*((LPDWORD)lpConfiguration + offset) = value;
	error = SendDWord(offset);							// send offset down
	error = SendDWord(*((LPDWORD)lpConfiguration + offset));	// send parameter

	error = ExpectYN();
	
	return error;
}

///////////////////////////////////////////////////////////////////////////////
// PrepareAcquisition
//	prepares and starts the DMA
//
//	Parameters:
//		nSer:			serial dimension of image
//		nPar:			parallel dimension of image
//		lpImage:		pointer to image buffer
//		lpszFileName	ptr to file name for fast save
//		wDInterlace		de-interlace flag
//		wSave			fast save flag
//		lpszFitsHeader	ptr to FITS header string
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::PrepareAcquisition(WORD row,				// serial length
								WORD col,				// parallel length
								LPWORD lpImage,			// pointer to image
								LPSTR lpszFileName,		// ptr to file name for fast save
								WORD wDInterlace,		// de-interlace flag
								WORD wSave,				// fast save flag
								LPSTR lpszFitsHeader)	// ptr to FITS header string
{
	if (m_DmaActive)
		return E_DMA_ACTIVE;
	if (IsBadReadPtr(lpImage, row*col*sizeof(WORD)))	// check what they gave us
		return E_DATA_ERROR;							// return if bogus
	(lpCamDLL->lpInitDmaSync)(row, col, lpImage, lpszFileName, wDInterlace, wSave, lpszFitsHeader);			// start the DMA
	(lpCamDLL->lpStartDma)(0);							// allways normal mode, video mode not supported here
	m_DmaActive = TRUE;									// flag DMA started

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// EndAcquisition
//	finishes the DMA
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::EndAcquisition()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	(lpCamDLL->lpEndDma)();								// end DMA
	m_DmaActive = FALSE;								// release flag
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// DmaStatus
//	retrieves the readout status
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::DmaStatus()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return (int)(lpCamDLL->lpDmaDone)();				// just hand through
}

///////////////////////////////////////////////////////////////////////////////
// ImageTest
//	requests a test image
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ImageTest()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return SendCommand('C');

}

///////////////////////////////////////////////////////////////////////////////
// ImageTest
//	requests a regular image with shuttered exposure
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ImageExpose()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return SendCommand('D');
}

///////////////////////////////////////////////////////////////////////////////
// ImageRead
//	requests a dark image with closed shutter
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ImageExposeandRead()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return SendCommand('D');
}

///////////////////////////////////////////////////////////////////////////////
// ImageTdi
//	requests a tdi image
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ImageTdi()
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return SendCommand('Y');
}

///////////////////////////////////////////////////////////////////////////////
// CoolerOn
//	turns cooler on
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::CoolerOn()
{
	if (SendCommand('S'))
		Texit("Error turning camera cooler on");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// CoolerOff
//	turns cooler off
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::CoolerOff()
{
	return SendCommand('T');
}

///////////////////////////////////////////////////////////////////////////////
// EEpromRead
//	causes the EEPROM in the camera to be read into the camera's configuration
//	buffer.
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::EEpromRead()
{
	return SendCommand('P');
}

///////////////////////////////////////////////////////////////////////////////
// EEpromWrite
//	causes the camera's configuration buffer to be copied to the camera's EEPROM
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::EEpromWrite()
{
	return SendCommand('M');
}

///////////////////////////////////////////////////////////////////////////////
// AbortReadout
//	aborts an ongoing exposure (camera cannot be stopped during actual readout)
//
//	Parameters:
//		none
//
//	Return:
//		error code
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::AbortReadout()
{
	return SendCommand('O');

}


///////////////////////////////////////////////////////////////////////////////
// medium level functions
//		medium level functions can be called from outside the class but
//		provide only limited functionality
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SendCommand
//	sends a command to the camera and waits for the echo
//	times out if no echo is received after timeout time
//
//	Parameters:
//		command to be sent
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendCommand(char cCommand)
{
	int		error;
	int		iTimeout = 10000;							// set timeout to 10 seconds
	char	cEcho = 0;									// set echo to invalid

	ClearBuffer();										// clear the buffer
	SendCharacter(cCommand);							// send the command

	
	error = ReceiveCharacter(&cEcho, iTimeout);
	if (error) return error;

	if (cEcho != cCommand)
	{
		sprintf(szLastErrorMessage, "SendCommand: Received different character than sent");
		return (E_COM_ERROR);
	}

	return (NO_ERROR);
}

///////////////////////////////////////////////////////////////////////////////
// ReceiveDWord
//	receives four characters from buffer and converts them to a DWORD
//	times out if DWORD is not received within timeout time (10 seconds)
//
//	Parameters:
//		DWORD pointer
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ReceiveDWord(LPDWORD lpValue)
{
	int		error;
	int		i;
	int		iTimeout = 10000;
	char	cMyChar;
	BYTE	bChar;
	DWORD	dwMyDword = 0;

	for (i=0; i<4; i++)
	{
		error = ReceiveCharacter(&cMyChar, iTimeout);
		if (error) return error;

		bChar = (BYTE)cMyChar;							// make it unsigned, otherwise there will be an error in the calculation below
		dwMyDword = dwMyDword << 8;						// shift up
		dwMyDword += (DWORD)bChar;						// and add byte

	}

	*lpValue = dwMyDword;

	return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// SendDWord
//	sends a DWORD as four characters to camera
//	times out if DWORD is not received within timeout time (10 seconds)
//
//	Parameters:
//		DWORD pointer
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::SendDWord(DWORD dwValue)
{

	SendCharacter((char) ((dwValue >>24) & 0xff));
	SendCharacter((char) ((dwValue >>16) & 0xff));
	SendCharacter((char) ((dwValue >>8) & 0xff));
	SendCharacter((char) (dwValue & 0xff));

	return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// ExpectYN
//	checks if the camera responds with 'Y' or 'N'
//	error if neither 'Y' or 'N' or if timeout (30 seconds)
//
//	Parameters:
//		BOOL yes
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ExpectYN()
{
	char	cYes;
	int		error;
	int		iTimeout = 30000;							// set to 30 second timeout

	error = ReceiveCharacter(&cYes, iTimeout);			// get the response
	if (error) return error;

	if ((cYes != 'Y') && (cYes != 'N'))
	{
		sprintf(szLastErrorMessage, "ExpectYN: Unexpected response");
		return E_COM_ERROR;
	}
	if (cYes == 'N')
	{
		sprintf(szLastErrorMessage, "ExpectYN: Received NO");
		return E_COM_ERROR;
	}

	return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// low level functions
//		these functions are only called within the Class
//		they are all protected
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ReceiveCharacter
//	waits for a character to be available.
//  times out
//
//	Parameters:
//		character returnes
//		timeout in ms
//
//	Return:
//		error
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::ReceiveCharacter(char* cCharacter, int iTimeout)
{
	DWORD	dwTargetTime;
	char	cChar = 0;
	BOOL	bGotIt = FALSE;

	dwTargetTime = GetTickCount() + iTimeout;			// start timeout
	
	while (GetTickCount() < dwTargetTime)
	{
		if (CharactersAvailable())						// are there characters?
		{
			cChar = GetCharacter();						// get the character
			bGotIt = TRUE;
			break;										// break out while loop
		}
	}

	if (!bGotIt)
	{
		sprintf(szLastErrorMessage, "ReceiveCharacter: Timeout");
		return (E_TIMEOUT);
	}

	*cCharacter = cChar;

	return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
// CharactersAvailable
//	returns the number of characters available in buffer
//
//	Parameters:
//		none
//
//	Return:
//		number of characters available
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::CharactersAvailable()
{

	return (lpCamDLL->lpCharsAvail)();

}

///////////////////////////////////////////////////////////////////////////////
// GetCharacter
//	returns a character from buffer
//
//	Parameters:
//		none
//
//	Return:
//		character
//
///////////////////////////////////////////////////////////////////////////////
char CSI800Camera::GetCharacter()
{

	return (lpCamDLL->lpGetChar)();

}

///////////////////////////////////////////////////////////////////////////////
// SendCharacter
//	sends a character to camera
//
//	Parameters:
//		character
//
//	Return:
//		none
//
///////////////////////////////////////////////////////////////////////////////
void CSI800Camera::SendCharacter(char cChar)
{

	(lpCamDLL->lpSendChar)(cChar);

}

///////////////////////////////////////////////////////////////////////////////
// ClearBuffer
//	clears the UART buffer
//
//	Parameters:
//		none
//
//	Return:
//		none
//
///////////////////////////////////////////////////////////////////////////////
void CSI800Camera::ClearBuffer()
{

	(lpCamDLL->lpClearBuff)();

}

///////////////////////////////////////////////////////////////////////////////
// MapDll
//	maps external DLL by explicitly loading it
//
//	Parameters:
//		none
//
//	Return:
//		none
//
///////////////////////////////////////////////////////////////////////////////
int CSI800Camera::MapDll()
{

	BOOL		fRunTimeLinkSuccess = FALSE;
    char		lpValueString[40];		// return value buffer 
    DWORD		rSize;					// return length
	HINSTANCE	hinstLib;				// handle for loaded library


	// read the DLL name
	//rSize = GetPrivateProfileString("Interface", "PciDll", "", lpValueString, sizeof(lpValueString), "SiSettings.ini");
	//if (!rSize) return (-1);


	hinstLib = LoadLibrary("Specinst.dll");			// load DLL
	if (hinstLib == NULL) return (-1);

	// get all process addresses
	lpCamDLL->lpInstallIsr =			(INSTALL_ISR)			GetProcAddress(hinstLib, "install_isr");
	lpCamDLL->lpRemoveIsr =				(REMOVE_ISR)			GetProcAddress(hinstLib, "remove_isr");
	lpCamDLL->lpInitDma =				(INIT_DMA)				GetProcAddress(hinstLib, "init_dma");
	lpCamDLL->lpInitDmaSync =			(INIT_DMA_SYNC)			GetProcAddress(hinstLib, "init_dma_sync");
	lpCamDLL->lpStartDma =				(START_DMA)				GetProcAddress(hinstLib, "start_dma");
	lpCamDLL->lpDmaDone =				(DMA_DONE)				GetProcAddress(hinstLib, "dma_done");
	lpCamDLL->lpEndDma =				(END_DMA)				GetProcAddress(hinstLib, "end_dma");
	lpCamDLL->lpInitCom =				(INIT_COM)				GetProcAddress(hinstLib, "init_com");
	lpCamDLL->lpSendBreak =				(SEND_BREAK)			GetProcAddress(hinstLib, "send_break");
	lpCamDLL->lpSendChar =				(SEND_CHAR)				GetProcAddress(hinstLib, "send_char");
	lpCamDLL->lpGetChar =				(GET_CHAR)				GetProcAddress(hinstLib, "get_char");
	lpCamDLL->lpSendString =			(SEND_STRING)			GetProcAddress(hinstLib, "send_string");
	lpCamDLL->lpGetString =				(GET_STRING)			GetProcAddress(hinstLib, "get_string");
	lpCamDLL->lpCharsAvail =			(CHARS_AVAIL)			GetProcAddress(hinstLib, "chars_avail");
	lpCamDLL->lpCharsToSend =			(CHARS_TO_SEND)			GetProcAddress(hinstLib, "chars_to_send");
	lpCamDLL->lpClearBuff =				(CLEAR_BUFF)			GetProcAddress(hinstLib, "clear_buff");
	lpCamDLL->lpSendfile =				(SENDFILE)				GetProcAddress(hinstLib, "sendfile");
	lpCamDLL->lpCheckFrameComplete =	(CHECK_FRAME_COMPLETE)	GetProcAddress(hinstLib, "check_frame_complete");
	lpCamDLL->lpResetFrameComplete =	(RESET_FRAME_COMPLETE)	GetProcAddress(hinstLib, "reset_frame_complete");
	lpCamDLL->lpGetFrameCount =			(GET_FRAME_COUNT)		GetProcAddress(hinstLib, "get_frame_count");
	// check if all were mapped
	fRunTimeLinkSuccess =	(lpCamDLL->lpInstallIsr != NULL) &&
							(lpCamDLL->lpRemoveIsr != NULL) &&
							(lpCamDLL->lpInitDma != NULL) &&
							(lpCamDLL->lpInitDmaSync != NULL) &&
							(lpCamDLL->lpStartDma != NULL) &&
							(lpCamDLL->lpDmaDone != NULL) &&
							(lpCamDLL->lpEndDma != NULL) &&
							(lpCamDLL->lpInitCom != NULL) &&
							(lpCamDLL->lpSendBreak != NULL) &&
							(lpCamDLL->lpSendChar != NULL) &&
							(lpCamDLL->lpGetChar != NULL) &&
							(lpCamDLL->lpSendString != NULL) &&
							(lpCamDLL->lpGetString != NULL) &&
							(lpCamDLL->lpCharsAvail != NULL) &&
							(lpCamDLL->lpCharsToSend != NULL) &&
							(lpCamDLL->lpClearBuff != NULL) &&
							(lpCamDLL->lpSendfile != NULL) &&
							(lpCamDLL->lpCheckFrameComplete != NULL) &&
							(lpCamDLL->lpResetFrameComplete != NULL) &&
							(lpCamDLL->lpGetFrameCount != NULL);// &&
	if (!fRunTimeLinkSuccess) return (-1);

	return(0);
}


int CSI800Camera::GetPepperCount(void)
{
	return 0;
}

void CSI800Camera::SetPepper(int PepperLevel)
{
}

int CSI800Camera::GetPepper(void)
{
	return 0;
}

float CSI800Camera::GetTemperature(void)
{
	GetStatus();
	return (float)(lpCamStatus->CCDTemperature*0.1-273.15);
}


int CSI800Camera::GetNumActiveColumns(void)
{
	return 2040;
}

int CSI800Camera::TDIReadout(C843 *pSlide, unsigned long ** image, int XSize, int YSize, int Bin, double FirstStop, long FinalPosition, double StepSize, bool IsDark, bool ShutterOpen, int FrameNum, int NumFrames, unsigned int TDIDelay)
{
	BOOL test,*PepperFlag;
	int Error = 0;
	unsigned short *pPercentDone;
	unsigned long *pPointerPos;
	INT32 a,b,c,x,y,xstart,xend,ystart,yend,Status,BytesRead,temp, NumRows, y0, y1, y2;
	int CCDXSize, CCDYSize;
	int Bin2;
	float yf,frac;
	unsigned short *TDIBuffer, **TDIArray, *CCDLine, *TDILine;

	NumRows = XSize * Bin + 4;
	//GetCCDSize(&CCDYSize, &CCDXSize);
	Bin2 = Bin*Bin;
	TDIBuffer = new unsigned short[NumRows * YSize * Bin];
	TDIArray  = new unsigned short*[NumRows];
	for (a=0; a<NumRows; ++a)
		TDIArray[a] = &TDIBuffer[a*YSize*Bin];

	Error = Camera.LoadReadoutParameters();
	Error = Camera.LoadConfigurationParameters();

	Camera.lpParameter->SerialOrigin = 2050 - m_NumColumns;
	Camera.lpParameter->SerialReadLength = m_NumColumns/2;
	Camera.lpParameter->SerialBinningFactor = 2;
	Camera.lpParameter->SerialPostscan = 2046 - m_NumColumns;
	Camera.lpParameter->ParallelOrigin = m_NumRows + 9;
	Camera.lpParameter->ParallelReadLength = NumRows;
	Camera.lpParameter->ParallelBinningFactor = 2;
	Camera.lpParameter->ParallelPostscan = 0;
	Camera.lpParameter->DSISampleTime = 14;  //$$$ Should not be less than 14
	Camera.lpParameter->TDIDelayTime = (TDIDelay);
	Camera.lpParameter->Port1Offset = PORT1OFFSET;
	Camera.lpParameter->Port2Offset = PORT2OFFSET;

	if (IsDark)
		Camera.lpParameter->TDIShutter = 1;
	else
		Camera.lpParameter->TDIShutter = 0;
	if (ShutterOpen)
		Camera.lpParameter->TDIShutter = 2;
	Camera.lpParameter->TDICommand = 26;
	if(Camera.SendReadoutParameters())
		Texit("cannot send readout parameters to camera");

 
	//C843::TriggerCamera();// $$$test
	
	if (Camera.PrepareAcquisition(m_NumColumns, Camera.lpParameter->ParallelReadLength, TDIBuffer, NULL, 2, 0, NULL))
		Texit("Error preparing camera acquisition");
	
	if (Camera.ImageInternalTDI())
		Texit("Error sending camera read command");
	//theApp.SetThreadPriority(THREAD_PRIORITY_TIME_CRITICAL);

	pSlide->SetTriggerEvent(2,0);
	pSlide->SetTriggerPoint(2,FirstStop);

	pSlide->Move(FinalPosition);
//C843::TriggerCamera(); //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

	/*for (a=0; a<Camera.lpParameter->ParallelOrigin; ++a) 
	{
		pSlide->WaitForPositionPositive((long)Position);
		C843::TriggerCamera();
		Position += StepSize;
	}

	for (a=0; a<Camera.lpParameter->ParallelReadLength; ++a) 
	{
		pSlide->WaitForPositionPositive((long)Position);
		C843::TriggerCamera();
		Position += StepSize;
	}*/

	//theApp.SetThreadPriority(THREAD_PRIORITY_NORMAL);
	int t;
	while(!(t=Camera.DmaStatus()))
		Sleep(50);
	if (t == 2)
	{
		Error = 1;
		for (int j=0; j<50; ++j)
		{
            C843::TriggerCamera();
			C843::Pause(100);
		}
		Restart();
	}
	if (Camera.EndAcquisition())
		Texit("Camera data acquisition error");

	//theApp.SetThreadPriority(THREAD_PRIORITY_NORMAL);

	
/*	if (m_Pepper)
	{
		int nX = m_XSize * Bin;
		int nY = m_YSize * Bin
		CCDLine = new unsigned short[nX];
		TDILine = new unsigned short[nX+2];
		PepperFlag = new BOOL[NumRows];
		m_PepperCount = 0;
		for (a=0; a<YSize; ++a)
		{
			unsigned short p1;
			unsigned short p2 = TDIArray[0][a];
			unsigned short p3 = TDIArray[1][a];
			x = 2;
			for (b=0; b<nX+2; ++b)
			{
				p1 = p2;
				TDILine[b] = p2 = p3;
				p3 = TDIArray[b+2][a];
				if ((p2-(p1>>1)-(p3>>1)) > m_Pepper)
				{
					++m_PepperCount;
					PepperFlag[b] = TRUE;
				}
				else
					PepperFlag[b] = FALSE;
			}
			for (b=1; b<=nX; ++b)
			{
				if (PepperFlag[b])
				{
					c = b-1;
					while ((PepperFlag[c] || PepperFlag[c-1]) && (c>0))
						--c;
					temp = TDILine[c];
					c = b+1;
					while ((PepperFlag[c] || PepperFlag[c+1]) && (c<=nX))
						++c;
					temp += TDILine[c];
					CCDLine[b-1] = (unsigned int)(temp/2);
				}
				else
					CCDLine[b-1] = TDILine[b];
			}
			unsigned short *p = CCDLine;
			unsigned short *pI = image[a];
			for (b=0; b<XSize; ++b)
			{
				temp = *p++;
				for (c=1; c<Bin; ++c)
					temp += *p++;
				temp /= Bin;
				pI[XSize-1-b] = (unsigned short)temp;
			}
		}
	}
	else*/
	if (!Error)
	{
		if (Bin == 2)
		{
			for (a=0; a<XSize; ++a)
			{
				xstart = (XSize-1-a)*2+2;
				xend = xstart + 2;
				yf = YSize*(1-VERTICAL_MAGNIFICATION)+1;
				for (b=0; b<YSize; ++b)
				{
					if (FrameNum == 0)
						image[b][a] = 0;
					temp = 0;
					y1 = int(yf);
					y0 = y1 - 1;
					y2 = y1 + 1;
					frac = yf - y1;

					for (x=xstart; x<xend; ++x)
						temp += (TDIArray[x][y1] + (1-frac)*TDIArray[x][y0] + frac*TDIArray[x][y2]);
					image[b][a] += (unsigned short)(temp/4);
					if (FrameNum == (NumFrames-1))
						image[b][a] /= NumFrames;
					yf += 2*VERTICAL_MAGNIFICATION;
				}
			}
		}
		else
		{
			for (a=0; a<XSize; ++a)
			{
				xstart = (XSize-1-a)*Bin+2;
				xend = xstart + Bin;
				for (b=0; b<YSize; ++b)
				{
					if (FrameNum == 0)
						image[b][a] = 0;
					temp = 0;
					ystart = b*Bin;
					yend = ystart + Bin;
					for (x=xstart; x<xend; ++x)
					{
						for (y = ystart; y < yend; ++y)
							temp += TDIArray[x][y];
					}
					image[b][a] += (unsigned short)(temp/Bin2);
					if (FrameNum == (NumFrames-1))
						image[b][a] /= NumFrames;
				}
			}
		}
	}
	delete TDIBuffer;
	delete TDIArray;
	return Error;
}


void CSI800Camera::SetGain(int Gain, int Speed)
{
	Camera.lpParameter->AnalogAttenuation = Gain;
	if(Camera.SendReadoutParameters())
		Texit("cannot send readout parameters to camera");
}

float CSI800Camera::GetGain(int Gain, int Speed)
{
	return (float)Camera.lpParameter->AnalogAttenuation;
}

void CSI800Camera::ExposeandReadoutRegion(float exposure, unsigned long ** image, int X, int Y, int XSize, int YSize, int Bin)
{
	int SerialReadLength = YSize/2*Bin;
	INT32 a,b,c,x,y,xstart,xend,ystart,yend,Status,BytesRead,temp, NumRows;
	int ParallelReadLength = NumRows = XSize*Bin;
	int Bin2;
	unsigned short *TDIBuffer, **TDIArray, *CCDLine, *TDILine;
	double Position;

	Bin2 = Bin*Bin;
	TDIBuffer = new unsigned short[NumRows * YSize * Bin];
	TDIArray  = new unsigned short*[NumRows];
	for (a=0; a<NumRows; ++a)
		TDIArray[a] = &TDIBuffer[a*YSize*Bin];
	Camera.lpParameter->ExposureTime = (DWORD)exposure;
	Camera.lpParameter->SerialOrigin = 8 + Y*2;
	Camera.lpParameter->SerialReadLength = SerialReadLength;
	Camera.lpParameter->SerialBinningFactor = 2;
	Camera.lpParameter->SerialPostscan = 2048 - SerialReadLength*2 - Camera.lpParameter->SerialOrigin;
	Camera.lpParameter->ParallelOrigin = 8 + X*2;
	Camera.lpParameter->ParallelReadLength = ParallelReadLength;
	Camera.lpParameter->ParallelBinningFactor = 2;
	Camera.lpParameter->ParallelPostscan = 4097 - ParallelReadLength*2 - Camera.lpParameter->ParallelOrigin;
	if(Camera.SendReadoutParameters())
		Texit("cannot send readout parameters to camera");

	if (Camera.PrepareAcquisition(SerialReadLength*2, ParallelReadLength, TDIBuffer, NULL, 2, 0, NULL))
		Texit("Error preparing camera acquisition");
	if (Camera.ImageExposeandRead())
		Texit("Error sending camera read command");
	while(!Camera.DmaStatus())
		;
	if (Camera.EndAcquisition())
		Texit("Camera data acquisition error");

	for (a=0; a<XSize; ++a)
	{
		xstart = (XSize-1-a)*Bin;
		xend = xstart + Bin;
		for (b=0; b<YSize; ++b)
		{
			temp = 0;
			ystart = b*Bin;
			yend = ystart + Bin;
			for (x=xstart; x<xend; ++x)
			{
				for (y = ystart; y < yend; ++y)
					temp += TDIArray[x][y];
			}
			image[b][a] = (unsigned short)(temp/Bin2);
		}
	}
	delete TDIBuffer;
	delete TDIArray;
}

void CSI800Camera::StillImage(float exposure, unsigned long ** image, int XSize, int YSize, int Bin)
{
	int SerialReadLength = 1000; // Change back to 1000
	int ParallelReadLength = 2000;
	INT32 a,b,c,x,y,xstart,xend,ystart,yend,Status,BytesRead,temp, NumRows,Error;
	int Bin2;
	unsigned short *TDIBuffer, **TDIArray, *CCDLine, *TDILine;
	double Position;

	NumRows = XSize * Bin;
	Bin2 = Bin*Bin;
	TDIBuffer = new unsigned short[NumRows * YSize * Bin];
	TDIArray  = new unsigned short*[NumRows];
	for (a=0; a<NumRows; ++a)
		TDIArray[a] = &TDIBuffer[a*YSize*Bin];
	Error = Camera.LoadReadoutParameters();
	Error = Camera.LoadConfigurationParameters();
	Camera.lpParameter->ExposureTime = (DWORD)exposure;
	Camera.lpParameter->SerialOrigin = 2050 - SerialReadLength*2;  //Change this back --I have
	Camera.lpParameter->SerialReadLength = SerialReadLength;
	Camera.lpParameter->SerialBinningFactor = 2;
	Camera.lpConfiguration->NumberOfPorts = 1; // Change this back -- I have
	Camera.lpConfiguration->SerialRegisterPhasing = 0;
	Camera.lpConfiguration->SerialRegisterSplit = 1;  //Change back to 1
	Camera.lpConfiguration->ParallelRegisterPhasing = 0;
	Camera.lpParameter->SerialPostscan = 0;//2046 - SerialReadLength*2;
	Camera.lpParameter->ParallelOrigin = 9;
	Camera.lpParameter->ParallelReadLength = NumRows;
	Camera.lpParameter->ParallelBinningFactor = 2;
	Camera.lpParameter->ParallelPostscan = 4089 - NumRows*2-9;
	Camera.lpParameter->Port1Offset = PORT1OFFSET;
	Camera.lpParameter->Port2Offset = PORT2OFFSET;
	if(Camera.SendReadoutParameters())
		Texit("cannot send readout parameters to camera");
	if(Camera.SendConfigurationParameters())
		Texit("cannot send Configuration parameters to camera");
//
//	if (Camera.PrepareAcquisition(SerialReadLength*2, NumRows, TDIBuffer, NULL, 2, 0, NULL))
////	if (Camera.PrepareAcquisition(SerialReadLength, NumRows, TDIBuffer, NULL, 2, 0, NULL))
//		Texit("Error preparing camera acquisition");

//	LPWORD lpImage = new WORD[2048*2040];
	//Error = Camera.LoadReadoutParameters();
	//Camera.lpParameter->SerialOrigin = 2050 - SerialReadLength*2;
	//Camera.lpParameter->SerialReadLength = SerialReadLength;
	//Camera.lpParameter->SerialBinningFactor = 2;
	//Camera.lpConfiguration->SerialRegisterPhasing = 0;
	//Camera.lpConfiguration->NumberOfPorts = 1;
	//Camera.lpConfiguration->SerialRegisterSplit = 1;  //Change back to 1
	//Camera.lpParameter->SerialPostscan = 0;
	//Camera.lpParameter->ParallelOrigin = 9;
	//Camera.lpParameter->ParallelReadLength = NumRows;
	//Camera.lpParameter->ParallelBinningFactor = 2;
	//Camera.lpParameter->ParallelPostscan = 9;
	//Camera.lpParameter->ExposureTime = 1000;
	//Camera.lpParameter->TDIDelayTime = 2000;
	printf("\nAcquiring\n");
	if (Camera.PrepareAcquisition(SerialReadLength*2, NumRows, TDIBuffer, NULL, 2, 0, NULL))
		Texit("Error preparing camera acquisition");


	if (Camera.ImageExposeandRead())
		Texit("Error sending camera read command");
	while(!Camera.DmaStatus())
		;
	if (Camera.EndAcquisition())
		Texit("Camera data acquisition error");
	for (a=0; a<XSize; ++a)
	{
		xstart = (XSize-1-a)*Bin;
		xend = xstart + Bin;
		for (b=0; b<YSize; ++b)
		{
			temp = 0;
			ystart = b*Bin;
			yend = ystart + Bin;
			for (x=xstart; x<xend; ++x)
			{
				for (y = ystart; y < yend; ++y)
					temp += TDIArray[x][y];
			}
			image[b][a] = (unsigned short)(temp/Bin2);
		}
	}
	delete TDIBuffer;
	delete TDIArray;

}

void CSI800Camera::GetCCDSize(int * NumCols, int * NumRows)
{
	if (Camera.LoadReadoutParameters())
		Texit("Cannot get readout parameters from camera");
	
	Camera.lpParameter->SerialOrigin = 28;//8;
	Camera.lpParameter->SerialReadLength = 1000;//1020;
	Camera.lpParameter->SerialBinningFactor = 2;
	Camera.lpParameter->SerialPostscan = 8;
	Camera.lpParameter->ParallelOrigin = 8;
	Camera.lpParameter->ParallelReadLength = 2040;
	Camera.lpParameter->ParallelBinningFactor = 2;
	Camera.lpParameter->ParallelPostscan = 9;
	//Camera.lpParameter->ExposureTime = 0;
	//Camera.lpParameter->TDIDelayTime = 2000;
	
	if(Camera.SendReadoutParameters())
		Texit("cannot send readout parameters to camera");
	*NumCols = m_NumColumns = 2000;
	*NumRows = m_NumRows = 2040;
}

void CSI800Camera::CExit(char * Message)
{
	CoolerOff();
	if (m_DmaActive) (lpCamDLL->lpEndDma)();			// end DMA if it is still active
	if (m_IsrActive) (lpCamDLL->lpRemoveIsr)();			// remove interrupt service routine if still present
	delete lpParameter;
	delete lpConfiguration;
	delete lpCamStatus;
	delete lpCamDLL;
	::MessageBox(NULL,Message,"Error",MB_OK|MB_ICONHAND);
	exit(1);
}

void CSI800Camera::GetTempPressure(float *Temperature, float *Pressure)
{
	int a, Value;
	float LowMargin, HighMargin;
	struct
	{
		int Reading;
		float Pressure;
	} Lookup[22] = {
		{169, 0.0001},
		{180, 0.001},
		{197, 0.003},
		{223, 0.005},
		{241, 0.007},
		{266, 0.010},
		{396, 0.030},
		{481, 0.050},
		{560, 0.070},
		{654, 0.100},
		{1048, 0.300},
		{1281, 0.500},
		{1446, 0.700},
		{1621, 1.000},
		{2126, 3.000},
		{2304, 5.00},
		{2395, 7.00},
		{2457, 10.0},
		{2573, 30.00},
		{2597, 50},
		{2608, 70},
		{2615, 100}
	};
	GetStatus();
	Value = lpCamStatus->HeadPressure;
	a=-1;
	while (Lookup[++a].Reading < Value)
		;
	LowMargin = (Value - Lookup[a-1].Reading)/((float)(Lookup[a].Reading - Lookup[a-1].Reading));
	HighMargin = (Lookup[a].Reading - Value)/((float)(Lookup[a].Reading - Lookup[a-1].Reading));
	*Pressure = LowMargin*Lookup[a].Pressure + HighMargin*Lookup[a-1].Pressure;
	*Temperature = (float)(lpCamStatus->CCDTemperature*0.1-273.15);

	return;
}

void CSI800Camera::Restart(void)
{
	C843::Pause(5000);
	if (!SendCommand('_'))
		return;
	(lpCamDLL->lpSendfile)(250, CAMERABINFILE);

}

int CSI800Camera::ImageInternalTDI(void)
{
	if (!m_DmaActive)									// error if no DMA active
		return E_DMA_NOT_ACTIVE;
	return SendCommand('U');
}
