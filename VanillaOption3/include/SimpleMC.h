#pragma once
#include <Payoff.h>
#include <Vanilla.h>
#include <Parameters.h>

double SimpleMonteCarlo(const VanillaOption& theOption,
                        double Spot,
                        const Parameters& Vol,
                        const Parameters& r,
                        unsigned long NumberOfPaths);

#include "SimpleMC.tpp"