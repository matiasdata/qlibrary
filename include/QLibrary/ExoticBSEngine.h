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
    
    virtual void GetOnePath(MyArray& SpotValues);
    virtual ~ExoticBSEngine(){};
private:
        Wrapper<RandomBase> TheGenerator;
        MyArray Drifts;
        MyArray StandardDeviations;
        double LogSpot;
        unsigned long NumberOfTimes;
        MyArray Variates;

};