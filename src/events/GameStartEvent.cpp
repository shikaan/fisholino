#include <latebit/core/events/Event.h>

using namespace lb;

const std::string GAME_START = "gameStart";

class GameStartEvent : public Event {
public:
  GameStartEvent() { setType(GAME_START); }
};