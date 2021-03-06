#include "RobotModel.c"
#include "RobotModel.h"
#include "RobotDriver.c"
#include "graphSearch.c"
#include "DFS.c"

task main()
{
	float startx = 0.0;
	float starty = 0.0;
	float goalx = .3048;//1.676;
	float goaly = .9144;//0.6096;
	writeDebugStream("starting!\n");
	robotModel rob;
	init(&rob,startx,starty,0.0);
	writeDebugStream("init successful.\n");


	//wow sorry






	writeDebugStream("making path.\n");
	node graph[NUM_WAYPOINTS];
	//bottom row
	graph[0].x = 0.1524; graph[0].y = 0.1524;
	graph[1].x = 0.762;	 graph[1].y = 0.1524;
	graph[2].x = 0.9144; graph[2].y = 0.1524;
	graph[3].x = 2.134;  graph[3].y = 0.1524;
	//top row
	graph[4].x = 0.3048; graph[4].y = 0.9144;
	graph[5].x = 0.9144; graph[5].y = 1.067;
	graph[6].x = 1.372;  graph[6].y = 1.067;
	graph[7].x = 1.676;  graph[7].y = 0.6096;
	graph[8].x = 2.286;  graph[8].y = 0.762;
	graph[9].x = 1.3716; graph[9].y = 0.4572;
	graph[10].x = 1.3716; graph[10].y = 0.1524;
	graph[11].x = 1.676; graph[11].y = 0.1524;
	//set up neighbors. do we need to make the remaining ones NULL?
	graph[0].neighbors[0] = &(graph[1]);
	graph[0].neighbors[1] = NULL; graph[0].neighbors[2] = NULL;	graph[0].neighbors[3] = NULL;		graph[0].neighbors[4] = NULL;
	graph[1].neighbors[0] = &(graph[0]);
	graph[1].neighbors[1] = &(graph[2]);
	graph[1].neighbors[2] = NULL;	graph[1].neighbors[3] = NULL;		graph[1].neighbors[4] = NULL;
	graph[2].neighbors[0] = &(graph[1]);
	graph[2].neighbors[1] = &(graph[9]);
	graph[2].neighbors[2] = &(graph[10]);
	graph[2].neighbors[3] = NULL;		graph[2].neighbors[4] = NULL;
	graph[3].neighbors[0] = &(graph[7]);
	graph[3].neighbors[1] = &(graph[8]);
	graph[3].neighbors[2] = &(graph[11]);
	graph[3].neighbors[3] = NULL;		graph[3].neighbors[4] = NULL;


	graph[4].neighbors[0] = &(graph[5]);
	graph[4].neighbors[1] = NULL;		graph[4].neighbors[2] = NULL; graph[4].neighbors[3] = NULL;		graph[4].neighbors[4] = NULL;
	graph[5].neighbors[0] = &(graph[4]);
	graph[5].neighbors[1] = &(graph[6]);
	graph[5].neighbors[2] = NULL;		graph[5].neighbors[3] = NULL; graph[5].neighbors[4] = NULL;
	graph[6].neighbors[0] = &(graph[5]);
	graph[6].neighbors[1] = &(graph[7]);
	graph[6].neighbors[2] = NULL;		graph[6].neighbors[3] = NULL; graph[6].neighbors[4] = NULL;
	graph[7].neighbors[0] = &(graph[6]);
	graph[7].neighbors[1] = &(graph[9]);
	graph[7].neighbors[2] = &(graph[3]);
	graph[7].neighbors[3] = NULL; graph[7].neighbors[4] = NULL;
	graph[8].neighbors[0] = &(graph[3]);
	graph[8].neighbors[1] = NULL;		graph[8].neighbors[2] = NULL; graph[8].neighbors[3] = NULL;		graph[8].neighbors[4] = NULL;
	graph[9].neighbors[0] = &(graph[2]);
	graph[9].neighbors[1] = &(graph[7]);
	graph[9].neighbors[2] = NULL;		graph[9].neighbors[3] = NULL; graph[9].neighbors[4] = NULL;

	graph[10].neighbors[0] = &(graph[2]);
	graph[10].neighbors[1] = NULL;		graph[10].neighbors[2] = NULL; graph[10].neighbors[3] = NULL;		graph[10].neighbors[4] = NULL;
	graph[11].neighbors[0] = &(graph[3]);
	graph[11].neighbors[1] = NULL;		graph[11].neighbors[2] = NULL; graph[11].neighbors[3] = NULL;		graph[11].neighbors[4] = NULL;

	//start and end
	node st;
	node goal;
	st.x = startx;
	st.y = starty;
	goal.x = goalx;
	goal.y = goaly;
	st.neighbors[0] = NULL;
	goal.neighbors[0] = NULL;
	writeDebugStream("set up neighbors, except for start and goal.\n");

	//now add start and end- go through waypoints, finding closest valid one.
	//connect the start and end to those points.

	for(int i = 0; i < NUM_WAYPOINTS; i++){
		if (st.neighbors[0] == NULL){
			writeDebugStream("set st's initial neighbor. \n");
			st.neighbors[0] = &graph[i];
			graph[i].neighbors[3] = &st;
			writeDebugStream("st.x: %f2 st.y: %f2 stn.x: %f2 stn.y: %f2\n",st.x,st.y,st.neighbors[0]->x,st.neighbors[0]->y);

			}else{
			if (L2Distance(&st,&graph[i]) < L2Distance(&st,(st.neighbors[0]))){
				st.neighbors[0] = &(graph[i]);
				graph[i].neighbors[3] = &st;
			}
			writeDebugStream("st.x: %f2 st.y: %f2 stn.x: %f2 stn.y: %f2\n",st.x,st.y,st.neighbors[0]->x,st.neighbors[0]->y);

		}

		if (goal.neighbors[0] == NULL){
			writeDebugStream("set goal's initial neighbor. \n");
			goal.neighbors[0] = &graph[i];
			graph[i].neighbors[4] = &goal;
			}else{
			if (L2Distance(&goal,&graph[i]) < L2Distance(&goal,(goal.neighbors[0]))){
				goal.neighbors[0] = &(graph[i]);
				graph[i].neighbors[4] = &goal;
			}
			writeDebugStream("goal.x: %f2 goal.y: %f2 goal.x: %f2 goal.y: %f2\n",goal.x,goal.y,goal.neighbors[0]->x,goal.neighbors[0]->y);
		}
	}

	writeDebugStream("successfully put in start and goal.\n");
	//now do dfs to find a path. dfs(start,goal)

	float cs[16];
	path botPath;
	botPath.nElems = 1;
	botPath.coords = cs;
	botPath.coords[0] = startx;
	botPath.coords[1] = starty;

	int yay = 0;

	node *stack[12];
	node *visited[12];
	int stackCount = 0;
	int visitCount = 0;
	stack[stackCount] = &st;
	stackCount++; // Put the first node in the stack.
	node* currNode;
	while (stackCount > 0) { // While there are still nodes to examine.
		stackCount--;
		currNode = stack[stackCount]; // Pop the stack.
		int av = 0;
		for(int i = 0; i < visitCount; i++) {
			if(visited[i].x == currNode->x && visited[i].y == currNode->y) av = 1;
		}
		if (!av) { // If we have not already visited the node.
			visited[visitCount] = currNode; // Visit the node.
			visitCount++;
			writeDebugStream("Visiting: %f,%f\n", currNode->x,currNode->y);
			botPath.coords[2 * botPath.nElems] = currNode->x; // Add the node to the path.
			botPath.coords[2 * botPath.nElems + 1] = currNode->y;
			botPath.nElems++;
			if (currNode->x == goal.x && currNode->y == goal.y) {
				writeDebugStream("We are done!\n");
				yay =  1;// If we are at the goal then we are done.
				break;
			}
			writeDebugStream("aslkjfdajfhasd: %f\n",currNode->neighbors[0]);
			for (int i = 0; i < 5; i++) { // Otherwise add every neighbor to the stack.
				if (currNode->neighbors[i] != NULL) {
					stack[stackCount] = (currNode->neighbors[i]);
					stackCount++;
				}
			}
			} else {
			botPath.nElems--; // If we could not find the goal then backtrack.
		}
	}
	yay = 0; // We failed to find a path.







	if (!yay) writeDebugStream("DFS unsuccessful! \n");
	//path[0] = st.x; path[1] = st.y;
	//path[2] = goal.x; path[3] = goal.y;

	writeDebugStream("DFS completed.\n");






	writeDebugStream("botPath length is: %d\n", botPath.nElems);
	for (int i = 1; i < botPath.nElems; i++) {
		writeDebugStream("Path point: %d is x:%f, y:%f\n",i,botPath.coords[2*i], botPath.coords[2 * i + 1]);
	}
	//botPath = makePath(stx,sty,glx,gly);
	writeDebugStream("going!\n");

	for(int i = 1; i < botPath.nElems; i++){
		writeDebugStream("going to (%f2, %f2)\n", botPath.coords[2 * i], botPath.coords[2 * i+1]);
		driveTo(&rob,(botPath.coords[2 * (i)])*100 - 15,(botPath.coords[2 * i + 1])*100 - 15);
	}

}
