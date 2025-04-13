#include <RandomGen.h>
#include <iostream>

int main()
{
    MLCG gen;
    for(int i = 0; i < 10; i++)
    {
        std::cout << gen.getInteger() << std::endl;
    }
    int dim = 2;
    RandomMLCG rg(dim);
    MyArray arr(dim);
    std::cout << "Generating 10 2-dimensional multivariate gaussians: " << std::endl;
    for(int i = 0; i < 10; i++)
    {
        rg.getGaussians(arr);
        std::cout << "(" << arr[0] << ", " << arr[1] << ")" << std::endl;
    }
    return 0;
}