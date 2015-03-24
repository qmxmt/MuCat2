#include "StdAfx.h"
#include "C843.h"
#include "843.h"

C843::C843(int Axis, int Stage)
: m_Velocity(0)
{
	if (!m_ChipReset)
	{
		OpenBoard();
		setQMC(RESET,0,0);
		OpenBoard();
		m_ChipReset = 1;
		TDITriggerHigh();
	}
	m_Axis = Axis;
	InitAxis(m_Axis+1);
	setQMC(SET_OUTPUT_MODE,m_Axis,1);
	setQMC(SET_POSITION_ERROR_LIMIT,m_Axis,25000);
	m_StageType = Stage;
	switch(Stage)
	{
	case LINEAR_PD:
		SetPID(200,50,400,400000);
		m_TopSpeed = 250000;
		break;
	case LINEAR_PD1:
		SetPID(55,50,18,400000);
		m_TopSpeed = 250000;
		break;
	case LINEAR_GEARED:
		SetPID(250,50,800,2000000);
		m_TopSpeed = 180000;
		break;
	case ROTATIONAL_DIRECT:
		SetPID(200,50,400,750000);
		m_TopSpeed = 120000;
		setQMC(SET_POSITION_ERROR_LIMIT,m_Axis,50000);
		break;
	case ROTATIONAL_PD:
//		SetPID(510, 500, 400, 1000000);
		SetPID(45, 65, 46, 1000000L);
		m_TopSpeed = 600000;
	}
	setQMC(SET_INTEGRATION_LIMIT,m_Axis,2000);
	SetVelocityFraction(1.0);
}

C843::~C843()
{
}

int C843::m_ChipReset = 0;
char* C843::m_Report = new char[128];
int C843::m_EndStopPosition;

/*void C843::WriteByte(unsigned char x)
{
	while((_inp(MOTOR_BASE+1)&128) == 0)
		;
	_outp(MOTOR_BASE, x);
}

void C843::WriteWord(short x)
{
	unsigned char *pByte;
	pByte = (unsigned char *)&x;
	WriteByte(pByte[1]);
	WriteByte(pByte[0]);
}

void C843::WriteDWord(long x)
{
	unsigned char *pByte;
	pByte = (unsigned char *)&x;
	WriteByte(pByte[3]);
	WriteByte(pByte[2]);
	WriteByte(pByte[1]);
	WriteByte(pByte[0]);
}*/

void C843::Move(long Position)
{
	if (m_StageType == ROTATIONAL_PD)
		Position *= -5;
	if (m_StageType == LINEAR_PD1)
		Position *= 1.024;
	setQMC(RESET_EVENT_STATUS, m_Axis, 0XF6);
	setQMC(UPDATE,m_Axis,0);
	MoveA(m_Axis+1, Position);
//	setQMC(m_Axis);
//	setQMC(PI_SET_POS);
//	WriteDWord(Position);
//	setQMC(PI_SET_POS, m_Axis, Position);
//	setQMC(PI_UPDATE,m_Axis,0);
}

void C843::SetPID( int proportional, int integral, int derivative, long acceleration)
{
//	setQMC(m_Axis);
//	setQMC(PI_SET_KP);
//	WriteWord(integral);
//	setQMC(PI_SET_KI);
//	WriteWord(proportional);
//	setQMC(PI_SET_KD);
//	WriteWord(derivative);
//	setQMC(PI_SET_ACC);
//	WriteDWord(acceleration*819/78125);
	setQMC(SET_KP, m_Axis, proportional);
	setQMC(SET_KI, m_Axis, integral);
	setQMC(SET_KD, m_Axis, derivative);
	SetAcceleration(acceleration);
}


void C843::SetVelocity(long velocity)
{
//	setQMC(m_Axis);
//	setQMC(PI_SET_VEL);
//	WriteDWord(velocity*16384/625);
	m_Velocity = velocity;
	//execute(m_Axis, SV, velocity, m_Report);
	setQMC(SET_VELOCITY, m_Axis, (long)(velocity*26.86976));
	
}

void C843::SetVelocityFraction(double fraction)
{
	SetVelocity((long)(m_TopSpeed*fraction));
}

unsigned short C843::ReadSignalStatus() 
{
	
	unsigned short status;
//	setQMC(m_Axis);
//	status = ReadWord();
	get_signal_status(m_Axis+1, &status);
	return status;
}

