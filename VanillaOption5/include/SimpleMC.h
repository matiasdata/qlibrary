#pragma once
#include <Payoff.h>
#include <Vanilla.h>
#include <Parameters.h>
#include <MCStatistics.h>
#include <RandomGen.h>

void SimpleMonteCarlo(const VanillaOption& theOption,
                        double Spot,
                        const Parameters& Vol,
                        const Parameters& r,
                        unsigned long NumberOfPaths,
                        MCStatistics<double>& gatherer,
                        RandomBase& rg);

#include "SimpleMC.tpp"