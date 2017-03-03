#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <list>
#include <vector>
#include <stdlib.h>
#include "Util.h"
#include "Node.h"

int FindPath(int nStartX, int nStartY, int nTargetX, int nTargetY,
	unsigned char const* pMap, int nMapWidth, int nMapHeight, int* pOutBuffer, int nOutBufferSize);

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	static Node* FindNodeOnList(std::list<Node*>& nodeList, Util::Point point);

	static unsigned int CalcTotalCost(int g);

	static unsigned int ManhattanDistance(Util::Point src, Util::Point target);

	static Util::Point CalcDelta(Util::Point src, Util::Point target);

	static int OutputPath(int* pOutBuffer, Node* curNode, Node* startNode, const unsigned char* pMap, const int nMapWidth, const int nOutBufferSize);
};

#endif