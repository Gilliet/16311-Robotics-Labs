#include "RobotModel.c"
#include "RobotModel.h"
#include "RobotDriver.c"
#include "graphSearch.c"
//#include William's code

task main()
{
	float stx = 0.1;
	float sty = 0.1;
	float glx = 0.1;
	float gly = 0.5;
	int i = 0;
	robotModel rob;
	init(&rob);
	float *path = makePath(stx,sty,glx,gly);
		writeDebugStream("going!\n");
	while (path[i] != NULL){
		writeDebugStream("going to (%f2, %f2)\n",path[i],path[i+1]);
		driveTo(&rob,path[i]*100,path[i+1]*100);
		path = path+2;
	}

}
