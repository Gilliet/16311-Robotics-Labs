#include "DFS.c"

#define BOARD_WIDTH 1.219
#define BOARD_HEIGHT 2.438 //lengths in meters, yo
#define NUM_OBSTACLES 6
#define NUM_WAYPOINTS 12
#define START_X 0.01 //dummy values
#define START_Y 0.01
#define GOAL_X 0.02
#define GOAL_Y 0.01
/*
already defined in dfs!
typedef struct graphNode{
	float x;
	float y;
	graphNode *neighbors[5];
	//ptrs to neighbors! any node has <= 5 neighbors, including start & goal.
	//start goes in index 3 if it's there, goal goes in index 4
} node;
*/

float max(float a, float b){
	if (a > b) return a;
	return b;
}

float min(float a, float b){
	if (a < b) return a;
	return b;
}

/* L1Distance: computes the L1 (manhattan) distance between st and end.
*/
float L1Distance(node st, node end){
	if (st == NULL || end == NULL){
		writeDebugStream("null point passed to L1Distance! \n");
		return 1000000.0; //don't go this way, something's wrong
	}
	return abs((end.x)-(st.x))+abs((end.y)-(st.y));
}

/* L2Distance: computes the L2 (euclidean) distance between st and end.
*/
float L2Distance(node *st, node *end){
	if (st == NULL || end == NULL){
		writeDebugStream("null point passed to L2Distance! \n");
		return 1000000.0; //don't go this way, something's wrong
	}
	writeDebugStream("endx: %f2 stx: %f2 endy: %f2 sty: %f2\n",end->x,st->x,end->y,st->y);
	return sqrt(pow((end->x)-(st->x),2.0)+pow((end->y)-(st->y),2.0));
}

/* cost: computes the cost of the edge between st and end.
*  		current metric: (L2 distance from st to end) + 0.5*(L2 from end to goal)
*
float cost(node st, node end, node goal){
	return (L2Distance(st,end)+0.5*L2Distance(end,goal));
}
*/

path *makePath(float startx, float starty, float goalx, float goaly){
	//build the graph, hardcoded and miserable
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

 for(int i = 0; i < 1; i++){
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
		}
  }

	writeDebugStream("successfully put in start and goal.\n");
	//now do dfs to find a path. dfs(start,goal)
  //assumption: from path, we get a float * of points to travel to
  path *traveledPath;
  node visitedNodes[14];
  int yay =0;// DFS (traveledPath, st, goal);
  if (!yay) writeDebugStream("DFS unsuccessful! \n");
  //path[0] = st.x; path[1] = st.y;
  //path[2] = goal.x; path[3] = goal.y;

	writeDebugStream("DFS completed.\n");
  return traveledPath;
}
/*
task main()
{
	//build the graph, hardcoded and miserable
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
	graph[1].neighbors[0] = &(graph[0]);
	graph[1].neighbors[1] = &(graph[2]);
	graph[2].neighbors[0] = &(graph[1]);
	graph[2].neighbors[1] = &(graph[9]);
	graph[2].neighbors[2] = &(graph[10]);
	graph[3].neighbors[0] = &(graph[7]);
	graph[3].neighbors[1] = &(graph[8]);
	graph[3].neighbors[2] = &(graph[11]);

	graph[4].neighbors[0] = &(graph[5]);
	graph[5].neighbors[0] = &(graph[4]);
	graph[5].neighbors[1] = &(graph[6]);
	graph[6].neighbors[0] = &(graph[5]);
	graph[6].neighbors[1] = &(graph[7]);
	graph[7].neighbors[0] = &(graph[6]);
	graph[7].neighbors[1] = &(graph[9]);
	graph[7].neighbors[2] = &(graph[3]);
	graph[8].neighbors[0] = &(graph[3]);
	graph[9].neighbors[0] = &(graph[2]);
	graph[9].neighbors[1] = &(graph[7]);

	graph[10].neighbors[0] = &(graph[2]);
	graph[11].neighbors[0] = &(graph[3]);

	//start and end
	node st;
	node goal;
	st.x = START_X;
	st.y = START_Y;
	goal.x = GOAL_X;
	goal.y = GOAL_Y;

	//now add start and end- go through waypoints, finding closest valid one.
	//connect the start and end to those points.
	for(int i = 0; i < NUM_WAYPOINTS; i++){
		if (st.neighbors[0] == NULL){
			st.neighbors[0] = &graph[i];
			graph[i].neighbors[3] = &st;
		}else{
			if (L2Distance(st,graph[i]) < L2Distance(st,*(st.neighbors[0]))){
				st.neighbors[0] = &(graph[i]);
				graph[i].neighbors[3] = &st;
		  }
		}

		if (goal.neighbors[0] == NULL){
		  goal.neighbors[0] = &graph[i];
			graph[i].neighbors[4] = &goal;
		}else{
			if (L2Distance(goal,graph[i]) < L2Distance(goal,*(goal.neighbors[0]))){
				goal.neighbors[0] = &(graph[i]);
	  		graph[i].neighbors[4] = &goal;
		  }
		}
  }

  //for sanity's sake, print the graph to debug
  writeDebugStream("start (%f5,%f5) goes to (%f5,%f5)\n", st.x,st.y,
  									st.neighbors[0]->x,st.neighbors[0]->y);

  writeDebugStream("goal (%f5,%f5) goes to (%f5,%f5)\n", goal.x,goal.y,
  									goal.neighbors[0]->x,goal.neighbors[0]->y);
  for(int i = 0; i < NUM_WAYPOINTS; i++){
  	for(int j = 0; j < 5; j++){
  		if (graph[i].neighbors[j] != NULL){
  			  writeDebugStream("node %d (%f5,%f5) goes to (%f5,%f5)\n", i,
  			  					graph[i].x,graph[i].y,
  									graph[i].neighbors[j]->x,graph[i].neighbors[j]->y);
  		}
 	 }
	}
}*/
