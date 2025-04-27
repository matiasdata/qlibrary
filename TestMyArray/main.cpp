// TestMyArray/main.cpp
#include <QLibrary/MyArray.h>
#include <iostream>

void PrintMyArray(const MyArray& arr)
{
    for(unsigned int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

int main()
{
    MyArray arr(10);
    arr = 1;
    PrintMyArray(arr);
    arr += 2;
    PrintMyArray(arr);
    return 0;
}

