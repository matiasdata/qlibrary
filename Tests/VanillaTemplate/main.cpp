// Tests/VanillaOption/main.cpp
#include <iostream>
#include <QLibrary/SimpleMCTemplate.h>
#include <chrono>

int main()
{
    double Strike = 100;
    double Spot = 100;
    QLibrary::PayoffCallType callPayoff(Strike);
    QLibrary::PayoffPutType putPayoff(Strike);
    QLibrary::parametersConstant Vol{0.2};
    QLibrary::parametersPiecewise Vol2({0.0, 0.5, 1.0}, {0.4, 0.3, 0.2});
    QLibrary::parametersConstant r{0.05};
    QLibrary::parametersPiecewise r2({0.0, 0.5, 1.0}, {0.05, 0.04, 0.03});
    double Expiry = 1;
    unsigned long NumberOfPaths = 1000000;
    QLibrary::Vanilla<QLibrary::PayoffCallType> callOption(callPayoff,Expiry);
    QLibrary::MCStatisticsMean gatherer_call;
    QLibrary::ConvergenceTable gatherer_call_cv(gatherer_call);
    QLibrary::RandomMLCG rg(1,0);
    auto start = std::chrono::high_resolution_clock::now();
    QLibrary::SimpleMonteCarloTemplate(callOption, Spot, Vol2, r2, NumberOfPaths, gatherer_call, rg);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end-start;
    std::cout << "Elapsed time: " << diff.count() << " seconds\n";
    return 0;
}

