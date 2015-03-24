#pragma once


#define LINEAR_PD 1
#define LINEAR_GEARED 2
#define ROTATIONAL_DIRECT 3
#define ROTATIONAL_GEARED 4
#define ROTATIONAL_PD 5
#define LINEAR_PD1 6

class C843  
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
	C843(int Axis, int Stage);
	virtual ~C843();
	unsigned short ReadSignalStatus();
	void MoveToEnd();
	int SetTriggerPoints(long Xpos1, long Ypos1, long Xpos2, long Ypos2, BOOL bothways);
	int SetTriggerPoint(BYTE TriggerAxis, long position);
	int SetTriggerEvent(BYTE TriggerAxis, short bpNo);
	int C843::CheckPositions(void);

protected:
	int GetEndStopPosition();
	static int m_EndStopPosition;
	int m_StageType;
	int GetLimitSwitches();
	long GetCapturePos();
	long GetCaptureNeg();
//	long ReadDWord();
//	short ReadWord();
//	void ReadByte(unsigned char* pByte);
	static int m_ChipReset;
	static char* m_Report;
	long m_TopSpeed;
	unsigned char m_Axis;
//	void WriteDWord(long x);
//	void WriteWord(short x);
//	void WriteByte(unsigned char x);
	void set_nonblocking_breakpoint(BYTE axis, BYTE BP_no, long value);
	void set_triggered_event(BYTE AxisIOpin, BYTE TriggerAxis, BYTE bit, BYTE status_register);

public:
	unsigned short ReadEventStatus(void);
	unsigned short ReadActivityStatus(void);
protected:
	long m_Velocity;
public:
	static void Output(char OutputData);
	static void TDITriggerHigh(void);
	static void TDITriggerLow(void);
	static void TriggerCamera(void);
	void SetTopSpeed(int Speed);
	static void Pause(long NumClockCycles);
	static void Reset(void);
	void RotationHome(void);
};
