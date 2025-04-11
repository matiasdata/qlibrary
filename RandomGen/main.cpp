#include <RandomGen.h>
#include <iostream>

int main()
{
    MLCG gen;
    for(int i = 0; i < 10; i++)
    {
        std::cout << gen.getInteger() << std::endl;
    }
    return 0;
}