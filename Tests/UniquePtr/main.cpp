// TestUniquePtr/main.cpp
#include <QLibrary/UniquePtr.h>
#include <iostream>

using namespace QLibrary;

int main()
{
    int x = 5;
    UniquePtr<int> uniquePtr1(x);
    std::cout << "uniquePtr1 value: " << *uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 address: " << &uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 inner pointer address: " << &*uniquePtr1 << std::endl;
    (*uniquePtr1)++;
    std::cout << "uniquePtr1 value: " << *uniquePtr1 << std::endl;
    UniquePtr<int> uniquePtr2(new int(2));
    std::cout << "uniquePtr2 value: " << *uniquePtr2 << std::endl;
    std::cout << "uniquePtr2 address: " << &uniquePtr2 << std::endl;
    std::cout << "uniquePtr2 inner pointer address: " << &*uniquePtr2 << std::endl;
    // move assignment
    uniquePtr1 = std::move(uniquePtr2); 
    // uniquePtr1 = uniquePtr2 is not allowed.
    std::cout << "uniquePtr1 value: " << *uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 address: " << &uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 inner pointer address: " << &*uniquePtr1 << std::endl;
    // If the right-hand side is a temporary (an rvalue) = it is allowed.
    uniquePtr1 = UniquePtr<int>(new int(3));
    std::cout << "uniquePtr1 value: " << *uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 address: " << &uniquePtr1 << std::endl;
    std::cout << "uniquePtr1 inner pointer address: " << &*uniquePtr1 << std::endl;

    return 0;
}