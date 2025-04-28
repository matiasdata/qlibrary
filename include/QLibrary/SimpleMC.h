#pragma once
#include <QLibrary/Payoff.h>
#include <QLibrary/Vanilla.h>
#include <QLibrary/Parameters.h>
#include <QLibrary/MCStatistics.h>
#include <QLibrary/RandomGen.h>

namespace QLibrary{

void SimpleMonteCarlo(const VanillaOption& theOption,
                        double Spot,
                        const Parameters& Vol,
                        const Parameters& r,
                        unsigned long NumberOfPaths,
                        MCStatistics& gatherer,
                        RandomBase& rg);

}