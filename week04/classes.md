# Classes & Objects in C++

## Classes

A class in C++ is the building block, that leads to Object-Oriented programming. It is a user-defined data type, which holds its own **data members** and **member functions**, which can be accessed and used by creating an instance of that class. *A C++ class is like a blueprint for an object.*

>**For Example:** Consider the Class of Cars. There may be many cars with different names and brand but all of them will share some common properties like all of them will have 4 wheels, Speed Limit, Mileage range etc. So here, Car is the class and wheels, speed limits, mileage are their properties.

* Data members are the data variables and member functions are the functions used to manipulate these variables and together these data members and member functions define the properties and behavior of the objects in a Class.

>In the above example of class Car, the data member will be speed limit, mileage etc and member functions can be apply brakes, increase speed etc.

## Objects

An Object is an instance of a Class. When a class is defined, no memory is allocated but when it is instantiated (i.e. an object is created) memory is allocated.

## Defining a Class and Declaring Objects

A class is defined in C++ using keyword *class* followed by the name of class. The body of class is defined inside the curly brackets and terminated by a semicolon at the end.

```
class <class_name> 
{
<access_specifier>: // private, public or protected
    <data_member_type> <data_member_name>; // variables or constants
    ...
    <member_function_declaration> // or definition in case the function is inline
    ...
}; // essential semicolon at the end of the declaration
```

### C++ Naming Conventions 

Names are the key to program readability. If the name is appropriate everything fits together naturally, relationships are clear, meaning is derivable, and reasoning from common human expectations works as expected. Good names save time when debugging and save time when extending.
If you find all your names could be Thing and DoIt then you should probably revisit your design. Avoid the temptation to have short names everywhere, and avoid non-standard abbreviations. **Source code is meant to be read by humans.** This is the most important thing to remember. As well as communicating your intent to the machine, you must make it clear what that intent is to those who will read the source code. This includes you! Code you’ve written more than about 3 weeks ago may as well have been written by somebody else.

[Here](file:///home/merilin/Downloads/codingStandards.pdf, "C++ Naming Conventions") is some helpful information about the topic.

### Access Modifiers in C++

Access modifiers are used to implement an important feature of Object-Oriented Programming known as *Data Hiding*.

There are 3 types of access modifiers available in C++:

* **Public**: All the class members declared under public will be available to everyone. The data members and member functions declared public can be accessed by other classes too. The public members of a class can be accessed from anywhere in the program using the direct member access operator (.) with the object of that class.

*Example:*
```
// C++ program to demonstrate public 
// access modifier 
  
#include<iostream> 
using namespace std; 
  
// class definition 
class Circle 
{ 
    public:  
        double radius; 
          
        double  compute_area() 
        { 
            return 3.14*radius*radius; 
        } 
      
}; 
  
// main function 
int main() 
{ 
    Circle obj; 
      
    // accessing public data member outside the class 
    obj.radius = 5.5; 
      
    cout << "Radius is: " << obj.radius << "\n"; 
    cout << "Area is: " << obj.compute_area(); 
    return 0; 
} 
```

*Output:*

```
Radius is: 5.5
Area is: 94.985
```
>In the above program the data member radius is **public** so we are allowed to access it outside the class.

* **Private**:  The class members declared as private can be accessed only by the functions inside the class. They are not allowed to be accessed directly by any object or function outside the class. Only the member functions or the friend functions are allowed to access the private data members of a class.

*Example:*
```
// C++ program to demonstrate private 
// access modifier 
  
#include<iostream> 
using namespace std; 
  
class Circle 
{    
    // private data member 
    private:  
        double radius; 
       
    // public member function     
    public:     
        double  compute_area() 
        {   // member function can access private  
            // data member radius 
            return 3.14*radius*radius; 
        } 
      
}; 
  
// main function 
int main() 
{    
    // creating object of the class 
    Circle obj; 
      
    // trying to access private data member 
    // directly outside the class 
    obj.radius = 1.5; 
      
    cout << "Area is:" << obj.compute_area(); 
    return 0; 
} 
```

>The output of above program will be a compile time error because we are not allowed to access the private data members of a class directly outside the class.

*Output:*
```
 In function 'int main()':
11:16: error: 'double Circle::radius' is private
         double radius;
                ^
31:9: error: within this context
     obj.radius = 1.5;
         ^
```
>However, we can access the private data members of a class indirectly using the public member functions of the class. Below program explains how to do this:

```
// C++ program to demonstrate private 
// access modifier 
  
#include<iostream> 
using namespace std; 
  
class Circle 
{    
    // private data member 
    private:  
        double radius; 
       
    // public member function     
    public:     
        void compute_area(double r) 
        {   // member function can access private  
            // data member radius 
            radius = r; 
              
            double area = 3.14*radius*radius; 
              
            cout << "Radius is: " << radius << endl; 
            cout << "Area is: " << area; 
        } 
      
}; 
  
// main function 
int main() 
{    
    // creating an object of the class 
    Circle obj; 
      
    // trying to access a private data member 
    // directly outside of the class 
    obj.compute_area(1.5); 
      
      
    return 0; 
} 
```

*Output:*
```
Radius is: 1.5
Area is: 7.065
```

* **Protected**: Protected access modifier is similar to that of private access modifiers, the difference is that the class member declared as Protected are inaccessible outside the class but they can be accessed by any subclass(derived class) of that class.

>**Note:** If we do not specify any access modifiers for the members inside the class then by default the access modifier for the members will be **Private**.

### Member Functions in Classes

There are 2 ways to define a member function:

* Inside class definition
* Outside class definition

To define a member function outside the class definition we have to use the scope resolution :: operator along with class name and function name.
```
// C++ program to demonstrate function  
// declaration outside class 
  
#include <iostream> 

class FMIstudent 
{ 
    public: 
    std::string name; 
    int fn; 
      
    // printName is not defined inside class definition 
    void printName()const; 
      
    // printFN is defined inside class definition 
    void printFN()const 
    { 
        std::cout << "Student FN is: " << fn << std::endl;
    } 
}; 
  
// Definition of printName using scope resolution operator :: 
void FMIstudent::printName() 
{ 
    std::cout << "Student name is: " << name << std::endl;
} 

int main() { 
      
    FMIstudent student1; 
    student1.name = "Pesho"; 
    student1.fn = 88888; 
      
    // call printName() 
    student1.printName(); 
      
    // call printFN() 
    student1.printFN(); 

    return 0; 
} 
```

*Output:*
```
Student name is: Pesho
Student FN is: 88888
```
>Note that all the member functions defined inside the class definition are by default **inline**, but you can also make any non-class function inline by using keyword inline with them. Inline functions are actual functions, which are copied everywhere during compilation, like pre-processor macro, so the overhead of function calling is reduced.

>*Note:* Declaring a **friend** function is a way to give private access to a non-member function.


### Declaring Objects

When a class is defined, only the specification for the object is defined; no memory or storage is allocated. To use the data and access functions defined in the class, you need to create objects.
```
ClassName ObjectName;
```
