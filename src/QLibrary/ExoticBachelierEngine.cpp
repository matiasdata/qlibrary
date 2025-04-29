// ExoticBachelierEngine.cpp
#include <QLibrary/ExoticBachelierEngine.h>
#include <cmath>

namespace QLibrary{

ExoticBachelierEngine::ExoticBachelierEngine(const Wrapper<PathDependent>& TheProduct_,
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
    Drifts[0] = R_->Integral(0.0,Times[0]) - D_->Integral(0.0,Times[0]);
    StandardDeviations[0] = sqrt(Variance);

    for(unsigned long j = 1; j < NumberOfTimes; ++j)
    {
        double ThisVariance = Vol_->IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_->Integral(Times[j-1],Times[j]) - D_->Integral(Times[j-1],Times[j]);
        StandardDeviations[j] = sqrt(ThisVariance);
    }
    unsigned long last = NumberOfTimes-1;
    double Forward = Spot_ * exp(Drifts[last]);
    Variates.resize(NumberOfTimes);
}

void ExoticBachelierEngine::GetOnePath(MyArray& SpotValues)
{
    TheGenerator->getGaussians(Variates);
    double CurrentForward = Forward;
    unsigned long last = NumberOfTimes-1;
    for(unsigned long j = 0; j < NumberOfTimes; j++)
    {
        CurrentForward += StandardDeviations[j] * Variates[j];
        SpotValues[j] = CurrentForward * exp(-(Drifts[last]-Drifts[j]));
    }
    return;
}

}
