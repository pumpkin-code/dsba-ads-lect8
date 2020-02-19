/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.1
 *  \date       11.02.2020
 *
 *  rvalues references and move semantics
 */

#include <iostream>
#include <string>
//#include <stdexcept>
//#include <cassert>

#include "safe_array.hpp"


std::string demo6str()
{
    return std::string("Hello World!");
}

void demo6()
{
    int x = 42;
    int y = x + 100;

    std::string s1 = "Hello ";
    std::string s2 = "world!";
    std::string hw = s1 + s2;

    std::string hw2 = demo6str();
}


void demo7()
{
    std::string s1 = "Hello ";
    std::string s2 = "world!";

    std::string&& rref = s1 + s2;       // the result of s1 + s2 is an rvalue

    rref += " (RREF version)";          // now can change the temporary string

    std::cout << rref << '\n';          // "Hello world! (RREF version)"
}


typedef SafeArray<int> IntSafeArray;

IntSafeArray demo8getArray()
{
    IntSafeArray arr = {1, 2, 3};
    return arr;
}

// repetitive copying when there is no move constructors
// watch the difference with enablem move constructor
void demo8()
{
    IntSafeArray arr1 = demo8getArray();
    IntSafeArray arr2 = {10, 20};
    arr2 = demo8getArray();
}


// moving lvalue
void demo9()
{
    IntSafeArray a1 {1, 2, 3};
    IntSafeArray a2(a1);
    IntSafeArray a3(std::move(a1));
}


int main()
{
    demo6();
    demo7();
    //demo8();
    demo9();

    return 0;
}
