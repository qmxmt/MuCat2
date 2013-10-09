#define NPARAMS				3
#define NAXES				2
#define	GET_SAMPLE_TIME		0x61
#define ARC_RADIUS			30
#define CIRCULAR_PROFILE	10



	char szAxes[] = "12"; // determine names of the axes
	char szBAxes[] = "12"; // determine names of x- and y- Axes for CircleGenerator
						   // that way you can switch the axes without reconnecting
	int board = 1;			// number of used Board
	
	char* szStages[] = { "M-531.PD","M-531.PD"}; // determine stages on axes
	
	BOOL bShowDialog = TRUE;// if you don't want to edit settings with the dialog, set FALSE

	double dVals[4];		// Values to pass to MVR(move relative)-Command
	double dPoses[4];		// Values to pass to MOV(move to position)-Command
	double dMaxPoses[4];	// Maximum Position Values
	double dMinPoses[4];	// Minimum Position Values
	
	int nrAxes = int(strlen( szAxes)); // number of Axes, defined by Axes string
	int nrBAxes = int(strlen( szBAxes)); // number of Axes, defined by Axes string
	int axis = 0;			// local variables
	int turn = 0;
	int i,j,k;
	int counter = 0;
	BOOL bFlags[4];			// return Variable for various Functions
	char szLimAxes[5];		// Axes w/ Limit Switches
	char szRefAxes[5];		// Axes w/ References
	char szNoRefAxes[5];	// Axes w/o References
	int nrLimAxes = 0;		// number of Axes w/ L.Sw.
	int nrRefAxes = 0;		// number of Axes w/ Ref.
	char szAxis[2] = { '\0', '\0' }; 
	char szAxisses[5] = { '\0', '\0' ,'\0', '\0' ,'\0'}; 
	char szStopCmd[2] = {(char)24,'\0'};
	char* szAnswer;
	int ProfileID = -32000;
	double startX = 0, startY = 0;
	int BoardHandle;
	



