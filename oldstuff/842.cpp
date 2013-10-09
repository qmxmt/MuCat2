// 842.cpp: implementation of the C842 class.
//
//////////////////////////////////////////////////////////////////////
#include <Afx.h>
#include "842.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C842::C842(int Axis, int Stage)
{
	if (!m_ChipReset)
	{
		Command(PI_RESET);
		m_ChipReset = 1;
	}
	m_Axis = Axis;
	_outp(MOTOR_BASE+2, 0x0f); // Set board function register
	Command(PI_SET_OUTPUT_DAC16);
	Command(m_Axis);
	Command(PI_CLR_STATUS);
	Command(PI_AXIS_ON);
	Command(PI_MTR_ON);
//	Command(PI_SET_POS_ERR);
//	WriteWord(1000);
	Command(PI_SET_AUTO_STOP_ON);
	Command(PI_SET_PRFL_TRAP);
	Command(PI_SET_AUTO_UPDATE_ON);
	m_StageType = Stage;
	switch(Stage)
	{
	case LINEAR_DIRECT:
		SetPID(200,50,400,500000);
		m_TopSpeed = 100000;
		break;
	case LINEAR_GEARED:
		SetPID(250,50,800,2000000);
		m_TopSpeed = 180000;
		break;
	case ROTATIONAL_DIRECT:
		SetPID(200,50,400,750000);
		m_TopSpeed = 160000;
		break;
	}
	Command(PI_SET_I_LM);
	WriteWord(2000);
	SetVelocityFraction(1.0);
}

C842::~C842()
{

}

int C842::m_ChipReset = 0;
int C842::m_EndStopPosition;

void C842::WriteByte(unsigned char x)
{
	while((_inp(MOTOR_BASE+1)&128) == 0)
		;
	_outp(MOTOR_BASE, x);
}

void C842::WriteWord(short x)
{
	unsigned char *pByte;
	pByte = (unsigned char *)&x;
	WriteByte(pByte[1]);
	WriteByte(pByte[0]);
}

void C842::WriteDWord(long x)
{
	unsigned char *pByte;
	pByte = (unsigned char *)&x;
	WriteByte(pByte[3]);
	WriteByte(pByte[2]);
	WriteByte(pByte[1]);
	WriteByte(pByte[0]);
}

void C842::Move(long Position)
{
	Command(m_Axis);
	Command(PI_SET_POS);
	WriteDWord(Position);
	Command(PI_UPDATE);
}

void C842::SetPID( int integral, int proportional,int derivative, long acceleration)
{
	Command(m_Axis);
	Command(PI_SET_KP);
	WriteWord(integral);
	Command(PI_SET_KI);
	WriteWord(proportional);
	Command(PI_SET_KD);
	WriteWord(derivative);
	Command(PI_SET_ACC);
	WriteDWord(acceleration*819/78125);
}

void C842::SetVelocity(long velocity)
{
	Command(m_Axis);
	Command(PI_SET_VEL);
	WriteDWord(velocity*16384/625);
}

void C842::SetVelocityFraction(double fraction)
{
	SetVelocity((long)(m_TopSpeed*fraction));
}

unsigned short C842::ReadStatus() 
{
	unsigned short status;
	Command(m_Axis);
	status = ReadWord();
	return status;
}

void C842::WaitForStop()
{
int count = 0;
int result;
	Command(m_Axis);
	Command(PI_CLR_STATUS);
	while(((result=ReadStatus()) &1024))
		++count;
}

