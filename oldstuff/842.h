// 842.h: interface for the C842 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_842_H__CC0D9B83_D449_11D1_A406_0000010049AB__INCLUDED_)
#define AFX_842_H__CC0D9B83_D449_11D1_A406_0000010049AB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#define MOTOR_BASE 0x210

#define LINEAR_DIRECT 1
#define LINEAR_GEARED 2
#define ROTATIONAL_DIRECT 3
#define ROTATIONAL_GEARED 4

#define PI_SET_1                   0X01
#define PI_SET_2                   0X02
#define PI_SET_3                   0X03
#define PI_SET_4                   0X04
#define PI_SET_I                   0X08
#define PI_SET_PRFL_S_CRV          0X0B
#define PI_SET_PRFL_TRAP           0X09
#define PI_SET_PRFL_VEL            0X0A
#define PI_SET_PRFL_GEAR           0X0C
#define PI_SET_POS                 0X10
#define PI_SET_VEL                 0X11
#define PI_SET_ACC                 0X12
#define PI_SET_MAX_ACC             0X15
#define PI_SET_JERK                0X13
#define PI_SET_RATIO               0X14
#define PI_STOP_CLR_PRFL           0X46
#define PI_SMOOTH_STOP             0X4E
#define PI_SYNCH_PRFL              0X47
#define PI_GET_POS                 0X4A
#define PI_GET_VEL                 0X4B
#define PI_GET_ACC                 0X4C
#define PI_GET_MAX_ACC             0X4F
#define PI_GET_JERK                0X58
#define PI_GET_RATIO               0X59
#define PI_GET_TRGT_POS            0X1D
#define PI_GET_TGRT_VEL            0X1E
#define PI_SET_KP                  0X25
#define PI_SET_KD                  0X27
#define PI_SET_KI                  0X26
#define PI_SET_KVFF                0X2B
#define PI_SET_I_LM                0X28
#define PI_SET_MTR_LMT             0X06
#define PI_SET_MTR_BIAS            0X0F
#define PI_SET_POS_ERR             0X29
#define PI_GET_KP                  0X50
#define PI_GET_KD                  0X52
#define PI_GET_KI                  0X51
#define PI_GET_KVFF                0X54
#define PI_GET_I_LM                0X53
#define PI_GET_MTR_LMT             0X07
#define PI_GET_MTR_BIAS            0X2D
#define PI_GET_POS_ERR             0X55
#define PI_GET_INTGR               0X2E
#define PI_GET_ACTL_POS_ERR        0X60
#define PI_SET_AUTO_STOP_ON        0X45
#define PI_SET_AUTO_STOP_OFF       0X44
#define PI_SET_TIME_BRK            0X17
#define PI_SET_POS_BRK             0X18
#define PI_SET_NEG_BRK             0X19
#define PI_SET_ACTL_POS_BRK        0X1B
#define PI_SET_ACTL_NEG_BRK        0X1C
#define PI_SET_MTN_CMPLT_BRK       0X35
#define PI_SET_EXT_BRK             0X5E
#define PI_SET_BRK_OFF             0X6D
#define PI_SET_BRK_PNT             0X16
#define PI_UPDATE                  0X1A
#define PI_MULTI_UPDATE            0X5B
#define PI_SET_AUTO_UPDATE_ON      0X5C
#define PI_SET_AUTO_UPDATE_OFF     0X5D
#define PI_GET_BRK_PNT             0X57
#define PI_SET_INTRPT_MASK         0X2F
#define PI_GET_INTRPT              0X30
#define PI_RST_INTRPT              0X32
#define PI_GET_INTRPT_MASK         0X56
#define PI_CLR_STATUS              0X33
#define PI_RST_STATUS              0X34
#define PI_GET_STATUS              0X31
#define PI_GET_MODE                0X48
#define PI_SET_CNTS                0X68
#define PI_SET_CAPT_INDEX          0X64
#define PI_SET_CAPT_HOME           0X65
#define PI_GET_CAPT                0X36
#define PI_GET_CNTS                0X6F
#define PI_SET_OUTPUT_PWM          0X3C
#define PI_SET_OUTPUT_DAC16        0X3B
#define PI_MTR_ON                  0X43
#define PI_MTR_OFF                 0X42
#define PI_SET_MTR_CMD             0X62
#define PI_GET_MTR_CMD             0X3A
#define PI_GET_OUTPUT_MODE         0X6E
#define PI_AXIS_ON                 0X41
#define PI_AXIS_OFF                0X40
#define PI_SET_ACTL_POS            0X4D
#define PI_GET_ACTL_POS            0X37
#define PI_SET_LMT_SENSE           0X66
#define PI_GET_LMT_SWTCH           0X67
#define PI_LMTS_ON                 0X70
#define PI_LMTS_OFF                0X71
#define PI_GET_HOME                0X05
#define PI_SET_SMPL_TIME           0X38
#define PI_GET_SMPL_TIME           0X61
#define PI_RESET                   0X39
#define PI_GET_VRSN                0X6C
#define PI_GET_TIME                0X3E
#include <conio.h>
class C842  
{
public:
	void SetAcceleration(long);
	void WaitForPositionPositive(long Position);
	void Stop();
	long GetPosition();
	void StopAtEnd();
	void FindHome();
	void WaitForStop();
	void SetVelocityFraction(double fraction);
	void SetVelocity(long velocity);
	void SetPID(int integral, int proportional, int derivative, long acceleration);
	void Move(long Position);
	C842(int Axis, int Stage);
	virtual ~C842();
	unsigned short ReadStatus();
	void MoveToEnd();

protected:
	int GetEndStopPosition();
	static int m_EndStopPosition;
	int m_StageType;
	int GetLimitSwitches();
	long GetCapture();
	long ReadDWord();
	short ReadWord();
	void ReadByte(unsigned char* pByte);
	static int m_ChipReset;
	long m_TopSpeed;
	unsigned char m_Axis;
	void WriteDWord(long x);
	void WriteWord(short x);
	void WriteByte(unsigned char x);
void C842::Command(unsigned char x)
{
	while((_inp(MOTOR_BASE+1)&128) == 0)
		;
	_outp(MOTOR_BASE+1, x);
}

};

#endif // !defined(AFX_842_H__CC0D9B83_D449_11D1_A406_0000010049AB__INCLUDED_)
