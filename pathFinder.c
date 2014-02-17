#include "RobotModel.c"
#include "RobotModel.h"
#include "RobotDriver.c"
#include "graphSearch.c"
#include "DFS.c"

task main()
{
	float stx = 0.1;
	float sty = 0.1;
	float glx = 0.1;
	float gly = 0.5;

	robotModel rob;
	init(&rob);
	path *botPath = makePath(stx,sty,glx,gly);
	writeDebugStream("going!\n");

	for(int i = 0; i < botPath->nElems; i++){
		writeDebugStream("going to (%f2, %f2)\n", botPath->coords[i], botPath->coords[i+1]);
	  driveTo(&rob,(botPath->coords[i])*100,(botPath->coords[i+1])*100);
  }

}