void C842::FindHome()
{	
	long Position, Step;
	Command(m_Axis);
	Command(PI_CLR_STATUS);
	Command(PI_SET_ACTL_POS);//		Set position to zero.
	WriteDWord(0);
	if (m_StageType == LINEAR_DIRECT)
		SetVelocityFraction(0.5);
	else
		SetVelocityFraction(1.0);
if (m_StageType == LINEAR_GEARED)
{
Command(PI_SET_ACTL_POS);//		Set position to zero.
WriteDWord(0);
Move(50000);
Move(-500000);
int temp = GetPosition();
Move(-5000000);
Move(50000);
Move(50000);
Move(50000);
Move(50000);
}
	if (m_StageType == LINEAR_DIRECT || m_StageType == LINEAR_GEARED)
	{
		if (GetLimitSwitches() & 0x01)
		{
			Move(-1000000);
			while(GetLimitSwitches() & 0x01)
				;
		}
		Command(PI_SET_ACTL_POS);//		Set position to zero.
		WriteDWord(0);
		Command(PI_CLR_STATUS);
		Move(+10000000);//				Hit +ve end stop.
		WaitForStop();
		Command(PI_SET_ACTL_POS);//		Set actual position to 0 at end stop.
		WriteDWord(0);
		SetVelocityFraction(1.0);
		Command(PI_CLR_STATUS);
	}
	Move(-10000000);//				Move in -ve direction.
	Command(PI_SET_CAPT_HOME);
	Position = GetCapture();//		Wait for index.
	Stop();
	WaitForStop();
	SetVelocityFraction(0.1);
	Move(10000000);//				Reverse at 1/10th speed.
	Position = GetCapture();//		Wait for index and store position.
	Stop();
	WaitForStop();
	SetVelocityFraction(0.01);
	Move(-10000000);//				Reverse back at 1/100th speed.
	Position = GetCapture();//		Wait for index and store position.
	Stop();
	WaitForStop();
	m_EndStopPosition = -Position;
	Step = GetPosition() - Position;
	if (m_StageType == ROTATIONAL_DIRECT)
		Step += 133550;//			Sets the offset for rotational stage
	Command(PI_SET_ACTL_POS);//		Set final position relative to index.
	WriteDWord(Step);
	SetVelocityFraction(1.0);
	Move(0L);
}

void C842::ReadByte(unsigned char *pByte)
{
	while((_inp(MOTOR_BASE+1)&128) == 0)
		;
	*pByte=_inp(MOTOR_BASE);
}

short C842::ReadWord()
{
	short result;
	unsigned char *pByte;
	pByte = (unsigned char*) &result;
	ReadByte(pByte+1);
	ReadByte(pByte);
	return result;
}

void C842::StopAtEnd()
{
	Command(m_Axis);
	while(!(ReadStatus()&0x60))
		;
	Command(PI_SMOOTH_STOP);
	Command(PI_UPDATE);
}

long C842::ReadDWord()
{
	long result;
	unsigned char *pByte;
	pByte = (unsigned char*) &result;
	ReadByte(pByte+3);
	ReadByte(pByte+2);
	ReadByte(pByte+1);
	ReadByte(pByte);
	return result;
}

long C842::GetCapture()
{
	long Position;
	Command(PI_GET_CAPT);
	Position = ReadDWord();
	Command(PI_CLR_STATUS);
	while(!(ReadStatus() & 0x08))
		;
	Command(PI_GET_CAPT);
	Position = ReadDWord();
	return Position;
}

long C842::GetPosition()
{
	long Position;
	Command(m_Axis);
	Command(PI_GET_ACTL_POS);
	Position = ReadDWord();
	return Position;
}

int C842::GetLimitSwitches()
{
	// Bit 0 = +ve switch, bit 1 = -ve switch, 1 = set.
	short temp;
	Command(PI_GET_LMT_SWTCH);
	temp = ReadWord();
	return (temp >> ((m_Axis-1)*2)) &0x03;
}

void C842::Stop()
{
	Command(m_Axis);
	Command(PI_SMOOTH_STOP);
	Command(PI_UPDATE);
}

void C842::WaitForPositionPositive(long Position)
{
	Command(m_Axis);
	/*Command(PI_SET_I);
	Command(PI_SET_INTRPT_MASK);
	WriteWord(0x04);//			Set interrupt for breakpoint
	Command(PI_RST_INTRPT);
	Command(PI_SET_BRK_PNT);
	WriteDWord(Position);
	Command(PI_SET_ACTL_POS_BRK);
	while(_inp(MOTOR_BASE+1)&0x40)// Wait for interrupt line (polling)
		;*/
	while(GetPosition() < Position)
		;
}

void C842::SetAcceleration(long Acc)
{
	Command(m_Axis);
	Command(PI_SET_ACC);
	WriteDWord(Acc*819/78125);
}

int C842::GetEndStopPosition()
{
	return m_EndStopPosition;
}

void C842::MoveToEnd()
{
	Move((m_EndStopPosition*97)/100);
}
