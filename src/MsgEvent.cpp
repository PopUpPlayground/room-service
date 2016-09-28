#include "MsgEvent.h"
#include <string>
#include <assert.h>

// Our event is a simple one, we display the string passed
// at creation!
bool MsgEvent::processEvent(print_f print, Game *queue) {
    print(msg.c_str());

    // Done with this message, clear it now.
    return true;
}
