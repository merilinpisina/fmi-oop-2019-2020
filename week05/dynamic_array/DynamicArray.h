#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_

#include <iostream>

template <typename T>
class DynamicArray {

public:

	// big 4
	DynamicArray();
	DynamicArray(const DynamicArray&);
	DynamicArray& operator=(const DynamicArray&);
	~DynamicArray();

	//
	DynamicArray(int);

	// operators
	const T operator[](int)const;
	T operator[](int);

	// 
	void push(T);
	T pop();
	void add(int, T);
	T remove(int);

private:
	
	T* data;
	int size;
	int capacity;

	void copy(const DynamicArray&);
	void destroy();
	void resize();
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0), data(nullptr), capacity(8) {
	data = new (std::nothrow) T[capacity];
	if (!data) {
		return;
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(int startCapacity) : size(0), data(nullptr), capacity(startCapacity) {
	data = new (std::nothrow) T[capacity];
	if (!data) {
		return;
	}
}

template <typename T>
const T DynamicArray<T>::operator[](int index) const
{
	if (index >= 0 && index < size) {
		return data[index];
	}

	return -1;
}

template <typename T>
T DynamicArray<T>::operator[](int index)
{
	if (index >= 0 && index < size) {
		return data[index];
	}

	return -1;
}

template <typename T>
void DynamicArray<T>::push(T newInt)
{
	if (size == capacity) {
		resize();
	}

	data[size++] = newInt;
}

template <typename T>
T DynamicArray<T>::pop()
{
	if (data == nullptr || size == 0) {
		return 0;
	}

	T temp = data[size - 1];
	data[size--] = 0;

	return temp;
}

template <typename T>
void DynamicArray<T>::add(int index, T element) {

	if (index >= 0 && index <= size) {
		data[index] = element;
		if (index == size) {
			size++;
		}
	}
}

template <typename T>
T DynamicArray<T>::remove(int)
{
	return 0;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &other)
{
	copy(other);
}

template <typename T>
DynamicArray<T> & DynamicArray<T>::operator=(const DynamicArray<T> &other)
{
	if (this != &other) {
		destroy();
		copy(other);
	}

	return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	destroy();
}

template <typename T>
void DynamicArray<T>::copy(const DynamicArray<T> &other)
{

	this->capacity = other.capacity;
	this->size = other.size;

	this->data = new (std::nothrow) T[capacity];
	if (!data) {
		return;
	}

	memcpy(data, other.data, other.size * sizeof(T));

	// or
	//for (int i = 0; i < size; ++i) {
	//	this->data[i] = other.data[i];
	//}
}

template <typename T>
void DynamicArray<T>::destroy()
{

	delete[] this->data;
	this->data = nullptr;
	this->size = 0;
	this->capacity = 0;
}

template <typename T>
void DynamicArray<T>::resize()
{
	this->capacity *= 2;

	T* helper = new (std::nothrow) T[this->capacity];
	if (!helper) {
		return;
	}

	for (int i = 0; i < this->size; ++i) {
		helper[i] = this->data[i];
	}

	delete[] this->data;
	this->data = helper;

	// Alternatively:
	//T *temp = data;

	//allocating new memory
	//data = new T[capacity * 2];

	//copies all old values
	//memcpy(data, temp, size * sizeof(T));

	//capacity *= 2;

	//delete[] temp;
}




#endif
