#include <latebit/core/events/Event.h>

using namespace lb;
using namespace std;

const string BOOT = "boot";

class BootEvent : public Event {
public:
  BootEvent() { setType(BOOT); }
};