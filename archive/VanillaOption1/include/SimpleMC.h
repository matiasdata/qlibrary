#pragma once
#include <Payoff.h>
#include <Vanilla.h>

double SimpleMonteCarlo(const VanillaOption& theOption,
                        double Spot,
                        double Vol,
                        double r,
                        unsigned long NumberOfPaths);

#include "SimpleMC.tpp"