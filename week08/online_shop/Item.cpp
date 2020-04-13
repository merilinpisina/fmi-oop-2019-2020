#include "Item.h"

#include <sstream>

std::istream & operator>>(std::istream &in, Item &item)
{
	in >> item.name >> item.quantity >> item.price;
	return in;
}

std::ostream & operator<<(std::ostream & out, const Item & item)
{
	out << item.name << " " << item.quantity << " " << item.price;
	return out;
}
