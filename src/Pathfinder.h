#pragma once
#include <list>
#include <vector>
#include "Util.h"
#include "Node.h"

class Pathfinder
{
public:
	Pathfinder();
	~Pathfinder();

	int FindPath(const int nStartX, const int nStartY,
		const int nTargetX, const int nTargetY,
		const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
		int* pOutBuffer, const int nOutBufferSize);

	Node* FindNodeOnList(std::list<Node*>& nodeList, Util::Point point);

	unsigned int CalcTotalCost(int g);

	unsigned int ManhattanDistance(Util::Point src, Util::Point target);

	Util::Point CalcDelta(Util::Point src, Util::Point target);

	unsigned int OutputPath(int* pOutBuffer, Node* curNode, const unsigned char* pMap, const int nMapWidth, const int nOutBufferSize);
};

