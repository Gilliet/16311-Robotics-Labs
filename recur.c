#define NUM_POINTS 12
#include "RobotModel.c"
#include "RobotModel.h"
#include "RobotDriver.c"
float xNode (int index) {
	switch (index) {
	case 0:return 0.1524;
	case 1:return 0.762;
	case 2:return 0.9144;
	case 3:return 2.134;
	case 4:return 0.3048;
	case 5:return 0.9144;
	case 6:return 1.372;
	case 7:return 1.626;
	case 8:return 2.286;
	case 9:return 1.3716;
	case 10:return 1.3716;
	case 11:return 1.676;
	default: return 0;
	}
}
float yNode (int index) {
	switch (index) {
	case 0:return 0.1524;
	case 1:return 0.1524;
	case 2:return 0.1524;
	case 3:return 0.1524;
	case 4:return 0.9144;
	case 5:return 1.067;
	case 6:return 1.067;
	case 7:return 0.6096;
	case 8:return 0.762;
	case 9:return 0.4572;
	case 10:return 0.1524;
	case 11:return 0.1524;
	default: return 0;
	}
}

int getNeighbors (int index,int neighbor) {
	switch (index) {
	case 0:
		if (neighbor == 0) return 1;
		else return -1;
	case 1:
		switch (neighbor){
		case 0: return 0;
		case 1: return 2;
		default: return -1;
		}
	case 2:
		switch (neighbor){
		case 0: return 1;
		case 1: return 9;
		case 2: return 10;
		default: return -1;
		}
	case 3:
		switch (neighbor){
		case 0: return 7;
		case 1: return 8;
		case 2: return 11;
		default: return -1;
		}

	case 4:
		switch (neighbor){
		case 0: return 5;
		default: return -1;
		}
	case 5:
		switch (neighbor){
		case 0: return 4;
		case 1: return 6;
		default: return -1;
		}
	case 6:
		switch(neighbor){
		case 0: return 5;
		case 1: return 7;
		default: return -1;
		}
	case 7:
		switch(neighbor){
		case 0: return 6;
		case 1: return 9;
		case 2: return 3;
		default: return -1;
		}
	case 8:
		switch(neighbor){
		case 0: return 3;
		default: return -1;
		}
	case 9:
		switch(neighbor){
		case 0: return 2;
		case 1: return 7;
		default: return -1;
		}
	case 10:
		switch(neighbor){
		case 0: return 2;
		default: return -1;
		}
	case 11:
		switch(neighbor){
		case 0: return 3;
		default: return -1;
		}
	}
	return -1;
}
int path[12];
int disc[12];
int DFS (int depth, int currNode, int goalNode) {
	if (currNode == goalNode) {
		path[depth] = currNode;
		for (int i = depth + 1; i < NUM_POINTS; i++) {
			path[i] = -1;
		}
		return 1;
	}
	int i = 0;
	writeDebugStream("Visiting: %d\n",currNode);
	while (getNeighbors(currNode,i) != -1) {
		if (!disc[getNeighbors(currNode,i)]) {
			writeDebugStream("Depth: %d\n",depth);
			path[depth] = currNode;
			disc[currNode] = 1;
			int res = DFS(depth + 1, getNeighbors(currNode,i),goalNode);
			if (res) {
				return 1;
			}
		}
		i++;
	}
	return 0;
}


task main()
{
	float startx = .15;
	float starty = .15;
	float goalx =  3 * .15;
	float goaly = 5 * .15;
	float startmin = 0;
	float startdist = abs(startx - xNode(0)) + abs(starty - yNode(0));
	float goalmin = 0;
	float goaldist = abs(goalx - xNode(0)) + abs(goaly - yNode(0));
	for (int i = 1; i < NUM_POINTS; i++) {
		float dist = abs(startx - xNode(i)) + abs(starty - yNode(i));
		if (dist < startdist) {
			startmin = i;
			startdist = dist;
		}
		dist = abs(goalx - xNode(i)) + abs(goaly - yNode(i));
		if (dist < goaldist) {
			goalmin = i;
			goaldist = dist;
		}
	}
	for (int i = 0; i < NUM_POINTS; i++) {
		disc[i] = 0;
		path[i] = 0;
	}
	int res = DFS(0,startmin,goalmin);
	writeDebugStream("SUCCESS STATUS: %d\nPATH: [",res);
	for (int i = 0; i < NUM_POINTS; i++) {
		writeDebugStream("%d, ",path[i]);
	}
	writeDebugStream("]\n");

	int i = 0;
	robotModel rob;
	init(&rob,startx* 100,starty * 100,PI / 2);
	while (path[i] != -1) {
		float tempx = xNode(path[i]);
		float tempy = yNode(path[i]);
		writeDebugStream("ROBOT GOALS: %f,%f\n",tempx,tempy);
		driveTo(&rob,tempx*100,tempy*100);
		i++;
	}
	driveTo(&rob,goalx * 100,goaly * 100);

}
