#ifndef _VECTOR
#define _VECTOR

#include <iostream>
#include <cassert>
#include <algorithm>
#include <initializer_list>

template<typename T>
using predicate = bool(*) (const T&);

template<typename T>
class vector {
private:
	size_t length;
	size_t max_size;
	T* data;

	void copy(const vector<T>& other) {
		length = other.length;
		max_size = other.max_size;
		data = new (std::nothrow) T[max_size];
		for (size_t i = 0; i < length; i++) {
			data[i] = other.data[i];
		}
	}
	void destroy() {
		delete[] data;
		data = nullptr;
		length = 0;
		max_size = 0;
	}
	void resize() {
		max_size *= 2;
		T* temp = new (std::nothrow) T[max_size];
		assert(temp);
		for (size_t i = 0; i < length; i++) {
			temp[i] = data[i];
		}
		delete[]data;
		data = temp;
	}
public:
	class Iterator {
	private:
		const vector<T> *v;
		size_t i;
	public:
		using reference = T & ;
		using pointer = T * ;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		Iterator() : v(nullptr), i(0) {}
		Iterator(const vector<T>* vec, size_t index = 0) : v(vec), i(index) {}
		//		Iterator(const Iterator& other) { v = other.v; i = other.i; }
		//		Iterator& operator=(const Iterator& other) { v = other.v; i = other.i; }
		//		~Iterator() {}

		Iterator& operator++() {
			++i;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp(*this);
			++i;
			return temp;
		}
		Iterator& operator--() {
			if (i > 0) {
				--i;
			}
			return *this;
		}
		Iterator operator--(int) {
			Iterator temp(*this);
			if (i > 0) {
				--i;
			}
			return temp;
		}

		reference operator*() {
			return (*v).data[i];
		}
		const reference operator*()const {
			return (*v).data[i];
		}
		pointer operator->() {
			return &((*v).data[i]);
		}
		const pointer operator->()const {
			return &((*v).data[i]);
		}

		bool operator>(const Iterator &other)const {
			return i > other.i;
		}
		bool operator<(const Iterator &other)const {
			return i < other.i;
		}
		bool operator==(const Iterator &other)const {
			return i == other.i;
		}
		bool operator>=(const Iterator &other)const {
			return i >= other.i;
		}
		bool operator<=(const Iterator &other)const {
			return i <= other.i;
		}
		bool operator!=(const Iterator &other)const {
			return i != other.i;
		}

		Iterator operator+(int n) {
			Iterator temp(*this);
			temp += n;
			return temp;
		}
		friend Iterator operator+(int n, const Iterator &it) {
			Iterator temp;
			temp = it + n;
			return temp;
		}
		Iterator operator-(int n) {
			Iterator temp(*this);
			temp -= n;
			return temp;
		}
		difference_type operator-(const Iterator &other)const {
			return i - other.i;
		}
		Iterator& operator+=(int n) {
			i += n;
			return *this;
		}
		Iterator& operator-=(int n) {
			i -= n;
			return *this;
		}

		size_t get_position()const {
			return i;
		}
	};
	vector();
	vector(size_t);
	vector(size_t, T);
	vector(std::initializer_list<T>);
	vector(const vector<T>&);
	vector<T>& operator=(const vector<T>&);
	~vector();

	T& operator[](size_t);
	const T& operator[](size_t)const;

	T& at(size_t);
	const T& at(size_t)const;

	T& front();
	const T& front()const;

	T& back();
	const T& back()const;

	Iterator begin()const {
		return Iterator(this, 0);
	}
	Iterator end()const {
		return Iterator(this, length);
	}

	bool empty()const;
	size_t size()const;
	size_t capacity()const;
	void reserve(size_t);
	void shrink_to_fit();

	Iterator insert(const Iterator& position, T element) {
		size_t index = position.get_position();
		if (length == max_size) {
			reserve(max_size * 2);
		}
		length++;
		for (size_t i = length; i > index; i--) {
			data[i] = data[i - 1];
		}
		data[index] = element;
		return Iterator(this, index);
	}
	Iterator erase(const Iterator& position) {
		size_t index = position.get_position();
		length--;
		for (size_t i = index; i < length; i++) {
			data[i] = data[i + 1];
		}
		data[length + 1] = T();
		return Iterator(this, index);
	}

	void push_back(T);
	void pop_back();

	void swap(vector<T>&);

	void erase(T);
	void print()const;
	void erase_if(predicate<T>);

	bool operator>(const vector<T>&)const;
	bool operator<(const vector<T>&)const;
	bool operator==(const vector<T>&)const;
	bool operator>=(const vector<T>&)const;
	bool operator<=(const vector<T>&)const;
	bool operator!=(const vector<T>&)const;

private:
	int inVec(T)const;
};

template<typename T>
inline vector<T>::vector() : data(nullptr), length(0), max_size(0) {}

template<typename T>
inline vector<T>::vector(const size_t capacity) : length(0), max_size(capacity)
{
	data = new (std::nothrow) T[capacity];
	assert(data);
}

template<typename T>
inline vector<T>::vector(const size_t number, const T element) : length(number), max_size(number)
{
	data = new (std::nothrow) T[number];
	assert(data);
	for (size_t i = 0; i < number; i++) {
		data[i] = element;
	}
}

template<typename T>
inline vector<T>::vector(std::initializer_list<T> list) : length(list.size()), max_size(list.size())
{
	data = new (std::nothrow) T[max_size];
	assert(data);
	for (size_t i = 0; i < length; i++) {
		data[i] = *(list.begin() + i);
	}
}

