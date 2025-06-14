// ExoticBSEngine.cpp
#include <QLibrary/ExoticBSEngine.h>
#include <cmath>

namespace QLibrary{

ExoticBSEngine::ExoticBSEngine(const Wrapper<PathDependent>& TheProduct_,
        const Wrapper<Parameters>& R_,
        const Wrapper<Parameters>& D_,
        const Wrapper<Parameters>& Vol_,
        const Wrapper<RandomBase>& TheGenerator_,
        double Spot_) : ExoticEngine{TheProduct_,R_}, TheGenerator{TheGenerator_}
{
    MyArray Times(TheProduct_->GetLookAtTimes());
    NumberOfTimes = Times.size();

    TheGenerator->resetDimensionality(NumberOfTimes);
    Drifts.resize(NumberOfTimes);
    StandardDeviations.resize(NumberOfTimes);

    double Variance = Vol_->IntegralSquare(0.0,Times[0]);
    Drifts[0] = R_->Integral(0.0,Times[0]) - D_->Integral(0.0,Times[0]) - 0.5 * Variance;
    StandardDeviations[0] = std::sqrt(Variance);

    for(unsigned long j = 1; j < NumberOfTimes; ++j)
    {
        double ThisVariance = Vol_->IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_->Integral(Times[j-1],Times[j]) - D_->Integral(Times[j-1],Times[j]) - 0.5 * ThisVariance;
        StandardDeviations[j] = std::sqrt(ThisVariance);
    }
    LogSpot = std::log(Spot_);
    Variates.resize(NumberOfTimes);
}

void ExoticBSEngine::GetOnePath(MyArray& SpotValues)
{
    TheGenerator->getGaussians(Variates);
    double CurrentLogSpot = LogSpot;
    for(unsigned long j = 0; j < NumberOfTimes; j++)
    {
        CurrentLogSpot += Drifts[j];
        CurrentLogSpot += StandardDeviations[j] * Variates[j];
        SpotValues[j] = std::exp(CurrentLogSpot);
    }
    return;
}

}

/*
The constructor precomputes all the drifts and standard deviations needed to compute pats.
It also computes the NumberOfTimes from TheProduct, sets the RNG to be of the appropriate dimensionality, and resizes the variates. 
It also computes the LogSpot, as it will be used repeatedly to compute SpotValues paths. 

virtual void GetOnePath(MyArray& SpotValues) override: 
Computes a SpotValues path
        1) Generate Gaussians and stores these in the Variates. 
        2) computes the logSpot at each date by using the precomputed drifts, standard deviations and gaussian variates. 
        3) Takes the exponential to compute each Spot value. 
*/