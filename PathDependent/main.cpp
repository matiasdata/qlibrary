// main.cpp
#include <QLibrary/SharedPtr.h>
#include <iostream>


int main()
{
    SharedPtr<double> ptr(5.0);
    std::cout << "Pointer value: " << *ptr << std::endl;
    std::cout << "Pointer value: " << ptr.operator*() << std::endl;  // value, another more convoluted way
    std::cout << "Pointing address (heap): " << &*ptr << std::endl;
    std::cout << "Pointing address (heap): " << ptr.operator->() << std::endl; // address pointed at, in the heap (as allocated via new)
    std::cout << "SharedPtr Address (stack): " << &ptr << std::endl; // in the stack
    return 0;
}