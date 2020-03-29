# Operator Overloading in C++

In C++, we can make operators to work for user defined classes. This means C++ has the ability to provide the operators with a special meaning for a data type, this ability is known as operator overloading.
For example, we can overload an operator ‘+’ in a class like String so that we can concatenate two strings by just using +.

*Example:*
```
#include<iostream> 
using namespace std; 
  
class Complex { 
private: 
    int real, imag; 
public: 
    Complex(int r = 0, int i =0)  {real = r;   imag = i;} 
      
    // This is automatically called when '+' is used with 
    // between two Complex objects 
    Complex operator + (Complex const &obj) { 
         Complex res; 
         res.real = real + obj.real; 
         res.imag = imag + obj.imag; 
         return res; 
    } 
    void print() { cout << real << " + i" << imag << endl; } 
}; 
  
int main() 
{ 
    Complex c1(10, 5), c2(2, 4); 
    Complex c3 = c1 + c2; // An example call to "operator+" 
    c3.print(); 
} 
```

*Output:*
```
12 + i9
```

## Can we overload all operators?

Almost all operators can be overloaded except few. Following is the list of operators that cannot be overloaded.
```
   . (dot) 
   :: 
   ?: 
   sizeof 
```

### Why can’t . (dot), ::, ?: and sizeof be overloaded?

See [this](http://www.stroustrup.com/bs_faq2.html#overload-dot) for answers from Stroustrup himself.

## Operator Overloading Examples

* [**Unary Operators Overloading**](https://www.tutorialspoint.com/cplusplus/unary_operators_overloading.htm)

* [**Binary Operators Overloading**](https://www.tutorialspoint.com/cplusplus/binary_operators_overloading.htm)

* [**Relational Operators Overloading**](https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm)

* [**Input/Output Operators Overloading**](https://www.tutorialspoint.com/cplusplus/input_output_operators_overloading.htm)

* [**++ and -- Operators Overloading**](https://www.tutorialspoint.com/cplusplus/increment_decrement_operators_overloading.htm)

* [**Assignment Operators Overloading**](https://www.tutorialspoint.com/cplusplus/assignment_operators_overloading.htm)

* [**Function call () Operator Overloading**](https://www.tutorialspoint.com/cplusplus/function_call_operator_overloading.htm)

* [**Subscripting [] Operator Overloading**](https://www.tutorialspoint.com/cplusplus/subscripting_operator_overloading.htm)

* [**Class Member Access Operator -> Overloading**](https://www.tutorialspoint.com/cplusplus/class_member_access_operator_overloading.htm)

