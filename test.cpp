#include <iostream>
#include <cmath>
#include <vector>

template<typename T>
void fill(T *arr, int size, T elem)
{
    for(int i = 0; i < size; ++i)
    {
        arr[i] = elem;
    }
}

void doF(int arr[10], int size, int elem)
{
    for(int i = 0; i < size; ++i)
    {
        arr[i] = elem;
    }
}

int main(int argc, char const *argv[])
{
    const int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    // doF(arr, 10, 19);
    fill(arr, 10, 20);

    for(int i = 0; i < 10; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    // fill(&arr, 10, 10);
}
