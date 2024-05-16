#pragma once
#include <latebit/core/events/Event.h>

using namespace lb;

const std::string GAME_OVER = "gameOver";

class GameOverEvent : public Event {
public:
  GameOverEvent() { setType(GAME_OVER); }
};