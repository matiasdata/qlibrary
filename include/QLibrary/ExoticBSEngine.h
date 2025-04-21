// ExoticBSEngine.h
#include <QLibrary/ExoticEngine.h>
#include <QLibrary/RandomGen.h>


class ExoticBSEngine : public ExoticEngine
{
public:
    ExoticBSEngine(const Wrapper<PathDependent>& TheProduct_,
                    const Wrapper<Parameters>& R_,
                    const Wrapper<Parameters>& D_,
                    const Wrapper<Parameters>& Vol_,
                    const Wrapper<RandomBase>& TheGenerator_,
                    double Spot_);
    
    virtual void GetOnePath(MyArray& SpotValues) override;
    virtual ~ExoticBSEngine() override = default;
private:
        Wrapper<RandomBase> TheGenerator;
        MyArray Drifts;
        MyArray StandardDeviations;
        double LogSpot;
        unsigned long NumberOfTimes;
        MyArray Variates;
};

/*
ExoticBSEngine is an simulation engine for the Black-Scholes model, which accepts time-dependent deterministic parameters. 

It stores a random number generator. It also stores drifts and standard deviations as these are path independent. 
Main formula to compute spot values is:
log S_{t_{j+1}} = log S_{t_j} + \int_{t_j}^{t_{j+1}} r(s) - d(s) - 0.5 * sigma(s)^2 ds + \sqrt{\int_{t_j}^{t_{j+1}} sigma(s)^2 ds} W_{j+1}

*/