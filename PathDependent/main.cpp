// main.cpp
#include <QLibrary/PathDependentAsian.h>
#include <QLibrary/ExoticBSEngine.h>
#include <QLibrary/MCStatistics.h>
#include <QLibrary/RandomGen.h>
#include <iostream>


int main()
{
    double Expiry = 1.0;
    double Strike = 100.0;
    double Spot = 100.0;
    double Vol = 0.2;
    double r = 0.05;
    double d = 0.02; // dividend rate
    unsigned long NumberOfPaths = 1000000;
    unsigned long NumberOfDates = 12;
    PayoffCall ThePayoff(Strike);
    MyArray Times(NumberOfDates);
    for(unsigned long i = 0; i < NumberOfDates; i++)
    {
        Times[i] = (i+1.0)*Expiry/NumberOfDates;
    }
    parametersConstant VolParam(Vol);
    parametersConstant rParam(r);
    parametersConstant dParam(d);
    PathDependentAsian theOption(Times, Expiry, ThePayoff);
    MCStatisticsMean<double> gatherer;
    RandomMLCG gen(NumberOfDates,0);
    ExoticBSEngine theEngine(theOption,rParam,dParam,VolParam,gen,Spot);
    theEngine.DoSimulation(gatherer, NumberOfPaths);
    std::cout << gatherer.getResults()["mean"] << std::endl;
    return 0;
}