template<typename T>
inline vector<T>::vector(const vector<T>& other)
{
	copy(other);
}

template<typename T>
inline vector<T>& vector<T>::operator=(const vector<T>& other)
{
	if (this != &other) {
		destroy();
		copy(other);
	}
	return *this;
}

template<typename T>
inline vector<T>::~vector()
{
	destroy();
}

template<typename T>
inline T & vector<T>::operator[](size_t index)
{
	if (index >= 0 && index < max_size && data) {
		return data[index];
	}
	else {
		std::cout << "Out of bounds!\n";
		exit(1);
	}
}

template<typename T>
inline const T & vector<T>::operator[](size_t index) const
{
	if (index >= 0 && index < max_size && data) {
		return data[index];
	}
	else {
		std::cout << "Out of bounds!\n";
		exit(1);
	}
}
template<typename T>
inline T & vector<T>::at(size_t index)
{
	if (index < 0 || index >= max_size) {
		std::cout << "Index out of bounds!\n";
		exit(1);
	}
	else {
		if (data) return data[index];
	}
}
template<typename T>
inline const T & vector<T>::at(size_t index) const
{
	if (index < 0 || index >= max_size) {
		std::cout << "Index out of bounds!\n";
		exit(1);
	}
	else {
		if (data) return data[index];
	}
}
template<typename T>
inline T & vector<T>::front()
{
	if (data) {
		return data[0];
	}
}
template<typename T>
inline const T & vector<T>::front() const
{
	if (data) {
		return data[0];
	}
}
template<typename T>
inline T & vector<T>::back()
{
	if (data) {
		return data[length - 1];
	}
}
template<typename T>
inline const T & vector<T>::back() const
{
	if (data) {
		return data[length - 1];
	}
}
template<typename T>
inline bool vector<T>::empty() const
{
	return (length == 0);
}
template<typename T>
inline size_t vector<T>::size() const
{
	return length;
}
template<typename T>
inline size_t vector<T>::capacity() const
{
	return max_size;
}
template<typename T>
inline void vector<T>::reserve(size_t n)
{
	if (!data && n > 0) {
		max_size = n;
		data = new (std::nothrow) T[n];
		assert(data);
		return;
	}
	if (n > max_size) {
		T* temp = new (std::nothrow) T[n];
		assert(temp);
		for (size_t i = 0; i < length; i++) {
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
		max_size = n;
	}
}
template<typename T>
inline void vector<T>::shrink_to_fit()
{
	T* temp = new (std::nothrow) T[length];
	assert(temp);
	for (size_t i = 0; i < length; i++) {
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
	max_size = length;
}

template<typename T>
inline void vector<T>::push_back(T element)
{
	if (!data) {
		reserve(8);
	}
	else {
		if (length == max_size) {
			resize();
		}
	}
	data[length++] = element;
}

template<typename T>
inline void vector<T>::pop_back()
{
	if (!empty()) {
		data[length - 1] = T();
		length--;
	}
}

template<typename T>
inline void vector<T>::swap(vector<T>& other)
{
	std::swap(length, other.length);
	std::swap(max_size, other.max_size);
	std::swap(data, other.data);
}

template<typename T>
inline void vector<T>::erase(T element)
{
	int index = inVec(element);
	size_t newSize = 0;
	if (index != -1) {
		newSize = index;
		for (size_t i = index + 1; i < length; i++) {
			if (data[i] == element) {
				continue;
			}
			data[newSize++] = data[i];
		}
		int temp = length;
		for (size_t i = 0; i < temp - newSize; i++) {
			pop_back();
		}
	}
}

template<typename T>
inline void vector<T>::print() const
{
	for (size_t i = 0; i < length; i++) {
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}

template<typename T>
inline void vector<T>::erase_if(predicate<T> pred)
{
	vector<T> newVec(length);
	for (size_t i = 0; i < length; i++) {
		if (!pred(data[i])) {
			newVec.push_back(data[i]);
		}
	}
	newVec.shrink_to_fit();
	*this = newVec;
}

template<typename T>
inline bool vector<T>::operator>(const vector<T>& other) const
{
	if (length > other.length) {
		return true;
	}
	if (length < other.length) {
		return false;
	}
	for (size_t i = 0; i < length; i++) {
		if (data[i] < other.data[i]) {
			return false;
		}
	}
	return !((*this) == other);
}

template<typename T>
inline bool vector<T>::operator<(const vector<T>& other) const
{
	if (length < other.length) {
		return true;
	}
	if (length > other.length) {
		return false;
	}
	for (size_t i = 0; i < length; i++) {
		if (data[i] > other.data[i]) {
			return false;
		}
	}
	return !((*this) == other);
}

template<typename T>
inline bool vector<T>::operator==(const vector<T>& other) const
{
	if (length != other.length) {
		return false;
	}
	for (size_t i = 0; i < length; i++) {
		if (data[i] != other.data[i]) {
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool vector<T>::operator>=(const vector<T>& other) const
{
	return ((*this) == other) || ((*this) > other);
}

template<typename T>
inline bool vector<T>::operator<=(const vector<T>& other) const
{
	return ((*this) == other) || ((*this) < other);
}

template<typename T>
inline bool vector<T>::operator!=(const vector<T>& other) const
{
	return !((*this) == other);
}

template<typename T>
inline int vector<T>::inVec(T element) const
{
	int index = -1;
	for (size_t i = 0; i < length; i++) {
		if (data[i] == element) {
			index = i;
			break;
		}
	}
	return index;
}
#endif