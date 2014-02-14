#define BOARD_WIDTH 1.219
#define BOARD_HEIGHT 2.438 //lengths in meters, yo
#define NUM_OBSTACLES 6
#define NUM_WAYPOINTS 12
#define START_X 0.01 //dummy values
#define START_Y 0.01
#define GOAL_X 0.02
#define GOAL_Y 0.01

typedef struct graphNode{
	float x;
	float y;
	graphNode *neighbors[5]; //array of pointers to neighbors. has at most 5, including .
} node;

typedef struct obstacle{
	float c0x;	//its four corners. should go clockwise around it and include padding
	float c0y;
	float c1x;
	float c1y;
	float c2x;
	float c2y;
	float c3x;
	float c3y;
} obstacle;


float max(float a, float b){
	if (a > b) return a;
	return b;
}

float min(float a, float b){
	if (a < b) return a;
	return b;
}

/* L1Distance: computes the L1 (manhattan) distance between st and end.
*
float L1Distance(node st, node end){
	if (st == NULL || end == NULL){
		writeDebugStream("null point passed to L1Distance! \n");
		return 1000000.0; //don't go this way, something's wrong
	}
	return abs((end.x)-(st.x))+abs((end.y)-(st.y));
}
*/
/* L2Distance: computes the L2 (euclidean) distance between st and end.
*/
float L2Distance(node st, node end){
	if (st == NULL || end == NULL){
		writeDebugStream("null point passed to L1Distance! \n");
		return 1000000.0; //don't go this way, something's wrong
	}
	return sqrt(pow((end.x)-(st.x),2.0)+pow((end.y)-(st.y),2.0));
}

/* cost: computes the cost of the edge between st and end.
*  		current metric: (L2 distance from st to end) + 0.5*(L2 from end to goal)
*
float cost(node st, node end, node goal){
	return (L2Distance(st,end)+0.5*L2Distance(end,goal));
}
*/

/* crosses: does a path from s1 to e1 cross a path from s2 to e2? 1 = yes, 0 = no
*/
int pathsCross(node s1, node e1,float s2x,float s2y,float e2x, float e2y){
	float ub1 = max(s1.y,e1.y);
	float db1 = min(s1.y,e1.y);
	float rb1 = max(s1.x,e1.x);
	float lb1 = min(s1.x,e1.x);

	float ub2 = max(s2y,e2y);
	float db2 = min(s2y,e2y);
	float rb2 = max(s2x,e2x);
	float lb2 = min(s2x,e2x);

	if ((ub1 >= ub2 && db1 <= ub2)||(ub1 >= db2 && db1 <= db2)){ //does 2 fall inside 1?
		if ((rb1 >= rb2 && lb1 <= rb2)||(rb1 >= lb2 && lb1 <= lb2)){
			return 1;
		}
	}
  if ((ub2 >= ub1 && db2 <= ub1)||(ub2 >= db1 && db2 <= db1)){ //does 1 fall inside 2?
		if ((rb2 >= rb1 && lb2 <= rb1)||(rb2 >= lb1 && lb2 <= lb1)){
			return 1;
		}
	}
	return 0;
}

/*crossesObstacle: determines if a path from st to end will cross an obstacle
*	does this by determining if the path will cross an imaginary path made
*	by the corners of the object. returns 1 for true, 0 for false
*     Note: the circles, for simplicity, are treated as diamonds: <o>
*/
int crossesObstacle(node st, node end, obstacle *obstacles){
	for(int i = 0; i < NUM_OBSTACLES; i++){
		if  (pathsCross(st,end,obstacles[i].c1,obstacles[i].c2)
			|| pathsCross(st,end,obstacles[i].c2,obstacles[i].c3)
		  || pathsCross(st,end,obstacles[i].c3,obstacles[i].c4)
		  || pathsCross(st,end,obstacles[i].c4,obstacles[i].c1)){
			return 1;
		}
	}
	return 0;
}


task main()
{
	//build the graph, hardcoded and miserable

  //fill in obstacle array
//	obstacle obArray[NUM_OBSTACLES];

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
	graph[3].neighbors[0] = &(graph[7]);
	graph[3].neighbors[1] = &(graph[8]);
	/*
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
	*/
	//start and end
	node st;
	node goal;
	st.x = START_X;
	st.y = START_Y;
	goal.x = GOAL_X;
	goal.y = GOAL_Y;
	st.neighbors[0] = &goal;// this is dangerous and should be changed
	goal.neighbors[0] = &st;
	//now add start and end- go through waypoints, finding closest valid one.
	//connect the start and end to those points.
	for(int i = 0; i < NUM_WAYPOINTS; i++){
		float d1 = L2Distance(st,graph[i]);
		float d2 = L2Distance(st,*(st.neighbors[0]));
		if (d1 < d2){}
 	//	&& (!crossesObstacle(st,graph[i],obArray))){
	//		st.neighbors[0] = &(graph[i]);
	//  }
  }
}
