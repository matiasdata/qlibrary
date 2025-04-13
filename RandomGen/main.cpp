// main.cpp 
#include <RandomGen.h>
#include <iostream>
#include <fstream>

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

    dim = 1;
    RandomMLCG rg2(dim);
    MyArray arr2(dim);

    std::ofstream file("samples.csv");
    int n_samples = 10000;

    for (int i = 0; i < n_samples; ++i) {
        rg2.getGaussians(arr2);
        file << arr2[0] << "\n";
    }

    file.close();
    std::cout << "Generated " << n_samples << " Gaussian samples to samples.csv\n";
    return 0;
}