// TestTree/main.cpp

#include <QLibrary/BinomialTree.h>
#include <QLibrary/TreeAmerican.h>
#include <QLibrary/TreeEuropean.h>
#include <QLibrary/TreeBarrier.h>
#include <QLibrary/Payoff.h>
#include <QLibrary/PayoffForward.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/BlackScholesFormulas.h>
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
    unsigned long Steps = 1000;
    QLibrary::parametersConstant rParam(r);
    QLibrary::parametersConstant dParam(d);

    QLibrary::PayoffCall ThePayoffCall(Strike);
    QLibrary::PayoffPut ThePayoffPut(Strike);

    QLibrary::TreeEuropean europeanCallOption(Expiry,ThePayoffCall);
    QLibrary::TreeAmerican americanCallOption(Expiry,ThePayoffCall);
    QLibrary::TreeEuropean europeanPutOption(Expiry,ThePayoffPut);
    QLibrary::TreeAmerican americanPutOption(Expiry,ThePayoffPut);
    std::cout << "Created European and American options" << std::endl;


    QLibrary::SimpleBinomialTree theTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    std::cout << "Created Binomial Tree" << std::endl;
    double euroCallPrice = theTree.GetThePrice(europeanCallOption);
    double americanCallPrice = theTree.GetThePrice(americanCallOption);
    double euroPutPrice = theTree.GetThePrice(europeanPutOption);
    double americanPutPrice = theTree.GetThePrice(americanPutOption);

    std::cout << "European Call option price: " << euroCallPrice << std::endl;
    std::cout << "American Call option price: " << americanCallPrice << std::endl;
    
    std::cout << "European Put option price: " << euroPutPrice << std::endl;
    std::cout << "American Put option price: " << americanPutPrice << std::endl;

    double bsCallPrice = QLibrary::BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
    double bsPutPrice = QLibrary::BlackScholesPut(Spot,Strike,r,d,Vol,Expiry);
    std::cout << "Black-Scholes formula Call price: " << bsCallPrice << std::endl;
    std::cout << "Black-Scholes formula Put price: " << bsPutPrice << std::endl;


    QLibrary::PayoffForward forwardPayoff(Strike);
    QLibrary::TreeEuropean forwardOption(Expiry,forwardPayoff);

    double forwardPrice = theTree.GetThePrice(forwardOption);
    std::cout << "forward price by tree: " << forwardPrice << std::endl;

    double actualForwardPrice = std::exp(-r*Expiry)*(Spot*std::exp((r-d)*Expiry)-Strike);
    std::cout << "actual forward price: " << actualForwardPrice << std::endl;

    double barrierLevel = 120.0;
    QLibrary::TreeBarrier barrierCallOption(Expiry,ThePayoffCall,barrierLevel);
    std::cout << "Created Barrier option" << std::endl;
    double barrierCallPrice = theTree.GetThePrice(barrierCallOption);
    std::cout << "Barrier Call option price: " << barrierCallPrice << std::endl;

    return 0;
}
