#include <iostream>
#include <fstream>
#include <functional>

template <typename T>
void printArray(T arr[], int arrSize) {
	for (int i = 0; i < arrSize; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

template <typename T>
using fn = T(*) (T);

template <typename T>
using voidfn = void(*) (T&);

template <typename T>
T addOne(T a) {
	return ++a;
}

template <typename T>
void fillv(T& in) {
	std::cin >> in;
}

template <typename T>
void map(T arr[], int arrSize, fn<T> func) {
	for (int i = 0; i < arrSize; ++i) {
		arr[i] = func(arr[i]);
	}
}

template <typename T>
void map(T arr[], int arrSize, voidfn<T> func) {
	for (int i = 0; i < arrSize; ++i) {
		func(arr[i]);
	}
}

using predicate = int(*)(int);

template <typename T>
void map(T arr[], int arrSize, std::function<int(int)> pred) {
	for (int i = 0; i < arrSize; ++i) {
		arr[i] = pred(arr[i]);
	}
}

template <typename T>
void swap(T& element) {
	element.swap();
}


struct S {
	int a, b, c;

	S() :a(0), b(0), c(0) {}
	S(int a_, int b_, int c_) :a(a_), b(b_), c(c_){}

	friend std::istream& operator>>(std::istream& in, S& element);
	friend std::ostream& operator<<(std::ostream& out, const S& element);

	// prefix ++a
	// b = ++a
	// a = a + 1;
	// b = a;

	// a = 6
	// b = a++ -> b = 6, a = 7
	// b = ++a -> b = 7, a = 7
	S operator++() {
		++(this->a);
		return *this;
	}

	// postfix a++
	// b = a++
	// b = a;
	// a = a + 1;

	S operator++(int) {
		S tmp{ this->a, this->b, this->c };
		++(*this);
		return tmp;
	}

	void swap() {
		int t = this->a;
		this->a = this->b;
		this->b = t;
	}

};

template <typename T>
T fill(T element) {
	std::cin >> element;
	return element;
}

template <typename T>
T print(T element) {
	std::cout << element;
	return element;
}

template <typename T>
using f = [](T a) -> T {
	return a + 1;
};

// Lambda function
template <typename T>
using repeated = [&a](int k, f func) {
	if (k == 0) {
		return;
	}
	func(a);
	repeated(k-1, func);
}

int main() {


	//map<int>(arr, 6, print);

	//map<int>(arr, 6, addOne);
	//std::cout << std::endl;
	//map<int>(arr, 6, print);
	//std::cout << std::endl;

	//S A[3];
	//map<S>(A, 3, fill);
	//map<S>(A, 3, print);
	//std::cout << std::endl;

	//map<S>(A, 3, addOne);
	//map<S>(A, 3, print);
	//std::cout << std::endl;

	//map<S>(A, 3, swap);
	//map<S>(A, 3, print);
	//std::cout << std::endl;

	int a, b;
	int lambda = [=]() -> int{
		//a++;
		//b++;
		//std::cout << "Hello, I'm a lambda function! I use: " << a << ", " << b << std::endl;;
		std::cout << "Hello, I'm a lambda function!" << std::endl;
		return 0;
	}();

	std::function<int(int)> lambdaFn = [](int val)->int {return val + 1; };

	int result = lambdaFn(5);

	std::function<int(int)> sq = [](int val)->int {return val * val; };
	std::function<int(int, int)> fxsq = [sq](int x, int y)->int {return sq(x) + sq(y) + 2 * x * y; };

	std::function<int(int)> isEven = [](int p) -> int {
		return (int)(p % 2 == 0);
	};

	int arr[] = { 1, 2, 3, 4, 5, 6 };

	map<int>(arr, 6, isEven);
	map<int>(arr, 6, print);
	std::cout << std::endl;



	system ("pause");
	return 0;
}

std::istream & operator>>(std::istream & in, S& element)
{
	std::cout << "Enter values for a, b, c: ";
	in >> element.a >> element.b >> element.c;
	return in;
}

std::ostream & operator<<(std::ostream & out, S& element)
{
	std::cout << element.a << " " << element.b << " " << element.c << std::endl;
	return out;
}
