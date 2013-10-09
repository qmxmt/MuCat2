#include "StdAfx.h"
#include "C843Profile.h"
#include "C843ProfileVars.h"
//#include "ProfileGeneratorDLL.h"
#include "C843_GCS_DLL.h"
//#include "SPAParams.h"
#include "c843cmd.h"
#include "C843.h"
#include <math.h>

using namespace std;
//TODO : add proper error handling to these methods - at the moment they just return the same value regardless of success or fail.


C843Profile::C843Profile(int numberofpoints)
	{
		//empty constructor

	}

//int C843Profile::init()
//	{
//	load_stage_defaults(ProfileID);
//	return 1;
//	}
//
//
//int C843Profile::SetAcceleration(double Acc)
//	{
//	
//	ProfileGenerator_SetParam(ProfileID,ACCFAC,Acc);
//	ProfileGenerator_SetParam(ProfileID,DECFAC,Acc);
//	return 1;
//	}
//int C843Profile::SetVelocity(double Vel)
//	{
//	
//	Vel = Vel/125.0;								//we need a fraction, top speed is 125mm/s so divide
//	ProfileGenerator_SetParam(ProfileID,VELFAC,Vel);
//	return 1;
//	}

//int C843Profile::SetRadius(double radius)
//	{
//	ProfileGenerator_SetParam(ProfileID,RADIUS,radius);
//	return 1;
//	}

int C843Profile::SetTriggerEvent(BYTE TriggerAxis, short bpNo)
	{
	// TriggerAxis as passed is from 1-4. Need to convert to QFL format (zerobased) 
	// this uses the QFL command set, so things are a little different
	// no units, just absolute counts. The first axis is axis zero.
	// we use bit '2' on event status register '1' for breakpoint 1
	// and bit 'E' as BP two 
	// we signal an event on AxisIO pin 0 (Axis 1)

	short tmp = 0;
	BYTE BIT = 2;
	for (tmp = 0; tmp<bpNo+1; tmp++)
		{
		set_triggered_event(0,TriggerAxis-1,BIT,1);
		BIT+=0x0c;
		}
	return 1;
	}
void C843Profile::SetTriggerPoint(BYTE TriggerAxis, long position)
	{
		//TriggerAxis in 1-4, needs to be in QFL 0-3 format.

	set_nonblocking_breakpoint(TriggerAxis-1, 0, position);

	}




//int C843Profile::SetTriggerPoints(double startangle, double endangle, double radius, BOOL bothways)
//	{
//	//units are in counts. NOT cm or anything nice
//	//radius is in cm
//	//20,000 counts per cm
//
//	long Xpos1 = 20000 * (radius * cos(startangle *(3.14/180)));
//	long Ypos1 = 20000 * (radius * sin(startangle *(3.14/180)));
//	long Xpos2 = 20000 * (radius * cos(endangle *(3.14/180)));
//	long Ypos2 = 20000 * (radius * sin(endangle *(3.14/180)));
//
//	//pass all values even if we only need 1 or 2 breakpoints, BOOL bothways deals with what is actually used.
//
//	SetTriggerPoints(Xpos1,Ypos1,Xpos2,Ypos2,bothways);
//	
//	return 1;
//	}

//int C843Profile::SetTriggerPoints(long Xpos1, long Ypos1, long Xpos2, long Ypos2, BOOL bothways)
//	{
//	//this assumes that X is axis 0 and Y is axis 1
//	//Trigger point values are in milimeter - convert to counts to program 
//
//	Xpos1 *= 2000;
//	Xpos2 *= 2000;
//	Ypos1 *= 2000;
//	Ypos2 *= 2000;
//
//
//	if(!bothways)
//		{
//		set_nonblocking_breakpoint(0,0,Xpos1);
//		set_nonblocking_breakpoint(1,0,Ypos1);
//		}
//	else
//		{
//		set_nonblocking_breakpoint(0,0,Xpos1);
//		set_nonblocking_breakpoint(0,1,Xpos2);
//		set_nonblocking_breakpoint(1,0,Ypos1);
//		set_nonblocking_breakpoint(1,1,Ypos2);
//		}
//		return 1;
//	}

