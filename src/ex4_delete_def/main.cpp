/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.1
 *  \date       11.02.2020
 *
 *  Demonstrates  how to lock copy constructor and copy assignment operator
 *  from being used.
 */

#include <iostream>
//#include <stdexcept>
//#include <cassert>


/***************************************************************************//**
 *  Represents a custom object w/ no copy ability
 ******************************************************************************/
class NonCopyable {
public:
    NonCopyable()
    {
        std::cout << "Default constructor called\n";
    }

    NonCopyable(int a)
    {
        std::cout << "Init constructor called\n";
    }

    // the following is "modern" approach
    NonCopyable(const NonCopyable& other) = delete;
    const NonCopyable& operator = (const NonCopyable& rhv) = delete;

//// this is "classical" approach
//private:
//    NonCopyable(const NonCopyable& other);                  // CC is not available
//    const NonCopyable& operator = (const NonCopyable& rhv); // CAO is not available
};






void demo1()
{
    NonCopyable o1;         // default
    NonCopyable o2(42);     // init
    //NonCopyable o3(o2);     // not available
    //o2 = o1;                // not available
}


int main()
{
    demo1();

    return 0;
}
