// Tree/main.cpp

#include <QLibrary/BinomialTree.h>
#include <QLibrary/LightBinomialTree.h>
#include <QLibrary/TrinomialTree.h>
#include <QLibrary/BinomialTreeVol.h>
#include <QLibrary/KnockInBinomialTree.h>
#include <QLibrary/TreeAmerican.h>
#include <QLibrary/TreeEuropean.h>
#include <QLibrary/TreeBarrier.h>
#include <QLibrary/TreeKnockIn.h>
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
    unsigned long Steps = 100;
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
    double euroCallPriceMartingale = theTree.GetThePrice(europeanCallOption, true);
    double americanCallPrice = theTree.GetThePrice(americanCallOption);
    double euroPutPrice = theTree.GetThePrice(europeanPutOption);
    double americanPutPrice = theTree.GetThePrice(americanPutOption);

    std::cout << "European Call option price: " << euroCallPrice << std::endl;
    std::cout << "European Call option price (Martingale): " << euroCallPriceMartingale << std::endl;
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
    QLibrary::TreeOutBarrier barrierUpCallOption(Expiry,ThePayoffCall,barrierLevel,QLibrary::TreeOutBarrier::BarrierType::Up);
    std::cout << "Created Up and Out Barrier option" << std::endl;
    double barrierUpOutCallPrice = theTree.GetThePrice(barrierUpCallOption);
    std::cout << "Barrier  Up and Out Call option price: " << barrierUpOutCallPrice << std::endl;
    double barrierUpInCallPrice = barrierUpCallOption.PriceInBarrier(theTree);
    std::cout << "Barrier  Up and In Call option price: " << barrierUpInCallPrice << std::endl;

    QLibrary::LightBinomialTree theLightTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    double euroCallPriceLight = theLightTree.GetThePrice(europeanCallOption);
    std::cout << "European Call option price (Light): " << euroCallPriceLight << std::endl;

    QLibrary::SimpleTrinomialTree theTrinomialTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    double euroCallPriceTrinomial = theTrinomialTree.GetThePrice(europeanCallOption);
    std::cout << "European Call option price (Trinomial): " << euroCallPriceTrinomial << std::endl;


    QLibrary::parametersPiecewise VolParam({0.0, 0.25, 0.5, 0.75, 1.0}, {0.4, 0.35, 0.3, 0.25, 0.2});
    double realizedVariance = VolParam.IntegralSquare(0.0,1.0);
    double volVar = std::sqrt(realizedVariance/Expiry);
    QLibrary::BinomialTreeVol theVariableVolTree(Spot,rParam,dParam,VolParam,Steps,Expiry);
    std::cout << "Created Binomial Tree with variable Volatility" << std::endl;
    double euroCallPriceVarVol = theVariableVolTree.GetThePrice(europeanCallOption);
    std::cout << "European Call Option Price on model with Variable Volatility: " << euroCallPriceVarVol << std::endl;
    double bsCallPriceVarVol = QLibrary::BlackScholesCall(Spot,Strike,r,d,volVar,Expiry);
    std::cout << "Black-Scholes formula Call price on model with Variable Volatility: " << bsCallPriceVarVol << std::endl;

    barrierLevel = 80.0;
    QLibrary::KnockInBinomialTree theKnockInTree(Spot,rParam,dParam,Vol,Steps,Expiry);
    QLibrary::TreeKnockIn americanKnockInPutOption(Expiry,ThePayoffPut,barrierLevel,QLibrary::TreeKnockIn::BarrierType::Down);
    double americanKnockInPutPrice = theKnockInTree.GetThePrice(americanKnockInPutOption);
    std::cout << "American Knock In Barrier Put Price: " << americanKnockInPutPrice << std::endl;

    return 0;
}
