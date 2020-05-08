#pragma once

#include "Figure.h"

typedef Figure* FigurePtr;
// FigurePtr = Figure*
// typedef unsigned int uint;

//a polymorphic container of figures
class FigureContainer {

	FigurePtr* figures; // Figure** figures;
	size_t size;

public:

	FigureContainer();

	//no need to be copyable
	FigureContainer(const FigureContainer&) = delete; // difference between = 0 and = delete
	FigureContainer& operator=(const FigureContainer&) = delete;

	~FigureContainer();

public:

	void push_back(Figure*);
	Figure* back() const;
	Figure* getAt(size_t) const;


	size_t getSize() const {

		return size;
	}
};

