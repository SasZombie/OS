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

// #define min(a,b)    ((a) < (b) ? (a) : (b))
// #define max(a,b)    ((a) > (b) ? (a) : (b))