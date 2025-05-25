// Tests/ImpliedVolatility/Main.cpp

#include <QLibrary/Bisection.h>
#include <QLibrary/BSCallClass.h>
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
    double Vol = QLibrary::Bisection(Price,low,high,Tolerance,theCall);
    double PriceTwo = QLibrary::BlackScholesCall(Spot,Strike,r,d,Vol,Expiry);
    std::cout << "Vol = " << Vol << "\nPriceTwo = " << PriceTwo << std::endl;
    return 0;
}