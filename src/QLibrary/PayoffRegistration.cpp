// PayoffRegistration.cpp

#include <QLibrary/PayoffConstructible.h>
#include <QLibrary/PayoffForward.h>

namespace QLibrary
{

namespace
{
PayoffHelper<PayoffCall> RegisterCall("call");

PayoffHelper<PayoffPut> RegisterPut("put");

PayoffHelper<PayoffForward> RegisterForward("forward");

}
// variables are global but invisible, as they are defined in an unnamed namespace.

} //namespace QLibrary