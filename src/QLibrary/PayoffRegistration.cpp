// PayoffRegistration.cpp

#include <QLibrary/PayoffConstructible.h>
#include <QLibrary/PayoffForward.h>
#include <QLibrary/PayoffStraddle.h>

namespace QLibrary
{

namespace
{
PayoffHelper<PayoffCall> RegisterCall("call");

PayoffHelper<PayoffPut> RegisterPut("put");

PayoffHelper<PayoffForward> RegisterForward("forward");

PayoffHelper<PayoffStraddle> RegisterStraddle("straddle");

PayoffHelper<PayoffDoubleDigital> RegisterDoubleDigital("doubleDigital");

}
// variables are global but invisible, as they are defined in an unnamed namespace.

} //namespace QLibrary