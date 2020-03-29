#include "DynamicArray.h"

// #include <vector>

struct Point {
	int x, y;
};

class Animal {
public:
	Animal();
	Animal(const Animal&) = delete;
	Animal& operator=(const Animal&) = delete;
	~Animal();

	void breathe();
	void eat();
	void sleep();
	void makeSound();

protected:
	int protect;

private:
	char* name;
	int age;
};

class Cat :public Animal {

};


int main () {

	DynamicArray<Point> points(10);
	DynamicArray<int> arr(10);
	
	for (int i = 0; i < 10; i++)
		arr.push(i);

	for (int i = 0; i < 10; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;


	return 0;
}