//int C843Profile::SetupArc(double radius, double phase_start, double angle, double runInOff)
//	{
//
//	// the camera has a size, we need to be clear this size either side of the needed arc
//	// consider the camera size as a projection along the wanted arc length, this will over estimate
//	// the size, but is quick and easy
//
//	
//
//	double theta = 0;
//	
//	double runInOffAngle = runInOff/radius;
//	phase_start = phase_start - runInOffAngle;
//	theta =  angle + 2*runInOffAngle;
//	
//	startX = (radius * cos(phase_start*(3.1415926/180))+150);
//	
//	startY = (radius * sin(phase_start*(3.1415926/180)));
//	
//
//	//use the two following lines instead for centre of axis motion
//	//startX = (radius * cos(phase_start*(3.14/180))+ 150);
//	//startY = (radius * sin(phase_start*(3.14/180))+ 150);
//
//
//	ProfileGenerator_SetParam(ProfileID,STARTANGLE,phase_start);	//phase to start at
//	ProfileGenerator_SetParam(ProfileID,TRAVELANGLE,theta);			//total phase to move
//	ProfileGenerator_SetParam(ProfileID,RADIUS,radius);				//Radius of circular arc
//	ProfileGenerator_SetParam(ProfileID,STARTX,startX);				
//	ProfileGenerator_SetParam(ProfileID,STARTY,startY);	
//	ProfileGenerator_SetParam(ProfileID,CENTERX,0);					//centres at origin
//	ProfileGenerator_SetParam(ProfileID,CENTERY,0);
//	ProfileGenerator_SetParam(ProfileID,TARGETANGLE,360);
//	ProfileGenerator_SetParam(ProfileID,DIRECTION,1);	
//	ProfileGenerator_SetParam(ProfileID,STRETCHX,1);				//just hardcode these values
//	ProfileGenerator_SetParam(ProfileID,STRETCHY,1);				//they are just scale factors we set these from radius anyway
//	ProfileGenerator_SetParam(ProfileID,LISSAY,1);					//theses just allow for lissajours figures
//	ProfileGenerator_SetParam(ProfileID,LISSAX,1);					//we don't use them
//
//	ProfileGenerator_SetIntParam(ProfileID,WRAPPING,0);				//also not used
//	ProfileGenerator_SetIntParam(ProfileID,ADDITIONAL_HALTS,15);	// "    "   "
//
//	//int tmp = -32000;
//
//	//tmp = ProfileGenerator_GetError(ProfileID);
//	//tmp = ProfileGenerator_UpdateProfile(ProfileID, 100);
//	//tmp = ProfileGenerator_GetError(ProfileID);
//
//
//	return 1;
//
//	}

//int C843Profile::Update(BOOL display)
//	{
//	int tmp = -32000;
//
//	ProfileGenerator_GetError(ProfileID);
//	ProfileGenerator_UpdateProfile(ProfileID, 100);
//	ProfileGenerator_GetError(ProfileID);
//	ProfileGenerator_GenerateProfileOutput(ProfileID);			//generate a command string
//	
//	if (!display)
//		{return 1;}
//	else
//		tmp = ProfileGenerator_OpenDialog(ProfileID);				//let it be edited
//		ProfileGenerator_GenerateProfileOutput(ProfileID);			//re-generate the string to allow for edits 
//		return tmp;
//	}

