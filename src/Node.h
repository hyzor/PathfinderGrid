#pragma once

#include "Util.h"

class Node
{
public:
	Node();
	Node(Util::Point coords, unsigned int traversable);
	~Node();

	const bool IsTraversable() { return traversable; }
	const bool IsOpened() { return opened; }
	const bool IsClosed() { return closed; }

	// Getters
	Node* GetParent() { return parent; }
	Util::Point GetCoordinates() { return coordinates; }
	const unsigned int GetGScore() { return g; }
	const unsigned int GetHScore() { return h; }
	const unsigned int GetFScore() { return g + h; }

	// Setters
	void SetParent(Node* parent) { this->parent = parent; }
	void SetCoordinates(Util::Point coords) { this->coordinates = coords; }
	void SetGScore(int gScore) { this->g = gScore; }
	void SetHScore(int hScore) { this->h = hScore; }

	void Open() { opened = true; closed = false; }
	void Close() { closed = true; opened = false; }

private:
	Util::Point coordinates;
	bool traversable;
	Node* parent;

	// A-star specific members
	bool opened;
	bool closed;
	unsigned int g, h, f;
};