#ifndef ONLINE_STORE_H
#define ONLINE_STORE_H

#include "Item.h"

const unsigned int START_CAPACITY = 8;

class OnlineStore {
public:
	OnlineStore() : capacity(START_CAPACITY), size(0), items(nullptr) {
		items = new (std::nothrow) Item[capacity];
		if (!items) {
			std::cout << "Error! Could not allocate memory for Item array!\n";
			return;
		}
	}

	OnlineStore(unsigned int _capacity) : capacity(_capacity), size(0), items(nullptr) {
		items = new (std::nothrow) Item[capacity];
		if (!items) {
			std::cout << "Error! Could not allocate memory for Item array!\n";
			return;
		}
	}
	
	OnlineStore(const OnlineStore& other) {
		copy(other);
	}

	OnlineStore& operator=(const OnlineStore& other) {
		if (this != &other) {
			destroy();
			copy(other);
		}
		return *this;
	}

	~OnlineStore() {
		destroy();
	}

	void add(const Item& newItem) {
		if (size >= capacity) {
			resize();
		}
		items[size++] = newItem;
	}

	friend std::ostream& operator<<(std::ostream&, const OnlineStore&);

private:
	Item* items;
	unsigned int size;
	unsigned int capacity;

	void copy(const OnlineStore& other) {
		size = other.size;
		capacity = other.capacity;
		items = new (std::nothrow) Item[capacity];
		if(!items){
			std::cout << "Error! Could not allocate memory for Item array!\n";
			return;
		}
		for (int i = 0; i < size; ++i) {
			items[i] = other.items[i];
		}
	}

	void resize() {
		Item* temp = items;
		capacity *= 2;
		items = new (std::nothrow) Item[capacity];

		for (int i = 0; i < size; ++i) {
			items[i] = temp[i];
		}

		delete[]temp;
	}
	
	void destroy() {
		if (!items) {
			return;
		}
		delete[] items;

		size = 0;
		capacity = 0;
		items = nullptr;
	}

};



#endif // !ONLINE_STORE_H
