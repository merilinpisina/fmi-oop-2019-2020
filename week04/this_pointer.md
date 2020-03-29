# C++ this Pointer

In C++, **this** pointer is used to represent the address of an object inside a member function. For example, consider an object *obj* calling one of its member function say *method()* as *obj.method()*. Then, **this** pointer will hold the address of object *obj* inside the member function *method()*. The **this** pointer acts as an implicit argument to all the member functions.
```
class ClassName {

       private:   
         int dataMember;
 
       public:
           method(int a) {

   // this pointer stores the address of object obj and access dataMember
               this->dataMember = a;
               ... .. ...
           } 
}

int main() {

    ClassName obj;
    obj.method(5);
    ... .. ...
 }
```

## Applications of this pointer

### Return Object

One of the important applications of using **this** pointer is to return the object it points. For example, the statement
```
return *this;
```
inside a member function will return the object that calls the function.

### Method Chaining

After returning the object from a function, a very useful application would be to chain the methods for ease and a cleaner code.

For example,
```
positionObj->setX(15)->setY(15)->setZ(15);
```
Here, the methods *setX*, *setY*, *setZ* are chained to the object, *positionObj*. This is possible because each method returns *this pointer.
This is equivalent to:
```
positionObj->setX(15);
positionObj->setY(15);
positionObj->setZ(15);
```

### Distinguish Data Members

Another application of **this** pointer is distinguishing data members from local variables of member functions if they have same name. For example,

```
// C++ program using this pointer to distinguish 
// local members from parameters.

#include <iostream>

class sample
{
    
public:
    void input(int a, int b)
    {
        this->a = a + b;
        this->b = a - b;
    }

    void output()
    {
        std::cout << "a = " << a << std::endl << "b = " << b << std::endl;
    }
private:
    int a, b;
};

int main()
{
    sample x;
    x.input(5, 8);
    x.output();

    return 0;
}
```
>A class *sample* is created in the program with data members *a* and *b* and member functions *input()* and *output()*. *input()* function receives two integer parameters *a* and *b* which are of same name as data member of class *sample*. To distinguish the local variable of *input()* data member of class, **this** pointer is used. When *input()* is called, the data of object inside it is represented as *this->a* and *this->b* while the local variable of the function is represented simply as *a* and *b*.

*Output:*
```
a = 13
b = -3
```

>It should be noted that, a **friend** function and a **static** function cannot have **this** pointer. It's because a friend function is not a member function of the class. And a static function can be invoked without initialization of an object, i.e, static functions are not associated with any object.  