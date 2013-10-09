//-----------------------------------------------------------------------------
//	Copyright (c) 2001 @TOLL, Bruchsal
//		ALL RIGHTS RESERVED
//
//	VERSION	   	   : 1.007
//
//	DESCRIPTION	   : define low lewel commands for C843 and 
//                   qfl statements
//  HISTORY        : 20/01/02 added REC command
//-----------------------------------------------------------------------------

#ifndef _C843CMD_H_
#define _C843CMD_H_

// low level C843CMD commands
#define	ADJUST_ACTUAL_POSITION		0xf5
#define	CLEAR_INTERRUPT				0xac
#define	CLEAR_POSITION_ERROR		0x47
#define	GET_ACTIVITY_STATUS			0xa6
#define	GET_ACTUAL_VELOCITY			0xad
#define	GET_CAPTURE_VALUE			0x36
#define	GET_CHECKSUM				0xf8
#define	GET_COMMANDED_ACCELERATION	0xa7
#define	GET_COMMANDED_POSITION		0x1d
#define	GET_COMMANDED_VELOCITY		0x1e
#define	GET_CURRENT_MOTOR_COMMAND	0x3a
#define	GET_DERIVATIVE				0x9b
#define	GET_EVENT_STATUS			0x31
#define	GET_HOST_IO_ERROR			0xa5
#define	GET_INTEGRAL				0x9a
#define	GET_INTERRUPT_AXIS			0xe1
#define	GET_INTERRUPT_AXIS			0xe1
#define	GET_PHASE_COMMAND			0xea
#define	GET_POSITION_ERROR			0x99
#define	GET_SIGNAL_STATUS			0xa4
#define	GET_TIME					0x3e
#define	GET_TRACE_COUNT				0xbb
#define	GET_TRACE_STATUS			0xba
#define	GET_VERSION					0x8f
#define	INITIALIZE_PHASE			0x7a
#define	MULTI_UPDATE				0x5b
#define	NO_OPERATION				0x00
#define	READ_ANALOG					0xef
#define	READ_BUFFER					0xc9
#define	READ_IO						0x83
#define	RESET						0x39
#define	RESET_EVENT_STATUS			0x34
#define	SET_ACCELERATION			0x90
#define	GET_ACCELERATION			0x4c
#define	SET_ACTUAL_POSITION			0x4d
#define	GET_ACTUAL_POSITION			0x37
#define	SET_ACTUAL_POSITION_UNITS	0xbe
#define	GET_ACTUAL_POSITION_UNITS	0xbf
#define	SET_AUTO_STOP_MODE			0xd2
#define	GET_AUTO_STOP_MODE			0xd3
#define	SET_AXIS_MODE				0x87
#define	GET_AXIS_MODE				0x88
#define	SET_AXIS_OUT_SOURCE			0xed
#define	GET_AXIS_OUT_SOURCE			0xee
#define	SET_BREAKPOINT				0xd4
#define	GET_BREAKPOINT				0xd5
#define	SET_BREAKPOINT_VALUE		0xd6
#define	GET_BREAKPOINT_VALUE		0xd7
#define	SET_BUFFER_FUNCTION			0xca
#define	GET_BUFFER_FUNCTION			0xcb
#define	SET_BUFFER_LENGTH			0xc2
#define	GET_BUFFER_LENGTH			0xc3
#define	SET_BUFFER_READ_INDEX		0xc6
#define	GET_BUFFER_READ_INDEX		0xc7
#define	SET_BUFFER_START			0xc0
#define	GET_BUFFER_START			0xc1
#define	SET_BUFFER_WRITE_INDEX		0xc4
#define	GET_BUFFER_WRITE_INDEX		0xc5
#define	SET_CAPTURE_SOURCE			0xd8
#define	GET_CAPTURE_SOURCE			0xd9
#define	SET_COMMUTATION_MODE		0xe2
#define	GET_COMMUTATION_MODE		0xe3
#define	SET_DECELERATION			0x91
#define	GET_DECELERATION			0x92
#define	SET_DERIVATIVE_TIME			0x9c
#define	GET_DERIVATIVE_TIME			0x9d
#define	SET_DIAGNOSTIC_PORT_MODE	0x89
#define	GET_DIAGNOSTIC_PORT_MODE	0x8a
#define	SET_ENCODER_MODULUS			0x8e
#define	GET_ENCODER_MODULUS			0x8d
#define	SET_ENCODER_SOURCE			0xda
#define	GET_ENCODER_SOURCE			0xdb
#define	SET_ENCODER_TO_STEP_RATIO	0xde
#define	GET_ENCODER_TO_STEP_RATIO	0xdf
#define	SET_GEAR_MASTER				0xae
#define	GET_GEAR_MASTER				0xaf
#define	SET_GEAR_RATIO				0x14
#define	GET_GEAR_RATIO				0x59
#define	SET_INTEGRATION_LIMIT		0x95
#define	GET_INTEGRATION_LIMIT		0x96
#define	SET_INTERRUPT_MASK			0x2f
#define	GET_INTERRUPT_MASK			0x56
#define	SET_JERK					0x13
#define	GET_JERK					0x58
#define	SET_KAFF					0x93
#define	GET_KAFF					0x94
#define	SET_KD						0x27
#define	GET_KD						0x52
#define	SET_KI						0x26
#define	GET_KI						0x51
#define	SET_KOUT					0x9e
#define	GET_KOUT					0x9f
#define	SET_KP						0x25
#define	GET_KP						0x50
#define	SET_KVFF					0x2b
#define	GET_KVFF					0x54
#define	SET_LIMIT_SWITCH_MODE		0x80
#define GET_LIMIT_SWITCH_MODE		0x81
#define	SET_MOTION_COMPLETE_MODE	0xeb
#define	GET_MOTION_COMPLETE_MODE	0xec
#define	SET_MOTOR_BIAS				0x0f
#define	GET_MOTOR_BIAS				0x2d
#define	SET_MOTOR_COMMAND			0x77
#define	GET_MOTOR_COMMAND			0x69
#define	SET_MOTOR_LIMIT				0x06
#define	GET_MOTOR_LIMIT				0x07
#define	SET_MOTOR_MODE				0xdc
#define	GET_MOTOR_MODE				0xdd
#define	SET_NUMBER_PHASES			0x85
#define	GET_NUMBER_PHASES			0x86
#define	SET_OUTPUT_MODE				0xe0
#define	GET_OUTPUT_MODE				0x6e
#define	SET_PHASE_ANGLE				0x84
#define	GET_PHASE_ANGLE				0x2c
#define	SET_PHASE_CORRECTION_MODE	0xe8
#define	GET_PHASE_CORRECTION_MODE	0xe9
#define	SET_PHASE_COUNTS			0x75
#define	GET_PHASE_COUNTS			0x7d
#define	SET_PHASE_INITIALIZE_MODE	0xe4
#define	GET_PHASE_INITIALIZE_MODE	0xe5
#define	SET_PHASE_INITIALIZE_TIME	0x72
#define	GET_PHASE_INITIALIZE_TIME	0x7c
#define	SET_PHASE_OFFSET			0x76
#define	GET_PHASE_OFFSET			0x7b
#define	SET_PHASE_PRESCALE			0xe6
#define	GET_PHASE_PRESCALE			0xe7
#define	SET_POSITION				0x10
#define	GET_POSITION				0x4a
#define	SET_POSITION_ERROR_LIMIT	0x97
#define	GET_POSITION_ERROR_LIMIT	0x98
#define	SET_PROFILE_MODE			0xa0
#define	GET_PROFILE_MODE			0xa1
#define	SET_SAMPLE_TIME				0x38
#define	GET_SAMPLE_TIME				0x61
#define	SET_SERIAL_PORT_MODE		0x8b
#define	GET_SERIAL_PORT_MODE		0x8c
#define	SET_SETTLE_TIME				0xaa
#define	GET_SETTLE_TIME				0xab
#define	SET_SETTLE_WINDOW			0xbc
#define	GET_SETTLE_WINDOW			0xbd
#define	SET_SIGNAL_SENSE			0xa2
#define	GET_SIGNAL_SENSE			0xa3
#define	SET_START_VELOCITY			0x6a
#define	GET_START_VELOCITY			0x6b
#define	SET_STEP_RANGE				0xcf
#define	GET_STEP_RANGE				0xce
#define	SET_STOP_MODE				0xd0
#define	GET_STOP_MODE				0xd1
#define	SET_TRACE_MODE				0xb0
#define	GET_TRACE_MODE				0xb1
#define	SET_TRACE_PERIOD			0xb8
#define	GET_TRACE_PERIOD			0xb9
#define	SET_TRACE_START				0xb2
#define	GET_TRACE_START				0xb3
#define	SET_TRACE_STOP				0xb4
#define	GET_TRACE_STOP				0xb5
#define	SET_TRACE_VARIABLE			0xb6
#define	GET_TRACE_VARIABLE			0xb7
#define	SET_TRACKING_WINDOW			0xa8
#define	GET_TRACKING_WINDOW			0xa9
#define	SET_VELOCITY				0x11
#define	GET_VELOCITY				0x4b
#define	UPDATE						0x1a
#define	WRITE_BUFFER				0xc8
#define	WRITE_IO					0x82

