/*! \file       main.cpp
 *  \author     Sergey Shershakov
 *  \version    0.1
 *  \date       11.02.2020
 *
 *  Demonstrates copy elision problem.
 *
 *  Instructions: try to build this app with -fno-elide-constructors and w/o it.
 *  Study the difference in behaviour in both cases.
 */

#include <iostream>
//#include <stdexcept>
//#include <cassert>


/***************************************************************************//**
 *  Represents a complex big objects with some custom copy logic
 ******************************************************************************/
class VeryComplexType {
public:
    VeryComplexType()
    {
        ++_counter;
        std::cout << "Constructor called: " << _counter << '\n';
    }

    VeryComplexType(const VeryComplexType& oth)
    {
        ++_counter;
        std::cout << "Copy constructor called: " << _counter << '\n';
    }
public:
    static size_t getCounter() { return _counter; }

private:
    static size_t _counter;                 ///< Conts a number of instances.
}; // class VeryComplexType


// initialize a static field: must be performed out of the defining class
// static variables are just nothing else as global variables with narrowed scope!
size_t VeryComplexType::_counter = 0;





// static field
void demo1()
{
    size_t initCtr = VeryComplexType::getCounter();
}



// creates a number of objects
void demo2()
{
    size_t ctr = VeryComplexType::getCounter();

    VeryComplexType o1;
    ctr = VeryComplexType::getCounter();

    VeryComplexType o2, o3;
    ctr = VeryComplexType::getCounter();
}


VeryComplexType demo3Foo()
{
    VeryComplexType o;
    return o;
}



// calls a function with return by value
void demo3()
{
    size_t ctr = VeryComplexType::getCounter();

    VeryComplexType o = demo3Foo();
    ctr = VeryComplexType::getCounter();
}

void demo4Bar(VeryComplexType param)
{
    param;
}

void demo4()
{
    size_t ctr = VeryComplexType::getCounter();

    VeryComplexType o;
    demo4Bar(o);
    ctr = VeryComplexType::getCounter();
}


void demo5()
{
    size_t ctr = VeryComplexType::getCounter();

    VeryComplexType o = VeryComplexType();  // explicitly call def. constructor
    ctr = VeryComplexType::getCounter();
}


int main()
{
//    demo1();
//    demo2();
    //demo3();
    //demo4();
    demo5();

    return 0;
}
