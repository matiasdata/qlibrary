// main.cpp
#include <QLibrary/PathDependentBarrier.h>
#include <QLibrary/ExoticBSEngine.h>
#include <QLibrary/MCStatistics.h>
#include <QLibrary/RandomGen.h>
#include <QLibrary/Vanilla.h>
#include <QLibrary/SimpleMC.h>
#include <iostream>
//#include <chrono>

using namespace QLibrary;

int main()
{
    double Expiry = 1.0;
    double Strike = 100.0;
    double Spot = 100.0;
    double Vol = 0.2;
    double r = 0.05;
    double d = 0.02; // dividend rate
    double level = 120.0;
    double rebate = 5.0;
    unsigned long NumberOfPaths = 1000000;
    unsigned long NumberOfDates = 12;
    PayoffCall ThePayoff(Strike);
    UpOutBarrier TheUpOutBarrier(level,rebate);
    
    MyArray Times(NumberOfDates);
    for(unsigned long i = 0; i < NumberOfDates; i++)
    {
        Times[i] = (i+1.0)*Expiry/NumberOfDates; // set the times for sampling the Spot.
    }
    parametersConstant VolParam(Vol);
    parametersConstant rParam(r);
    parametersConstant dParam(d);
    PathDependentBarrier TheUpOutBarrierOption(Times,ThePayoff,TheUpOutBarrier);
    MCStatisticsMean gathererUpOut;
    RandomMLCG gen(1UL,0);
    ExoticBSEngine theEngine(TheUpOutBarrierOption,rParam,dParam,VolParam,gen,Spot);
    // auto start = std::chrono::high_resolution_clock::now();
    theEngine.DoSimulation(gathererUpOut, NumberOfPaths);
    // auto end = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> diff = end-start;
    // std::cout << "Elapsed time: " << diff.count() << " seconds\n";
    std::cout << "MC Up Out Barrier Call Price: " << gathererUpOut.getResults()["mean"] << std::endl;

    MCStatisticsMean gathererUpIn;
    UpInBarrier TheUpInBarrier(level,rebate);
    PathDependentBarrier TheUpInBarrierOption(Times,ThePayoff,TheUpInBarrier);
    gen.reset();
    theEngine = ExoticBSEngine(TheUpInBarrierOption,rParam,dParam,VolParam,gen,Spot);
    theEngine.DoSimulation(gathererUpIn, NumberOfPaths);
    std::cout << "MC Up In Barrier Call Price: " << gathererUpIn.getResults()["mean"] << std::endl;


    std::cout << "Resetting parameters" << std::endl;

    d = 0.0;
    dParam = parametersConstant(d); // update dividend rate to zero
    TheUpOutBarrier = UpOutBarrier(level); // update rebate to zero. (default value)
    TheUpOutBarrierOption = PathDependentBarrier(Times,ThePayoff,TheUpOutBarrier);
    TheUpInBarrier = UpInBarrier(level); // update rebate to zero. (default value)
    TheUpInBarrierOption = PathDependentBarrier(Times,ThePayoff,TheUpInBarrier);

    gathererUpOut.reset();
    gen.reset();
    theEngine = ExoticBSEngine(TheUpOutBarrierOption,rParam,dParam,VolParam,gen,Spot);
    theEngine.DoSimulation(gathererUpOut, NumberOfPaths);
    double UpOutBarrierPrice = gathererUpOut.getResults()["mean"];
    std::cout << "MC Up Out Barrier Call Price: " << UpOutBarrierPrice << std::endl;

    gathererUpIn.reset();
    gen.reset();
    theEngine = ExoticBSEngine(TheUpInBarrierOption,rParam,dParam,VolParam,gen,Spot);
    theEngine.DoSimulation(gathererUpIn, NumberOfPaths);
    double UpInBarrierPrice = gathererUpIn.getResults()["mean"];
    std::cout << "MC Up Out Barrier Call Price: " << UpInBarrierPrice << std::endl;

    MCStatisticsMean gathererVanilla;
    gen.reset();
    VanillaOption callOption(ThePayoff,Expiry);
    SimpleMonteCarlo(callOption,Spot,VolParam,rParam,NumberOfPaths,gathererVanilla,gen);
    double VanillaCallPrice = gathererVanilla.getResults()["mean"];
    std::cout << "MC Vanilla call Price: " << VanillaCallPrice << std::endl;


    return 0;
}