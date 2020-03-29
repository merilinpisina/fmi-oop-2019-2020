#ifndef MATH_VECT
#define MATH_VECT

#include <iostream>

class MathVector {

public:
	MathVector();
	MathVector(const MathVector&);
	MathVector& operator=(const MathVector&);
	~MathVector();

	MathVector(int);

	// operator overloading
	const double operator[](int index)const;
	double operator[](int index);

	MathVector& operator+=(const MathVector&);
	MathVector operator+(const MathVector&)const;

	MathVector& operator-=(const MathVector&);
	MathVector operator-(const MathVector&)const;

	MathVector& operator*=(const double);
	MathVector operator*(const double)const;

	MathVector& operator/=(const double);
	MathVector operator/(const double)const;

	// scalar operator
	double operator%(const MathVector&)const;

	// length
	double operator~()const;

	// ||
	bool operator||(const MathVector&)const;

	// perpendicular
	bool operator|=(const MathVector&)const;

	// print
	void print()const;

	// overloading  ostream & istream operator
	friend std::ostream& operator<<(std::ostream&, const MathVector&);
	friend std::istream& operator>>(std::istream&, MathVector&);

private:

	double* data;
	int size;

	void copy(const MathVector&);
	void destroy();
	void resize(int);

};

#endif // !MATH_VECT

