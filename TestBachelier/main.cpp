// main.cpp
#include <QLibrary/PathDependentAsian.h>
#include <QLibrary/ExoticBachelierEngine.h>
#include <QLibrary/MCStatistics.h>
#include <QLibrary/RandomGen.h>
#include <QLibrary/Wrapper.h>
#include <iostream>
//#include <chrono>

int main()
{
    double Expiry = 1.0;
    double Strike = 100.0;
    double Spot = 100.0;
    double Vol = 0.2 * Spot; // volatility of the forward will be constant 20
    double r = 0.05;
    double d = 0.02; // dividend rate
    unsigned long NumberOfPaths = 1000000;
    unsigned long NumberOfDates = 12;
    QLibrary::PayoffCall ThePayoff(Strike);
    QLibrary::MyArray Times(NumberOfDates);
    for(unsigned long i = 0; i < NumberOfDates; i++)
    {
        Times[i] = (i+1.0)*Expiry/NumberOfDates; // set the times for sampling the Spot.
    }
    QLibrary::parametersConstant VolParam(Vol);
    QLibrary::parametersConstant rParam(r);
    QLibrary::parametersConstant dParam(d);
    QLibrary::PathDependentAsian theOption(Times, Expiry, ThePayoff);
    QLibrary::MCStatisticsMean gatherer;
    QLibrary::RandomMLCG gen(1UL,0);
    QLibrary::ExoticBachelierEngine theEngine(theOption,rParam,dParam,VolParam,gen,Spot);
    //auto start = std::chrono::high_resolution_clock::now();
    theEngine.DoSimulation(gatherer, NumberOfPaths);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> diff = end-start;
    //std::cout << "Elapsed time: " << diff.count() << " seconds\n";
    std::cout << gatherer.getResults()["mean"] << std::endl;
    return 0;
}
