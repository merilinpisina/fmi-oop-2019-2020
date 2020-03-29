#include "MathVector.h"
#include <cmath>

MathVector::MathVector(): size(0), data(nullptr) {}

MathVector::MathVector(int v_size) : size(v_size), data(nullptr) {
	data = new (std::nothrow) double[v_size];
	if (!data) {
		std::cout << "Error! No memory allocated." << std::endl;
		return;
	}

	for (int i = 0; i < size; ++i) {
		data[i] = 0;
	}

}

const double MathVector::operator[](int index) const
{
	if (index >= 0 && index < size) {
		return data[index];
	}
	return 0.0;
}

double MathVector::operator[](int index)
{
	if (index >= 0 && index < size) {
		return data[index];
	}
	return 0.0;
}

MathVector& MathVector::operator+=(const MathVector &other)
{
	if (this->size < other.size) {
		resize(other.size);
	}

	for (int i = 0; i < this->size; ++i) {
		this->data[i] += other.data[i];
	}

	return *this;
}

MathVector MathVector::operator+(const MathVector &other)const
{
	MathVector sum(*this);
	sum += other;

	return sum;
}

MathVector& MathVector::operator-=(const MathVector &other)
{
	if (this->size < other.size) {
		resize(other.size);
	}

	for (int i = 0; i < this->size; ++i) {
		this->data[i] -= other.data[i];
	}

	return *this;
}

MathVector MathVector::operator-(const MathVector &other)const
{
	MathVector diff(*this);
	diff -= other;

	return diff;
}

MathVector& MathVector::operator*=(const double scalar) {

	for (int i = 0; i < size; ++i) {
		data[i] *= scalar;
	}
	return *this;
}

MathVector MathVector::operator*(const double scalar)const
{
	MathVector scal(*this);
	scal *= scalar;

	return scal;
}

MathVector& MathVector::operator/=(const double scalar) {

	for (int i = 0; i < size; ++i) {
		data[i] /= scalar;
	}
	return *this;
}

MathVector MathVector::operator/(const double scalar)const
{
	MathVector scal(*this);
	scal /= scalar;

	return scal;
}

double MathVector::operator%(const MathVector &other) const
{
	int shorter = (this->size < other.size) ? this->size : other.size;

	double product = 0.0;

	for (int i = 0; i < shorter; ++i) {
		product += data[i] * other.data[i];
	}

	return product;
}

double MathVector::operator~() const
{
	return sqrt(operator%(*this));

	// calling:
	// sqrt(this->operator%(*this))
	// or
	// sqrt((*this).operator%(*this))
}

bool MathVector::operator||(const MathVector &other) const
{
	if (this->size != other.size) {
		return false;
	}

	double coeff = data[0] / other.data[0];
	const double eps = 0.00001;

	for (int i = 1; i < size; ++i) {
		double currentCoeff = data[i] / other.data[i];
		if (abs(coeff - currentCoeff) > eps) {
			return false;
		}
	}

	return true;
}

bool MathVector::operator|=(const MathVector &other) const
{
	return (operator%(other) == 0);
}

void MathVector::print() const
{
	std::cout << "(";
	for (int i = 0; i < size - 1; ++i) {
		std::cout << data[i] << ", ";
	}
	std::cout << data[size - 1] << ")\n";
}

std::ostream & operator<<(std::ostream &os, const MathVector& vect)
{
	os << "(";
	for (int i = 0; i < vect.size - 1; ++i) {
		os << vect.data[i] << ", ";
	}
	os << vect.data[vect.size - 1] << ")\n";
	return os;
}

std::istream & operator>>(std::istream &is, MathVector& vect)
{
	std::cout << "Enter " << vect.size << " values: \n";

	for (int i = 0; i < vect.size; ++i) {
		is >> vect.data[i];
	}

	std::cout << "Result: \n";
	std::cout << vect;

	return is;
}

MathVector::MathVector(const MathVector &other) {
	copy(other);
}

MathVector& MathVector::operator=(const MathVector &other) {
	if (this != &other) {
		destroy();
		copy(other);
	}

	return *this;
}

MathVector::~MathVector()
{
	destroy();
}

void MathVector::copy(const MathVector &other)
{
	this->size = other.size;
	this->data = new (std::nothrow) double[other.size];
	if (!this->data) {
		std::cout << "Error! No memory allocated." << std::endl;
		return;
	}

	memcpy(this->data, other.data, sizeof(double) * other.size);
}

void MathVector::destroy() {

	if (!data){
		return;
	}

	delete[]data;
	size = 0;
	data = nullptr;
}

void MathVector::resize(int newSize)
{
	if (newSize < 0) {
		return;
	}

	if (data == nullptr) {
		data = new (std::nothrow) double[newSize];
		if (!data) {
			std::cout << "Error! No memory allocated." << std::endl;
			return;
		}
		size = newSize;

		memset(data, 0, sizeof(double) * newSize);
	}

	else {

		double* temp = new (std::nothrow) double[newSize];
		if (!temp) {
			std::cout << "Error! No memory allocated." << std::endl;
			return;
		}

		memcpy(temp, data, sizeof(double)* newSize);

		delete[]data;
		data = temp;

		for (int i = size; i < newSize; ++i) {
			data[i] = 0;
		}

		size = newSize;
	}


}