void C843::WaitForStop()
{
//	setQMC(m_Axis);
//	setQMC(PI_CLR_STATUS);
	unsigned short Status;
/*	long ClockTime, NewTime;
	getQMC(GET_TIME, m_Axis, &ClockTime);
	do
	{
		getQMC(GET_TIME, m_Axis, &NewTime);
	} while (ClockTime == NewTime);
	ClockTime = NewTime;
	do
	{
		getQMC(GET_TIME, m_Axis, &NewTime);
	} while (ClockTime == NewTime);*/
	Pause(3);
	while(((Status = ReadActivityStatus()) &1024) != 0)
		;
}

void C843::FindHome()
{	
	if (m_StageType != ROTATIONAL_PD)
	{
	long Position;
	setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
	if (m_StageType == LINEAR_PD)
		SetVelocityFraction(0.5);
	else
		SetVelocityFraction(1.0);
	/*if (m_StageType == LINEAR_PD || m_StageType == LINEAR_GEARED)
	{
		if (GetLimitSwitches() & 0x02)
		{
			Move(-1000000);
			while(GetLimitSwitches() & 0x02)
				;
		}
		setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
		SetVelocityFraction(0.5);
		Move(+10000000);//				Hit +ve end stop.
		WaitForStop();
		setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
		SetVelocityFraction(1.0);
	}*/
	setQMC(SET_SIGNAL_SENSE, m_Axis, 0);
	Move(1000000);
	while(ReadSignalStatus()&0x08)
		;
	Move(-10000000);//				Move in -ve direction.
	while(!(ReadSignalStatus()&0x08))
		;
	SetVelocityFraction(0.1);
	
	Move(10000000);//				Reverse at 1/10th speed.
	Position = GetCapturePos();//		Wait for home and store position.
	Move(Position);
	WaitForStop();
	//if (m_StageType == ROTATIONAL_DIRECT)
	//	Step += 133550;//			Sets the offset for rotational stage
	setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
	SetVelocityFraction(1.0);
	Move(0L);
	}
	else
	{
		RotationHome();
	}

}

void C843::RotationHome(void)
{
	long Position;
	setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
	SetVelocityFraction(1.0);
	
	setQMC(SET_SIGNAL_SENSE, m_Axis, 0);
	Move(-10000000);//				Move in -ve direction.
	while(!(ReadSignalStatus()&0x08))
		;
	Move(1000000);
	while(!(ReadSignalStatus()&0x08))
		;
	while(ReadSignalStatus()&0x08)
		;
	//SetVelocityFraction(0.1)
	Move(-10000000);//				Move in -ve direction.
	while(ReadSignalStatus()&0x08)
		;
	while(!(ReadSignalStatus()&0x08))
		;
	SetVelocityFraction(0.1);
	
	Move(10000000);//				Reverse at 80% speed.
	Position = GetCapturePos();//		Wait for home and store position.
	Move(Position);
	WaitForStop();
	
	setQMC(SET_ACTUAL_POSITION,m_Axis,0);//		Set position to zero.
	SetVelocityFraction(1.0);
	Move(0L);
}


/*void C843::ReadByte(unsigned char *pByte)
{
	while((_inp(MOTOR_BASE+1)&128) == 0)
		;
	*pByte=_inp(MOTOR_BASE);
}*/

/*short C843::ReadWord()
{
	short result;
	unsigned char *pByte;
	pByte = (unsigned char*) &result;
	ReadByte(pByte+1);
	ReadByte(pByte);
	return result;
}*/

/*void C843::StopAtEnd()
{
	while(!(ReadStatus() & 0x60))
		;
	setQMC(PI_SMOOTH_STOP,m_Axis,0);
	setQMC(PI_UPDATE,m_Axis,0);
}*/

/*long C843::ReadDWord()
{
	long result;
	unsigned char *pByte;
	pByte = (unsigned char*) &result;
	ReadByte(pByte+3);
	ReadByte(pByte+2);
	ReadByte(pByte+1);
	ReadByte(pByte);
	return result;
}*/

long C843::GetCapturePos()
{
	long Position;
	getQMC(GET_CAPTURE_VALUE,m_Axis,&Position);
	setQMC(SET_SIGNAL_SENSE, m_Axis, 0x00);
	setQMC(SET_CAPTURE_SOURCE,m_Axis,1);// Set capture for home position
	setQMC(RESET_EVENT_STATUS,m_Axis,0XF7);
	while(!(ReadEventStatus() & 0x08))
		;
	getQMC(GET_CAPTURE_VALUE,m_Axis,&Position);
	if (m_StageType == ROTATIONAL_PD)
		Position /= -5;
	if (m_StageType == LINEAR_PD1)
		Position /= 1.024;
	return Position;
}