// QMC commands for execute and translate function
typedef enum
{
	AB = 0xef,	// abort motion
	BN = 0xfa,	// motor brake on
	BF = 0xfb,	// motor brake off
	CF = 0xed,	// channel off
	CN = 0xec,	// channel on
	DD = 0x27,	// define derivative gain
	DF = 0x2b,	// define feedforward gain
	DH = 0x4d,	// define home
	DI = 0x26,	// define integral gain
	DL = 0x95,  // define integration limit
	DP = 0x25,	// define proportional gain
	FEN = 0xf3,	// find edge in negative direction
	FEP = 0xf2,	// find edge in positive direction
	GA = 0x4c,	// get acceleration
	GAM = 0x88,	// get axis mode
	GAS = 0xa6,	// get activity status
	GES = 0x31,	// get event status
	GB = 0xd4,	// get breakpoint
	GBV = 0xd7,	// get breakpoint value
	GD = 0x52,	// get derivative gain
	GF = 0x54,	// get feedforward gain
	GGM = 0xaf,	// get gear master
	GGR = 0x59,	// get gear ratio
	GH = 0xe2,	// go home
	GI = 0x51,	// get integral gain
	GIP = 0x36,	// get index position
	GJ = 0x58,	// get jerk
	GL = 0x96,	// get integration limit
	GLM = 0x81,	// get limit switch mode
	GMM = 0xdd,	// get motor mode
	GOM = 0x6e,	// get output mode
	GP = 0x50,	// get proportional gain
	GPE = 0x99,	// get position error
	GPM = 0xa1,	// get profile mode
	GPP = 0x1d,	// get commanded position
	GSM = 0xd3,	// get auto stop mode
	GPV = 0x1e,	// get commanded velocity
	GSI = 0x9a,	// get integrated position error value
	GSS = 0xa3,	// get signal sense
	GT = 0x61,	// get sample time
	GTI = 0x3e,	// get time
	MA = 0x10,	// move absolute
	MR = 0xe1,	// move relative
	MUP = 0x5b,	// multi axis update
	RES = 0x34,	// reset event status register
	RT = 0x39,	// reset c-843
	SA = 0x90,	// set acceleration
	SAM = 0x87,	// set axis mode
	SB = 0xd4,	// set breakpoint
	SBV = 0xd6,	// set breakpoint value
	SCS = 0xd8,	// set capture source
	SEM = 0x8e,	// set encoder modulus
	SD = 0x91,	// set deceleration
	SGM = 0xae,	// set gear master
	SGR = 0x18,	// set gear ratio
	SJ = 0x13,	// set jerk
	SLM = 0x80,	// set limit switch mode
	SMO = 0x90,	// set motor output
	SMM = 0xdc,	// set motor mode
	SOM = 0xe0,	// set output mode
	SPE = 0x97,	// set maximum position error limit
	SPM = 0xa0,	// set profile mode
	SSM = 0xd2,	// set auto stop mode
	SSS = 0xa2,	// set signal sense
	SST = 0x38,	// set servo loop sample time
	ST = 0xe5,	// stop with programmed acceleration
	SV = 0x11,	// set velocity
	TC = 0xeb,	// tell channel in hex notation
	TD = 0x92,	// tell deceleration
	TE = 0xe6,	// tell position error
	TF = 0x99,	// tell error
	TA = 0x4c,	// synonym ot the GIP command
	TP = 0x37,	// tell position
	TT = 0x4a,	// tell target
	TV = 0xad,	// get velocity
	TX = 0x36,	// synonym ot the GIP command
	TY = 0x4b,	// tell velocity
	UP = 0x1a,	// update
	VE = 0x8f,	// get version
	WA = 0xe8,	// wait absolute
	WS = 0xe3,	// wait for motor stop
	WC = 0xf0,	// wait for channel
	WT = 0xf1,	// wait and trigger
	REC = 0x01,	// recover
	DLL = 0x02,	// DLL version
	SP = 0x03,	// set position
	RET = 0x04,	// return to working conditions
// NEW DS
	GIA = 0xfe,	// get interrupt axis
	GIM = 0x56,	// get interrupt mask
	SIM = 0x2f,	// set interrupt mask
	CI = 0xac,	// clear interrupt
	NO = 0x0	// no operation
// END DS

}  TCMD;


#endif // _C843CMD_H_