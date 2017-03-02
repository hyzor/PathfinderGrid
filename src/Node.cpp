#include "Node.h"

Node::Node()
{
	coordinates = Util::Point(0, 0);
	traversable = true;
	parent = nullptr;
	opened = closed = false;
	g = h = f = 0;
}

Node::Node(Util::Point coords, unsigned int traversable)
	: Node()
{
	this->coordinates = coords;
	this->traversable = (traversable != 0);
}

Node::~Node()
{
}
