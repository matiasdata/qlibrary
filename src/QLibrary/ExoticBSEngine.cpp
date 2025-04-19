// ExoticBSEngine.cpp
#include <QLibrary/ExoticBSEngine.h>
#include <cmath>

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
    StandardDeviations[0] = sqrt(Variance);

    for(unsigned long j = 1; j < NumberOfTimes; ++j)
    {
        double ThisVariance = Vol_->IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_->Integral(Times[j-1],Times[j]) - D_->Integral(Times[j-1],Times[j]) - 0.5 * ThisVariance;
        StandardDeviations[j] = sqrt(ThisVariance);
    }
    LogSpot = log(Spot_);
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
        SpotValues[j] = exp(CurrentLogSpot);
    }
    return;
}