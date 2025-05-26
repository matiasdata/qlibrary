// Tests/ImpliedVolatility/Main.cpp

#include <QLibrary/Bisection.h>
#include <QLibrary/NewtonRaphson.h>
#include <QLibrary/BSCallClass.h>
#include <QLibrary/BSCallTwo.h>
#include <QLibrary/BlackScholesFormulas.h>
#include <iostream>

int main()
{
    double Expiry = 1.0;
    double Strike = 100.0;
    double Spot = 100.0;
    double r = 0.05;
    double d = 0.02;
    double Price = 10.0;
    double low = 0.05;
    double high = 0.5;
    double Tolerance = 1e-6;
    
    
    QLibrary::BSCall theCall(r,d,Expiry,Spot,Strike);
    // Alternatively, use lambda functions.
    auto theCallAlt = [r,d,Expiry,Spot,Strike](double vol) -> double
    {
        return QLibrary::BlackScholesCall(Spot,Strike,r,d,vol,Expiry);
    };

    double Vol1 = QLibrary::Bisection(Price,low,high,Tolerance,theCall);
    double Vol2 = QLibrary::Bisection(Price,low,high,Tolerance,theCallAlt);
    double Price1 = QLibrary::BlackScholesCall(Spot,Strike,r,d,Vol1,Expiry);
    double Price2 = QLibrary::BlackScholesCall(Spot,Strike,r,d,Vol2,Expiry);
    std::cout << "Vol1 = " << Vol1 << "\nPrice1 = " << Price1 << std::endl;
    std::cout << "Vol2 = " << Vol2 << "\nPrice2 = " << Price2 << std::endl;

    double guess = 0.1;

    QLibrary::BSCallTwo theCallTwo(r,d,Expiry,Spot,Strike);
    double VolNR = QLibrary::NewtonRaphson<QLibrary::BSCallTwo, &QLibrary::BSCallTwo::Price, &QLibrary::BSCallTwo::Vega>(Price,guess,Tolerance,theCallTwo);
    double PriceNR = QLibrary::BlackScholesCall(Spot,Strike,r,d,VolNR,Expiry);
    std::cout << "VolNR = " << VolNR << "\nPriceNR = " << PriceNR << std::endl;
    return 0;
}