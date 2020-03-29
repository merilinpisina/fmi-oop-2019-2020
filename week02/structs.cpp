#include <iostream>
#include <string.h>
using namespace std;

struct Student{
    char* name;
    int fn;
    double grade;
};

int main(){

    int size;
    char name[32];
    Student* students; 

    cin >> size;
    if(size < 0){
        return 1;
    }
    students = new Student[size];

    for (int i = 0; i < size; ++i)
    {
       cin >> students[i].fn >> students[i].grade;
       cin >> name;
       students[i].name = new char[strlen(name)+1];
       strcpy(students[i].name, name);
    }


    delete[] students;
    return 0;
}