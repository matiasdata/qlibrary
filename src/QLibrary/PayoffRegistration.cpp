// PayoffRegistration.cpp

#include <QLibrary/PayoffConstructible.h>

namespace QLibrary
{

namespace
{
PayoffHelper<PayoffCall> RegisterCall("call");

PayoffHelper<PayoffPut> RegisterPut("put");
}
// variables are global but invisible, as they are defined in an unnamed namespace.

} //namespace QLibrary