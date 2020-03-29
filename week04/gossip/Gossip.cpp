#include "Gossip.h"



Gossip::Gossip()
{
	std::cout << "Default constructor...\n";
}

Gossip::Gossip(const Gossip& other)
{
	std::cout << "Copy constructor...\n";
}

Gossip & Gossip::operator=(const Gossip &)
{
	std::cout << "Assignment operator...\n";
	return *this;
}

Gossip::~Gossip()
{
	std::cout << "Destructor...\n";
}
