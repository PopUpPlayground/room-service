#include "MsgEvent.h"
#include <string>
#include <assert.h>

// Our event is a simple one, we return the string passed
// at creation!
std::string MsgEvent::processEvent() {
    return msg;
}
