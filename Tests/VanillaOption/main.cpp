// /TestVanillaOption/main.cpp
#include <iostream>
#include <QLibrary/SimpleMC.h>
//#include <chrono>

int main()
{
    double Strike = 100;
    double Spot = 100;
    QLibrary::PayoffCall callPayoff(Strike);
    QLibrary::PayoffPut putPayoff(Strike);
    double Lower = 100;
    double Upper = 120;
    QLibrary::PayoffDoubleDigital doubleDigitalPayoff(Lower,Upper);
    QLibrary::parametersConstant Vol{0.2};
    QLibrary::parametersPiecewise Vol2({0.0, 0.5, 1.0}, {0.4, 0.3, 0.2});
    QLibrary::parametersConstant r{0.05};
    QLibrary::parametersPiecewise r2({0.0, 0.5, 1.0}, {0.05, 0.04, 0.03});
    double Expiry = 1;
    unsigned long NumberOfPaths = 1000000;
    QLibrary::VanillaOption callOption(callPayoff,Expiry);
    QLibrary::VanillaOption putOption(putPayoff,Expiry);
    QLibrary::VanillaOption doubleDigitalOption(doubleDigitalPayoff,Expiry);
    QLibrary::MCStatisticsMean gatherer_call, gatherer_put, gatherer_doubleDigital;
    QLibrary::ConvergenceTable gatherer_call_cv(gatherer_call);
    QLibrary::RandomMLCG rg(1,0);
    //auto start = std::chrono::high_resolution_clock::now();
    QLibrary::SimpleMonteCarlo(callOption, Spot, Vol2, r2, NumberOfPaths,gatherer_call,rg);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> diff = end-start;
    //std::cout << "Elapsed time: " << diff.count() << " seconds\n";
    QLibrary::SimpleMonteCarlo(putOption, Spot, Vol2, r2, NumberOfPaths,gatherer_put,rg);
    QLibrary::SimpleMonteCarlo(doubleDigitalOption, Spot, Vol2, r2, NumberOfPaths, gatherer_doubleDigital,rg);
    // Print MC simulation results
    std::cout << "Monte Carlo price of a call: " << gatherer_call.getResults()["mean"] << std::endl;
    std::cout << "Monte Carlo price of a put: " << gatherer_put.getResults()["mean"] << std::endl;
    std::cout << "Monte Carlo price of a double digital: " << gatherer_doubleDigital.getResults()["mean"] << std::endl;
    // Convergence Table
    QLibrary::SimpleMonteCarlo(callOption, Spot, Vol2, r2, NumberOfPaths,gatherer_call_cv,rg);
    std::map<std::string, std::vector<double>> results = gatherer_call_cv.getConvergenceTable();
    // Print the results of the convergence table
    std::cout << "Convergence of MC of a call: "<< std::endl;
    for (const auto& entry : results) {
        std::cout << entry.first << ": ";
        for (double value : entry.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

