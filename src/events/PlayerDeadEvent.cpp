#include <latebit/core/events/Event.h>

using namespace lb;

const std::string PLAYER_DEAD = "playerDead";

class PlayerDeadEvent : public Event {
public:
  PlayerDeadEvent() { setType(PLAYER_DEAD); }
};