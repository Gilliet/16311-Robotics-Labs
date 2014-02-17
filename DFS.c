// Structs needed for the DFS to properly function.

typedef struct graphNode{
	float x;
	float y;
	graphNode *neighbors[5];
	//ptrs to neighbors! any node has <= 5 neighbors, including start & goal.
	//start goes in index 3 if it's there, goal goes in index 4
} node;

// Path struct. It's good stuff.
typedef struct path {
	int nElems;
	float coords[20];//[14];
} path;

// Small helper.
int alreadyVisited (node* visited, int n, node* next) {
	for(int i = 0; i < n; i++) {
		if(visited[i] == next) return 1;
	}
	return 0;
}

int DFS (path* p, node* currNode, node* endNode, node* visited, int nVisited) {
	// Mark the current node as visited.
  writeDebugStream("visiting: (%f2,%f2)\n",currNode->x,currNode->y);
	if (p == NULL) writeDebugStream("p is null?! \n");
  visited[nVisited] = *currNode;
	nVisited ++;
	// Number of elements in the path coming into this node
	int nPath = p->nElems;
	// If we're at our destination, check pointer equality, cause that's a thing
	if (currNode == endNode) {
		p->coords[2*nPath] = currNode->x;
		p->coords[2*nPath+1] = currNode->y;
		p->nElems++;
		return 1;
	} else {
		// We're not at the destination, so lets see if we are part of the path
		p->coords[2*nPath] = currNode->x;
		p->coords[2*nPath + 1] = currNode->y;
		int i = 0;
		// Check through each of our neighbors
		for (int i = 0; i < 5; i++) {
			// To make sure we don't infinitely loop, check that we haven't already
			// visited the node, especially important since the graph has undirected
		  // edges.
		writeDebugStream("nVisited: %d \n",nVisited);
			if(!alreadyVisited(visited, nVisited, currNode->neighbors[i])) {
				// Reset the location in the path after each unsuccessful branch we explore
				p->nElems = nPath + 1;
				int goodPath = DFS(p, currNode->neighbors[i], endNode, visited, nVisited);
				// We have found a good path, and that means that all of the coordinates we
				// need to go through have been added to the path in order.
				if(goodPath) return 1;
				//
				// Insert cleaning loop here if necessary to remove extra elements from
				// the path
				//
				// We didn't find the destination so we can keep looping through.
			}
		}
		// If we're here, we didn't find it by checking all of our neighbors, so we
		// signal that to the rest of the code.
		return 0;
		// Each point in the DFS keeps track of the variables that it needs for
		// successful recursive calls, so we shouldn't have to reset anything.
	}
}
