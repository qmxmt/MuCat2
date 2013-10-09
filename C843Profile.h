#pragma once



class C843Profile {

public:
		C843Profile(int numberofpoints);		//constructor.

		int init(void);						//load up the defaults
		int SetAcceleration(double);		//acceleration and deceleration fraction
		int SetVelocity(double);			//velocity	mm/s
//		int SetRadius(double);				//distance mm
//		int SetRunInOut(double);			//width of camera in mm, class converts to an angular distance
//		int CalculateArc();					//calculates the profile & returns 0 if in error
		
		void SetTriggerPoint(BYTE TriggerAxis, long position);
		int SetTriggerPoints(double startangle, double endangle, double radius, BOOL bothways);
		int SetTriggerPoints(long Xpos1, long Ypos1, long Xpos2, long Ypos2, BOOL bothways);
		
		int SetTriggerEvent(BYTE TriggerAxis, short bpNo);
		
		int SetupArc(double radius, double phase_start, double angle, double runInOff);
		int Update(BOOL display);			//update the profile and display it onscreen if display is set
		int RunProfile();					//run the profile
		int CheckPositions(void);
		int CheckPositions(char* filename, double speed);
		
		//C843Profile(void);
		virtual ~C843Profile(void);
	
	protected:
	int load_stage_defaults(int ProfileID);				//set up the max and min values that are stage specific.
	void set_nonblocking_breakpoint(BYTE axis, BYTE BP_no, long value);
	void set_triggered_event(BYTE AxisIOpin, BYTE TriggerAxis, BYTE bit, BYTE status_register);

	
	
	
	
	
	};
