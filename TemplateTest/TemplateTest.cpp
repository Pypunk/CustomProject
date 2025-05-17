// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "blob.h"
#include <vector>

template <typename T>
T Sum(T lhs, T rhs);
float Sum(float a, int b);
float Sum(int a, float b);

template <typename T>
T SumEquals(T& lhs, T& rhs);

template <typename T>
T Subtract(T lhs, T rhs);
float Subtract(float a, int b);
float Subtract(int a, float b);

template <typename T>
std::vector<T> InitializeVector(T item, int amount, int interval = 0);

int main()
{
    std::cout << "Hello World!\n";
    Sum(5, 6);
    Sum(8.5f, 6.4f);
    Sum(9, 1.5f);
    Sum(4.6f, 8);
    Sum(blob(2), blob(6));
    int value1{ 5 };
    int value2{ 6 };
    SumEquals(value1, value2);
    blob b1(6);
    blob b2(4);
    SumEquals(b1, b2);
    blob b3(8);
    b1 = b3;
    InitializeVector(0, 10);
    InitializeVector(b2, 10, 5);
}

template <typename T>
T Sum(T lhs, T rhs)
{
    return lhs + rhs;
}

template<typename T>
T SumEquals(T& lhs, T& rhs)
{
    return lhs += rhs;
}

template<typename T>
T Subtract(T lhs, T rhs)
{
    return lhs - rhs;
}

float Sum(float a, int b)
{
    return Sum(a, static_cast<float>(b));
}

float Sum(int a, float b)
{
    return Sum(static_cast<float>(a), b);
}

float Subtract(float a, int b)
{
    return Subtract(a, static_cast<float>(b));
}

float Subtract(int a, float b)
{
    return Subtract(static_cast<float>(a), b);
}

template<typename T>
std::vector<T> InitializeVector(T item, int amount, int interval)
{
    std::vector<T> temp{};
    for (int i{}; i < amount; i++)
    {
        temp.push_back(item);
        if (interval == 0)
        {
            item++;
        }
        else 
        {
            item += interval;
        }
    }
    return temp;
}
