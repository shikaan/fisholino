#pragma once
#include <latebit/core/events/Event.h>

using namespace lb;

const std::string SCORE_EVENT = "score";

class ScoreEvent : public Event {
private:
  int m_points;

public:
  ScoreEvent(int points) {
    setType(SCORE_EVENT);
    m_points = points;
  }

  int getPoints() const { return m_points; }
};