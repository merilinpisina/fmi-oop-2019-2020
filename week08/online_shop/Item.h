#ifndef _ITEM_H_
#define _ITEM_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>

class Item {
public:
	Item(): name(""), quantity(0), price(0.0) {}

	Item(std::string _name, unsigned int _quantity, double _price): name(_name), quantity(_price){}

	Item(const Item& other) {
		name = other.name;
		quantity = other.quantity;
		price = other.price;
	}

	Item& operator=(const Item& other) {
		name = other.name;
		quantity = other.quantity;
		price = other.price;
		return *this;
	}

	// ~Item();

	friend std::istream& operator >> (std::istream&, Item&);
	friend std::ostream& operator << (std::ostream&, const Item&);

private:
	std::string name;
	unsigned int quantity;
	double price;
};

#endif