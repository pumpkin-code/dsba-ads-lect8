/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.1
 *  \date       11.02.2020
 *
 *  lvalues and rvalues
 */

#include <iostream>
//#include <stdexcept>
//#include <cassert>



void demo1()
{
    int x = 42;         // x is lvalue, 42 is rvalue
    int* p = &x;

    int z;              // z is lvalue
    //42 = z;           // error
}


int demo2set()
{
    return 42;
}

void demo2()
{
    //demo2set() = 43;    // error
}


int globVar = 42;

int& demo3get()
{
    return globVar;
}

void demo3()
{
    demo3get() = 43;
    std::cout << globVar << '\n';   // 43 surprisingly
}


void demo4()
{
    int x = 10;
    int y = 20;
    int z = x + y;
}


void demo5bar(const int& t)
{
    std::cout << t;
}

void demo5foo(int& t)
{
    std::cout << t;
}

void demo5()
{
    int x = 42;
    int& y = x;                 // reference
    ++y;                        // increments x actually

    //int& z = 42;                // is it possible?
    //demo5foo(42);               // and this?

    const int& cz = 42;         // const ref, compiler prepares a backing field
    demo5bar(42);
}


int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();

    return 0;
}
