#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <algorithm>

int gcd(int a, int b) {
	while (a && b) {
		std::swap(a, b);
		b %= a;
	}

	return a ? a : b;
}


class Rational {

public:

	Rational(int _nom = 0, int _denom = 0): nom(_nom), denom(_denom) 
	{
		normalize();
	}

	operator bool() const; // +/-
	operator double() const; 
	Rational& operator+=(const Rational&);
	Rational& operator+=(int);

	bool operator==(const Rational&)const;
	bool operator!=(const Rational&)const;
	bool operator>(const Rational&)const;
	bool operator<(const Rational&)const;

	// ++a
	Rational& operator++();
	// a++
	Rational operator++(int);

private:
	int nom;
	int denom;

	void normalize() {
		if (denom == 0) {
			return;
		}
		int g = gcd(nom, denom);
		nom /= g;
		denom /= g;
	}
};

#endif // !RATIONAL_H
