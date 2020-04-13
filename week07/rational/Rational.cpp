#include "Rational.h"

using fn = void(*) ();

Rational::operator bool() const
{
	return (nom >= 0 && denom >= 0) || (nom < 0 && denom < 0);
}

Rational::operator double() const
{
	if (denom == 0) {
		return 0;
	}

	return static_cast<double>(nom) / denom;
}

Rational & Rational::operator+=(const Rational &other)
{
	this->nom = this->nom * other.denom + this->denom * other.nom;
	this->denom = this->denom * other.denom;
	return *this;
}

Rational & Rational::operator+=(int number)
{
	this->nom = this->nom + this->denom * number;
	return *this;
}

bool Rational::operator==(const Rational &other) const
{
	return (this->nom * other.denom == this->denom * other.nom);
}

bool Rational::operator!=(const Rational &other) const
{
	return !(*this == other);
}

bool Rational::operator>(const Rational &other) const
{
	if (this->denom == other.denom) {
		return this->nom > other.nom;
	}
	return (this->nom * other.denom > this->denom * other.nom);
}

bool Rational::operator<(const Rational &other) const
{
	if (this->denom == other.denom) {
		return this->nom < other.nom;
	}
	return (this->nom * other.denom < this->denom * other.nom);
}

Rational & Rational::operator++()
{
	return *this += 1;
}

Rational Rational::operator++(int)
{
	Rational temp = *this;
	++*this;
	return temp;
}
