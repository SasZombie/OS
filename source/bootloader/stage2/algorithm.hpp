#pragma once

template <typename T>
T min(T a, T b)
{
    if(a < b)
        return a;
    return b;
}

template <typename T>
T max(T a, T b)
{
    if(a > b)
        return a;
    return b;
}

template <typename T>
int round(T num)
{
    //Stiu ca este de forma ab.cdefg...
    //Ma intereseaza C

    unsigned maxIter = 10;
    T multiplied = num * 10;
    while (multiplied % 10 == 0 && maxIter)
    {
        multiplied = multiplied * 10;
        --maxIter;
    }

    T lastDigit = multiplied % 10;
    
    if(lastDigit > 5)
    {
        return ((int) num) + 1;
    }

    return (int)num;
}

template <typename T>
void fill(T *arr, unsigned int size, T element)
{
    for(unsigned int i = 0; i < size; ++i)
    {
        arr[i] = element;
    }
}