//int C843Profile::RunProfile()
//	{
//	//pre move to start position
//	dPoses[0] = startX;
//	dPoses[1] = startY;
//
//	double velocity[2];
//	velocity[0] = 200;
//	velocity[1] = 200;
//
//	C843_VEL(ProfileID,szBAxes,velocity);
//	C843_MOV(ProfileID,szBAxes, dPoses);
//	BOOL bIsMoving = TRUE;
//		while(bIsMoving) // wait for end of motion
//		{
//			C843_IsMoving(BoardHandle, szBAxes, bFlags);
//			bIsMoving = FALSE;
//			for (axis = 0; axis < nrBAxes; axis++)
//			{
//				bIsMoving |= bFlags[axis];
//			}
//			Sleep(100);
//		}
//	int tmp = -32000;
//
//		do
//		{
//			tmp = ProfileGenerator_GetOutputSize(ProfileID,(long*)&j);
//			tmp = ProfileGenerator_GetError(ProfileID);			
//					if (j)
//					{
//						char* cmdString = new char[j];
//						ProfileGenerator_GetOutput(ProfileID,cmdString,j);
//						TRACE("%s \n",cmdString);
//						C843_GcsCommandset(BoardHandle, cmdString);
//						delete[] cmdString;
//
//					};
//
//				}while(j);
//		
//
//		//BOOL bTmp[2];
//				//for (int nn = 0; nn< 50;nn++)
//				//{
//				//	// this loop demonstrates how to poll the user profile mode activity
//				//	Sleep(200);
//				//	C843_IsUserProfileActive(BoardHandle,"12",bTmp);
//				//	TRACE("active: %d, %d\n",bTmp[0],bTmp[0]);
//				//}
//	return 1;
//	}
C843Profile::~C843Profile(void)
	{
	}

//int C843Profile::load_stage_defaults(int ProfileID)
//	{
//	//you must define a profile before doing this.
//	//these folloing paramaters MUST be set - damage may occur otherwise. YOU HAVE BEEN WARNED!
//
//
//
//	ProfileGenerator_SetParam(ProfileID,TIMEBASE,0.410);			//Utterly MAGIC - don't know where this value comes from yet
//	
//	ProfileGenerator_SetParam(ProfileID,MINX,0);					//stage specific (units  = mm)
//	ProfileGenerator_SetParam(ProfileID,MINY,0);					//stage specific (units  = mm)
//	
//	ProfileGenerator_SetParam(ProfileID,MAXY, 300);					//stage specific (units  = mm)
//	ProfileGenerator_SetParam(ProfileID,MAXX, 300);					//stage specific (units  = mm)
//	
//	ProfileGenerator_SetIntParam(ProfileID,XAXISNAME, (int)szBAxes[0]);				//single char name
//	ProfileGenerator_SetIntParam(ProfileID,YAXISNAME, (int)szBAxes[1]);				//single char name
//	
//	ProfileGenerator_SetParam(ProfileID,XAXISMAXVEL, 125);			//stage specific values here mm/s
//	ProfileGenerator_SetParam(ProfileID,XAXISMAXACC, 800);			//stage specific values here mm/s^2	
//	ProfileGenerator_SetParam(ProfileID,XAXISMAXDEC, 800);			//stage specific values here mm/s^2	
//	
//	ProfileGenerator_SetParam(ProfileID,YAXISMAXVEL, 125);			//stage specific values here mm/s
//	ProfileGenerator_SetParam(ProfileID,YAXISMAXACC, 800);			//stage specific values here mm/s^2	
//	ProfileGenerator_SetParam(ProfileID,YAXISMAXDEC, 800);			//stage specific values here mm/s^2	
//
//
//	//utterly crap numbers from autotune.
//	//magic PID numbers from autotune
//
//	////axis0 is lower axis
//	//setQMC(SET_KP, 0, 809);
//	//setQMC(SET_KI, 0, 16868);
//	//setQMC(SET_KD, 0, 309);
//
//	//setQMC(UPDATE, 0, 0);
//
//	//setQMC(SET_KP, 1, 644);
//	//setQMC(SET_KI, 1, 4091);
//	//setQMC(SET_KD, 1, 811);
//	//
//	//setQMC(UPDATE, 1, 0);
//
//
//	//end of DIRE WARNINGS.
//	return 1;
//	}



