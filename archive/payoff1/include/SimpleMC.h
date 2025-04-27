#pragma once
#include <Payoff1.h>

double SimpleMonteCarlo(const Payoff& thePayoff,
                        double Expiry,
                        double Spot,
                        double Vol,
                        double r,
                        unsigned long NumberOfPaths);

#include "SimpleMC.tpp"