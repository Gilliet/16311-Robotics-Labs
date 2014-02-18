#define NUM_POINTS 12
float xNode (int index) {
	switch (index) {
	case 0:return 0.1524;
	case 1:return 0.762;
	case 2:return 0.9144;
	case 3:return 2.134;
	case 4:return 0.3048;
	case 5:return 0.9144;
	case 6:return 1.372;
	case 7:return 1.676;
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


task main()
{
	float startx = xNode(4);
	float starty = yNode(4);
	float goalx = xNode(0);
	float goaly = yNode(0);
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
	int path[12];
	int plen = 0;
	int stack[12];
	int visited[12];
	int stackCount = 0;
	int visitCount = 0;
	stack[stackCount] = startmin;
	stackCount++;
	int currNode;
	int succ = 0;
	while (stackCount > 0) {
		writeDebugStream("STACK: [");
		for (int i = 0; i < stackCount; i++) {
			writeDebugStream("%d ",stack[i]);
		}
		writeDebugStream("]\n");

		writeDebugStream("PATH: [");
		for (int i = 0; i < plen; i++) {
			writeDebugStream("%d ",path[i]);
		}
		writeDebugStream("]\n");

		stackCount--;
		currNode = stack[stackCount];
		int av = 0;
		for (int i = 0; i < visitCount; i++) {
			if (visited[i] == currNode) av = 1;
		}
		path[plen] = currNode;
		plen++;
		writeDebugStream("Visiting: %d\n",currNode);
		if (!av) {
			visited[visitCount] = currNode;
			visitCount++;
			if (currNode == goalmin) {
				succ = 1;
				break;
			}
			for (int i = 0; i < 5; i++) {
				if (getNeighbors(currNode,i) != -1) {
					stack[stackCount] = getNeighbors(currNode,i);
					stackCount++;
				}
			}
			} else {
			plen--;
			writeDebugStream("already visited node %d.\n",path[plen]);
			/*
			int remove = plen - 1;
			while (path[remove] != currNode && remove > 0) {
				remove--;
				writeDebugStream("Removing: %d\n",path[remove]);
			}
			if (remove > 0)
				plen = remove + 1;
		*/

		}
	}
	writeDebugStream("start -> %d", path[0]);
	for (int i = 1; i < plen; i++) {
		writeDebugStream(" -> %d",path[i]);
	}
	writeDebugStream(" -> goal\n");

}
