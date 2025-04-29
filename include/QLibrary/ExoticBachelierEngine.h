// ExoticBachelierEngine.h
#include <QLibrary/ExoticEngine.h>
#include <QLibrary/RandomGen.h>

namespace QLibrary{

class ExoticBachelierEngine : public ExoticEngine
{
public:
    ExoticBachelierEngine(const Wrapper<PathDependent>& TheProduct_,
                    const Wrapper<Parameters>& R_,
                    const Wrapper<Parameters>& D_,
                    const Wrapper<Parameters>& Vol_,
                    const Wrapper<RandomBase>& TheGenerator_,
                    double Spot_);
    
    virtual void GetOnePath(MyArray& SpotValues) override;
    virtual ~ExoticBachelierEngine() override = default;
private:
        Wrapper<RandomBase> TheGenerator;
        MyArray Drifts;
        MyArray StandardDeviations;
        double Forward;
        unsigned long NumberOfTimes;
        MyArray Variates;
};

}