void C843Profile::set_nonblocking_breakpoint(BYTE axis, BYTE BP_no, long value)
	{
	setQMC(RESET_EVENT_STATUS, axis, ~0x4); //reset breakpoint bit in status regsiter

	WORD BPword = 0x0000;
	BPword |=BP_no;

	WORD BP_second_dataword = 0x0000;

	BP_second_dataword |=(3<<8);	//trigger = positive actual position
	
	BP_second_dataword |=(0<<4);	//Do Nothing
	
	//BP_second_dataword |=(1<<4); //Update axis 
	//BP_second_dataword |=(2<<4); //Hard stop axis
	//BP_second_dataword |=(3<<4); //slow stop
	//BP_second_dataword |=(4<<4); //Motor off

	
	BP_second_dataword |=0; //Axis1
	//BP_second_dataword |=1; //Axis2


	setQMCA(SET_BREAKPOINT_VALUE, axis, BPword, value);

	setQMCA(SET_BREAKPOINT, axis, BPword, BP_second_dataword);
	}

void C843Profile::set_triggered_event(BYTE AxisIOpin, BYTE TriggerAxis, BYTE bit, BYTE status_register)
	{
		//15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
		//0  0  0  0      R E G   B I T  SOURCE


	unsigned short data = 0x00;	//16bits of goodness to pack with our commands

	//pack status register as bits 11 to 8
	status_register <<= 4;
	data |= status_register;
	data <<= 4;
	
	//pack BIT as bits 7 to 4
	bit <<= 4;
	data |= bit;

	//pack TriggerAxis as SOURCE

	data |= TriggerAxis;

	setQMC(SET_AXIS_OUT_SOURCE,AxisIOpin,data);

	}

//int C843Profile::CheckPositions(void)
//	{
//#define limiter 26000
//
//	long first_time[limiter], second_time[limiter], xpos[limiter], ypos[limiter], counter;
//	for (counter=0;counter<limiter;counter++)
//		{
//		getQMC(GET_TIME, 0, &first_time[counter]);
//		getQMC(GET_ACTUAL_POSITION, 1, &ypos[counter]);
//		getQMC(GET_ACTUAL_POSITION, 0, &xpos[counter]);
//		getQMC(GET_TIME, 0, &second_time[counter]);
//		}
//	
//	TRACE("\nTime1, XPOS, YPOS, Time2");
//	for (counter=0;counter<limiter;counter++)
//		{
//		TRACE("\n %d, %d, %d, %d",first_time[counter],xpos[counter],ypos[counter],second_time[counter]);
//		}
//
//return 1;
//
//	}


//int C843Profile::CheckPositions(char* filename, double speed)
//	{
//
//#define arraylimit 64000				// if you need more than this then you are doing something wrong
//int counterlimit = 29800*(20/speed);
//
//if (counterlimit > arraylimit) 
//	{
//	::MessageBoxA(NULL,"Setting limit to arraylimit, to prevent errors - check the code or stage speed to stop this","BIT OF A PROBLEM OLD CHAP!",MB_OK|MB_ICONERROR);
//	printf("Setting limit to arraylimit, to prevent errors - check the code or stage speed to stop this");
//	counterlimit = arraylimit;
//	}
//
//ofstream out(filename);
//if(!out) { 
//    cout << "Cannot open file.\n"; 
//    return 1; 
//   } 
//
//	long first_time[arraylimit], second_time[arraylimit], xpos[arraylimit], ypos[arraylimit], counter;
//	for (counter=0;counter<counterlimit;counter++)
//		{
//		getQMC(GET_TIME, 0, &first_time[counter]);
//		getQMC(GET_ACTUAL_POSITION, 1, &ypos[counter]);
//		getQMC(GET_ACTUAL_POSITION, 0, &xpos[counter]);
//		getQMC(GET_TIME, 0, &second_time[counter]);
//		}
//	out << "Time1, XPos, YPos, Time2" <<endl;
//	for (counter=0;counter<counterlimit;counter++)
//		{
//		
//		out << first_time[counter]<< "," <<xpos[counter]<<","<<ypos[counter]<<","<<second_time[counter]<<endl;
//		}
//
//
//	out.close();
//return 0;
//
//	}