long C843::GetPosition()
{
	long Position;
	getQMC(GET_ACTUAL_POSITION,m_Axis,&Position);
	if (m_StageType == ROTATIONAL_PD)
		Position /= -5;
	if (m_StageType == LINEAR_PD1)
		Position /= 1.024;
	return Position;
}

int C843::GetLimitSwitches()
{
	// Bit 0 = +ve switch, bit 1 = -ve switch, 1 = set.
	unsigned short Status;
	Status = ReadSignalStatus();
	return (Status>>4) & 0x03;
}

void C843::Stop()
{
	setQMC(SET_STOP_MODE,m_Axis,2);
	setQMC(UPDATE,m_Axis,0);
	SetVelocity(m_Velocity);
}

void C843::WaitForPositionPositive(long Position)
{
	/*setQMC(m_Axis);
	setQMC(PI_SET_I);
	setQMC(PI_SET_INTRPT_MASK);
	WriteWord(0x04);//			Set interrupt for breakpoint
	setQMC(PI_RST_INTRPT);
	setQMC(PI_SET_BRK_PNT);
	WriteDWord(Position);
	setQMC(PI_SET_ACTL_POS_BRK);
	while(_inp(MOTOR_BASE+1)&0x40)// Wait for interrupt line (polling)
		;*/
	while(GetPosition() < Position)
		;
}

void C843::SetAcceleration(long Acc)
{
	setQMC(SET_ACCELERATION,m_Axis,(long)(Acc*0.0110166));
	setQMC(SET_DECELERATION,m_Axis,(long)(Acc*0.0110166));
	setQMC(UPDATE,m_Axis,0);
}

int C843::GetEndStopPosition()
{
	long Position = m_EndStopPosition;
	if (m_StageType == ROTATIONAL_PD)
		Position /= -5;
	return Position;
}

void C843::MoveToEnd()
{
	Move((m_EndStopPosition*97)/100);
}

unsigned short C843::ReadEventStatus(void)
{
	unsigned short Status;
	get_event_status(m_Axis+1, &Status);
	return Status;
}

unsigned short C843::ReadActivityStatus(void)
{
	unsigned short Status;
	get_activity_status(m_Axis+1, &Status);
	return Status;
}

long C843::GetCaptureNeg()
{
	long Position;
	getQMC(GET_CAPTURE_VALUE,m_Axis,&Position);
	setQMC(SET_SIGNAL_SENSE, m_Axis, 0x08);
	setQMC(RESET_EVENT_STATUS,m_Axis,0XF7);
	setQMC(SET_CAPTURE_SOURCE,m_Axis,1);// Set capture for home position
	while(!(ReadEventStatus() & 0x08))
		;
	getQMC(GET_CAPTURE_VALUE,m_Axis,&Position);
	if (m_StageType == ROTATIONAL_PD)
		Position /= -5;
	return Position;
}

void C843::Output(char OutputData)
{
	setQMC(WRITE_IO, 0, OutputData);
}

void C843::TDITriggerHigh(void)
{
	execute(0,CN,1,m_Report);
}

void C843::TDITriggerLow(void)
{
	execute(0,CF,1,m_Report);
}

void C843::TriggerCamera(void)
{
	TDITriggerLow();
	Pause(1);
	TDITriggerHigh();
}

void C843::SetTopSpeed(int Speed)
{
	m_TopSpeed = Speed;
}

void C843::Pause(long NumClockCycles)
{
	long ClockTime, NewTime;
	getQMC(GET_TIME, 0, &ClockTime);
	do
	{
		getQMC(GET_TIME, 0, &NewTime);
	} while ((NewTime - ClockTime) < NumClockCycles);
}

void C843::Reset(void)
{
	if (!m_ChipReset)
	{
		OpenBoard();
		setQMC(RESET,0,0);
		OpenBoard();
	//	m_ChipReset = 1;
		TDITriggerHigh();
	}
}


int C843::SetTriggerEvent(BYTE TriggerAxis, short bpNo)
	{
	// this uses the QFL command set, so things are a little different
	// no units, just absolute counts. The first axis is axis zero.
	// we use bit '2' on event status register '1' for breakpoint 1
	// and bit 'E' as BP two 
	// we signal an event on AxisIO pin 0 (Axis 1)

	short tmp = 0;
	BYTE BIT = 2;
	for (tmp = 0; tmp<bpNo+1; tmp++)
		{
		set_triggered_event(0,TriggerAxis,BIT,1);
		BIT+=0x0c;
		}
	return 1;
	}

