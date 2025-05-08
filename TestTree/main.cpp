// TestTree/main.cpp

#include <QLibrary/BinomialTree.h>
#include <QLibrary/TreeAmerican.h>
#include <QLibrary/TreeEuropean.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffForward.h>
#include <QLibrary/Parameters.h>
#include <iostream>
#include <cmath>

int main()
{
    double Expiry = 1.0;
    double Strike = 100.0;
    double Spot = 100.0;
    double r = 0.05;
    double d = 0.02;
    double Vol = 0.2;
    unsigned long Steps = 12;
    QLibrary::parametersConstant rParam(r);
    QLibrary::parametersConstant dParam(d);

    QLibrary::PayoffCall ThePayoff(Strike);

    QLibrary::TreeEuropean europeanOption(Expiry,ThePayoff);
    QLibrary::TreeAmerican americanOption(Expiry,ThePayoff);
    std::cout << americanOption.PreFinalValue(120,0.5,121.5) << std::endl;

    QLibrary::SimpleBinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    std::cout << "Created Binomial Tree" << std::endl;
    double euroPrice = theTree.GetThePrice(europeanOption);
    double americanPrice = theTree.GetThePrice(americanOption);

    std::cout << "European option price: " << euroPrice << std::endl;
    std::cout << "American option price: " << americanPrice << std::endl;

    QLibrary::PayoffForward forwardPayoff(Strike);
    QLibrary::TreeEuropean forwardOption(Expiry,forwardPayoff);

    double forwardPrice = theTree.GetThePrice(forwardOption);
    std::cout << "forward price by tree: " << forwardPrice << std::endl;

    double actualForwardPrice = std::exp(-r*Expiry)*(Spot*std::exp((r-d)*Expiry)-Strike);
    std::cout << "actual forward price: " << actualForwardPrice << std::endl;

    return 0;
}
