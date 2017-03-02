#include "Pathfinder.h"

Pathfinder::Pathfinder()
{
}

Pathfinder::~Pathfinder()
{
}

int Pathfinder::FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight, int* pOutBuffer, const int nOutBufferSize)
{
	// Wrap start and target positions into nodes
	Node* startNode = new Node(Util::Point(nStartX, nStartY), pMap[Util::CoordinatesToIndex(nStartX, nStartY, nMapWidth)]);
	Node* targetNode = new Node(Util::Point(nTargetX, nTargetY), pMap[Util::CoordinatesToIndex(nTargetX, nTargetY, nMapWidth)]);

	const int numDirections = 4;

	Util::Point directions[numDirections] = {
		Util::Point(-1, 0),
		Util::Point(1, 0),
		Util::Point(0, 1),
		Util::Point(0, -1) };

	// Keep track of current node and child
	Node* curNode;
	//Node* curChild;

	// Keep track of open and closed nodes
	std::list<Node*> openList;
	std::list<Node*> closedList;
	std::list<Node*>::iterator it;

	openList.push_back(startNode);
	startNode->Open();

	bool targetReached = false;

	while (!openList.empty())
	{
		curNode = *openList.begin();

		// Find lowest F score of all open nodes
		for (it = openList.begin(); it != openList.end(); ++it)
		{
			// Does this node have a lower F score than the current one?
			if ((*it)->GetFScore() <= curNode->GetFScore())
			{
				curNode = *it;
			}
		}

		// Have we reached the target?
		if (curNode->GetCoordinates() == targetNode->GetCoordinates())
		{
			targetReached = true;
			break;
		}

		// Close this node and push it to the closed list
		openList.remove(curNode);
		closedList.push_back(curNode);
		curNode->Close();

		unsigned int totalCost = CalcTotalCost(curNode->GetGScore());

		// Get neighboring nodes (4 assumed--diagonal excluded)
		for (unsigned int i = 0; i < numDirections; ++i)
		{
			// Get new point
			Util::Point point = curNode->GetCoordinates() + directions[i];

			// Is this point out of bounds?
			if (point.x < 0 || point.x >= nMapWidth)
				continue;

			if (point.y < 0 || point.y >= nMapHeight)
				continue;

			// Is this point not traversable?
			if (pMap[Util::PointToIndex(point, nMapWidth)] == 0)
				continue;

			// Is this point already in the closed list?
			if (FindNodeOnList(closedList, point))
				continue;

			Node* child = FindNodeOnList(openList, point);

			// Node was not found in the open list--add it
			if (child == nullptr)
			{
				child = new Node(point, pMap[Util::PointToIndex(point, nMapWidth)]);

				child->SetParent(curNode);

				// Set G score
				child->SetGScore(totalCost);

				// Calculate heuristic score based on the Manhattan distance
				child->SetHScore(ManhattanDistance(child->GetCoordinates(), targetNode->GetCoordinates()));

				// Now push it back to the open list
				child->Open();
				openList.push_back(child);
			}

			// Node already in open list--update its parent and cost
			else if (totalCost < child->GetGScore())
			{
				child->SetParent(curNode);
				child->SetGScore(totalCost);
			}
		}
	}

	// Pathfinding is done--assume target was not reached
	int pathLength = -1;

	// If target was actually reached, we output the path and its length
	if (targetReached)
		pathLength = OutputPath(pOutBuffer, curNode, pMap, nMapWidth, nOutBufferSize);

	// Clean up
	for (it = openList.begin(); it != openList.end();)
	{
		delete *it;
		it = openList.erase(it);
	}

	for (it = closedList.begin(); it != closedList.end();)
	{
		delete *it;
		it = closedList.erase(it);
	}

	delete targetNode;

	return pathLength;
}

Node* Pathfinder::FindNodeOnList(std::list<Node*>& nodeList, Util::Point point)
{
	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		if ((*it)->GetCoordinates() == point)
			return *it;
	}

	return nullptr;
}

unsigned int Pathfinder::CalcTotalCost(int g)
{
	return g + 10;
}

unsigned int Pathfinder::ManhattanDistance(Util::Point src, Util::Point target)
{
	Util::Point delta = std::move(CalcDelta(src, target));
	return static_cast<unsigned int>(10 * (delta.x + delta.y));
}

Util::Point Pathfinder::CalcDelta(Util::Point src, Util::Point target)
{
	return Util::Point(std::abs(src.x - target.x), std::abs(src.y - target.y));
}

unsigned int Pathfinder::OutputPath(int* pOutBuffer, Node* curNode, const unsigned char* pMap, const int nMapWidth, const int nOutBufferSize)
{
	Node* node = curNode;
	std::vector<int> path;
	unsigned int numNodesAdded = 0;

	while (node != nullptr)
	{
		path.push_back(Util::PointToIndex(node->GetCoordinates(), nMapWidth));
		node = node->GetParent();
	}

	// Make sure that the path is shorter than or equal to the buffer length
	assert(path.size() <= (size_t)nOutBufferSize);

	// Output path to the buffer in reverse order (and skip starting point)
	for (unsigned int i = 0; i < path.size() - 1; ++i)
	{
		pOutBuffer[i] = path[(path.size() - 2) - i];
		numNodesAdded++;
	}

	return numNodesAdded;
}
