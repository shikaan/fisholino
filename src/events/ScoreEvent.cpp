#include <latebit/core/events/Event.h>

using namespace lb;

const std::string SCORE_EVENT = "score";

class ScoreEvent : public Event {
private:
  int points;

public:
  ScoreEvent(int points) {
    setType(SCORE_EVENT);
    this->points = points;
  }

  int getPoints() const { return points; }
};