int C843::SetTriggerPoints(long Xpos1, long Ypos1, long Xpos2, long Ypos2, BOOL bothways)
	{
	//this assumes that X is axis 0 and Y is axis 1

	


	if(!bothways)
		{
		set_nonblocking_breakpoint(0,0,Xpos1);
		//set_nonblocking_breakpoint(1,0,Ypos1);
		}
	else
		{
		set_nonblocking_breakpoint(0,0,Xpos1);
		//set_nonblocking_breakpoint(0,1,Xpos2);
		//set_nonblocking_breakpoint(1,0,Ypos1);
		//set_nonblocking_breakpoint(1,1,Ypos2);
		}
		return 1;
	}






int C843::SetTriggerPoint(BYTE TriggerAxis, long position)
	{
	set_nonblocking_breakpoint(TriggerAxis, 0, position);
return 1;
	}

void C843::set_nonblocking_breakpoint(BYTE axis, BYTE BP_no, long value)
	{
	//Axes run from Axis0 to Axis3 in this way of addressing them. Just to confuse matters.

	WORD BPword = 0x0000;
	BPword |=BP_no;

	WORD BP_second_dataword = 0x0000;
	BP_second_dataword |=(6<<8);

	//BP_second_dataword |=(1<<4);	//Update axis 
	//BP_second_dataword |=(2<<4);	//Hard stop axis -works! yay!
	//BP_second_dataword |=(3<<4);  //slow stop
	//BP_second_dataword |=(4<<4);	//Motor off
	BP_second_dataword |=(0<<4);	//Do Nothing - take no action on a BP, just flag that it happened.
	
	BP_second_dataword |=axis; //
	//BP_second_dataword |=1; //Axis2

	
	HRESULT tmp;
	long BPReadback;


	tmp = setQMCA(SET_BREAKPOINT_VALUE, axis, BPword, value);
	if(tmp == NULL)
	{ 
	  printf("Error setting BP value... but it might work anyway...\n");
	  tmp = getQMC(GET_BREAKPOINT_VALUE, axis, &BPReadback);
	  printf("Value Set was... %d",BPReadback);
	
	}

	tmp = setQMCA(SET_BREAKPOINT, axis, BPword, BP_second_dataword);
	if(tmp == NULL)
	{ 
	  printf("Error setting BP on Axis... but it might work anyway...\n");
	}
	}

void C843::set_triggered_event(BYTE AxisIOpin, BYTE TriggerAxis, BYTE bit, BYTE status_register)
	{
		//15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
		//0  0  0  0      R E G   B I T  SOURCE


	unsigned short data = 0x00;	//16bits of goodness to pack with our commands

	setQMC(RESET_EVENT_STATUS, m_Axis, ~0x4); //reset breakpoint bit in status regsiter
	//setQMC(RESET_EVENT_STATUS, 1, 0x8fb); //reset breakpoint bit in status regsiter

	//tell IO pin to track encoder A value as a test

	
	//pack status register as bits 11 to 8

	status_register <<= 4;
	data |= status_register;
	data <<= 4;
	
	//pack BIT as bits 7 to 4
	bit <<= 4;
	data |= bit;

	//pack TriggerAxis as SOURCE

	data |= TriggerAxis;

	
	setQMC(SET_AXIS_OUT_SOURCE,0,data);
	
	}

int C843::CheckPositions(void)
	{
#define limiter 5000

	long first_time[limiter], second_time[limiter], xpos[limiter], ypos[limiter], counter;
	for (counter=0;counter<limiter;counter++)
		{
		getQMC(GET_TIME, 0, &first_time[counter]);
		getQMC(GET_ACTUAL_POSITION, 0, &xpos[counter]);
		getQMC(GET_ACTUAL_POSITION, 1, &ypos[counter]);
		getQMC(GET_TIME, 0, &second_time[counter]);
		}
	for (counter=0;counter<limiter;counter++)
		{
		printf("\nTime = %d", first_time[counter]);
		printf("\nXPOS = %d", xpos[counter]);
		printf("\nYPOS = %d", ypos[counter]);
		printf("\nTime = %d", first_time[counter]);
		printf("\n");
		}
return 1;

	}

