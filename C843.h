//-----------------------------------------------------------------------------
//	Copyright (c) 2001 @TOLL, Bruchsal
//		ALL RIGHTS RESERVED
//
//	VERSION	   	   : 1.007
//
//	DESCRIPTION	   : contains definition of DLL 
//					 exporting function
//
//  HISTORY        : 17/12/01 translate was added
//                   04/01/02 many functions added (see DLLFinal.doc)
//-----------------------------------------------------------------------------
#ifndef _C843_H_
#define _C843_H_


#ifdef __cplusplus
	extern "C" {
#endif

#ifdef C843_DLL
	#define FUNC_DECL __declspec(dllexport) _stdcall
#else
	#define FUNC_DECL __declspec(dllimport) _stdcall
#endif

typedef int H843RESULT;
typedef unsigned char BYTE;
typedef long LONG;
typedef unsigned short int WORD;
typedef int BOOL;
typedef unsigned int UINT;

#include "C843cmd.h"


//
// this is for debug purposes only
//
#ifdef DUMPING
enum tagMCCALLBACKREASON
{
	REASON_COMMAND,
	REASON_SENT,
	REASON_RECEIVED
};


typedef void (WINAPI *IOCallbackProc)(int reason, unsigned long userVal,
		 const unsigned short* pData, unsigned cData);

void FUNC_DECL SetIOCallback(IOCallbackProc pProc, unsigned long userVal);

void IOCallback(int reason, const unsigned short* pData, unsigned cData);

#endif // DUMPING



//************************************************************
// FUNCTION:	Select_Board(BYTE boradnumber)
// PURPOSE:		Selects current PCI board
//
// PARAMETERS:
//		boradnumber - board number   [1...MAX_BOARD]
//
// RETURNS: TRUE if borsd is present
//************************************************************
//BOOL  Select_Board(BYTE boardnumber);
//BOOL FUNC_DECL Select_Board(BYTE boardnumber);


//************************************************************
// FUNCTION:	Axis_Installed(BYTE* pnumber)
//
// PURPOSE:		returns the number of motor axis
//         
//
// PARAMETERS:  pnumber - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL Axis_Installed(BYTE* pnumber);

//IK (3/1/02, 5:30:22 PM): 
//************************************************************
// FUNCTION:	GetNumberOfInstalledBoards(BYTE* pnumber)
//
// PURPOSE:		returns the number of installed and 
//				currently available boards         
//
// PARAMETERS:  pnumber - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL GetNumberOfInstalledBoards(BYTE* pnumber);


//************************************************************
// FUNCTION:	InitBoard(void)
// PURPOSE:		Initializes current PCI board
//
// PARAMETERS:  none
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL InitBoard(void);

//IK (3/1/02, 2:24:58 PM): 
//************************************************************
// FUNCTION:	OpenBoard(void)
// PURPOSE:		Opens current PCI board(without initialization)
//
// PARAMETERS:  none
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL OpenBoard();

//************************************************************
// FUNCTION:	InitAxis(BYTE axis);
// PURPOSE:		Initializes the specified axis and sets 
//              default values
//
// PARAMETERS:	axis - number of axis [0..4]
//
// RETURNS: error code or S_OK
// 
// this function not implemented succesfully
//************************************************************
H843RESULT FUNC_DECL InitAxis(BYTE axis);

//************************************************************
// FUNCTION:	setQMC(BYTE bCmd, BYTE bAxis, long lParam)
// PURPOSE:		Sets parameter of axis and checks arguments
// 
// PARAMETERS:
//		bCmd - command byte
//		bAxis - axis number [0..3]
//		lParam - required parameter
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL setQMC(BYTE bCmd,
						 BYTE bAxis, 
						 LONG Param);

//************************************************************
// FUNCTION:	getQMC(BYTE bCmd, BYTE bAxis, long* plResult)
// PURPOSE:		Gets parameter of axis and checks arguments 
//
// PARAMETERS:
//		bCmd - command byte
//		bAxis - axis number
//		plResult - pointer to returned variable (must be nonzero)
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL getQMC(BYTE bCmd, 
						 BYTE bAxis,
						 LONG* pResult);

//************************************************************
// FUNCTION:	setQMCA(BYTE bCmd, BYTE bAxis, 
//						long lParam1, long lParam2)
// PURPOSE:		Sets parameter of axis and checks arguments
//
// PARAMETERS:
//		bCmd - command byte
//		bAxis - axis number
//		lParam1 - required parameter #1
//		lParam2 - required parameter #2
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL setQMCA(BYTE bCmd,
						  BYTE bAxis,
						  WORD Param1, 
						  LONG lParam2);

//************************************************************
// FUNCTION:	getQMCA(BYTE bCmd, BYTE bAxis,
//						long lParam, long* plResult);
// PURPOSE:		Gets parameter of axis and checks arguments
//
// PARAMETERS:
//		bCmd - command byte
//		bAxis - axis number
//		lParam - required parameter
//		plResult - pointer to returned variable (must be nonzero)
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL getQMCA(BYTE bCmd,
						  BYTE bAxis,
						  WORD lParam,
						  LONG* pResult);

//************************************************************
// FUNCTION:	translate(const char* szQFL, char* szReport);
//
// PURPOSE:		executes qfl statement
//
// PARAMETERS:  szQFL - string with qfl statement, exaple: "1AB"
//				szReport - pointer to 256 bytes buffer allocated
//              by caller, when report string will be replaced;
//              may be 0 if report is not needed
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL translate(const char* szQFL, char* szReport);

//IK (2/21/02, 2:27:27 PM): 
//************************************************************
// FUNCTION:	General_Command_Parser(const char* szQFL, char* szReport)
//
// PURPOSE:		executes general command
//
// PARAMETERS:  Pointer to character array
//				(zero terminated string), holds
//				command string including axis identifier,
//				command and parameter.
//

//				Pointer to character array, 
//				supplied by the calling function.
//				The calling program should define
//				a character array of 256 characters
//				to take the report message. 
//				This string is only filled by commands
//				with a question mark.

// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL General_Command_Parser(const char *command, char *report);

//************************************************************
// FUNCTION:	translate_error(H843RESULT error_code, char* report);
//
// PURPOSE:		translates the error code into a string comprehensible
//              for user
//
// PARAMETERS:  error_code - error code
//              report - caller allocated string buffer, size 256 bytes
//
//************************************************************
void FUNC_DECL translate_error(H843RESULT error_code, char* report);

//************************************************************
// FUNCTION:	execute(BYTE bAxis, TCMD cmd, long arg, char* report);
//
// PURPOSE:		calls one of more than 100 sub-functions of the QFL library
//         
//
// PARAMETERS:  bAxis - number of axis [0...4]
//              cmd - command
//              arg - optional parameter
//              report - caller allocated string buffer, size 256 bytes
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL execute(BYTE bAxis, TCMD cmd, long arg, char* report);

//************************************************************
// FUNCTION:	execute2(BYTE bAxis, TCMD cmd, long arg1, long arg2, char* report);
//
// PURPOSE:		calls several sub-functions of the QFL library
//         
//
// PARAMETERS:  bAxis - number of axis [0...4]
//              cmd - command
//              arg1 - parameter #1
//				arg2 - parameter #2
//              report - caller allocated string buffer, size 256 bytes
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL execute2(BYTE bAxis, TCMD cmd, long arg1, long arg2, char* report);

//************************************************************
// FUNCTION:	Init_LS(BYTE axis1, BYTE axis2, BYTE axis3, BYTE axis4)
//
// PURPOSE:		enables or disables the limit switch sensing for 
//              specified axis
//         
//
// PARAMETERS:  axis1..axis4 - if limit switches are connected
//              to corresponding axis it have to be set to 1,
//              otherwise it have to be set 0
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL Init_LS(BYTE axis1, BYTE axis2, BYTE axis3, BYTE axis4);

//************************************************************
// FUNCTION:	autodetect(BYTE axis);
//
// PURPOSE:		reads the current limit switch lines levels of all
//              axes and defines the reading as normal state.
//
// PARAMETERS:  axis1..axis4
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL autodetect(BYTE axis);

//************************************************************
// FUNCTION:	set_pos(BYTE axis, long position);
//
// PURPOSE:		defines the target position for the next move
//         
//
// PARAMETERS:  axis - axis number [0..4]
//              position - new position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL set_pos(BYTE axis, long position);

//************************************************************
// FUNCTION:	WaitStop(BYTE axis);
//
// PURPOSE:		controls the dynamic position of the specified
//              axis and returns if the motor has reached the target
//              User can break this function pressing CTRL+SHIFT
//
// PARAMETERS:  axis - axis number [0..4]
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL WaitStop(BYTE axis);

//************************************************************
// FUNCTION:	moving(BYTE axis);
//
// PURPOSE:		returns TRUE if trajectory of the specified axis
//              has not yet reached the target position
//
// PARAMETERS:  axis - number of axis [1..4]
//
// RETURNS: FALSE not moving (or error), TRUE moving
//************************************************************
BOOL FUNC_DECL moving(BYTE axis);

//************************************************************
// FUNCTION:	get_pos(BYTE axis, long* ppos);
//
// PURPOSE:		reads the current position of the indicated motor
//
// PARAMETERS:  axis - axis number [1..4]
//              ppos - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_pos(BYTE axis, long* ppos);

//************************************************************
// FUNCTION:	get_PosErr(BYTE axis, long* perror_count);
//
// PURPOSE:		reads the current deviation of the encoder 
//              position from the profile position in encoder counts
//
// PARAMETERS:  axis - number of axis
//              perror_count - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_PosErr(BYTE axis, long* perror_count);

//************************************************************
// FUNCTION:	get_pos4(long Pos[4]);
//
// PURPOSE:		reads the current position of all 4 axes and
//              writes it into an array of 4 long integers
//
// PARAMETERS:  Pos[4] - array of return values
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_pos4(long Pos[4]);

//************************************************************
// FUNCTION:	get_v(BYTE axis, long* pvel);
//
// PURPOSE:		reads the current velocity of the defined axis
//              and returns it in counts/s
//
// PARAMETERS:  axis - number of axis
//              pvel - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_v(BYTE axis, long* pvel);

//************************************************************
// FUNCTION:	get_activity_status(BYTE axis, WORD* preg_val);
//
// PURPOSE:		reads the activity status register of 
//              the specified axis
//
// PARAMETERS:  axis - number of axis
//              preg_val - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_activity_status(BYTE axis, WORD* preg_val);

//************************************************************
// FUNCTION:	get_event_status(BYTE axis, WORD* preg_val);
//
// PURPOSE:		reads the event status register of 
//              the specified axis
//
// PARAMETERS:  axis - number of axis
//              preg_val - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_event_status(BYTE axis, WORD* preg_val);

//************************************************************
// FUNCTION:	get_signal_status(BYTE axis, WORD* preg_val);
//
// PURPOSE:		reads the signal status register of 
//              the specified axis
//
// PARAMETERS:  axis - number of axis
//              preg_val - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_signal_status(BYTE axis, WORD* preg_val);

//************************************************************
// FUNCTION:	get_RefSignal(BYTE axis, BOOL *pref_value);
//
// PURPOSE:		function reads the current reference 
//              signal line level and returns 0 if the
//              line is low or 1 if the line is high
//
// PARAMETERS:  axis - number of axis
//              pref_value - pointer to return value
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL get_RefSignal(BYTE axis, BOOL *pref_value);

//************************************************************
// FUNCTION:	MoveA(BYTE axis, long position);
//
// PURPOSE:		starts one or all motors to move to an absolute 
//              position
//
// PARAMETERS:  axis - number of axis [0..4]
//              position - absolute position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveA(BYTE axis, long position);

//************************************************************
// FUNCTION:	MoveA_12(long position1, long position2);
//
// PURPOSE:	    starts two motors to move to an absolute 
//              position
//
// PARAMETERS:  position1, position2 - absolute position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveA_12(long position1, long position2);

//************************************************************
// FUNCTION:	MoveA_123(long position1, long position2, long position3);
//
// PURPOSE:	    starts three motors to move to an absolute 
//              position
//
// PARAMETERS:  position1, position2, position3 - absolute position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveA_123(long position1, long position2, long position3);

//************************************************************
// FUNCTION:	MoveR(BYTE axis, long position);
//
// PURPOSE:		starts one or all motors to move to a relative 
//              position
//
// PARAMETERS:  axis - number of axis [0..4]
//              position - relative position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveR(BYTE axis, long position);

//************************************************************
// FUNCTION:	MoveR_12(long position1, long position2);
//
// PURPOSE:	    starts two motors to move to an relative 
//              position
//
// PARAMETERS:  position1, position2 - relative position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveR_12(long position1, long position2);

//************************************************************
// FUNCTION:	MoveR_123(long position1, long position2, long position3);
//
// PURPOSE:	    starts three motors to move to an relative 
//              position
//
// PARAMETERS:  position1, position2, position3 - relative position
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL MoveR_123(long position1, long position2, long position3);

//************************************************************
// FUNCTION:    VectorA(BYTE axis1, BYTE axis2, 
//                   long position1, long position2, long vel);
//
// PURPOSE:	    performs a linear interpolation and starts 
//              axis1 and axis2 at the same time towards the 
//              coordinate point with the path velocity.
//
// PARAMETERS:  axis1, axis2 - numbers of axes [1..4]
//              position1, position2 - absolute position of a point
//              vel - path velocity
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL VectorA(BYTE axis1, BYTE axis2, 
                   long position1, long position2, long vel);

//************************************************************
// FUNCTION:    VectorR(BYTE axis1, BYTE axis2, 
//                   long position1, long position2, long vel);
//
// PURPOSE:	    performs a linear interpolation and starts 
//              axis1 and axis2 at the same time towards the 
//              coordinate point with the path velocity.
//
// PARAMETERS:  axis1, axis2 - numbers of axes [1..4]
//              position1, position2 - relative position of a point
//              vel - path velocity
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL VectorR(BYTE axis1, BYTE axis2, 
                   long position1, long position2, long vel);

//************************************************************
// FUNCTION:    AutoFindEdge(BYTE axis, BYTE mode);
//
// PURPOSE:	    function can be used with stages having 
//              automatic reference heading option, 
//              e.g. M-500 or M-400 series. 
//              After this function is called, the stage starts 
//              in the right direction towards the origin point.
//
// PARAMETERS:  axis - numbers of axes [0..4]
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL AutoFindEdge(BYTE axis);

//************************************************************
// FUNCTION:    Recover(BYTE axis, long vel);
//
// PURPOSE:	    recovers axis after limit condition
//
// PARAMETERS:  axis - numbers of axes [1..4]
//              vel - velosity, which will be set
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL Recover(BYTE axis, long vel);


//************************************************************
// FUNCTION:    Get_Version(long* ver);
//
// PURPOSE:	    returns version of DLL
//				Example for version 1.0.0.9 returns 1009
//
// PARAMETERS:  ver [out]
//
// RETURNS: error code or S_OK
//************************************************************
H843RESULT FUNC_DECL Get_Version(long* ver);


//************************************************************
//				NEW Functions
//************************************************************

//$$$ commented out for console
//H843RESULT FUNC_DECL InitMessaging(UINT nAxisNo);
//H843RESULT FUNC_DECL RegisterMessage(HWND hwndWindow, DWORD MessageID, DWORD reason, int AxisNo = 0);
//H843RESULT FUNC_DECL UnRegisterMessage(HWND hwndWindow);
//VOID ProcessMessage(DWORD reasonAndAxis);
//************************************************************

#define MOTION_COMPLETE_MSG		0x0001
#define WRAP_ARROUND_MSG		0x0002
#define BREAKPOINT1_MSG			0x0004
#define CAPTURE_RECEIVED_MSG	0x0008
#define MOTION_ERROR_MSG		0x0010
#define POSITIVE_LIMIT_MSG		0x0020
#define NEGATIVE_LIMIT_MSG		0x0040
#define INSTRUCTION_ERRPR_MSG	0x0080

#ifdef __cplusplus
	};
#endif

#endif //_DLLMAIN_H_