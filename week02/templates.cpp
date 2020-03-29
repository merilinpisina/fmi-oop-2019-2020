#include <iostream>
using namespace std;

template <typename T>
bool higher(T a, T b){
    return (a>b);
}

template <typename T>
bool lower(T a, T b){
    return (a<b);
}

template <typename T>
T findMinMax(T* array, int size, bool (*comparator) (T, T)){
    T helper = array[0];
    for (int i = 1; i < size; ++i)
    {
        if(comparator<T>(helper,array[i])){
            helper = array[i];
        }
    }
    return helper;
}





int main(){



    return 0;
}
