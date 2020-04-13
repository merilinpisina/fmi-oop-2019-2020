#include<iostream>
#include "Vector.h"
#include <vector>

// Examples for operator()

// Similar to void PrintHello() { std::cout << "Hello, World!" << std::endl; }
struct PrintHello
{
	void operator()() const
	{
		std::cout << "Hello, World!" << std::endl;
	}
};

// These functions can also return things
struct Return0
{
public:
	int operator()() const
	{
		return 0;
	}
};

// They can take arguments, too
struct AddNumbers
{
	int operator()(int a, int b) const
	{
		return a + b;
	}
};

template <typename T>
struct AddTNumbers
{
	T operator()(T a, T b) const
	{
		return a + b;
	}
};

// They can have state
struct AddX
{
	int x;
	int operator()(int a) const
	{
		return a + x;
	}
};

// They can be overloaded
struct Overloaded
{
	void operator()(int a) const
	{
		std::cout << "Integer: " << a << std::endl;
	}

	void operator()(const char* a) const
	{
		if (a)
		{
			std::cout << "CString: " << a << std::endl;
		}
		else
		{
			std::cout << "nullptr" << std::endl;
		}
	}
};

using f = int(*) (int);

vector<int> * map (int (*fxn) (int), vector<int> * vec) {
	for (auto v : *vec) {
		v = fxn(v);
	}
	return vec;
}

vector<int> * filter(bool(*fxn) (int), vector<int> * vec) {
	vector<int> newVec;
	for (auto v : *vec) {
		if (fxn(v)) {
			newVec.push_back(v);
		}
	}
	return &newVec;
}

// int reduce(int(*fxn) (int, int), vector<int> * vec);

// int square(int); // For use with map
// bool isEven(int); // For use with filter
// int product(int, int); // For use with reduce

int main()
{
	//PrintHello{}();
	//std::cout << Return0{}() << std::endl;
	//std::cout << AddNumbers{}(10, 20) << std::endl;
	//std::cout << AddX{ 21 }(30) << std::endl;
	//Overloaded{}(10);
	//Overloaded{}("Kappa123");

	// More on how this can be useful after we learn about templates

	// Squaring a vector of integers in place:
	vector<int> v{ 1, 2, 3, 4 };
	v.print();	
	auto unary_op = [](int num) {return std::pow(num, 2); };
	std::transform(v.begin(), v.end(), v.begin(), unary_op);
	v.print();

	//Filtering odd numbers only from a vector of integers :
	std::vector<int> nums{ 1, 2, 3, 4 };
	std::vector<int> odd_nums;
	auto pred = [](int num) {return num & 1; };
	std::copy_if(nums.begin(), nums.end(), std::back_inserter(odd_nums), pred);


	system("pause");
	return 0;
}