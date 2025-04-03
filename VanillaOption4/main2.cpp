#include <iostream>
#include <SharedPtr.h>
int main()
{
    // Shared Pointer tests.
    double x = 5;
    SharedPtr<double> sharedPtr1(x);
    SharedPtr<double> sharedPtr2(sharedPtr1); // Copy constructor
    SharedPtr<double> sharedPtr3; // Default constructor
    sharedPtr3 = sharedPtr1; // Assignment operator
    std::cout << "Shared Pointer 1 address: " << &sharedPtr1 << std::endl;
    std::cout << "Shared Pointer 2 address: " << &sharedPtr2 << std::endl;
    std::cout << "Shared Pointer 3 address: " << &sharedPtr3 << std::endl;
    std::cout << "Shared Pointer 1 val: " << *sharedPtr1 << std::endl;
    std::cout << "Shared Pointer 2 val: " << *sharedPtr2 << std::endl;
    std::cout << "Shared Pointer 3 val: " << *sharedPtr3 << std::endl;
    std::cout << "Shared Pointer 1 inner pointer address: " << &(*sharedPtr1) << std::endl;
    std::cout << "Shared Pointer 2 inner pointer address: " << &(*sharedPtr2) << std::endl;
    std::cout << "Shared Pointer 3 inner pointer address: " << &(*sharedPtr3) << std::endl;
    *sharedPtr1 = 10; // Change the value of sharedPtr1
    std::cout << "Changing value to 10." << std::endl;
    std::cout << "Shared Pointer 1 val: " << *sharedPtr1 << std::endl;
    std::cout << "Shared Pointer 2 val: " << *sharedPtr2 << std::endl;
    std::cout << "Shared Pointer 3 val: " << *sharedPtr3 << std::endl;
    std::cout << "Shared Pointer 1 reference count: " << sharedPtr1.getRefCount() << std::endl;
    std::cout << "Shared Pointer 2 reference count: " << sharedPtr2.getRefCount() << std::endl;
    std::cout << "Shared Pointer 3 reference count: " << sharedPtr3.getRefCount() << std::endl;
    sharedPtr1 = SharedPtr<double>(new double(0)); // now sharedPtr1 points to a different place, others are unchanged.
    std::cout << "Changing sharedPtr1 to point to a new address" << std::endl;
    std::cout << "Shared Pointer 1 reference count: " << sharedPtr1.getRefCount() << std::endl;
    std::cout << "Shared Pointer 2 reference count: " << sharedPtr2.getRefCount() << std::endl;
    std::cout << "Shared Pointer 3 reference count: " << sharedPtr3.getRefCount() << std::endl;

    return 0;
}