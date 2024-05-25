#include "state.h"
#include "events/events.h"
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>

using namespace lb;

int State::score = 0;

void State::setScore(int s) {
  State::score = s;
  WM.onEvent(new ScoreUpdated(s));
}

void State::addScore(int s) {
  State::score += s;
  WM.onEvent(new ScoreUpdated(State::score));
}

int State::getScore() { return State::score; }
